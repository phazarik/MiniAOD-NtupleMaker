import FWCore.ParameterSet.Config as cms

process = cms.Process("FlatNtupleMaker")
process.load("FWCore.MessageService.MessageLogger_cfi")

#Loading additinoal modules:
process.load("FWCore.MessageService.MessageLogger_cfi") #For displaying reports
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '130X_mcRun3_2023_realistic_v14', '') #Run3Summer23

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(
                                #'file:/afs/cern.ch/cms/Tutorials/workbook_twiki2021/MinBias_pythia8_14TeV_100events.root'
                                'file:/eos/user/p/phazarik/EGM_photonID_samples/GJet_PT-10to40/016190b7-ea07-437f-83b8-c90272321e32.root'
                            )
                            )
#Output file: (closeFileFast makes sure that there is no subfolder nesting)
process.TFileService = cms.Service("TFileService", fileName = cms.string('egmNtuple.root'), closeFileFast = cms.untracked.bool(True))

#Setup the parameters of the class here:
process.flatNtupleMaker = cms.EDAnalyzer('MiniAnalyzer',
                                         tracks         = cms.untracked.InputTag('displacedTracks'), #Not using this parameter in the source code.
                                         vtxSrc         = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                         genParticleSrc = cms.InputTag("prunedGenParticles"),
                                         photonSrc      = cms.InputTag("slimmedPhotons")
                                         )

process.p = cms.Path(process.flatNtupleMaker)
