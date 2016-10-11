/**
 *  @file   AnalysisScripts/src/CouplingAnalysis.cc
 *
 *  @brief  Implementation of the coupling analysis class.
 *
 *  $Log: $
 */

#include "CouplingAnalysis.h"

//============================================================================

CouplingAnalysis::CouplingAnalysis(const ProcessVector &processVector, PostMVASelection *pPostMVASelection) : 
    m_processVector(processVector),
    m_pPostMVASelection(pPostMVASelection),
    m_eventsNeedingWeights(pPostMVASelection->GetEventsNeedingWeightsList()),
    m_numberUniqueAlpha4(0),
    m_numberUniqueAlpha5(0),
    m_a4IntMin(-5),
    m_a4IntMax(4),
    m_a4Step(0.01f),
    m_a5IntMin(-5),
    m_a5IntMax(4),
    m_a5Step(0.01f),
    m_weightsLoaded(false)
{
    m_weightsDirectory = "/r06/lc/sg568/PhysicsAnalysis/Generator/ee_nunuqqqq/1400GeV/ConcatenatedWeightsXml/";

    for (int a4Int = m_a4IntMin; a4Int < m_a4IntMax+1; a4Int++)
    {
        m_alpha4Vector.push_back((float)(m_a4Step*a4Int));
    }

    for (int a5Int = m_a5IntMin; a5Int < m_a5IntMax+1; a5Int++)
    {
        m_alpha5Vector.push_back((float)(m_a5Step*a5Int));
    }

    std::sort(m_alpha4Vector.begin(), m_alpha4Vector.end());
    std::sort(m_alpha5Vector.begin(), m_alpha5Vector.end());
}

//============================================================================

CouplingAnalysis::~CouplingAnalysis()
{
}

//============================================================================

void CouplingAnalysis::GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight)
{
//std::cout << "void CouplingAnalysis::GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight)" << std::endl;
//std::cout << "void CouplingAnalysis::GetWeight(const int " << eventNumber << ", const float " << alpha4 << ", const float " << alpha5 << ", float &" << eventWeight << ")" << std::endl;
    if (!m_weightsLoaded)
    {
        this->LoadConcatenatedWeightXml();
        m_weightsLoaded = true;
    }
//std::cout << "HERE" << std::endl;
    IntToIntToIntToFloatMap::const_iterator it = m_eventToAlpha4ToAlpha5ToWeightMap.find(eventNumber);

    if (it == m_eventToAlpha4ToAlpha5ToWeightMap.end())
    {
        //std::cout << "Missing event number " << eventNumber << std::endl;
        return;
    }

    if (alpha4 < *(m_alpha4Vector.begin()) or *(m_alpha4Vector.rbegin()) < alpha4 or alpha5 < *(m_alpha5Vector.begin()) or *(m_alpha5Vector.rbegin()) < alpha5)
    {
        //std::cout << "Unable to apply bilinear interpolation to event, please add more weight samples to be able to reweight (alpha4, alpha5) = (" << alpha4 << ", " << alpha5 << ").  Setting event weight to 1." << std::endl;
        eventWeight = 1.f;
    }

    if (alpha4 < *(m_alpha4Vector.begin() + 1) or *(m_alpha4Vector.rbegin() + 1) < alpha4 or alpha5 < *(m_alpha5Vector.begin() + 1) or *(m_alpha5Vector.rbegin() + 1) < alpha5)
    {
        //std::cout << "Unable to apply bicubic interpolation to event, please add more weight samples to be able to reweight (alpha4, alpha5) = (" << alpha4 << ", " << alpha5 << ").  Setting event weight to 1." << std::endl;
        eventWeight = 1.f;
    }

//std::cout << "HERE2" << std::endl;

    IntVector alpha4BoundingKeys = {0, 0, 0, 0}; // alpha 4 between key 1 and 2
    IntVector alpha5BoundingKeys = {0, 0, 0, 0}; // alpha 4 between key 1 and 2

//for (int key : alpha4BoundingKeys)
//{
//std::cout << "alpha4BoundingKeys = " << key << std::endl;
//std::cout << "alpha5BoundingKeys = " << key << std::endl;
//}
    this->SetAlpha4BoundingKeys(alpha4, alpha4BoundingKeys);
    this->SetAlpha5BoundingKeys(alpha5, alpha5BoundingKeys);

//for (unsigned int i = 0; i < 4; i++)
//{
//std::cout << "alpha4BoundingKeys.at(" << i << ") = " << alpha4BoundingKeys.at(i) << std::endl;
//std::cout << "alpha5BoundingKeys.at(" << i << ") = " << alpha5BoundingKeys.at(i) << std::endl;
//}

//std::cout << "HERE3" << std::endl;

    FloatVector alpha4BoundingValues = {0.f, 0.f, 0.f, 0.f};
    FloatVector alpha5BoundingValues = {0.f, 0.f, 0.f, 0.f};

    for (unsigned int i = 0; i < 4; i++)
    {
        //std::cout << "Getting alpha value for bounding index " << i << std::endl;
        //std::cout << "Key Value alpha 4 " << alpha4BoundingKeys.at(i) << std::endl;
        //std::cout << "Key Value alpha 5 " << alpha5BoundingKeys.at(i) << std::endl;

        alpha4BoundingValues.at(i) = this->GetAlpha4(alpha4BoundingKeys.at(i));
        alpha5BoundingValues.at(i) = this->GetAlpha5(alpha5BoundingKeys.at(i));
    }
//std::cout << "HERE4" << std::endl;

    const float lowerA4(alpha4BoundingValues.at(1));
    const float upperA4(alpha4BoundingValues.at(2));
    const float lowerA5(alpha5BoundingValues.at(1));
    const float upperA5(alpha5BoundingValues.at(2));

    const float lowerA4lowerA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(1)).at(alpha5BoundingKeys.at(1)));
    const float lowerA4upperA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(2)).at(alpha5BoundingKeys.at(1)));
    const float upperA4lowerA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(1)).at(alpha5BoundingKeys.at(2)));
    const float upperA4upperA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(2)).at(alpha5BoundingKeys.at(2)));

//    eventWeight = this->BilinearInterpolation(lowerA4lowerA5,lowerA4upperA5,upperA4lowerA5,upperA4upperA5,alpha4,lowerA4,upperA4,alpha5,lowerA5,upperA5);


    const float p00(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(0)).at(alpha5BoundingKeys.at(0)));
    const float p01(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(0)).at(alpha5BoundingKeys.at(1)));
    const float p02(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(0)).at(alpha5BoundingKeys.at(2)));
    const float p03(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(0)).at(alpha5BoundingKeys.at(3)));
    const float p10(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(1)).at(alpha5BoundingKeys.at(0)));
    const float p11(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(1)).at(alpha5BoundingKeys.at(1)));
    const float p12(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(1)).at(alpha5BoundingKeys.at(2)));
    const float p13(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(1)).at(alpha5BoundingKeys.at(3)));
    const float p20(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(2)).at(alpha5BoundingKeys.at(0)));
    const float p21(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(2)).at(alpha5BoundingKeys.at(1)));
    const float p22(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(2)).at(alpha5BoundingKeys.at(2)));
    const float p23(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(2)).at(alpha5BoundingKeys.at(3)));
    const float p30(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(3)).at(alpha5BoundingKeys.at(0)));
    const float p31(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(3)).at(alpha5BoundingKeys.at(1)));
    const float p32(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(3)).at(alpha5BoundingKeys.at(2)));
    const float p33(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4BoundingKeys.at(3)).at(alpha5BoundingKeys.at(3)));

    float p[4][4] = {{p00,p01,p02,p03}, {p10,p11,p12,p13}, {p20,p21,p22,p23}, {p30,p31,p32,p33}};

    const float x = (alpha4 - alpha4BoundingValues.at(1))/(alpha4BoundingValues.at(2) - alpha4BoundingValues.at(1));
    const float y = (alpha5 - alpha5BoundingValues.at(1))/(alpha5BoundingValues.at(2) - alpha5BoundingValues.at(1));
/*
    //std::cout << "p11 : " << p11 << " " << p21 << " p21" << std::endl;
    //std::cout << "p12 : " << p12 << " " << p22 << " p22" << std::endl;
    //std::cout << "Bicubic interpretation : " << this->BicubicInterpolation(p,x,y) << std::endl;
*/
    eventWeight = this->BicubicInterpolation(p,x,y);
}

//============================================================================

PostMVASelection *CouplingAnalysis::GetPostMVASelection() const
{
    return m_pPostMVASelection;
}
    
//============================================================================ Read in Concatenated Data

void CouplingAnalysis::LoadConcatenatedWeightXml()
{
    TSystemDirectory *pTSystemDirectoryWeightFiles =  new TSystemDirectory(m_weightsDirectory.c_str(), m_weightsDirectory.c_str());
    TList *pTListWeightFiles = pTSystemDirectoryWeightFiles->GetListOfFiles();
    pTListWeightFiles->Sort(); // Alphabetises the list

    if (pTListWeightFiles)
    {
        TSystemFile *pTSystemFileWeightFile;
        TIter next(pTListWeightFiles);

        while ((pTSystemFileWeightFile=(TSystemFile*)next()))
        {
            TString weightFileCandidate = pTSystemFileWeightFile->GetName();
            if (!pTSystemFileWeightFile->IsDirectory() and weightFileCandidate.EndsWith("xml") and weightFileCandidate.Contains("ConcatenatedWeights"))
            {
                std::string weightFileToLoad = m_weightsDirectory + weightFileCandidate.Data();
//std::cout << "Reading in " << weightFileToLoad << std::endl;
                this->LoadIndividualConcatenatedWeightXml(weightFileToLoad);
            }
        }
    }
    delete pTListWeightFiles, pTSystemDirectoryWeightFiles;
}

//============================================================================

void CouplingAnalysis::LoadIndividualConcatenatedWeightXml(std::string weightFileToLoad)
{
    TiXmlDocument *pTiXmlDocument = new TiXmlDocument();

    if (!pTiXmlDocument->LoadFile(weightFileToLoad.c_str()))
    {
        std::cerr << pTiXmlDocument->ErrorDesc() << std::endl;
    }

    TiXmlElement *pDocumentTiXmlElement = pTiXmlDocument->FirstChildElement();

    for (TiXmlElement *pHeadTiXmlElement = pDocumentTiXmlElement->FirstChildElement(); pHeadTiXmlElement != NULL; pHeadTiXmlElement = pHeadTiXmlElement->NextSiblingElement())
    {
        if (pHeadTiXmlElement == NULL)
        {
            std::cerr << "Failed to load file: No root element." << std::endl;
            pTiXmlDocument->Clear();
        }

        std::string process(pHeadTiXmlElement->Attribute("EventType"));
        std::string energy(pHeadTiXmlElement->Attribute("Energy"));
        const float alpha4(atof(pHeadTiXmlElement->Attribute("Alpha_Four")));
        const float alpha5(atof(pHeadTiXmlElement->Attribute("Alpha_Five")));

        for (TiXmlElement *pSubTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pSubTiXmlElement != NULL; pSubTiXmlElement = pSubTiXmlElement->NextSiblingElement())
        {
            const int eventNumber(atoi(pSubTiXmlElement->Attribute("Event_Number")));
            const float weight(atof(pSubTiXmlElement->Attribute("Ratio_of_Integrands")));

            if (!this->DoesAlpha4KeyExist(alpha4))
                this->SetAlpha4Key(alpha4);

            if (!this->DoesAlpha5KeyExist(alpha5))
                this->SetAlpha5Key(alpha5);

            const int alpha4Key(this->GetAlpha4Key(alpha4));
            const int alpha5Key(this->GetAlpha5Key(alpha5));

            m_eventToAlpha4ToAlpha5ToWeightMap[eventNumber][alpha4Key][alpha5Key] = weight;
        }
    }

    pTiXmlDocument->Clear();
    delete pTiXmlDocument, pDocumentTiXmlElement;
}

//============================================================================

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type 
CouplingAnalysis::AlmostEqual(T x, T y, int ulp = 2) const
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    // unless the result is subnormal
    return std::abs(x-y) < std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp || std::abs(x-y) < std::numeric_limits<T>::min();
}

//============================================================================

bool CouplingAnalysis::DoesAlpha4KeyExist(const float alpha4) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha4Map.begin(); iter != m_keyToAlpha4Map.end(); ++iter)
    {
//std::cout << "Comparing " << iter->second << " with " << alpha4 << std::endl;
        if (this->AlmostEqual(iter->second, alpha4))
        {
            //std::cout << "Match!" << std::endl;
            return true;
        }
    }
    //std::cout << "No Match" << std::endl;
    return false;
}

//============================================================================

void CouplingAnalysis::SetAlpha4Key(const float alpha4)
{
    m_keyToAlpha4Map.insert(std::make_pair(m_numberUniqueAlpha4,alpha4));
    m_numberUniqueAlpha4++;
    m_alpha4Vector.push_back(alpha4);
}

//============================================================================

int CouplingAnalysis::GetAlpha4Key(const float alpha4) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha4Map.begin(); iter != m_keyToAlpha4Map.end(); ++iter)
    {
        if (this->AlmostEqual(iter->second, alpha4))
        {
            return iter->first;
        }
    }

//std::cout << "int CouplingAnalysis::GetAlpha4Key(const float alpha4) const" << std::endl;
//std::cout << "int CouplingAnalysis::GetAlpha4Key(const float " << alpha4 << ") const" << std::endl;
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha4Map.begin(); iter != m_keyToAlpha4Map.end(); ++iter)
    {
//std::cout << "Map Contains : (" << iter->first << ", " << iter->second << ")" << std::endl;
//std::cout << "alpha " << alpha4 << std::endl;
    }
    return -1;
}

//============================================================================

float CouplingAnalysis::GetAlpha4(int key) const
{
//std::cout << "HERE5" << std::endl;
//std::cout << "key to search " << key << std::endl;
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha4Map.begin(); iter != m_keyToAlpha4Map.end(); ++iter)
    {
//std::cout << "Map Contains : (" << iter->first << ", " << iter->second << std::endl;
    }

    return m_keyToAlpha4Map.at(key);
//std::cout << "HERE5b" << std::endl;
}

//============================================================================

bool CouplingAnalysis::DoesAlpha5KeyExist(const float alpha5) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha5Map.begin(); iter != m_keyToAlpha5Map.end(); ++iter)
    {
        if (this->AlmostEqual(iter->second, alpha5))
            return true;
    }
    return false;
}

//============================================================================

void CouplingAnalysis::SetAlpha5Key(const float alpha5)
{
    m_keyToAlpha5Map.insert(std::make_pair(m_numberUniqueAlpha5,alpha5));
    m_numberUniqueAlpha5++;
    m_alpha5Vector.push_back(alpha5);
}

//============================================================================

int CouplingAnalysis::GetAlpha5Key(const float alpha5) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha5Map.begin(); iter != m_keyToAlpha5Map.end(); ++iter)
    {
        if (this->AlmostEqual(iter->second, alpha5))
        {
            return iter->first;
        }
    }
}

//============================================================================

float CouplingAnalysis::GetAlpha5(int key) const
{
//std::cout << "HERE6" << std::endl;
    return m_keyToAlpha5Map.at(key);
}

//============================================================================ Do Weighting

void CouplingAnalysis::SetAlpha4BoundingKeys(const float alpha4, IntVector &alpha4BoundingKeys) const
{
    for (FloatVector::const_iterator iter = m_alpha4Vector.begin(); iter != m_alpha4Vector.end() - 1; iter++)
    {
        const int position(iter - m_alpha4Vector.begin());

        if (m_alpha4Vector.at(position) <= alpha4 and alpha4 < m_alpha4Vector.at(position+1))
        { 
//std::cout << "position : " << position << std::endl;
//std::cout << "position-1 : " << position-1 << std::endl;
//std::cout << "m_alpha4Vector.at(position-1) : " << m_alpha4Vector.at(position-1) << std::endl;
//std::cout << "m_alpha4Vector.at(position) : " << m_alpha4Vector.at(position) << std::endl;
//std::cout << "m_alpha4Vector.at(position+1) : " << m_alpha4Vector.at(position+1) << std::endl;
//std::cout << "m_alpha4Vector.at(position+2) : " << m_alpha4Vector.at(position+2) << std::endl;
//std::cout << "alpha4BoundingKeys->at(0) " << alpha4BoundingKeys.at(0) << std::endl;
            alpha4BoundingKeys.at(0) = this->GetAlpha4Key(m_alpha4Vector.at(position-1));
//std::cout << "alpha4BoundingKeys->at(0) " << alpha4BoundingKeys.at(0) << std::endl;
            alpha4BoundingKeys.at(1) = this->GetAlpha4Key(m_alpha4Vector.at(position));
            alpha4BoundingKeys.at(2) = this->GetAlpha4Key(m_alpha4Vector.at(position+1));
            alpha4BoundingKeys.at(3) = this->GetAlpha4Key(m_alpha4Vector.at(position+2));
            return;
        }
    }
}

//============================================================================

void CouplingAnalysis::SetAlpha5BoundingKeys(const float alpha5, IntVector &alpha5BoundingKeys) const 
{
    for (FloatVector::const_iterator iter = m_alpha5Vector.begin(); iter != m_alpha5Vector.end() - 1; iter++)
    {
        const int position(iter - m_alpha5Vector.begin());
        if (m_alpha5Vector.at(position) <= alpha5 and alpha5 < m_alpha5Vector.at(position+1))
        {
//std::cout << "position : " << position << std::endl;
//std::cout << "m_alpha5Vector.at(position-1) : " << m_alpha5Vector.at(position-1) << std::endl;
//std::cout << "m_alpha5Vector.at(position) : " << m_alpha5Vector.at(position) << std::endl;
//std::cout << "m_alpha5Vector.at(position+1) : " << m_alpha5Vector.at(position+1) << std::endl;
//std::cout << "m_alpha5Vector.at(position+2) : " << m_alpha5Vector.at(position+2) << std::endl;

            alpha5BoundingKeys.at(0) = this->GetAlpha5Key(m_alpha5Vector.at(position-1));
            alpha5BoundingKeys.at(1) = this->GetAlpha5Key(m_alpha5Vector.at(position));
            alpha5BoundingKeys.at(2) = this->GetAlpha5Key(m_alpha5Vector.at(position+1));
            alpha5BoundingKeys.at(3) = this->GetAlpha5Key(m_alpha5Vector.at(position+2));
            return;
        }
    }
}

//============================================================================

float CouplingAnalysis::BilinearInterpolation(const float f11, const float f12, const float f21, const float f22, const float x, const float x1, const float x2, const float y, const float y1, const float y2) const
{
    const float numerator((x2-x) * ((f11 * (y2-y)) + (f12 * (y-y1))) + (x-x1) * ((f21 * (y2-y)) + (f22 * (y-y1))));
    const float denominator((x2-x1)*(y2-y1));
    return numerator/denominator;
}

//============================================================================

float CouplingAnalysis::CubicInterpolation(float p[4], float x) 
{
    return p[1] + 0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

//============================================================================

float CouplingAnalysis::BicubicInterpolation(float p[4][4], float x, float y) 
{
    float arr[4];
    arr[0] = this->CubicInterpolation(p[0], y);
    arr[1] = this->CubicInterpolation(p[1], y);
    arr[2] = this->CubicInterpolation(p[2], y);
    arr[3] = this->CubicInterpolation(p[3], y);
    return this->CubicInterpolation(arr, x);
}

//============================================================================ Helper

//void CouplingAnalysis::Print() const
//{
//
//}

//============================================================================

template <class T>
std::string CouplingAnalysis::NumberToString(T Number) const 
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string CouplingAnalysis::FileNumberToString(T Number) const 
{
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(3) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string CouplingAnalysis::AlphasToString(T Number) const 
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(5) << Number;
    return ss.str();
}

//============================================================================
