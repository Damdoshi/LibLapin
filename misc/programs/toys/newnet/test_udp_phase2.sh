#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_udp_phase2.$$}"
TIMEOUT="${TIMEOUT:-timeout}"
CASE_TIMEOUT="${CASE_TIMEOUT:-10}"
BASE_PORT="${BASE_PORT:-$((44000 + ($$ % 10000)))}"
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
    sed -n '1,260p' "$file"
  else
    echo "(missing log)"
  fi
}

contains_message() { grep -q '\[MESSAGE\]' "$1"; }
contains_summary() { grep -q '\[SUMMARY\]' "$1"; }
contains_send_fail() { grep -q '\[SEND\].*FAIL' "$1"; }
contains_peer_minus_one() { grep -q 'from peer -1' "$1"; }
contains_open_failed() { grep -q '\[OPEN\] failed' "$1"; }
summary_value() {
  local key="$1"
  local file="$2"
  grep '\[SUMMARY\]' "$file" | tail -1 | sed -n "s/.*${key}=\([0-9][0-9]*\).*/\1/p"
}

check_common_log() {
  local name="$1"
  local file="$2"

  if contains_open_failed "$file"; then
    fail "$name (open failed in $file)"
    return 1
  fi
  if contains_send_fail "$file"; then
    fail "$name (send failure in $file)"
    return 1
  fi
  if contains_peer_minus_one "$file"; then
    fail "$name (peer -1 in $file)"
    return 1
  fi
  if ! contains_summary "$file"; then
    fail "$name (missing summary in $file)"
    return 1
  fi
  return 0
}

check_logs_min_messages() {
  local name="$1"
  local min_total="$2"
  shift 2
  local files=("$@")
  local f
  local total=0
  local v

  for f in "${files[@]}"; do
    check_common_log "$name" "$f" || return
    v="$(summary_value received_messages "$f")"
    [ -z "$v" ] && v=0
    total=$((total + v))
  done

  if [ "$total" -lt "$min_total" ]; then
    fail "$name (received_messages total $total < $min_total)"
    return
  fi

  pass "$name"
}

check_receiver_min_messages() {
  local name="$1"
  local receiver="$2"
  local min_messages="$3"
  shift 3
  local f
  local v

  for f in "$receiver" "$@"; do
    check_common_log "$name" "$f" || return
  done

  v="$(summary_value received_messages "$receiver")"
  [ -z "$v" ] && v=0
  if [ "$v" -lt "$min_messages" ]; then
    fail "$name (receiver got $v messages < $min_messages)"
    return
  fi

  pass "$name"
}

run_pair_case() {
  local name="$1"
  local a_args="$2"
  local b_args="$3"
  local min_total="$4"
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

  check_logs_min_messages "$name" "$min_total" "$a_log" "$b_log"
  sleep "$SLEEP_BETWEEN"
}

run_unidirectional_case() {
  local name="$1"
  local port="$2"
  local recv_log="$TMPDIR/${name}_receiver.log"
  local send_log="$TMPDIR/${name}_sender.log"

  : >"$recv_log"
  : >"$send_log"

  log "=== CASE $name ==="
  log "receiver: $PROG -p udp -L $port --no-send -D 3500 -m receiver"
  run_bg "$PROG" -p udp -L "$port" --no-send -D 3500 -m receiver >"$recv_log" 2>&1 &
  local recv_pid=$!

  sleep 1

  log "sender: $PROG -p udp -R 127.0.0.1 $port -n 6 -i 120 -D 2500 -m sender"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 6 -i 120 -D 2500 -m sender >"$send_log" 2>&1 &
  local send_pid=$!

  wait "$send_pid" || true
  wait "$recv_pid" || true

  show_log_excerpt "$name receiver" "$recv_log"
  show_log_excerpt "$name sender" "$send_log"

  check_receiver_min_messages "$name" "$recv_log" 3 "$send_log"
  sleep "$SLEEP_BETWEEN"
}

run_three_peer_case() {
  local name="$1"
  local port="$2"
  local a_log="$TMPDIR/${name}_A.log"
  local b_log="$TMPDIR/${name}_B.log"
  local c_log="$TMPDIR/${name}_C.log"

  : >"$a_log"
  : >"$b_log"
  : >"$c_log"

  log "=== CASE $name ==="
  log "A: $PROG -p udp -L $port -n 8 -i 100 -D 4500 -m A"
  run_bg "$PROG" -p udp -L "$port" -n 8 -i 100 -D 4500 -m A >"$a_log" 2>&1 &
  local a_pid=$!

  sleep 1

  log "B: $PROG -p udp -R 127.0.0.1 $port -n 8 -i 100 -D 3000 -m B"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 8 -i 100 -D 3000 -m B >"$b_log" 2>&1 &
  local b_pid=$!

  sleep 1

  log "C: $PROG -p udp -R 127.0.0.1 $port -n 8 -i 100 -D 3000 -m C"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 8 -i 100 -D 3000 -m C >"$c_log" 2>&1 &
  local c_pid=$!

  wait "$c_pid" || true
  wait "$b_pid" || true
  wait "$a_pid" || true

  show_log_excerpt "$name A" "$a_log"
  show_log_excerpt "$name B" "$b_log"
  show_log_excerpt "$name C" "$c_log"

  check_logs_min_messages "$name" 6 "$a_log" "$b_log" "$c_log"
  sleep "$SLEEP_BETWEEN"
}

run_payload_sweep() {
  local base="$1"
  local port
  local size
  local idx=0

  for size in 1 8 63 64 65 256 1024 1400; do
    port=$((base + idx))
    run_pair_case \
      "udp_payload_${size}" \
      "-p udp -L $port -n 6 -i 80 -s $size -D 3000 -m A" \
      "-p udp -R 127.0.0.1 $port -n 6 -i 80 -s $size -D 2500 -m B" \
      4
    idx=$((idx + 1))
  done
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
    "udp_pair_bidirectional" \
    "-p udp -L $((BASE_PORT + 0)) -n 8 -i 100 -D 3500 -m A" \
    "-p udp -R 127.0.0.1 $((BASE_PORT + 0)) -n 8 -i 100 -D 2500 -m B" \
    4

  run_unidirectional_case "udp_unidirectional_to_listener" "$((BASE_PORT + 1))"

  run_three_peer_case "udp_three_peers" "$((BASE_PORT + 2))"

  run_payload_sweep "$((BASE_PORT + 10))"

  summary
}

main "$@"
