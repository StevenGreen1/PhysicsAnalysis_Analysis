/**
 *  @file   include/CouplingAnalysis.h
 * 
 *  @brief  Header file for the handling of reweighting information in vector boson scattering physics analysis
 * 
 *  $Log: $
 */
#ifndef COUPLING_ANALYSIS_H
#define COUPLING_ANALYSIS_H

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

class CouplingAnalysis
{
    typedef std::map<int, float> IntToFloatMap;
    typedef std::map<int, IntToFloatMap > IntToIntToFloatMap;
    typedef std::map<int, IntToIntToFloatMap > IntToIntToIntToFloatMap;
    typedef std::vector<const Process*> ProcessVector;

    public:
        /**
         *  @brief Constructor
         */
        CouplingAnalysis(const ProcessVector &processVector, PostMVASelection *pPostMVASelection);

        /**
         *  @brief Destructor
         */
        ~CouplingAnalysis();

        /**
         * @brief  Get the event weight for a specific event and a given value of alpha4 and alpha5
         *
         * @param  eventNumber 
         * @param  alpha4  
         * @param  alpha5 
         * @param  eventWeight event weight for the given event number, alpha4 and alpha5 values
         */
        void GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight);

        /**
         *  @brief Return the post MVA selection class used in analysis
         */
        PostMVASelection* GetPostMVASelection() const;

    private:
         /**
          *  @brief Load concatenated xml data for event weights
          */
        void LoadConcatenatedWeightXml();

         /**
          *  @brief Load individual concatenated xml data for event weights
          */
        void LoadIndividualConcatenatedWeightXml(std::string weightFileToLoad);

        /**
         *  @brief Check to see if two numbers of class T are, firstly non integer, and secondly identical to within a given number of units in the last place
         *
         *  @param x number to compare 
         *  @param y number to compare 
         *  @param ulp number of units in the last place to compare to.  Optional parameter, default 2
         */
        template<class T>
        typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
        AlmostEqual(T x, T y, int ulp) const;

        /**
         *  @brief Retrun a bool asking does a key already exist for this value of alpha4
         *
         *  @param alpha4 value in question
         */
        bool DoesAlpha4KeyExist(const float alpha4) const;

        /**
         * @brief Set a new int key for the given value of alpha4
         *
         * @param alpha4 value to set key for
         */
        void SetAlpha4Key(const float alpha4);

        /**
         * @brief Return the int key for the given value of alpha4
         *
         * @param alpha4 value to get key for
         */
        int GetAlpha4Key(const float alpha4) const;

        /**
         * @brief Get the value of alpha4 for the given key
         *
         * @param alpha4Key integer key to the alpha4 value requested
         */
        float GetAlpha4(int key) const;

        /**
         *  @brief Retrun a bool asking does a key already exist for this value of alpha5
         *
         *  @param alpha5 value in question
         */
        bool DoesAlpha5KeyExist(const float alpha5) const;

        /**
         * @brief Set a new int key for the given value of alpha5
         *
         * @param alpha5 value to set key for
         */
        void SetAlpha5Key(const float alpha5);

        /**
         * @brief Return the int key for the given value of alpha5
         *
         * @param alpha5 value to get key for
         */
        int GetAlpha5Key(const float alpha5) const;

        /**
         * @brief Get the value of alpha5 for the given key
         *
         * @param key integer key to the alpha5 value requested
         */
        float GetAlpha5(int key) const;

        /**
         *  @brief Set the bounding key values, for key->float value with recorded weights, for the given value of alpha4 requested
         *
         *  @param alpha4 value in question
         *  @param alpha4BoundingKeys Array of keys bounding alpha4 
         */
        void SetAlpha4BoundingKeys(const float alpha4, IntVector &alpha4BoundingKeys) const;

        /**
         *  @brief Set the bounding key values, for key->float value with recorded weights, for the given value of alpha5 requested
         *
         *  @param alpha5 value in question
         *  @param alpha5BoundingKeys Array of keys bounding alpha5
         */
        void SetAlpha5BoundingKeys(const float alpha5, IntVector &alpha5BoundingKeys) const;

        /**
         *  @brief Perform bilinear interpolation based on the bounding weight values for the requested x and y
         *
         *  @param f11 Value of function at x1, y1
         *  @param f12 Value of function at x1, y2
         *  @param f21 Value of function at x2, y1
         *  @param f22 Value of function at x2, y2
         *  @param x Value of interpolated point
         *  @param x1 Lower bounding value of interpolated point
         *  @param x2 Upper bounding value of interpolated point
         *  @param y Value of interpolated point
         *  @param y1 Lower bounding value of interpolated point
         *  @param y2 Upper bounding value of interpolated point
         */
        float BilinearInterpolation(const float f11, const float f12, const float f21, const float f22, const float x, const float x1, const float x2, const float y, const float y1, const float y2) const;

        /**
         *  @brief Apply cubic interpolation assuming p = y(x=-1), y(x=0), y(x=1), y(x=2) where x is between 0 and 1
         *
         *  @param x value to apply cubic interpolation at
         */
        float CubicInterpolation(float p[4], float x);

        /**
         *  @brief Apply bicubic interpolation i.e. two dimensional cubic interpolation where x and y are between 0 and 1
         *
         *  @param p values of function in a 4x4 grid surrounding (x,y)
         *  @param x value to apply cubic interpolation at
         *  @param y value to apply cubic interpolation at
         */
        float BicubicInterpolation(float p[4][4], float x, float y);

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

        typedef std::vector<CouplingAnalysis::Event*> EventVector;

        ProcessVector           m_processVector;                    ///< Vector of processes to load
        PostMVASelection       *m_pPostMVASelection;                ///< Post MVA selection
        TiXmlDocument          *m_pTiXmlResultsDocument;            ///< Xml document used for saving data
        TiXmlElement           *m_pDocumentTiXmlElement;            ///< Xml element handle for head of results
        EventVector             m_events;                           ///< Vector of events to save to xml
        std::string             m_weightsDirectory;                 ///< Directory to send concatenated weight files to
        int                     m_numberUniqueAlpha4;               ///< Number of unique values of alpha4 simulated in whizard and read in
        int                     m_numberUniqueAlpha5;               ///< Number of unique values of alpha5 simulated in whizard and read in
        int                     m_a4IntMin;                         ///< Min int to use for stepping alpha4 values
        int                     m_a4IntMax;                         ///< Max int to use for stepping alpha4 values
        int                     m_a5IntMin;                         ///< Min int to use for stepping alpha5 values
        int                     m_a5IntMax;                         ///< Max int to use for stepping alpha5 values
        float                   m_a4Step;                           ///< Step value for alpha4
        float                   m_a5Step;                           ///< Step value for alpha5
        IntVector               m_eventsNeedingWeights;             ///< Vector of event numbers requiring weights
        IntVector               m_readInGenNumbers;                 ///< GenN values read in
        FloatVector             m_alpha4Vector;                     ///< Vector of unique values of alpha4 simulated in whizard and read in
        FloatVector             m_alpha5Vector;                     ///< Vector of unique values of alpha5 simulated in whizard and read in
        IntToFloatMap           m_keyToAlpha4Map;                   ///< Map of integer keys to unique values of alpha4 simulated in whizard 
        IntToFloatMap           m_keyToAlpha5Map;                   ///< Map of integer keys to unique values of alpha5 simulated in whizard
        IntToIntToIntToFloatMap m_eventToAlpha4ToAlpha5ToWeightMap; ///< Map of event number to alpha4 to alpha5 to event weight 
        bool                    m_weightsLoaded;                    ///< Bool indicating if concatenated weights have been loaded
};

#endif
