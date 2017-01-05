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
    int energy(atoi(argv[2]));

    srand(time(0));
    gStyle->SetOptStat(0);

    std::vector<const Process*> processes;
    PreSelection *pPreSelectionSemiFinal = new PreSelection(processes);
    PostMVASelection *pPostMVASelection = new PostMVASelection(processes, pPreSelectionSemiFinal);
    ConcatenateWeights *pConcatenateWeights = new ConcatenateWeights(pPostMVASelection, "ee_nunuqqqq", energy);
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
