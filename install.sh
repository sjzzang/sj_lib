#!/bin/bash

if [ -d "build" ]
then
	echo "already have directory"
	rm -rf build
	rm -rf lib
	rm -rf include
else
	echo "create directory"
fi
mkdir build

cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../
make
make install
