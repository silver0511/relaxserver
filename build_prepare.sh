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

#proto
rm -rf ./include/package/protobuf/hpb
rm -rf ./pb_serialize/hpb
mkdir ./pb_serialize/hpb
mkdir ./include/package/protobuf/hpb
protoc -I=./include/package/protobuf/pb --cpp_out=./include/package/protobuf/hpb ./include/package/protobuf/pb/*.proto
rm -rf ./include/package/protobuf/hpb/*.cc
protoc -I=./include/package/protobuf/pb --cpp_out=./pb_serialize/hpb ./include/package/protobuf/pb/*.proto
rm -rf ./pb_serialize/hpb/*.h

date
if [ -z $COMPILE_TYPE ];
then
    echo -e "Error need a Param  --> Usage ./build_prepare.sh  [debug] or [release]-----------------------"
    exit
fi

#-----------begin --------------------------------
if [ "$COMPILE_TYPE" == "release" ];
then
    echo -e "Start cmake release-----------------------"
    cd ./build/release
    cmake -DCOMPILE_TYPE=release -DCOMPILE_TOOL=command ../../
    cd ../../
    echo -e "End cmake release-------------------------"
else
    echo -e "Start cmake debug-----------------------"
    cd ./build/debug
    cmake -DCOMPILE_TYPE=debug -DCOMPILE_TOOL=command  ../../
    cd ../../
    echo -e "End cmake debug-------------------------"
fi
#-----------end--------------------------------

