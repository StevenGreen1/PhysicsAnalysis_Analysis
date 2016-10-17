import os
import re
import sys
import random
import threading

from ILCDIRAC.Interfaces.API.DiracILC import  DiracILC
from ILCDIRAC.Interfaces.API.NewInterface.UserJob import *
from ILCDIRAC.Interfaces.API.NewInterface.Applications import *
from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient

from GridTools import *
from TemplateWriterTools import * 

### ----------------------------------------------------------------------------------------------------
### Start of SubmitCLICJob function
### ----------------------------------------------------------------------------------------------------

def SubmitCLICJob(jobInfo):
    #########################
    # Unpack job information
    #########################
    eventType = jobInfo['eventType']
    energy = jobInfo['energy']
    detectorModel = jobInfo['detectorModel']
    reconstructionVariant = jobInfo['reconstructionVariant']
    clicFile = jobInfo['clicFile']
    analysisTag = jobInfo['analysisTag']
    jobDescription = jobInfo['jobDescription']
    prodID = jobInfo['prodID']
    idx = jobInfo['idx']
    numberOfFiles = jobInfo['numberOfFiles']
    gearFileLocal = jobInfo['gearFileLocal']
    diracInstance =  jobInfo['diracInstance']
    pandoraPFOsToUse = jobInfo['pandoraPFOsToUse']
    jetClusteringMode = jobInfo['jetClusteringMode']
    nJetsToCluster = jobInfo['nJetsToCluster']
    jetClusteringAlgorithm = jobInfo['jetClusteringAlgorithm']
    jetClusteringRadius = jobInfo['jetClusteringRadius']
    jetAlgorithmConfigString = pandoraPFOsToUse + '_' + jetClusteringAlgorithm + '_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    flavourTaggingWeights = ''
    rootFileSuffix = ''

    if pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.50':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p50.tar.gz' 
        rootFileSuffix = 'SPFOs_kt_0p50.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'SPFOs_kt_0p70.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.90':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p90.tar.gz'
        rootFileSuffix = 'SPFOs_kt_0p90.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '1.00':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_1p00.tar.gz'
        rootFileSuffix = 'SPFOs_kt_1p00.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '1.10':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_1p10.tar.gz'
        rootFileSuffix = 'SPFOs_kt_1p10.root'

    elif pandoraPFOsToUse == 'TightSelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_TightPFOs_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'TPFOs_kt_0p70.root'

    elif pandoraPFOsToUse == 'LooseSelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_LoosePFOs_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'LPFOs_kt_0p70.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'cambridge_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_cambridge_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'SPFOs_cam_0p70.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'ee_kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_ee_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'SPFOs_ee_kt_0p70.root'
 

    clicFileNoPath = os.path.basename(clicFile) 
    inputSandbox = [
                       'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/MarlinAnalysisProcessor.tar.gz', 
                       'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/JetsToPFOProcessor.tar.gz', 
                       'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/vtxprob.tar.gz', 
                       flavourTaggingWeights
                   ]

    #########################
    # Modify Template
    #########################
    steeringTemplate = GetTemplate(jobInfo)

    outputPath = '/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV/AnalysisTag' + str(analysisTag)
    rootFileName = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Tag' + str(analysisTag) + '_' + str(idx+1) + '_Of_' + str(numberOfFiles) + rootFileSuffix

    outputFiles = []
    outputFiles.append(rootFileName)

    steeringTemplate = re.sub('InputSlcioFile',clicFileNoPath,steeringTemplate)
    steeringTemplate = re.sub('GearFile',gearFileLocal,steeringTemplate)
    steeringTemplate = re.sub('MaximumNumberOfEventsToRecord','-1',steeringTemplate)
    steeringTemplate = re.sub('AnalysisProcessorRootFile', rootFileName, steeringTemplate)

    #########################
    # Check output doesn't exist already
    #########################
    print 'Checking CLIC sample ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  CLIC file ' + clicFile + '.'
    skipJob = False
    for outputFile in outputFiles:
        lfn = '/ilc/user/s/sgreen' + outputPath + '/' + outputFile
        if doesFileExist(lfn):
            skipJob = True
    if skipJob:
        return
    print 'Submitting ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  CLIC file ' + clicFile + '.'  

    #########################
    # Write Template File
    #########################
    marlinSteeringFilename = 'MarlinSteering_' + str(idx+1) + '_' + eventType + '_' + jetAlgorithmConfigString + '.steer'
    with open(marlinSteeringFilename ,'w') as SteeringFile:
        SteeringFile.write(steeringTemplate)

    #########################
    # Setup Marlin Application
    #########################
    ma = Marlin()
    ma.setVersion('v01-16-02')
    ma.setSteeringFile(marlinSteeringFilename)
    ma.setGearFile(gearFileLocal)
    ma.setInputFile('lfn:' + clicFile)
    ma.setProcessorsToUse(['libMarlinFastJet.so', 'libJetsToPFOs.so', 'libLCFIPlus.so', 'libAnalysisProcessor.so', 'libMarlinReco.so'])

    #########################
    # Submit Job
    #########################
    jobDetailedName = jobDescription + '_' + eventType + '_' + str(energy) + 'GeV_Tag' + str(analysisTag) + '_ProdID_' + str(prodID) + '_Number_' + str(idx+1) + '_Of_' + str(numberOfFiles)
    job = UserJob()
    job.setJobGroup(jobDescription)
    job.setInputSandbox(inputSandbox) # Local files
    job.setOutputSandbox(['*.log','*.gear','*.mac','*.steer','*.xml'])
    job.setOutputData(outputFiles,OutputPath=outputPath) # On grid
    job.setName(jobDetailedName)
    job.setBannedSites(['LCG.IN2P3-CC.fr','LCG.IN2P3-IRES.fr','LCG.KEK.jp','OSG.PNNL.us','OSG.CIT.us','LCG.LAPP.fr','LCG.UKI-LT2-IC-HEP.uk','LCG.Tau.il','LCG.Weizmann.il','OSG.BNL.us','LCG.GRIF.fr','LCG.UKI-SOUTHGRID-RALPP.uk', 'LCG.RAL-LCG2.uk'])
    job.setCPUTime(21600) # 6 hour, should be excessive
    job.dontPromptMe()

    res = job.append(ma)
    if not res['OK']:
        print res['Message']
        exit()

    job.submit(diracInstance)
    os.system('rm ' + marlinSteeringFilename)
    print 'Job submitted to grid.'

### ----------------------------------------------------------------------------------------------------
### End of SubmitCLICJob function
### ----------------------------------------------------------------------------------------------------
### Start of CLICWorker function
### ----------------------------------------------------------------------------------------------------

def CLICWorker(threadingSemaphore, pool, jobInfo):
    with threadingSemaphore:
        name = threading.currentThread().getName()
        pool.makeActive(name)
        SubmitCLICJob(jobInfo)
        pool.makeInactive(name)

### ----------------------------------------------------------------------------------------------------
### End of CLICWorker function
### ----------------------------------------------------------------------------------------------------
### Start of SubmitJob function
### ----------------------------------------------------------------------------------------------------

def SubmitJob(jobInfo):
    #########################
    # Unpack job information
    #########################
    eventType = jobInfo['eventType']
    energy = jobInfo['energy']
    detectorModel = jobInfo['detectorModel']
    reconstructionVariant = jobInfo['reconstructionVariant']
    slcioFile = jobInfo['slcioFile']
    analysisTag = jobInfo['analysisTag']
    jobDescription = jobInfo['jobDescription']
    idx = jobInfo['idx']
    numberOfFiles = jobInfo['numberOfFiles']
    gearFileLocal = jobInfo['gearFileLocal']
    diracInstance =  jobInfo['diracInstance']
    slcioFormat = jobInfo['slcioFormat'] 

    pandoraPFOsToUse = jobInfo['pandoraPFOsToUse']
    jetClusteringMode = jobInfo['jetClusteringMode']
    nJetsToCluster = jobInfo['nJetsToCluster']
    jetClusteringAlgorithm = jobInfo['jetClusteringAlgorithm']
    jetClusteringRadius = jobInfo['jetClusteringRadius']
    jetAlgorithmConfigString = pandoraPFOsToUse + '_' + jetClusteringAlgorithm + '_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    flavourTaggingWeights = ''
    rootFileSuffix = ''

    if pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.50':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p50.tar.gz'
        rootFileSuffix = 'SPFOs_kt_0p50.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'SPFOs_kt_0p70.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.90':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p90.tar.gz'
        rootFileSuffix = 'SPFOs_kt_0p90.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '1.00':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_1p00.tar.gz'
        rootFileSuffix = 'SPFOs_kt_1p00.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '1.10':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_1p10.tar.gz'
        rootFileSuffix = 'SPFOs_kt_1p10.root'

    elif pandoraPFOsToUse == 'TightSelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_TightPFOs_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'TPFOs_kt_0p70.root'

    elif pandoraPFOsToUse == 'LooseSelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_LoosePFOs_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'LPFOs_kt_0p70.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'cambridge_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_cambridge_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'SPFOs_cam_0p70.root'

    elif pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs' and (int)(energy) == 1400 and jetClusteringAlgorithm == 'ee_kt_algorithm' and (int)(nJetsToCluster) == 2 and str(format(jetClusteringRadius,'.2f')) == '0.70':
        flavourTaggingWeights = 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_ee_kt_algorithm_2jets_0p70.tar.gz'
        rootFileSuffix = 'SPFOs_ee_kt_0p70.root'

    slcioFileNoPath = os.path.basename(slcioFile)
    inputSandbox = [
                       'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/MarlinAnalysisProcessor.tar.gz',
                       'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/JetsToPFOProcessor.tar.gz',
                       'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/vtxprob.tar.gz',
                       flavourTaggingWeights
                   ]

    #########################
    # Get info from file name
    #########################
    matchObj = re.match(slcioFormat, os.path.basename(slcioFile), re.M|re.I)
    generatorSerialNumber = 0
    numberOfEventsInFile = 0
    startEventNumber = 0 # In generator level, not reconstruction.  Start event for all reconstruction is 0.

    if matchObj:
        generatorSerialNumber = matchObj.group(1)
        numberOfEventsInFile = matchObj.group(2)
        startEventNumber = matchObj.group(3)
    else:
        print 'Wrong slcio format.  Please check.'
        return 

    #########################
    # Modify Template
    #########################
    steeringTemplate = GetTemplate(jobInfo)

    outputPath = '/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '/' + str(energy) + 'GeV/AnalysisTag' + str(analysisTag)
    rootFileName = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenN_' + str(generatorSerialNumber) + '_' + str(numberOfEventsInFile) + '_' + str(startEventNumber) + '_Tag' + str(analysisTag) + rootFileSuffix

    outputFiles = []
    outputFiles.append(rootFileName)

    steeringTemplate = re.sub('InputSlcioFile',slcioFileNoPath,steeringTemplate)
    steeringTemplate = re.sub('GearFile',gearFileLocal,steeringTemplate)
    steeringTemplate = re.sub('MaximumNumberOfEventsToRecord','-1',steeringTemplate)
    steeringTemplate = re.sub('AnalysisProcessorRootFile', rootFileName, steeringTemplate)

    #########################
    # Check output doesn't exist already
    #########################
    print 'Checking ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  SLCIO file ' + slcioFile + '.'
    skipJob = False
    for outputFile in outputFiles:
        lfn = '/ilc/user/s/sgreen' + outputPath + '/' + outputFile
        if doesFileExist(lfn):
            skipJob = True
    if skipJob:
        return
    print 'Submitting ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  SLCIO file ' + slcioFile + '.'

    #########################
    # Write Template File
    #########################
    marlinSteeringFilename = 'MarlinSteering_' + str(idx+1) + '_' + eventType + '_' + jetAlgorithmConfigString + '.steer'
    with open(marlinSteeringFilename ,'w') as SteeringFile:
        SteeringFile.write(steeringTemplate)

    #########################
    # Setup Marlin Application
    #########################
    ma = Marlin()
    ma.setVersion('v01-16-02')
    ma.setSteeringFile(marlinSteeringFilename)
    ma.setGearFile(gearFileLocal)
    ma.setInputFile('lfn:' + slcioFile)
    ma.setProcessorsToUse(['libMarlinFastJet.so', 'libJetsToPFOs.so', 'libLCFIPlus.so', 'libAnalysisProcessor.so', 'libMarlinReco.so'])

    #########################
    # Submit Job
    #########################
    jobDetailedName = jobDescription + '_DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenNumber_' + str(generatorSerialNumber) + '_' +  str(numberOfEventsInFile) + '_' + str(startEventNumber)
    job = UserJob()
    job.setJobGroup(jobDescription)
    job.setInputSandbox(inputSandbox) # Local files
    job.setOutputSandbox(['*.log','*.gear','*.mac','*.steer','*.xml'])
    job.setOutputData(outputFiles,OutputPath=outputPath) # On grid
    job.setName(jobDetailedName)
    job.setBannedSites(['LCG.IN2P3-CC.fr','LCG.IN2P3-IRES.fr','LCG.KEK.jp','OSG.PNNL.us','OSG.CIT.us','LCG.LAPP.fr','LCG.UKI-LT2-IC-HEP.uk','LCG.Tau.il','LCG.Weizmann.il','OSG.BNL.us','LCG.GRIF.fr','LCG.UKI-SOUTHGRID-RALPP.uk', 'LCG.RAL-LCG2.uk'])
    job.setCPUTime(21600) # 6 hour, should be excessive
    job.dontPromptMe()

    res = job.append(ma)
    if not res['OK']:
        print res['Message']
        exit()

    job.submit(diracInstance)
    os.system('rm ' + marlinSteeringFilename)
    print 'Job submitted to grid.'

### ----------------------------------------------------------------------------------------------------
### End of SubmitJob function
### ----------------------------------------------------------------------------------------------------
### Start of Worker function
### ----------------------------------------------------------------------------------------------------

def Worker(threadingSemaphore, pool, jobInfo):
    with threadingSemaphore:
        name = threading.currentThread().getName()
        pool.makeActive(name)
        SubmitJob(jobInfo)
        pool.makeInactive(name)

### ----------------------------------------------------------------------------------------------------
### End of Worker function
### ----------------------------------------------------------------------------------------------------
### Start of ActivePool function
### ----------------------------------------------------------------------------------------------------

class ActivePool(object):
    def __init__(self):
        super(ActivePool, self).__init__()
        self.active = []
        self.lock = threading.Lock()
    def makeActive(self, name):
        with self.lock:
            self.active.append(name)
    def makeInactive(self, name):
        with self.lock:
            self.active.remove(name)

### ----------------------------------------------------------------------------------------------------
### End of ActivePool function
### ----------------------------------------------------------------------------------------------------


