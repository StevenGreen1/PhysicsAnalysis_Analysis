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

    // When concatenating the weight file information just need processing that requires weights  
    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq_1(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_2(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_3(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_4(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_5(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_6(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_7(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_8(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true));
    const Process *pProcess_ee_nunuqqqq_9(new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11,true));

    std::vector<const Process*> processes;
    processes.push_back(pProcess_ee_nunuqqqq_1);
    processes.push_back(pProcess_ee_nunuqqqq_2);
    processes.push_back(pProcess_ee_nunuqqqq_3);
    processes.push_back(pProcess_ee_nunuqqqq_4);
    processes.push_back(pProcess_ee_nunuqqqq_5);
    processes.push_back(pProcess_ee_nunuqqqq_6);
    processes.push_back(pProcess_ee_nunuqqqq_7);
    processes.push_back(pProcess_ee_nunuqqqq_8);
    processes.push_back(pProcess_ee_nunuqqqq_9);

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);
//    pPreSelectionSemiFinal->ApplyTransverseMomentumCut(100.0, 10000.0);
//    pPreSelectionSemiFinal->ApplyInvariantMassCut(200.0, 10000.0);
//    pPreSelectionSemiFinal->ApplyBosonInvariantMassCut(0.0, 10000.0);
//    pPreSelectionSemiFinal->ApplyNIsolatedLeptonCut(0, 0);

    PostMVASelection *pPostMVASelection = new PostMVASelection(processes, pPreSelectionSemiFinal);
//    pPostMVASelectionSelected->ApplyBDTCut(0.0641, 10000.0);
    pPostMVASelection->MakeWeightList(false); // <- Must call to get list of events needing weights for fitting

    ConcatenateWeights *pConcatenateWeights = new ConcatenateWeights(pPostMVASelection);
    pConcatenateWeights->LoadWeightXml(simulationEventNumber, pProcess_ee_nunuqqqq_1);  // Only uses process for event name and energy
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
