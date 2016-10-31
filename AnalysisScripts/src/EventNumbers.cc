/**
 *  @file   AnalysisScripts/src/EventNumbers.cc 
 * 
 *  @brief  Implementation of the event number class.
 * 
 *  $Log: $
 */

#include "EventNumbers.h"

//=====================================================================

EventNumbers::EventNumbers()
{
}

//=====================================================================

EventNumbers::~EventNumbers()
{
}

//=====================================================================

int EventNumbers::GetSimulationNumberFromGlobal(int globalEventNumber) const
{
    return 1 + floor((globalEventNumber - 1) / 1000.0);
}

//=====================================================================

int EventNumbers::GetGeneratorNumberFromGlobal(int globalEventNumber) const
{
    return floor((globalEventNumber - 1) / 1000000.0);
}

//=====================================================================

int EventNumbers::GetGeneratorNumberFromSimulation(int simulationEventNumber) const
{
    return floor((simulationEventNumber - 1) / 1000.0);
}

//=====================================================================

int EventNumbers::SetGlobalEventNumber(int simulationEventNumber, int jobEventNumber) const
{
    return 1e3 * (simulationEventNumber - 1) + jobEventNumber;
}

//=====================================================================

/* E.g. 1,003,273
 * Generator number 1
 * Simulation number 1004 
 * Local job number 273
 */

