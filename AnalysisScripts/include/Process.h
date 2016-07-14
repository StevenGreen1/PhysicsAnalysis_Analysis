/**
 *  @file   AnalysisScripts/include/Process.h 
 * 
 *  @brief  Header file for the process class.
 * 
 *  $Log: $
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "TChain.h"

class Process
{
    public:
        /**
         *  @brief Constructor
         *
         *  @param jobDescription
         *  @param detectorModel
         *  @param reconstructionVariant
         *  @param eventType
         *  @param crossSection
         *  @param energy
         */
        Process(std::string jobDescription, std::string detectorModel, std::string reconstructionVariant, std::string eventType, const float crossSection, const float luminoscity, const int energy);

        /**
         *  @brief Default destructor
         */
        ~Process();

        /**
         *  @brief Return pointer to TChain made from input root files
         */
        TChain* GetTChain();

        /**
         *  @brief Return the weight for the given process
         */
        float GetProcessWeight() const;

        /**
         *  @brief Return the event type for the given process
         */
        std::string GetEventType() const;

        /**
         *  @brief Print out all information about this process
         */
        void Print();

    private:
        /**
         *  @brief Make TChain of from input root files
         */
        void MakeTChain();

        /**
         *  @brief Convert a number to a string
         *
         *  @param T number to convert to string
         */
        template <class T>
        std::string NumberToString(T Number);

        // Member variables 
        const std::string     m_jobDescription;
        const std::string     m_detectorModel;
        const std::string     m_reconstructionVariant;
        const std::string     m_eventType;
        const float           m_crossSection;
        const float           m_luminoscity;
        const unsigned int    m_energy;
        TChain*               m_pTChain;
        int                   m_numberOfEntries;
        float                 m_processWeight;
        std::string           m_pathToFiles;
};

#endif
