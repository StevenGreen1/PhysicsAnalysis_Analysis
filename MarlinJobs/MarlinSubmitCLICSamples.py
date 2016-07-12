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
                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':5527, 'NumberOfEvents': 335300 },
                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':5594, 'NumberOfEvents': 715200 },
                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':5572, 'NumberOfEvents': 1101100 },
                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':4034, 'NumberOfEvents': 591800 },
                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3243, 'NumberOfEvents': 577200 },
                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3249, 'NumberOfEvents': 2043200 },
                       { 'EventType': 'ee_ll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3246, 'NumberOfEvents': 2104400 },
                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':2091, 'NumberOfEvents': 459000 }.

                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3366, 'NumberOfEvents': 129100 }.
                       { 'EventType': 'egamma_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3369, 'NumberOfEvents': 126300 }.
                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3372, 'NumberOfEvents': 137400 }.
                       { 'EventType': 'gammae_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3375, 'NumberOfEvents': 120200 }.

                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3378, 'NumberOfEvents': 180100 }.
                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3381, 'NumberOfEvents': 175000 }.
                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3384, 'NumberOfEvents': 177800 }.
                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3387, 'NumberOfEvents': 173800 }.

                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3414, 'NumberOfEvents': 167300 }.
                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3417, 'NumberOfEvents': 167900 }.
                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3420, 'NumberOfEvents': 170700 }.
                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID':3423, 'NumberOfEvents': 159800 }
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
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    energy = eventSelection['Energy']
    gearFile = 'TemplateSteering/' + detectorModel + '.gear'

    # Make local gear file
    os.system('cp ' + gearFile + ' .')
    gearFileLocal = os.path.basename(gearFile)

    JobIdentificationString = jobDescription + '_Detector_Model_' + detectorModel + '_Reco_' + reconstructionVariant
    diracInstance = DiracILC(withRepo=True,repoLocation='%s.cfg' %( JobIdentificationString))

    clicFiles = []
    clicFiles = getCLICFiles(prodID)

    if not clicFiles:
        print 'No clic files with production ID ' + str(prodID) + ' found.  Exiting job submission.'
        continue

    numberOfFiles = len(clicFiles)

    for idx, clicFile in enumerate(clicFiles):
        print 'Checking CLIC sample ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  Slcio file ' + clicFile + '.'
        clicFileNoPath = os.path.basename(clicFile) 
        inputSandbox = ['LFN:/ilc/user/s/sgreen/SelectionProcessorTarBall/MarlinSelectionProcessor.tar.gz']

        #########################
        # Modify Template
        #########################
        steeringTemplate = steeringTemplateContent

        outputPath = '/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV'

        rootFileName = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_Number_' + str(idx+1) + '_Of_' + str(numberOfFiles)

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
        steeringTemplate = re.sub('InputSlcioFile',clicFileNoPath,steeringTemplate)

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
        ma.setInputFile('lfn:' + clicFile)
        ma.setProcessorsToUse(['libSelectionProcessor.so','libMarlinFastJet.so'])

        #########################
        # Submit Job
        #########################
        jobDetailedName = jobDescription + '_DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_Tag' + str(analysisTag) + '_ProdID_' + str(prodID) + '_Number_' + str(idx+1) + '_Of_' + str(numberOfFiles)

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
