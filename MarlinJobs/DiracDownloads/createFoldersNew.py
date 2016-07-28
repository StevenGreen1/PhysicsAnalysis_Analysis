import os, sys
import logging
import random
import threading
import time

logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s (%(threadName)-2s) %(message)s',
                    )

from DIRAC.Core.Base import Script
Script.parseCommandLine()

from DIRAC.DataManagementSystem.Client.DataManager import DataManager
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient
from DIRAC.Core.Utilities.ReturnValues import returnSingleResult


foldername1400="hhnunu20160722"
nameJobGroup1400="anaDSTana"

prodIDs1400 = [6022, 5527, 6183, 5572, 6191, 5594, 4034, 3366, 3369, 3372, 3375, 3378, 6497, 6799, 3381, 6500, 6802, 3384, 6503, 6805, 3387, 6506, 6808, 3414, 3417,3420,3423, 3243, 3246, 3249, 2091, 6788, 6791, 6794]

foldername3000="hhnunu20160722"
nameJobGroup3000="anaDSTana3TeV"

prodIDs3000 = [6025, 6751, 6754, 6540, 6776, 6733, 6736, 6739, 6742, 6571, 6574, 6577, 6580, 6721, 6724, 6727, 6730, 6583, 3048, 6747, 4586, 6779, 6782, 6785 ]


def getFolderID(id):
    return {6183: 5527, 6191: 5594, 6497:3378, 6799:3378, 6500:3381, 6802:3381, 6503:3384, 6805:3384, 6506:3387, 6808:3387
    }.get(id, id)

dm = DataManager()
fc = FileCatalogClient()
maxThread = 50
def hasFilesInFolder(folder):
    if fc.isDirectory(folder)['OK'] :
        getFiles = fc.getDirectorySize(folder)
        if getFiles['OK']:
            if getFiles['Value']['Successful']:
                for key, values in getFiles['Value']['Successful'].iteritems():
                    return (values['LogicalFiles'] > 0)
    return False
    
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
            #logging.debug('Running: %s', self.active)
    def makeInactive(self, name):
        with self.lock:
            self.active.remove(name)
            #logging.debug('Running: %s', self.active)

def worker(s, pool, dm, lfn, localFolder):
    #logging.debug('Waiting to join the pool')
    with s:
        name = threading.currentThread().getName()
        pool.makeActive(name)
        downloadFile(dm, lfn, localFolder)
        pool.makeInactive(name)

def downloadFiles(prodIDs, folderName, nameJobGroup):
    totalThreads = []
    pool = ActivePool()
    s = threading.Semaphore(maxThread)
    
    currentFolder = os.path.normpath(os.path.dirname(os.path.realpath(__file__)))
    for prodID in prodIDs:
        downloadFolder = os.path.join(currentFolder, folderName, nameJobGroup + "_prod" + str(getFolderID(prodID)))
        
        if not os.path.exists(downloadFolder):
            os.makedirs(downloadFolder)
            print "Create: "+ downloadFolder
        else:
            print "Exist: "+ downloadFolder

        meta = {'Owner': 'bxu'}
        lfnFolder = os.path.join('/ilc/user/b/bxu/', folderName, nameJobGroup + "_prod" + str(prodID)) 
        #print lfnFolderF
        if not hasFilesInFolder(lfnFolder):
            print "Empty folder:" + lfnFolder
            continue

        res = fc.findFilesByMetadata(meta, lfnFolder)
        if not res['OK']:
            print res['Message']
            sys.exit(0)
        lfns = res['Value']

        print  str(len(lfns)) + " files in " + lfnFolder

        for lfn in lfns:

            filename = os.path.basename(lfn)
            if not filename:
                print "lfn is empty %s"%lfn
                continue

            localFileName = os.path.join(downloadFolder, filename)
            #print localFileName
            if os.path.isfile(localFileName):
                continue
            else:
                print "Will download file %s"%lfn
                #downloadThread = thread.thread(downloadFile, (dm, lfn, downloadFolder))
                #downloadFile(dm, lfn, downloadFolder)
                while threading.activeCount() > (maxThread * 2):
                    time.sleep(5)

                downloadThread = threading.Thread(target=worker, name=str(filename), args=(s, pool, dm, lfn, downloadFolder))
                downloadThread.start()
                '''totalThreads.append(downloadThread)'''
    '''for thread in totalThreads:
        thread.start()    
    for thread in totalThreads:
        thread.join(2) '''
    main_thread = threading.currentThread()
    for t in threading.enumerate():
        if t is main_thread:
            continue
        #logging.debug('joining %s', t.getName())
        t.join(500)
print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

if len(sys.argv) < 2:
    print "No extra argument provided"
    sys.exit(0)
for arg in sys.argv:
    if arg == "1.4TeV":
        downloadFiles(prodIDs1400, foldername1400, nameJobGroup1400)
    elif arg == "3TeV":
        downloadFiles(prodIDs3000, foldername3000, nameJobGroup3000)
        
