#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_net_stress.$$}"
ROUNDS="${ROUNDS:-5}"
SLEEP_BETWEEN="${SLEEP_BETWEEN:-1}"
VALGRIND="${VALGRIND:-valgrind}"
TIMEOUT="${TIMEOUT:-timeout}"
CASE_TIMEOUT="${CASE_TIMEOUT:-12}"

mkdir -p "$TMPDIR"

PASS=0
FAIL=0

BASE_PORT="${BASE_PORT:-$((42000 + ($$ % 15000)))}"

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
  command -v "$VALGRIND" >/dev/null 2>&1 || {
    echo "Missing valgrind" >&2
    exit 1
  }
  command -v "$TIMEOUT" >/dev/null 2>&1 || {
    echo "Missing timeout" >&2
    exit 1
  }
  command -v stdbuf >/dev/null 2>&1 || {
    echo "Missing stdbuf" >&2
    exit 1
  }
}

run_bg_vg() {
  local vglog="$1"
  shift
  stdbuf -oL -eL \
    "$TIMEOUT" "${CASE_TIMEOUT}s" \
    "$VALGRIND" \
      --quiet \
      --tool=memcheck \
      --leak-check=full \
      --show-leak-kinds=definite,possible \
      --errors-for-leak-kinds=definite,possible \
      --track-origins=yes \
      --error-exitcode=97 \
      --log-file="$vglog" \
    "$@"
}

show_log_excerpt() {
  local title="$1"
  local file="$2"
  log "--- $title ---"
  if [ -f "$file" ]; then
    sed -n '1,160p' "$file"
  else
    echo "(missing log)"
  fi
}

contains_message() {
  grep -q "\[MESSAGE\]" "$1"
}

contains_connect() {
  grep -q "\[CONNECT\]" "$1"
}

contains_send_fail() {
  grep -q "\[SEND\].*FAIL" "$1"
}

contains_open_failed() {
  grep -q "\[OPEN\] failed" "$1"
}

vg_has_errors() {
  local f="$1"
  [ ! -f "$f" ] && return 0
  grep -Eq \
    "Invalid read|Invalid write|Use of uninitialised|Conditional jump or move depends on uninitialised|definitely lost: [1-9][0-9,]* bytes|ERROR SUMMARY: [1-9]" \
    "$f"
}

check_pair_result() {
  local name="$1"
  local srv_log="$2"
  local cli_log="$3"
  local srv_vg="$4"
  local cli_vg="$5"

  show_log_excerpt "server log ($name)" "$srv_log"
  show_log_excerpt "client log ($name)" "$cli_log"

  if [ -f "$srv_vg" ]; then
    show_log_excerpt "server valgrind ($name)" "$srv_vg"
  fi
  if [ -f "$cli_vg" ]; then
    show_log_excerpt "client valgrind ($name)" "$cli_vg"
  fi

  if contains_open_failed "$srv_log"; then
    fail "$name (server open failed)"
    return
  fi
  if vg_has_errors "$srv_vg"; then
    fail "$name (server valgrind errors)"
    return
  fi
  if vg_has_errors "$cli_vg"; then
    fail "$name (client valgrind errors)"
    return
  fi
  if contains_send_fail "$srv_log" || contains_send_fail "$cli_log"; then
    fail "$name (send failure)"
    return
  fi
  if contains_message "$srv_log" || contains_message "$cli_log"; then
    pass "$name"
    return
  fi
  if contains_connect "$srv_log" || contains_connect "$cli_log"; then
    fail "$name (connect without message)"
    return
  fi
  fail "$name (no connect/message detected)"
}

run_case() {
  local name="$1"
  local server_args="$2"
  local client_args="$3"

  local srv_log="$TMPDIR/${name}_server.log"
  local cli_log="$TMPDIR/${name}_client.log"
  local srv_vg="$TMPDIR/${name}_server.vg"
  local cli_vg="$TMPDIR/${name}_client.vg"

  : >"$srv_log"
  : >"$cli_log"
  : >"$srv_vg"
  : >"$cli_vg"

  log "=== CASE $name ==="
  log "server: $PROG $server_args"
  run_bg_vg "$srv_vg" "$PROG" $server_args >"$srv_log" 2>&1 &
  local srv_pid=$!

  sleep 1

  log "client: $PROG $client_args"
  run_bg_vg "$cli_vg" "$PROG" $client_args >"$cli_log" 2>&1 &
  local cli_pid=$!

  wait "$cli_pid" || true
  wait "$srv_pid" || true

  check_pair_result "$name" "$srv_log" "$cli_log" "$srv_vg" "$cli_vg"

  sleep "$SLEEP_BETWEEN"
}

run_round() {
  local round="$1"
  local p0=$((BASE_PORT + round * 20))

  run_case \
    "r${round}_tcp_small" \
    "-p tcp -L $((p0 + 0)) -n 8 -i 100 -m server" \
    "-p tcp -R 127.0.0.1 $((p0 + 0)) -n 8 -i 100 -m client"

  run_case \
    "r${round}_term_small" \
    "-p term -L $((p0 + 1)) -n 8 -i 100 -m server" \
    "-p term -R 127.0.0.1 $((p0 + 1)) -n 8 -i 100 -m client"

  run_case \
    "r${round}_fixed_64" \
    "-p fixed -L $((p0 + 2)) -n 8 -i 100 -s 64 --hex -m server" \
    "-p fixed -R 127.0.0.1 $((p0 + 2)) -n 8 -i 100 -s 64 --hex -m client"

  run_case \
    "r${round}_size_128" \
    "-p size -L $((p0 + 3)) -n 8 -i 100 -s 128 -m server" \
    "-p size -R 127.0.0.1 $((p0 + 3)) -n 8 -i 100 -s 128 -m client"

  run_case \
    "r${round}_size_1024" \
    "-p size -L $((p0 + 4)) -n 8 -i 100 -s 1024 -m server" \
    "-p size -R 127.0.0.1 $((p0 + 4)) -n 8 -i 100 -s 1024 -m client"

  run_case \
    "r${round}_udp" \
    "-p udp -L $((p0 + 5)) -n 8 -i 100 -m A" \
    "-p udp -R 127.0.0.1 $((p0 + 5)) -n 8 -i 100 -m B"
}

summary() {
  echo
  echo "=============================="
  echo "PASS: $PASS"
  echo "FAIL: $FAIL"
  echo "ROUNDS: $ROUNDS"
  echo "BASE_PORT: $BASE_PORT"
  echo "Logs: $TMPDIR"
  echo "=============================="
  echo
  [ "$FAIL" -eq 0 ]
}

main() {
  require_tools
  log "Using BASE_PORT=$BASE_PORT"
  log "Using ROUNDS=$ROUNDS"

  local r
  for ((r = 0; r < ROUNDS; ++r)); do
    log "##### ROUND $r #####"
    run_round "$r"
  done

  summary
}

main "$@"

