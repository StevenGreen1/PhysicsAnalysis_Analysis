# Example to submit Marlin job
import os
import re
import sys
import random

from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient
from ILCDIRAC.Interfaces.API.DiracILC import  DiracILC
from ILCDIRAC.Interfaces.API.NewInterface.UserJob import *
from ILCDIRAC.Interfaces.API.NewInterface.Applications import *

from Logic.GridTools import *

#===== User Input =====

jobDescription = 'PhysicsAnalysis'

eventsToSimulate = [
                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':2152, 'NumberOfEvents': 100000 },
                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':2169, 'NumberOfEvents': 200000 },
                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':2166, 'NumberOfEvents': 120000 },
                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':2163, 'NumberOfEvents': 500000 },
                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':2094, 'NumberOfEvents': 500000 },
                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3249, 'NumberOfEvents': 2000000 },
                       { 'EventType': 'ee_ll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3246, 'NumberOfEvents': 2000000 },
                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':2091, 'NumberOfEvents': 500000 }
                   ]

#===== Second level user input =====

gearFile = 'TemplateSteering/' + detectorModel + '.gear'
steeringTemplateFile = 'TemplateSteering/AnalysisTemplate.xml'

# If applying overlay set this to true and point to relevant steering file 
ggHadBackground = True

##############
# Begin
##############

if ggHadBackground:
    reconstructionVariant += '_ggHadBkg'

# Make local gear file
os.system('cp ' + gearFile + ' .')
gearFileLocal = os.path.basename(gearFile)

# Get content of template 
base = open(steeringTemplateFile,'r')
steeringTemplateContent = base.read()
base.close()

# Start submission
JobIdentificationString = jobDescription + '_Detector_Model_' + detectorModel + '_Reco_' + reconstructionVariant
diracInstance = DiracILC(withRepo=True,repoLocation='%s.cfg' %( JobIdentificationString))

for eventSelection in eventsToSimulate:
    eventType = eventSelection['EventType']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    energy = eventSelection['Energy']
    gearFile = 'TemplateSteering/' + detectorModel + '.gear'

    clicFiles = []
    clicFiles = getCLICFiles(prodID)

    if not slcioFilesToProcess:
        print 'No slcio files found.  Exiting job submission.'
        sys.exit()

    for clicFile in clicFiles:
        print 'Checking CLIC sample ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  Slcio file ' + slcioFile + '.'

        inputSandbox = ['LFN:/ilc/user/s/sgreen/SelectionProcessorTarBall/MarlinSelectionProcessor.tar.gz']

        #########################
        # Modify Template
        #########################
        steeringTemplate = steeringTemplateContent

        outputPath = '/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV'

        rootFileName = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag)

        rootFileNameSelected = rootFileName + '_Selected.root'
        rootFileNameTight = rootFileName + '_Tight.root'
        rootFileNameLoose = rootFileName + '_Loose.root'

        outputFiles = []
        outputFiles.append(rootFileNameSelected)
        outputFiles.append(rootFileNameTight)
        outputFiles.append(rootFileNameLoose)

        steeringTemplate = re.sub('SelectionProcessorRootFileSelected',rootFileNameSelected,steeringTemplate)
        steeringTemplate = re.sub('SelectionProcessorRootFileTight',rootFileNameTight,steeringTemplate)
        steeringTemplate = re.sub('SelectionProcessorRootFileLoose',rootFileNameLoose,steeringTemplate)
        steeringTemplate = re.sub('MCEnergy',str(energy),steeringTemplate)
        steeringTemplate = re.sub('GearFile',gearFileLocal,steeringTemplate)
        steeringTemplate = re.sub('InputSlcioFile',slcioFileNoPath,steeringTemplate)

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
        ma.setProcessorsToUse(['libSelectionProcessor.so','libMarlinFastJet.so'])

        #########################
        # Submit Job
        #########################
        jobDetailedName = jobDescription + '_DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_AnalysisTag' + str(analysisTag) + '_ProdID_' + str(prodID)

        job = UserJob()
        job.setJobGroup(jobDescription)
        job.setInputSandbox(inputSandbox) # Local files
        job.setOutputSandbox(['*.log','*.gear','*.mac','*.steer','*.xml'])
        job.setOutputData(outputFiles,OutputPath=outputPath) # On grid
        job.setName(jobDetailedName)
        job.setBannedSites(['LCG.IN2P3-CC.fr','LCG.IN2P3-IRES.fr','LCG.KEK.jp','OSG.PNNL.us','OSG.CIT.us','LCG.LAPP.fr'])
        job.dontPromptMe()

        res = job.append(ma)

        if not res['OK']:
            print res['Message']
            exit()
        job.submit(diracInstance)
        os.system('rm *.cfg')
        #sys.exit()

# Tidy Up
os.system('rm MarlinSteering.steer')
os.system('rm ' + gearFileLocal)
