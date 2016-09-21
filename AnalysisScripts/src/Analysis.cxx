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
#include "Fit.h"
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
//    CouplingAnalysis();

    srand(time(0));

    // Signal, luminoscity copied from nunuqqqq final state
    //const Process *pProcess_ee_nunuww_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuww_nunuqqqq",24.7,1500,1400,3);
    //const Process *pProcess_ee_nunuzz_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuzz_nunuqqqq",24.7,1500,1400,3);
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",22.16,1500,1400,5);
    //const Process *pProcess_CLIC_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","CLIC_ee_nunuqqqq",24.7,1500,1400,3); // <-CLIC 

    // CLIC Backgrounds
/*
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqqqq",115.3,1500,1400,5);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_llqqqq",71.7,1500,1400,5);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqqq",1328.1,1500,1400,5);

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
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_EPA",4018.7,1500,1400,5);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_BS",4009.5,1500,1400,5);
*/
    std::vector<const Process*> processes;

    processes.push_back(pProcess_ee_nunuqqqq);
//    processes.push_back(pProcess_CLIC_ee_nunuqqqq);
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
/*
    PreSelection *pPreSelectionUsing = new PreSelection(processes);
    pPreSelectionUsing->ApplyTransverseMomentumCut(100.0,10000.0);
    pPreSelectionUsing->ApplyInvariantMassCut(100.0,10000.0);
    pPreSelectionUsing->ApplyBosonInvariantMassCut(0.0,500.0);
    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, pPreSelectionUsing);

    std::cout << "Tight" << std::endl;
    PreSelection *pPreSelectionTight = new PreSelection(processes);
    pPreSelectionTight->ApplyTransverseMomentumCut(100.0,10000.0);
    pPreSelectionTight->ApplyInvariantMassCut(100.0,10000.0);
    pPreSelectionTight->ApplyBosonInvariantMassCut(0.0, 500.0);
    pPreSelectionTight->ApplyPreSelection();

    std::cout << "Loose" << std::endl;
    PreSelection *pPreSelectionLoose = new PreSelection(processes);
    pPreSelectionLoose->ApplyTransverseMomentumCut(100.0,10000.0);
    pPreSelectionLoose->ApplyInvariantMassCut(100.0,10000.0);
    pPreSelectionLoose->ApplyBosonInvariantMassCut(0.0, 1000.0);
    pPreSelectionLoose->ApplyPreSelection();
*/
/*
    std::cout << "Selected" << std::endl;
    PreSelection *pPreSelectionSelected = new PreSelection(processes);
    pPreSelectionSelected->ApplyTransverseMomentumCut(100.0,10000.0);
    pPreSelectionSelected->ApplyInvariantMassCut(100.0,10000.0);
    pPreSelectionSelected->ApplyBosonInvariantMassCut(0.0,500.0);
    pPreSelectionSelected->ApplyPreSelection();
*/
/*
    PostMVASelection *pPostMVASelectionLoose = new PostMVASelection(processes);
    pPostMVASelectionLoose->ApplyBDTCut(0,10000.0);
    pPostMVASelectionLoose->ApplyPostMVASelection(); 

    PostMVASelection *pPostMVASelectionSelected = new PostMVASelection(processes);
    pPostMVASelectionSelected->ApplyBDTCut(0.2,10000.0);
    pPostMVASelectionSelected->ApplyPostMVASelection();

    PostMVASelection *pPostMVASelectionTight = new PostMVASelection(processes);
    pPostMVASelectionTight->ApplyBDTCut(0.4,10000.0);
    pPostMVASelectionTight->ApplyPostMVASelection();
*/
    Fit *fit = new Fit(processes);
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
