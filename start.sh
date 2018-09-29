#!/usr/bin/env bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
rm -rf log/*

sleep 2
./server.1.1.100 &
exit