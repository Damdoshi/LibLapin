cd ../../../../
find src/network/ -name "*.o" -delete
make -j12
./school_install.sh
cd -
make re
