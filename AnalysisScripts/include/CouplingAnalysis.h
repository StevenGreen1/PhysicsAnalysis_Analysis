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
         *  @brief Read in all event weights from file and concatenate data into one xml file
         */ 
        void GetWeightsFromFiles();

        /**
         * @brief  Get the event weight for a specific event and a given value of alpha4 and alpha5
         *
         * @param  eventNumber 
         * @param  alpha4  
         * @param  alpha5 
         * @param  eventWeight event weight for the given event number, alpha4 and alpha5 values
         */
        void GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight) const;

    private:
         /**
          *  @brief Load files for all alpha 4 and alpha 5 values sharing same generator number for a given process
          *
          *  @param genN Generator number to link to xml file to load
          *  @param pProcess Process indicating which data to load 
          */
        void LoadXmlData(const int genN, const Process *pProcess);

         /**
          *  @brief Load files for a single alpha 4 and alpha 5 values sharing same generator number for a given process
          *
          *  @param genN Generator number to link to xml file to load
          *  @param alpha4 value to link to xml file to load
          *  @param alpha5 value to link to xml file to load
          *  @param pProcess Process indicating which data to load
          */
        void LoadIndividualXmlData(const int &genN, const float &alpha4, const float &alpha5, const Process *pProcess);

         /**
          *  @brief Save concatenated xml data for event weights
          *
          *  @param generatorNumber 
          */
        void SaveXmlData(int generatorNumber);

         /**
          *  @brief Load concatenated xml data for event weights
          */
        void LoadData();

        /**
         *  @brief Check to see if two floats are identical to floating point precision
         *
         *  @param a float to compare
         *  @param b float to compare
         */
        bool DoFloatsMatch(float a, float b) const;

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
         *  @param lowAlpha4Key Lower bound of requested alpha value
         *  @param highAlpha4Key High bound of requested alpha value
         */
        void SetAlpha4BoundingKeys(const float alpha4, int &lowAlpha4Key, int &highAlpha4Key) const;

        /**
         *  @brief Set the bounding key values, for key->float value with recorded weights, for the given value of alpha5 requested
         *
         *  @param alpha5 value in question
         *  @param lowAlpha5Key Lower bound of requested alpha value
         *  @param highAlpha5Key High bound of requested alpha value
         */
        void SetAlpha5BoundingKeys(const float alpha5, int &lowAlpha5Key, int &highAlpha5Key) const;

        /**
         * @brief Perform bilinear interpolation based on the bounding weight values for the requested x and y
         *
         * @param f11 Value of function at x1, y1
         * @param f12 Value of function at x1, y2
         * @param f21 Value of function at x2, y1
         * @param f22 Value of function at x2, y2
         * @param x Value of interpolated point
         * @param x1 Lower bounding value of interpolated point
         * @param x2 Upper bounding value of interpolated point
         * @param y Value of interpolated point
         * @param y1 Lower bounding value of interpolated point
         * @param y2 Upper bounding value of interpolated point
         */
        float BilinearInterpolation(const float f11, const float f12, const float f21, const float f22, const float x, const float x1, const float x2, const float y, const float y1, const float y2) const;

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

//        std::string             m_process;                          ///< String of process under consideration
//        std::string             m_energy;                           ///< Energy of process under consideration

        ProcessVector           m_processVector;
        PostMVASelection       *m_pPostMVASelection;
        IntVector               m_eventsNeedingWeights;

        int                     m_numberUniqueAlpha4;               ///< Number of unique values of alpha4 simulated in whizard and read in
        int                     m_numberUniqueAlpha5;               ///< Number of unique values of alpha5 simulated in whizard and read in
        int                     m_a4IntMin;                         ///< Min int to use for stepping alpha4 values
        int                     m_a4IntMax;                         ///< Max int to use for stepping alpha4 values
        float                   m_a4Step;                           ///< Step value for alpha4
        int                     m_a5IntMin;                         ///< Min int to use for stepping alpha5 values
        int                     m_a5IntMax;                         ///< Max int to use for stepping alpha5 values
        float                   m_a5Step;                           ///< Step value for alpha5
        IntVector               m_readInGenNumbers;                 ///< GenN values read in
        FloatVector             m_alpha4Vector;                     ///< Vector of unique values of alpha4 simulated in whizard and read in
        FloatVector             m_alpha5Vector;                     ///< Vector of unique values of alpha5 simulated in whizard and read in
        IntToFloatMap           m_keyToAlpha4Map;                   ///< Map of integer keys to unique values of alpha4 simulated in whizard 
        IntToFloatMap           m_keyToAlpha5Map;                   ///< Map of integer keys to unique values of alpha5 simulated in whizard
        IntToIntToIntToFloatMap m_eventToAlpha4ToAlpha5ToWeightMap; ///< Map of event number to alpha4 to alpha5 to event weight 

        class Event
        {
            private:
                std::string m_Process;
                std::string m_Energy;
                int m_EventNumber;
                float m_Alpha4;
                float m_Alpha5;
                float m_Weight;
            public:
                void SetEventNumber(int eventNumber) { m_EventNumber = eventNumber; }
                void SetAlpha4(float alpha4) { m_Alpha4 = alpha4; }
                void SetAlpha5(float alpha5) { m_Alpha5 = alpha5; }
                void SetWeight(float weight) { m_Weight = weight; }
                void SetProcess(std::string process) { m_Process = process; }
                void SetEnergy(std::string energy) { m_Energy = energy; }
                int GetEventNumber() { return m_EventNumber; }
                float GetAlpha4() { return m_Alpha4; }
                float GetAlpha5() { return m_Alpha5; }
                float GetWeight() { return m_Weight; }
                std::string GetProcess() { return m_Process; }
                std::string GetEnergy() { return m_Energy; }
        };

        typedef std::vector<CouplingAnalysis::Event*> EventVector;
        EventVector m_Events;
};

#endif
