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

#include "BuildDistributions.h"
#include "CouplingAnalysis.h"
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

    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq_1 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_nunuqqqq",23.2,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_2 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5",85.f,"ee_nunuqqqq",23.2,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_3 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9",90.f,"ee_nunuqqqq",23.2,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_4 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0",92.f,"ee_nunuqqqq",23.2,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_5 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1",94.f,"ee_nunuqqqq",23.2,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_6 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",85.f,"ee_nunuqqqq",23.2,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_7 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",92.f,"ee_nunuqqqq",23.2,1500,1400,18,true);
//    const Process *pProcess_ee_nunuqqqq_8 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7", ? ,"ee_nunuqqqq",23.2,1500,1400,18,true);
//    const Process *pProcess_ee_nunuqqqq_9 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7", ? ,"ee_nunuqqqq",23.2,1500,1400,18,true);

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
    processes_all.push_back(pProcess_ee_nunuqqqq_1);
    processes_all.push_back(pProcess_ee_nunuqqqq_2);
    processes_all.push_back(pProcess_ee_nunuqqqq_3);
    processes_all.push_back(pProcess_ee_nunuqqqq_4);
    processes_all.push_back(pProcess_ee_nunuqqqq_5);
    processes_all.push_back(pProcess_ee_nunuqqqq_6);
    processes_all.push_back(pProcess_ee_nunuqqqq_7);
//    processes_all.push_back(pProcess_ee_nunuqqqq_8);
//    processes_all.push_back(pProcess_ee_nunuqqqq_9);

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes_all);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes_all, pPreSelectionSemiFinal);
    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting

//    MakeDerivedPlots *makePlots = new MakeDerivedPlots(processes, pPreSelectionSemiFinal, pPostMVASelection);

    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pPostMVASelection, 1400);

    BuildDistributions *pBuildDistributions_1 = new BuildDistributions(processes_1, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "SPFOs_kt_0p70_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV", outputPath);
    pBuildDistributions_1->SetNBins(10);
    pBuildDistributions_1->BuildDistribution();
    delete pBuildDistributions_1;

    BuildDistributions *pBuildDistributions_2 = new BuildDistributions(processes_2, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "SPFOs_kt_0p70_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV", outputPath);
    pBuildDistributions_2->SetNBins(10);
    pBuildDistributions_2->BuildDistribution();
    delete pBuildDistributions_2;

    BuildDistributions *pBuildDistributions_3 = new BuildDistributions(processes_3, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "SPFOs_kt_0p90_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV", outputPath);
    pBuildDistributions_3->SetNBins(10);
    pBuildDistributions_3->BuildDistribution();
    delete pBuildDistributions_3;

    BuildDistributions *pBuildDistributions_4 = new BuildDistributions(processes_4, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "SPFOs_kt_1p00_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV", outputPath);
    pBuildDistributions_4->SetNBins(10);
    pBuildDistributions_4->BuildDistribution();
    delete pBuildDistributions_4;

    BuildDistributions *pBuildDistributions_5 = new BuildDistributions(processes_5, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "SPFOs_kt_1p10_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV", outputPath);
    pBuildDistributions_5->SetNBins(10);
    pBuildDistributions_5->BuildDistribution();
    delete pBuildDistributions_5;

    BuildDistributions *pBuildDistributions_6 = new BuildDistributions(processes_6, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "TPFOs_kt_0p70_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV", outputPath);
    pBuildDistributions_6->SetNBins(10);
    pBuildDistributions_6->BuildDistribution();
    delete pBuildDistributions_6;

    BuildDistributions *pBuildDistributions_7 = new BuildDistributions(processes_7, pCouplingAnalysis, nEvtsStart, nEvtsEnd, "LPFOs_kt_0p70_10Bins_Start_" + NumberToString(nEvtsStart) + "_End_" + NumberToString(nEvtsEnd) + "_1400GeV", outputPath);
    pBuildDistributions_7->SetNBins(10);
    pBuildDistributions_7->BuildDistribution();
    delete pBuildDistributions_7;
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
