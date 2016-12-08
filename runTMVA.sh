#!/bin/bash

path=`pwd`
cd $path

pars=("pi" "e" "mu")
ens=(1 2 3 5 7 10 20 30 40 50 70 120 250)
pos=("endcap" "overlap" "barrel1" "barrel2" "all")

ipar=1
pnum=3

ien=0
while [ "$ien" -lt "11" ]
do
export SimuWorkDir=InputFiles

INPUT="$SimuWorkDir/all_${energy}GeV/PID_${energy}GeV.root"
ipos=0
while [ "$ipos" -lt "5" ]
do
POS=${pos[$ipos]}
OUTPUTDATA="cepc_TMVA"
if [ -f "$INPUT" ]; then
echo $SimuWorkDir/$OUTPUTDATA
mkdir -p $SimuWorkDir/$OUTPUTDATA
OUTPUTTMVA="TMVA_${energy}GeV_$POS.root"
TMVAMulticlassEN="TMVAMulticlass_${energy}GeV_$POS"

cp -fr TMVAClassification_$POS.C $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C
sed -i "s#INPUT#$INPUT#g" $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C
sed -i "s#OUTPUTTMVA#$OUTPUTTMVA#g" $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C
sed -i "s#TMVAMulticlassEN#$TMVAMulticlassEN#g" $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C

cd $SimuWorkDir/$OUTPUTDATA/
echo $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C
root -q -l $SimuWorkDir/$OUTPUTDATA/TMVAClassification.C\(\"BDTG\"\)
cd $path
fi
let "ipos+=1"
done
let "ien+=1"
done

