#!/usr/bin/env bash

COMPILE_TYPE=$1

#build文件夹检查
if [ ! -d "./build/debug" ]; then
    mkdir -p "./build/debug"
fi
if [ ! -d "./build/release" ]; then
    mkdir -p "./build/release"
fi

#lib文件夹检查
if [ ! -d "./lib/debug" ]; then
    mkdir -p "./lib/debug"
fi
if [ ! -d "./lib/release" ]; then
    mkdir -p "./lib/release"
fi

#bin文件夹检查
if [ ! -d "./bin/debug/log" ]; then
    mkdir -p "./bin/debug/log"
fi
if [ ! -d "./bin/release/log" ]; then
    mkdir -p "./bin/release/log"
fi

#copy config
rm -rf ./bin/debug/config
rm -rf ./bin/release/config
cp -rf ./config ./bin/debug
cp -rf ./config ./bin/release

#copy third_party
rm -rf ./bin/debug/third_party
rm -rf ./bin/release/third_party
cp -rf ./third_party ./bin/debug
cp -rf ./third_party ./bin/release


date
if [ -z $COMPILE_TYPE ];
then
    echo -e "Error need a Param  --> Usage ./build_cs.sh  [debug] or [release]-----------------------"
    exit
fi

#-----------begin --------------------------------
if [ "$COMPILE_TYPE" == "release" ];
then
    echo -e "Start cmake release-----------------------"
    cd ./build/release
    cmake -DCOMPILE_TYPE=release ../../
    cd ../../
    echo -e "End cmake release-------------------------"
else
    echo -e "Start cmake debug-----------------------"
    cd ./build/debug
    cmake -DCOMPILE_TYPE=debug ../../
    cd ../../
    echo -e "End cmake debug-------------------------"
fi
#-----------end--------------------------------

