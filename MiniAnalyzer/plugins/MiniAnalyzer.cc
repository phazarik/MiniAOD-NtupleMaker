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

// ----------------------------------------------------------------//
// Changes made from the EDAnalyzer template:                      //
// The analyzer class is declared in the header file, so that      //
// it is visible to all the additional plugins during compilation. //
// Additional features of the class are defined here.              //
// ----------------------------------------------------------------//

//Constructor for setting up the tokens and the global variables:
MiniAnalyzer::MiniAnalyzer(const edm::ParameterSet& iConfig){
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  
  // Extracting parameters from the config file and setting the tokens:
  vtxToken_ = consumes<reco::VertexCollection>(iConfig.getParameter<InputTag>("vtxSrc"));
  photonCollection_ = consumes<edm::View<pat::Photon>>(iConfig.getParameter<edm::InputTag>("photonSrc"));
  genParticlesCollection_ = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticleSrc"));

  //-------------------------------------------------------------------------------------------------
  // NOTE:
  // Alternative way to access the collections:
  // Define a egm::Handle object as follows:
  // edm::Handle<reco::VertexCollection> vtxHandle; iEvent.getByToken(vtxCollection_, vtxHandle);
  // Where, vtxHandle is the output of cosumes<>().
  // I like using the handle in the analyze function directly, for looping over an object collection.
  //-------------------------------------------------------------------------------------------------
  
  //Creating the tree:
  edm::Service<TFileService> fs;
  //tree = fs->make<TTree>("Events", "EventInfo");
  TFile &rootFile = fs->file();
  tree = new TTree("Events", "EventInfo"); //This makes sure that fs does not create any nested folder in the root file
  rootFile.cd();
  tree->SetDirectory(&rootFile);

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

  // Put flags for rejecting bad events here.

  // Setting proper vertex:
  // P.S. Not needed, unless you want to work with vertices.
  // This is just an example to show how objects are accessed from the input files.
  edm::Handle<reco::VertexCollection> vtxHandle;
  iEvent.getByToken(vtxToken_, vtxHandle);
  reco::Vertex vtx; //Set vertex
  math::XYZPoint pv(0, 0, 0); //reference for the vertex
  for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {
    // replace isFake() for miniAOD since it requires tracks while miniAOD vertices don't have tracks:
    // Vertex.h: bool isFake() const {return (chi2_==0 && ndof_==0 && tracks_.empty());}
    bool isFake = (v->chi2() == 0 && v->ndof() == 0);
    if (!isFake) {
      pv.SetXYZ(v->x(), v->y(), v->z());
      vtx = *v;
      break;
    }
  }
  
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
  // This happens before the declaration of the class.
  // That's why you can't declare/initialize trees/histograms here. 
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

  //Template instructions:
  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MiniAnalyzer);
