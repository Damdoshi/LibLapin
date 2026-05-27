#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_udp_phase1.$$}"
TIMEOUT="${TIMEOUT:-timeout}"
CASE_TIMEOUT="${CASE_TIMEOUT:-8}"
BASE_PORT="${BASE_PORT:-$((43000 + ($$ % 12000)))}"
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

require_tools() {
  if [ ! -x "$PROG" ]; then
    echo "Binary not found or not executable: $PROG" >&2
    exit 1
  fi
  command -v "$TIMEOUT" >/dev/null 2>&1 || {
    echo "Missing timeout" >&2
    exit 1
  }
  command -v stdbuf >/dev/null 2>&1 || {
    echo "Missing stdbuf" >&2
    exit 1
  }
}

run_bg() {
  stdbuf -oL -eL "$TIMEOUT" "${CASE_TIMEOUT}s" "$@"
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

contains_message() { grep -q '\[MESSAGE\]' "$1"; }
contains_summary() { grep -q '\[SUMMARY\]' "$1"; }
contains_send_fail() { grep -q '\[SEND\].*FAIL' "$1"; }
contains_peer_minus_one() { grep -q 'from peer -1' "$1"; }
contains_open_failed() { grep -q '\[OPEN\] failed' "$1"; }

check_logs() {
  local name="$1"
  shift
  local files=("$@")
  local f
  local any_message=0

  for f in "${files[@]}"; do
    contains_message "$f" && any_message=1
    if contains_open_failed "$f"; then
      fail "$name (open failed in $f)"
      return
    fi
    if contains_send_fail "$f"; then
      fail "$name (send failure in $f)"
      return
    fi
    if contains_peer_minus_one "$f"; then
      fail "$name (peer -1 in $f)"
      return
    fi
    if ! contains_summary "$f"; then
      fail "$name (missing summary in $f)"
      return
    fi
  done

  if [ "$any_message" -eq 0 ]; then
    fail "$name (no message)"
    return
  fi

  pass "$name"
}

run_pair_case() {
  local name="$1"
  local port="$2"
  local a_args="$3"
  local b_args="$4"
  local a_log="$TMPDIR/${name}_A.log"
  local b_log="$TMPDIR/${name}_B.log"

  : >"$a_log"
  : >"$b_log"

  log "=== CASE $name ==="
  log "A: $PROG $a_args"
  run_bg "$PROG" $a_args >"$a_log" 2>&1 &
  local a_pid=$!

  sleep 1

  log "B: $PROG $b_args"
  run_bg "$PROG" $b_args >"$b_log" 2>&1 &
  local b_pid=$!

  wait "$b_pid" || true
  wait "$a_pid" || true

  show_log_excerpt "$name A" "$a_log"
  show_log_excerpt "$name B" "$b_log"

  check_logs "$name" "$a_log" "$b_log"
  sleep "$SLEEP_BETWEEN"
}

run_three_peer_case() {
  local name="udp_three_peers"
  local port="$1"
  local a_log="$TMPDIR/${name}_A.log"
  local b_log="$TMPDIR/${name}_B.log"
  local c_log="$TMPDIR/${name}_C.log"

  : >"$a_log"
  : >"$b_log"
  : >"$c_log"

  log "=== CASE $name ==="
  run_bg "$PROG" -p udp -L "$port" -n 4 -i 150 -m A >"$a_log" 2>&1 &
  local a_pid=$!
  sleep 1
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 4 -i 150 -m B >"$b_log" 2>&1 &
  local b_pid=$!
  sleep 1
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 4 -i 150 -m C >"$c_log" 2>&1 &
  local c_pid=$!

  wait "$c_pid" || true
  wait "$b_pid" || true
  wait "$a_pid" || true

  show_log_excerpt "$name A" "$a_log"
  show_log_excerpt "$name B" "$b_log"
  show_log_excerpt "$name C" "$c_log"

  check_logs "$name" "$a_log" "$b_log" "$c_log"
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
  require_tools
  log "Using BASE_PORT=$BASE_PORT"

  run_pair_case \
    "udp_pair" "$((BASE_PORT + 0))" \
    "-p udp -L $((BASE_PORT + 0)) -n 5 -i 150 -m A" \
    "-p udp -R 127.0.0.1 $((BASE_PORT + 0)) -n 5 -i 150 -m B"

  run_pair_case \
    "rudp_pair" "$((BASE_PORT + 1))" \
    "-p rudp -L $((BASE_PORT + 1)) -n 5 -i 150 -m A" \
    "-p rudp -R 127.0.0.1 $((BASE_PORT + 1)) -n 5 -i 150 -m B"

  run_pair_case \
    "udp_payload_256" "$((BASE_PORT + 2))" \
    "-p udp -L $((BASE_PORT + 2)) -n 5 -i 150 -s 256 -m A" \
    "-p udp -R 127.0.0.1 $((BASE_PORT + 2)) -n 5 -i 150 -s 256 -m B"

  run_three_peer_case "$((BASE_PORT + 3))"

  summary
}

main "$@"
