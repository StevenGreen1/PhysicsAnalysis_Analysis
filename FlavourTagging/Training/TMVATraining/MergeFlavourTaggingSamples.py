#!/usr/bin/env python

import os, subprocess
from subprocess import Popen, PIPE
from os import environ

eventsToMerge = [
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.0 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.0 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.0 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3039, 'NumberOfEvents': 94050, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3042, 'NumberOfEvents': 96600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  3000, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 3045, 'NumberOfEvents': 97950, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 }

                ]

jobDescription = 'PhysicsAnalysis_FlavourTagging'

for eventSelection in eventsToMerge:
    eventType = eventSelection['EventType']
    energy = eventSelection['Energy']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    numberOfEvent = eventSelection['NumberOfEvents']
    pandoraPFOsToUse = eventSelection['PandoraPFOsToUse']
    jetClusteringMode = eventSelection['JetClusteringMode']
    nJetsToCluster = eventSelection['NJetsToCluster']
    jetClusteringAlgorithm = eventSelection['JetClusteringAlgorithm']
    jetClusteringRadius = eventSelection['JetClusteringRadius']
    jetAlgorithmConfigString = jetClusteringAlgorithm + '_' + str(nJetsToCluster) + 'jets_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    if pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs':
        jetAlgorithmConfigString = 'SelectedPFOs_' + jetAlgorithmConfigString
    elif pandoraPFOsToUse == 'TightSelectedPandoraPFANewPFOs':
        jetAlgorithmConfigString = 'TightPFOs_' + jetAlgorithmConfigString
    elif pandoraPFOsToUse == 'LooseSelectedPandoraPFANewPFOs':
        jetAlgorithmConfigString = 'LoosePFOs_' + jetAlgorithmConfigString
    else:
        print 'Please select a set of PFOs from SelectedPandoraPFANewPFOs, TightSelectedPandoraPFANewPFOs or LooseSelectedPandoraPFANewPFOs.'
        exit()

    localPath = '/r06/lc/sg568/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV/' + jetAlgorithmConfigString

    haddRootFileOutput = os.path.join(localPath, 'RootFilesForTrainingFT_ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_' + jetAlgorithmConfigString + '.root')
    haddRootFileInput = os.path.join(localPath, 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_Number_*_Of_*.root')

    os.system('hadd -f ' +  haddRootFileOutput + ' ' + haddRootFileInput)
