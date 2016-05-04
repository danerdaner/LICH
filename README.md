# Marlin-PID-processor

The processor can be used for producing sample to train the TMVA, or use the TMVA weight files for charged particle identification. A ilcsoft package is needed.

1.Install

mkdir build
cd build
cmake -C $ILCSOFT/ILCSoft.cmake ..
make install

cd ..
source env.sh

2.Sample producing 

With your own simulated sample at different energy points, (here is (1,2,3,5,7,10,20,30,40,50,70) by default, you can change it sub\_PID.sh), you can run sub\_PID.sh after turn trainingF to 1 and put your directories inside

3.Training

Once the Sample produced, runTMVA.sh can be run for training.

4.Identification

If weight files exits, you can turn trainingF to 0 in sub\_PID.sh and run it for PID. Attention, the "InputEnergyPoints" parameter must be the same as the energy points of the weight files. A ReconstrutedParticle collection called typedPFOs will be produced in the output slcio file.






