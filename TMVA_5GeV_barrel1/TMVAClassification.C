#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void TMVAClassification( TString myMethodList = "" )
{
  TMVA::Tools::Instance();

  TString outfileName( "TMVA_5GeV_barrel1.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  TMVA::Factory* factory = new TMVA::Factory("TMVAMulticlass_5GeV_barrel1",outputFile,
		                           "!V:!Silent:Color:!DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=multiclass" );
  TFile* file_0 = TFile::Open("/afs/ihep.ac.cn/users/y/yudan/yudan/proPID/tmp_5GeV/output.root_5.root");
  if (!file_0->IsOpen()) std::cout << "could not open file" <<std::endl;
  
  TTree* treePi = (TTree*)file_0->Get("Pion");
  if (treePi == 0) std::cout << "could not open tree" <<std::endl;
  
  TTree* treeMu = (TTree*)file_0->Get("Muon");
  if (treeMu == 0) std::cout << "could not open tree" <<std::endl;
  
  TTree* treeE = (TTree*)file_0->Get("Electron");
  if (treeE == 0) std::cout << "could not open tree" <<std::endl;


  factory->AddTree( treePi, TString("Pi"), 1.,"abs(cosTheta)<0.3" );
  factory->AddTree( treeMu, TString("Mu"), 1.,"abs(cosTheta)<0.3");
  factory->AddTree( treeE, TString("E"), 1.,"abs(cosTheta)<0.3");


  factory->AddVariable("EcalNHit","EcalNHit", "units", 'I');
  factory->AddVariable("HcalNHit","HcalNHit", "units", 'I');
  factory->AddVariable("NLEcal","NLEcal", "units", 'I');
  factory->AddVariable("NLHcal","NLHcal", "units", 'I');
  factory->AddVariable("maxDisHtoL","maxDisHtoL", "units", 'F');
  factory->AddVariable("avDisHtoL","avDisHtoL", "units", 'F');
  factory->AddVariable("EE := EcalEn/EClu","EcalEn", "units", 'F');
  factory->AddVariable("graDepth","graDepth", "units", 'F');
  factory->AddVariable("cluDepth","cluDepth", "units", 'F');
  factory->AddVariable("minDepth","minDepth", "units", 'F');
  factory->AddVariable("MaxDisHel","MaxDisHel", "units", 'F');
  factory->AddVariable("FD_all","FD_all", "units", 'F');
  factory->AddVariable("FD_ECAL","FD_ECAL", "units", 'F');
  factory->AddVariable("FD_HCAL","FD_HCAL", "units", 'F');
  factory->AddVariable("E_10 := EEClu_L10/EcalEn","EEClu_L10", "units", 'F');
  factory->AddVariable("E_R := EEClu_R/EcalEn","EEClu_R", "units", 'F');
  factory->AddVariable("E_r := EEClu_r/EcalEn","EEClu_r", "units", 'F');
  factory->AddVariable("rms_Hcal","rms_Hcal", "units", 'F');
  factory->AddVariable("av_NHH","av_NHH", "units", 'F');
  factory->AddVariable("AL_Ecal","AL_Ecal", "units", 'I');
  factory->AddVariable("FD_ECALF10","FD_ECALF10", "units", 'F');
  factory->AddVariable("FD_ECALL20","FD_ECALL20", "units", 'F');
  factory->AddVariable("NH_ECALF10","NH_ECALF10", "units", 'I');
  factory->AddVariable("dEdx","dEdx", "units", 'F');
	  
  
   std::cout << "--- TMVAClassification       : Using input file: " << std::endl;
   

   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   
   factory->PrepareTrainingAndTestTree( "", "SplitMode=Random:NormMode=NumEvents:!V" );
   
   factory->BookMethod( TMVA::Types::kBDT, "BDTG",
			"!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.50:nCuts=20:NNodesMax=8" );
   
   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();

   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

}
