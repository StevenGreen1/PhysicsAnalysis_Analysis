# Example to submit Marlin job
import os
import re
import sys
import random

from ILCDIRAC.Interfaces.API.DiracILC import  DiracILC
from ILCDIRAC.Interfaces.API.NewInterface.UserJob import *
from ILCDIRAC.Interfaces.API.NewInterface.Applications import *
from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient

from Logic.GridTools import *
from Logic.ThreadedTools import *

#===== User Input =====

jobDescription = 'PhysicsAnalysis_FlavourTagging'

#eventsToSimulate = [ <- Already Simulated
#                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
#                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
#                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
#                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
#                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 },
#                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.0 }
#                   ]

# Study PFO Collections, Jet Clustering Algorithm, Jet Clustering Radius 

eventsToSimulate = [
                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },

                       { 'EventType': 'ee_Znunu_Zbb', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2804, 'NumberOfEvents': 99000, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 },
                       { 'EventType': 'ee_Znunu_Zcc', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2807, 'NumberOfEvents': 99600, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 },
                       { 'EventType': 'ee_Znunu_Zudsqudsq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'ProdID': 2801, 'NumberOfEvents': 99800, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 }

                   ]

#ee_kt_algorithm ExclusiveNJets
#antikt_algorithm Inclusive <- Avoid using
#cambridge_algorithm ExclusiveNJets
#kt_algorithm ExclusiveNJets

#eventsToSimulate = [
#                       { 'EventType': 'ee_nunuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 5527, 'NumberOfEvents': 335300 },  
#                       { 'EventType': 'ee_lnuqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 5594, 'NumberOfEvents': 715200 },
#                       { 'EventType': 'ee_llqqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 5572, 'NumberOfEvents': 1101100 },
#                       { 'EventType': 'ee_qqqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 4034, 'NumberOfEvents': 591800 },
#                       { 'EventType': 'ee_nunuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3243, 'NumberOfEvents': 577200 },
#                       { 'EventType': 'ee_lnuqq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3249, 'NumberOfEvents': 2043200 },
#                       { 'EventType': 'ee_ll', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3246, 'NumberOfEvents': 2104400 },
#                       { 'EventType': 'ee_qq', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 2091, 'NumberOfEvents': 459000 },
#                       { 'EventType': 'egamma_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3366, 'NumberOfEvents': 129100 },
#                       { 'EventType': 'egamma_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3369, 'NumberOfEvents': 126300 },
#                       { 'EventType': 'gammae_qqqqe_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3372, 'NumberOfEvents': 137400 },
#                       { 'EventType': 'gammae_qqqqe_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3375, 'NumberOfEvents': 120200 },
#                       { 'EventType': 'egamma_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3378, 'NumberOfEvents': 180100 },
#                       { 'EventType': 'egamma_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3381, 'NumberOfEvents': 175000 },
#                       { 'EventType': 'gammae_qqqqnu_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3384, 'NumberOfEvents': 177800 },
#                       { 'EventType': 'gammae_qqqqnu_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3387, 'NumberOfEvents': 173800 },
#                       { 'EventType': 'gammagamma_qqqq_EPA_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3414, 'NumberOfEvents': 167300 },
#                       { 'EventType': 'gammagamma_qqqq_EPA_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3417, 'NumberOfEvents': 167900 },
#                       { 'EventType': 'gammagamma_qqqq_BS_EPA', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3420, 'NumberOfEvents': 170700 },
#                       { 'EventType': 'gammagamma_qqqq_BS_BS', 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 3, 'ProdID': 3423, 'NumberOfEvents': 159800 }
#                   ]

#===== Second level user input =====

gearFile = 'TemplateSteering/clic_ild_cdr.gear'
steeringTemplateFile = 'TemplateSteering/FlavourTaggingTrainingTemplate.xml'
marlinVersion = 'v01-16-02'
maxThread = 100

##############
# Begin
##############

# Get content of template 
base = open(steeringTemplateFile,'r')
steeringTemplateContent = base.read()
base.close()

pool = ActivePool()
threadingSemaphore = threading.Semaphore(maxThread)

for eventSelection in eventsToSimulate:
    eventType = eventSelection['EventType']
    detectorModel = eventSelection['DetectorModel']
    reconstructionVariant = eventSelection['ReconstructionVariant']
    analysisTag = eventSelection['AnalysisTag']
    prodID = eventSelection['ProdID']
    energy = eventSelection['Energy']
    gearFile = 'TemplateSteering/' + detectorModel + '.gear'

    pandoraPFOsToUse = eventSelection['PandoraPFOsToUse']
    shortPandoraPFOsToUse = ''
    jetClusteringMode = eventSelection['JetClusteringMode']
    nJetsToCluster = eventSelection['NJetsToCluster']
    jetClusteringAlgorithm = eventSelection['JetClusteringAlgorithm']
    jetClusteringRadius = eventSelection['JetClusteringRadius']
    jetAlgorithmConfigString = jetClusteringAlgorithm + '_' + str(nJetsToCluster) + 'jets_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    if pandoraPFOsToUse == 'SelectedPandoraPFANewPFOs':
        shortPandoraPFOsToUse = 'SelectedPFOs'
        jetAlgorithmConfigString = 'SelectedPFOs_' + jetAlgorithmConfigString
    elif pandoraPFOsToUse == 'TightSelectedPandoraPFANewPFOs':
        shortPandoraPFOsToUse = 'TightPFOs'
        jetAlgorithmConfigString = 'TightPFOs_' + jetAlgorithmConfigString
    elif pandoraPFOsToUse == 'LooseSelectedPandoraPFANewPFOs':
        shortPandoraPFOsToUse = 'LoosePFOs'
        jetAlgorithmConfigString = 'LoosePFOs_' + jetAlgorithmConfigString
    else:
        print 'Please select a set of PFOs from SelectedPandoraPFANewPFOs, TightSelectedPandoraPFANewPFOs or LooseSelectedPandoraPFANewPFOs.'
        exit()

    # Make local gear file
    os.system('cp ' + gearFile + ' .')
    gearFileLocal = os.path.basename(gearFile)

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
        jobInfo['steeringTemplateContent'] = steeringTemplateContent
        jobInfo['prodID'] = prodID
        jobInfo['idx'] = idx
        jobInfo['numberOfFiles'] = numberOfFiles
        jobInfo['gearFileLocal'] = gearFileLocal
        jobInfo['diracInstance'] = diracInstance
        jobInfo['pandoraPFOsToUse'] = pandoraPFOsToUse
        jobInfo['shortPandoraPFOsToUse'] = shortPandoraPFOsToUse
        jobInfo['jetClusteringMode'] = jetClusteringMode
        jobInfo['nJetsToCluster'] = nJetsToCluster
        jobInfo['jetClusteringAlgorithm'] = jetClusteringAlgorithm
        jobInfo['jetClusteringRadius'] = jetClusteringRadius
        jobInfo['jetAlgorithmConfigString'] = jetAlgorithmConfigString

        downloadThread = threading.Thread(target=CLICWorker, name=str(clicFile), args=(threadingSemaphore, pool, jobInfo))
       downloadThread.start()

currentThread = threading.currentThread()
for thread in threading.enumerate():
    if thread is currentThread:
        continue
    thread.join(60)

# Tidy Up
os.system('rm ' + gearFileLocal)
