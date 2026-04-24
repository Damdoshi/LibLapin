cd ../../../../
find src/network/ -name "*.o" -delete
make -j8
sudo make install
cd -
make re
