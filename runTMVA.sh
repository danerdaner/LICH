#!/bin/bash

path=`pwd`
cd $path

ens=(1 2 3 5 7 10 20 30 40 50 70)
pos=("endcap" "overlap" "barrel1" "barrel2" "all")

ien=0
while [ "$ien" -lt "11" ]
do

export SimuWorkDir=$path

energy=${ens[$ien]}
INPUT="$SimuWorkDir/tmp_${energy}GeV/output.root_${energy}.root"

ipos=0
while [ "$ipos" -lt "5" ]
do

POS=${pos[$ipos]}
OUTPUTDATA="TMVA_${energy}GeV_$POS"
mkdir -p $SimuWorkDir/$OUTPUTDATA
OUTPUTTMVA="TMVA_${energy}GeV_$POS.root"
TMVAMulticlassEN="TMVAMulticlass_${energy}GeV_$POS"

echo "$SimuWorkDir/$OUTPUTDATA/"
rm -rf $SimuWorkDir/$OUTPUTDATA/*
cp -fr $path/TMVAClassification_$POS.C $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C
sed -i "s#INPUT#$INPUT#g" $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C
sed -i "s#OUTPUTTMVA#$OUTPUTTMVA#g" $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C
sed -i "s#TMVAMulticlassEN#$TMVAMulticlassEN#g" $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C

cd $SimuWorkDir/$OUTPUTDATA/
root -q -l $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C\(\"BDTG\"\)
cd $path
let "ipos+=1"
done
let "ien+=1"
done

