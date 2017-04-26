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

    int nEvtsStart(0);
    int nEvtsEnd(0);
    std::string outputPath("");

    if (argc == 4)
    {
        nEvtsStart = atoi(argv[1]);
        nEvtsEnd = atoi(argv[2]);
        outputPath = argv[3];
    }
    else if (argc != 1)
    {
        std::cout << "Unexpected number of arguments.  Please check." << std::endl;
        return 0;
    }

    // Energy 1400 GeV
    const float nominalLuminosity(1500.f);
    const float eeLuminosityRatio(1.f);
    const float egammaLuminosityRatio(0.75f);
    const float gammaeLuminosityRatio(0.75f);
    const float gammagammaLuminosityRatio(0.64f);

    const bool quickLoad(true); // i.e. post MVA needed only
    const bool trivialMVA(false); // i.e. files concatenated, but bdt is deprecated 

    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",24.7,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_lnuqqqq",110.4,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_llqqqq",62.1,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_qqqq",1245.1,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqq",787.7,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_lnuqq",4309.7,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_qqll",2725.8,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_qq",4009.5,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqe_EPA",287.1,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqe_BS",1160.7,nominalLuminosity*egammaLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqe_EPA",286.9,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqe_BS",1156.3,nominalLuminosity*gammaeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqnu_EPA",32.6,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqnu_BS",136.9,nominalLuminosity*egammaLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqnu_EPA",32.6,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqnu_BS",136.4,nominalLuminosity*gammaeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_EPA_EPA",753.0,nominalLuminosity*eeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_EPA_BS",4034.8,nominalLuminosity*egammaLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_BS_EPA",4018.7,nominalLuminosity*gammaeLuminosityRatio,1400,18,quickLoad,trivialMVA);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_BS_BS",21406.2,nominalLuminosity*gammagammaLuminosityRatio,1400,18,quickLoad,trivialMVA);

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
    std::cout << "Transverse Momentum Cut - 100GeV and NIsoLep = 0." << std::endl;
    PreSelection *pPreSelection10 = new PreSelection(processes);
    pPreSelection10->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelection10->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelection10->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection10->ApplyNIsolatedLeptonCut(0, 0);
    pPreSelection10->ApplyPreSelection();
    MakeDerivedPlots *pMakeDerivedPlots4 = new MakeDerivedPlots(processes, "1400GeV_Pt_gt100GeV_NIsoLep_eq0_Cuts", pPreSelection10);
*/

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);
    pPreSelectionSemiFinal->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelectionSemiFinal->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelectionSemiFinal->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelectionSemiFinal->ApplyNIsolatedLeptonCut(0, 0);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes, pPreSelectionSemiFinal);

    // Preselection Numbers
    pPostMVASelection->ApplyBDTCut(-10000.0, 10000.0); // Remove for condor jobs
    std::cout << "Preselection Only" << std::endl; // Remove for condor jobs
    pPostMVASelection->ApplyPostMVASelection(); // Remove for condor jobs

    // MVA Numbers
    pPostMVASelection->ApplyBDTCut(0.0540, 10000.0);
    std::cout << "Post MVA and Preselection" << std::endl; // Remove for condor jobs
    pPostMVASelection->ApplyPostMVASelection(); // Remove for condor jobs

    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting
    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, "1400GeV_PostPreSelection_PostMVA_Cuts", pPreSelectionSemiFinal, pPostMVASelection);

/*
    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pPostMVASelection, 1400);

    BuildIndividualDistributions *pBuildIndividualDistributions = new BuildIndividualDistributions(processes, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "SPFOs_kt_0p90_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV_Final", outputPath);
    pBuildIndividualDistributions->SetNBins(10);
    pBuildIndividualDistributions->BuildDistribution(true); // Bool is with or without background, adjusts scan.
    delete pBuildIndividualDistributions;
*/
/*
    BuildDistributions *pBuildDistributions = new BuildDistributions(processes, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "SPFOs_kt_0p90_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV_Final", outputPath);
    pBuildDistributions->SetNBins(10);
    pBuildDistributions->BuildDistribution(true); // Bool is with or without background, adjusts scan.
    delete pBuildDistributions;

//    delete pCouplingAnalysis;
    delete pPreSelectionSemiFinal, pPostMVASelection;
    delete pProcess_ee_nunuqqqq, pProcess_ee_lnuqqqq, pProcess_ee_llqqqq, pProcess_ee_qqqq, pProcess_ee_nunuqq, pProcess_ee_lnuqq, pProcess_ee_qqll, pProcess_ee_qq, pProcess_egamma_qqqqe_EPA, pProcess_egamma_qqqqe_BS, pProcess_gammae_qqqqe_EPA, pProcess_gammae_qqqqe_BS, pProcess_egamma_qqqqnu_EPA, pProcess_egamma_qqqqnu_BS, pProcess_gammae_qqqqnu_EPA, pProcess_gammae_qqqqnu_BS, pProcess_gammagamma_qqqq_EPA_EPA, pProcess_gammagamma_qqqq_EPA_BS, pProcess_gammagamma_qqqq_BS_EPA, pProcess_gammagamma_qqqq_BS_BS;
*/
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
