/**
 *  @file   AnalysisScripts/src/Analysis.cc
 * 
 *  @brief  Implementation of the anomalous coupling physics analysis processor.
 * 
 *  $Log: $
 */

#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "CouplingAnalysis.h"
#include "BuildDistributions.h"
#include "BuildIndividualDistributions.h"
#include "MakeDerivedPlots.h"
#include "MakeSimplePlots.h"
#include "PostMVASelection.h"
#include "PreSelection.h"
#include "Process.h"

template <class T>
std::string NumberToString(T Number);

//=====================================================================
// Luminoscity is 1.5 ab-1 = 1500 fb-1 at 1.4 TeV

int main(int argc, char **argv)
{
    srand(time(0));
    gStyle->SetOptStat(0);

    const int nEvtsStart(atoi(argv[1]));
    const int nEvtsEnd(atoi(argv[2]));
    const std::string outputPath(argv[3]);

    // Energy 3000 GeV
    float nominalLuminosity(2000);
    float eeLuminosityRatio(1.0);
    float egammaLuminosityRatio(0.79);
    float gammaeLuminosityRatio(0.79);
    float gammagammaLuminosityRatio(0.69);

    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_lnuqqqq",106.6,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_llqqqq",169.3,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qqqq",546.5,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqq",1317.5,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_lnuqq",5560.9,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qqll",3319.6,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qq",2948.9,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqe_EPA",287.8,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqe_BS",1268.6,nominalLuminosity*egammaLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqe_EPA",287.8,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqe_BS",1267.3,nominalLuminosity*gammaeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqnu_EPA",54.2,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqnu_BS",262.5,nominalLuminosity*egammaLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqnu_EPA",54.2,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqnu_BS",262.3,nominalLuminosity*gammaeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_EPA_EPA",402.7,nominalLuminosity*eeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_EPA_BS",2423.1,nominalLuminosity*egammaLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_BS_EPA",2420.6,nominalLuminosity*gammaeLuminosityRatio,3000,18,true,false);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_BS_BS",13050.3,nominalLuminosity*gammagammaLuminosityRatio,3000,18,true,false);

    std::vector<const Process*> processes;

    processes.push_back(pProcess_ee_nunuqqqq);

    processes.push_back(pProcess_ee_lnuqqqq);
    processes.push_back(pProcess_ee_llqqqq);
    processes.push_back(pProcess_ee_qqqq);

    processes.push_back(pProcess_ee_nunuqq);
    processes.push_back(pProcess_ee_lnuqq);
    processes.push_back(pProcess_ee_qqll);
    processes.push_back(pProcess_ee_qq);

    processes.push_back(pProcess_egamma_qqqqe_EPA);
    processes.push_back(pProcess_egamma_qqqqe_BS);
    processes.push_back(pProcess_gammae_qqqqe_EPA);
    processes.push_back(pProcess_gammae_qqqqe_BS);

    processes.push_back(pProcess_egamma_qqqqnu_EPA);
    processes.push_back(pProcess_egamma_qqqqnu_BS);
    processes.push_back(pProcess_gammae_qqqqnu_EPA);
    processes.push_back(pProcess_gammae_qqqqnu_BS);

    processes.push_back(pProcess_gammagamma_qqqq_EPA_EPA);
    processes.push_back(pProcess_gammagamma_qqqq_EPA_BS);
    processes.push_back(pProcess_gammagamma_qqqq_BS_EPA);
    processes.push_back(pProcess_gammagamma_qqqq_BS_BS);
/*
    std::cout << "No Cuts" << std::endl;
    PreSelection *pPreSelection1 = new PreSelection(processes);
    pPreSelection1->ApplyTransverseMomentumCut(0.0, 10000.0);
    pPreSelection1->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelection1->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection1->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection1->ApplyPreSelection();
    MakeDerivedPlots *pMakeDerivedPlots1 = new MakeDerivedPlots(processes, "3000GeV_No_Cuts", pPreSelection1);

    std::cout << "Transverse Momentum Cut - 50GeV." << std::endl;
    PreSelection *pPreSelection2 = new PreSelection(processes);
    pPreSelection2->ApplyTransverseMomentumCut(50.0, 10000.0);
    pPreSelection2->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelection2->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection2->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection2->ApplyPreSelection();

    std::cout << "Transverse Momentum Cut - 100GeV." << std::endl;
    PreSelection *pPreSelection3 = new PreSelection(processes);
    pPreSelection3->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection3->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelection3->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection3->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection3->ApplyPreSelection();
    MakeDerivedPlots *pMakeDerivedPlots2 = new MakeDerivedPlots(processes, "3000GeV_Pt_gt100GeV_Cuts", pPreSelection3);

    std::cout << "Transverse Momentum Cut - 150GeV." << std::endl;
    PreSelection *pPreSelection4 = new PreSelection(processes);
    pPreSelection4->ApplyTransverseMomentumCut(150.0, 10000.0);
    pPreSelection4->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelection4->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection4->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection4->ApplyPreSelection();

    std::cout << "Transverse Momentum Cut - 100GeV and Visible Mass System - 100 GeV." << std::endl;
    PreSelection *pPreSelection5 = new PreSelection(processes);
    pPreSelection5->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection5->ApplyInvariantMassCut(100.0, 10000.0);
    pPreSelection5->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection5->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection5->ApplyPreSelection();

    std::cout << "Transverse Momentum Cut - 100GeV and Visible Mass System - 200 GeV." << std::endl;
    PreSelection *pPreSelection6 = new PreSelection(processes);
    pPreSelection6->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection6->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelection6->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection6->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection6->ApplyPreSelection();
    MakeDerivedPlots *pMakeDerivedPlots3 = new MakeDerivedPlots(processes, "3000GeV_Pt_gt100GeV_MVis_gt200GeV_Cuts", pPreSelection6);

    std::cout << "Transverse Momentum Cut - 100GeV and Visible Mass System - 300 GeV." << std::endl;
    PreSelection *pPreSelection7 = new PreSelection(processes);
    pPreSelection7->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection7->ApplyInvariantMassCut(300.0, 10000.0);
    pPreSelection7->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection7->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection7->ApplyPreSelection();

    std::cout << "Transverse Momentum Cut - 100GeV and Visible Mass System - 200 GeV and NIsoLep = 0,1,2." << std::endl;
    PreSelection *pPreSelection8 = new PreSelection(processes);
    pPreSelection8->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection8->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelection8->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection8->ApplyNIsolatedLeptonCut(0, 2);
    pPreSelection8->ApplyPreSelection();

    std::cout << "Transverse Momentum Cut - 100GeV and Visible Mass System - 200 GeV and NIsoLep = 0,1." << std::endl;
    PreSelection *pPreSelection9 = new PreSelection(processes);
    pPreSelection9->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection9->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelection9->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection9->ApplyNIsolatedLeptonCut(0, 1);
    pPreSelection9->ApplyPreSelection();

    std::cout << "Transverse Momentum Cut - 100GeV and Visible Mass System - 200 GeV and NIsoLep = 0." << std::endl;
    PreSelection *pPreSelection10 = new PreSelection(processes);
    pPreSelection10->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection10->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelection10->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection10->ApplyNIsolatedLeptonCut(0, 0);
    pPreSelection10->ApplyPreSelection();
    MakeDerivedPlots *pMakeDerivedPlots4 = new MakeDerivedPlots(processes, "3000GeV_Pt_gt100GeV_MVis_gt200GeV_NIsoLep_eq0_Cuts", pPreSelection10);
*/

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);
    pPreSelectionSemiFinal->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelectionSemiFinal->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelectionSemiFinal->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelectionSemiFinal->ApplyNIsolatedLeptonCut(0, 0);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes, pPreSelectionSemiFinal);
//    pPostMVASelection->ApplyBDTCut(-10000.0, 10000.0); // Remove for condor jobs
//    std::cout << "Preselection Only" << std::endl; // Remove for condor jobs
//    pPostMVASelection->ApplyPostMVASelection(); // Remove for condor jobs
    pPostMVASelection->ApplyBDTCut(0.0388, 10000.0);
//    std::cout << "Post MVA and Preselection" << std::endl; // Remove for condor jobs
    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting
//    pPostMVASelection->ApplyPostMVASelection(); // Remove for condor jobs
//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, "3000GeV_PostPreSelection_PostMVA_Cuts", pPreSelectionSemiFinal, pPostMVASelection);

    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pPostMVASelection, 3000);

    BuildIndividualDistributions *pBuildIndividualDistributions = new BuildIndividualDistributions(processes, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "TPFOs_kt_1p10_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_3000GeV_Final", outputPath);
    pBuildIndividualDistributions->SetNBins(10);
    pBuildIndividualDistributions->BuildDistribution(true); // Bool is with or without background, adjusts scan.
    delete pBuildIndividualDistributions;

/*
    BuildDistributions *pBuildDistributions = new BuildDistributions(processes, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "TPFOs_kt_1p10_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_3000GeV_Final", outputPath);
    pBuildDistributions->SetNBins(10);
    pBuildDistributions->BuildDistribution(true); // Bool is with or without background, adjusts scan.
    delete pBuildDistributions;
*/

    delete pCouplingAnalysis;
    delete pPreSelectionSemiFinal, pPostMVASelection;
    delete pProcess_ee_nunuqqqq, pProcess_ee_lnuqqqq, pProcess_ee_llqqqq, pProcess_ee_qqqq, pProcess_ee_nunuqq, pProcess_ee_lnuqq, pProcess_ee_qqll, pProcess_ee_qq, pProcess_egamma_qqqqe_EPA, pProcess_egamma_qqqqe_BS, pProcess_gammae_qqqqe_EPA, pProcess_gammae_qqqqe_BS, pProcess_egamma_qqqqnu_EPA, pProcess_egamma_qqqqnu_BS, pProcess_gammae_qqqqnu_EPA, pProcess_gammae_qqqqnu_BS, pProcess_gammagamma_qqqq_EPA_EPA, pProcess_gammagamma_qqqq_EPA_BS, pProcess_gammagamma_qqqq_BS_EPA, pProcess_gammagamma_qqqq_BS_BS;
}

//=====================================================================

template <class T>
std::string NumberToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

//=====================================================================
