import os
import sys
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
                       { 'EventType': "ee_nunuqqqq"         , 'EventsPerFile' : 100 , 'Energies':  ['3000'], 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 18 },
                       { 'EventType': "ee_nunuqqqq"         , 'EventsPerFile' : 1000 , 'Energies':  ['1400'], 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 18 }
#                       { 'EventType': "ee_nunuqqqq"         , 'EventsPerFile' : 1000 , 'Energies':  ['1400'], 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 11 }
#                       { 'EventType': 'ee_nunuww_nunuqqqq'  , 'EventsPerFile' : 1000 , 'Energies':  ['1400'], 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3 },
#                       { 'EventType': 'ee_nunuzz_nunuqqqq'  , 'EventsPerFile' : 1000 , 'Energies':  ['1400'], 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3 }
                   ]

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
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    analysisTag = eventSelection['AnalysisTag']

    for energy in eventSelection['Energies']:
        localPath = '/r06/lc/sg568/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV/AnalysisTag' + str(analysisTag)
        if not os.path.exists(localPath):
            os.makedirs(localPath)

        gridPath = '/ilc/user/s/sgreen/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV/AnalysisTag' + str(analysisTag)

        meta = {}
        meta['Owner'] = 'sgreen'

        res = fc.findFilesByMetadata(meta, gridPath)
        if not res['OK']:
            print res['Message']

        lfns = res['Value']
        fileFormat = 'DetModel_' + detectorModel + '_RecoVar_' + reconstructionVariant + '_' + eventType + '_' + str(energy) + 'GeV_GenN_(\d+)_(\d+)_(\d+)_Tag' + str(analysisTag) + '(.*?).root'

        for lfn in lfns:
            matchObj = re.match(fileFormat, localFile, re.M|re.I)
            if not matchObj:
                continue

            fineLocalPath = os.path.join(localPath, matchObj.group(4))
            localFile = os.path.basename(lfn)
            localFilePath = os.path.join(fineLocalPath, localFile)

            if not os.path.isfile(localPath):
                while threading.activeCount() > (maxThread * 2):
                    time.sleep(5)

                print 'Downloading : ' + lfn
                downloadThread = threading.Thread(target=worker, name=str(localFilePath), args=(threadingSemaphore, pool, dm, lfn, fineLocalPath))
                downloadThread.start()

currentThread = threading.currentThread()

for thread in threading.enumerate():
    if thread is currentThread:
        continue
    thread.join(500)

print 'Download script has finished.'
