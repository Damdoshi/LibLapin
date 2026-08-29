#!/bin/sh

{
  find . -type f \( \
    -name 'Makefile' -o \
    -name 'makefile' -o \
    -name '*.mk' -o \
    -name '*.sh' -o \
    -name '*.c' -o \
    -name '*.cpp' -o \
    -name '*.h' -o \
    -name '*.hpp' -o \
    -name '*.dab' -o \
    -name '*.ini' \
  \) -print0

  find debian -type f -print0 2>/dev/null
  find . -maxdepth 2 -type f \( \
    -name 'Makefile' -o \
    -name 'makefile' -o \
    -name 'control' -o \
    -name 'rules' \
  \) -print0

  find misc/docs/website/ -type f -print0

  echo bcc b++ bcontext
} | tar --null -czf lapin_sources.tar.gz --files-from=-

