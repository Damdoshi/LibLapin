#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_rudp_phase5.$$}"
BASE_PORT="${BASE_PORT:-$((54000 + ($$ % 10000)))}"
mkdir -p "$TMPDIR"

PASS=0
FAIL=0

log() { printf '[%s] %s\n' "$(date +%H:%M:%S)" "$*"; }
pass() { log "PASS: $*"; PASS=$((PASS + 1)); }
fail() { log "FAIL: $*"; FAIL=$((FAIL + 1)); }

cleanup() {
  jobs -p | xargs -r kill 2>/dev/null || true
  wait 2>/dev/null || true
}
trap cleanup EXIT INT TERM

show_log() {
  local title="$1"
  local file="$2"
  log "--- $title ---"
  [ -f "$file" ] && sed -n '1,220p' "$file" || echo "(missing log)"
}

summary_value() {
  local key="$1"
  local file="$2"
  grep '^\[SUMMARY\]' "$file" | tail -1 | tr ' ' '\n' | awk -F= -v k="$key" '$1 == k { print $2; exit }'
}

peer_sum_value() {
  local key="$1"
  local file="$2"
  grep '^\[PEER\]' "$file" | tr ' ' '\n' | awk -F= -v k="$key" '$1 == k { s += $2 } END { print s + 0 }'
}

basic_bad_log() {
  local f="$1"
  grep -q '\[OPEN\] failed' "$f" && return 0
  grep -q '\[SEND\].*FAIL' "$f" && return 0
  grep -q 'from peer -1' "$f" && return 0
  return 1
}

duplicates_bad_log() {
  local f="$1"
  grep -q 'seq_duplicates=[1-9]' "$f" && return 0
  return 1
}

check_pair_loss_data() {
  local name="$1" a="$2" b="$3" min_a="$4" min_b="$5"
  show_log "$name A" "$a"
  show_log "$name B" "$b"
  if basic_bad_log "$a" || basic_bad_log "$b" || duplicates_bad_log "$a" || duplicates_bad_log "$b"; then
    fail "$name (bad log)"
    return
  fi
  local ra rb da db
  ra=$(summary_value received_messages "$a")
  rb=$(summary_value received_messages "$b")
  da=$(peer_sum_value seq_duplicates "$a")
  db=$(peer_sum_value seq_duplicates "$b")
  : "${ra:=0}"; : "${rb:=0}"; : "${da:=0}"; : "${db:=0}"
  if [ "$ra" -lt "$min_a" ] || [ "$rb" -lt "$min_b" ] || [ "$da" -ne 0 ] || [ "$db" -ne 0 ]; then
    fail "$name (received A=$ra/$min_a B=$rb/$min_b dupA=$da dupB=$db)"
    return
  fi
  pass "$name"
}

check_pair_ack_loss() {
  local name="$1" a="$2" b="$3" min_a="$4" min_b="$5"
  show_log "$name A" "$a"
  show_log "$name B" "$b"
  if basic_bad_log "$a" || basic_bad_log "$b" || duplicates_bad_log "$a" || duplicates_bad_log "$b"; then
    fail "$name (bad log)"
    return
  fi
  local ra rb da db
  ra=$(summary_value received_messages "$a")
  rb=$(summary_value received_messages "$b")
  da=$(peer_sum_value seq_duplicates "$a")
  db=$(peer_sum_value seq_duplicates "$b")
  : "${ra:=0}"; : "${rb:=0}"; : "${da:=0}"; : "${db:=0}"
  if [ "$ra" -lt "$min_a" ] || [ "$rb" -lt "$min_b" ] || [ "$da" -ne 0 ] || [ "$db" -ne 0 ]; then
    fail "$name (received A=$ra/$min_a B=$rb/$min_b dupA=$da dupB=$db)"
    return
  fi
  pass "$name"
}

run_pair_loss_data() {
  local name="rudp_data_loss_retransmit"
  local port=$((BASE_PORT + 0))
  local a="$TMPDIR/${name}_A.log"
  local b="$TMPDIR/${name}_B.log"
  log "=== CASE $name ==="
  log "A: LIBLAPIN_RUDP_DROP_DATA_MOD=3 $PROG -p rudp -L $port -n 24 -i 40 -s 128 --seq --quiet-payload -D 6500 -F 500 -m A"
  LIBLAPIN_RUDP_DROP_DATA_MOD=3 "$PROG" -p rudp -L "$port" -n 24 -i 40 -s 128 --seq --quiet-payload -D 6500 -F 500 -m A >"$a" 2>&1 &
  local apid=$!
  sleep 1
  log "B: LIBLAPIN_RUDP_DROP_DATA_MOD=3 $PROG -p rudp -R 127.0.0.1 $port -n 24 -i 40 -s 128 --seq --quiet-payload -D 5200 -F 500 -m B"
  LIBLAPIN_RUDP_DROP_DATA_MOD=3 "$PROG" -p rudp -R 127.0.0.1 "$port" -n 24 -i 40 -s 128 --seq --quiet-payload -D 5200 -F 500 -m B >"$b" 2>&1 &
  local bpid=$!
  wait "$bpid" || true
  wait "$apid" || true
  check_pair_loss_data "$name" "$a" "$b" 24 24
}

run_pair_loss_ack() {
  local name="rudp_ack_loss_retransmit_no_duplicate"
  local port=$((BASE_PORT + 1))
  local a="$TMPDIR/${name}_A.log"
  local b="$TMPDIR/${name}_B.log"
  log "=== CASE $name ==="
  LIBLAPIN_RUDP_DROP_ACK_MOD=2 "$PROG" -p rudp -L "$port" -n 16 -i 50 -s 96 --seq --quiet-payload -D 6500 -F 500 -m A >"$a" 2>&1 &
  local apid=$!
  sleep 1
  LIBLAPIN_RUDP_DROP_ACK_MOD=2 "$PROG" -p rudp -R 127.0.0.1 "$port" -n 16 -i 50 -s 96 --seq --quiet-payload -D 5200 -F 500 -m B >"$b" 2>&1 &
  local bpid=$!
  wait "$bpid" || true
  wait "$apid" || true
  check_pair_ack_loss "$name" "$a" "$b" 16 16
}

run_many_senders_loss() {
  local name="rudp_many_senders_data_loss"
  local port=$((BASE_PORT + 2))
  local l="$TMPDIR/${name}_listener.log"
  local pids=""
  log "=== CASE $name ==="
  LIBLAPIN_RUDP_DROP_DATA_MOD=4 "$PROG" -p rudp -L "$port" -s 256 --no-send --seq --quiet-payload -D 7000 -F 500 -m listener >"$l" 2>&1 &
  local lpid=$!
  sleep 1
  for i in 0 1 2; do
    local f="$TMPDIR/${name}_S${i}.log"
    LIBLAPIN_RUDP_DROP_DATA_MOD=4 "$PROG" -p rudp -R 127.0.0.1 "$port" -s 256 -n 12 -i 50 --seq --quiet-payload -D 4500 -F 500 -m "S$i" >"$f" 2>&1 &
    pids="$pids $!"
    sleep 0.15
  done
  for p in $pids; do wait "$p" || true; done
  wait "$lpid" || true
  show_log "$name listener" "$l"
  for i in 0 1 2; do show_log "$name S$i" "$TMPDIR/${name}_S${i}.log"; done
  if basic_bad_log "$l" || duplicates_bad_log "$l"; then
    fail "$name (bad listener log)"
    return
  fi
  local peers rec dup
  peers=$(summary_value peers "$l")
  rec=$(summary_value received_messages "$l")
  dup=$(peer_sum_value seq_duplicates "$l")
  : "${peers:=0}"; : "${rec:=0}"; : "${dup:=0}"
  if [ "$peers" -ne 3 ] || [ "$rec" -lt 36 ] || [ "$dup" -ne 0 ]; then
    fail "$name (peers=$peers rec=$rec dup=$dup)"
    return
  fi
  pass "$name"
}

main() {
  [ -x "$PROG" ] || { echo "Binary not found or not executable: $PROG" >&2; exit 1; }
  log "Using BASE_PORT=$BASE_PORT"
  run_pair_loss_data
  run_pair_loss_ack
  run_many_senders_loss
  echo
  echo "=============================="
  echo "PASS: $PASS"
  echo "FAIL: $FAIL"
  echo "BASE_PORT: $BASE_PORT"
  echo "Logs: $TMPDIR"
  echo "=============================="
  echo
  [ "$FAIL" -eq 0 ]
}

main "$@"
