#!/usr/bin/env python

import os, subprocess
from subprocess import Popen, PIPE
from os import environ

eventsToMerge = [
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 4, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 }
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
    shortPandoraPFOsToUse = ''
    jetClusteringMode = eventSelection['JetClusteringMode']
    nJetsToCluster = eventSelection['NJetsToCluster']
    jetClusteringAlgorithm = eventSelection['JetClusteringAlgorithm']
    jetClusteringRadius = eventSelection['JetClusteringRadius']
    jetAlgorithmConfigString = jetClusteringAlgorithm + '_' + str(nJetsToCluster) + 'jets_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    localPath = '/r06/lc/sg568/' + jobDescription + '/MarlinJobs/Detector_Model_' + str(detectorModel) + '/Reconstruction_Variant_' + str(reconstructionVariant) + '/' + eventType + '/' + str(energy) + 'GeV/' + jetAlgorithmConfigString

    os.chdir(localPath)
    print 'Changing directory to ' + localPath

    haddRootFileOutput = 'RootFilesForTrainingFT_ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_' + jetAlgorithmConfigString + '.root'
    haddRootFileInput = 'ProdID_' + str(prodID) + '_' + eventType + '_' + str(energy) + 'GeV_Analysis_' + str(analysisTag) + '_Number_*_Of_*.root'

    subprocess.call(['hadd', haddRootFileOutput, haddRootFileInput])

