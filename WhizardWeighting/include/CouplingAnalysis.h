#ifndef WEIGHT_TO_XML_CONVERTER_H
#define WEIGHT_TO_XML_CONVERTER_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TH2F.h"

#include "tinyxml.h"

using namespace std;

enum SuccessEnum {FAILURE, SUCCESS};

class CouplingAnalysis
{
    public:
        CouplingAnalysis();

        ~CouplingAnalysis();

    private:
        void LoadXml();

        void LoadIndividualXml(std::string process, std::string energy, const float alpha4, const float alpha5);

        void AnalyseSingleEvent(const int eventNumber);

        template <class T>
        std::string FileNumberToString(T Number);

        template <class T>
        std::string AlphasToString(T Number);

        template <class T>
        std::string NumberToString(T Number);

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
