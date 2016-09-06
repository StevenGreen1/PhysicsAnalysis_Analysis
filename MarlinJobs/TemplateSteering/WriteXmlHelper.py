#!/usr/bin/env python

import os

for jetN in [""" + str(jetN) + """,4,2]:
    for radius in [[0,""" + str(radius[1]) + """], [1,0]]:
        xmlString = """
    <processor name="JetClustering_SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string"> ??? </parameter> <!-- input PFO collection -->
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_BuildUpVertex </parameter> <!-- vertex collections to be used in JC -->
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_VertexJets </parameter> <!-- output collection name, may be multiple -->
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_VertexJets </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_RefinedVertex </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_PrimaryVertex </parameter>
    </processor>
"""
#        print xmlString



for jetN in [6,4,2]:
    for radius in [[0,7], [1,0]]:
        xmlString = """
    <processor name="JetClusteringAndFlavourTagGroup_SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet" type="LcfiplusProcessor">
      <parameter name="JetClustering.NJetsRequested" type="intVec" value=""" + "\"" + str(jetN) + "\"" + """/> <!-- Multiple NJets can be specified -->
      <parameter name="PFOCollection" type="string"> ??? </parameter> <!-- input PFO collection -->
      <parameter name="JetClustering.InputVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_BuildUpVertex </parameter> <!-- vertex collections to be used in JC -->
      <parameter name="JetClustering.OutputJetCollectionName" type="stringVec"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_VertexJets </parameter> <!-- output collection name, may be multiple -->
      <parameter name="JetVertexRefiner.InputJetCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_VertexJets  </parameter>
      <parameter name="JetVertexRefiner.OutputJetCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet </parameter>
      <parameter name="JetVertexRefiner.PrimaryVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_PrimaryVertex </parameter>
      <parameter name="JetVertexRefiner.InputVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_BuildUpVertex </parameter>
      <parameter name="JetVertexRefiner.V0VertexCollectionName" type="string">  SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_BuildUpVertex_V0 </parameter>
      <parameter name="JetVertexRefiner.OutputVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_RefinedVertex </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_PrimaryVertex </parameter>
      <parameter name="FlavorTag.JetCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet </parameter>
      <parameter name="FlavorTag.WeightsDirectory" type="string">lcfiweights_SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_1400GeV_2jets</parameter>
    </processor>
"""
#        print xmlString


for jetN in [6,4,2]:
    for radius in [[0,7], [1,0]]:
        xmlString = """
    <processor name = "MyFastJetProcessor_SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet" type="FastJetProcessor">
      <parameter name="clusteringMode" type="StringVec">ExclusiveNJets """ + str(jetN) + """</parameter>
      <parameter name="algorithm" type="StringVec">kt_algorithm """ + str(radius[0]) + """.""" + str(radius[1]) + """ </parameter>
      <parameter name="jetOut" type="string" lcioOutType="ReconstructedParticle"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_Initial </parameter>
    </processor>
"""
#        print xmlString


for jetN in [6,4,2]:
    for radius in [[0,7], [1,0]]:
        xmlString = """
    <processor name="MakeNtuple_SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet" type="LcfiplusProcessor">
      <parameter name="PFOCollection" type="string">  ??? </parameter>
      <parameter name="PrimaryVertexCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_PrimaryVertex </parameter>
      <parameter name="FlavorTag.JetCollectionName" type="string"> SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet_Intermediate </parameter>
      <parameter name="MakeNtuple.OutputRootFileName" type="string"> RootFileName_SelectedPFOs_kt_""" + str(radius[0]) + """p""" + str(radius[1]) + """_""" + str(jetN) + """jet </parameter>
    </processor>
"""
        print xmlString

