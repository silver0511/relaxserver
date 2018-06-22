#!/usr/bin/env bash
echo "clean build cache start...................."
rm -rf build/debug/*
rm -rf build/release/*
rm -rf build
echo "clean build cache success.................."

echo "clean bin cache start......................"
rm -rf bin/debug/*
rm -rf bin/release/*
rm -rf bin
echo "clean bin cache success...................."

echo "clean lib cache start......................"
rm -rf lib
echo "clean lib cache end........................"
