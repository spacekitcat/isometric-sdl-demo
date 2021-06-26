#!/bin/bash

# Convenience script for doing a clean build. 
# Useful when new files are added to ./assets
# 
# Dependencies: coreutils (OSX: `brew install coreutils`)

build_path=$(realpath ./build)

if [ -d $build_path ]
    then
        echo "Deleting build directory ($build_path)"
        rm -r $build_path
fi

if [ ! -d $build_path ]
    then
        echo "Recreating build directory ($build_path)"
        mkdir $build_path
fi

echo "Generating build"
cmake -S . -B $build_path

echo "Running build"
cmake --build $build_path
