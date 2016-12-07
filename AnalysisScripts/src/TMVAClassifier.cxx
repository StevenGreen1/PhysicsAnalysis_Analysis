/**
 *  @file   AnalysisScripts/src/TMVAClassifier.cxx 
 * 
 *  @brief  Implementation of the TMVA classifier class.
 * 
 *  $Log: $
 */

#include "TMVAClassifier.h"

//=====================================================================

int main(int argc, char **argv)
{
    typedef std::vector<const Process*> ProcessVector;

    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_nunuqqqq",22.16,1500,1400,11);

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_lnuqqqq",115.3,1500,1400,9);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_llqqqq",71.7,1500,1400,9);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_qqqq",1328.1,1500,1400,9);

    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_nunuqq",933.9,1500,1400,9);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_lnuqq",4309.7,1500,1400,9);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_qqll",2725.8,1500,1400,9);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_qq",4009.5,1500,1400,9);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"egamma_qqqqe_EPA",287.1,1500,1400,9);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"egamma_qqqqe_BS",1160.7,1500,1400,9);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammae_qqqqe_EPA",286.9,1500,1400,9);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammae_qqqqe_BS",1156.3,1500,1400,9);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"egamma_qqqqnu_EPA",32.6,1500,1400,9);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"egamma_qqqqnu_BS",136.9,1500,1400,9);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammae_qqqqnu_EPA",32.6,1500,1400,9);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammae_qqqqnu_BS",136.4,1500,1400,9);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammagamma_qqqq_EPA_EPA",753.0,1500,1400,9);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammagamma_qqqq_EPA_BS",4034.8,1500,1400,9);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammagamma_qqqq_BS_EPA",4018.7,1500,1400,9);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"gammagamma_qqqq_BS_BS",4009.5,1500,1400,9);

    ProcessVector sigProcesses;
    ProcessVector bkgProcesses;

    sigProcesses.push_back(pProcess_ee_nunuqqqq);

    bkgProcesses.push_back(pProcess_ee_lnuqqqq);
    bkgProcesses.push_back(pProcess_ee_llqqqq);
    bkgProcesses.push_back(pProcess_ee_qqqq);

    bkgProcesses.push_back(pProcess_ee_nunuqq);
    bkgProcesses.push_back(pProcess_ee_lnuqq);
    bkgProcesses.push_back(pProcess_ee_qqll);
    bkgProcesses.push_back(pProcess_ee_qq);

    bkgProcesses.push_back(pProcess_egamma_qqqqe_EPA);
    bkgProcesses.push_back(pProcess_egamma_qqqqe_BS);
    bkgProcesses.push_back(pProcess_gammae_qqqqe_EPA);
    bkgProcesses.push_back(pProcess_gammae_qqqqe_BS);

    bkgProcesses.push_back(pProcess_egamma_qqqqnu_EPA);
    bkgProcesses.push_back(pProcess_egamma_qqqqnu_BS);
    bkgProcesses.push_back(pProcess_gammae_qqqqnu_EPA);
    bkgProcesses.push_back(pProcess_gammae_qqqqnu_BS);

    bkgProcesses.push_back(pProcess_gammagamma_qqqq_EPA_EPA);
    bkgProcesses.push_back(pProcess_gammagamma_qqqq_EPA_BS);
    bkgProcesses.push_back(pProcess_gammagamma_qqqq_BS_EPA);
    bkgProcesses.push_back(pProcess_gammagamma_qqqq_BS_BS);

    TMVAClassifier *pTMVAClassifier = new TMVAClassifier(sigProcesses, bkgProcesses);
}

//=====================================================================

TMVAClassifier::TMVAClassifier(ProcessVector sigProcesses, ProcessVector bkgProcesses)
{
    TString outfileName( "TMVA.root" );
    TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

//    factory->AddVariable( "myvar1 := var1 + var2", 'D' );
//    factory->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'D' );
//    factory->AddVariable( "var3",                "Variable 3", "units", 'D' );
//    factory->AddVariable( "var4",                "Variable 4", "units", 'D' );

    factory->AddVariable( "NPfos := NParticlesJet1 + NParticlesJet2 + NParticlesJet3 + NParticlesJet4", "Number of PFOs", "", 'I');
//    factory->AddVariable( "NumberOfIsolatedLeptons", "Number of Isolated Leptons", "", 'I');
    factory->AddVariable( "InvMassWVector1", "Invariant Mass W Boson 1", "GeV", 'D');
    factory->AddVariable( "InvMassWVector2", "Invariant Mass W Boson 2", "GeV", 'D');
    factory->AddVariable( "InvMassZVector1", "Invariant Mass Z Boson 1", "GeV", 'D');
    factory->AddVariable( "InvMassZVector2", "Invariant Mass Z Boson 2", "GeV", 'D');
    factory->AddVariable( "TransverseMomentum", "Transverse Momentum", "GeV", 'D');
    factory->AddVariable( "TransverseMomentumBosonW1", "Transverse Momentum W Boson 1", "GeV", 'D');
    factory->AddVariable( "TransverseMomentumBosonW2", "Transverse Momentum W Boson 2", "GeV", 'D');
    factory->AddVariable( "TransverseMomentumBosonZ1", "Transverse Momentum Z Boson 1", "GeV", 'D');
    factory->AddVariable( "TransverseMomentumBosonZ2", "Transverse Momentum Z Boson 2", "GeV", 'D');
    factory->AddVariable( "TransverseEnergy", "Transverse Energy", "GeV", 'D');
    factory->AddVariable( "TransverseEnergyBosonW1", "Transverse Energy W Boson 1", "GeV", 'D');
    factory->AddVariable( "TransverseEnergyBosonW2", "Transverse Energy W Boson 2", "GeV", 'D');
    factory->AddVariable( "TransverseEnergyBosonZ1", "Transverse Energy Z Boson 1", "GeV", 'D');
    factory->AddVariable( "TransverseEnergyBosonZ2", "Transverse Energy Z Boson 2", "GeV", 'D');
/*
    factory->AddVariable( "EnergyW1 := (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>0.5 && WBosonJet2Is<1.5) * (EnergyJet1 + EnergyJet2) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * (EnergyJet1 + EnergyJet3) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * (EnergyJet1 + EnergyJet4) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * (EnergyJet2 + EnergyJet3) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * (EnergyJet2 + EnergyJet4) + (WBosonJet1Is>1.5 && WBosonJet1Is<2.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * (EnergyJet3 + EnergyJet4)", "Energy W Boson 1", "GeV", 'D');

    factory->AddVariable( "EnergyW2 := (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>0.5 && WBosonJet4Is<1.5) * (EnergyJet1 + EnergyJet2) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * (EnergyJet1 + EnergyJet3) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * (EnergyJet1 + EnergyJet4) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * (EnergyJet2 + EnergyJet3) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * (EnergyJet2 + EnergyJet4) + (WBosonJet3Is>1.5 && WBosonJet3Is<2.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * (EnergyJet3 + EnergyJet4)", "Energy W Boson 2", "GeV", 'D');

//    factory->AddVariable( "EnergyZ1 := (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>0.5 && ZBosonJet2Is<1.5) * (EnergyJet1 + EnergyJet2) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * (EnergyJet1 + EnergyJet3) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * (EnergyJet1 + EnergyJet4) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * (EnergyJet2 + EnergyJet3) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * (EnergyJet2 + EnergyJet4) + (ZBosonJet1Is>1.5 && ZBosonJet1Is<2.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * (EnergyJet3 + EnergyJet4)", "Energy Z Boson 1", "GeV", 'D');

//    factory->AddVariable( "EnergyZ2 := (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>0.5 && ZBosonJet4Is<1.5) * (EnergyJet1 + EnergyJet2) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * (EnergyJet1 + EnergyJet3) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * (EnergyJet1 + EnergyJet4) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * (EnergyJet2 + EnergyJet3) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * (EnergyJet2 + EnergyJet4) + (ZBosonJet3Is>1.5 && ZBosonJet3Is<2.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * (EnergyJet3 + EnergyJet4)", "Energy Z Boson 2", "GeV", 'D');
*/
    factory->AddVariable( "CosThetaMissing", "Cosine Theta Of Missing Momentum", "", 'D');
    factory->AddVariable( "CosThetaMostEnergeticTrack", "Cosine Theta Of Most Energetic Track", "", 'D');
    factory->AddVariable( "y12", "Jet Clustering Parameter Y12", "", 'D');
    factory->AddVariable( "y23", "Jet Clustering Parameter Y23", "", 'D');
    factory->AddVariable( "y34", "Jet Clustering Parameter Y34", "", 'D');
    factory->AddVariable( "y45", "Jet Clustering Parameter Y45", "", 'D');
    factory->AddVariable( "y56", "Jet Clustering Parameter Y56", "", 'D');
    factory->AddVariable( "y67", "Jet Clustering Parameter Y67", "", 'D');
    factory->AddVariable( "InvariantMassSystem", "Invariant Mass of the System", "GeV", 'D');
////    factory->AddVariable( "CosThetaStarWBosons", "Cosine Theta Star of W Boson with W Pairing", "", 'D');
////    factory->AddVariable( "CosThetaStarZBosons", "Cosine Theta Star of Z Boson with Z Pairing", "", 'D');
////    factory->AddVariable( "CosThetaStarWJet1", "Cosine Theta Star of Jets from W Boson 1 with W Pairing", "", 'D');
////    factory->AddVariable( "CosThetaStarWJet2", "Cosine Theta Star of Jets from W Boson 2 with W Pairing", "", 'D');
////    factory->AddVariable( "CosThetaStarZJet1", "Cosine Theta Star of Jets from Z Boson 1 with W Pairing", "", 'D');
////    factory->AddVariable( "CosThetaStarZJet2", "Cosine Theta Star of Jets from Z Boson 2 with W Pairing", "", 'D');
    factory->AddVariable( "AcolinearityJetsW1", "Acolinearity Jets From W Boson 1", "", 'D');
    factory->AddVariable( "AcolinearityJetsW2", "Acolinearity Jets From W Boson 2", "", 'D');
    factory->AddVariable( "AcolinearityJetsZ1", "Acolinearity Jets From Z Boson 1", "", 'D');
    factory->AddVariable( "AcolinearityJetsZ2", "Acolinearity Jets From Z Boson 2", "", 'D');
    factory->AddVariable( "AcolinearityBosonsW", "Acolinearity W Bosons", "", 'D');
    factory->AddVariable( "AcolinearityBosonsZ", "Acolinearity Z Bosons", "", 'D');
    factory->AddVariable( "PrincipleThrustValue", "PrincipleThrustValue", "", 'D');
    factory->AddVariable( "MajorThrustValue", "MajorThrustValue", "", 'D');
    factory->AddVariable( "MinorThrustValue", "MinorThrustValue", "", 'D');
    factory->AddVariable( "Sphericity", "Sphericity", "", 'D');
    factory->AddVariable( "Aplanarity", "Aplanarity", "", 'D');

    factory->AddVariable( "(HighestEnergyElectronEnergy<10000)*HighestEnergyElectronEnergy", "Highest Energy Electron Energy", "GeV", 'D');
    factory->AddVariable( "(HighestEnergyElectronMomentum<10000)*HighestEnergyElectronMomentum", "Highest Energy Electron Momentum", "GeV", 'D');
    factory->AddVariable( "(HighestEnergyElectronTransverseMomentum<10000)*HighestEnergyElectronTransverseMomentum", "Highest Energy Electron Transverse Momentum", "GeV", 'D');
////    factory->AddVariable( "HighestEnergyElectronCosTheta", "HighestEnergyElectronCosTheta", "", 'D');
    factory->AddVariable( "(HighestEnergyMuonEnergy<10000)*HighestEnergyMuonEnergy", "Highest Energy Muon Energy", "GeV", 'D');
    factory->AddVariable( "(HighestEnergyMuonMomentum<10000)*HighestEnergyMuonMomentum", "Highest Energy Muon Momentum", "GeV", 'D');
    factory->AddVariable( "(HighestEnergyMuonTransverseMomentum<10000)*HighestEnergyMuonTransverseMomentum", "Highest Energy Muon Transverse Momentum", "GeV", 'D');
////    factory->AddVariable( "HighestEnergyMuonCosTheta", "HighestEnergyMuonCosTheta", "", 'D');
    factory->AddVariable( "(HighestEnergyPfoEnergy<10000)*HighestEnergyPfoEnergy", "Highest Energy Pfo Energy", "GeV", 'D');
    factory->AddVariable( "(HighestEnergyPfoMomentum<10000)*HighestEnergyPfoMomentum", "Highest Energy Pfo Momentum", "GeV", 'D');
    factory->AddVariable( "(HighestEnergyPfoTransverseMomentum<10000)*HighestEnergyPfoTransverseMomentum", "Highest Energy Pfo Transverse Momentum", "GeV", 'D');
////    factory->AddVariable( "HighestEnergyPfoCosTheta", "HighestEnergyPfoCosTheta", "", 'D');

    factory->AddVariable( "MaxBTag := TMath::Max(BTagForJet1, TMath::Max(BTagForJet2, TMath::Max(BTagForJet3,BTagForJet4)))", "Maximum BTag For Jets", "", 'D');
    factory->AddVariable( "MinBTag := TMath::Min(BTagForJet1, TMath::Min(BTagForJet2, TMath::Min(BTagForJet3,BTagForJet4)))", "Minimum BTag For Jets", "", 'D');
    factory->AddVariable( "MaxCTag := TMath::Max(CTagForJet1, TMath::Max(CTagForJet2, TMath::Max(CTagForJet3,CTagForJet4)))", "Maximum CTag For Jets", "", 'D');
    factory->AddVariable( "MinCTag := TMath::Min(CTagForJet1, TMath::Min(CTagForJet2, TMath::Min(CTagForJet3,CTagForJet4)))", "Minimum CTag For Jets", "", 'D');
/*
    factory->AddVariable( "MaxBTagW1 := (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>0.5 && WBosonJet2Is<1.5) * TMath::Max(BTagForJet1, BTagForJet2) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Max(BTagForJet1, BTagForJet3) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Max(BTagForJet1, BTagForJet4) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Max(BTagForJet2, BTagForJet3) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Max(BTagForJet2, BTagForJet4) + (WBosonJet1Is>1.5 && WBosonJet1Is<2.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Max(BTagForJet3, BTagForJet4)", "MaximumBTagForW1", "", 'D');
    factory->AddVariable( "MinBTagW1 := (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>0.5 && WBosonJet2Is<1.5) * TMath::Min(BTagForJet1, BTagForJet2) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Min(BTagForJet1, BTagForJet3) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Min(BTagForJet1, BTagForJet4) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Min(BTagForJet2, BTagForJet3) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Min(BTagForJet2, BTagForJet4) + (WBosonJet1Is>1.5 && WBosonJet1Is<2.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Min(BTagForJet3, BTagForJet4)", "MinimumBTagForW1", "", 'D');
    factory->AddVariable( "MaxBTagW2 := (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>0.5 && WBosonJet4Is<1.5) * TMath::Max(BTagForJet1, BTagForJet2) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Max(BTagForJet1, BTagForJet3) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Max(BTagForJet1, BTagForJet4) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Max(BTagForJet2, BTagForJet3) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Max(BTagForJet2, BTagForJet4) + (WBosonJet3Is>1.5 && WBosonJet3Is<2.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Max(BTagForJet3, BTagForJet4)", "MaximumBTagForW2", "", 'D');
    factory->AddVariable( "MinBTagW2 := (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>0.5 && WBosonJet4Is<1.5) * TMath::Min(BTagForJet1, BTagForJet2) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Min(BTagForJet1, BTagForJet3) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Min(BTagForJet1, BTagForJet4) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Min(BTagForJet2, BTagForJet3) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Min(BTagForJet2, BTagForJet4) + (WBosonJet3Is>1.5 && WBosonJet3Is<2.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Min(BTagForJet3, BTagForJet4)", "MinimumBTagForW2", "", 'D');
    factory->AddVariable( "MaxCTagW1 := (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>0.5 && WBosonJet2Is<1.5) * TMath::Max(CTagForJet1, CTagForJet2) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Max(CTagForJet1, CTagForJet3) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Max(CTagForJet1, CTagForJet4) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Max(CTagForJet2, CTagForJet3) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Max(CTagForJet2, CTagForJet4) + (WBosonJet1Is>1.5 && WBosonJet1Is<2.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Max(CTagForJet3, CTagForJet4)", "MaximumCTagForW1", "", 'D');
    factory->AddVariable( "MinCTagW1 := (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>0.5 && WBosonJet2Is<1.5) * TMath::Min(CTagForJet1, CTagForJet2) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Min(CTagForJet1, CTagForJet3) + (WBosonJet1Is>-0.5 && WBosonJet1Is<0.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Min(CTagForJet1, CTagForJet4) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>1.5 && WBosonJet2Is<2.5) * TMath::Min(CTagForJet2, CTagForJet3) + (WBosonJet1Is>0.5 && WBosonJet1Is<1.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Min(CTagForJet2, CTagForJet4) + (WBosonJet1Is>1.5 && WBosonJet1Is<2.5 && WBosonJet2Is>2.5 && WBosonJet2Is<3.5) * TMath::Min(CTagForJet3, CTagForJet4)", "MinimumCTagForW1", "", 'D');
    factory->AddVariable( "MaxCTagW2 := (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>0.5 && WBosonJet4Is<1.5) * TMath::Max(CTagForJet1, CTagForJet2) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Max(CTagForJet1, CTagForJet3) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Max(CTagForJet1, CTagForJet4) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Max(CTagForJet2, CTagForJet3) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Max(CTagForJet2, CTagForJet4) + (WBosonJet3Is>1.5 && WBosonJet3Is<2.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Max(CTagForJet3, CTagForJet4)", "MaximumCTagForW2", "", 'D');
    factory->AddVariable( "MinCTagW2 := (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>0.5 && WBosonJet4Is<1.5) * TMath::Min(CTagForJet1, CTagForJet2) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Min(CTagForJet1, CTagForJet3) + (WBosonJet3Is>-0.5 && WBosonJet3Is<0.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Min(CTagForJet1, CTagForJet4) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>1.5 && WBosonJet4Is<2.5) * TMath::Min(CTagForJet2, CTagForJet3) + (WBosonJet3Is>0.5 && WBosonJet3Is<1.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Min(CTagForJet2, CTagForJet4) + (WBosonJet3Is>1.5 && WBosonJet3Is<2.5 && WBosonJet4Is>2.5 && WBosonJet4Is<3.5) * TMath::Min(CTagForJet3, CTagForJet4)", "MinimumCTagForW2", "", 'D');
    factory->AddVariable( "MaxBTagZ1 := (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>0.5 && ZBosonJet2Is<1.5) * TMath::Max(BTagForJet1, BTagForJet2) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Max(BTagForJet1, BTagForJet3) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Max(BTagForJet1, BTagForJet4) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Max(BTagForJet2, BTagForJet3) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Max(BTagForJet2, BTagForJet4) + (ZBosonJet1Is>1.5 && ZBosonJet1Is<2.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Max(BTagForJet3, BTagForJet4)", "MaximumBTagForZ1", "", 'D');
    factory->AddVariable( "MinBTagZ1 := (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>0.5 && ZBosonJet2Is<1.5) * TMath::Min(BTagForJet1, BTagForJet2) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Min(BTagForJet1, BTagForJet3) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Min(BTagForJet1, BTagForJet4) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Min(BTagForJet2, BTagForJet3) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Min(BTagForJet2, BTagForJet4) + (ZBosonJet1Is>1.5 && ZBosonJet1Is<2.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Min(BTagForJet3, BTagForJet4)", "MinimumBTagForZ1", "", 'D');
    factory->AddVariable( "MaxBTagZ2 := (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>0.5 && ZBosonJet4Is<1.5) * TMath::Max(BTagForJet1, BTagForJet2) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Max(BTagForJet1, BTagForJet3) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Max(BTagForJet1, BTagForJet4) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Max(BTagForJet2, BTagForJet3) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Max(BTagForJet2, BTagForJet4) + (ZBosonJet3Is>1.5 && ZBosonJet3Is<2.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Max(BTagForJet3, BTagForJet4)", "MaximumBTagForZ2", "", 'D');
    factory->AddVariable( "MinBTagZ2 := (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>0.5 && ZBosonJet4Is<1.5) * TMath::Min(BTagForJet1, BTagForJet2) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Min(BTagForJet1, BTagForJet3) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Min(BTagForJet1, BTagForJet4) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Min(BTagForJet2, BTagForJet3) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Min(BTagForJet2, BTagForJet4) + (ZBosonJet3Is>1.5 && ZBosonJet3Is<2.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Min(BTagForJet3, BTagForJet4)", "MinimumBTagForZ2", "", 'D');
    factory->AddVariable( "MaxCTagZ1 := (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>0.5 && ZBosonJet2Is<1.5) * TMath::Max(CTagForJet1, CTagForJet2) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Max(CTagForJet1, CTagForJet3) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Max(CTagForJet1, CTagForJet4) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Max(CTagForJet2, CTagForJet3) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Max(CTagForJet2, CTagForJet4) + (ZBosonJet1Is>1.5 && ZBosonJet1Is<2.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Max(CTagForJet3, CTagForJet4)", "MaximumCTagForZ1", "", 'D');
    factory->AddVariable( "MinCTagZ1 := (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>0.5 && ZBosonJet2Is<1.5) * TMath::Min(CTagForJet1, CTagForJet2) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Min(CTagForJet1, CTagForJet3) + (ZBosonJet1Is>-0.5 && ZBosonJet1Is<0.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Min(CTagForJet1, CTagForJet4) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>1.5 && ZBosonJet2Is<2.5) * TMath::Min(CTagForJet2, CTagForJet3) + (ZBosonJet1Is>0.5 && ZBosonJet1Is<1.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Min(CTagForJet2, CTagForJet4) + (ZBosonJet1Is>1.5 && ZBosonJet1Is<2.5 && ZBosonJet2Is>2.5 && ZBosonJet2Is<3.5) * TMath::Min(CTagForJet3, CTagForJet4)", "MinimumCTagForZ1", "", 'D');
//    factory->AddVariable( "MaxCTagZ2 := (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>0.5 && ZBosonJet4Is<1.5) * TMath::Max(CTagForJet1, CTagForJet2) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Max(CTagForJet1, CTagForJet3) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Max(CTagForJet1, CTagForJet4) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Max(CTagForJet2, CTagForJet3) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Max(CTagForJet2, CTagForJet4) + (ZBosonJet3Is>1.5 && ZBosonJet3Is<2.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Max(CTagForJet3, CTagForJet4)", "MaximumCTagForZ2", "", 'D');
//    factory->AddVariable( "MinCTagZ2 := (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>0.5 && ZBosonJet4Is<1.5) * TMath::Min(CTagForJet1, CTagForJet2) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Min(CTagForJet1, CTagForJet3) + (ZBosonJet3Is>-0.5 && ZBosonJet3Is<0.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Min(CTagForJet1, CTagForJet4) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>1.5 && ZBosonJet4Is<2.5) * TMath::Min(CTagForJet2, CTagForJet3) + (ZBosonJet3Is>0.5 && ZBosonJet3Is<1.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Min(CTagForJet2, CTagForJet4) + (ZBosonJet3Is>1.5 && ZBosonJet3Is<2.5 && ZBosonJet4Is>2.5 && ZBosonJet4Is<3.5) * TMath::Min(CTagForJet3, CTagForJet4)", "MinimumCTagForZ2", "", 'D');
*/
    for (ProcessVector::iterator itPro = sigProcesses.begin(); itPro != sigProcesses.end(); itPro++)
    {
        const Process *pSigProcess(*itPro); 
        const float signalCrossSection(pSigProcess->GetCrossSection());
        const float signalLuminosity(pSigProcess->GetLuminosity());
        TChain *pTrainingTChain(pSigProcess->GetTrainingTChain()); 
        float weight(signalCrossSection*signalLuminosity/pTrainingTChain->GetEntries());
        factory->AddSignalTree(pTrainingTChain, weight);
    }

    for (ProcessVector::iterator itPro = bkgProcesses.begin(); itPro != bkgProcesses.end(); itPro++)
    {
        const Process *pBkgProcess(*itPro);
        const float bkgCrossSection(pBkgProcess->GetCrossSection());
        const float bkgLuminosity(pBkgProcess->GetLuminosity());
        TChain *pTrainingTChain(pBkgProcess->GetTrainingTChain());
        float weight(bkgCrossSection*bkgLuminosity/pTrainingTChain->GetEntries());
        factory->AddBackgroundTree(pTrainingTChain, weight);
    }

    TCut mycuts = "TransverseMomentum>100 && TransverseMomentum<10000 && InvariantMassSystem>200 && InvariantMassSystem<10000 && NumberOfIsolatedLeptons==0"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
    TCut mycutb = "TransverseMomentum>100 && TransverseMomentum<10000 && InvariantMassSystem>200 && InvariantMassSystem<10000 && NumberOfIsolatedLeptons==0"; // for example: TCut mycutb = "abs(var1)<0.5";
//    TCut mycutb = "InvMassWVector1>0 && InvMassWVector1<500 && InvMassWVector2>0 && InvMassWVector2<500 && InvMassZVector1>0 && InvMassZVector1<500 && InvMassZVector2>0 && InvMassZVector2<500 && TransverseMomentum>100 && TransverseMomentum<10000 && InvariantMassSystem<10000 && InvariantMassSystem>100"; // for example: TCut mycutb = "abs(var1)<0.5";

    factory->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees2000_MaxDepth3_NCuts25", "!H:!V:NTrees=2000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees2000_MaxDepth4_NCuts25", "!H:!V:NTrees=2000:MinNodeSize=2.5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees2000_MaxDepth5_NCuts25", "!H:!V:NTrees=2000:MinNodeSize=2.5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees2000_MaxDepth3_NCuts20", "!H:!V:NTrees=2000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees2000_MaxDepth3_NCuts30", "!H:!V:NTrees=2000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30" );


/*
 * NTrees
 * MaxDepth
 * nCuts // Kind of number of bins in phase space
 */

//    factory->BookMethod( TMVA::Types::kCuts, "Cuts", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
//    factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood", "H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

//    factory->BookMethod( TMVA::Types::kPDERS, "PDERS", "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );
//    factory->BookMethod( TMVA::Types::kKNN, "KNN", "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
//    factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N + 1,N"  );

    // --------------------------------------------------------------------------------------------------

    // ---- Now you can tell the factory to train, test, and evaluate the MVAs

    // Train MVAs using the set of training events
    factory->TrainAllMethods();

    // ---- Evaluate all MVAs using the set of test events
    factory->TestAllMethods();

    // ----- Evaluate and compare performance of all configured MVAs
    factory->EvaluateAllMethods();

    // --------------------------------------------------------------

    // Save the output
    outputFile->Close();

    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl
              << "==> TMVAClassification is done!" << std::endl
              << std::endl
              << "==> To view the results, launch the GUI: \"root -l ./TMVAGui.C\"" << std::endl
              << std::endl;

    // Clean up
    delete factory;
}

//=====================================================================
