/**
 *  @file   AnalysisScripts/src/Analysis.cc
 * 
 *  @brief  Implementation of the anomalous coupling physics analysis processor.
 * 
 *  $Log: $
 */

#include <memory>
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
    srand(time(0));
    gStyle->SetOptStat(0);

    // Signal, luminosity copied from nunuqqqq final state
//    const Process *pProcess_ee_nunuqqqq_1 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5","ee_nunuqqqq",22.16,1500,1400,11,true);
//    const Process *pProcess_ee_nunuqqqq_2 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
//    const Process *pProcess_ee_nunuqqqq_3 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",22.16,1500,1400,11,true);
//    const Process *pProcess_ee_nunuqqqq_4 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0","ee_nunuqqqq",22.16,1500,1400,11,true);
//    const Process *pProcess_ee_nunuqqqq_5 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_6 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,13,true);
    const Process *pProcess_ee_nunuqqqq_7 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,13,true);
//    const Process *pProcess_ee_nunuqqqq_8 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
//    const Process *pProcess_ee_nunuqqqq_9 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
/*
    std::vector<const Process*> processes_1; 
    processes_1.push_back(pProcess_ee_nunuqqqq_1);

    std::vector<const Process*> processes_2; 
    processes_2.push_back(pProcess_ee_nunuqqqq_2);

    std::vector<const Process*> processes_3; 
    processes_3.push_back(pProcess_ee_nunuqqqq_3);

    std::vector<const Process*> processes_4; 
    processes_4.push_back(pProcess_ee_nunuqqqq_4);

    std::vector<const Process*> processes_5; 
    processes_5.push_back(pProcess_ee_nunuqqqq_5);
*/
    std::vector<const Process*> processes_6;
    processes_6.push_back(pProcess_ee_nunuqqqq_6);

    std::vector<const Process*> processes_7; 
    processes_7.push_back(pProcess_ee_nunuqqqq_7);
/*
    std::vector<const Process*> processes_8; 
    processes_8.push_back(pProcess_ee_nunuqqqq_8);

    std::vector<const Process*> processes_9; 
    processes_9.push_back(pProcess_ee_nunuqqqq_9);
*/
    std::vector<const Process*> processes_all;
//    processes_all.push_back(pProcess_ee_nunuqqqq_1);
//    processes_all.push_back(pProcess_ee_nunuqqqq_2);
//    processes_all.push_back(pProcess_ee_nunuqqqq_3);
//    processes_all.push_back(pProcess_ee_nunuqqqq_4);
//    processes_all.push_back(pProcess_ee_nunuqqqq_5);
    processes_all.push_back(pProcess_ee_nunuqqqq_6);
    processes_all.push_back(pProcess_ee_nunuqqqq_7);
//    processes_all.push_back(pProcess_ee_nunuqqqq_8);
//    processes_all.push_back(pProcess_ee_nunuqqqq_9);

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes_all);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes_all, pPreSelectionSemiFinal);
    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting

//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, pPreSelectionSemiFinal, pPostMVASelection);

    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pPostMVASelection);
/*
    Fit *pFit_1 = new Fit(processes_1, pCouplingAnalysis, "SPFOs_kt_0p50_5Bins_1000000Evts_MyFit");
    pFit_1->SetNBins(5);
    pFit_1->SetNEvents(1000000);
    pFit_1->MyFit();
    delete pFit_1;

    Fit *pFit_2 = new Fit(processes_2, pCouplingAnalysis, "SPFOs_kt_0p70_5Bins_1000000Evts_MyFit");
    pFit_2->SetNBins(5);
    pFit_2->SetNEvents(1000000);
    pFit_2->MyFit();
    delete pFit_2;

    Fit *pFit_3 = new Fit(processes_3, pCouplingAnalysis, "SPFOs_kt_0p90_5Bins_1000000Evts_MyFit");
    pFit_3->SetNBins(5);
    pFit_3->SetNEvents(1000000);
    pFit_3->MyFit();
    delete pFit_3;

    Fit *pFit_4 = new Fit(processes_4, pCouplingAnalysis, "SPFOs_kt_1p00_5Bins_1000000Evts_MyFit");
    pFit_4->SetNBins(5);
    pFit_4->SetNEvents(1000000);
    pFit_4->MyFit();
    delete pFit_4;

    Fit *pFit_5 = new Fit(processes_5, pCouplingAnalysis, "SPFOs_kt_1p10_5Bins_1000000Evts_MyFit");
    pFit_5->SetNBins(5);
    pFit_5->SetNEvents(1000000);
    pFit_5->MyFit();
    delete pFit_5;
*/

    Fit *pFit_6 = new Fit(processes_6, pCouplingAnalysis, "TPFOs_kt_0p70_5Bins_1000000Evts_MyFit");
    pFit_6->SetNBins(5);
    pFit_6->SetNEvents(1000000);
    pFit_6->MyFit();
    delete pFit_6;

    Fit *pFit_7 = new Fit(processes_7, pCouplingAnalysis, "LPFOs_kt_0p70_5Bins_1000000Evts_MyFit");
    pFit_7->SetNBins(5);
    pFit_7->SetNEvents(1000000);
    pFit_7->MyFit();
    delete pFit_7;

/*
    Fit *pFit_8 = new Fit(processes_8, pCouplingAnalysis, "SPFOs_ee_kt_0p70_5Bins_1000000Evts_MyFit");
    pFit_8->SetNBins(5);
    pFit_8->SetNEvents(1000000);
    pFit_8->MyFit();
    delete pFit_8;

    Fit *pFit_9 = new Fit(processes_9, pCouplingAnalysis, "SPFOs_cam_0p70_5Bins_1000000Evts_MyFit");
    pFit_9->SetNBins(5);
    pFit_9->SetNEvents(1000000);
    pFit_9->MyFit();
    delete pFit_9;
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
