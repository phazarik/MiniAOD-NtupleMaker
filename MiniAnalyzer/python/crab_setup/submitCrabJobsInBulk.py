###########################################################
# This python script is used to submit crab-jobs in bulk, #
# as given in the list. Run it using python3.             #
###########################################################

import os,sys

os.system('bash set_environment.sh') #This will ask for the PEM password

#Global settings:
jobname = 'ntuple_PFID_Run3Summer23_Jul08_v0'
outdir = '/store/user/phazarik/EGM_photonID_crabdump/'
#List of samples
samples = [
    ('GJet_PT-10to40',    '/GJet_PT-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM'),
    ('GJet_PT-40',        '/GJet_PT-40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM'),
    ('QCD_PT-80to120',    '/QCD_PT-80to120_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM'),
    ('QCD_PT-120to170',   '/QCD_PT-120to170_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM'),
    ('QCD_PT-170to300',   '/QCD_PT-170to300_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM'),
    ('QCD_PT-300toInf',   '/QCD_PT-300toInf_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM'),
    ('TauGun_E-10to100',  '/TauGun_E-10to100_13p6TeV_pythia8/Run3Summer23BPixMiniAODv4-130X_mcRun3_2023_realistic_postBPix_v2-v2/MINIAODSIM'),
    ('TauGun_E-100to3000','/TauGun_E-100to3000_13p6TeV_pythia8/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2/MINIAODSIM')
]

for name, dataset in samples:
    requestname = jobname
    workarea    = 'crabjob_'+jobname+'_'+name
    outdir = outdir+'/'+jobname+'/'+name
    
    #Setting the arguments:
    argument1 = 'General.requestName='+requestname
    argument2 = 'General.workArea='   +workarea
    argument3 = 'Data.inputDataset='  +dataset
    argument4 = 'Data.outLFNDirBase=' +outdir

    #Main processline:
    processline = 'crab submit crab_cfg_basic.py '+argument1+' '+argument2+' '+argument3+' '+argument4
    print('\nprocessing ... '+processline)
    os.system(processline)
    print('Done!\n')
