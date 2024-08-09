#!/bin/sh

dpkg-buildpackage -us -uc -d
mkdir conf/incoming
(cd conf/incoming/ && reprepro -b . includedeb stable ../../../liblapin*.deb)

