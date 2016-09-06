# Example to submit Marlin job
import os
import re
import sys
import random

from ILCDIRAC.Interfaces.API.DiracILC import  DiracILC
from ILCDIRAC.Interfaces.API.NewInterface.UserJob import *
from ILCDIRAC.Interfaces.API.NewInterface.Applications import *
from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient

from Logic.GridTools import *

#===== User Input =====

jobDescription = 'PhysicsAnalysis'

# Always define event type, events per file and energies in same way.  If not CLIC sample set ProdID to 0

eventsToSimulate = [
                       { 'EventType': "ee_nunuqqqq"         , 'Energy': 1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4 }
                   ]

#===== Second level user input =====

gearFile = 'TemplateSteering/clic_ild_cdr.gear'
steeringTemplateFile = 'TemplateSteering/AnalysisTemplate.xml'

##############
# Begin
##############

# Get content of template 
base = open(steeringTemplateFile,'r')
steeringTemplateContent = base.read()
base.close()

for eventSelection in eventsToSimulate:
    eventType = eventSelection['EventType']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    energy = eventSelection['Energy']
    analysisTag = eventSelection['AnalysisTag']

    # Make local gear file
    os.system('cp ' + gearFile + ' .')
    gearFileLocal = os.path.basename(gearFile)

    diracInstance = DiracILC(withRepo=False)

    slcioFormat = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenNumber_(.*?)_(.*?)_(.*?)_DST.slcio'
    slcioFilesToProcess = getDstSlcioFiles(jobDescription,detectorModel,reconstructionVariant,energy,eventType)

    if not slcioFilesToProcess:
        print 'No slcio files found.  Exiting job submission.'
        sys.exit()

    for slcioFile in slcioFilesToProcess:
        print 'Checking ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  Slcio file ' + slcioFile + '.'
        slcioFileNoPath = os.path.basename(slcioFile)
        inputSandbox = ['LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/MarlinAnalysisProcessor.tar.gz', 'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/JetsToPFOProcessor.tar.gz', 'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/vtxprob.tar.gz']

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
            continue

        #########################
        # Modify Template
        #########################
        steeringTemplate = steeringTemplateContent

        outputPath = '/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '/' + str(energy) + 'GeV'
        rootFileName = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenNumber_' + str(generatorSerialNumber) + '_' + str(numberOfEventsInFile) + '_' + str(startEventNumber) + '_Analysis_' + str(analysisTag)
        rootFileNameSelectedPFOs_kt_1p0 = rootFileName + '_SelectedPFOs_kt_1p0.root'
        rootFileNameSelectedPFOs_kt_0p7 = rootFileName + '_SelectedPFOs_kt_0p7.root'

        outputFiles = []
        outputFiles.append(rootFileNameSelectedPFOs_kt_1p0)
        outputFiles.append(rootFileNameSelectedPFOs_kt_0p7)

        steeringTemplate = re.sub('InputSlcioFile',clicFileNoPath,steeringTemplate)
        steeringTemplate = re.sub('GearFile',gearFileLocal,steeringTemplate)
        steeringTemplate = re.sub('AnalysisProcessorRootFile_SelectedPFOs_kt_1p0',rootFileNameSelectedPFOs_kt_1p0,steeringTemplate)
        steeringTemplate = re.sub('AnalysisProcessorRootFile_SelectedPFOs_kt_0p7',rootFileNameSelectedPFOs_kt_0p7,steeringTemplate)

        #########################
        # Write Template File
        #########################
        with open('MarlinSteering.steer' ,'w') as SteeringFile:
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
        ma.setVersion('ILCSoft-01-17-08_gcc48')
        ma.setSteeringFile('MarlinSteering.steer')
        ma.setGearFile(gearFileLocal)
        ma.setInputFile('lfn:' + slcioFile)
        ma.setProcessorsToUse(['libMarlinFastJet.so', 'libJetsToPFOs.so', 'libLCFIPlus.so', 'libAnalysisProcessor.so'])

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
        job.setBannedSites(['LCG.IN2P3-CC.fr','LCG.IN2P3-IRES.fr','LCG.KEK.jp','OSG.PNNL.us','OSG.CIT.us','LCG.LAPP.fr','LCG.UKI-LT2-IC-HEP.uk','LCG.Tau.il','LCG.Weizmann.il','OSG.BNL.us'])
        job.setCPUTime(21600) # 6 hour, should be excessive
        job.dontPromptMe()

        res = job.append(ma)

        if not res['OK']:
            print res['Message']
            exit()
        job.submit(diracInstance)
        #sys.exit()

# Tidy Up
os.system('rm MarlinSteering.steer')
os.system('rm ' + gearFileLocal)
