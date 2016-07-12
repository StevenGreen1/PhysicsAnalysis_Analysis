import os

from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient

#=================================

jobDescription = 'PhysicsAnalysis'

eventsToDownload = [
                       { 'EventType': 'ee_nunuww_nunuqqqq'  , 'EventsPerFile' : 1000 , 'Energies':  ['1400'], 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1 },
                       { 'EventType': 'ee_nunuzz_nunuqqqq'  , 'EventsPerFile' : 1000 , 'Energies':  ['1400'], 'DetectorModel': 'clic_ild_cdr', 'ReconstructionVariant': 'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 1 },
                   ]

#=================================

fc = FileCatalogClient()

for eventSelection in eventsToDownload:
    eventType = eventSelection['EventType']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    analysisTag = eventSelection['AnalysisTag']

    for energy in eventSelection['Energies']:
        path = '/r06/lc/sg568/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV' 

        if not os.path.exists(path):
            os.makedirs(path)

        os.chdir(path)

        meta = {}
        meta['JobDescription'] = jobDescription
        meta['Type'] = 'Rec'
        meta['DetectorModel'] = str(detectorModel)
        meta['ReconstructionStage'] = str(reconstructionVariant)
        meta['Energy'] = str(energy)
        meta['EvtType'] = eventType

        res = fc.findFilesByMetadata(meta)
        if not res['OK']:
            print res['Message']

        lfns = res['Value']

        for lfn in lfns:
            analysisString = 'Analysis_' + str(analysisTag)
            if analysisString in lfn:
                localFile = os.path.basename(lfn)
                if not os.path.isfile(localFile):
                    os.system('dirac-dms-get-file ' + lfn)

print 'Download script has finished.'
