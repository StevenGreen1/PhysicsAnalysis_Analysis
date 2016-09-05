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

    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",22.16,1500,1400,3);
    //const Process *pProcess_CLIC_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","CLIC_ee_nunuqqqq",24.7,1500,1400,3); // <-CLIC

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqqqq",115.3,1500,1400,3);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_llqqqq",71.7,1500,1400,3);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqqq",1328.1,1500,1400,3);

    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqq",933.9,1500,1400,3);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqq",4309.7,1500,1400,3);
    const Process *pProcess_ee_ll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_ll",2725.8,1500,1400,3);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qq",4009.5,1500,1400,3);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_EPA",287.1,1500,1400,3);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_BS",1160.7,1500,1400,3);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_EPA",286.9,1500,1400,3);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_BS",1156.3,1500,1400,3);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_EPA",32.6,1500,1400,3);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_BS",136.9,1500,1400,3);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_EPA",32.6,1500,1400,3);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_BS",136.4,1500,1400,3);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_EPA",753.0,1500,1400,3);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_BS",4034.8,1500,1400,3);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_EPA",4018.7,1500,1400,3);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_BS",4009.5,1500,1400,3);

    ProcessVector sigProcesses;
    ProcessVector bkgProcesses;

    sigProcesses.push_back(pProcess_ee_nunuqqqq);
//    processes.push_back(pProcess_CLIC_ee_nunuqqqq);

    bkgProcesses.push_back(pProcess_ee_lnuqqqq);
    bkgProcesses.push_back(pProcess_ee_llqqqq);
    bkgProcesses.push_back(pProcess_ee_qqqq);

    bkgProcesses.push_back(pProcess_ee_nunuqq);
    bkgProcesses.push_back(pProcess_ee_lnuqq);
    bkgProcesses.push_back(pProcess_ee_ll);
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
    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

//    factory->AddVariable( "myvar1 := var1+var2", 'F' );
//    factory->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'F' );
//    factory->AddVariable( "var3",                "Variable 3", "units", 'F' );
//    factory->AddVariable( "var4",                "Variable 4", "units", 'F' );

    factory->AddVariable( "RecoilMass", "Recoil Mass", "GeV", 'F');
    factory->AddVariable( "TransverseMomentum", "Transverse Momentum", "GeV", 'F');
    factory->AddVariable( "TransverseEnergy", "Transverse Energy", "GeV", 'F');
    factory->AddVariable( "CosThetaMissing", "Cosine Theta Of Missing Momentum", "", 'F');
    factory->AddVariable( "CosThetaMostEnergeticTrack", "Cosine Theta Of Most Energetic Track", "", 'F');
    factory->AddVariable( "y34", "Jet Clustering Parameter Y34", "", 'F');
    factory->AddVariable( "InvariantMassSystem", "Invariant Mass of the System", "GeV", 'F');
    factory->AddVariable( "CosThetaStarWBosons", "Cosine Theta Star of W Boson with W Pairing", "", 'F');
    factory->AddVariable( "CosThetaStarZBosons", "Cosine Theta Star of Z Boson with Z Pairing", "", 'F');

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

    TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
    TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";



/*
    TString signalRootFiles = "/r06/lc/sg568/PhysicsAnalysis/MarlinJobs/Detector_Model_clic_ild_cdr/Reconstruction_Variant_clic_ild_cdr_ggHadBkg/ee_nunuqqqq/1400GeV/DetModel_clic_ild_cdr_RecoVar_clic_ild_cdr_ggHadBkg_ee_nunuqqqq_1400GeV_GenNumber_*_Analysis_3_Selected.root";

    const float signalXs(22.16);
    const float luminosity(1500);

    TChain *pTChainSig = new TChain("SelectionProcessorTree");
    pTChainSig->Add(signalRootFiles);

    const float bkgXs(115.3);

    TString backgroundRootFiles = "/r06/lc/sg568/PhysicsAnalysis/MarlinJobs/Detector_Model_clic_ild_cdr/Reconstruction_Variant_clic_ild_cdr_ggHadBkg/ee_lnuqqqq/1400GeV/ProdID_5594_ee_lnuqqqq_1400GeV_Analysis_3_Number_*_Of_7531_Selected.root";
    TChain *pTChainBkg = new TChain("SelectionProcessorTree");
    pTChainBkg->Add(backgroundRootFiles);

    // --- Register the training and test trees

    // global event weights per tree (see below for setting event-wise weights)
    Double_t signalWeight     = 2 * signalXs * luminosity / pTChainSig->GetEntries(); //1.0; // Cross section x luminosity / number of events 
    Double_t backgroundWeight = 2 * bkgXs * luminosity / pTChainSig->GetEntries(); //1.0; // Cross section x luminosity / number of events (x2 for cheating thing)

    // You can add an arbitrary number of signal or background trees
    factory->AddSignalTree    ( pTChainSig,     signalWeight     );
    factory->AddBackgroundTree( pTChainBkg,     backgroundWeight );
*/
    // Set individual event weights (the variables must exist in the original TTree)
    //    for signal    : factory->SetSignalWeightExpression    ("weight1*weight2");
    //    for background: factory->SetBackgroundWeightExpression("weight1*weight2");
    //factory->SetBackgroundWeightExpression("weight");

    // Apply additional cuts on the signal and background samples (can be different)
    TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
    TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

    // Tell the factory how to use the training and testing events
    //
    // If no numbers of events are given, half of the events in the tree are used
    // for training, and the other half for testing:
    //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
    // To also specify the number of testing events, use:
    //    factory->PrepareTrainingAndTestTree( mycut,
    //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
    factory->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

    factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

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
