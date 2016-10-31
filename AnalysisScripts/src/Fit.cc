/**
 *  @file   AnalysisScripts/src/Fit.cc 
 * 
 *  @brief  Implementation of the fit class.
 * 
 *  $Log: $
 */

#include "Fit.h"

#include "TSystem.h"
#include <fcntl.h>

void Pause();

//=====================================================================

Fit::Fit(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, std::string descriptor) : 
    m_processVector(processVector),
    m_pPostMVASelection(pCouplingAnalysis->GetPostMVASelection()),
    m_pCouplingAnalysis(pCouplingAnalysis),
    m_descriptor(descriptor),
    m_alpha4IntMinGlobal(-40),
    m_alpha4IntMaxGlobal(40),
    m_alpha4StepGlobal(0.001f),
    m_alpha5IntMinGlobal(-40),
    m_alpha5IntMaxGlobal(40),
    m_alpha5StepGlobal(0.001f),
    m_wBosonMass(80.385f),
    m_zBosonMass(91.1876f),
    m_binsInFit(25),
    m_rootFileName(descriptor + "FitData.root")
{
    TH1::AddDirectory(kFALSE);

    // Make things look pretty 
    m_red = {0.0, 0.00392156862745, 0.835294117647, 1.0, 0.619607843137, 0.0549019607843, 1.0, 0.0, 0.0, 0.58431372549, 1.0, 0.643137254902, 0.0, 0.56862745098, 0.38431372549, 0.419607843137, 0.0, 0.0, 0.41568627451, 0.0, 0.760784313725, 0.745098039216, 0.0, 0.372549019608, 1.0, 1.0, 1.0, 0.407843137255, 1.0, 0.588235294118, 0.596078431373, 0.654901960784, 0.00392156862745, 1.0, 0.996078431373, 0.741176470588, 0.00392156862745, 0.733333333333, 0.458823529412, 0.647058823529, 1.0, 0.466666666667, 0.478431372549, 0.149019607843, 0.0, 0.262745098039, 0.709803921569, 1.0, 1.0, 0.564705882353, 0.494117647059, 0.741176470588, 0.898039215686, 0.870588235294, 0.0, 0.0, 0.0, 0.0, 0.521568627451, 0.0, 0.470588235294, 0.0, 1.0, 0.909803921569};
    m_green = {0.0, 0.0, 1.0, 0.0, 0.0, 0.298039215686, 0.898039215686, 0.372549019608, 1.0, 0.0, 0.576470588235, 0.141176470588, 0.0823529411765, 0.81568627451, 0.0549019607843, 0.407843137255, 0.0, 0.490196078431, 0.509803921569, 0.682352941176, 0.549019607843, 0.6, 0.560784313725, 0.678431372549, 0.0, 0.0, 0.0078431372549, 0.239215686275, 0.454901960784, 0.541176470588, 1.0, 0.341176470588, 1.0, 0.933333333333, 0.537254901961, 0.776470588235, 0.81568627451, 0.533333333333, 0.266666666667, 1.0, 0.650980392157, 0.301960784314, 0.278431372549, 0.203921568627, 0.278431372549, 0.0, 0.0, 0.694117647059, 0.858823529412, 0.98431372549, 0.176470588235, 0.827450980392, 0.435294117647, 1.0, 1.0, 0.607843137255, 0.392156862745, 0.462745098039, 0.662745098039, 0.725490196078, 0.509803921569, 1.0, 0.43137254902, 0.36862745098};
    m_blue = {0.0, 0.403921568627, 0.0, 0.337254901961, 0.556862745098, 0.63137254902, 0.0078431372549, 0.223529411765, 0.0, 0.227450980392, 0.494117647059, 0.0, 0.266666666667, 0.796078431373, 0.0, 0.509803921569, 1.0, 0.709803921569, 0.423529411765, 0.494117647059, 0.623529411765, 0.439215686275, 0.611764705882, 0.305882352941, 0.0, 0.964705882353, 0.61568627451, 0.23137254902, 0.639215686275, 0.909803921569, 0.321568627451, 0.250980392157, 0.996078431373, 0.909803921569, 0.0, 1.0, 1.0, 0.0, 0.694117647059, 0.823529411765, 0.996078431373, 0.0, 0.509803921569, 0.0, 0.329411764706, 0.172549019608, 1.0, 0.403921568627, 0.4, 0.572549019608, 0.823529411765, 0.576470588235, 0.996078431373, 0.454901960784, 0.470588235294, 1.0, 0.00392156862745, 1.0, 0.0, 0.0901960784314, 0.192156862745, 0.776470588235, 0.254901960784, 0.745098039216};

    m_fillStyle = {3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001};

    // Output data file
    m_pTFile = new TFile(m_rootFileName.c_str(), "recreate");


    const float alpha4(blah...);
    const float alpha5(blah...);

    this->GetNNL(alpha4, alpha5);






    for (int alpha4Int = m_alpha4IntMinGlobal; alpha4Int < m_alpha4IntMaxGlobal+1; alpha4Int = alpha4Int + 4)
    {
        m_alpha4IntMin = alpha4Int;
        m_alpha4IntMax = alpha4Int + 3;

        if (m_alpha4IntMax > m_alpha4IntMaxGlobal)
            m_alpha4IntMax = m_alpha4IntMaxGlobal;

std::cout << "m_alpha4IntMin " << m_alpha4IntMin << std::endl;
std::cout << "m_alpha4IntMax " << m_alpha4IntMax << std::endl;

        m_alpha4Step = m_alpha4StepGlobal;
        m_alpha5IntMin = m_alpha5IntMinGlobal;
        m_alpha5IntMax = m_alpha5IntMaxGlobal;
        m_alpha5Step = m_alpha5StepGlobal;

std::cout << "m_alpha5IntMin " << m_alpha5IntMin << std::endl;
std::cout << "m_alpha5IntMax " << m_alpha5IntMax << std::endl;

        this->Initialise();
        this->FillDistribution();
        this->AnalyseDistribution();
        this->Clear();
    }

    this->SaveDistribution();
}

//=====================================================================

Fit::~Fit()
{
}

//=====================================================================

void Fit::Initialise()
{
    // Reference distributions for log likelihood fit
    std::shared_ptr<TH1F> pTH1F_CTSWJetsRef(new TH1F("CTSWJetsRef","Reference Cos#theta_{WJets}^{*}",m_binsInFit,0,1));
    m_pTH1F_CTSWJetsRef = std::move(pTH1F_CTSWJetsRef);
    std::shared_ptr<TH1F> pTH1F_CTSWBosonsRef(new TH1F("CTSWBosonsRef","Reference Cos#theta_{WBosons}^{*}",m_binsInFit,0,1));
    m_pTH1F_CTSWBosonsRef = std::move(pTH1F_CTSWBosonsRef);
    std::shared_ptr<TH2F> pTH2F_CTSWJets_vs_CTSWBosonsRef(new TH2F("CTSWJets_vs_CTSWBosonsRef","Reference Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_binsInFit,0,1,m_binsInFit,0,1));
    m_pTH2F_CTSWJets_vs_CTSWBosonsRef = std::move(pTH2F_CTSWJets_vs_CTSWBosonsRef);

    std::shared_ptr<TH1F> pTH1F_CTSZJetsRef(new TH1F("CTSZJetsRef","Reference Cos#theta_{ZJets}^{*}",m_binsInFit,0,1));
    m_pTH1F_CTSZJetsRef = std::move(pTH1F_CTSZJetsRef);
    std::shared_ptr<TH1F> pTH1F_CTSZBosonsRef(new TH1F("CTSZBosonsRef","Reference Cos#theta_{ZBosons}^{*}",m_binsInFit,0,1));
    m_pTH1F_CTSZBosonsRef = std::move(pTH1F_CTSZBosonsRef);
    std::shared_ptr<TH2F> pTH2F_CTSZJets_vs_CTSZBosonsRef(new TH2F("CTSZJets_vs_CTSZBosonsRef","Reference Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_binsInFit,0,1,m_binsInFit,0,1));
    m_pTH2F_CTSZJets_vs_CTSZBosonsRef = std::move(pTH2F_CTSZJets_vs_CTSZBosonsRef);

    // Make containters for stack plot
/*
    for (const auto &process: m_processVector)
    {
        std::string nameCTSWJetsStack =  "StackCTSWJets";
        std::string titleCTSWJetsStack = "For Stack Cos#theta_{WJets}^{*}";
        m_eventTypeToCTSJets[process.GetEventType()] =  new TH1F(nameCTSWJetsStack.c_str(), titleCTSWJetsStack.c_str(),m_binsInFit,0,1);
    }
*/

    // Make containters for non zero alpha4 and alpha5 distributions
    for (int alpha4Int = m_alpha4IntMin; alpha4Int < m_alpha4IntMax+1; alpha4Int++)
    {
        for (int alpha5Int = m_alpha5IntMin; alpha5Int < m_alpha5IntMax+1; alpha5Int++)
        {
            std::string nameCTSWJets =  "CTSWJets_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string titleCTSWJets = "Cos#theta_{WJets}^{*}";
//            TH1F *pTH1F_CTSWJets = new TH1F(nameCTSWJets.c_str(), titleCTSWJets.c_str(), m_binsInFit, 0 ,1);
            std::shared_ptr<TH1F> pTH1F_CTSWJets(new TH1F(nameCTSWJets.c_str(), titleCTSWJets.c_str(), m_binsInFit, 0 ,1)); 
            m_mapAlphaIntToCTSWJets[alpha4Int][alpha5Int] = std::move(pTH1F_CTSWJets);
//(TH1F*)(pTH1F_CTSWJets->Clone());

            std::string nameCTSWBoson = "CTSWBosons_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string titleCTSWBoson = "Cos#theta_{WBoson}^{*}";
//            TH1F *pTH1F_CTSWBoson = new TH1F(nameCTSWBoson.c_str(), titleCTSWBoson.c_str(), m_binsInFit, 0 ,1);
            std::shared_ptr<TH1F> pTH1F_CTSWBoson(new TH1F(nameCTSWBoson.c_str(), titleCTSWBoson.c_str(), m_binsInFit, 0 ,1));
            m_mapAlphaIntToCTSWBosons[alpha4Int][alpha5Int] = std::move(pTH1F_CTSWBoson);
// (TH1F*)(pTH1F_CTSWBoson->Clone());

            std::string nameCTSWJets_vs_CTSWBosons =  "CTSWJets_vs_CTSWBosons_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string titleCTSWJets_vs_CTSWBosons = "Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}";
//            TH2F *pTH2F_CTSWJets_vs_CTSWBosons = new TH2F(nameCTSWJets_vs_CTSWBosons.c_str(), titleCTSWJets_vs_CTSWBosons.c_str(), m_binsInFit, 0, 1, m_binsInFit, 0, 1);
            std::shared_ptr<TH2F> pTH2F_CTSWJets_vs_CTSWBosons(new TH2F(nameCTSWJets_vs_CTSWBosons.c_str(), titleCTSWJets_vs_CTSWBosons.c_str(), m_binsInFit, 0, 1, m_binsInFit, 0, 1));
            m_mapAlphaIntToCTSWJets_vs_CTSWBosons[alpha4Int][alpha5Int] = std::move(pTH2F_CTSWJets_vs_CTSWBosons);
//(TH2F*)(pTH2F_CTSWJets_vs_CTSWBosons->Clone());

            std::string nameCTSZJets =  "CTSZJets_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string titleCTSZJets = "Cos#theta_{ZJets}^{*}";
//            TH1F *pTH1F_CTSZJets = new TH1F(nameCTSZJets.c_str(), titleCTSZJets.c_str(), m_binsInFit, 0 ,1);
            std::shared_ptr<TH1F> pTH1F_CTSZJets(new TH1F(nameCTSZJets.c_str(), titleCTSZJets.c_str(), m_binsInFit, 0 ,1));
            m_mapAlphaIntToCTSZJets[alpha4Int][alpha5Int] = std::move(pTH1F_CTSZJets);
//(TH1F*)(pTH1F_CTSZJets->Clone());

            std::string nameCTSZBoson = "CTSZBosons_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string titleCTSZBoson = "Cos#theta_{ZBoson}^{*}";
//            TH1F *pTH1F_CTSZBoson = new TH1F(nameCTSZBoson.c_str(), titleCTSZBoson.c_str(), m_binsInFit, 0 ,1);
            std::shared_ptr<TH1F> pTH1F_CTSZBoson(new TH1F(nameCTSZBoson.c_str(), titleCTSZBoson.c_str(), m_binsInFit, 0 ,1));
            m_mapAlphaIntToCTSZBosons[alpha4Int][alpha5Int] = std::move(pTH1F_CTSZBoson);
//(TH1F*)(pTH1F_CTSZBoson->Clone());

            std::string nameCTSZJets_vs_CTSZBosons =  "CTSZJets_vs_CTSZBosons_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string titleCTSZJets_vs_CTSZBosons = "Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}";
//            TH2F *pTH2F_CTSZJets_vs_CTSZBosons = new TH2F(nameCTSZJets_vs_CTSZBosons.c_str(), titleCTSZJets_vs_CTSZBosons.c_str(), m_binsInFit, 0, 1, m_binsInFit, 0, 1);
            std::shared_ptr<TH2F> pTH2F_CTSZJets_vs_CTSZBosons(new TH2F(nameCTSZJets_vs_CTSZBosons.c_str(), titleCTSZJets_vs_CTSZBosons.c_str(), m_binsInFit, 0, 1, m_binsInFit, 0, 1));
            m_mapAlphaIntToCTSZJets_vs_CTSZBosons[alpha4Int][alpha5Int] = std::move(pTH2F_CTSZJets_vs_CTSZBosons);
//(TH2F*)(pTH2F_CTSZJets_vs_CTSZBosons->Clone());

//            delete pTH1F_CTSWJets, pTH1F_CTSWBoson, pTH2F_CTSWJets_vs_CTSWBosons, pTH1F_CTSZJets, pTH1F_CTSZBoson, pTH2F_CTSZJets_vs_CTSZBosons;
        }
    }
}

//=====================================================================

void Fit::Clear()
{
//    delete m_pTH1F_CTSWJetsRef, m_pTH1F_CTSWBosonsRef, m_pTH2F_CTSWJets_vs_CTSWBosonsRef, m_pTH1F_CTSZJetsRef, m_pTH1F_CTSZBosonsRef, m_pTH2F_CTSZJets_vs_CTSZBosonsRef;

//    this->DeletePointersInMap(m_mapAlphaIntToCTSWJets);
    m_mapAlphaIntToCTSWJets.clear();

//    this->DeletePointersInMap(m_mapAlphaIntToCTSWBosons);
    m_mapAlphaIntToCTSWBosons.clear();

//    this->DeletePointersInMap(m_mapAlphaIntToCTSWJets_vs_CTSWBosons);
    m_mapAlphaIntToCTSWJets_vs_CTSWBosons.clear();

//    this->DeletePointersInMap(m_mapAlphaIntToCTSZJets);
    m_mapAlphaIntToCTSZJets.clear();

//    this->DeletePointersInMap(m_mapAlphaIntToCTSZBosons);
    m_mapAlphaIntToCTSZBosons.clear();

//    this->DeletePointersInMap(m_mapAlphaIntToCTSZJets_vs_CTSZBosons);
    m_mapAlphaIntToCTSZJets_vs_CTSZBosons.clear();
}

//=====================================================================

template <class Map>
void Fit::DeletePointersInMap(Map map)
{
    for (auto it: map)
    {
        for (auto iter: it.second)
        {
            delete iter.second;
        }
    }
}

//=====================================================================

void Fit::FillDistribution()
{
    for (const auto &pProcess: m_processVector)
    {
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons(std::numeric_limits<int>::max());
        Double_t transverseMomentum(std::numeric_limits<double>::max());
        Double_t invariantMassSystem(std::numeric_limits<double>::max());
        Double_t ctsWBoson(std::numeric_limits<double>::max());
        Double_t ctsWJet1(std::numeric_limits<double>::max());
        Double_t ctsWJet2(std::numeric_limits<double>::max());
        Double_t invMassWBoson1(std::numeric_limits<double>::max());
        Double_t invMassWBoson2(std::numeric_limits<double>::max());
        Double_t ctsZBoson(std::numeric_limits<double>::max());
        Double_t ctsZJet1(std::numeric_limits<double>::max());
        Double_t ctsZJet2(std::numeric_limits<double>::max());
        Double_t invMassZBoson1(std::numeric_limits<double>::max());
        Double_t invMassZBoson2(std::numeric_limits<double>::max());

        Double_t bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("CosThetaStarWBosons", &ctsWBoson);
        pTChain->SetBranchAddress("CosThetaStarWJet1", &ctsWJet1);
        pTChain->SetBranchAddress("CosThetaStarWJet2", &ctsWJet2);
        pTChain->SetBranchAddress("InvMassWVector1", &invMassWBoson1);
        pTChain->SetBranchAddress("InvMassWVector2", &invMassWBoson2);
        pTChain->SetBranchAddress("CosThetaStarZBosons", &ctsZBoson);
        pTChain->SetBranchAddress("CosThetaStarZJet1", &ctsZJet1);
        pTChain->SetBranchAddress("CosThetaStarZJet2", &ctsZJet2);
        pTChain->SetBranchAddress("InvMassZVector1", &invMassZBoson1);
        pTChain->SetBranchAddress("InvMassZVector2", &invMassZBoson2);

        pTChain->SetBranchAddress("BDT", &bdt);

        int nEventsToProcess(pTChain->GetEntries() > 2000 ? 2000 : pTChain->GetEntries());

        for (unsigned int event = 0; event < nEventsToProcess; event++)
        {
            pTChain->GetEntry(event);

            // Cuts
            if (bdt < m_pPostMVASelection->GetBDTLowCut() or m_pPostMVASelection->GetBDTHighCut() < bdt)
                continue;
            if (nIsolatedLeptons < m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsLowCut() or m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumLowCut() or m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemLowCut() or m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemHighCut() < invariantMassSystem)
                continue;

            double rW = std::sqrt( (m_wBosonMass - invMassWBoson1) * (m_wBosonMass - invMassWBoson1) + (m_wBosonMass - invMassWBoson2) * (m_wBosonMass - invMassWBoson2) );
            double rZ = std::sqrt( (m_zBosonMass - invMassZBoson1) * (m_zBosonMass - invMassZBoson1) + (m_zBosonMass - invMassZBoson2) * (m_zBosonMass - invMassZBoson2) );

            bool isW(false);

            if (rZ > rW)
                isW = true;
            else
                isW = false;

            if (isW)
            {
                // Fill Reference Distributions
                m_pTH1F_CTSWJetsRef->Fill(ctsWJet1, weight);
                m_pTH1F_CTSWJetsRef->Fill(ctsWJet2, weight);
                m_pTH1F_CTSWBosonsRef->Fill(ctsWBoson,weight);
                m_pTH2F_CTSWJets_vs_CTSWBosonsRef->Fill(ctsWJet1, ctsWBoson, weight);
                m_pTH2F_CTSWJets_vs_CTSWBosonsRef->Fill(ctsWJet2, ctsWBoson, weight);

                // Fill Weighted Distribution
                for (int alpha4Int = m_alpha4IntMin; alpha4Int < m_alpha4IntMax+1; alpha4Int++)
                {
                    for (int alpha5Int = m_alpha5IntMin; alpha5Int < m_alpha5IntMax+1; alpha5Int++)
                    {
                        float matrixElementWeight(1.f);

                        if (pProcess->GetEventType() == "ee_nunuqqqq")
                        {
                            const float alpha4(m_alpha4Step * (float)(alpha4Int));
                            const float alpha5(m_alpha5Step * (float)(alpha5Int));
                            m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                        }

                        m_mapAlphaIntToCTSWBosons[alpha4Int][alpha5Int]->Fill(ctsWBoson, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSWJets[alpha4Int][alpha5Int]->Fill(ctsWJet1, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSWJets[alpha4Int][alpha5Int]->Fill(ctsWJet2, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSWJets_vs_CTSWBosons[alpha4Int][alpha5Int]->Fill(ctsWJet1, ctsWBoson, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSWJets_vs_CTSWBosons[alpha4Int][alpha5Int]->Fill(ctsWJet2, ctsWBoson, weight*matrixElementWeight);
                    }
                }
            }

            else
            {
                // Fill Reference Distributions
                m_pTH1F_CTSZJetsRef->Fill(ctsZJet1, weight);
                m_pTH1F_CTSZJetsRef->Fill(ctsZJet2, weight);
                m_pTH1F_CTSZBosonsRef->Fill(ctsZBoson,weight);
                m_pTH2F_CTSZJets_vs_CTSZBosonsRef->Fill(ctsZJet1, ctsZBoson, weight);
                m_pTH2F_CTSZJets_vs_CTSZBosonsRef->Fill(ctsZJet2, ctsZBoson, weight);

                // Fill Weighted Distribution
                for (int alpha4Int = m_alpha4IntMin; alpha4Int < m_alpha4IntMax+1; alpha4Int++)
                {
                    for (int alpha5Int = m_alpha5IntMin; alpha5Int < m_alpha5IntMax+1; alpha5Int++)
                    {
                        float matrixElementWeight(1.f);

                        if (pProcess->GetEventType() == "ee_nunuqqqq")
                        {
                            const float alpha4(m_alpha4Step * (float)(alpha4Int));
                            const float alpha5(m_alpha5Step * (float)(alpha5Int));
                            m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                        }

                        m_mapAlphaIntToCTSZBosons[alpha4Int][alpha5Int]->Fill(ctsZBoson, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSZJets[alpha4Int][alpha5Int]->Fill(ctsZJet1, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSZJets[alpha4Int][alpha5Int]->Fill(ctsZJet2, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSZJets_vs_CTSZBosons[alpha4Int][alpha5Int]->Fill(ctsZJet1, ctsZBoson, weight*matrixElementWeight);
                        m_mapAlphaIntToCTSZJets_vs_CTSZBosons[alpha4Int][alpha5Int]->Fill(ctsZJet2, ctsZBoson, weight*matrixElementWeight);
                    }
                }
            }
/*
            m_eventTypeToCTSJets[process.GetEventType()]->Fill(ctsWJet1, weight);
            m_eventTypeToCTSJets[process.GetEventType()]->Fill(ctsWJet2, weight);
*/
        }
    } 
}

//=====================================================================

void Fit::AnalyseDistribution()
{
    this->AnalyseCTSJets(m_pTH1F_CTSWJetsRef, m_mapAlphaIntToCTSWJets, m_nllCTSWJets);
    this->AnalyseCTSJets(m_pTH1F_CTSZJetsRef, m_mapAlphaIntToCTSZJets, m_nllCTSZJets);
    //this->MakeStackCTSWJets()
//    this->AnalyseCTSWBosons();
    this->AnalyseCTSJets_vs_CTSBosons(m_pTH2F_CTSWJets_vs_CTSWBosonsRef, m_mapAlphaIntToCTSWJets_vs_CTSWBosons, m_nllCTSWJets_vs_CTSWBosons);
    this->AnalyseCTSJets_vs_CTSBosons(m_pTH2F_CTSZJets_vs_CTSZBosonsRef, m_mapAlphaIntToCTSZJets_vs_CTSZBosons, m_nllCTSZJets_vs_CTSZBosons);

    std::cout << "m_nllCTSWJets.size() " <<  m_nllCTSWJets.size() << std::endl;
    std::cout << "m_nllCTSZJets.size() " <<  m_nllCTSZJets.size() << std::endl;
    std::cout << "m_nllCTSWJets_vs_CTSWBosons.size() " <<  m_nllCTSWJets_vs_CTSWBosons.size() << std::endl;
    std::cout << "m_nllCTSZJets_vs_CTSZBosons.size() " <<  m_nllCTSZJets_vs_CTSZBosons.size() << std::endl;
}

//=====================================================================

void Fit::AnalyseCTSJets(std::shared_ptr<TH1F> pTH1FRef, IntIntHistMap &mapAlphaIntToHist, FloatFloatFloatMap &mapAlphaToNLL)
{
    for (auto it: mapAlphaIntToHist)
    {
        const int alpha4Int(it.first);
        for (auto iter: it.second)
        {
            const int alpha5Int(iter.first);
            std::shared_ptr<TH1F> pTH1F_CTSJets = iter.second;

            TCanvas *pTCanvas = new TCanvas();
            pTCanvas->Draw();
            pTH1FRef->Draw();

            pTH1FRef->SetLineColor(kRed);
            pTH1FRef->SetFillColor(kRed);
            pTH1FRef->SetFillStyle(3004);

            pTH1F_CTSJets->SetLineColor(kGreen-2);
            pTH1F_CTSJets->SetFillColor(kGreen-2);
            pTH1F_CTSJets->SetFillStyle(3005);

            int binMaxRef = pTH1FRef->GetBinContent(pTH1FRef->GetMaximumBin());
            int binMax = pTH1F_CTSJets->GetBinContent(pTH1F_CTSJets->GetMaximumBin());

            if (binMaxRef > binMax)
            {
                pTH1FRef->GetYaxis()->SetRangeUser(0,binMaxRef*1.05);
                pTH1F_CTSJets->GetYaxis()->SetRangeUser(0,binMaxRef*1.05);
                pTH1FRef->Draw();
                pTH1F_CTSJets->Draw("same");
            }
            else 
            {
                pTH1FRef->GetYaxis()->SetRangeUser(0,binMax*1.05);
                pTH1F_CTSJets->GetYaxis()->SetRangeUser(0,binMax*1.05);
                pTH1F_CTSJets->Draw();
                pTH1FRef->Draw("same");
            }

            TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);
            std::string legendDescriptionRef = "#alpha_{4} = 0, #alpha_{5} = 0";
            std::string legendDescription = "#alpha_{4} = " + this->NumberToString(alpha4Int*m_alpha4Step) + ", #alpha_{5} = " + this->NumberToString(alpha5Int*m_alpha5Step);
            pTLegend->AddEntry(pTH1F_CTSJets.get(),legendDescription.c_str(),"f");
            pTLegend->AddEntry(pTH1FRef.get(),legendDescriptionRef.c_str(),"f");
            pTLegend->Draw("same");

//            m_pTFile->cd();
//            pTH1F_CTSJets->Write();
//            pTCanvas->Write();

            double nLL(this->CalculateLogLikelihood1D(pTH1F_CTSJets, pTH1FRef));
            mapAlphaToNLL[alpha4Int*m_alpha4Step][alpha5Int*m_alpha5Step] = nLL;
            delete pTLegend, pTCanvas;
        }
    }
}

//=====================================================================

void Fit::MakeStackCTSWJets()
{
    std::string nameCTSWJetsStack =  "StackCTSWJets";
    std::string titleCTSWJetsStack = "Cos#theta_{WJets}^{*}";
    TLegend *pTLegend = new TLegend(0.7,0.7,1.0,1.0);
    THStack *pTHStack = new THStack(nameCTSWJetsStack.c_str(), titleCTSWJetsStack.c_str());
    int counter(0);

    for (const auto &pProcess: m_processVector)
    {
        Color_t color = TColor::GetColor(m_red.at(counter), m_green.at(counter), m_blue.at(counter));
        m_eventTypeToCTSJets[pProcess->GetEventType()]->SetLineColor(color);
        m_eventTypeToCTSJets[pProcess->GetEventType()]->SetFillColor(color);
        m_eventTypeToCTSJets[pProcess->GetEventType()]->SetFillStyle(m_fillStyle.at(counter));
        counter++;
        pTHStack->Add(m_eventTypeToCTSJets[pProcess->GetEventType()].get());
        pTLegend->AddEntry(m_eventTypeToCTSJets[pProcess->GetEventType()].get(), pProcess->GetEventType().c_str(), "f");
    }

//    pTHStack->Write();
    TCanvas *pTCanvas = new TCanvas();
    pTCanvas->Draw();
    pTHStack->Draw();
    pTLegend->Draw("same");
//    pTCanvas->Write();

    std::string plotTitlePng("StackCTSWJets_" + m_descriptor + ".png");
    std::string plotTitleDotC("StackCTSWJets_" + m_descriptor + ".C");
    pTCanvas->SaveAs(plotTitlePng.c_str());
    pTCanvas->SaveAs(plotTitleDotC.c_str());
    delete pTHStack, pTLegend, pTCanvas;
}

//=====================================================================

void Fit::AnalyseCTSWBosons()
{
}

//=====================================================================

void Fit::AnalyseCTSJets_vs_CTSBosons(std::shared_ptr<TH2F> pTH2FRef, IntInt2DHistMap &mapAlphaIntToHist, FloatFloatFloatMap &mapAlphaToNLL)
{
    for (auto element: mapAlphaIntToHist)
    {
        const int alpha4Int(element.first);
        for (auto subElement: element.second)
        {
            const int alpha5Int(subElement.first);
            std::shared_ptr<TH2F> pTH2F_CTSJets_vs_CTSBosons = subElement.second;

            TString nameStack = "Stack_";
            nameStack += pTH2F_CTSJets_vs_CTSBosons->GetName();
            TString titleStack = "Stack ";
            titleStack += pTH2F_CTSJets_vs_CTSBosons->GetTitle();
//            THStack *pTHStack_CTSJets_vs_CTSBosons = new THStack(nameStack, titleStack);
            std::shared_ptr<THStack> pTHStack_CTSJets_vs_CTSBosons(new THStack(nameStack, titleStack)); 

//            TCanvas *pTCanvas = new TCanvas();
            std::shared_ptr<TCanvas> pTCanvas(new TCanvas());
            pTCanvas->Draw();
            pTH2FRef->Draw();

            pTH2FRef->SetLineColor(kRed);
            pTH2FRef->SetFillColor(kRed);
            pTH2FRef->SetFillStyle(3004);

            pTH2F_CTSJets_vs_CTSBosons->SetLineColor(kGreen-2);
            pTH2F_CTSJets_vs_CTSBosons->SetFillColor(kGreen-2);
            pTH2F_CTSJets_vs_CTSBosons->SetFillStyle(3005);

            pTHStack_CTSJets_vs_CTSBosons->Add(pTH2FRef.get());
            pTHStack_CTSJets_vs_CTSBosons->Add(pTH2F_CTSJets_vs_CTSBosons.get());
            pTHStack_CTSJets_vs_CTSBosons->Draw();

//            TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);
            std::shared_ptr<TLegend> pTLegend(new TLegend(0.5,0.7,0.9,0.9));
            std::string legendDescriptionRef = "#alpha_{4} = 0, #alpha_{5} = 0";
            std::string legendDescription = "#alpha_{4} = " + this->NumberToString(alpha4Int*m_alpha4Step) + ", #alpha_{5} = " + this->NumberToString(alpha5Int*m_alpha5Step);
            pTLegend->AddEntry(pTH2F_CTSJets_vs_CTSBosons.get(), legendDescription.c_str(),"f");
            pTLegend->AddEntry(pTH2FRef.get(), legendDescriptionRef.c_str(),"f");
            pTLegend->Draw("same");

//            m_pTFile->cd();
//            pTCanvas->Write();
//            pTH2F_CTSJets_vs_CTSBosons->Write();
//            pTHStack_CTSJets_vs_CTSBosons->Write();

            double nLL(this->CalculateLogLikelihood2D(pTH2F_CTSJets_vs_CTSBosons, pTH2FRef));
            mapAlphaToNLL[alpha4Int*m_alpha4Step][alpha5Int*m_alpha5Step] = nLL;
//            delete pTHStack_CTSJets_vs_CTSBosons, pTLegend, pTCanvas;
        }
    }
}

//=====================================================================

double Fit::CalculateLogLikelihood1D(std::shared_ptr<TH1F> pTH1F, std::shared_ptr<TH1F> pTH1FRef)
{
    if (!gApplication) new TApplication("Application", ((int *)0), ((char **)0));

    double nLL(0.0);
    const int nBinsX = pTH1F->GetXaxis()->GetNbins();
    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        const double binContent = pTH1F->GetBinContent(xBin);
        const double binContentRef = pTH1FRef->GetBinContent(xBin);
        nLL += (-1.0 * binContentRef * log(binContent)) + binContent;
    }
    return nLL;
}

//=====================================================================

double Fit::CalculateLogLikelihood2D(std::shared_ptr<TH2F> pTH2F, std::shared_ptr<TH2F> pTH2FRef)
{
    if (!gApplication) new TApplication("Application", ((int *)0), ((char **)0));

    double nLL(0.0);

    const int nBinsX = pTH2F->GetXaxis()->GetNbins();
    const int nBinsY = pTH2F->GetYaxis()->GetNbins();
    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        for (unsigned int yBin = 1; yBin < nBinsY; yBin++)
        {
            const double binContent = pTH2F->GetBinContent(xBin, yBin);
            const double binContentRef = pTH2FRef->GetBinContent(xBin, yBin);
            nLL += (-1.0 * binContentRef * log(binContent)) + binContent;
        }
    }
    return nLL;
}

//=====================================================================

void Fit::SaveDistribution()
{
//    TGraph2D *pTGraph2D_NLLCTSWJets = new TGraph2D();
    std::unique_ptr<TGraph2D> pTGraph2D_NLLCTSWJets(new TGraph2D()); 
    pTGraph2D_NLLCTSWJets->SetName("TGraph2D_NLLCTSWJets");
    pTGraph2D_NLLCTSWJets->SetTitle("Negative Log Likelihood Cos#theta_{WJets}^{*}");

//    TGraph2D *pTGraph2D_NLLCTSZJets = new TGraph2D();
    std::unique_ptr<TGraph2D> pTGraph2D_NLLCTSZJets(new TGraph2D());
    pTGraph2D_NLLCTSZJets->SetName("TGraph2D_NLLCTSZJets");
    pTGraph2D_NLLCTSZJets->SetTitle("Negative Log Likelihood Cos#theta_{ZJets}^{*}");

//    TGraph2D *pTGraph2D_NLLCTSWJets_vs_CTSWBosons = new TGraph2D();
    std::unique_ptr<TGraph2D> pTGraph2D_NLLCTSWJets_vs_CTSWBosons(new TGraph2D());
    pTGraph2D_NLLCTSWJets_vs_CTSWBosons->SetName("TGraph2D_NLLCTSWJets_vs_CTSWBosons");
    pTGraph2D_NLLCTSWJets_vs_CTSWBosons->SetTitle("Negative Log Likelihood Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}");

//    TGraph2D *pTGraph2D_NLLCTSZJets_vs_CTSZBosons = new TGraph2D();
    std::unique_ptr<TGraph2D> pTGraph2D_NLLCTSZJets_vs_CTSZBosons(new TGraph2D()); 
    pTGraph2D_NLLCTSZJets_vs_CTSZBosons->SetName("TGraph2D_NLLCTSZJets_vs_CTSZBosons");
    pTGraph2D_NLLCTSZJets_vs_CTSZBosons->SetTitle("Negative Log Likelihood Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}");

    this->PopulateLogLikelihoodGraph(*pTGraph2D_NLLCTSWJets, m_nllCTSWJets);
    this->PopulateLogLikelihoodGraph(*pTGraph2D_NLLCTSZJets, m_nllCTSZJets);
    this->PopulateLogLikelihoodGraph(*pTGraph2D_NLLCTSWJets_vs_CTSWBosons, m_nllCTSWJets_vs_CTSWBosons);
    this->PopulateLogLikelihoodGraph(*pTGraph2D_NLLCTSZJets_vs_CTSZBosons, m_nllCTSZJets_vs_CTSZBosons);

//    TCanvas *pTCanvas = new TCanvas();
    std::unique_ptr<TCanvas> pTCanvas(new TCanvas());
    pTGraph2D_NLLCTSWJets->Draw("SURF3");
    std::string name("NLLCTSWJets_" + m_descriptor + ".C");
    pTCanvas->SaveAs(name.c_str());

//    TCanvas *pTCanvas2 = new TCanvas();
    std::unique_ptr<TCanvas> pTCanvas2(new TCanvas());
    pTGraph2D_NLLCTSZJets->Draw("SURF3");
    std::string name2("NLLCTSZJets_" + m_descriptor + ".C");
    pTCanvas2->SaveAs(name2.c_str());

//    TCanvas *pTCanvas3 = new TCanvas();
    std::unique_ptr<TCanvas> pTCanvas3(new TCanvas());
    pTGraph2D_NLLCTSWJets_vs_CTSWBosons->Draw("SURF3");
    std::string name3("NLLCTSWJets_vs_CTSWBosons_" + m_descriptor + ".C");
    pTCanvas3->SaveAs(name3.c_str());

//    TCanvas *pTCanvas4 = new TCanvas();
    std::unique_ptr<TCanvas> pTCanvas4(new TCanvas());
    pTGraph2D_NLLCTSZJets_vs_CTSZBosons->Draw("SURF3");
    std::string name4("NLLCTSZJets_vs_CTSZBosons_" + m_descriptor + ".C");
    pTCanvas4->SaveAs(name4.c_str());

    m_pTFile->cd();
    pTGraph2D_NLLCTSWJets->Write();
    pTGraph2D_NLLCTSZJets->Write();
    pTGraph2D_NLLCTSWJets_vs_CTSWBosons->Write();
    pTGraph2D_NLLCTSZJets_vs_CTSZBosons->Write();
//    delete pTGraph2D_NLLCTSWJets, pTGraph2D_NLLCTSZJets, pTGraph2D_NLLCTSWJets_vs_CTSWBosons, pTGraph2D_NLLCTSZJets_vs_CTSZBosons, pTCanvas;
}

//=====================================================================

void Fit::PopulateLogLikelihoodGraph(TGraph2D &tGraph2D, FloatFloatFloatMap &floatFloatFloatMap)
{
    float minNLL(std::numeric_limits<float>::max());

    for (auto element: floatFloatFloatMap)
    {
        const float alpha4(element.first);
        for (auto subElement: element.second)
        {
            const float alpha5(subElement.first);
            const float nLL(subElement.second);
            if (minNLL > nLL)
                minNLL = nLL;
        }
    }

    for (auto element: floatFloatFloatMap)
    {
        const float alpha4(element.first);
        for (auto subElement: element.second)
        {
            const float alpha5(subElement.first);
            const float nLL(subElement.second);
            tGraph2D.SetPoint(tGraph2D.GetN(), alpha4, alpha5, nLL - minNLL);
        }
    }
}

//=====================================================================

std::string Fit::RandomName()
{
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int strLen = sizeof(alphabet)-1;
    char genRandom;
    std::string str;
    for(int i=0; i < 10; i++)
    {
        genRandom = alphabet[rand()%strLen];
        str += genRandom;
    }
    return str;
}

//=====================================================================

template <class T>
std::string Fit::NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================

void Pause()
{
#ifdef __unix__
    std::cout << "Press return to continue ..." << std::endl;
    int flag = fcntl(1, F_GETFL, 0);

    int key = 0;
    while(true)
    {
        gSystem->ProcessEvents();
        fcntl(1, F_SETFL, flag | O_NONBLOCK);
        key = getchar();

        if((key == '\n') || (key == '\r'))
            break;

        usleep(1000);
    }

    fcntl(1, F_SETFL, flag);
#else
    std::cout << "Pause() is only implemented for unix operating systems." << std::endl;
#endif
}

//=====================================================================
