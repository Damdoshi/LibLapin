#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_net_test.$$}"
mkdir -p "$TMPDIR"

PASS=0
FAIL=0

# Base de ports pseudo-aléatoire dans une zone haute
BASE_PORT="${BASE_PORT:-$((40000 + ($$ % 20000)))}"

PORT_TCP=$((BASE_PORT + 0))
PORT_TERM=$((BASE_PORT + 1))
PORT_SIZE=$((BASE_PORT + 2))
PORT_FIXED=$((BASE_PORT + 3))
PORT_UDP=$((BASE_PORT + 4))

run_bg() {
  stdbuf -oL -eL "$@"
}

cleanup() {
  jobs -p | xargs -r kill 2>/dev/null || true
  wait 2>/dev/null || true
}
trap cleanup EXIT INT TERM

log() {
  printf '[%s] %s\n' "$(date +%H:%M:%S)" "$*"
}

pass() {
  log "PASS: $*"
  PASS=$((PASS + 1))
}

fail() {
  log "FAIL: $*"
  FAIL=$((FAIL + 1))
}

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
    sed -n '1,200p' "$file"
  else
    echo "(missing log)"
  fi
}

contains_message() {
  local file="$1"
  grep -q "\[MESSAGE\]" "$file"
}

contains_connect() {
  local file="$1"
  grep -q "\[CONNECT\]" "$file"
}

contains_send_fail() {
  local file="$1"
  grep -q "\[SEND\].*FAIL" "$file"
}

contains_open_failed() {
  local file="$1"
  grep -q "\[OPEN\] failed" "$file"
}

run_server_client_case() {
  local name="$1"
  local port="$2"
  local server_args="$3"
  local client_args="$4"

  local srv_log="$TMPDIR/${name}_server.log"
  local cli_log="$TMPDIR/${name}_client.log"

  log "=== CASE $name ==="
  log "server: $PROG $server_args"
  run_bg "$PROG" $server_args >"$srv_log" 2>&1 &
  local srv_pid=$!

  sleep 1

  log "client: $PROG $client_args"
  run_bg "$PROG" $client_args >"$cli_log" 2>&1 &
  local cli_pid=$!

  sleep 5

  kill "$cli_pid" 2>/dev/null || true
  kill "$srv_pid" 2>/dev/null || true
  wait "$cli_pid" 2>/dev/null || true
  wait "$srv_pid" 2>/dev/null || true

  show_log_excerpt "server log ($name)" "$srv_log"
  show_log_excerpt "client log ($name)" "$cli_log"

  if contains_open_failed "$srv_log"; then
    fail "$name (server open failed on port $port)"
  elif { contains_message "$srv_log" || contains_message "$cli_log"; } \
       && ! contains_send_fail "$srv_log" \
       && ! contains_send_fail "$cli_log"; then
    pass "$name"
  elif contains_message "$srv_log" || contains_message "$cli_log"; then
    fail "$name (messages seen, but send failures present)"
  elif contains_connect "$srv_log" || contains_connect "$cli_log"; then
    fail "$name (connect seen, but no message)"
  else
    fail "$name (no connect/message detected)"
  fi

  sleep 1
}

run_udp_case() {
  local name="udp"
  local port="$1"
  local a_log="$TMPDIR/${name}_A.log"
  local b_log="$TMPDIR/${name}_B.log"

  log "=== CASE $name ==="
  log "peer A: $PROG -p udp -L $port -n 5 -i 300 -m A"
  run_bg "$PROG" -p udp -L "$port" -n 5 -i 300 -m A >"$a_log" 2>&1 &
  local a_pid=$!

  sleep 1

  log "peer B: $PROG -p udp -R 127.0.0.1 $port -n 5 -i 300 -m B"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 5 -i 300 -m B >"$b_log" 2>&1 &
  local b_pid=$!

  sleep 5

  kill "$b_pid" 2>/dev/null || true
  kill "$a_pid" 2>/dev/null || true
  wait "$b_pid" 2>/dev/null || true
  wait "$a_pid" 2>/dev/null || true

  show_log_excerpt "peer A log" "$a_log"
  show_log_excerpt "peer B log" "$b_log"

  if { contains_message "$a_log" || contains_message "$b_log"; } \
     && ! contains_send_fail "$a_log" \
     && ! contains_send_fail "$b_log"; then
    pass "$name"
  elif contains_message "$a_log" || contains_message "$b_log"; then
    fail "$name (messages seen, but send failures present)"
  elif contains_connect "$a_log" || contains_connect "$b_log"; then
    fail "$name (connect seen, but no message)"
  else
    fail "$name (no connect/message detected)"
  fi
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

  run_server_client_case \
    "tcp" "$PORT_TCP" \
    "-p tcp -L $PORT_TCP -n 5 -i 300 -m server" \
    "-p tcp -R 127.0.0.1 $PORT_TCP -n 5 -i 300 -m client"

  run_server_client_case \
    "term" "$PORT_TERM" \
    "-p term -L $PORT_TERM -n 5 -i 300 -m server" \
    "-p term -R 127.0.0.1 $PORT_TERM -n 5 -i 300 -m client"

  run_server_client_case \
    "size" "$PORT_SIZE" \
    "-p size -L $PORT_SIZE -n 5 -i 300 -s 128 -m server" \
    "-p size -R 127.0.0.1 $PORT_SIZE -n 5 -i 300 -s 128 -m client"

  run_server_client_case \
    "fixed" "$PORT_FIXED" \
    "-p fixed -L $PORT_FIXED -n 5 -i 300 -s 64 --hex -m server" \
    "-p fixed -R 127.0.0.1 $PORT_FIXED -n 5 -i 300 -s 64 --hex -m client"

  run_udp_case "$PORT_UDP"

  summary
}

main "$@"

