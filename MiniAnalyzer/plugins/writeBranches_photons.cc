//-----------------------
// Prachurjya
//-----------------------

#include "MiniAnalyzer.h"
#include "Rtypes.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <cmath>
#include <vector>
using namespace std;
using namespace edm;

//-----------------------------------------------------
// Declaring event-level variables that I want to keep:
// Object level bariables are vectors.
//-----------------------------------------------------

Int_t          nPho_;
vector<float>  phoE_;
vector<float>  phoEt_;
vector<float>  phoPt_;
vector<float>  phoEta_;
vector<float>  phoPhi_;

//-----------------------------------
// Creating the branches:
//-----------------------------------
void MiniAnalyzer::createBranches_photons(TTree* tree){
  tree->Branch("nPho",   &nPho_);
  tree->Branch("phoE",   &phoE_);
  tree->Branch("phoEt",  &phoEt_);
  tree->Branch("phoPt",  &phoPt_);
  tree->Branch("phoEta", &phoEta_);
  tree->Branch("phoPhi", &phoPhi_);
}

//-----------------------------------
// Filling up the branches:
//-----------------------------------
void MiniAnalyzer::fillBranches_photons(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  //Initializing the variables, to get rid of the previous events in the loop.
  phoE_   .clear();
  phoEt_  .clear();
  phoPt_  .clear();
  phoEta_ .clear();
  phoPhi_ .clear();

  edm::Handle<edm::View<pat::Photon> > photonHandle;
  iEvent.getByToken(photonCollection_, photonHandle); //The token is defined in the main cc file
  
  //Flags:
  if (!photonHandle.isValid()) {
    edm::LogWarning("ntuple-maker") << "no pat::Photons in event";
    return;
  }

  //Filling up the vectors in object loop:
  for (edm::View<pat::Photon>::const_iterator iPho = photonHandle->begin(); iPho != photonHandle->end(); ++iPho) {

    nPho_++;

    phoE_               .push_back(iPho->energy());
    phoEt_              .push_back(iPho->et());
    phoPt_              .push_back(iPho->pt());
    phoEta_             .push_back(iPho->eta());
    phoPhi_             .push_back(iPho->phi());
    
  }
    
}
