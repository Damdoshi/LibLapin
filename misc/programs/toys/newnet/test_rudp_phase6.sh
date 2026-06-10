#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_rudp_phase6.$$}"
BASE_PORT="${BASE_PORT:-$((60000 + ($$ % 5000)))}"
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

first_seq_value() {
  local file="$1"
  sed -n 's/^\[SEQ\] peer [0-9][0-9]* first=\([0-9][0-9]*\)$/\1/p' "$file" | head -1
}

has_bad_basics() {
  local f="$1"
  grep -q "\[OPEN\] failed" "$f" && return 0
  grep -q "\[SEND\].*FAIL" "$f" && return 0
  grep -q "from peer -1" "$f" && return 0
  return 1
}

check_unordered_first_drop_oneway() {
  local name="rudp_unordered_first_drop_oneway"
  local port=$((BASE_PORT + 0))
  local recv="$TMPDIR/${name}_recv.log"
  local send="$TMPDIR/${name}_send.log"

  log "=== CASE $name ==="
  LIBLAPIN_RUDP_DROP_DATA_SEQ=0 "$PROG" -p rudp -L "$port" --no-send --seq --quiet-payload -D 4200 -F 500 -m recv >"$recv" 2>&1 &
  local rpid=$!
  sleep 1
  "$PROG" -p rudp -R 127.0.0.1 "$port" -n 8 -i 40 -s 96 --seq --quiet-payload -D 3000 -F 500 -m send >"$send" 2>&1 &
  local spid=$!
  wait "$spid" || true
  wait "$rpid" || true

  show_log "$name recv" "$recv"
  show_log "$name send" "$send"

  if has_bad_basics "$recv" || has_bad_basics "$send"; then
    fail "$name (bad log)"
    return
  fi

  local rec first
  rec=$(summary_value received_messages "$recv")
  first=$(first_seq_value "$recv")
  : "${rec:=0}"; : "${first:=0}"
  if [ "$rec" -lt 8 ] || [ "$first" -eq 0 ]; then
    fail "$name (rec=$rec first=$first)"
    return
  fi
  pass "$name"
}

check_unordered_first_drop_bidirectional() {
  local name="rudp_unordered_first_drop_bidirectional"
  local port=$((BASE_PORT + 1))
  local a="$TMPDIR/${name}_A.log"
  local b="$TMPDIR/${name}_B.log"

  log "=== CASE $name ==="
  LIBLAPIN_RUDP_DROP_DATA_SEQ=0 "$PROG" -p rudp -L "$port" -n 12 -i 35 -s 128 --seq --quiet-payload -D 6200 -F 500 -m A >"$a" 2>&1 &
  local apid=$!
  sleep 1
  LIBLAPIN_RUDP_DROP_DATA_SEQ=0 "$PROG" -p rudp -R 127.0.0.1 "$port" -n 12 -i 35 -s 128 --seq --quiet-payload -D 5200 -F 500 -m B >"$b" 2>&1 &
  local bpid=$!
  wait "$bpid" || true
  wait "$apid" || true

  show_log "$name A" "$a"
  show_log "$name B" "$b"

  if has_bad_basics "$a" || has_bad_basics "$b"; then
    fail "$name (bad log)"
    return
  fi

  local ra rb fa fb
  ra=$(summary_value received_messages "$a")
  rb=$(summary_value received_messages "$b")
  fa=$(first_seq_value "$a")
  fb=$(first_seq_value "$b")
  : "${ra:=0}"; : "${rb:=0}"; : "${fa:=0}"; : "${fb:=0}"
  if [ "$ra" -lt 12 ] || [ "$rb" -lt 12 ] || [ "$fa" -eq 0 ] || [ "$fb" -eq 0 ]; then
    fail "$name (A rec=$ra first=$fa, B rec=$rb first=$fb)"
    return
  fi
  pass "$name"
}

check_window_burst_loss() {
  local name="rudp_window_burst_loss"
  local port=$((BASE_PORT + 2))
  local recv="$TMPDIR/${name}_recv.log"
  local send="$TMPDIR/${name}_send.log"

  log "=== CASE $name ==="
  LIBLAPIN_RUDP_DROP_DATA_MOD=5 "$PROG" -p rudp -L "$port" --no-send --seq --quiet-payload -D 7500 -F 1000 -m recv >"$recv" 2>&1 &
  local rpid=$!
  sleep 1
  "$PROG" -p rudp -R 127.0.0.1 "$port" -n 96 -i 1 -s 128 --seq --quiet-payload -D 4500 -F 1000 -m send >"$send" 2>&1 &
  local spid=$!
  wait "$spid" || true
  wait "$rpid" || true

  show_log "$name recv" "$recv"
  show_log "$name send" "$send"

  if has_bad_basics "$recv" || has_bad_basics "$send"; then
    fail "$name (bad log)"
    return
  fi

  local rec dup
  rec=$(summary_value received_messages "$recv")
  dup=$(grep '^\[PEER\]' "$recv" | tail -1 | tr ' ' '\n' | awk -F= '$1 == "seq_duplicates" { print $2; exit }')
  : "${rec:=0}"; : "${dup:=0}"
  if [ "$rec" -lt 96 ] || [ "$dup" -ne 0 ]; then
    fail "$name (rec=$rec dup=$dup)"
    return
  fi
  pass "$name"
}

main() {
  [ -x "$PROG" ] || { echo "Binary not found or not executable: $PROG" >&2; exit 1; }
  log "Using BASE_PORT=$BASE_PORT"
  check_unordered_first_drop_oneway
  check_unordered_first_drop_bidirectional
  check_window_burst_loss
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
