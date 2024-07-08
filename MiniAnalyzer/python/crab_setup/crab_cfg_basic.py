######################################################
# This is a trivial crab submission file which       #
# submits jobs for only one dataset at a time.       #
# It takes the workarea, dataset, input and  output  #
# locations as arguments. Run the crab_driver script #
# for submitting a larger number of jobs.            #
######################################################

#Setting up the job
from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
#config.General.requestName = 'name' #Taken from external
#config.General.workArea = 'blah' #Taken from external

config.section_('JobType')
config.JobType.psetName = '/afs/cern.ch/user/p/phazarik/work/EGamma/dnn_photon_ID/CMSSW_13_0_13/src/FlatNtupleMaker/MiniAnalyzer/python/ConfFile_cfg.py'
config.JobType.pluginName = 'Analysis'
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.publication = False
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob   = 1
config.Data.allowNonValidInputDataset = True
#config.Data.outLFNDirBase = 'dir name' #Taken from outside
#config.Data.inputDataset = 'das name' #Taken from outside

config.section_('Site')
config.Site.storageSite = 'T3_CH_CERNBOX'
