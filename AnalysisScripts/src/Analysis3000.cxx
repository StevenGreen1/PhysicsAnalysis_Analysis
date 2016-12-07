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
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_nunuqqqq",22.16,1500,3000,11);

/*
    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_lnuqqqq",115.3,1500,3000,9);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_llqqqq",169.3,1500,3000,9);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_qqqq",,1500,3000,9);

    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqq",,1500,3000,9);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_lnuqq",,1500,3000,9);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_qqll",,1500,3000,9);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_qq",,1500,3000,9);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","egamma_qqqqe_EPA",,1500,3000,9);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","egamma_qqqqe_BS",,1500,3000,9);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammae_qqqqe_EPA",,1500,3000,9);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammae_qqqqe_BS",,1500,3000,9);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","egamma_qqqqnu_EPA",,1500,3000,9);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","egamma_qqqqnu_BS",,1500,3000,9);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammae_qqqqnu_EPA",,1500,3000,9);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammae_qqqqnu_BS",,1500,3000,9);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammagamma_qqqq_EPA_EPA",,1500,3000,9);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammagamma_qqqq_EPA_BS",,1500,3000,9);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammagamma_qqqq_BS_EPA",,1500,3000,9);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","gammagamma_qqqq_BS_BS",,1500,3000,9);
*/

    std::vector<const Process*> processes;

    processes.push_back(pProcess_ee_nunuqqqq);
/*
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
*/
    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);
    pPreSelectionSemiFinal->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelectionSemiFinal->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelectionSemiFinal->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelectionSemiFinal->ApplyNIsolatedLeptonCut(0, 0);

    PostMVASelection *pPostMVASelectionSelected = new PostMVASelection(processes, pPreSelectionSemiFinal);
    pPostMVASelectionSelected->ApplyBDTCut(0.0641, 10000.0);
    pPostMVASelectionSelected->MakeWeightList(); // <- Must call to get list of events needing weights for fitting

//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, pPreSelectionSemiFinal, pPostMVASelectionSelected);

    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pPostMVASelectionSelected, 3000);

//    Fit *fit = new Fit(processes, pCouplingAnalysis);
//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes);
//    MakeSimplePlots *makePlots = new MakeSimplePlots(processes);
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
