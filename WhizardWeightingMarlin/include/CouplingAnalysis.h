/**
 *  @file   include/CouplingAnalysis.h
 * 
 *  @brief  Header file for the handling of reweighting information in vector boson scattering physics analysis
 * 
 *  $Log: $
 */
#ifndef WEIGHT_TO_XML_CONVERTER_H
#define WEIGHT_TO_XML_CONVERTER_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TH2F.h"

#include <algorithm>

#include "tinyxml.h"

using namespace std;

enum SuccessEnum {FAILURE, SUCCESS};

class CouplingAnalysis
{
    public:
        /**
         * @brief Constructor
         */
        CouplingAnalysis();

        /**
         * @brief Destructor
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
        void GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight) const;

    private:
        /**
         * @brief Event class used as container for reweighting matrix element information
         */
        class Event
        {
            private:
                std::string m_Process;                                              ///< Physics process being simulated
                std::string m_Energy;                                               ///< Energy of process
                int m_EventNumber;                                                  ///< Event number
                float m_Alpha4;                                                     ///< Alpha4 value used in simulation
                float m_Alpha5;                                                     ///< Alpha5 value used in simulation
                float m_Weight;                                                     ///< Ratio of integrands produced for a particular event with specified alpha 4/5 values
            public:
                /**
                 * @brief Set the event number for the event 
                 *
                 * @param eventNumber
                 */
                void SetEventNumber(int eventNumber) { m_EventNumber = eventNumber; }

                /**
                 * @brief Set the alpha4 value for the event 
                 *
                 * @pram alpha4
                 */
                void SetAlpha4(float alpha4) { m_Alpha4 = alpha4; }

                /**
                 * @brief Set the alpha5 value for the event
                 *
                 * @param alpha5
                 */
                void SetAlpha5(float alpha5) { m_Alpha5 = alpha5; }

                /**
                 * @brief Set the ratio of integrands for the event 
                 *
                 * @param weight
                 */
                void SetWeight(float weight) { m_Weight = weight; }

                /**
                 * @brief Set the process for the event
                 *
                 * @param process
                 */
                void SetProcess(std::string process) { m_Process = process; }

                /**
                 * @brief Set the energy for the event 
                 *
                 * @param energy
                 */
                void SetEnergy(std::string energy) { m_Energy = energy; }

                /**
                 * @brief Return the event number for the event
                 */
                int GetEventNumber() { return m_EventNumber; }

                /** 
                 * @brief Return the alpha4 for the event 
                 */
                float GetAlpha4() { return m_Alpha4; }

                /**
                 * @brief Return the alpha5 for the event
                 */
                float GetAlpha5() { return m_Alpha5; }

                /**
                 * @brief Return the ratio of integrands for the event 
                 */
                float GetWeight() { return m_Weight; }

                /**
                 * @brief Return the process for the event 
                 */
                std::string GetProcess() { return m_Process; }

                /**
                 * @brief Return the energy for the event 
                 */
                std::string GetEnergy() { return m_Energy; }
        };

        typedef std::vector<float> FloatVector;
        typedef std::vector<CouplingAnalysis::Event*> EventVector;
        typedef std::map<int, float> IntToFloatMap;
        typedef std::map<int, IntToFloatMap > IntToIntToFloatMap;
        typedef std::map<int, IntToIntToFloatMap > IntToIntToIntToFloatMap;

        /**
         * @brief Load all the xml files containing the reweighting information
         */
        void LoadXml();

        /**
         * @brief Load a single xml file containing the reweighting information
         *
         * @param process being analysed
         * @param energy, energy in GeV of the process
         * @param alpha4 value used in weight information for the loaded xml file
         * @param alpha5 value used in weight information for the loaded xml file
         */
        void LoadIndividualXml(std::string process, std::string energy, const float alpha4, const float alpha5);

        /**
         * @brief Perform bilinear interpolation based on the bounding weight values for the requested alpha4 and alpha5
         *
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         */
        float BilinearInterpolation(const float l4l5, const float l4u5, const float u4l5, const float u4u5, const float lowerAlpha4, const float upperAlpha4, const float lowerAlpha5, const float upperAlpha5, const float alpha4, const float alpha5) const;

        /**
         * @brief Make weight information plot for a single event 
         *
         * @param eventNumber
         */
        void AnalyseSingleEvent(const int eventNumber) const;

        /**
         * @brief Find from the list of alpha values simulated in whizard the alpha value bounding the requested value of alpha value
         *
         * @param alphaVector list of alpha values simulated in whizard
         * @param lowAlpha lower bound of currentAlpha
         * @param highAlpha upper bound of currentAlpha
         * @param currentAlpha requested value of alpha
         */
        void Bounds(const FloatVector &alphaVector, float &lowAlpha, float &highAlpha, const float currentAlpha) const;

        /**
         * @brief Return the weight value for a given event simulated in whizard with a specific alpha values
         *
         * @param eventNumber for event in question 
         * @param alpha4 value simulated in whizard
         * @param alpha5 value simulated in whizard
         */
        float GetStoredWeight(const int eventNumber, const float alpha4, const float alpha5) const;

        /**
         * @brief Find the int key to the stored values of alpha4 that were simulated in whizard.  Returns false if value not found.
         *
         * @param alpha4 value simulated in whizard
         * @param alpha4Key integer key to alpha4 value simulated in whizard
         */
        bool GetAlpha4Key(const float alpha4, int &alpha4Key) const;

        /**
         * @brief Find the int key to the stored values of alpha5 that were simulated in whizard.  Returns false if value not found.
         *
         * @param alpha5 value simulated in whizard
         * @param alpha5Key integer key to alpha4 value simulated in whizard
         */
        bool GetAlpha5Key(const float alpha5, int &alpha5Key) const;

        /**
         * @brief Get the value of alpha4 for a given alpha4 integer key
         *
         * @param alpha4Key integer key to the alpha4 value requested
         */
        float GetAlpha4(int alpha4Key) const;

        /**
         * @brief Get the value of alpha5 for a given alpha4 integer key
         *
         * @param alpha5Key integer key to the alpha5 value requested
         */
        float GetAlpha5(int alpha5Key) const;

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

        int m_NumberUniqueAlpha4;                                           ///< Number of unique values of alpha4 simulated in whizard and read in
        int m_NumberUniqueAlpha5;                                           ///< Number of unique values of alpha5 simulated in whizard and read in
        EventVector m_Events;                                               ///< Vector of stored event weight classes
        FloatVector m_Alpha4Vector;                                         ///< Vector of unique values of alpha4 simulated in whizard and read in
        FloatVector m_Alpha5Vector;                                         ///< Vector of unique values of alpha5 simulated in whizard and read in
        IntToFloatMap m_KeyToAlpha4Map;                                     ///< Map of integer keys to unique values of alpha4 simulated in whizard 
        IntToFloatMap m_KeyToAlpha5Map;                                     ///< Map of integer keys to unique values of alpha5 simulated in whizard
        IntToIntToIntToFloatMap m_EventToAlpha4ToAlpha5ToWeightMap;         ///< Map of event number to alpha4 to alpha5 to event weight 
};

#endif
