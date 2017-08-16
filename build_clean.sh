#!/usr/bin/env bash
echo "clean build cache start...................."
rm -rf build/debug/*
rm -rf build/release/*
echo "clean build cache success.................."

echo "clean bin cache start......................"
rm -rf bin/debug/*
rm -rf bin/release/*
echo "clean bin cache success...................."