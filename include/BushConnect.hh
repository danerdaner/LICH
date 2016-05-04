#ifndef _BushConnect_hh_
#define _BushConnect_hh_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <marlin/Processor.h>
#include <EVENT/CalorimeterHit.h>
#include <EVENT/Cluster.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Track.h>
#include <IMPL/LCFlagImpl.h>
#include <TNtuple.h>
#include <TObject.h>

#include <TTree.h>
#include <TFile.h>
#include <TH3.h>
#include <TVector3.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/Config.h"



class TTree;

  class BushConnect  : public marlin::Processor
  {
  public:

    Processor*  newProcessor() { return new BushConnect ; }
 
    BushConnect();
    
    ~BushConnect() {};

    void init();

    void Clean();

    void TrackSort(EVENT::LCEvent* evtPP);
    void NewClusterFlag(Cluster* a_tree, Track* a_trk, LCCollection *col_TPCTrk);
    void EHBush2ndMerge(EVENT::LCEvent* evtPP);

    void BushSelfMerge(EVENT::LCEvent* evtPP);
 
    void BushTrackMatch(EVENT::LCEvent* evtPP);

    void BushMCPMatch(LCEvent * evtPP);

    void ParticleReco(LCEvent * evtPP);

    void processEvent( LCEvent * evtP );   

    void end();


  protected:
	std::string _treeFileName;
    std::vector<std::string> _BushCollections; 
    std::vector<std::string> _HitCollections;
    LCFlagImpl Cluflag;
    std::ostream *_output;

    std::vector<Track*> SortedTracks;
    std::map<Track*, float> Track_Energy;
    std::map<Track*, int> Track_Type;	
  
    std::map<Cluster*, int> ClusterType_1stID;
    std::map<ReconstructedParticle*, int> ChCoreID; 

// Add by V3

    std::vector<Cluster*> SortedSMBushes;	//SelfMerge Cluster output
    std::map<Cluster*, int> SMBushes_Type; 

// end Add V3

    std::vector<Cluster*> ecalchcore_tight;         //TightCores
    std::vector<Cluster*> ecalchcore_medium;
    std::vector<Cluster*> ecalchcore_loose;         //LooseCores    Let's also get
    std::vector<Cluster*> ecalchcore; 		    //Above three
    std::vector<Cluster*> ecalnecore;
    std::vector<Cluster*> ecalnecore_EM;
    std::vector<Cluster*> ecalnecore_NonEM;
    std::vector<Cluster*> ecalfrag;
    std::vector<Cluster*> ecalundef;
    std::vector<Cluster*> ecalfrag_TBM_CH;
    std::vector<Cluster*> ecalfrag_TBM_NE_EM;
    std::vector<Cluster*> ecalfrag_TBM_NE_NonEM;
    std::vector<Cluster*> ecalundef_iso;
    std::vector<Cluster*> ecalpotentialbackscattering;

    std::vector<Cluster*> hcalchcore_tight;         //LooseCores    Let's also get
    std::vector<Cluster*> hcalchcore_medium;
    std::vector<Cluster*> hcalchcore_loose;
    std::vector<Cluster*> hcalchcore;
    std::vector<Cluster*> hcalnecore;
    std::vector<Cluster*> hcalfrag;
    std::vector<Cluster*> hcalundef;
    std::vector<Cluster*> hcalfrag_TBM_CH;
    std::vector<Cluster*> hcalfrag_TBM_NE_EM;
    std::vector<Cluster*> hcalfrag_TBM_NE_NonEM;
    std::vector<Cluster*> hcalundef_iso; 

    std::vector<Cluster*> chargedclustercore;
    std::vector<Cluster*> chargedclustercore_abs;
    std::vector<Cluster*> non_chargedclustercore;

    std::map<Track*, TVector3> trkendposition;
    std::map<Cluster*, float> CluFD; 
    std::vector<TMVA::Reader*> reader_all;

    /*
       std::vector<Cluster*> PotentialEcalMuonCluster; 
       std::vector<Cluster*> PotentialHcalMuonCluster;
       std::vector<Cluster*> PotentialEcalEMCluster;
       std::vector<Cluster*> PotentialHcalEMCluster;
       std::vector<Cluster*> PotentialEcalHadCluster;
       std::vector<Cluster*> PotentialHcalHadCluster;
       std::vector<Cluster*> EcalFragments; 
       std::vector<Cluster*> HcalFragments;
       std::vector<Cluster*> PotentialIsoCluster; 

       std::vector<Cluster*> CoreChargedCluster; 
       std::vector<Cluster*> CoreNeutralCluster; 
       std::vector<Cluster*> PotentialChargedCluster; 
       std::vector<Cluster*> PotentialNeutralCluster; 

*/
	int EcalNHit, HcalNHit, CluNHit, NLEcal, NLHcal, NH[16], NL[16];
	float maxDisHtoL, minDisHtoL, avDisHtoL, avEnDisHtoL;
	float EcalEn, HcalEn, EClu, graDepth, cluDepth, graAbsDepth, maxDepth, minDepth, MaxDisHel, MinDisHel, FD_all, FD_ECAL, FD_HCAL, FD[16];
	float crdis, EEClu_L10, EEClu_R, EEClu_r, EEClu_p, rms_Ecal, rms_Hcal, rms_Ecal2, rms_Hcal2, av_NHE, av_NHH;
        int AL_Ecal, AL_Hcal;
	float FD_ECALF10, FD_ECALL20;
	int NH_ECALF10, NH_ECALL20;
	int CluIDFlag, ClusterID;
	float dEdx, mvaVal_pi, mvaVal_mu, mvaVal_e, cosTheta, Phi;
	int eventNr;
	float mvacut_pi=0.5;
	float mvacut_mu=0.5;
	float mvacut_e=0.5;
	int _outputtestroot;
	TTree *arborTree;
	TFile *tree_file;


  };

#endif


