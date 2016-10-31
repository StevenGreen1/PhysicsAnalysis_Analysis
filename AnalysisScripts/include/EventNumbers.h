/**
 *  @file   AnalysisScripts/include/EventNumbers.h 
 * 
 *  @brief  Header file for the event number class.
 * 
 *  $Log: $
 */

#ifndef EVENT_NUMBER_H
#define EVENT_NUMBER_H

#include <cmath>
#include <iostream>

class EventNumbers
{
    public:
        /**
         *  @brief Constructor
         */
        EventNumbers();

        /**
         *  @brief Default destructor
         */
        ~EventNumbers();

        /**
         *  @brief Get simulation job number from global event number
         *
         *  @param globalEventNumber
         */
        int GetSimulationNumberFromGlobal(int globalEventNumber) const;

        /**
         *  @brief Get generator job number from global event number
         *
         *  @param globalEventNumber
         */
        int GetGeneratorNumberFromGlobal(int globalEventNumber) const;

        /**
         *  @brief Get generator job number from simulation job number
         *
         *  @param simulationEventNumber
         */
        int GetGeneratorNumberFromSimulation(int simulationEventNumber) const;

        /**
         *  @brief Set the global event number for simulationEventNumber and jobEventNumber
         *
         *  @param simulationEventNumber
         *  @param jobEventNumber
         */
        int SetGlobalEventNumber(int simulationEventNumber, int jobEventNumber) const;
};

#endif
