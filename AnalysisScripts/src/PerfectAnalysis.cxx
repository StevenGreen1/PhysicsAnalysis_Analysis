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
    std::shared_ptr<const Process> pProcess_ee_nunuqqqq_1(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5","ee_nunuqqqq",22.16,1500,1400,11,true)); 

/*
    const Process *pProcess_ee_nunuqqqq_2 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_3 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_4 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_5 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_6 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_7 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_8 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
    const Process *pProcess_ee_nunuqqqq_9 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true);
*/
    std::vector<std::shared_ptr<const Process> > processes_1; 

    processes_1.push_back(pProcess_ee_nunuqqqq_1);
/*
    std::vector<const Process*> processes_2; 
    processes_2.push_back(pProcess_ee_nunuqqqq_2);

    std::vector<const Process*> processes_3; 
    processes_3.push_back(pProcess_ee_nunuqqqq_3);

    std::vector<const Process*> processes_4; 
    processes_4.push_back(pProcess_ee_nunuqqqq_4);

    std::vector<const Process*> processes_5; 
    processes_5.push_back(pProcess_ee_nunuqqqq_5);

    std::vector<const Process*> processes_6;
    processes_6.push_back(pProcess_ee_nunuqqqq_6);

    std::vector<const Process*> processes_7; 
    processes_7.push_back(pProcess_ee_nunuqqqq_7);

    std::vector<const Process*> processes_8; 
    processes_8.push_back(pProcess_ee_nunuqqqq_8);

    std::vector<const Process*> processes_9; 
    processes_9.push_back(pProcess_ee_nunuqqqq_9);
*/

//    std::vector<const Process*> processes_all;
    std::vector<std::shared_ptr<const Process> > processes_all;
    processes_all.push_back(pProcess_ee_nunuqqqq_1);
/*
    processes_all.push_back(pProcess_ee_nunuqqqq_2);
    processes_all.push_back(pProcess_ee_nunuqqqq_3);
    processes_all.push_back(pProcess_ee_nunuqqqq_4);
    processes_all.push_back(pProcess_ee_nunuqqqq_5);
    processes_all.push_back(pProcess_ee_nunuqqqq_6);
    processes_all.push_back(pProcess_ee_nunuqqqq_7);
    processes_all.push_back(pProcess_ee_nunuqqqq_8);
    processes_all.push_back(pProcess_ee_nunuqqqq_9);
*/
    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes_all);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes_all, pPreSelectionSemiFinal);
    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting

//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, pPreSelectionSemiFinal, pPostMVASelection);

    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pPostMVASelection);

    Fit *fit_1 = new Fit(processes_1, pCouplingAnalysis, "SPFOs_kt_0p50");
    std::unique_ptr<Fit> pFit1(new Fit(processes_1, pCouplingAnalysis, "SPFOs_kt_0p50"));

/*
    Fit *fit_2 = new Fit(processes_2, pCouplingAnalysis, "SPFOs_kt_0p70");
    delete fit_2;
    Fit *fit_3 = new Fit(processes_3, pCouplingAnalysis, "SPFOs_kt_0p90");
    delete fit_3;
    Fit *fit_4 = new Fit(processes_4, pCouplingAnalysis, "SPFOs_kt_1p00");
    delete fit_4;
    Fit *fit_5 = new Fit(processes_5, pCouplingAnalysis, "SPFOs_kt_1p10");
    delete fit_5;
    Fit *fit_6 = new Fit(processes_6, pCouplingAnalysis, "TPFOs_kt_0p70");
    delete fit_6;
    Fit *fit_7 = new Fit(processes_7, pCouplingAnalysis, "LPFOs_kt_0p70");
    delete fit_7;
    Fit *fit_8 = new Fit(processes_8, pCouplingAnalysis, "SPFOs_ee_kt_0p70");
    delete fit_8;
    Fit *fit_9 = new Fit(processes_9, pCouplingAnalysis, "SPFOs_cam_0p70");
    delete fit_9;
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
