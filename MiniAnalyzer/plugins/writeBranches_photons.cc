//----------------------------------------------//
// This plugin is called in the header file.    //
// No need to repeat it in the main source.     //
// The functions are called in the main source, //
// and must be declared in the header file.     //
//                               - Prachurjya   //
//----------------------------------------------//

#include "MiniAnalyzer.h"
#include "Rtypes.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <cmath>
#include <vector>
using namespace std;
using namespace edm;

//------------------------------------------------------------
// Declaring event/object-level variables that I want to keep:
// Object level variables are vectors.
//------------------------------------------------------------

//Basic 4-vectors:
Int_t         nPho_;
vector<float> phoE_;
vector<float> phoEt_;
vector<float> phoPt_;
vector<float> phoEta_;
vector<float> phoPhi_;
vector<float> phoMatchingGenPt_; //gen-pt, if it matches with the reco photon

//Variables that I need for the photon-id
//Shower shape variables:
vector<float> phoHoverE_;
vector<float> phoHoverECone_;
vector<float> phoHoverEValid_; //boolean
vector<float> phoSigmaIEtaIEtaFull5x5_;
vector<float> phoSigmaIEtaIPhiFull5x5_;
vector<float> phoSigmaIPhiIPhiFull5x5_;
vector<float> phoR9Full5x5_;
vector<float> phoR93x3_;
vector<float> phoSigmaIEtaIEta3x3_;

//Calorimeter features:
vector<float> phoEcalPFClusterIso_;
vector<float> phoHcalPFClusterIso_;
vector<float> phoEcalRecHit_;
vector<float> phoHcalTower_;
vector<int>   phohasPixelSeed_; //boolean

//Track features:
vector<float> phoTrkSumPtHollow_;
vector<float> phoTrkSumPtSolid_;

//Flags:
vector<int> isPhotonMatching_;
vector<int> isPromptFinalState_;
vector<int> isDirectHardProcessTauDecayProductFinalState_;
vector<int> isDirectHadronDecayProduct_;
vector<int> isTauDecayProduct_;
vector<int> isPromptTauDecayProduct_;
vector<int> isDirectTauDecayProduct_;
vector<int> isDirectPromptTauDecayProduct_;
vector<int> isDirectPromptTauDecayProductFinalState_;
vector<int> isHardProcess_;
vector<int> fromHardProcessFinalState_;
vector<int> fromHardProcessDecayed_;
vector<int> isPionMother_;
vector<int> isPFPhoton_;

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
  tree->Branch("phoHoverE",                        &phoHoverE_);
  tree->Branch("phoHoverECone",                    &phoHoverECone_);
  tree->Branch("phoHoverEValid",                   &phoHoverEValid_);
  tree->Branch("phoSigmaIEtaIEtaFull5x5",          &phoSigmaIEtaIEtaFull5x5_);
  tree->Branch("phoSigmaIEtaIPhiFull5x5",          &phoSigmaIEtaIPhiFull5x5_);
  tree->Branch("phoSigmaIPhiIPhiFull5x5",          &phoSigmaIPhiIPhiFull5x5_);
  tree->Branch("phoR9Full5x5",                     &phoR9Full5x5_);
  tree->Branch("phoR93x3",                         &phoR93x3_);
  tree->Branch("phoSigmaIEtaIEta3x3",              &phoSigmaIEtaIEta3x3_);
  tree->Branch("phoEcalPFClusterIso",              &phoEcalPFClusterIso_);
  tree->Branch("phoHcalPFClusterIso",              &phoHcalPFClusterIso_);
  tree->Branch("phoEcalRecHit",                    &phoEcalRecHit_);
  tree->Branch("phoHcalTower",                     &phoHcalTower_);
  tree->Branch("phohasPixelSeed",                  &phohasPixelSeed_);
  tree->Branch("phoTrkSumPtHollow",                &phoTrkSumPtHollow_);
  tree->Branch("phoTrkSumPtSolid",                 &phoTrkSumPtSolid_);
  tree->Branch("isPromptFinalState",               &isPromptFinalState_);
  tree->Branch("isDirectHardProcessTauDecayProductFinalState", &isDirectHardProcessTauDecayProductFinalState_);
  tree->Branch("isDirectHadronDecayProduct",       &isDirectHadronDecayProduct_);
  tree->Branch("isTauDecayProduct",                &isTauDecayProduct_);
  tree->Branch("isPromptTauDecayProduct",          &isPromptTauDecayProduct_);
  tree->Branch("isDirectTauDecayProduct",          &isDirectTauDecayProduct_);
  tree->Branch("isDirectPromptTauDecayProduct",    &isDirectPromptTauDecayProduct_);
  tree->Branch("isDirectPromptTauDecayProductFinalState", &isDirectPromptTauDecayProductFinalState_);
  tree->Branch("isHardProcess",                    &isHardProcess_);
  tree->Branch("fromHardProcessFinalState",        &fromHardProcessFinalState_);
  tree->Branch("fromHardProcessDecayed",           &fromHardProcessDecayed_);
  tree->Branch("phoMatchingGenPt",                 &phoMatchingGenPt_);
  tree->Branch("isPionMother",                     &isPionMother_);
  tree->Branch("isPFPhoton",                       &isPFPhoton_);

}

//-----------------------------------
// Filling up the branches:
//-----------------------------------
void MiniAnalyzer::fillBranches_photons(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  //This functions runs per event.
 
  //Initializing the variables, to get rid of the previous events in the loop.
  nPho_ = 0;
  phoE_   .clear();
  phoEt_  .clear();
  phoPt_  .clear();
  phoEta_ .clear();
  phoPhi_ .clear();
  phoMatchingGenPt_        .clear();
  phoHoverE_               .clear();
  phoHoverECone_           .clear();
  phoHoverEValid_          .clear();
  phoSigmaIEtaIEtaFull5x5_ .clear();
  phoSigmaIEtaIPhiFull5x5_ .clear();
  phoSigmaIPhiIPhiFull5x5_ .clear();
  phoR9Full5x5_            .clear();
  phoR93x3_                .clear();
  phoSigmaIEtaIEta3x3_     .clear();
  phoEcalPFClusterIso_     .clear();
  phoHcalPFClusterIso_     .clear();
  phoEcalRecHit_           .clear();
  phoHcalTower_            .clear();
  phohasPixelSeed_         .clear(); 
  phoTrkSumPtHollow_       .clear();
  phoTrkSumPtSolid_        .clear();
  isPromptFinalState_      .clear();
  isDirectHardProcessTauDecayProductFinalState_ .clear();
  isDirectHadronDecayProduct_ .clear();
  isTauDecayProduct_       .clear();
  isPromptTauDecayProduct_ .clear();
  isDirectTauDecayProduct_ .clear();
  isDirectPromptTauDecayProduct_ .clear();
  isDirectPromptTauDecayProductFinalState_ .clear();
  isHardProcess_           .clear();
  fromHardProcessFinalState_ .clear();
  fromHardProcessDecayed_  .clear();
  isPionMother_            .clear();
  isPFPhoton_              .clear();

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

    phoE_   .push_back(iPho->energy());
    phoEt_  .push_back(iPho->et());
    phoPt_  .push_back(iPho->pt());
    phoEta_ .push_back(iPho->eta());
    phoPhi_ .push_back(iPho->phi());

    //Shower-shape variables:
    phoHoverE_               .push_back(iPho->hadTowOverEm());
    phoHoverECone_           .push_back(iPho->hadronicOverEm());
    phoHoverEValid_          .push_back(iPho->hadTowOverEmValid());
    phoSigmaIEtaIEtaFull5x5_ .push_back(iPho->full5x5_sigmaIetaIeta());
    phoSigmaIEtaIPhiFull5x5_ .push_back(iPho->full5x5_showerShapeVariables().sigmaIetaIphi);
    phoSigmaIPhiIPhiFull5x5_ .push_back(iPho->full5x5_showerShapeVariables().sigmaIphiIphi);
    phoR9Full5x5_            .push_back(iPho->full5x5_r9());
    phoR93x3_                .push_back(iPho->r9());
    phoSigmaIEtaIEta3x3_     .push_back(iPho->sigmaIetaIeta());

    //Calorimeter features:
    phoEcalPFClusterIso_     .push_back(iPho->ecalPFClusterIso());
    phoHcalPFClusterIso_     .push_back(iPho->hcalPFClusterIso());
    phoEcalRecHit_           .push_back(iPho->ecalRecHitSumEtConeDR03());
    phoHcalTower_            .push_back(iPho->hcalTowerSumEtConeDR03());
    phohasPixelSeed_         .push_back(iPho->hasPixelSeed());
    //Track features:
    phoTrkSumPtHollow_       .push_back(iPho->trkSumPtHollowConeDR03());
    phoTrkSumPtSolid_        .push_back(iPho->trkSumPtSolidConeDR03());

    //-----------------------------------//
    // Filling up gen-level information  //
    //-----------------------------------//
    edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
    iEvent.getByToken(genParticlesCollection_, genParticlesHandle);
    if (!genParticlesHandle.isValid()) { edm::LogWarning("egmNtuplizer") << "no reco::GenParticles in event"; return;}
    float dR_min = 1000; int genIndex = 0; int matching_index=-1;
    for (vector<reco::GenParticle>::const_iterator iGenPho = genParticlesHandle->begin(); iGenPho != genParticlesHandle->end(); ++iGenPho) {
      genIndex++;
      if(iGenPho->pdgId() == 22 && iGenPho->status()==1){ //if the gen particle is a real photon,
	float deta = iPho->eta() - iGenPho->eta();
	float dphi = iPho->phi() - iGenPho->phi();
	if(dphi>M_PI) dphi = 2*M_PI-dphi; //if the difference is over pi, then we must take the other side of the angle
	float dR_sq = deta*deta + dphi*dphi;
	float dR = sqrt(dR_sq);
	if(dR<dR_min){
	  dR_min=dR;
	  matching_index = genIndex;
	}
      }
    }
    if(dR_min<0.1){
      isPhotonMatching_.push_back(1);
      int index=0;
      for (vector<reco::GenParticle>::const_iterator iGenPho = genParticlesHandle->begin(); iGenPho != genParticlesHandle->end(); ++iGenPho){
	index++;
	if(iGenPho->pdgId() == 22 && iGenPho->status()==1 && index==matching_index){//photon, real, matching
	  phoMatchingGenPt_ .push_back(iGenPho->pt());
	  isPromptFinalState_                                  .push_back(iGenPho->isPromptFinalState());
	  isDirectHardProcessTauDecayProductFinalState_        .push_back(iGenPho->isDirectHardProcessTauDecayProductFinalState());
	  isDirectHadronDecayProduct_                          .push_back(iGenPho->statusFlags().isDirectHadronDecayProduct());
	  isTauDecayProduct_                                   .push_back(iGenPho->statusFlags().isTauDecayProduct());
	  isPromptTauDecayProduct_                             .push_back(iGenPho->statusFlags().isPromptTauDecayProduct());
	  isDirectTauDecayProduct_                             .push_back(iGenPho->statusFlags().isDirectTauDecayProduct());
	  isDirectPromptTauDecayProduct_                       .push_back(iGenPho->statusFlags().isDirectPromptTauDecayProduct());
	  isDirectPromptTauDecayProductFinalState_             .push_back(iGenPho->isDirectPromptTauDecayProductFinalState());
	  isHardProcess_                                       .push_back(iGenPho->isHardProcess());
	  fromHardProcessFinalState_                           .push_back(iGenPho->fromHardProcessFinalState());
	  fromHardProcessDecayed_                              .push_back(iGenPho->fromHardProcessDecayed());
	  if(iGenPho->mother()->pdgId() == 111) isPionMother_  .push_back(1);
	  else isPionMother_                                   .push_back(0);
	}
      }
    }
    else{
      isPhotonMatching_                            .push_back(0);
      phoMatchingGenPt_                            .push_back(-999);
      isPromptFinalState_                          .push_back(-999);
      isDirectHardProcessTauDecayProductFinalState_.push_back(-999);
      isDirectHadronDecayProduct_                  .push_back(-999);
      isTauDecayProduct_                           .push_back(-999);
      isPromptTauDecayProduct_                     .push_back(-999);
      isDirectTauDecayProduct_                     .push_back(-999);
      isDirectPromptTauDecayProduct_               .push_back(-999);
      isDirectPromptTauDecayProductFinalState_     .push_back(-999);
      isHardProcess_                               .push_back(-999);
      fromHardProcessFinalState_                   .push_back(-999);
      fromHardProcessDecayed_                      .push_back(-999);
      isPionMother_                                .push_back(-999);
    }
    
    //--------------------//
    //  Particle Flow ID  //
    //--------------------//
    // For the particle-flow photons, the following restrictions are put on a photon candidate:
    // 1. Kinematic restriction: A minimum pT of 10 GeV.
    // 2. HCAL/ECAL deposit < 0.05 (most of the energy showd be deposited in the ECAL region).
    // 3. Isolation restriction : The sum of pT + ECAL ET + HCAL ET of the other objects within dR 0.3 should be less than 10.
    // 4. If HCAL deposit is non-zero, then the sum of track pT (including the photon itself) within dR 0.3 should be less that 10 + 3*phoPt
    // 5. Shower shape restrictions: for barrel (endcap), sigmaIetaIeta (3x3) should be less than 0.0125 (0.034).
    // These conditions are implemented as shown  below. (Bad photons are vetoed by setting the flag to false.)
    
    bool fillPFflag = true;
    if(iPho->pt() < 10.0)           fillPFflag = false;
    if(iPho->hadTowOverEm() > 0.05) fillPFflag = false;
    if(iPho->trkSumPtHollowConeDR03() + iPho->ecalRecHitSumEtConeDR03() + iPho->hcalTowerSumEtConeDR03() > 10.0) fillPFflag = false;
    if(iPho->hadTowOverEmValid() != 0 && iPho->trkSumPtSolidConeDR03() > 10.0 + 0.3*iPho->pt()) fillPFflag = false;
    if(abs(iPho->eta()) < 1.442 && iPho->sigmaIetaIeta() > 0.0125) fillPFflag = false; //Barrel photons with abs(eta) < 1.442
    if(abs(iPho->eta()) > 1.566 && iPho->sigmaIetaIeta() > 0.034)  fillPFflag = false; //Endcap photons with abs(eta) > 1.556 (no upper cap)

    if(fillPFflag == true) isPFPhoton_ .push_back(1);
    else                   isPFPhoton_ .push_back(0);
  }//Photon loop ends here.
    
}
