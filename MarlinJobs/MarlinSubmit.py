# Example to submit Marlin job
import os
import re
import sys
import random
import time

from ILCDIRAC.Interfaces.API.DiracILC import  DiracILC
from ILCDIRAC.Interfaces.API.NewInterface.UserJob import *
from ILCDIRAC.Interfaces.API.NewInterface.Applications import *
from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient

from Logic.GridTools import *
from Logic.ThreadedTools import *

#===== User Input =====

jobDescription = 'PhysicsAnalysis'

# Always define event type, events per file and energies in same way.  If not CLIC sample set ProdID to 0

eventsToSimulate = [
#                       { 'EventType': 'ee_nunuqqqq', 'Energy': 1400, 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 12 }
                       { 'EventType': 'ee_nunuqqqq', 'Energy': 3000, 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 12 }
                   ]

jetRecoConfigToSimulate = [
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 },
                              { 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                              { 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.0 }
                           ]

#===== Second level user input =====

gearFile = 'TemplateSteering/clic_ild_cdr.gear'
maxThread = 100

# Make local gear file
os.system('cp ' + gearFile + ' .')
gearFileLocal = os.path.basename(gearFile)

##############
# Begin
##############

pool = ActivePool()
threadingSemaphore = threading.Semaphore(maxThread)

for eventSelection in eventsToSimulate:
    eventType = eventSelection['EventType']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    energy = eventSelection['Energy']
    analysisTag = eventSelection['AnalysisTag']

    for jetRecoConfigSelection in jetRecoConfigToSimulate:
        pandoraPFOsToUse = jetRecoConfigSelection['PandoraPFOsToUse']
        jetClusteringMode = jetRecoConfigSelection['JetClusteringMode']
        nJetsToCluster = jetRecoConfigSelection['NJetsToCluster']
        jetClusteringAlgorithm = jetRecoConfigSelection['JetClusteringAlgorithm']
        jetClusteringRadius = jetRecoConfigSelection['JetClusteringRadius']

        diracInstance = DiracILC(withRepo=False)

        slcioFormat = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenNumber_(.*?)_(.*?)_(.*?)_DST.slcio'
        slcioFiles = getDstSlcioFiles(jobDescription,detectorModel,reconstructionVariant,energy,eventType)

        if not slcioFiles:
            print 'No slcio files found.  Exiting job submission.'
            sys.exit()

        numberOfFiles = len(slcioFiles)

        for idx, slcioFile in enumerate(slcioFiles):
            while threading.activeCount() > (maxThread * 2):
                time.sleep(5)

            jobInfo = {}
            jobInfo['eventType'] = eventType
            jobInfo['energy'] = energy
            jobInfo['detectorModel'] = detectorModel
            jobInfo['reconstructionVariant'] = reconstructionVariant
            jobInfo['slcioFile'] = slcioFile
            jobInfo['analysisTag'] = analysisTag
            jobInfo['jobDescription'] = jobDescription
            jobInfo['numberOfFiles'] = numberOfFiles
            jobInfo['gearFileLocal'] = gearFileLocal
            jobInfo['diracInstance'] = diracInstance
            jobInfo['slcioFormat'] = slcioFormat
            jobInfo['idx'] = idx
            jobInfo['pandoraPFOsToUse'] = pandoraPFOsToUse
            jobInfo['jetClusteringMode'] = jetClusteringMode
            jobInfo['nJetsToCluster'] = nJetsToCluster
            jobInfo['jetClusteringAlgorithm'] = jetClusteringAlgorithm
            jobInfo['jetClusteringRadius'] = jetClusteringRadius

            downloadThread = threading.Thread(target=Worker, name=str(slcioFile), args=(threadingSemaphore, pool, jobInfo))
            downloadThread.start()

currentThread = threading.currentThread()
for thread in threading.enumerate():
    if thread is currentThread:
        continue
    thread.join(60)

# Tidy Up
os.system('rm ' + gearFileLocal)
