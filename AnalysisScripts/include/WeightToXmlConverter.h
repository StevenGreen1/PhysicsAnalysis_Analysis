/**
 *  @file   include/WeightToXmlConverter.h
 *
 *  @brief  Header file for the WeightToXmlConverter class 
 *
 *  $Log: $
 */

#ifndef WEIGHT_TO_XML_CONVERTER_H
#define WEIGHT_TO_XML_CONVERTER_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "tinyxml.h"

using namespace std;

enum SuccessEnum {FAILURE, SUCCESS};

class WeightToXmlConverter
{
    public:
        /**
         *  @brief Constructor
         *
         *  @param process event type
         *  @param energy value to read in
         *  @param alpha4 alpha 4 value to read in
         *  @param alpha4 alpha 5 value to read in
         *  @param whizard job set number to read in
         */
        WeightToXmlConverter(const std::string process, const int energy, const float alpha4, const float alpha5, const int generatorNumber);

        /**
         *  @brief Destructor
         */
        ~WeightToXmlConverter();

    private:
        /**
         *  @brief Load the ascii files containing the weight values
         */
        void LoadASCII();

        /**
         *  @brief Save the weights to xml file
         */
        void SaveXml(std::string wightsFileName);

        /**
         *  @brief Convert a number to right string format to use for reading in
         */
        template <class T>
        std::string FileNumberToString(T Number);

        /**
         *  @brief Convert an alpha value to right string format to use for reading in
         */
        template <class T>
        std::string AlphasToStringReading(T Number);

        /**
         *  @brief Convert an alpha value to right string format to use for writing
         */
        template <class T>
        std::string AlphasToStringWriting(T Number);

        /**
         *  @brief Convert a number to a string 
         */
        template <class T>
        std::string NumberToString(T Number);

        /**
         *  @brief Event class for holding information 
         */
        class Event
        {
            private:
//                std::string m_eventType;   ///< Event type
//                std::string m_energy;      ///< Event energy
                int m_eventNumber;         ///< Event number
//                float m_alpha4;            ///< Alpha 4
//                float m_alpha5;            ///< Alpha 5
                float m_weight;            ///< Event weight
            public:
                void SetEventNumber(int eventNumber) { m_eventNumber = eventNumber; } ///< Set event number
//                void SetAlpha4(float alpha4) { m_alpha4 = alpha4; }                   ///< Set alpha 4
//                void SetAlpha5(float alpha5) { m_alpha5 = alpha5; }                   ///< Set alpha 5
                void SetWeight(float weight) { m_weight = weight; }                   ///< Set weight
//                void SetProcess(std::string process) { m_eventType = process; }       ///< Set event type
//                void SetEnergy(std::string energy) { m_energy = energy; }             ///< Set energy
                int GetEventNumber() { return m_eventNumber; }                        ///< Get event number
//                float GetAlpha4() { return m_alpha4; }                                ///< Get alpha 4
//                float GetAlpha5() { return m_alpha5; }                                ///< Get alpha 5
                float GetWeight() { return m_weight; }                                ///< Get weight
//                std::string GetProcess() { return m_eventType; }                      ///< Get process
//                std::string GetEnergy() { return m_energy; }                          ///< Get energy
        };

        typedef std::vector<WeightToXmlConverter::Event*> EventVector;

        EventVector          m_events;              ///< Vector of events 
        const int            m_generatorNumber;     ///< Whizard job set number
        const float          m_alpha4;              ///< Alpha 4
        const float          m_alpha5;              ///< Alpha 5
        const std::string    m_eventType;           ///< Event type
        const int            m_energy;              ///< Energy 
};

#endif
