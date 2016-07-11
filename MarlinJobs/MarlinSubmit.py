# Example to submit Marlin job
import os
import re
import sys
import random

from DIRAC.Core.Base import Script
Script.parseCommandLine()
from ILCDIRAC.Interfaces.API.DiracILC import  DiracILC
from ILCDIRAC.Interfaces.API.NewInterface.UserJob import *
from ILCDIRAC.Interfaces.API.NewInterface.Applications import *

from Logic.GridTools import *

#===== User Input =====

jobDescription = 'PhysicsAnalysis'

# Always define event type, events per file and energies in same way.  If not CLIC sample set ProdID to 0

eventsToSimulate = [
                       { 'EventType': "ee_nunuww_nunuqqqq"  , 'EventsPerFile' : 1000 , 'Energies':  ['1400'] },
                       { 'EventType': "ee_nunuzz_nunuqqqq"  , 'EventsPerFile' : 1000 , 'Energies':  ['1400'] }
                   ]

#===== Second level user input =====

detectorModel = 'clic_ild_cdr'
reconstructionVariant = 'clic_ild_cdr'
analysisTag = 1

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
diracInstance = DiracILC(withRepo=True,repoLocation="%s.cfg" %( JobIdentificationString))

for eventSelection in eventsToSimulate:
    eventType = eventSelection['EventType']
    for energy in eventSelection['Energies']:
        slcioFormat = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenNumber_(.*?)_(.*?)_(.*?)_REC.slcio'
        slcioFilesToProcess = getRecSlcioFiles(jobDescription,detectorModel,reconstructionVariant,energy,eventType)

        if not slcioFilesToProcess:
            print 'No slcio files found.  Exiting job submission.'
            sys.exit()

        for slcioFile in slcioFilesToProcess:
            print 'Checking ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  Slcio file ' + slcioFile + '.'
            slcioFileNoPath = os.path.basename(slcioFile)

            inputSandbox = ['LFN:/ilc/user/s/sgreen/SelectionProcessorTarBall/MarlinSelectionProcessor.tar.gz']

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
            with open("MarlinSteering.steer" ,"w") as SteeringFile:
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

            print 'Submitting ' + eventType + ' ' + str(energy) + 'GeV jobs.  Detector model ' + detectorModel + '.  Reconstruction stage ' + reconstructionVariant + '.  Slcio file ' + slcioFile + '.'  

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
            jobDetailedName = jobDescription + '_DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenNumber_' + str(generatorSerialNumber) + '_' +  str(numberOfEventsInFile) + '_' + str(startEventNumber)

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
