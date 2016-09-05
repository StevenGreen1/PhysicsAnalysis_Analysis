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

using namespace std;

enum SuccessEnum {FAILURE, SUCCESS};

class CouplingAnalysis
{
    typedef std::vector<float> FloatVector;
    typedef std::map<int, float> IntToFloatMap;
    typedef std::map<int, IntToFloatMap > IntToIntToFloatMap;
    typedef std::map<int, IntToIntToFloatMap > IntToIntToIntToFloatMap;

    public:
        /**
         * @brief Constructor
         */
        CouplingAnalysis(std::string process, std::string energy);

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
         * @brief Load all the xml files containing the reweighting information
         */
        void LoadXml();

        /**
         * @brief Load a single xml file containing the reweighting information
         *
         * @param alpha4 value used in weight information for the loaded xml file
         * @param alpha5 value used in weight information for the loaded xml file
         */
        void LoadIndividualXml(const float alpha4, const float alpha5);

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

        bool DoFloatsMatch(float a, float b) const;

        /**
         * @brief Find the int key to the stored values of alpha4 that were simulated in whizard.  If not in m_Alpha4Vector add to vector and make new key.
         *
         * @param alpha4 value simulated in whizard
         * @param alpha4Key integer key to alpha4 value simulated in whizard
         */
        void SetAlpha4Key(const float alpha4, int &alpha4Key);

        /**
         * @brief Find the int key to the stored values of alpha4 that were simulated in whizard.  Do nothing if not found in m_Alpha4Vector.
         *
         * @param alpha4 value simulated in whizard
         * @param alpha4Key integer key to alpha4 value simulated in whizard
         */
        void GetAlpha4Key(const float alpha4, int &alpha4Key) const;

        /**
         * @brief Find the int key to the stored values of alpha5 that were simulated in whizard.  If not in m_Alpha5Vector add to vector and make new key.
         *
         * @param alpha5 value simulated in whizard
         * @param alpha5Key integer key to alpha4 value simulated in whizard
         */
        void SetAlpha5Key(const float alpha5, int &alpha5Key);

        /**
         * @brief Find the int key to the stored values of alpha5 that were simulated in whizard.  Do nothing if not found in m_Alpha4Vector.
         *
         * @param alpha5 value simulated in whizard
         * @param alpha5Key integer key to alpha4 value simulated in whizard
         */
        void GetAlpha5Key(const float alpha5, int &alpha5Key) const;

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

        std::string             m_process;                          ///< String of process under consideration
        std::string             m_energy;                           ///< Energy of process under consideration
        int                     m_NumberUniqueAlpha4;               ///< Number of unique values of alpha4 simulated in whizard and read in
        int                     m_NumberUniqueAlpha5;               ///< Number of unique values of alpha5 simulated in whizard and read in
        FloatVector             m_Alpha4Vector;                     ///< Vector of unique values of alpha4 simulated in whizard and read in
        FloatVector             m_Alpha5Vector;                     ///< Vector of unique values of alpha5 simulated in whizard and read in
        IntToFloatMap           m_KeyToAlpha4Map;                   ///< Map of integer keys to unique values of alpha4 simulated in whizard 
        IntToFloatMap           m_KeyToAlpha5Map;                   ///< Map of integer keys to unique values of alpha5 simulated in whizard
        IntToIntToIntToFloatMap m_EventToAlpha4ToAlpha5ToWeightMap; ///< Map of event number to alpha4 to alpha5 to event weight 
};

#endif
