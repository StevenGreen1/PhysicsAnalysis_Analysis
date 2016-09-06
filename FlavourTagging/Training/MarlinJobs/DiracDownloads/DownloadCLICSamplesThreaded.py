import os
import re
import time
import threading

from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.DataManagementSystem.Client.DataManager import DataManager
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient
from DIRAC.Core.Utilities.ReturnValues import returnSingleResult

#=================================

jobDescription = 'PhysicsAnalysis_FlavourTagging'

eventsToSimulate = [
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 }
                   ]

#=================================

maxThread = 100

#=================================

def downloadFile(dm, lfn, localFolder):
    res = returnSingleResult(dm.getFile(lfn, localFolder))
    if not res or not res['OK']:
        print "Error with file %s"%lfn
        print res
    else:
        print "Downloaded %s"%lfn

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

def worker(threadingSemaphore, pool, dm, lfn, localFolder):
    with threadingSemaphore:
        name = threading.currentThread().getName()
        pool.makeActive(name)
        downloadFile(dm, lfn, localFolder)
        pool.makeInactive(name)

#=================================

fc = FileCatalogClient()
dm = DataManager()

pool = ActivePool()
threadingSemaphore = threading.Semaphore(maxThread)

for eventSelection in eventsToDownload:
    eventType = eventSelection['EventType']
    energy = eventSelection['Energy']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    numberOfEvent = eventSelection['NumberOfEvents']
    pandoraPFOsToUse = eventSelection['PandoraPFOsToUse']
    shortPandoraPFOsToUse = ''
    jetClusteringMode = eventSelection['JetClusteringMode']
    nJetsToCluster = eventSelection['NJetsToCluster']
    jetClusteringAlgorithm = eventSelection['JetClusteringAlgorithm']
    jetClusteringRadius = eventSelection['JetClusteringRadius']
    jetAlgorithmConfigString = jetClusteringAlgorithm + '_' + str(nJetsToCluster) + 'jets_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')


    gridPath = '/ilc/user/s/sgreen/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV/' + jetAlgorithmConfigString
    localPath = '/r06/lc/sg568/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV/' + jetAlgorithmConfigString 

    print 'Downloading from : ' + gridPath
    if not os.path.exists(localPath):
        os.makedirs(localPath)

    meta = {}
    meta['Owner'] = 'sgreen'

    res = fc.findFilesByMetadata(meta, gridPath)
    if not res['OK']:
        print res['Message']

    lfns = res['Value']
    for lfn in lfns:
        print 'Checking file : ' + lfn
        localFile = os.path.basename(lfn)

        if 'ProdID' not in lfn:
            continue

        fileFormat = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_Number_(\d+)_Of_(\d+).root'
        matchObj = re.match(fileFormat, localFile, re.M|re.I)
        if not matchObj:
            continue

        if not os.path.isfile(localFile):
            print 'Downloading : ' + lfn
            while threading.activeCount() > (maxThread * 2):
                time.sleep(5)

            downloadThread = threading.Thread(target=worker, name=str(localFile), args=(threadingSemaphore, pool, dm, lfn, localPath))
            downloadThread.start()

currentThread = threading.currentThread()

for thread in threading.enumerate():
    if thread is currentThread:
        continue
    thread.join(500)

print 'Download script has finished.'