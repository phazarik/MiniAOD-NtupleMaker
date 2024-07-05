# MiniAOD-NtupleMaker

### Compiling the setup in a CMSSW environment
```
>cmsrel CMSSW_13_0_0
>cd CMSSW_13_0_0/src
>cmsenv
>git clone git@github.com:phazarik/MiniAOD-NtupleMaker.git FlatNtupleMaker
>cd FlatNtupleMaker
>scram b -j8
```
### Running local test
```
>. set_environment.sh
> cmsRun ConfFile_cfg.py
```

### Submitting crab jobs
<span style="color:red"> [Currently under development] </span>
### Code structure
<span style="color:red"> [Currently under development] </span>