#!/bin/bash

path=`pwd`
cd $path

ens=(1 2 3 5 7 10 20 30 40 50 70)


ien=0
while [ "$ien" -lt "11" ]
do

energy=${ens[$ien]}

export SimuWorkDir=$PWD

##Put your ILCsoft path here
export ILC_HOME=/afs/ihep.ac.cn/soft/common/gcc/v01-17-05

##The input lcio files can be chaged to your own path here
InputFiles_slcio_pi="$PWD/Reco_pi_${energy}GeV.slcio"
InputFiles_slcio_e="$PWD/Reco_e_${energy}GeV.slcio"
InputFiles_slcio_mu="$PWD/Reco_mu_${energy}GeV.slcio"

##Gearfile
GEARFILE="/afs/ihep.ac.cn/users/y/yudan/yudan/PID/Track.xml"

OUTPUTDATA="tmp_${energy}GeV"
OUTPUT_slcio="$SimuWorkDir/$OUTPUTDATA/Output_${energy}GeV.slcio"
OUTPUT_root="$SimuWorkDir/$OUTPUTDATA/output"

##1 when you want to produce the sample files for training, 0 when there is already weight files for PID
trainingF=0

##the name of recontructed particle in the input lcio files
inputPFO=ArborPFOs

##the path of weight file
WEIGHTDIR=$path

mkdir -p $SimuWorkDir/$OUTPUTDATA/

cp -fr $PWD/reco.xml $SimuWorkDir/$OUTPUTDATA/pid.xml

sed -i "s#INPUTLCIO_PI#$InputFiles_slcio_pi#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#INPUTLCIO_E#$InputFiles_slcio_e#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#INPUTLCIO_MU#$InputFiles_slcio_mu#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#GEARFILE#$GEARFILE#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#OUTPUTLCIO#$OUTPUT_slcio#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#OUTPUT#$OUTPUT_root#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#TRAININGEN#$energy#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#TRAININGFLAG#$trainingF#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#INPUTPFO#$inputPFO#g" $SimuWorkDir/$OUTPUTDATA/pid.xml
sed -i "s#WEIGHTDIR#$WEIGHTDIR#g" $SimuWorkDir/$OUTPUTDATA/pid.xml

echo \
"#! /bin/bash
source $ILC_HOME/init_ilcsoft.sh
source $PWD/env.sh
Marlin $SimuWorkDir/$OUTPUTDATA/pid.xml

" > $SimuWorkDir/$OUTPUTDATA/job_${energy}GeV.sh
echo "$SimuWorkDir/$OUTPUTDATA/job_${energy}GeV.sh"
sh $SimuWorkDir/$OUTPUTDATA/job_${energy}GeV.sh
let "ien+=1"
done

