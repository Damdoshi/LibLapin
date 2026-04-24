#!/bin/sh

find . -type f \( -name '*.sh' -o -name '*.c' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' -o -name '*.dab' -o -name '*.ini' \) -print0 | tar --null -czf lapin_sources.tar.gz --files-from=-
