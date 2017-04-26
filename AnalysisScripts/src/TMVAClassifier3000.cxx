/**
 *  @file   AnalysisScripts/src/TMVAClassifier3000.cxx 
 * 
 *  @brief  Implementation of the TMVA classifier class.
 * 
 *  $Log: $
 */

#include "TMVAClassifier3000.h"

//=====================================================================

int main(int argc, char **argv)
{
    typedef std::vector<const Process*> ProcessVector;

    // Energy 3000 GeV
    float nominalLuminosity(2000);
    float eeLuminosityRatio(1.0);
    float egammaLuminosityRatio(0.79);
    float gammaeLuminosityRatio(0.79);
    float gammagammaLuminosityRatio(0.69);

    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_lnuqqqq",106.6,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_llqqqq",169.3,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qqqq",546.5,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqq",1317.5,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_lnuqq",5560.9,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qqll",3319.6,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qq",2948.9,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqe_EPA",287.8,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqe_BS",1268.6,nominalLuminosity*egammaLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqe_EPA",287.8,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqe_BS",1267.3,nominalLuminosity*gammaeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqnu_EPA",54.2,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqnu_BS",262.5,nominalLuminosity*egammaLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqnu_EPA",54.2,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqnu_BS",262.3,nominalLuminosity*gammaeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_EPA_EPA",402.7,nominalLuminosity*eeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_EPA_BS",2423.1,nominalLuminosity*egammaLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_BS_EPA",2420.6,nominalLuminosity*gammaeLuminosityRatio,3000,18,false,false);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_BS_BS",13050.3,nominalLuminosity*gammagammaLuminosityRatio,3000,18,false,false);

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

    TMVAClassifier3000 *pTMVAClassifier3000 = new TMVAClassifier3000(sigProcesses, bkgProcesses);
}

//=====================================================================

TMVAClassifier3000::TMVAClassifier3000(ProcessVector sigProcesses, ProcessVector bkgProcesses)
{
    TString outfileName( "TMVA_3000GeV.root" );
    TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

    // Event
//    factory->AddVariable( "NPfos := NParticlesJet1 + NParticlesJet2 + NParticlesJet3 + NParticlesJet4", "Number of PFOs", "", 'I');
    factory->AddVariable( "NParticlesJet1", "Number of PFOs Jet 1", "", 'I');
    factory->AddVariable( "NParticlesJet2", "Number of PFOs Jet 2", "", 'I');
    factory->AddVariable( "NParticlesJet3", "Number of PFOs Jet 3", "", 'I');
    factory->AddVariable( "NParticlesJet4", "Number of PFOs Jet 4", "", 'I');
//    factory->AddVariable( "NChargedPfos := NChargedParticlesJet1 + NChargedParticlesJet2 + NChargedParticlesJet3 + NChargedParticlesJet4", "Number of Charged PFOs", "", 'I');
//~~    factory->AddVariable( "HighestEnergyPfoPDG", "Highest Energy Pfo PDG", "", 'I');
    factory->AddVariable( "TransverseMomentum", "Transverse Momentum", "GeV", 'D');
//    factory->AddVariable( "TransverseEnergy", "Transverse Energy", "GeV", 'D');
//~~    factory->AddVariable( "CosThetaMissing", "Cos Theta Of Missing Momentum", "", 'D');
    factory->AddVariable( "CosThetaMostEnergeticTrack", "Cosine Theta Of Most Energetic Track", "", 'D');
//~~    factory->AddVariable( "y12", "Jet Clustering Parameter Y12", "", 'D');
//~~    factory->AddVariable( "y23", "Jet Clustering Parameter Y23", "", 'D');
    factory->AddVariable( "y34", "Jet Clustering Parameter Y34", "", 'D');
    factory->AddVariable( "y45", "Jet Clustering Parameter Y45", "", 'D');
//~~    factory->AddVariable( "y56", "Jet Clustering Parameter Y56", "", 'D');
//~~    factory->AddVariable( "y67", "Jet Clustering Parameter Y67", "", 'D');
//    factory->AddVariable( "InvariantMassSystem", "Invariant Mass of the System", "GeV", 'D');
//~~    factory->AddVariable( "PrincipleThrustValue", "PrincipleThrustValue", "", 'D');
//    factory->AddVariable( "MajorThrustValue", "MajorThrustValue", "", 'D');
//    factory->AddVariable( "MinorThrustValue", "MinorThrustValue", "", 'D');
    factory->AddVariable( "Sphericity", "Sphericity", "", 'D');
//~~    factory->AddVariable( "Aplanarity", "Aplanarity", "", 'D');
    factory->AddVariable( "(HighestEnergyElectronEnergy<10000)*HighestEnergyElectronEnergy", "Highest Energy Electron Energy", "GeV", 'D');
//    factory->AddVariable( "(HighestEnergyElectronMomentum<10000)*HighestEnergyElectronMomentum", "Highest Energy Electron Momentum", "GeV", 'D');
//    factory->AddVariable( "(HighestEnergyElectronTransverseMomentum<10000)*HighestEnergyElectronTransverseMomentum", "Highest Energy Electron Transverse Momentum", "GeV", 'D');
//    factory->AddVariable( "(HighestEnergyMuonEnergy<10000)*HighestEnergyMuonEnergy", "Highest Energy Muon Energy", "GeV", 'D');
//    factory->AddVariable( "(HighestEnergyMuonMomentum<10000)*HighestEnergyMuonMomentum", "Highest Energy Muon Momentum", "GeV", 'D');
//    factory->AddVariable( "(HighestEnergyMuonTransverseMomentum<10000)*HighestEnergyMuonTransverseMomentum", "Highest Energy Muon Transverse Momentum", "GeV", 'D');
    factory->AddVariable( "(HighestEnergyPfoEnergy<10000)*HighestEnergyPfoEnergy", "Highest Energy Pfo Energy", "GeV", 'D');
//    factory->AddVariable( "(HighestEnergyPfoMomentum<10000)*HighestEnergyPfoMomentum", "Highest Energy Pfo Momentum", "GeV", 'D');
//    factory->AddVariable( "(HighestEnergyPfoTransverseMomentum<10000)*HighestEnergyPfoTransverseMomentum", "Highest Energy Pfo Transverse Momentum", "GeV", 'D');

    // Bosons
//    factory->AddVariable( "NPfosBosonSyn1", "Number of PFOs in Boson 1", "", 'I');
//    factory->AddVariable( "NPfosBosonSyn2", "Number of PFOs in Boson 2", "", 'I');
    factory->AddVariable( "EnergyBosonSyn1", "Energy Boson 1", "GeV", 'D');
    factory->AddVariable( "EnergyBosonSyn2", "Energy Boson 2", "GeV", 'D');
//    factory->AddVariable( "MomentumBosonSyn1", "Momentum Boson 1", "GeV", 'D');
//    factory->AddVariable( "MomentumBosonSyn2", "Momentum Boson 2", "GeV", 'D');
//    factory->AddVariable( "TransverseMomentumBosonSyn1", "Transverse Momentum Boson 1", "GeV", 'D');
//    factory->AddVariable( "TransverseMomentumBosonSyn2", "Transverse Momentum Boson 2", "GeV", 'D');
//    factory->AddVariable( "CosThetaBosonSyn1", "Cos Theta Boson 1", "GeV", 'D');
//    factory->AddVariable( "CosThetaBosonSyn2", "Cos Theta Boson 2", "GeV", 'D');
//    factory->AddVariable( "TransverseEnergyBosonSyn1", "Transverse Energy Boson 1", "GeV", 'D');
//    factory->AddVariable( "TransverseEnergyBosonSyn2", "Transverse Energy Boson 2", "GeV", 'D');
    factory->AddVariable( "AcolinearityBosonsSyn", "Acolinearity Bosons", "", 'D');
    factory->AddVariable( "InvariantMassSynBoson1", "Invariant Mass Boson 1", "GeV", 'D');
    factory->AddVariable( "InvariantMassSynBoson2", "Invariant Mass Boson 2", "GeV", 'D');
//    factory->AddVariable( "MaxBTagForBosonSyn1", "Max B Tag Boson 1", "", 'D');
//    factory->AddVariable( "MinBTagForBosonSyn1", "Min B Tag Boson 1", "", 'D');
//    factory->AddVariable( "MaxBTagForBosonSyn2", "Max B Tag Boson 2", "", 'D');
//    factory->AddVariable( "MinBTagForBosonSyn2", "Min B Tag Boson 2", "", 'D');
//    factory->AddVariable( "MaxCTagForBosonSyn1", "Max C Tag Boson 1", "", 'D');
//    factory->AddVariable( "MinCTagForBosonSyn1", "Min C Tag Boson 1", "", 'D');
//    factory->AddVariable( "MaxCTagForBosonSyn2", "Max C Tag Boson 2", "", 'D');
//    factory->AddVariable( "MinCTagForBosonSyn2", "Min C Tag Boson 2", "", 'D');

    // Jets
//~~    factory->AddVariable( "AcolinearityJetsSyn1", "Acolinearity Jets Boson 1", "", 'D');
//~~    factory->AddVariable( "AcolinearityJetsSyn2", "Acolinearity Jets Boson 2", "", 'D');
//    factory->AddVariable( "EnergyJet1", "Energy Jet 1", "GeV", 'D');
//    factory->AddVariable( "EnergyJet2", "Energy Jet 2", "GeV", 'D');
//    factory->AddVariable( "EnergyJet3", "Energy Jet 3", "GeV", 'D');
//    factory->AddVariable( "EnergyJet4", "Energy Jet 4", "GeV", 'D');
//    factory->AddVariable( "MomentumJet1", "Momentum Jet 1", "GeV", 'D');
//    factory->AddVariable( "MomentumJet2", "Momentum Jet 2", "GeV", 'D');
//    factory->AddVariable( "MomentumJet3", "Momentum Jet 3", "GeV", 'D');
//    factory->AddVariable( "MomentumJet4", "Momentum Jet 4", "GeV", 'D');
//    factory->AddVariable( "TransverseMomentumJet1", "Transverse Momentum Jet 1", "GeV", 'D');
//    factory->AddVariable( "TransverseMomentumJet2", "Transverse Momentum Jet 2", "GeV", 'D');
//    factory->AddVariable( "TransverseMomentumJet3", "Transverse Momentum Jet 3", "GeV", 'D');
//    factory->AddVariable( "TransverseMomentumJet4", "Transverse Momentum Jet 4", "GeV", 'D');
//    factory->AddVariable( "CosThetaJet1", "Cos Theta Jet 1", "", 'D');
//    factory->AddVariable( "CosThetaJet2", "Cos Theta Jet 2", "", 'D');
//    factory->AddVariable( "CosThetaJet3", "Cos Theta Jet 3", "", 'D');
//    factory->AddVariable( "CosThetaJet4", "Cos Theta Jet 4", "", 'D');
//    factory->AddVariable( "BTagForJet1", "B Tag Jet 1", "", 'D');
//    factory->AddVariable( "BTagForJet2", "B Tag Jet 2", "", 'D');
//    factory->AddVariable( "BTagForJet3", "B Tag Jet 3", "", 'D');
//    factory->AddVariable( "BTagForJet4", "B Tag Jet 4", "", 'D');
//    factory->AddVariable( "CTagForJet1", "C Tag Jet 1", "", 'D');
//    factory->AddVariable( "CTagForJet2", "C Tag Jet 2", "", 'D');
//    factory->AddVariable( "CTagForJet3", "C Tag Jet 3", "", 'D');
//    factory->AddVariable( "CTagForJet4", "C Tag Jet 4", "", 'D');

    for (ProcessVector::iterator itPro = sigProcesses.begin(); itPro != sigProcesses.end(); itPro++)
    {
        const Process *pSigProcess(*itPro); 
        TChain *pTrainingTChain(pSigProcess->GetTrainingTChain()); 
        float weight(pSigProcess->GetTrainingProcessWeight());
        factory->AddSignalTree(pTrainingTChain, weight);
    }

    for (ProcessVector::iterator itPro = bkgProcesses.begin(); itPro != bkgProcesses.end(); itPro++)
    {
        const Process *pBkgProcess(*itPro);
        TChain *pTrainingTChain(pBkgProcess->GetTrainingTChain());
        float weight(pBkgProcess->GetTrainingProcessWeight());
        factory->AddBackgroundTree(pTrainingTChain, weight);
    }

    TCut mycuts = "TransverseMomentum>100 && TransverseMomentum<10000 && NumberOfIsolatedLeptons==0"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
//~~    TCut mycuts = "TransverseMomentum>100 && TransverseMomentum<10000 && InvariantMassSystem>200 && InvariantMassSystem<10000 && NumberOfIsolatedLeptons==0"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
    TCut mycutb = "TransverseMomentum>100 && TransverseMomentum<10000 && NumberOfIsolatedLeptons==0"; // for example: TCut mycutb = "abs(var1)<0.5";
//~~    TCut mycutb = "TransverseMomentum>100 && TransverseMomentum<10000 && InvariantMassSystem>200 && InvariantMassSystem<10000 && NumberOfIsolatedLeptons==0"; // for example: TCut mycutb = "abs(var1)<0.5";

    factory->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees3000_MaxDepth3_NCuts25_3000GeV", "!H:!V:NTrees=3000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );

/*
    factory->BookMethod( TMVA::Types::kCuts, "Cuts_3000GeV", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
    factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood_3000GeV", "H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
    factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix_3000GeV", "!H:!V" );
    factory->BookMethod( TMVA::Types::kFisher, "Fisher_3000GeV", "H:!V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
    factory->BookMethod( TMVA::Types::kMLP, "MLP_3000GeV", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
    factory->BookMethod( TMVA::Types::kKNN, "KNN_3000GeV", "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
*/

/*
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees3000_MaxDepth3_NCuts25_3000GeV", "!H:!V:NTrees=3000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees2000_MaxDepth3_NCuts25_3000GeV", "!H:!V:NTrees=2000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees4000_MaxDepth3_NCuts25_3000GeV", "!H:!V:NTrees=4000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees3000_MaxDepth2_NCuts25_3000GeV", "!H:!V:NTrees=3000:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees3000_MaxDepth4_NCuts25_3000GeV", "!H:!V:NTrees=3000:MinNodeSize=2.5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=25" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees3000_MaxDepth3_NCuts20_3000GeV", "!H:!V:NTrees=3000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_NTrees3000_MaxDepth3_NCuts30_3000GeV", "!H:!V:NTrees=3000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30" );
*/

/*
 * NTrees
 * MaxDepth
 * nCuts // Kind of number of bins in phase space
 */

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
