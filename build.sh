#!/usr/bin/env bash

COMPILE_TYPE=$1

PRJ_COUNT=0
PRJ_LIST[0]=''
COST_TIME_LIST[0]=0
ALL_TIME_BEGIN=`date +%s`

if [ -z ${COMPILE_TYPE} ];
then
    echo -e "error need a param  --> usage ./build.sh  [debug] or [release]-----------------------"
    exit
fi

function Build()
{
    echo "-- $1 prject"
    echo "-- ${COMPILE_TYPE}"
    if [ ! -d $2 ];
    then
        echo -e "error build file " . $2 . " is not exsist-----------------"
        return
    fi
    cd $2
    BEGIN_TIME=`date +%s`

    make clean && make && make install
    cd -
    END_TIME=`date +%s`

    PRJ_LIST[$PRJ_COUNT]=$1
    COST_TIME_LIST[$PRJ_COUNT]=$(($END_TIME-$BEGIN_TIME))
    echo "-- duration ${COST_TIME_LIST[$PRJ_COUNT]} sec"
    PRJ_COUNT=${PRJ_COUNT}+1
}

N_TIME=`date`
echo -e "==============build start $N_TIME=================="
if [ "$COMPILE_TYPE" == "release" ];
then
    cd ./build/release
else
    cd ./build/debug
fi

#-----------begin --------------------------------
#make common
Build 'common' './common'
#network
Build 'nett' './network/nett'
#test
Build 'test' './test'
#-----------end--------------------------------

cd ../../
N_TIME=`date`
echo -e "==============build finished $N_TIME==============="

ALL_END_TIME=`date +%s`
duration=$(($ALL_END_TIME-$ALL_TIME_BEGIN))

echo  "==================all prjects build duration" $duration "seconds=================="
for((i=0; i<$PRJ_COUNT;i++))
do
  echo  ${PRJ_LIST[$i]} durate time ${COST_TIME_LIST[$i]} seconds
done
echo  "==================all prjects build duration" $duration "seconds=================="

