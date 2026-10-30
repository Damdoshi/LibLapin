#!/bin/sh
# Install the Arduino UNO tooling shipped with LibLapin.
# Usage: misc/arduino/install.sh [DESTDIR]

set -eu
base=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
root=${1:-}
case "$root" in
  ''|/*) ;;
  *) echo 'DESTDIR must be an absolute path' >&2; exit 2 ;;
esac
install -d "${root}/usr/bin" "${root}/usr/share/arduino"
install -m 755 "$base/avr-uno" "${root}/usr/bin/avr-uno"
install -m 755 "$base/bunny-uno-install" "${root}/usr/bin/bunny-uno-install"
install -m 644 "$base/bitbang.c" "${root}/usr/share/arduino/bitbang.c"
printf '%s\n' 'Bunny UNO v3 tools installed.'
