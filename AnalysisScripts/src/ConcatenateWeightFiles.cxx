/**
 *  @file   AnalysisScripts/src/ConcatenateWeightFiles.cxx
 * 
 *  @brief  Implementation of the concatenate weight files script.
 * 
 *  $Log: $
 */

#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "ConcatenateWeights.h"
#include "Process.h"
#include "PreSelection.h"
#include "PostMVASelection.h"

#include "TStyle.h"

template <class T>
std::string NumberToString(T Number);

int main(int argc, char **argv)
{
    int simulationEventNumber(atoi(argv[1]));

    srand(time(0));
    gStyle->SetOptStat(0);

// 1.4 TeV
/*
    const Process *pProcess_ee_nunuqqqq_1 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_nunuqqqq",22.16,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_2 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5",85.f,"ee_nunuqqqq",22.16,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_3 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9",90.f,"ee_nunuqqqq",22.16,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_4 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0",92.f,"ee_nunuqqqq",22.16,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_5 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1",94.f,"ee_nunuqqqq",22.16,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_6 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",84.f,"ee_nunuqqqq",22.16,1500,1400,18,true);
    const Process *pProcess_ee_nunuqqqq_7 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",90.f,"ee_nunuqqqq",22.16,1500,1400,18,true);
//    const Process *pProcess_ee_nunuqqqq_8 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7", ? ,"ee_nunuqqqq",22.16,1500,1400,18,true);
//    const Process *pProcess_ee_nunuqqqq_9 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7", ? ,"ee_nunuqqqq",22.16,1500,1400,18,true);

    std::vector<const Process*> processes;
    processes.push_back(pProcess_ee_nunuqqqq_1);
    processes.push_back(pProcess_ee_nunuqqqq_2);
    processes.push_back(pProcess_ee_nunuqqqq_3);
    processes.push_back(pProcess_ee_nunuqqqq_4);
    processes.push_back(pProcess_ee_nunuqqqq_5);
    processes.push_back(pProcess_ee_nunuqqqq_6);
    processes.push_back(pProcess_ee_nunuqqqq_7);
//    processes.push_back(pProcess_ee_nunuqqqq_8);
//    processes.push_back(pProcess_ee_nunuqqqq_9);

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes, pPreSelectionSemiFinal);
    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting

    ConcatenateWeights *pConcatenateWeights = new ConcatenateWeights(pPostMVASelection, "ee_nunuqqqq", 1400);
    pConcatenateWeights->LoadWeightXml(simulationEventNumber); 
*/

// 3 TeV
/*
    const Process *pProcess_ee_nunuqqqq_1 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",88.f,"ee_nunuqqqq",71.5,2000,3000,18,true);
    const Process *pProcess_ee_nunuqqqq_2 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5",85.f,"ee_nunuqqqq",71.5,2000,3000,18,true);
    const Process *pProcess_ee_nunuqqqq_3 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9",90.f,"ee_nunuqqqq",71.5,2000,3000,18,true);
    const Process *pProcess_ee_nunuqqqq_4 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0",92.f,"ee_nunuqqqq",71.5,2000,3000,18,true);
    const Process *pProcess_ee_nunuqqqq_5 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1",94.f,"ee_nunuqqqq",71.5,2000,3000,18,true);
    const Process *pProcess_ee_nunuqqqq_6 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",84.f,"ee_nunuqqqq",71.5,2000,3000,18,true);
    const Process *pProcess_ee_nunuqqqq_7 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7",90.f,"ee_nunuqqqq",71.5,2000,3000,18,true);
//    const Process *pProcess_ee_nunuqqqq_8 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7", ? ,"ee_nunuqqqq",71.5,2000,3000,18,true);
//    const Process *pProcess_ee_nunuqqqq_9 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7", ? ,"ee_nunuqqqq",71.5,2000,3000,18,true);

    std::vector<const Process*> processes;
    processes.push_back(pProcess_ee_nunuqqqq_1);
    processes.push_back(pProcess_ee_nunuqqqq_2);
    processes.push_back(pProcess_ee_nunuqqqq_3);
    processes.push_back(pProcess_ee_nunuqqqq_4);
    processes.push_back(pProcess_ee_nunuqqqq_5);
    processes.push_back(pProcess_ee_nunuqqqq_6);
    processes.push_back(pProcess_ee_nunuqqqq_7);
//    processes.push_back(pProcess_ee_nunuqqqq_8);
//    processes.push_back(pProcess_ee_nunuqqqq_9);

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes, pPreSelectionSemiFinal);
    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting, but most call either way to get list of event numbers needing new weights
*/

// This skips the check that the event number is used by the fit, big time saver on concatenation of files
    std::vector<const Process*> processes;
    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);
    PostMVASelection *pPostMVASelection = new PostMVASelection(processes, pPreSelectionSemiFinal);
    ConcatenateWeights *pConcatenateWeights = new ConcatenateWeights(pPostMVASelection, "ee_nunuqqqq", 3000);
    pConcatenateWeights->LoadWeightXml(simulationEventNumber);
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
