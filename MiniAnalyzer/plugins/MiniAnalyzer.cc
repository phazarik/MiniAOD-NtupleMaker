// -*- C++ -*-
//--------------------------------------------------------
//
// Package:    FlatNtupleMaker/MiniAnalyzer
// Class:      MiniAnalyzer
//
//
// Original Author:  Prachurjya Hazarika
//         Created:  Fri, 05 Jul 2024 05:33:29 GMT
//
//--------------------------------------------------------
using namespace std;
#include "MiniAnalyzer.h"

// --------------------------------------------------
// The analyzer class is declared in the header file,
// so that it is visible to all the modules.
// Additional features of the class are defined here.
// --------------------------------------------------

//Constructor for setting up the tokens and the global variables:
MiniAnalyzer::MiniAnalyzer(const edm::ParameterSet& iConfig){
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  
  // Extracting parameters from the config file and setting the tokens:
  photonCollection_ = consumes<edm::View<pat::Photon>>(iConfig.getParameter<edm::InputTag>("photonSrc"));
  genParticlesCollection_ = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticleSrc"));

  //Creating the tree:
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("Events", "EventInfo");

  //Assigning branches to the tree:
  //These branches are filled in the method called for each event. 
  createBranches_photons(tree); //Function defined in the photon file.
  
}

//Destructor:
MiniAnalyzer::~MiniAnalyzer() {
}

//--------------------------------------------------------
// ------------ method called for each event  ------------
//--------------------------------------------------------

void MiniAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;

  //Checking flags for good events that I want to keep:

  //Filling up the tree with events:
  fillBranches_photons(iEvent, iSetup); //Function defined in the photon file.
  tree->Fill();

  
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

//-------------------------------//
//        Other utilities        //
//-------------------------------//
void MiniAnalyzer::beginJob() {
  std::cout<<"Beginning job ..."<<endl;
}

void MiniAnalyzer::endJob() {
  std::cout<<"Job ran successfully."<<endl;
}

void MiniAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MiniAnalyzer);
