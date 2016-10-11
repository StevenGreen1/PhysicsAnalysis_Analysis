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
    int generatorNumberToConcatenate(atoi(argv[1]));

    srand(time(0));
    gStyle->SetOptStat(0);

    // When concatenating the weight file information just need processing that requires weights  
    // Signal, luminosity copied from nunuqqqq final state
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",22.16,1500,1400,9,true); // Enable quickload for post MVA root files only
    std::vector<const Process*> processes;
    processes.push_back(pProcess_ee_nunuqqqq);

    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);
    pPreSelectionSemiFinal->ApplyTransverseMomentumCut(100.0, 10000.0);
    pPreSelectionSemiFinal->ApplyInvariantMassCut(200.0, 10000.0);
    pPreSelectionSemiFinal->ApplyBosonInvariantMassCut(0.0, 10000.0);
    pPreSelectionSemiFinal->ApplyNIsolatedLeptonCut(0, 0);

    PostMVASelection *pPostMVASelectionSelected = new PostMVASelection(processes, pPreSelectionSemiFinal);
    pPostMVASelectionSelected->ApplyBDTCut(0.0641, 10000.0);
    pPostMVASelectionSelected->MakeWeightList(); // <- Must call to get list of events needing weights for fitting

    ConcatenateWeights *pConcatenateWeights = new ConcatenateWeights(pPostMVASelectionSelected);
    pConcatenateWeights->LoadWeightXml(generatorNumberToConcatenate, pProcess_ee_nunuqqqq);
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
