cd ../../../../
find src/network/ -name "*.o" -delete
make -j4
sudo make install
cd -
make re
