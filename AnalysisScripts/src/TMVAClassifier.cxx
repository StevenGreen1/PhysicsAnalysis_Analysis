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

    // Signal, luminoscity copied from nunuqqqq final state
    //const Process *pProcess_ee_nunuww_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuww_nunuqqqq",24.7,1500,1400,3);
    //const Process *pProcess_ee_nunuzz_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuzz_nunuqqqq",24.7,1500,1400,3);
//    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",22.16,1500,1400,5);
    //const Process *pProcess_CLIC_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","CLIC_ee_nunuqqqq",24.7,1500,1400,3); // <-CLIC

    // CLIC Backgrounds

//    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqqqq",115.3,1500,1400,5);
//    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_llqqqq",71.7,1500,1400,5);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqqq",1328.1,1500,1400,5);
/*
    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqq",933.9,1500,1400,5);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqq",4309.7,1500,1400,5);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqll",2725.8,1500,1400,5);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qq",4009.5,1500,1400,5);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_EPA",287.1,1500,1400,5);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_BS",1160.7,1500,1400,5);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_EPA",286.9,1500,1400,5);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_BS",1156.3,1500,1400,5);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_EPA",32.6,1500,1400,5);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_BS",136.9,1500,1400,5);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_EPA",32.6,1500,1400,5);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_BS",136.4,1500,1400,5);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_EPA",753.0,1500,1400,5);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_BS",4034.8,1500,1400,5);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_EPA",4018.7,1500,1400,5);*/
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_BS",4009.5,1500,1400,5);

    ProcessVector sigProcesses;
    ProcessVector bkgProcesses;

//    sigProcesses.push_back(pProcess_ee_nunuqqqq);
//    processes.push_back(pProcess_CLIC_ee_nunuqqqq);
    sigProcesses.push_back(pProcess_ee_qqqq);


/*
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
    bkgProcesses.push_back(pProcess_gammagamma_qqqq_BS_EPA);*/
    bkgProcesses.push_back(pProcess_gammagamma_qqqq_BS_BS);

    TMVAClassifier *pTMVAClassifier = new TMVAClassifier(sigProcesses, bkgProcesses);
}

//=====================================================================

TMVAClassifier::TMVAClassifier(ProcessVector sigProcesses, ProcessVector bkgProcesses)
{
    TString outfileName( "TMVA.root" );
    TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

//    factory->AddVariable( "myvar1 := var1+var2", 'D' );
//    factory->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'D' );
//    factory->AddVariable( "var3",                "Variable 3", "units", 'D' );
//    factory->AddVariable( "var4",                "Variable 4", "units", 'D' );

    factory->AddVariable( "NPfos := NParticlesJet1+NParticlesJet2+NParticlesJet3+NParticlesJet4", "Numer of PFOs", "", 'I');
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
    factory->AddVariable( "CosThetaMissing", "Cosine Theta Of Missing Momentum", "", 'D');
    factory->AddVariable( "CosThetaMostEnergeticTrack", "Cosine Theta Of Most Energetic Track", "", 'D');
    factory->AddVariable( "y12", "Jet Clustering Parameter Y12", "", 'D');
    factory->AddVariable( "y23", "Jet Clustering Parameter Y23", "", 'D');
    factory->AddVariable( "y34", "Jet Clustering Parameter Y34", "", 'D');
    factory->AddVariable( "y45", "Jet Clustering Parameter Y45", "", 'D');
    factory->AddVariable( "y56", "Jet Clustering Parameter Y56", "", 'D');
    factory->AddVariable( "y67", "Jet Clustering Parameter Y67", "", 'D');
    factory->AddVariable( "InvariantMassSystem", "Invariant Mass of the System", "GeV", 'D');
    factory->AddVariable( "CosThetaStarWBosons", "Cosine Theta Star of W Boson with W Pairing", "", 'D');
    factory->AddVariable( "CosThetaStarZBosons", "Cosine Theta Star of Z Boson with Z Pairing", "", 'D');
    factory->AddVariable( "CosThetaStarWJet1", "Cosine Theta Star of Jets from W Boson 1 with W Pairing", "", 'D');
    factory->AddVariable( "CosThetaStarWJet2", "Cosine Theta Star of Jets from W Boson 2 with W Pairing", "", 'D');
    factory->AddVariable( "CosThetaStarZJet1", "Cosine Theta Star of Jets from Z Boson 1 with W Pairing", "", 'D');
    factory->AddVariable( "CosThetaStarZJet2", "Cosine Theta Star of Jets from Z Boson 2 with W Pairing", "", 'D');
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

    TCut mycuts = "InvMassWVector1>0 && InvMassWVector1<500 && InvMassWVector2>0 && InvMassWVector2<500 && InvMassZVector1>0 && InvMassZVector1<500 && InvMassZVector2>0 && InvMassZVector2<500 && TransverseMomentum>100 && TransverseMomentum<10000 && InvariantMassSystem>100 && InvariantMassSystem<10000"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
    TCut mycutb = "InvMassWVector1>0 && InvMassWVector1<500 && InvMassWVector2>0 && InvMassWVector2<500 && InvMassZVector1>0 && InvMassZVector1<500 && InvMassZVector2>0 && InvMassZVector2<500 && TransverseMomentum>100 && TransverseMomentum<10000 && InvariantMassSystem<10000 && InvariantMassSystem>100"; // for example: TCut mycutb = "abs(var1)<0.5";

    factory->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

    factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
    factory->BookMethod( TMVA::Types::kCuts, "Cuts", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
    factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood", "H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
    factory->BookMethod( TMVA::Types::kPDERS, "PDERS", "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );
    factory->BookMethod( TMVA::Types::kKNN, "KNN", "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
    factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  );

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
