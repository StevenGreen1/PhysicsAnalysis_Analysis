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

eventsToSimulate = [
#                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 5527, 'NumberOfEvents': 335300 },  
                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 5594, 'NumberOfEvents': 715200 },
                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 5572, 'NumberOfEvents': 1101100 },
                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 4034, 'NumberOfEvents': 591800 },
                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3243, 'NumberOfEvents': 577200 },
                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3249, 'NumberOfEvents': 2043200 },
                       { 'EventType': 'ee_qqll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3246, 'NumberOfEvents': 2104400 },
                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2091, 'NumberOfEvents': 459000 },
                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3366, 'NumberOfEvents': 129100 },
                       { 'EventType': 'egamma_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3369, 'NumberOfEvents': 126300 },
                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3372, 'NumberOfEvents': 137400 },
                       { 'EventType': 'gammae_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3375, 'NumberOfEvents': 120200 },
                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3378, 'NumberOfEvents': 180100 },
                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3381, 'NumberOfEvents': 175000 },
                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3384, 'NumberOfEvents': 177800 },
                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3387, 'NumberOfEvents': 173800 },
                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3414, 'NumberOfEvents': 167300 },
                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3417, 'NumberOfEvents': 167900 },
                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3420, 'NumberOfEvents': 170700 },
                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 3423, 'NumberOfEvents': 159800 }
                   ]

#===== Second level user input =====

gearFile = 'TemplateSteering/clic_ild_cdr.gear'
steeringTemplateFile = 'TemplateSteering/AnalysisTemplate_Tag4.xml'

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
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    energy = eventSelection['Energy']

    # Make local gear file
    os.system('cp ' + gearFile + ' .')
    gearFileLocal = os.path.basename(gearFile)

    diracInstance = DiracILC(withRepo=False)

    clicFiles = []
    clicFiles = getCLICFiles(prodID)
    clicFiles = orderedList(clicFiles)

    if not clicFiles:
        print 'No clic files with production ID ' + str(prodID) + ' found.  Exiting job submission.'
        continue

    numberOfFiles = len(clicFiles)

    for idx, clicFile in enumerate(clicFiles):
        print 'Checking CLIC sample ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  Slcio file ' + clicFile + '.'
        clicFileNoPath = os.path.basename(clicFile) 
        inputSandbox = ['LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/MarlinAnalysisProcessor.tar.gz', 'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/JetsToPFOProcessor.tar.gz', 'LFN:/ilc/user/s/sgreen/AnalysisProcessorTarBall/vtxprob.tar.gz', 'LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p70.tar.gz','LFN:/ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_1p00.tar.gz']

        #########################
        # Modify Template
        #########################
        steeringTemplate = steeringTemplateContent

        outputPath = '/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV'
        rootFileName = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Tag' + str(analysisTag) + '_' + str(idx+1) + '_Of_' + str(numberOfFiles)
        rootFileNameSelectedPFOs_kt_1p0 = rootFileName + '_SPFOs_kt_2jets_1p00.root'
        rootFileNameSelectedPFOs_kt_0p7 = rootFileName + '_SPFOs_kt_2jets_0p70.root'

        outputFiles = []
        outputFiles.append(rootFileNameSelectedPFOs_kt_1p0)
        outputFiles.append(rootFileNameSelectedPFOs_kt_0p7)

        steeringTemplate = re.sub('InputSlcioFile',clicFileNoPath,steeringTemplate)
        steeringTemplate = re.sub('GearFile',gearFileLocal,steeringTemplate)
        steeringTemplate = re.sub('MaximumNumberOfEventsToRecord','2',steeringTemplate)
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
        ma.setVersion('v01-16-02')
        ma.setSteeringFile('MarlinSteering.steer')
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
        job.setBannedSites(['LCG.IN2P3-CC.fr','LCG.IN2P3-IRES.fr','LCG.KEK.jp','OSG.PNNL.us','OSG.CIT.us','LCG.LAPP.fr','LCG.UKI-LT2-IC-HEP.uk','LCG.Tau.il','LCG.Weizmann.il','OSG.BNL.us','LCG.GRIF.fr'])
        job.setCPUTime(21600) # 6 hour, should be excessive
        job.dontPromptMe()

        res = job.append(ma)

        if not res['OK']:
            print res['Message']
            exit()
        job.submit(diracInstance)
        sys.exit()

# Tidy Up
os.system('rm MarlinSteering.steer')
os.system('rm ' + gearFileLocal)
