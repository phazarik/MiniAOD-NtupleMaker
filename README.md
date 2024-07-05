# MiniAOD-NtupleMaker

This is a tool designed for creating custom Ntuples from CMS MiniAOD data structure, facilitating detailed analysis and research in particle physics. This can also be modified to work with the AOD format, by feeding the right tokens to the configuration file. The repository is structured as follows:

- **C++ based source code and plugins**
--  `MiniAnalyzer.cc`: This is the main source file where I have used the analyzer class to handle the initialization, event processing, and finalization of the analysis. It imports features from the other plugins, such as `writeBranches_photons.cc` , which are targeted to do specific tasks in an event.
-- `MiniAnalyzer.h`: This is the header file that has declarations of the analyzer class, the global variables and functions used in the different modules, including the main one. 

- **Python based configuration**
--  `ConfFile_cfg.py`: This configuration script is run using `cmsRun` locally. (*not using python !*) It is used to set values the global variables (like input, output and other parameters), which are declared in the header file.
-- `crab_submit.py`: It uses the configuration script to submit CRAB jobs. [work needed.]

## Requirements
- Access to a CERN computing account and lxplus.
- A ROOT framework based on CMS software. `CMSSW_13_0_13` has been used while developing this setup in an `lxplus9` machine, but this is simple enough to work with a variety of versions. 
- Access to the CMS Data Aquisition System (DAS) to pick the necessary input files compatible with the CMSSW version you are working with

## Installation and test-run
To set up MiniAOD-NtupleMaker, follow these steps: 
1. Initialize the required CMSSW Environment in lxplus. 
```
cmsrel CMSSW_13_0_13
cd CMSSW_13_0_13/src
cmsenv
```
2. Clone the repository as FlatNtupleMaker (this name is important).
```
git clone git@github.com:phazarik/MiniAOD-NtupleMaker.git FlatNtupleMaker
```
3. Compile the setup using `scram`. This has to be done every-time there is a change in the source code. This step may take a while.
```
cd FlatNtupleMaker
scram b -j8
```
4. Run a local test to see whether the setup is working or not. Pick an input file which is compatible with the CMSSW version and put its path in the `python/Config_cfg.py` file. This is done in the `process.source` section.  Make sure that the file is accessible. In case the file is directly accessed from DAS, run the `set_environment.sh` script to set up a voms-proxy. Then run the configuration file as follows.
```
cmsRun Config_cfg.py
```

## Submitting crab jobs
[work needed]

---
Feel free to further customize or expand sections as per your specific project needs. Let me know if there's anything else you'd like to adjust!