#this script simply run the program keeping in account the correct file paths
mkdir build
cd build
cmake ..
make
cd ..
./build/Pong