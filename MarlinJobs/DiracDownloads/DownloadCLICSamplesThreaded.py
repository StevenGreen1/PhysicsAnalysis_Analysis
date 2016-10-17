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

jobDescription = 'PhysicsAnalysis'

eventsToDownload = [
#                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 5527, 'NumberOfEvents': 335300 },
                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 5594, 'NumberOfEvents': 715200 },
                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 5572, 'NumberOfEvents': 1101100 },
                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 4034, 'NumberOfEvents': 591800 },
                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3243, 'NumberOfEvents': 577200 },
                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3249, 'NumberOfEvents': 2043200 },
                       { 'EventType': 'ee_qqll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3246, 'NumberOfEvents': 2104400 },
                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2091, 'NumberOfEvents': 459000 },
                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3366, 'NumberOfEvents': 129100 },
                       { 'EventType': 'egamma_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3369, 'NumberOfEvents': 126300 },
                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3372, 'NumberOfEvents': 137400 },
                       { 'EventType': 'gammae_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3375, 'NumberOfEvents': 120200 },
                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3378, 'NumberOfEvents': 180100 },
                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3381, 'NumberOfEvents': 175000 },
                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3384, 'NumberOfEvents': 177800 },
                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3387, 'NumberOfEvents': 173800 },
                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3414, 'NumberOfEvents': 167300 },
                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3417, 'NumberOfEvents': 167900 },
                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3420, 'NumberOfEvents': 170700 },
                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3423, 'NumberOfEvents': 159800 }
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

    gridPath = '/ilc/user/s/sgreen/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV/AnalysisTag' + str(analysisTag)

    print 'Downloading from : ' + gridPath

    localPath = '/r06/lc/sg568/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV/AnalysisTag' + str(analysisTag) 

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

        fileFormat = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Tag' + str(analysisTag) + '_(\d+)_Of_(\d+)_SPFOs_kt_2jets_(.*?).root'
        localFile = os.path.basename(lfn)

        if 'ProdID' not in lfn:
            continue

        matchObj = re.match(fileFormat, localFile, re.M|re.I)
        if not matchObj:
            continue

        if not os.path.isfile(os.path.join(localPath,localFile)):
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
