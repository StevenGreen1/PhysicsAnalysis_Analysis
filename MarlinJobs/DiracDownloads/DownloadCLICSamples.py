import os
import re

from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient

#=================================

jobDescription = 'PhysicsAnalysis'

eventsToDownload = [
                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 5527, 'NumberOfEvents': 335300 }
#                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 5594, 'NumberOfEvents': 715200 },
#                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 5572, 'NumberOfEvents': 1101100 },
#                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 4034, 'NumberOfEvents': 591800 },
#                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3243, 'NumberOfEvents': 577200 },
#                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3249, 'NumberOfEvents': 2043200 },
#                       { 'EventType': 'ee_ll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3246, 'NumberOfEvents': 2104400 },
#                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 2091, 'NumberOfEvents': 459000 },
#                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3366, 'NumberOfEvents': 129100 },
#                       { 'EventType': 'egamma_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3369, 'NumberOfEvents': 126300 },
#                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3372, 'NumberOfEvents': 137400 },
#                       { 'EventType': 'gammae_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3375, 'NumberOfEvents': 120200 },
#                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3378, 'NumberOfEvents': 180100 },
#                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3381, 'NumberOfEvents': 175000 },
#                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3384, 'NumberOfEvents': 177800 },
#                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3387, 'NumberOfEvents': 173800 },
#                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3414, 'NumberOfEvents': 167300 },
#                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3417, 'NumberOfEvents': 167900 },
#                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3420, 'NumberOfEvents': 170700 },
#                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1, 'ProdID': 3423, 'NumberOfEvents': 159800 }
                   ]

#rootFileName = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_Number_' + str(idx+1) + '_Of_' + str(numberOfFiles)
#rootFileNameSelected = rootFileName + '_Selected.root'
#rootFileNameTight = rootFileName + '_Tight.root'
#rootFileNameLoose = rootFileName + '_Loose.root'
#=================================

fc = FileCatalogClient()

for eventSelection in eventsToDownload:
    eventType = eventSelection['EventType']
    energy = eventSelection['Energy']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    numberOfEvent = eventSelection['NumberOfEvents']

    gridPath = '/ilc/user/s/sgreen/' + jobDescription + '/MarlinJobs/Detector_Model_' + detectorModel + '/Reconstruction_Variant_' + reconstructionVariant + '/' + eventType + '_ProdID_' + str(prodID) + '/' + str(energy) + 'GeV'

    print 'Downloading from : ' + gridPath

    localPath = '/r06/lc/sg568/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV' 

    if not os.path.exists(localPath):
        os.makedirs(localPath)

    os.chdir(localPath)

    meta = {}
    meta['Owner'] = 'sgreen'

    res = fc.findFilesByMetadata(meta, gridPath)
    if not res['OK']:
        print res['Message']

    lfns = res['Value']

    for lfn in lfns:
        print 'Checking file : ' + lfn

        fileFormat = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_Number_(\d+)_Of_(\d+)_(.*?).root'
        localFile = os.path.basename(lfn)

        if 'ProdID' not in lfn:
            continue

        print localFile
        print fileFormat

        matchObj = re.match(fileFormat, localFile, re.M|re.I)
        if not matchObj:
            continue

        if not os.path.isfile(localFile):
            os.system('dirac-dms-get-file ' + lfn)

print 'Download script has finished.'
