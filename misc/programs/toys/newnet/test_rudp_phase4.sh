#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_rudp_phase4.$$}"
BASE_PORT="${BASE_PORT:-$((52000 + ($$ % 10000)))}"
SLEEP_BETWEEN="${SLEEP_BETWEEN:-1}"

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

require_prog() {
  if [ ! -x "$PROG" ]; then
    echo "Binary not found or not executable: $PROG" >&2
    exit 1
  fi
}

show_log_excerpt() {
  local title="$1"
  local file="$2"
  log "--- $title ---"
  if [ -f "$file" ]; then
    sed -n '1,220p' "$file"
  else
    echo "(missing log)"
  fi
}

has() { grep -q "$2" "$1"; }

check_clean_log() {
  local file="$1"
  ! grep -q "\[SEND\].*FAIL" "$file" && \
  ! grep -q "from peer -1" "$file" && \
  ! grep -q "seq_gaps=[1-9]" "$file" && \
  ! grep -q "seq_duplicates=[1-9]" "$file" && \
  ! grep -q "seq_regressions=[1-9]" "$file"
}

check_case() {
  local name="$1"
  shift
  local ok=1
  local total_messages=0

  for f in "$@"; do
    show_log_excerpt "$name $(basename "$f")" "$f"
    check_clean_log "$f" || ok=0
    local msgs
    msgs=$(grep -c "\[MESSAGE\]" "$f" || true)
    total_messages=$((total_messages + msgs))
    has "$f" "\[SUMMARY\]" || ok=0
  done

  if [ "$total_messages" -le 0 ]; then
    ok=0
  fi

  if [ "$ok" -eq 1 ]; then
    pass "$name"
  else
    fail "$name"
  fi
}

run_pair() {
  local name="$1"
  local port="$2"
  local size="$3"
  local count="$4"
  local interval="$5"

  local a_log="$TMPDIR/${name}_A.log"
  local b_log="$TMPDIR/${name}_B.log"

  log "=== CASE $name ==="
  log "A: $PROG -p rudp -L $port -n $count -i $interval -s $size --seq --quiet-payload -D 4200 -F 300 -m A"
  "$PROG" -p rudp -L "$port" -n "$count" -i "$interval" -s "$size" --seq --quiet-payload -D 4200 -F 300 -m A >"$a_log" 2>&1 &
  local a_pid=$!

  sleep 1

  log "B: $PROG -p rudp -R 127.0.0.1 $port -n $count -i $interval -s $size --seq --quiet-payload -D 3200 -F 300 -m B"
  "$PROG" -p rudp -R 127.0.0.1 "$port" -n "$count" -i "$interval" -s "$size" --seq --quiet-payload -D 3200 -F 300 -m B >"$b_log" 2>&1 &
  local b_pid=$!

  wait "$b_pid" || true
  wait "$a_pid" || true

  check_case "$name" "$a_log" "$b_log"
  sleep "$SLEEP_BETWEEN"
}

run_listener_many() {
  local name="rudp_many_senders_to_listener"
  local port="$1"
  local listener_log="$TMPDIR/${name}_listener.log"

  log "=== CASE $name ==="
  log "listener: $PROG -p rudp -L $port --no-send --seq --quiet-payload -D 5200 -F 400 -m listener"
  "$PROG" -s 512 -p rudp -L "$port" --no-send --seq --quiet-payload -D 5200 -F 400 -m listener >"$listener_log" 2>&1 &
  local listener_pid=$!

  sleep 1

  local logs=("$listener_log")
  local pids=()
  for i in 0 1 2 3; do
    local logf="$TMPDIR/${name}_S${i}.log"
    logs+=("$logf")
    log "S$i: $PROG -p rudp -R 127.0.0.1 $port -n 12 -i 40 --seq --quiet-payload -D 2800 -F 400 -m S$i"
    "$PROG" -s 512 -p rudp -R 127.0.0.1 "$port" -n 12 -i 40 --seq --quiet-payload -D 2800 -F 400 -m "S$i" >"$logf" 2>&1 &
    pids+=("$!")
    sleep 0.15
  done

  for pid in "${pids[@]}"; do
    wait "$pid" || true
  done
  wait "$listener_pid" || true

  check_case "$name" "${logs[@]}"
  if ! grep -q "peers=4" "$listener_log"; then
    fail "$name (listener did not register 4 peers)"
  fi
  sleep "$SLEEP_BETWEEN"
}

summary() {
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

main() {
  require_prog
  log "Using BASE_PORT=$BASE_PORT"

  run_pair "rudp_pair_small" "$((BASE_PORT + 0))" 64 8 80
  run_pair "rudp_pair_1472" "$((BASE_PORT + 1))" 1472 5 80
  run_pair "rudp_pair_4096" "$((BASE_PORT + 2))" 4096 4 100
  run_listener_many "$((BASE_PORT + 3))"

  summary
}

main "$@"
