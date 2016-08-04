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
#include "TList.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"

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
         *  @param analysisTag
         */
        Process(std::string jobDescription, std::string detectorModel, std::string reconstructionVariant, std::string eventType, const float crossSection, const float luminosity, const int energy, const int analysisTag);

        /**
         *  @brief Default destructor
         */
        ~Process();

        /**
         *  @brief Return pointer to TChain made from input root files
         */
        TChain* GetTChain() const;

        /**
         *  @brief Return the weight for the given process
         */
        float GetProcessWeight() const;

        /**
         *  @brief Return the event type for the given process
         */
        std::string GetEventType() const;

        /**
         *  @brief Get analysis tag
         */
        int GetAnalysisTag() const;

        /**
         *  @brief Print out all information about this process
         */
        void Print() const;

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

        const std::string     m_jobDescription;          ///< Job description
        const std::string     m_detectorModel;           ///< Detector model
        const std::string     m_reconstructionVariant;   ///< Reconstruction variant
        const std::string     m_eventType;               ///< Process 
        const float           m_crossSection;            ///< Cross section of proces
        const float           m_luminosity;              ///< Luminosity
        const unsigned int    m_energy;                  ///< Energy of process
        const int             m_analysisTag;             ///< Analysis tag for bookeeping
        TChain*               m_pTChain;                 ///< Chain of analysis root files
        int                   m_numberOfEntries;         ///< Number of entries in tree
        float                 m_processWeight;           ///< Weight to give required luminosity
        std::string           m_pathToFiles;             ///< Path to analysis root files
};

#endif
