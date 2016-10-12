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
    steeringTemplateContent = jobInfo['steeringTemplateContent']
    prodID = jobInfo['prodID']
    idx = jobInfo['idx']
    numberOfFiles = jobInfo['numberOfFiles']
    gearFileLocal = jobInfo['gearFileLocal']
    diracInstance =  jobInfo['diracInstance']
    pandoraPFOsToUse = jobInfo['pandoraPFOsToUse']
    shortPandoraPFOsToUse = jobInfo['shortPandoraPFOsToUse']
    jetClusteringMode = jobInfo['jetClusteringMode']
    nJetsToCluster = jobInfo['nJetsToCluster']
    jetClusteringAlgorithm = jobInfo['jetClusteringAlgorithm']
    jetClusteringRadius = jobInfo['jetClusteringRadius']
    jetAlgorithmConfigString = jobInfo['jetAlgorithmConfigString']

    print 'Checking CLIC sample ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  Slcio file ' + clicFile + '.'
    clicFileNoPath = os.path.basename(clicFile)
    inputSandbox = ['LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/JetsToPFOProcessor.tar.gz', 'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/vtxprob.tar.gz']

    #########################
    # Modify Template
    #########################
    steeringTemplate = steeringTemplateContent

    outputPath = '/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV/' + jetAlgorithmConfigString
    rootFileName = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_Number_' + str(idx+1) + '_Of_' + str(numberOfFiles) + '.root'
    outputFiles = []
    outputFiles.append(rootFileName)

    steeringTemplate = re.sub('MakeNtupleRootFileName',rootFileName,steeringTemplate)
    steeringTemplate = re.sub('GearFile',gearFileLocal,steeringTemplate)
    steeringTemplate = re.sub('InputSlcioFile',clicFileNoPath,steeringTemplate)
    steeringTemplate = re.sub('PandoraPFOsToUse', pandoraPFOsToUse,steeringTemplate)
    steeringTemplate = re.sub('JetClusteringMode', jetClusteringMode,steeringTemplate)
    steeringTemplate = re.sub('NJetsToCluster', str(nJetsToCluster),steeringTemplate)
    steeringTemplate = re.sub('JetClusteringAlgorithm',jetClusteringAlgorithm,steeringTemplate)
    steeringTemplate = re.sub('JetClusteringRadius',  str(format(jetClusteringRadius,'.2f')),steeringTemplate)
#    steeringTemplate = re.sub('JetAlgorithmConfig',jetAlgorithmConfigString,steeringTemplate)

    #########################
    # Write Template File
    #########################
    marlinSteeringFilename = 'MarlinSteering_' + str(idx+1) + '_' + eventType + '_' + jetAlgorithmConfigString + '.steer'

    with open(marlinSteeringFilename ,'w') as SteeringFile:
        SteeringFile.write(steeringTemplate)

    #########################
    # Check output doesn't exist already
    #########################
    skipJob = False
    for outputFile in outputFiles:
        lfn = '/ilc/user/s/sgreen' + outputPath + '/' + outputFile
        if doesFileExist(lfn):
            skipJob = True

    if skipJob:
        continue

    print 'Submitting ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  CLIC file ' + clicFile + '.'

    #########################
    # Setup Marlin Application
    #########################
    ma = Marlin()
    ma.setVersion(marlinVersion)
    ma.setSteeringFile(marlinSteeringFilename)
    ma.setGearFile(gearFileLocal)
    ma.setInputFile('lfn:' + clicFile)
    ma.setProcessorsToUse(['libMarlinFastJet.so', 'libJetsToPFOs.so', 'libLCFIPlus.so'])

    #########################
    # Submit Job
    #########################
    jobDetailedName = jobDescription + '_' + eventType + '_' + str(energy) + 'GeV_Tag' + str(analysisTag) + '_ProdID_' + str(prodID) + '_Number_' + str(idx+1) + '_Of_' + str(numberOfFiles)

    job = UserJob()
    job.setJobGroup(jobDescription)
    job.setInputSandbox(inputSandbox) # Local files
    job.setOutputSandbox(['*.log','*.steer','*.xml'])
    job.setOutputData(outputFiles,OutputPath=outputPath) # On grid
    job.setName(jobDetailedName)
    job.setBannedSites(['LCG.IN2P3-CC.fr','LCG.IN2P3-IRES.fr','LCG.KEK.jp','OSG.PNNL.us','OSG.CIT.us','LCG.LAPP.fr','LCG.UKI-LT2-IC-HEP.uk','LCG.Tau.il','LCG.Weizmann.il','OSG.BNL.us'])
    job.setCPUTime(21600) # 6 hour, should be excessive
    job.dontPromptMe()
#    job.setDestination('LCG.CERN.ch')

    res = job.append(ma)

    if not res['OK']:
        print res['Message']
        exit()
    job.submit(diracInstance)

    # Tidy Up
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


