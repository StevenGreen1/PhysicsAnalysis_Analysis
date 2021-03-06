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

eventsToSimulate = [
#                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 5527, 'NumberOfEvents': 335300 },  
                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 5594, 'NumberOfEvents': 715200 },
                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 5572, 'NumberOfEvents': 1101100 },
                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 4034, 'NumberOfEvents': 591800 },
                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3243, 'NumberOfEvents': 577200 },
                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3249, 'NumberOfEvents': 2043200 },
                       { 'EventType': 'ee_qqll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3246, 'NumberOfEvents': 2104400 },
                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 2091, 'NumberOfEvents': 459000 },
                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3366, 'NumberOfEvents': 129100 },
                       { 'EventType': 'egamma_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3369, 'NumberOfEvents': 126300 },
                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3372, 'NumberOfEvents': 137400 },
                       { 'EventType': 'gammae_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3375, 'NumberOfEvents': 120200 },
                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3378, 'NumberOfEvents': 180100 },
                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3381, 'NumberOfEvents': 175000 },
                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3384, 'NumberOfEvents': 177800 },
                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3387, 'NumberOfEvents': 173800 },
                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3414, 'NumberOfEvents': 167300 },
                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3417, 'NumberOfEvents': 167900 },
                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3420, 'NumberOfEvents': 170700 },
                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3423, 'NumberOfEvents': 159800 },
                       { 'EventType': 'ee_lnuqqqq', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6540, 'NumberOfEvents': 990000 },
                       { 'EventType': 'ee_llqqqq', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6754, 'NumberOfEvents': 728900 },
                       { 'EventType': 'ee_qqqq', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6776, 'NumberOfEvents': 3084200 },
                       { 'EventType': 'ee_nunuqq', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6583, 'NumberOfEvents': 575200 },
                       { 'EventType': 'ee_lnuqq', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6747, 'NumberOfEvents': 2115000 },
                       { 'EventType': 'ee_qqll', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 3048, 'NumberOfEvents': 482500 },
                       { 'EventType': 'ee_qq', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 4586, 'NumberOfEvents': 196400 },
                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6733, 'NumberOfEvents': 70300 },
                       { 'EventType': 'egamma_qqqqe_BS', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6736, 'NumberOfEvents': 111800 },
                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6739, 'NumberOfEvents': 70800 },
                       { 'EventType': 'gammae_qqqqe_BS', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6742, 'NumberOfEvents': 114100 },
                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6571, 'NumberOfEvents': 138900 },
                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6574, 'NumberOfEvents': 567000 },
                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6577, 'NumberOfEvents': 138000 },
                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6580, 'NumberOfEvents': 571600 },
                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6721, 'NumberOfEvents': 134700 },
                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6724, 'NumberOfEvents': 268100 },
                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6727, 'NumberOfEvents': 273300 },
                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy': 3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 14, 'ProdID': 6730, 'NumberOfEvents': 509800 }
                  ]

jetRecoConfigToSimulate = [
#                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },
                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
#                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },
#                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
#                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 },
#                              { 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
#                              { 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
#                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },
#                              { 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode':'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.0 }
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
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    energy = eventSelection['Energy']

    for jetRecoConfigSelection in jetRecoConfigToSimulate:
        pandoraPFOsToUse = jetRecoConfigSelection['PandoraPFOsToUse']
        jetClusteringMode = jetRecoConfigSelection['JetClusteringMode']
        nJetsToCluster = jetRecoConfigSelection['NJetsToCluster']
        jetClusteringAlgorithm = jetRecoConfigSelection['JetClusteringAlgorithm']
        jetClusteringRadius = jetRecoConfigSelection['JetClusteringRadius']

        diracInstance = DiracILC(withRepo=False)

        clicFiles = []
        clicFiles = getCLICFiles(prodID)
        clicFiles = orderedList(clicFiles)

        if not clicFiles:
            print 'No clic files with production ID ' + str(prodID) + ' found.  Exiting job submission.'
            continue

        numberOfFiles = len(clicFiles)

        for idx, clicFile in enumerate(clicFiles):
            while threading.activeCount() > (maxThread * 2):
                time.sleep(5)

            jobInfo = {}
            jobInfo['eventType'] = eventType
            jobInfo['energy'] = energy
            jobInfo['detectorModel'] = detectorModel
            jobInfo['reconstructionVariant'] = reconstructionVariant
            jobInfo['clicFile'] = clicFile
            jobInfo['analysisTag'] = analysisTag
            jobInfo['jobDescription'] = jobDescription
            jobInfo['prodID'] = prodID
            jobInfo['idx'] = idx
            jobInfo['numberOfFiles'] = numberOfFiles
            jobInfo['gearFileLocal'] = gearFileLocal
            jobInfo['diracInstance'] = diracInstance
            jobInfo['pandoraPFOsToUse'] = pandoraPFOsToUse
            jobInfo['jetClusteringMode'] = jetClusteringMode
            jobInfo['nJetsToCluster'] = nJetsToCluster
            jobInfo['jetClusteringAlgorithm'] = jetClusteringAlgorithm
            jobInfo['jetClusteringRadius'] = jetClusteringRadius

            downloadThread = threading.Thread(target=CLICWorker, name=str(clicFile), args=(threadingSemaphore, pool, jobInfo))
            downloadThread.start()

currentThread = threading.currentThread()
for thread in threading.enumerate():
    if thread is currentThread:
        continue
    thread.join(60)

# Tidy Up
os.system('rm ' + gearFileLocal)
