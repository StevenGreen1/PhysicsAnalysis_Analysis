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
//#include "Fit.h"
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

    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",24.7,1500,1400,18);

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_lnuqqqq",110.4,1500,1400,18);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_llqqqq",62.1,1500,1400,18);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_qqqq",1245.1,1500,1400,18);

    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqq",787.7,1500,1400,18);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_lnuqq",4309.7,1500,1400,18);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_qqll",2725.8,1500,1400,18);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_qq",4009.5,1500,1400,18);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqe_EPA",287.1,1500,1400,18);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqe_BS",1160.7,1500,1400,18);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqe_EPA",286.9,1500,1400,18);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqe_BS",1156.3,1500,1400,18);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqnu_EPA",32.6,1500,1400,18);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","egamma_qqqqnu_BS",136.9,1500,1400,18);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqnu_EPA",32.6,1500,1400,18);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammae_qqqqnu_BS",136.4,1500,1400,18);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_EPA_EPA",753.0,1500,1400,18);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_EPA_BS",4034.8,1500,1400,18);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_BS_EPA",4018.7,1500,1400,18);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","gammagamma_qqqq_BS_BS",21406.2,1500,1400,18);

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
    std::cout << "No Cuts." << std::endl;
    PreSelection *pPreSelection1 = new PreSelection(processes);
    pPreSelection1->ApplyTransverseMomentumCut(0.0, 10000.0);
    pPreSelection1->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelection1->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelection1->ApplyNIsolatedLeptonCut(0, 10000);
    pPreSelection1->ApplyPreSelection();

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
*/

/*
    PreSelection *pPreSelectionCut1 = new PreSelection(processes);
    pPreSelectionCut1->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelectionCut1->ApplyInvariantMassCut(0.0, 10000.0);
    pPreSelectionCut1->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelectionCut1->ApplyNIsolatedLeptonCut(0, 10000);
    MakeDerivedPlots *makePlotsCut1 = new MakeDerivedPlots(processes, "1400GeV_Pt_gt100GeV_Cuts", pPreSelectionCut1);
    delete pPreSelectionCut1, makePlotsCut1;

    PreSelection *pPreSelectionCut2 = new PreSelection(processes);
    pPreSelectionCut2->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelectionCut2->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelectionCut2->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelectionCut2->ApplyNIsolatedLeptonCut(0, 10000);
    MakeDerivedPlots *makePlotsCut2 = new MakeDerivedPlots(processes, "1400GeV_Pt_gt100GeV_MVis_gt200GeV_Cuts", pPreSelectionCut2);
    delete pPreSelectionCut2, makePlotsCut2;

    PreSelection *pPreSelectionCut3 = new PreSelection(processes);
    pPreSelectionCut3->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelectionCut3->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelectionCut3->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelectionCut3->ApplyNIsolatedLeptonCut(0, 0);
    MakeDerivedPlots *makePlotsCut3 = new MakeDerivedPlots(processes, "1400GeV_Pt_gt100GeV_MVis_gt200GeV_NIsoLep_eq0_Cuts", pPreSelectionCut3);
    delete pPreSelectionCut3, makePlotsCut3;
*/

//    pPreSelectionSemiFinal->ApplyTransverseMomentumCut(100.0, 10000.0);
//    pPreSelectionSemiFinal->ApplyInvariantMassCut(200.0, 10000.0);
//    pPreSelectionSemiFinal->ApplyBosonInvariantMassCut(0.0, 10000.0);
//    pPreSelectionSemiFinal->ApplyNIsolatedLeptonCut(0, 0);

/*
    PostMVASelection *pPostMVASelectionSelected = new PostMVASelection(processes, pPreSelectionSemiFinal);
    pPostMVASelectionSelected->ApplyBDTCut(0.0641, 10000.0);
    pPostMVASelectionSelected->MakeWeightList(); // <- Must call to get list of events needing weights for fitting

//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, pPreSelectionSemiFinal, pPostMVASelectionSelected);

    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pPostMVASelectionSelected, 1400);

//    Fit *pFit = new Fit(processes, pCouplingAnalysis);
//    pFit->MyFit();
//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes);
//    MakeSimplePlots *makePlots = new MakeSimplePlots(processes);

    delete pPreSelectionSemiFinal, pPostMVASelectionSelected, pCouplingAnalysis;
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
