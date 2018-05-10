#!/bin/bash
if  test "build";then
	cd build
	cmake ..
	make
else
	mkdir build
	cd build
	cmake ..
	make
	
fi
