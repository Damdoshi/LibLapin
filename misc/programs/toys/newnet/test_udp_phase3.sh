#!/usr/bin/env bash
set -u

PROG="${PROG:-./newnet}"
TMPDIR="${TMPDIR:-/tmp/liblapin_udp_phase3.$$}"
TIMEOUT="${TIMEOUT:-timeout}"
CASE_TIMEOUT="${CASE_TIMEOUT:-12}"
BASE_PORT="${BASE_PORT:-$((47000 + ($$ % 15000)))}"
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

summary_value() {
  local file="$1"
  local key="$2"
  local line
  line="$(grep '^\[SUMMARY\]' "$file" | tail -n 1)"
  [ -n "$line" ] || return 1
  printf '%s\n' "$line" | tr ' ' '\n' | awk -F= -v k="$key" '$1 == k { print $2; found=1 } END { exit found ? 0 : 1 }'
}

peer_values() {
  local file="$1"
  local key="$2"
  grep '^\[PEER\] index=' "$file" | tr ' ' '\n' | awk -F= -v k="$key" '$1 == k { print $2 }'
}

sum_peer_field() {
  local file="$1"
  local key="$2"
  local values
  values="$(peer_values "$file" "$key")"
  if [ -z "$values" ]; then
    echo 0
    return 0
  fi
  printf '%s\n' "$values" | awk '{ s += $1 } END { print s + 0 }'
}

has_clean_log() {
  local name="$1"
  local file="$2"

  if grep -q '\[OPEN\] failed' "$file"; then
    fail "$name ($file open failed)"
    return 1
  fi
  if grep -q '\[SEND\].*FAIL' "$file"; then
    fail "$name ($file send failure)"
    return 1
  fi
  if grep -q 'from peer -1' "$file"; then
    fail "$name ($file peer -1)"
    return 1
  fi
  if ! grep -q '^\[SUMMARY\]' "$file"; then
    fail "$name ($file missing summary)"
    return 1
  fi
  return 0
}

check_no_sequence_anomaly() {
  local name="$1"
  local file="$2"
  local gaps duplicates regressions

  gaps="$(sum_peer_field "$file" seq_gaps)"
  duplicates="$(sum_peer_field "$file" seq_duplicates)"
  regressions="$(sum_peer_field "$file" seq_regressions)"

  if [ "$gaps" -ne 0 ] || [ "$duplicates" -ne 0 ] || [ "$regressions" -ne 0 ]; then
    fail "$name ($file sequence anomaly gaps=$gaps duplicates=$duplicates regressions=$regressions)"
    return 1
  fi
  return 0
}

expect_ge() {
  local name="$1"
  local actual="$2"
  local expected="$3"
  local label="$4"

  if [ -z "$actual" ]; then
    fail "$name (missing $label)"
    return 1
  fi
  if [ "$actual" -lt "$expected" ]; then
    fail "$name ($label expected >= $expected, got $actual)"
    return 1
  fi
  return 0
}

case_burst_sender_to_listener() {
  local name="udp_burst_sender_to_listener"
  local port=$((BASE_PORT + 0))
  local rlog="$TMPDIR/${name}_receiver.log"
  local slog="$TMPDIR/${name}_sender.log"

  log "=== CASE $name ==="
  log "receiver: $PROG -p udp -L $port --no-send --seq --quiet-payload -D 4500 -F 500 -m recv"
  run_bg "$PROG" -p udp -L "$port" --no-send --seq --quiet-payload -D 4500 -F 500 -m recv >"$rlog" 2>&1 &
  local rpid=$!
  sleep 1

  log "sender: $PROG -p udp -R 127.0.0.1 $port -n 200 -i 1 -s 128 --seq --quiet-payload -D 2500 -F 500 -m burst"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 200 -i 1 -s 128 --seq --quiet-payload -D 2500 -F 500 -m burst >"$slog" 2>&1 &
  local spid=$!

  wait "$spid" || true
  wait "$rpid" || true

  show_log_excerpt "$name receiver" "$rlog"
  show_log_excerpt "$name sender" "$slog"

  has_clean_log "$name" "$rlog" || return
  has_clean_log "$name" "$slog" || return
  check_no_sequence_anomaly "$name" "$rlog" || return
  expect_ge "$name" "$(summary_value "$rlog" received_messages)" 150 "receiver received_messages" || return
  expect_ge "$name" "$(summary_value "$slog" send_ok)" 150 "sender send_ok" || return
  pass "$name"
}

case_hub_replies_to_all_known() {
  local name="udp_hub_replies_to_all_known"
  local port=$((BASE_PORT + 1))
  local alog="$TMPDIR/${name}_A.log"
  local blog="$TMPDIR/${name}_B.log"
  local clog="$TMPDIR/${name}_C.log"

  log "=== CASE $name ==="
  log "A: $PROG -p udp -L $port -n 4 -i 100 --first-send-delay 2200 --seq --quiet-payload -D 5200 -F 200 -m A"
  run_bg "$PROG" -p udp -L "$port" -n 4 -i 100 --first-send-delay 2200 --seq --quiet-payload -D 5200 -F 200 -m A >"$alog" 2>&1 &
  local apid=$!
  sleep 0.7

  log "B: $PROG -p udp -R 127.0.0.1 $port -n 4 -i 120 --seq --quiet-payload -D 4200 -F 200 -m B"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 4 -i 120 --seq --quiet-payload -D 4200 -F 200 -m B >"$blog" 2>&1 &
  local bpid=$!
  sleep 0.7

  log "C: $PROG -p udp -R 127.0.0.1 $port -n 4 -i 120 --seq --quiet-payload -D 4200 -F 200 -m C"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 4 -i 120 --seq --quiet-payload -D 4200 -F 200 -m C >"$clog" 2>&1 &
  local cpid=$!

  wait "$bpid" || true
  wait "$cpid" || true
  wait "$apid" || true

  show_log_excerpt "$name A" "$alog"
  show_log_excerpt "$name B" "$blog"
  show_log_excerpt "$name C" "$clog"

  has_clean_log "$name" "$alog" || return
  has_clean_log "$name" "$blog" || return
  has_clean_log "$name" "$clog" || return
  check_no_sequence_anomaly "$name" "$alog" || return
  check_no_sequence_anomaly "$name" "$blog" || return
  check_no_sequence_anomaly "$name" "$clog" || return
  expect_ge "$name" "$(summary_value "$alog" peers)" 2 "A peers" || return
  expect_ge "$name" "$(summary_value "$alog" send_ok)" 8 "A send_ok" || return
  expect_ge "$name" "$(summary_value "$blog" received_messages)" 4 "B received_messages" || return
  expect_ge "$name" "$(summary_value "$clog" received_messages)" 4 "C received_messages" || return
  pass "$name"
}

case_late_peer_not_starved() {
  local name="udp_late_peer_not_starved"
  local port=$((BASE_PORT + 2))
  local alog="$TMPDIR/${name}_A.log"
  local blog="$TMPDIR/${name}_B.log"
  local clog="$TMPDIR/${name}_C.log"

  log "=== CASE $name ==="
  log "A: $PROG -p udp -L $port -n 20 -i 100 --first-send-delay 900 --seq --quiet-payload -D 5200 -F 200 -m A"
  run_bg "$PROG" -p udp -L "$port" -n 20 -i 100 --first-send-delay 900 --seq --quiet-payload -D 5200 -F 200 -m A >"$alog" 2>&1 &
  local apid=$!
  sleep 0.5

  log "B: $PROG -p udp -R 127.0.0.1 $port -n 6 -i 150 --seq --quiet-payload -D 4500 -F 200 -m B"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 6 -i 150 --seq --quiet-payload -D 4500 -F 200 -m B >"$blog" 2>&1 &
  local bpid=$!
  sleep 2.0

  log "C: $PROG -p udp -R 127.0.0.1 $port -n 6 -i 150 --seq --quiet-payload -D 3000 -F 200 -m C"
  run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 6 -i 150 --seq --quiet-payload -D 3000 -F 200 -m C >"$clog" 2>&1 &
  local cpid=$!

  wait "$bpid" || true
  wait "$cpid" || true
  wait "$apid" || true

  show_log_excerpt "$name A" "$alog"
  show_log_excerpt "$name B" "$blog"
  show_log_excerpt "$name C" "$clog"

  has_clean_log "$name" "$alog" || return
  has_clean_log "$name" "$blog" || return
  has_clean_log "$name" "$clog" || return
  check_no_sequence_anomaly "$name" "$blog" || return
  check_no_sequence_anomaly "$name" "$clog" || return
  expect_ge "$name" "$(summary_value "$alog" peers)" 2 "A peers" || return
  expect_ge "$name" "$(summary_value "$clog" received_messages)" 3 "C received_messages" || return
  pass "$name"
}

case_many_senders_to_listener() {
  local name="udp_many_senders_to_listener"
  local port=$((BASE_PORT + 3))
  local llog="$TMPDIR/${name}_listener.log"
  local pids=""

  log "=== CASE $name ==="
  log "listener: $PROG -p udp -L $port --no-send --seq --quiet-payload -D 5000 -F 300 -m listener"
  run_bg "$PROG" -p udp -L "$port" --no-send --seq --quiet-payload -D 5000 -F 300 -m listener >"$llog" 2>&1 &
  local lpid=$!
  sleep 1

  for n in 0 1 2 3 4; do
    local plog="$TMPDIR/${name}_sender_${n}.log"
    log "S$n: $PROG -p udp -R 127.0.0.1 $port -n 8 -i 50 --seq --quiet-payload -D 2500 -F 300 -m S$n"
    run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 8 -i 50 --seq --quiet-payload -D 2500 -F 300 -m "S$n" >"$plog" 2>&1 &
    pids="$pids $!:$plog"
    sleep 0.1
  done

  for item in $pids; do
    local pid="${item%%:*}"
    wait "$pid" || true
  done
  wait "$lpid" || true

  show_log_excerpt "$name listener" "$llog"
  has_clean_log "$name" "$llog" || return
  check_no_sequence_anomaly "$name" "$llog" || return
  expect_ge "$name" "$(summary_value "$llog" peers)" 5 "listener peers" || return
  expect_ge "$name" "$(summary_value "$llog" received_messages)" 40 "listener received_messages" || return

  for item in $pids; do
    local plog="${item#*:}"
    show_log_excerpt "$name sender ${plog##*_}" "$plog"
    has_clean_log "$name" "$plog" || return
  done

  pass "$name"
}

case_payload_edges() {
  local size
  local idx=0

  for size in 1472 2048 4096; do
    local name="udp_payload_edge_${size}"
    local port=$((BASE_PORT + 20 + idx))
    local alog="$TMPDIR/${name}_A.log"
    local blog="$TMPDIR/${name}_B.log"
    idx=$((idx + 1))

    log "=== CASE $name ==="
    log "A: $PROG -p udp -L $port -n 5 -i 80 -s $size --seq --quiet-payload -D 3500 -F 200 -m A"
    run_bg "$PROG" -p udp -L "$port" -n 5 -i 80 -s "$size" --seq --quiet-payload -D 3500 -F 200 -m A >"$alog" 2>&1 &
    local apid=$!
    sleep 1

    log "B: $PROG -p udp -R 127.0.0.1 $port -n 5 -i 80 -s $size --seq --quiet-payload -D 2800 -F 200 -m B"
    run_bg "$PROG" -p udp -R 127.0.0.1 "$port" -n 5 -i 80 -s "$size" --seq --quiet-payload -D 2800 -F 200 -m B >"$blog" 2>&1 &
    local bpid=$!

    wait "$bpid" || true
    wait "$apid" || true

    show_log_excerpt "$name A" "$alog"
    show_log_excerpt "$name B" "$blog"
    has_clean_log "$name" "$alog" || return
    has_clean_log "$name" "$blog" || return
    check_no_sequence_anomaly "$name" "$alog" || return
    check_no_sequence_anomaly "$name" "$blog" || return
    expect_ge "$name" "$(summary_value "$alog" received_messages)" 5 "A received_messages" || return
    expect_ge "$name" "$(summary_value "$blog" received_messages)" 5 "B received_messages" || return
    pass "$name"
    sleep "$SLEEP_BETWEEN"
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
  case_burst_sender_to_listener
  sleep "$SLEEP_BETWEEN"
  case_hub_replies_to_all_known
  sleep "$SLEEP_BETWEEN"
  case_late_peer_not_starved
  sleep "$SLEEP_BETWEEN"
  case_many_senders_to_listener
  sleep "$SLEEP_BETWEEN"
  case_payload_edges
  summary
}

main "$@"
