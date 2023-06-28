#!/bin/sh

SOURCE_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR="$SOURCE_DIR/build"


cd $SOURCE_DIR


BUILD_TYPE="Debug"

for arg in "$@" 
do
  if [ "$arg" = "Release" ]; then
    BUILD_TYPE="Release"
  fi
done

cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -S "$SOURCE_DIR/." -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"
