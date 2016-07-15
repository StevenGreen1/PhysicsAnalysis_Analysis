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

#include "MakePlots.h"
#include "Process.h"

template <class T>
std::string NumberToString(T Number);

//=====================================================================
// Luminoscity is 1.5 ab-1 = 1500 fb-1 at 1.4 TeV

int main(int argc, char **argv)
{
    srand(time(0));

    // Signal
    const Process *pProcess_ee_nunuww_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuww_nunuqqqq",427.2,1500,1400);

    // CLIC Backgrounds
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",24.7,1500,1400);

    pProcess_ee_nunuww_nunuqqqq->Print();
    pProcess_ee_nunuqqqq->Print();

    std::vector<const Process*> processes;
    processes.push_back(pProcess_ee_nunuww_nunuqqqq);
    processes.push_back(pProcess_ee_nunuqqqq);

    MakePlots *makePlots = new MakePlots(processes);
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
