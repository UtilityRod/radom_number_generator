rm -rf bin
rm server_main
mkdir bin
cd bin
cmake ..
make
mv ../bin/server_main ..
mv ../bin/client_main ..