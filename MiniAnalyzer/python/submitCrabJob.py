from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import config
from copy import deepcopy
import os
 
def submit(config):
    res = crabCommand('submit', config = config)
    #save crab config for the future
    with open(config.General.workArea + "/crab_" + config.General.requestName + "/crab_config.py", "w") as fi:
        fi.write(config.pythonise_())
        
# In the following list, give the sample names as a tuple in the form (DAS_String, samplename_string)
# Make sure that the samples are compatible with the CMSSW release.
samples = [    
    ('/GJet_PT-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM', 'GJet_PT-10to40')
]

if __name__ == "__main__":
    for dataset, name in samples:

        conf = config()
        submitVersion = "ntuple_PFID_Run3Summer23_test" #general jobname
        mainOutputDir = '/store/group/phys_egamma/phazarik/%s' % submitVersion #storage location

        conf.General.workArea = 'crab_%s' % submitVersion
        conf.General.transferOutputs = True
        conf.JobType.pluginName  = 'Analysis'

        # Name of the CMSSW confuration file
        conf.JobType.psetName  = '/afs/cern.ch/user/p/phazarik/work/EGamma/dnn_photon_ID/CMSSW_13_0_13/src/FlatNtupleMaker/MiniAnalyzer/python/ConfFile_cfg.py'
        conf.JobType.allowUndistributedCMSSW = True
        conf.Data.allowNonValidInputDataset = True
        
        conf.Data.inputDBS = 'global'
        conf.Data.publication = False
        
        #conf.Data.publishDataName =
        conf.Site.storageSite = 'T2_CH_CERN'
        
        conf.Data.outLFNDirBase = '%s/%s/' % (mainOutputDir,'mc')
        conf.Data.splitting     = 'FileBased'
        conf.Data.unitsPerJob   = 20
        conf.Data.allowNonValidInputDataset = True
        
        conf.General.requestName = name
        conf.Data.inputDataset = dataset
        
        submit(conf) 
