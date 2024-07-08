//-----------------------------------------------//
// Header file containing the analyzer class.    //
// Call all the other header files here.         //
// Don't call them again in the main source file.//
//                                  - Prachurjya //
//-----------------------------------------------//

#ifndef MINIANALYZER_H
#define MINIANALYZER_H

//Default headers from the template:
#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

//Custom headers for this setup:
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

//General ROOT/C++ headers:
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"
#include <cmath>
#include "TVector3.h"
#include "TLorentzVector.h"
#include "iterator"

using reco::TrackCollection;
using namespace std;
using namespace edm;

class MiniAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit MiniAnalyzer(const edm::ParameterSet&);
  ~MiniAnalyzer() override;
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  //Declaring global variables here:
  TTree *tree; 
  bool runOnParticleGun_;
  bool runOnSherpa_;
  bool doGenParticles_;
  
private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;
  
  //Declare all the functions from the other modules here.
  void createBranches_photons(TTree *);
  void fillBranches_photons(const edm::Event&, const edm::EventSetup&);
  
  // ----------member data ---------------------------
  // Note: all the token variables end with an underscore (e.g. *Token_ or *Collection_).
  edm::EDGetTokenT<TrackCollection>            tracksToken_;
  edm::EDGetTokenT<reco::VertexCollection>     vtxToken_;
  edm::EDGetTokenT<vector<reco::GenParticle> > genParticlesCollection_;
  edm::EDGetTokenT<edm::View<pat::Photon> >    photonCollection_;

  
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};

#endif // MINIANALYZER_H
