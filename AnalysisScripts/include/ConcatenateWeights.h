/**
 *  @file   include/ConcatenateWeights.h
 * 
 *  @brief  Header file for the handling of concatenation of weight information in vector boson scattering physics analysis
 * 
 *  $Log: $
 */
#ifndef CONCATENATE_WEIGHTS_H
#define CONCATENATE_WEIGHTS_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

//#include "TCanvas.h"
//#include "TGraph2D.h"
//#include "TF2.h"
//#include "TH2F.h"
//#include "TStyle.h"
//#include "Math/Minimizer.h"
//#include "Math/Factory.h"
//#include "Math/Functor.h"
//#include "Math/GSLMinimizer.h"

#include <algorithm>

#include "tinyxml.h"

#include "Process.h"
#include "PostMVASelection.h"

using namespace analysis_namespace;

class ConcatenateWeights
{
    public:
        /**
         *  @brief Constructor
         */
        ConcatenateWeights(PostMVASelection *pPostMVASelection);

        /**
         *  @brief Destructor
         */
        ~ConcatenateWeights();

         /**
          *  @brief Load files for all alpha 4 and alpha 5 values sharing same generator number for a given process
          *
          *  @param genN Generator number to link to xml file to load
          *  @param pProcess Process indicating which data to load 
          */
        void LoadWeightXml(const int genN, const Process *pProcess);

    private:
         /**
          *  @brief Load files for a single alpha 4 and alpha 5 values sharing same generator number for a given process
          *
          *  @param genN Generator number to link to xml file to load
          *  @param alpha4 value to link to xml file to load
          *  @param alpha5 value to link to xml file to load
          *  @param pProcess Process indicating which data to load
          */
        void LoadIndividualWeightXml(const int &genN, const float &alpha4, const float &alpha5, const Process *pProcess);

        /**
         *  @brief Add the xml data being read to the xml document being saved
         *
         *  @param eventType of events being recorded to concatenated xml
         *  @param energy of events being recorded to concatenated xml
         *  @param alpha4 of events being recorded to concatenated xml
         *  @param alpha5 of events being recorded to concatenated xml
         */
        void ConcatenateIndividualWeightXml(std::string eventType, const int energy, const float alpha4, const float alpha5);

         /**
          *  @brief Save concatenated xml data for event weights
          *
          *  @param generatorNumber 
          */
        void SaveConcatenatedWeightXml(int generatorNumber);

        /**
         * @brief Convert number to string in specific format for reading in xml files
         *
         * @param T number to convert to string
         */
        template <class T>
        std::string FileNumberToString(T Number) const;

        /**
         * @brief Convert alpha4/alpha5 float to string in specific format for reading in xml files
         *
         * @param T number to convert to string
         */
        template <class T>
        std::string AlphasToString(T Number) const;

        /**
         * @brief Convert number to string in general format
         *
         * @param T number to convert to string
         */
        template <class T>
        std::string NumberToString(T Number) const;

        class Event
        {
            private:
                int m_eventNumber;
                float m_weight;
            public:
                void SetEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
                void SetWeight(float weight) { m_weight = weight; }
                int GetEventNumber() { return m_eventNumber; }
                float GetWeight() { return m_weight; }
        };

        typedef std::vector<ConcatenateWeights::Event*> EventVector;

        IntVector               m_eventsNeedingWeights;             ///< Vector of event numbers requiring weights
        int                     m_a4IntMin;                         ///< Min int to use for stepping alpha4 values
        int                     m_a4IntMax;                         ///< Max int to use for stepping alpha4 values
        int                     m_a5IntMin;                         ///< Min int to use for stepping alpha5 values
        int                     m_a5IntMax;                         ///< Max int to use for stepping alpha5 values
        float                   m_a4Step;                           ///< Step value for alpha4
        float                   m_a5Step;                           ///< Step value for alpha5
        std::string             m_weightsDirectory;                 ///< Directory to send concatenated weight files to

        TiXmlDocument          *m_pTiXmlResultsDocument;            ///< Xml document used for saving data
        TiXmlElement           *m_pDocumentTiXmlElement;            ///< Xml element handle for head of results
        EventVector             m_events;                           ///< Vector of events to save to xml
        IntVector               m_readInGenNumbers;                 ///< GenN values read in
};

#endif
