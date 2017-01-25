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
    public:
        /**
         *  @brief Constructor
         *
         *  @param jobDescription
         *  @param detectorModel
         *  @param reconstructionVariant
         *  @param pandoraPFOs
         *  @param jetClusteringMode
         *  @param nJetsToCluster
         *  @param jetClusteringAlgorithm
         *  @param jetClusteringRadius
         *  @param eventType
         *  @param crossSection
         *  @param energy
         *  @param analysisTag
         *  @param quickLoad skip loading individual files
         *  @param trivialMVA is BDT applied in full or are files just concatenated
         */
        Process(std::string jobDescription, std::string detectorModel, std::string reconstructionVariant, std::string pandoraPFOs, std::string jetClusteringMode, const int nJetsToCluster, std::string jetClusteringAlgorithm, std::string jetClusteringRadius, std::string eventType, const float crossSection, const float luminosity, const int energy, const int analysisTag, bool quickLoad = false, bool trivialMVA = true);

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
         *  @brief Get full event sample TChain
         */
        TChain* GetFullTChain() const;

        /**
         *  @brief Return pointer to TChain made from input root files that will be used for training
         */
        TChain* GetPostMVATChain() const;

        /**
         *  @brief Return the weight for the given process
         */
        float GetProcessWeight() const;

        /**
         *  @brief Return the weight for the given process training tree
         */
        float GetTrainingProcessWeight() const;

        /**
         *  @brief Get full event sample TChain event weight
         */
        float GetFullProcessWeight() const;

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
         *  @brief Get trivial MVA
         */
        bool GetQuickLoad() const;

        /**
         *  @brief Get trivialMVA
         */
        bool GetTrivialMVA() const;

        /**
         *  @brief Get the root suffix
         */
        std::string GetRootSuffix() const;

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
         *  @brief Set the post MVA tchain
         *
         *  @param perfect is MVA applied or are files just concatenated
         */
        void SetMVARootFiles(bool perfect);

        const std::string     m_jobDescription;          ///< Job description
        const std::string     m_detectorModel;           ///< Detector model
        const std::string     m_reconstructionVariant;   ///< Reconstruction variant
        const std::string     m_pandoraPFOs;             ///< Pandora PFOs Selected, Tight or Loose
        const std::string     m_jetClusteringMode;       ///< Jet clustering mode
        const int             m_nJetsToCluster;          ///< Number of jets to cluster
        const std::string     m_jetClusteringAlgorithm;  ///< Jet clustering algorithm to use 
        const std::string     m_jetClusteringRadius;     ///< Jet clustering radius 
        const std::string     m_eventType;               ///< Process 
        const float           m_crossSection;            ///< Cross section of proces
        const float           m_luminosity;              ///< Luminosity
        const unsigned int    m_energy;                  ///< Energy of process
        const int             m_analysisTag;             ///< Analysis tag for bookeeping
        const bool            m_quickLoad;               ///< Skip loading individual root files
        const bool            m_trivialMVA;              ///< MVA applied to concatenate files, but not actually apply MVA
        std::string           m_rootSuffix;              ///< Root suffix for loading files
        TChain*               m_pTChain;                 ///< Chain of analysis root files
        TChain*               m_pTrainTChain;            ///< Chain of analysis root files for training TMVA
        TChain*               m_pFullTChain;             ///< Chain of all analysis root files
        TChain*               m_pPostMVATChain;          ///< Chain of analysis root files post DBT training 
        int                   m_numberOfEntries;         ///< Number of entries in tree
        int                   m_trainingNumberOfEntries; ///< Training tree number of entries
        int                   m_fullNumberOfEntries;     ///< Full tree number of entries
        float                 m_processWeight;           ///< Weight to give required luminosity
        float                 m_trainingProcessWeight;   ///< Weight to give required luminosity for training sample
        float                 m_fullProcessWeight;       ///< Weight to give required luminosity for full sample
        float                 m_postMVAProcessWeight;    ///< Weight to give required luminosity for post MVA
        std::string           m_pathToFiles;             ///< Path to analysis root files
        std::map<int,bool>    m_doesEventPassSelection;  ///< Does event number pass the selection cuts
};

#endif
