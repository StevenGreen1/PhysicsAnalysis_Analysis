#!/usr/bin/env python

import os

eventSelection = [
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'TightSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'LooseSelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'cambridge_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'ee_kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.5 },
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.7 },
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 0.9 },
                       { 'Energy':  1400, 'DetectorModel':'clic_ild_cdr', 'ReconstructionVariant':'clic_ild_cdr_ggHadBkg', 'AnalysisTag': 9, 'PandoraPFOsToUse': 'SelectedPandoraPFANewPFOs', 'JetClusteringMode': 'ExclusiveNJets', 'NJetsToCluster': 2, 'JetClusteringAlgorithm': 'kt_algorithm', 'JetClusteringRadius': 1.1 }
                ]

##############
# Begin
##############

template = """
<marlin>
  <execute>
    <group name="MyFastJetGroup"/>                    <!-- Make some jets -->
    <processor name = "MyJetsToPFOs"/>                <!-- Convert jets to PFOs -->
    <group name="MyVertexFinderGroup"/>               <!-- Find some vertices, not using jet information -->
    <group name="MyJetClusteringGroup"/>              <!-- Cluster some jets, then refine the vertexing using the jet information -->
    <group name="MyJetClusteringAndFlavourTagGroup"/> <!-- Cluster some jets, then refine the vertexing using the jet information and apply flavour tag information-->
    <group name="MyThrustReconstruction"/>            <!-- Calculate thrust -->
    <group name="MySphere"/>                          <!-- Calculate sphericity -->
    <group name="MyIsolatedLeptonFinder"/>            <!-- Isolated lepton finding -->
    <group name="MyAnalysisGroup"/>                   <!-- Run my analysis --> 
    <!--processor name="MyLCIOOutputProcessor"/-->
  </execute>

  <global>
    <parameter name="LCIOInputFiles">
      InputSlcioFile
    </parameter>
    <parameter name="GearXMLFile" value="GearFile"/>
    <parameter name="MaxRecordNumber" value="MaximumNumberOfEventsToRecord"/>
    <parameter name="SkipNEvents" value="0"/>
    <parameter name="SupressCheck" value="false"/>
    <parameter name="Verbosity" options="DEBUG0-4,MESSAGE0-4,WARNING0-4,ERROR0-4,SILENT"> MESSAGE </parameter>
  </global>

  <group name="MyFastJetGroup">
    <parameter name="recombinationScheme" type="string">E_scheme </parameter>
    <parameter name="recParticleIn" type="string" lcioInType="ReconstructedParticle"> SelectedPandoraPFANewPFOs </parameter>
"""

for event in eventSelection:
    pandoraPFOsToUse = event['PandoraPFOsToUse']
    jetClusteringMode = event['JetClusteringMode']
    nJetsToCluster = event['NJetsToCluster']
    jetClusteringAlgorithm = event['JetClusteringAlgorithm']
    jetClusteringRadius = event['JetClusteringRadius']
    jetAlgorithmConfigString = pandoraPFOsToUse + '_' + jetClusteringAlgorithm + '_' + str(format(jetClusteringRadius,'.2f')).replace('.','p') 

    template += """
    <processor name = "MyFastJetProcessor_""" + jetAlgorithmConfigString + """_6jet" type="FastJetProcessor">
      <parameter name="clusteringMode" type="StringVec">""" + jetClusteringMode + """ 6</parameter>
      <parameter name="algorithm" type="StringVec">""" + jetClusteringAlgorithm + """ """ + str(jetClusteringRadius) + """ </parameter>
      <parameter name="jetOut" type="string" lcioOutType="ReconstructedParticle"> """ + jetAlgorithmConfigString + """_6jet_Initial </parameter>
    </processor>
    <processor name = "MyFastJetProcessor_""" + jetAlgorithmConfigString + """_4jet" type="FastJetProcessor">
      <parameter name="clusteringMode" type="StringVec">""" + jetClusteringMode + """ 4</parameter>
      <parameter name="algorithm" type="StringVec">""" + jetClusteringAlgorithm + """ """ + str(jetClusteringRadius) + """ </parameter>
      <parameter name="jetOut" type="string" lcioOutType="ReconstructedParticle"> """ + jetAlgorithmConfigString + """_4jet_Initial </parameter>
    </processor>
    <processor name = "MyFastJetProcessor_""" + jetAlgorithmConfigString + """_2jet" type="FastJetProcessor">
      <parameter name="clusteringMode" type="StringVec">""" + jetClusteringMode + """ 2</parameter>
      <parameter name="algorithm" type="StringVec">""" + jetClusteringAlgorithm + """ """ + str(jetClusteringRadius) + """ </parameter>
      <parameter name="jetOut" type="string" lcioOutType="ReconstructedParticle"> """ + jetAlgorithmConfigString + """_2jet_Initial </parameter>
    </processor>
"""

template += """
  </group>

  <processor name="MyJetsToPFOs" type="JetsToPFOs">
    <parameter name="JetInputCollectionNames" type="StringVec"> """

for event in eventSelection:
    pandoraPFOsToUse = event['PandoraPFOsToUse']
    jetClusteringMode = event['JetClusteringMode']
    nJetsToCluster = event['NJetsToCluster']
    jetClusteringAlgorithm = event['JetClusteringAlgorithm']
    jetClusteringRadius = event['JetClusteringRadius']

    template += jetAlgorithmConfigString + '_6jet_Initial '
    template += jetAlgorithmConfigString + '_4jet_Initial '
    template += jetAlgorithmConfigString + '_2jet_Initial '

template += """
</parameter>
    <parameter name="PFOCollectionNames" type="StringVec"> """

for event in eventSelection:
    pandoraPFOsToUse = event['PandoraPFOsToUse']
    jetClusteringMode = event['JetClusteringMode']
    nJetsToCluster = event['NJetsToCluster']
    jetClusteringAlgorithm = event['JetClusteringAlgorithm']
    jetClusteringRadius = event['JetClusteringRadius']

    template += jetAlgorithmConfigString + '_6jet_pfos_Initial '
    template += jetAlgorithmConfigString + '_4jet_pfos_Initial '
    template += jetAlgorithmConfigString + '_2jet_pfos_Initial '

template += """
</parameter>
  </processor>

  <group name="MyVertexFinderGroup" type="LcfiplusProcessor">
    <!-- run primary and secondary vertex finders -->
    <parameter name="Algorithms" type="stringVec"> PrimaryVertexFinder BuildUpVertex </parameter>
    <parameter name="ReadSubdetectorEnergies" type="int" value="1"/> <!-- true for ILD -->
    <parameter name="UpdateVertexRPDaughters" type="int" value="0"/> <!-- false for non-updative PandoraPFOs -->
    <parameter name="PrintEventNumber" type="int" value="0"/> <!-- 0 for not printing event number, n for printing every n events -->
    <parameter name="MagneticField" type="float" value="4"/>
    <parameter name="BeamSizeX" type="float" value="45.0E-6"/>
    <parameter name="BeamSizeY" type="float" value="1.0E-6"/>
    <parameter name="BeamSizeZ" type="float" value="0.044"/>
    <!-- parameters for primary vertex finder -->
    <parameter name="PrimaryVertexFinder.TrackMaxD0" type="double" value="20." />
    <parameter name="PrimaryVertexFinder.TrackMaxZ0" type="double" value="20." />
    <parameter name="PrimaryVertexFinder.TrackMaxInnermostHitRadius" type="double" value="54" />
    <parameter name="PrimaryVertexFinder.TrackMinVtxFtdHits" type="int" value="1" />
    <parameter name="PrimaryVertexFinder.Chi2Threshold" type="double" value="25." />
    <parameter name="PrimaryVertexFinder.UseBeamConstraint" type="int" value="1" />
    <!-- parameters for secondary vertex finder -->
    <parameter name="BuildUpVertex.TrackMaxD0" type="double" value="10." />
    <parameter name="BuildUpVertex.TrackMaxZ0" type="double" value="20." />
    <parameter name="BuildUpVertex.TrackMinPt" type="double" value="0.1" />
    <parameter name="BuildUpVertex.TrackMaxD0Err" type="double" value="0.1" />
    <parameter name="BuildUpVertex.TrackMaxZ0Err" type="double" value="0.1" />
    <parameter name="BuildUpVertex.TrackMinTpcHits" type="int" value="20" />
    <parameter name="BuildUpVertex.TrackMinFtdHits" type="int" value="1" />
    <parameter name="BuildUpVertex.TrackMinVxdHits" type="int" value="1" />
    <parameter name="BuildUpVertex.TrackMinVxdFtdHits" type="int" value="1" />
    <parameter name="BuildUpVertex.PrimaryChi2Threshold" type="double" value="25." />
    <parameter name="BuildUpVertex.SecondaryChi2Threshold" type="double" value="9." />
    <parameter name="BuildUpVertex.MassThreshold" type="double" value="10." />
    <parameter name="BuildUpVertex.MinDistFromIP" type="double" value="0.3" />
    <parameter name="BuildUpVertex.MaxChi2ForDistOrder" type="double" value="1.0" />
    <parameter name="BuildUpVertex.AssocIPTracks" type="int" value="1" />
    <parameter name="BuildUpVertex.AssocIPTracksMinDist" type="double" value="0." />
    <parameter name="BuildUpVertex.AssocIPTracksChi2RatioSecToPri" type="double" value="2.0" />
    <parameter name="BuildUpVertex.UseV0Selection" type="int" value="1" />
    <!-- specify input collection names -->
"""

for event in eventSelection:
    pandoraPFOsToUse = event['PandoraPFOsToUse']
    jetClusteringMode = event['JetClusteringMode']
    nJetsToCluster = event['NJetsToCluster']
    jetClusteringAlgorithm = event['JetClusteringAlgorithm']
    jetClusteringRadius = event['JetClusteringRadius']
    jetAlgorithmConfigString = pandoraPFOsToUse + '_' + jetClusteringAlgorithm + '_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    template += """
    <processor name="VertexFinder_""" + jetAlgorithmConfigString + """_6jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_6jet_pfos_Initial </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_PrimaryVertex </parameter>
      <parameter name="BuildUpVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex </parameter>
      <parameter name="BuildUpVertex.V0VertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex_V0 </parameter>
    </processor>
    <processor name="VertexFinder_""" + jetAlgorithmConfigString + """_4jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_4jet_pfos_Initial </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_PrimaryVertex </parameter>
      <parameter name="BuildUpVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex </parameter>
      <parameter name="BuildUpVertex.V0VertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex_V0 </parameter>
    </processor>
    <processor name="VertexFinder_""" + jetAlgorithmConfigString + """_2jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_2jet_pfos_Initial </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_PrimaryVertex </parameter>
      <parameter name="BuildUpVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex </parameter>
      <parameter name="BuildUpVertex.V0VertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex_V0 </parameter>
    </processor>
"""

template += """
  </group>

  <group name="MyJetClusteringGroup" type="LcfiplusProcessor">
    <!-- run primary and secondary vertex finders -->
    <parameter name="Algorithms" type="stringVec"> JetClustering JetVertexRefiner</parameter>
    <!-- general parameters -->
    <parameter name="UseMCP" type="int" value="0" /> <!-- MC info not used -->
    <parameter name="MCPCollection" type="string" value="" /> <!-- not used -->
    <parameter name="MCPFORelation" type="string" value="" /> <!-- not used -->
    <parameter name="ReadSubdetectorEnergies" type="int" value="1"/> <!-- true for ILD -->
    <parameter name="UpdateVertexRPDaughters" type="int" value="0"/> <!-- false for non-updative PandoraPFOs -->
    <parameter name="MagneticField" type="float" value="4"/>
    <!-- jet clustering parameters -->
    <parameter name="JetClustering.NJetsRequested" type="intVec" value="2" />
    <parameter name="JetClustering.YCut" type="doubleVec" value="0." /> <!-- specify 0 if not used -->
    <parameter name="JetClustering.UseMuonID" type="int" value="1" /> <!-- jet-muon ID for jet clustering -->
    <parameter name="JetClustering.VertexSelectionMinimumDistance" type="double" value="0.3" /> <!-- in mm -->
    <parameter name="JetClustering.VertexSelectionMaximumDistance" type="double" value="30." /> <!-- in mm -->
    <parameter name="JetClustering.VertexSelectionK0MassWidth" type="double" value="0.02" /> <!-- in GeV -->
    <parameter name="JetClustering.YAddedForJetVertexVertex" type="double" value="100"/> <!-- add penalty for combining vertices -->
    <parameter name="JetClustering.YAddedForJetLeptonVertex" type="double" value="100"/> <!-- add penalty for combining lepton and vertex -->
    <parameter name="JetClustering.YAddedForJetLeptonLepton" type="double" value="100"/> <!-- add penalty for combining leptons -->
    <!-- vertex refiner parameters -->
    <parameter name="JetVertexRefiner.MinPosSingle" type="double" value="0.3" />
    <parameter name="JetVertexRefiner.MaxPosSingle" type="double" value="30." />
    <parameter name="JetVertexRefiner.MinEnergySingle" type="double" value="1." />
    <parameter name="JetVertexRefiner.MaxAngleSingle" type="double" value="0.5" />
    <parameter name="JetVertexRefiner.MaxSeparationPerPosSingle" type="double" value="0.1" />
    <parameter name="JetVertexRefiner.mind0sigSingle" type="double" value="5." />
    <parameter name="JetVertexRefiner.minz0sigSingle" type="double" value="5." />
    <parameter name="JetVertexRefiner.OneVertexProbThreshold" type="double" value="0.001" />
    <parameter name="JetVertexRefiner.MaxCharmFlightLengthPerJetEnergy" type="double" value="0.1" />
"""

for event in eventSelection:
    pandoraPFOsToUse = event['PandoraPFOsToUse']
    jetClusteringMode = event['JetClusteringMode']
    nJetsToCluster = event['NJetsToCluster']
    jetClusteringAlgorithm = event['JetClusteringAlgorithm']
    jetClusteringRadius = event['JetClusteringRadius']
    jetAlgorithmConfigString = pandoraPFOsToUse + '_' + jetClusteringAlgorithm + '_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    template += """
    <processor name="JetClustering_""" + jetAlgorithmConfigString + """_6jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_6jet_pfos_Initial </parameter>
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex </parameter>
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> """ + jetAlgorithmConfigString + """_6jet_VertexJets_Intermediate </parameter>
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_VertexJets_Intermediate </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_Intermediate </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_RefinedVertex_Intermediate </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_PrimaryVertex </parameter>
    </processor>
    <processor name="JetClustering_""" + jetAlgorithmConfigString + """_4jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_4jet_pfos_Initial </parameter>
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex </parameter>
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> """ + jetAlgorithmConfigString + """_4jet_VertexJets_Intermediate </parameter>
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_VertexJets_Intermediate </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_Intermediate </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_RefinedVertex_Intermediate </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_PrimaryVertex </parameter>
    </processor>
    <processor name="JetClustering_""" + jetAlgorithmConfigString + """_2jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_2jet_pfos_Initial </parameter>
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex </parameter>
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> """ + jetAlgorithmConfigString + """_2jet_VertexJets_Intermediate </parameter>
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_VertexJets_Intermediate </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_Intermediate </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_RefinedVertex_Intermediate </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_PrimaryVertex </parameter>
    </processor>
"""

template += """
  </group>

  <group name="MyJetClusteringAndFlavourTagGroup">
    <!-- run primary and secondary vertex finders -->
    <parameter name="Algorithms" type="stringVec"> JetClustering JetVertexRefiner FlavorTag ReadMVA</parameter>
    <!-- general parameters -->
    <parameter name="UseMCP" type="int" value="0" /> <!-- MC info not used -->
    <parameter name="MCPCollection" type="string" value="" /> <!-- not used -->
    <parameter name="MCPFORelation" type="string" value="" /> <!-- not used -->
    <parameter name="ReadSubdetectorEnergies" type="int" value="1"/> <!-- true for ILD -->
    <parameter name="UpdateVertexRPDaughters" type="int" value="0"/> <!-- false for non-updative PandoraPFOs -->
    <parameter name="TrackHitOrdering" type="int" value="0"/> <!-- Track hit ordering: 0=ILD-LOI,SID-DBD, 1=ILD-DBD; CLIC_ILD uses same convension as ILD-LOI -->
    <parameter name="PrintEventNumber" type="int" value="0"/> <!-- 0 for not printing event number, n for printing every n events -->
    <parameter name="MagneticField" type="float" value="4"/>
    <!-- jet clustering parameters -->
    <parameter name="JetClustering.YCut" type="doubleVec" value="0." /> <!-- specify 0 if not used -->
    <parameter name="JetClustering.UseMuonID" type="int" value="1" /> <!-- jet-muon ID for jet clustering -->
    <parameter name="JetClustering.VertexSelectionMinimumDistance" type="double" value="0.3" /> <!-- in mm -->
    <parameter name="JetClustering.VertexSelectionMaximumDistance" type="double" value="30." /> <!-- in mm -->
    <parameter name="JetClustering.VertexSelectionK0MassWidth" type="double" value="0.02" /> <!-- in GeV -->
    <parameter name="JetClustering.YAddedForJetVertexVertex" type="double" value="100"/> <!-- add penalty for combining vertices -->
    <parameter name="JetClustering.YAddedForJetLeptonVertex" type="double" value="100"/> <!-- add penalty for combining lepton and vertex -->
    <parameter name="JetClustering.YAddedForJetLeptonLepton" type="double" value="100"/> <!-- add penalty for combining leptons -->
    <!-- vertex refiner parameters -->
    <parameter name="JetVertexRefiner.MinPosSingle" type="double" value="0.3" />
    <parameter name="JetVertexRefiner.MaxPosSingle" type="double" value="30." />
    <parameter name="JetVertexRefiner.MinEnergySingle" type="double" value="1." />
    <parameter name="JetVertexRefiner.MaxAngleSingle" type="double" value="0.5" />
    <parameter name="JetVertexRefiner.MaxSeparationPerPosSingle" type="double" value="0.1" />
    <parameter name="JetVertexRefiner.mind0sigSingle" type="double" value="5." />
    <parameter name="JetVertexRefiner.minz0sigSingle" type="double" value="5." />
    <parameter name="JetVertexRefiner.OneVertexProbThreshold" type="double" value="0.001" />
    <parameter name="JetVertexRefiner.MaxCharmFlightLengthPerJetEnergy" type="double" value="0.1" />
    <!-- FlavorTag parameters -->
    <parameter name="MakeNtuple.AuxiliaryInfo" type="int" value="-1" />
    <parameter name="FlavorTag.D0ProbFileName" type="string">vtxprob/d0prob_zpole.root</parameter>
    <parameter name="FlavorTag.Z0ProbFileName" type="string">vtxprob/z0prob_zpole.root</parameter>
    <parameter name="FlavorTag.WeightsPrefix" type="string" value="2jets" />
    <parameter name="FlavorTag.BookName" type="string" value="bdt" />
    <parameter name="FlavorTag.PIDAlgo" type="string" value="lcfiplus" />
    <parameter name="FlavorTag.CategoryDefinition1" type="string">nvtx==0</parameter>
    <parameter name="FlavorTag.CategoryPreselection1" type="string">trk1d0sig!=0</parameter>
    <parameter name="FlavorTag.CategoryVariables1" type="stringVec">
      trk1d0sig trk2d0sig trk1z0sig trk2z0sig trk1pt_jete trk2pt_jete trkmass
      jprobr5sigma jprobz5sigma d0bprob d0cprob d0qprob z0bprob z0cprob z0qprob
    </parameter>
    <parameter name="FlavorTag.CategorySpectators1" type="stringVec">
      aux nvtx
    </parameter>
    <parameter name="FlavorTag.CategoryDefinition2" type="string">nvtx==1&amp;&amp;nvtxall==1</parameter>
    <parameter name="FlavorTag.CategoryPreselection2" type="string">trk1d0sig!=0</parameter>
    <parameter name="FlavorTag.CategoryVariables2" type="stringVec">
      trk1d0sig trk2d0sig trk1z0sig trk2z0sig trk1pt_jete trk2pt_jete jprobr jprobz
      vtxlen1_jete vtxsig1_jete vtxdirang1_jete vtxmom1_jete vtxmass1 vtxmult1 vtxmasspc vtxprob
      trkmass d0bprob d0cprob d0qprob z0bprob z0cprob z0qprob
    </parameter>
    <parameter name="FlavorTag.CategorySpectators2" type="stringVec">
      aux nvtx
    </parameter>
    <parameter name="FlavorTag.CategoryDefinition3" type="string">nvtx==1&amp;&amp;nvtxall==2</parameter>
    <parameter name="FlavorTag.CategoryPreselection3" type="string">trk1d0sig!=0</parameter>
    <parameter name="FlavorTag.CategoryVariables3" type="stringVec">
      trk1d0sig trk2d0sig trk1z0sig trk2z0sig trk1pt_jete trk2pt_jete jprobr jprobz
      vtxlen1_jete vtxsig1_jete vtxdirang1_jete vtxmom1_jete vtxmass1 vtxmult1 vtxmasspc vtxprob
      1vtxprob vtxlen12all_jete vtxmassall
    </parameter>
    <parameter name="FlavorTag.CategorySpectators3" type="stringVec">
      aux nvtx
    </parameter>
    <parameter name="FlavorTag.CategoryDefinition4" type="string">nvtx&gt;=2</parameter>
    <parameter name="FlavorTag.CategoryPreselection4" type="string">trk1d0sig!=0</parameter>
    <parameter name="FlavorTag.CategoryVariables4" type="stringVec">
      trk1d0sig trk2d0sig trk1z0sig trk2z0sig trk1pt_jete trk2pt_jete jprobr jprobz
      vtxlen1_jete vtxsig1_jete vtxdirang1_jete vtxmom1_jete vtxmass1 vtxmult1 vtxmasspc vtxprob
      vtxlen2_jete vtxsig2_jete vtxdirang2_jete vtxmom2_jete vtxmass2 vtxmult2
      vtxlen12_jete vtxsig12_jete vtxdirang12_jete vtxmom_jete vtxmass vtxmult
      1vtxprob
    </parameter>
    <parameter name="FlavorTag.CategorySpectators4" type="stringVec">
      aux nvtx
    </parameter>
"""

for event in eventSelection:
    energy = event['Energy']
    pandoraPFOsToUse = event['PandoraPFOsToUse']
    jetClusteringMode = event['JetClusteringMode']
    nJetsToCluster = event['NJetsToCluster']
    jetClusteringAlgorithm = event['JetClusteringAlgorithm']
    jetClusteringRadius = event['JetClusteringRadius']
    jetAlgorithmConfigString = pandoraPFOsToUse + '_' + jetClusteringAlgorithm + '_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    template += """
    <processor name="JetClusteringAndFlavourTagGroup_""" + jetAlgorithmConfigString + """_6jet" type="LcfiplusProcessor">
      <parameter name="JetClustering.NJetsRequested" type="intVec" value="6"/>
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_6jet_pfos_Initial </parameter>
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex </parameter>
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> """ + jetAlgorithmConfigString + """_6jet_VertexJets </parameter>
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_VertexJets  </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string">  """ + jetAlgorithmConfigString + """_6jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_RefinedVertex </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet_PrimaryVertex </parameter>
      <parameter name="FlavorTag.JetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_6jet </parameter>
      <parameter name="FlavorTag.WeightsDirectory" type="string">lcfiweights_""" + str(energy) + """GeV_""" + pandoraPFOsToUse + """_""" + jetClusteringAlgorithm + """_""" + str(nJetsToCluster) + """jets_""" + str(format(jetClusteringRadius,'.2f')).replace('.','p') + """</parameter>
    </processor>
    <processor name="JetClusteringAndFlavourTagGroup_""" + jetAlgorithmConfigString + """_4jet" type="LcfiplusProcessor">
      <parameter name="JetClustering.NJetsRequested" type="intVec" value="4"/>
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_4jet_pfos_Initial </parameter>
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex </parameter>
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> """ + jetAlgorithmConfigString + """_4jet_VertexJets </parameter>
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_VertexJets  </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string">  """ + jetAlgorithmConfigString + """_4jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_RefinedVertex </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet_PrimaryVertex </parameter>
      <parameter name="FlavorTag.JetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_4jet </parameter>
      <parameter name="FlavorTag.WeightsDirectory" type="string">lcfiweights_""" + str(energy) + """GeV_""" + pandoraPFOsToUse + """_""" + jetClusteringAlgorithm + """_""" + str(nJetsToCluster) + """jets_""" + str(format(jetClusteringRadius,'.2f')).replace('.','p') + """</parameter>
    </processor>
    <processor name="JetClusteringAndFlavourTagGroup_""" + jetAlgorithmConfigString + """_2jet" type="LcfiplusProcessor">
      <parameter name="JetClustering.NJetsRequested" type="intVec" value="2"/>
      <parameter name="PFOCollection" type="string"> """ + jetAlgorithmConfigString + """_2jet_pfos_Initial </parameter>
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex </parameter>
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> """ + jetAlgorithmConfigString + """_2jet_VertexJets </parameter>
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_VertexJets  </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string">  """ + jetAlgorithmConfigString + """_2jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_RefinedVertex </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet_PrimaryVertex </parameter>
      <parameter name="FlavorTag.JetCollectionName" type="string"> """ + jetAlgorithmConfigString + """_2jet </parameter>
      <parameter name="FlavorTag.WeightsDirectory" type="string">lcfiweights_""" + str(energy) + """GeV_""" + pandoraPFOsToUse + """_""" + jetClusteringAlgorithm + """_""" + str(nJetsToCluster) + """jets_""" + str(format(jetClusteringRadius,'.2f')).replace('.','p') + """</parameter>
    </processor>
"""

template += """
  </group>

  <group name="MyThrustReconstruction">
    <parameter name="typeOfThrustFinder"> 2 </parameter>
    <processor name="TightThrustReconstruction" type="ThrustReconstruction">
      <parameter name="inputCollectionName" type="string" lcioInType="ReconstructedParticle">TightSelectedPandoraPFANewPFOs</parameter>
    </processor>
    <processor name="SelectedThrustReconstruction" type="ThrustReconstruction">
      <parameter name="inputCollectionName" type="string" lcioInType="ReconstructedParticle">SelectedPandoraPFANewPFOs</parameter>
    </processor>
    <processor name="LooseThrustReconstruction" type="ThrustReconstruction">
      <parameter name="inputCollectionName" type="string" lcioInType="ReconstructedParticle">LooseSelectedPandoraPFANewPFOs</parameter>
    </processor>
  </group>

  <group name="MySphere">
    <processor name="TightSphere" type="Sphere">
      <parameter name="CollectionName" type="string" lcioInType="ReconstructedParticle">TightSelectedPandoraPFANewPFOs</parameter>
    </processor>
    <processor name="SelectedSphere" type="Sphere">
      <parameter name="CollectionName" type="string" lcioInType="ReconstructedParticle">SelectedPandoraPFANewPFOs</parameter>
    </processor>
    <processor name="LooseMySphere" type="Sphere">
      <parameter name="CollectionName" type="string" lcioInType="ReconstructedParticle">LooseSelectedPandoraPFANewPFOs</parameter>
    </processor>
  </group>

  <group name="MyIsolatedLeptonFinder">
    <parameter name="UseRectangularIsolation" type="bool">true </parameter>
    <parameter name="CosConeAngle" type="float">0.995 </parameter>
    <parameter name="IsolationMinimumConeEnergy" type="float">0 </parameter>
    <parameter name="IsolationMaximumConeEnergy" type="float">10000 </parameter>
    <parameter name="IsolationMinimumTrackEnergy" type="float">15 </parameter>
    <parameter name="IsolationMaximumTrackEnergy" type="float">10000 </parameter>
    <parameter name="UsePolynomialIsolation" type="bool">true </parameter>
    <parameter name="IsolationPolynomialCutA" type="float">0.0 </parameter>
    <parameter name="IsolationPolynomialCutB" type="float">5.7 </parameter>
    <parameter name="IsolationPolynomialCutC" type="float">-50. </parameter>
    <!--Use primitive particle ID based on calorimeter energy deposits-->
    <parameter name="UsePID" type="bool">true </parameter>
    <parameter name="MuonMinEcalToHcalFraction" type="float">0.05 </parameter>
    <parameter name="MuonMaxEcalToHcalFraction" type="float">0.25 </parameter>
    <parameter name="ElectronMinEcalToHcalFraction" type="float">0.9 </parameter>
    <!--Use impact parameter cuts for consistency with primary/secondary track-->
    <parameter name="UseImpactParameter" type="bool">true </parameter>
    <!--Minimum and maximum impact parameters-->
    <parameter name="ImpactParameterMinD0" type="float">0.0 </parameter>
    <parameter name="ImpactParameterMaxD0" type="float">0.02 </parameter>
    <parameter name="ImpactParameterMinZ0" type="float">0.0 </parameter>
    <parameter name="ImpactParameterMaxZ0" type="float">0.03 </parameter>
    <parameter name="ImpactParameterMin3D" type="float">0.0 </parameter>
    <parameter name="ImpactParameterMax3D" type="float">0.04 </parameter>
    <processor name="TightIsolatedLeptonFinder" type="IsolatedLeptonFinderProcessor">
      <parameter name="InputCollection" type="string" lcioInType="ReconstructedParticle"> TightSelectedPandoraPFANewPFOs </parameter>
      <parameter name="OutputCollectionIsolatedLeptons" type="string" lcioOutType="ReconstructedParticle"> TightSelectedPandoraPFANewPFOsIsolatedLeptons </parameter>
      <parameter name="OutputCollectionWithoutIsolatedLepton" type="string" lcioOutType="ReconstructedParticle"> TightSelectedPandoraPFANewPFOsWithoutIsolatedLeptons </parameter>
    </processor>
    <processor name="SelectedIsolatedLeptonFinder" type="IsolatedLeptonFinderProcessor">
      <parameter name="InputCollection" type="string" lcioInType="ReconstructedParticle"> SelectedPandoraPFANewPFOs </parameter>
      <parameter name="OutputCollectionIsolatedLeptons" type="string" lcioOutType="ReconstructedParticle"> SelectedPandoraPFANewPFOsIsolatedLeptons </parameter>
      <parameter name="OutputCollectionWithoutIsolatedLepton" type="string" lcioOutType="ReconstructedParticle"> SelectedPandoraPFANewPFOsWithoutIsolatedLeptons </parameter>
    </processor>
    <processor name="LooseIsolatedLeptonFinder" type="IsolatedLeptonFinderProcessor">
      <parameter name="InputCollection" type="string" lcioInType="ReconstructedParticle"> LooseSelectedPandoraPFANewPFOs </parameter>
      <parameter name="OutputCollectionIsolatedLeptons" type="string" lcioOutType="ReconstructedParticle"> LooseSelectedPandoraPFANewPFOsIsolatedLeptons </parameter>
      <parameter name="OutputCollectionWithoutIsolatedLepton" type="string" lcioOutType="ReconstructedParticle"> LooseSelectedPandoraPFANewPFOsWithoutIsolatedLeptons </parameter>
    </processor>
  </group>

  <group name="MyAnalysisGroup">
    <parameter name="MCParticleCollectionName" type="string" lcioInType="ReconstructedParticle">MCParticlesSkimmed</parameter>

"""

for event in eventSelection:
    energy = event['Energy']
    pandoraPFOsToUse = event['PandoraPFOsToUse']
    jetClusteringMode = event['JetClusteringMode']
    nJetsToCluster = event['NJetsToCluster']
    jetClusteringAlgorithm = event['JetClusteringAlgorithm']
    jetClusteringRadius = event['JetClusteringRadius']
    jetAlgorithmConfigString = pandoraPFOsToUse + '_' + jetClusteringAlgorithm + '_' + str(format(jetClusteringRadius,'.2f')).replace('.','p')

    template += """
    <processor name="AnalysisProcessor_""" + jetAlgorithmConfigString + """" type="AnalysisProcessor">
      <parameter name="PFOCollectionName" type="string" lcioInType="ReconstructedParticle">""" + pandoraPFOsToUse + """</parameter>
      <parameter name="IsolatedPFOsCollectionName" type="string" lcioInType="ReconstructedParticle">""" + pandoraPFOsToUse + """IsolatedLeptons</parameter>
      <parameter name="6JetCollectionName" type="string" lcioInType="ReconstructedParticle">""" + jetAlgorithmConfigString + """_6jet</parameter>
      <parameter name="4JetCollectionName" type="string" lcioInType="ReconstructedParticle">""" + jetAlgorithmConfigString + """_4jet</parameter>
      <parameter name="2JetCollectionName" type="string" lcioInType="ReconstructedParticle">""" + jetAlgorithmConfigString + """_2jet</parameter>
      <parameter name="RootFile" type="string">AnalysisProcessorRootFile_""" + jetAlgorithmConfigString + """</parameter>
    </processor>
"""

template += """
  </group>

  <processor name="MyLCIOOutputProcessor" type="LCIOOutputProcessor">
    <parameter name="LCIOOutputFile" type="string">OutputSlcioFile</parameter>
    <parameter name="LCIOWriteMode" type="string">WRITE_NEW</parameter>
    <!--parameter name="SplitFileSizekB" type="int">1992294 </parameter-->
  </processor>
</marlin>"""

file = open("Template.xml", "w")
file.write(template)
file.close()
