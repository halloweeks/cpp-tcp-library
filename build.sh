#!/usr/bin/env bash
if ! dpkg -s cmake >/dev/null 2>&1; then
  echo "We not found cmake on your system\nPlease run apt-get install cmake"
  exit 1;
fi

rm -rf build
mkdir build
cd build
cmake ..
make
rm -rf ../build