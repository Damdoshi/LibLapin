#!/bin/sh
clear
sh ./demo/bunny.sh
rm -rf ~/.froot/lib/libsfml*
rm -rf ~/.froot/lib/liblapin.a
rm -rf ~/.froot/lapin*
rm -rf ~/.froot/SFML/
echo "Uninstallation is almost complete. You still have to edit your shell configuration file."
