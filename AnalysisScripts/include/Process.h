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
#include <vector>

#include "TChain.h"
#include "TList.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"

namespace analysis_namespace
{
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
}

class Process
{
    typedef std::vector<int> IntVector;
    typedef std::vector<double> DoubleVector;

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
         *  @brief Return pointer to TChain made from input root files that will be used for training
         */
        TChain* GetTrainingTChain() const;

        /**
         *  @brief Return pointer to TChain made from input root files that will be used for training
         */
        TChain* GetPostMVATChain() const;

        /**
         *  @brief Return the weight for the given process
         */
        float GetProcessWeight() const;

        /**
         *  @brief Return the weight for the given process post MVA training
         */
        float GetPostMVAProcessWeight() const;

        /**
         *  @brief Return the event type for the given process
         */
        std::string GetEventType() const;

        /**
         *  @brief Retrun the cross section for the given process
         */
        float GetCrossSection() const;

        /**
         *  @brief Retrun the cross section for the given process
         */
        float GetLuminosity() const;
 
        /**
         *  @brief Return the energy for the given process
         */
        int GetEnergy() const;

        /**
         *  @brief Get analysis tag
         */
        int GetAnalysisTag() const;

        /**
         *  @brief Print out all information about this process
         */
        void Print() const;

        /**
         *  @brief Check to see if event passes selection cuts
         *
         *  @param eventNumber
         */
        bool DoesEventPassCuts(int eventNumber) const;

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

        /**
         *  @brief Make map of TChain entry for process to bool determining whether event passes selection cuts
         */
        void MakeSelection();

        /**
         *  @breif Set the post MVA tchain
         */
        void SetMVARootFiles();

        const std::string     m_jobDescription;          ///< Job description
        const std::string     m_detectorModel;           ///< Detector model
        const std::string     m_reconstructionVariant;   ///< Reconstruction variant
        const std::string     m_eventType;               ///< Process 
        const float           m_crossSection;            ///< Cross section of proces
        const float           m_luminosity;              ///< Luminosity
        const unsigned int    m_energy;                  ///< Energy of process
        const int             m_analysisTag;             ///< Analysis tag for bookeeping
        TChain*               m_pTChain;                 ///< Chain of analysis root files
        TChain*               m_pTrainTChain;            ///< Chain of analysis root files for training TMVA
        TChain*               m_pPostMVATChain;          ///< Chain of analysis root files post DBT training 
        int                   m_numberOfEntries;         ///< Number of entries in tree
        float                 m_processWeight;           ///< Weight to give required luminosity
        float                 m_postMVAProcessWeight;    ///< Weight to give required luminosity for post MVA
        std::string           m_pathToFiles;             ///< Path to analysis root files
        std::map<int,bool>    m_doesEventPassSelection;  ///< Does event number pass the selection cuts
};

#endif
