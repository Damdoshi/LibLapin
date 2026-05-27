#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_rudp_phase7.$$}"
BASE_PORT="${BASE_PORT:-$((56000 + ($$ % 8000)))}"
mkdir -p "$TMPDIR"
PASS=0
FAIL=0

log(){ printf '[%s] %s\n' "$(date +%H:%M:%S)" "$*"; }
pass(){ log "PASS: $*"; PASS=$((PASS+1)); }
fail(){ log "FAIL: $*"; FAIL=$((FAIL+1)); }
cleanup(){ jobs -p | xargs -r kill 2>/dev/null || true; wait 2>/dev/null || true; }
trap cleanup EXIT INT TERM

summary_value(){ local k="$1" f="$2"; grep '^\[SUMMARY\]' "$f" | tail -1 | tr ' ' '\n' | awk -F= -v k="$k" '$1==k{print $2; exit}'; }
peer_sum_value(){ local k="$1" f="$2"; grep '^\[PEER\]' "$f" | tr ' ' '\n' | awk -F= -v k="$k" '$1==k{s+=$2} END{print s+0}'; }
bad(){ local f="$1"; grep -q '\[OPEN\] failed' "$f" && return 0; grep -q '\[SEND\].*FAIL' "$f" && return 0; grep -q 'from peer -1' "$f" && return 0; grep -q 'seq_duplicates=[1-9]' "$f" && return 0; return 1; }
show(){ log "--- $1 ---"; sed -n '1,220p' "$2"; }

pair_stability(){
  local name port a b ra rb apid bpid
  name="rudp_long_pair_moderate_loss"
  port=$((BASE_PORT+0))
  a="$TMPDIR/${name}_A.log"
  b="$TMPDIR/${name}_B.log"

  log "=== CASE $name ==="
  LIBLAPIN_RUDP_DROP_DATA_MOD=5 "$PROG" -p rudp -L "$port" -n 90 -i 20 -s 128 --seq --quiet-payload -D 11000 -F 1000 -m A >"$a" 2>&1 &
  apid=$!
  sleep 1
  LIBLAPIN_RUDP_DROP_DATA_MOD=5 "$PROG" -p rudp -R 127.0.0.1 "$port" -n 90 -i 20 -s 128 --seq --quiet-payload -D 9500 -F 1000 -m B >"$b" 2>&1 &
  bpid=$!
  wait "$bpid" || true
  wait "$apid" || true
  show "$name A" "$a"
  show "$name B" "$b"
  if bad "$a" || bad "$b"; then fail "$name (bad log)"; return; fi
  ra=$(summary_value received_messages "$a"); rb=$(summary_value received_messages "$b")
  : "${ra:=0}"; : "${rb:=0}"
  if [ "$ra" -lt 90 ] || [ "$rb" -lt 90 ]; then fail "$name (received A=$ra B=$rb)"; return; fi
  pass "$name"
}

many_senders_stability(){
  local name port l pids lpid peers rec dup
  name="rudp_long_many_senders_moderate_loss"
  port=$((BASE_PORT+1))
  l="$TMPDIR/${name}_listener.log"
  pids=""

  log "=== CASE $name ==="
  LIBLAPIN_RUDP_DROP_DATA_MOD=6 "$PROG" -p rudp -L "$port" -s 192 --no-send --seq --quiet-payload -D 12000 -F 1000 -m listener >"$l" 2>&1 &
  lpid=$!
  sleep 1
  for i in 0 1 2 3; do
    local f
    f="$TMPDIR/${name}_S${i}.log"
    LIBLAPIN_RUDP_DROP_DATA_MOD=6 "$PROG" -p rudp -R 127.0.0.1 "$port" -s 192 -n 20 -i 35 --seq --quiet-payload -D 7000 -F 1000 -m "S$i" >"$f" 2>&1 &
    pids="$pids $!"
    sleep 0.15
  done
  for p in $pids; do wait "$p" || true; done
  wait "$lpid" || true
  show "$name listener" "$l"
  if bad "$l"; then fail "$name (bad listener log)"; return; fi
  peers=$(summary_value peers "$l")
  rec=$(summary_value received_messages "$l")
  dup=$(peer_sum_value seq_duplicates "$l")
  : "${peers:=0}"; : "${rec:=0}"; : "${dup:=0}"
  if [ "$peers" -ne 4 ] || [ "$rec" -lt 80 ] || [ "$dup" -ne 0 ]; then fail "$name (peers=$peers rec=$rec dup=$dup)"; return; fi
  pass "$name"
}

main(){
  [ -x "$PROG" ] || { echo "Binary not found or not executable: $PROG" >&2; exit 1; }
  log "Using BASE_PORT=$BASE_PORT"
  pair_stability
  many_senders_stability
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
