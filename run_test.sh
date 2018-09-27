#!/usr/bin/env bash

COMPILE_TYPE=$1
ROOT_DIR=`pwd`
if [ -z ${COMPILE_TYPE} ];
then
    echo -e "error need a param  --> usage ./build.sh  [debug] or [release]-----------------------"
    exit
fi

function readfile ()
{
  for file in `ls $1`
  do
    if [ -d $1"/"$file ]
    then
      readfile $1"/"$file
    elif [ -x $1"/"$file ]
    then
        FILE_NAME=`basename $file`
        if [ $FILE_NAME = "test_log_trace" ]
        then
            echo -e "skip $FILE_NAME test"
        else
            cd $1"/"
            chmod +x ./$file
            export LD_LIBRARY_PATH=$ROOT_DIR/bin/$COMPILE_TYPE:$LD_LIBRARY_PATH
            ./$file
            cd -
        fi
    fi
  done
}

TEST_ROOT_DIR=$ROOT_DIR/bin/$COMPILE_TYPE/test
if [ ! -d $TEST_ROOT_DIR ];
then
    echo -e "error test directory  $TEST_ROOT_DIR is not exsist------------"
    exit
fi


readfile $TEST_ROOT_DIR
