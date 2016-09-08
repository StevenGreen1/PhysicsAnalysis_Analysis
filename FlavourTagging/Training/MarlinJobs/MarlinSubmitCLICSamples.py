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

jobDescription = 'PhysicsAnalysis_FlavourTagging'

eventsToSimulate = [
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 }
                   ]

#eventsToSimulate = [
#                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 5527, 'NumberOfEvents': 335300 },  
#                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 5594, 'NumberOfEvents': 715200 },
#                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 5572, 'NumberOfEvents': 1101100 },
#                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 4034, 'NumberOfEvents': 591800 },
#                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3243, 'NumberOfEvents': 577200 },
#                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3249, 'NumberOfEvents': 2043200 },
#                       { 'EventType': 'ee_ll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3246, 'NumberOfEvents': 2104400 },
#                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 2091, 'NumberOfEvents': 459000 },
#                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3366, 'NumberOfEvents': 129100 },
#                       { 'EventType': 'egamma_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3369, 'NumberOfEvents': 126300 },
#                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3372, 'NumberOfEvents': 137400 },
#                       { 'EventType': 'gammae_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3375, 'NumberOfEvents': 120200 },
#                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3378, 'NumberOfEvents': 180100 },
#                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3381, 'NumberOfEvents': 175000 },
#                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3384, 'NumberOfEvents': 177800 },
#                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3387, 'NumberOfEvents': 173800 },
#                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3414, 'NumberOfEvents': 167300 },
#                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3417, 'NumberOfEvents': 167900 },
#                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3420, 'NumberOfEvents': 170700 },
#                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3423, 'NumberOfEvents': 159800 }
#                   ]

#===== Second level user input =====

gearFile = 'TemplateSteering/clic_ild_cdr.gear'
steeringTemplateFile = 'TemplateSteering/FlavourTaggingTrainingTemplate.xml'
marlinVersion = 'v01-16-02'

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
    gearFile = 'TemplateSteering/' + detectorModel + '.gear'

    pandoraPFOsToUse = eventSelection['PandoraPFOsToUse']
    shortPandoraPFOsToUse = ''
    jetClusteringMode = eventSelection['JetClusteringMode']
    nJetsToCluster = eventSelection['NJetsToCluster']
    jetClusteringAlgorithm = eventSelection['JetClusteringAlgorithm']
    jetClusteringRadius = eventSelection['JetClusteringRadius']
    jetAlgorithmConfigString = jetClusteringAlgorithm + '_' + str(nJetsToCluster) + 'jets_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    if pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs':
        shortPandoraPFOsToUse = 'SelectedPFOs'
        jetAlgorithmConfigString = 'SelectedPFOs_' + jetAlgorithmConfigString
    elif pandoraPFOsToUse == 'TightSelectedPandoraPFANewPFOs':
        shortPandoraPFOsToUse = 'TightPFOs'
        jetAlgorithmConfigString = 'TightPFOs_' + jetAlgorithmConfigString
    elif pandoraPFOsToUse == 'LooseSelectedPandoraPFANewPFOs':
        shortPandoraPFOsToUse = 'LoosePFOs'
        jetAlgorithmConfigString = 'LoosePFOs_' + jetAlgorithmConfigString
    else:
        print 'Please select a set of PFOs from SelectedPandoraPFANewPFOs, TightSelectedPandoraPFANewPFOs or LooseSelectedPandoraPFANewPFOs.'
        exit()

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
#        steeringTemplate = re.sub('JetAlgorithmConfig',jetAlgorithmConfigString,steeringTemplate)

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
        ma.setVersion(marlinVersion)
        ma.setSteeringFile('MarlinSteering.steer')
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
#        job.setDestination('LCG.CERN.ch')

        res = job.append(ma)

        if not res['OK']:
            print res['Message']
            exit()
        job.submit(diracInstance)
#        sys.exit()

# Tidy Up
os.system('rm MarlinSteering.steer')
os.system('rm ' + gearFileLocal)
