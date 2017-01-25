/**
 *  @file   AnalysisScripts/src/TMVAClassificationApplication3000.cxx 
 * 
 *  @brief  Implementation of the TMVA classifier class.
 * 
 *  $Log: $
 */

#include "TMVAClassificationApplication3000.h"

//=====================================================================

int main(int argc, char **argv)
{
    typedef std::vector<const Process*> ProcessVector;

/*
    // 3 TeV
    float nominalLuminosity(2000);
    float eeLuminosityRatio(1.0);
    float egammaLuminosityRatio(0.79);
    float gammaeLuminosityRatio(0.79);
    float gammagammaLuminosityRatio(0.69);

    // Signal 3 TeV
    const Process *pProcess_ee_nunuqqqq_1_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_2_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_3_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_4_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_5_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_6_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_7_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_8_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_9_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_10_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_11_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_12_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqqqq_13_3TeV = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);

    ProcessVector processes;
    processes.push_back(pProcess_ee_nunuqqqq_1_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_2_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_3_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_4_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_5_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_6_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_7_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_8_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_9_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_10_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_11_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_12_3TeV);
    processes.push_back(pProcess_ee_nunuqqqq_13_3TeV);
*/

    // 3 TeV
    float nominalLuminosity(2000);
    float eeLuminosityRatio(1.0);
    float egammaLuminosityRatio(0.79);
    float gammaeLuminosityRatio(0.79);
    float gammagammaLuminosityRatio(0.69);

    // Signal 3 TeV and background
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",71.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_lnuqqqq",106.6,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_llqqqq",169.3,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qqqq",546.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqq",1317.5,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_lnuqq",5560.9,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qqll",3319.6,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_qq",2948.9,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqe_EPA",287.8,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqe_BS",1268.6,nominalLuminosity*egammaLuminosityRatio,3000,18,false);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqe_EPA",287.8,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqe_BS",1267.3,nominalLuminosity*gammaeLuminosityRatio,3000,18,false);
    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqnu_EPA",54.2,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","egamma_qqqqnu_BS",262.5,nominalLuminosity*egammaLuminosityRatio,3000,18,false);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqnu_EPA",54.2,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammae_qqqqnu_BS",262.3,nominalLuminosity*gammaeLuminosityRatio,3000,18,false);
    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_EPA_EPA",402.7,nominalLuminosity*eeLuminosityRatio,3000,18,false);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_EPA_BS",2423.1,nominalLuminosity*egammaLuminosityRatio,3000,18,false);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_BS_EPA",2420.6,nominalLuminosity*gammaeLuminosityRatio,3000,18,false);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","gammagamma_qqqq_BS_BS",13050.3,nominalLuminosity*gammagammaLuminosityRatio,3000,18,false);

    ProcessVector processes;

    processes.push_back(pProcess_ee_nunuqqqq);
    processes.push_back(pProcess_ee_lnuqqqq);
    processes.push_back(pProcess_ee_llqqqq);
    processes.push_back(pProcess_ee_qqqq);
    processes.push_back(pProcess_ee_nunuqq);
    processes.push_back(pProcess_ee_lnuqq);
    processes.push_back(pProcess_ee_qqll);
    processes.push_back(pProcess_ee_qq);
    processes.push_back(pProcess_egamma_qqqqe_EPA);
    processes.push_back(pProcess_egamma_qqqqe_BS);
    processes.push_back(pProcess_gammae_qqqqe_EPA);
    processes.push_back(pProcess_gammae_qqqqe_BS);
    processes.push_back(pProcess_egamma_qqqqnu_EPA);
    processes.push_back(pProcess_egamma_qqqqnu_BS);
    processes.push_back(pProcess_gammae_qqqqnu_EPA);
    processes.push_back(pProcess_gammae_qqqqnu_BS);
    processes.push_back(pProcess_gammagamma_qqqq_EPA_EPA);
    processes.push_back(pProcess_gammagamma_qqqq_EPA_BS);
    processes.push_back(pProcess_gammagamma_qqqq_BS_EPA);
    processes.push_back(pProcess_gammagamma_qqqq_BS_BS);

    TMVAClassificationApplication3000 *pTMVAClassificationApplication3000 = new TMVAClassificationApplication3000(processes, false);
}

//=====================================================================

TMVAClassificationApplication3000::TMVAClassificationApplication3000(ProcessVector processes, bool perfect)
{
    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    EventNumbers *pEventNumbers = new EventNumbers();

    // Event
    Float_t nPFOs(std::numeric_limits<float>::max());
    Float_t highestEnergyPfoPDG(std::numeric_limits<float>::max());
    Float_t transverseMomentum(std::numeric_limits<float>::max());
    Float_t cosThetaMissing(std::numeric_limits<float>::max());
    Float_t cosThetaMostEnergeticTrack(std::numeric_limits<float>::max());
    Float_t y12(std::numeric_limits<float>::max());
    Float_t y23(std::numeric_limits<float>::max());
    Float_t y34(std::numeric_limits<float>::max());
    Float_t y45(std::numeric_limits<float>::max());
    Float_t y56(std::numeric_limits<float>::max());
    Float_t y67(std::numeric_limits<float>::max());
    Float_t principleThrustValue(std::numeric_limits<float>::max());
    Float_t sphericity(std::numeric_limits<float>::max());
    Float_t aplanarity(std::numeric_limits<float>::max());
    Float_t highestEnergyElectronEnergy(std::numeric_limits<float>::max());
    Float_t highestEnergyPfoEnergy(std::numeric_limits<float>::max());

    // Bosons
    Float_t energyBosonSyn1(std::numeric_limits<float>::max());
    Float_t energyBosonSyn2(std::numeric_limits<float>::max());
    Float_t acolinearityBosonsSyn(std::numeric_limits<float>::max());
    Float_t invariantMassSynBoson1(std::numeric_limits<float>::max());
    Float_t invariantMassSynBoson2(std::numeric_limits<float>::max());

    // Jets
    Float_t acolinearityJetsSyn1(std::numeric_limits<float>::max());
    Float_t acolinearityJetsSyn2(std::numeric_limits<float>::max());

    if (!perfect)
    {
        // Event
        reader->AddVariable("NPfos := NParticlesJet1+NParticlesJet2+NParticlesJet3+NParticlesJet4", &nPFOs);
        reader->AddVariable("HighestEnergyPfoPDG", &highestEnergyPfoPDG);
        reader->AddVariable("TransverseMomentum", &transverseMomentum);
        reader->AddVariable("CosThetaMissing", &cosThetaMissing);
        reader->AddVariable("CosThetaMostEnergeticTrack", &cosThetaMostEnergeticTrack);
        reader->AddVariable("y12", &y12);
        reader->AddVariable("y23", &y23);
        reader->AddVariable("y34", &y34);
        reader->AddVariable("y45", &y45);
        reader->AddVariable("y56", &y56);
        reader->AddVariable("y67", &y67);
        reader->AddVariable("PrincipleThrustValue", &principleThrustValue);
        reader->AddVariable("Sphericity", &sphericity);
        reader->AddVariable("Aplanarity", &aplanarity);
        reader->AddVariable("(HighestEnergyElectronEnergy<10000)*HighestEnergyElectronEnergy", &highestEnergyElectronEnergy);
        reader->AddVariable("(HighestEnergyPfoEnergy<10000)*HighestEnergyPfoEnergy", &highestEnergyPfoEnergy);
        // Bosons
        reader->AddVariable("EnergyBosonSyn1", &energyBosonSyn1);
        reader->AddVariable("EnergyBosonSyn2", &energyBosonSyn2);
        reader->AddVariable("AcolinearityBosonsSyn", &acolinearityBosonsSyn);
        reader->AddVariable("InvariantMassSynBoson1", &invariantMassSynBoson1);
        reader->AddVariable("InvariantMassSynBoson2", &invariantMassSynBoson2);
        // Jets
        reader->AddVariable("AcolinearityJetsSyn1", &acolinearityJetsSyn1);
        reader->AddVariable("AcolinearityJetsSyn2", &acolinearityJetsSyn2);

        reader->BookMVA("BDT method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/IdealConfiguration3000GeV/TMVAClassification_BDT_NTrees3000_MaxDepth3_NCuts25_3000GeV.weights.xml");
    }

    for (ProcessVector::iterator itPro = processes.begin(); itPro != processes.end(); itPro++)
    {
        // Branches straight from root tree
        Bool_t appropriateEvent_ToSaveAndRead(false);
        Bool_t isEventWW_ToSaveAndRead(false);
        Bool_t isEventWWMC_ToSaveAndRead(false);
        Bool_t isEventZZ_ToSaveAndRead(false);
        Bool_t isEventZZMC_ToSaveAndRead(false);

        Int_t nPfosBosonW1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nPfosBosonW2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nPfosBosonZ1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nPfosBosonZ2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nPfosBosonSyn1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nPfosBosonSyn2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWJet1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWJet2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWJet3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWJet4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJet1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJet2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJet3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJet4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynJets1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynJets2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynJets3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynJets4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWQuark1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWQuark2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWQuark3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWQuark4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZQuark1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZQuark2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZQuark3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZQuark4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynQuarks1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynQuarks2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynQuarks3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationSynQuarks4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJet1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJet2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJet3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJet4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJet1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJet2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJet3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJet4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t highestEnergyPfoPDG_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t highestEnergyIsolatedLeptonPDG_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t secondHighestEnergyIsolatedLeptonPDG_ToSaveAndRead(std::numeric_limits<int>::max());
        Double_t transverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaMissing_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaMissingMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaMostEnergeticTrack_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t recoilMass_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t recoilMassMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyAroundMostEnergeticPfo_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t y12_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t y23_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t y34_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t y45_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t y56_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t y67_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassSystem_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassSystemMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWBosons_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWBosonsMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZBosons_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZBosonsMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynBosons_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynBosonsMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityBosonsW_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityBosonsZ_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityBosonsSyn_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t principleThrustValue_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t majorThrustValue_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minorThrustValue_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t xThrustAxis_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t yThrustAxis_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t zThrustAxis_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t sphericity_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t aplanarity_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronTransverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonTransverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonTransverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoTransverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonTransverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonTransverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosons1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosons2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosons1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosons2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassSynBoson1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassSynBoson2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosonsMC1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosonsMC2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosonsMC1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosonsMC2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassSynBosonsMC1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassSynBosonsMC2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBoson1Pairing0123_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBoson2Pairing0123_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBoson1Pairing0213_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBoson2Pairing0213_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBoson1Pairing0312_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBoson2Pairing0312_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBosonMC1Pairing0123_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBosonMC2Pairing0123_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBosonMC1Pairing0213_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBosonMC2Pairing0213_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBosonMC1Pairing0312_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassBosonMC2Pairing0312_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJet3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJet4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumJet3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t momentumJet4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumJet3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumJet4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaJet3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaJet4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJet3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJet4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJet1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJet2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJet3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJet4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxBTagForBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minBTagForBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxBTagForBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minBTagForBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxCTagForBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minCTagForBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxCTagForBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minCTagForBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxBTagForBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minBTagForBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxBTagForBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minBTagForBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxCTagForBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minCTagForBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxCTagForBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minCTagForBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxBTagForBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minBTagForBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxBTagForBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minBTagForBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxCTagForBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minCTagForBosonSyn1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t maxCTagForBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minCTagForBosonSyn2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoEnergy1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoPx1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoPy1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoPz1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoEnergy2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoPx2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoPy2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t neutrinoPz2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkEnergy1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPx1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPy1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPz1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkEnergy2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPx2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPy2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPz2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkEnergy3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPx3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPy3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPz3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkEnergy4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPx4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPy4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t quarkPz4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cheatedInvariantMass1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cheatedInvariantMass2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cheatedMCInvariantMass1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cheatedMCInvariantMass2_ToSaveAndRead(std::numeric_limits<double>::max());

        // Have to define these variables from root branches or MVA reader
        Int_t nPFOs_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t globalEventNumber_ToSave(std::numeric_limits<int>::max());
        Double_t bdt(std::numeric_limits<double>::max());
        Double_t cuts(std::numeric_limits<double>::max());
        Double_t likelihood(std::numeric_limits<double>::max());
        Double_t pders(std::numeric_limits<double>::max());
        Double_t knn(std::numeric_limits<double>::max());
        Double_t cfmlpann(std::numeric_limits<double>::max());

        // To Save
        TTree *pTTree = new TTree("MVATree", "MVATree");
        pTTree->Branch("GlobalEventNumber", &globalEventNumber_ToSave);

        pTTree->Branch("BDT", &bdt);
//        pTTree->Branch("Cuts", &cuts);
//        pTTree->Branch("Likelihood", &likelihood);
//        pTTree->Branch("PDERS", &pders);
//        pTTree->Branch("KNN", &knn);
//        pTTree->Branch("CFMlpANN", &cfmlpann);
        pTTree->Branch("IsAppropriateEvent", &appropriateEvent_ToSaveAndRead);
        pTTree->Branch("IsEventWW", &isEventWW_ToSaveAndRead);
        pTTree->Branch("IsMCEventWW", &isEventWWMC_ToSaveAndRead);
        pTTree->Branch("IsEventZZ", &isEventZZ_ToSaveAndRead);
        pTTree->Branch("IsMCEventZZ", &isEventZZMC_ToSaveAndRead);
        pTTree->Branch("NPfosBosonW1", &nPfosBosonW1_ToSaveAndRead);
        pTTree->Branch("NPfosBosonW2", &nPfosBosonW2_ToSaveAndRead);
        pTTree->Branch("NPfosBosonZ1", &nPfosBosonZ1_ToSaveAndRead);
        pTTree->Branch("NPfosBosonZ2", &nPfosBosonZ2_ToSaveAndRead);
        pTTree->Branch("NPfosBosonSyn1", &nPfosBosonSyn1_ToSaveAndRead);
        pTTree->Branch("NPfosBosonSyn2", &nPfosBosonSyn2_ToSaveAndRead);
        pTTree->Branch("WBosonJet1Is", &combinationWJet1_ToSaveAndRead);
        pTTree->Branch("WBosonJet2Is", &combinationWJet2_ToSaveAndRead);
        pTTree->Branch("WBosonJet3Is", &combinationWJet3_ToSaveAndRead);
        pTTree->Branch("WBosonJet4Is", &combinationWJet4_ToSaveAndRead);
        pTTree->Branch("ZBosonJet1Is", &combinationZJet1_ToSaveAndRead);
        pTTree->Branch("ZBosonJet2Is", &combinationZJet2_ToSaveAndRead);
        pTTree->Branch("ZBosonJet3Is", &combinationZJet3_ToSaveAndRead);
        pTTree->Branch("ZBosonJet4Is", &combinationZJet4_ToSaveAndRead);
        pTTree->Branch("SynBosonJet1Is", &combinationSynJets1_ToSaveAndRead);
        pTTree->Branch("SynBosonJet2Is", &combinationSynJets2_ToSaveAndRead);
        pTTree->Branch("SynBosonJet3Is", &combinationSynJets3_ToSaveAndRead);
        pTTree->Branch("SynBosonJet4Is", &combinationSynJets4_ToSaveAndRead);
        pTTree->Branch("WBosonQuark1Is", &combinationWQuark1_ToSaveAndRead);
        pTTree->Branch("WBosonQuark2Is", &combinationWQuark2_ToSaveAndRead);
        pTTree->Branch("WBosonQuark3Is", &combinationWQuark3_ToSaveAndRead);
        pTTree->Branch("WBosonQuark4Is", &combinationWQuark4_ToSaveAndRead);
        pTTree->Branch("ZBosonQuark1Is", &combinationZQuark1_ToSaveAndRead);
        pTTree->Branch("ZBosonQuark2Is", &combinationZQuark2_ToSaveAndRead);
        pTTree->Branch("ZBosonQuark3Is", &combinationZQuark3_ToSaveAndRead);
        pTTree->Branch("ZBosonQuark4Is", &combinationZQuark4_ToSaveAndRead);
        pTTree->Branch("SynBosonQuark1Is", &combinationSynQuarks1_ToSaveAndRead);
        pTTree->Branch("SynBosonQuark2Is", &combinationSynQuarks2_ToSaveAndRead);
        pTTree->Branch("SynBosonQuark3Is", &combinationSynQuarks3_ToSaveAndRead);
        pTTree->Branch("SynBosonQuark4Is", &combinationSynQuarks4_ToSaveAndRead);
        pTTree->Branch("NParticlesJet1", &nParticlesJet1_ToSaveAndRead);
        pTTree->Branch("NParticlesJet2", &nParticlesJet2_ToSaveAndRead);
        pTTree->Branch("NParticlesJet3", &nParticlesJet3_ToSaveAndRead);
        pTTree->Branch("NParticlesJet4", &nParticlesJet4_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet1", &nChargedParticlesJet1_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet2", &nChargedParticlesJet2_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet3", &nChargedParticlesJet3_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet4", &nChargedParticlesJet4_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoPDG", &highestEnergyPfoPDG_ToSaveAndRead);
        pTTree->Branch("NumberOfIsolatedLeptons", &nIsolatedLeptons_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonPDG", &highestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonPDG", &secondHighestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTTree->Branch("TransverseMomentum", &transverseMomentum_ToSaveAndRead);
        pTTree->Branch("MCTransverseMomentum", &transverseMomentumMC_ToSaveAndRead);
        pTTree->Branch("TransverseEnergy", &transverseEnergy_ToSaveAndRead);
        pTTree->Branch("MCTransverseEnergy", &transverseEnergyMC_ToSaveAndRead);
        pTTree->Branch("EnergyBosonW1", &energyBosonW1_ToSaveAndRead);
        pTTree->Branch("EnergyBosonW2", &energyBosonW2_ToSaveAndRead);
        pTTree->Branch("EnergyBosonZ1", &energyBosonZ1_ToSaveAndRead);
        pTTree->Branch("EnergyBosonZ2", &energyBosonZ2_ToSaveAndRead);
        pTTree->Branch("EnergyBosonSyn1", &energyBosonSyn1_ToSaveAndRead);
        pTTree->Branch("EnergyBosonSyn2", &energyBosonSyn2_ToSaveAndRead);
        pTTree->Branch("MomentumBosonW1", &momentumBosonW1_ToSaveAndRead);
        pTTree->Branch("MomentumBosonW2", &momentumBosonW2_ToSaveAndRead);
        pTTree->Branch("MomentumBosonZ1", &momentumBosonZ1_ToSaveAndRead);
        pTTree->Branch("MomentumBosonZ2", &momentumBosonZ2_ToSaveAndRead);
        pTTree->Branch("MomentumBosonSyn1", &momentumBosonSyn1_ToSaveAndRead);
        pTTree->Branch("MomentumBosonSyn2", &momentumBosonSyn2_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonW1", &transverseMomentumBosonW1_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonW2", &transverseMomentumBosonW2_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonZ1", &transverseMomentumBosonZ1_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonZ2", &transverseMomentumBosonZ2_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonSyn1", &transverseMomentumBosonSyn1_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonSyn2", &transverseMomentumBosonSyn2_ToSaveAndRead);
        pTTree->Branch("CosThetaBosonW1", &cosThetaBosonW1_ToSaveAndRead);
        pTTree->Branch("CosThetaBosonW2", &cosThetaBosonW2_ToSaveAndRead);
        pTTree->Branch("CosThetaBosonZ1", &cosThetaBosonZ1_ToSaveAndRead);
        pTTree->Branch("CosThetaBosonZ2", &cosThetaBosonZ2_ToSaveAndRead);
        pTTree->Branch("CosThetaBosonSyn1", &cosThetaBosonSyn1_ToSaveAndRead);
        pTTree->Branch("CosThetaBosonSyn2", &cosThetaBosonSyn2_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonW1", &transverseEnergyBosonW1_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonW2", &transverseEnergyBosonW2_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonZ1", &transverseEnergyBosonZ1_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonZ2", &transverseEnergyBosonZ2_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonSyn1", &transverseEnergyBosonSyn1_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonSyn2", &transverseEnergyBosonSyn2_ToSaveAndRead);
        pTTree->Branch("CosThetaMissing", &cosThetaMissing_ToSaveAndRead);
        pTTree->Branch("MCCosThetaMissing", &cosThetaMissingMC_ToSaveAndRead);
        pTTree->Branch("CosThetaMostEnergeticTrack", &cosThetaMostEnergeticTrack_ToSaveAndRead);
        pTTree->Branch("RecoilMass", &recoilMass_ToSaveAndRead);
        pTTree->Branch("MCRecoilMass", &recoilMassMC_ToSaveAndRead);
        pTTree->Branch("EnergyAroundMostEnergeticTrack", &energyAroundMostEnergeticPfo_ToSaveAndRead);
        pTTree->Branch("y12", &y12_ToSaveAndRead);
        pTTree->Branch("y23", &y23_ToSaveAndRead);
        pTTree->Branch("y34", &y34_ToSaveAndRead);
        pTTree->Branch("y45", &y45_ToSaveAndRead);
        pTTree->Branch("y56", &y56_ToSaveAndRead);
        pTTree->Branch("y67", &y67_ToSaveAndRead);
        pTTree->Branch("InvariantMassSystem", &invariantMassSystem_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassSystem", &invariantMassSystemMC_ToSaveAndRead);
        pTTree->Branch("CosThetaStarWBosons", &cosThetaStarWBosons_ToSaveAndRead);
        pTTree->Branch("MCCosThetaStarWBosons", &cosThetaStarWBosonsMC_ToSaveAndRead);
        pTTree->Branch("CosThetaStarZBosons", &cosThetaStarZBosons_ToSaveAndRead);
        pTTree->Branch("MCCosThetaStarZBosons", &cosThetaStarZBosonsMC_ToSaveAndRead);
        pTTree->Branch("CosThetaStarSynBosons", &cosThetaStarSynBosons_ToSaveAndRead);
        pTTree->Branch("MCCosThetaStarSynBosons", &cosThetaStarSynBosonsMC_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsW1", &acolinearityJetsW1_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsW2", &acolinearityJetsW2_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsZ1", &acolinearityJetsZ1_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsZ2", &acolinearityJetsZ2_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsSyn1", &acolinearityJetsSyn1_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsSyn2", &acolinearityJetsSyn2_ToSaveAndRead);
        pTTree->Branch("AcolinearityBosonsW", &acolinearityBosonsW_ToSaveAndRead);
        pTTree->Branch("AcolinearityBosonsZ", &acolinearityBosonsZ_ToSaveAndRead);
        pTTree->Branch("AcolinearityBosonsSyn", &acolinearityBosonsSyn_ToSaveAndRead);
        pTTree->Branch("PrincipleThrustValue", &principleThrustValue_ToSaveAndRead);
        pTTree->Branch("MajorThrustValue", &majorThrustValue_ToSaveAndRead);
        pTTree->Branch("MinorThrustValue", &minorThrustValue_ToSaveAndRead);
        pTTree->Branch("XThrustAxis", &xThrustAxis_ToSaveAndRead);
        pTTree->Branch("YThrustAxis", &yThrustAxis_ToSaveAndRead);
        pTTree->Branch("ZThrustAxis", &zThrustAxis_ToSaveAndRead);
        pTTree->Branch("Sphericity", &sphericity_ToSaveAndRead);
        pTTree->Branch("Aplanarity", &aplanarity_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronEnergy", &highestEnergyElectronEnergy_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronMomentum", &highestEnergyElectronMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronTransverseMomentum", &highestEnergyElectronTransverseMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronCosTheta", &highestEnergyElectronCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonEnergy", &highestEnergyMuonEnergy_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonMomentum", &highestEnergyMuonMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonTransverseMomentum", &highestEnergyMuonTransverseMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonCosTheta", &highestEnergyMuonCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonEnergy", &highestEnergyPhotonEnergy_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonMomentum", &highestEnergyPhotonMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonTransverseMomentum", &highestEnergyPhotonTransverseMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonCosTheta", &highestEnergyPhotonCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoEnergy", &highestEnergyPfoEnergy_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoMomentum", &highestEnergyPfoMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoTransverseMomentum", &highestEnergyPfoTransverseMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoCosTheta", &highestEnergyPfoCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonEnergy", &highestEnergyIsolatedLeptonEnergy_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonMomentum", &highestEnergyIsolatedLeptonMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonTransverseMomentum", &highestEnergyIsolatedLeptonTransverseMomentum_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonCosTheta", &highestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonEnergy", &secondHighestEnergyIsolatedLeptonEnergy_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonMomentum", &secondHighestEnergyIsolatedLeptonMomentum_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonTransverseMomentum", &secondHighestEnergyIsolatedLeptonTransverseMomentum_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonCosTheta", &secondHighestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTTree->Branch("InvariantMassWBoson1", &invariantMassWBosons1_ToSaveAndRead);
        pTTree->Branch("InvariantMassWBoson2", &invariantMassWBosons2_ToSaveAndRead);
        pTTree->Branch("InvariantMassZBoson1", &invariantMassZBosons1_ToSaveAndRead);
        pTTree->Branch("InvariantMassZBoson2", &invariantMassZBosons2_ToSaveAndRead);
        pTTree->Branch("InvariantMassSynBoson1", &invariantMassSynBoson1_ToSaveAndRead);
        pTTree->Branch("InvariantMassSynBoson2", &invariantMassSynBoson2_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassWBoson1", &invariantMassWBosonsMC1_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassWBoson2", &invariantMassWBosonsMC2_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassZBoson1", &invariantMassZBosonsMC1_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassZBoson2", &invariantMassZBosonsMC2_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassSynBoson1", &invariantMassSynBosonsMC1_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassSynBoson2", &invariantMassSynBosonsMC2_ToSaveAndRead);
        pTTree->Branch("InvariantMassBoson1Pairing0123", &invariantMassBoson1Pairing0123_ToSaveAndRead);
        pTTree->Branch("InvariantMassBoson2Pairing0123", &invariantMassBoson2Pairing0123_ToSaveAndRead);
        pTTree->Branch("InvariantMassBoson1Pairing0213", &invariantMassBoson1Pairing0213_ToSaveAndRead);
        pTTree->Branch("InvariantMassBoson2Pairing0213", &invariantMassBoson2Pairing0213_ToSaveAndRead);
        pTTree->Branch("InvariantMassBoson1Pairing0312", &invariantMassBoson1Pairing0312_ToSaveAndRead);
        pTTree->Branch("InvariantMassBoson2Pairing0312", &invariantMassBoson2Pairing0312_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassBoson1Pairing0123", &invariantMassBosonMC1Pairing0123_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassBoson2Pairing0123", &invariantMassBosonMC2Pairing0123_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassBoson1Pairing0213", &invariantMassBosonMC1Pairing0213_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassBoson2Pairing0213", &invariantMassBosonMC2Pairing0213_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassBoson1Pairing0312", &invariantMassBosonMC1Pairing0312_ToSaveAndRead);
        pTTree->Branch("MCInvariantMassBoson2Pairing0312", &invariantMassBosonMC2Pairing0312_ToSaveAndRead);
        pTTree->Branch("EnergyJet1", &energyJet1_ToSaveAndRead);
        pTTree->Branch("EnergyJet2", &energyJet2_ToSaveAndRead);
        pTTree->Branch("EnergyJet3", &energyJet3_ToSaveAndRead);
        pTTree->Branch("EnergyJet4", &energyJet4_ToSaveAndRead);
        pTTree->Branch("MomentumJet1", &momentumJet1_ToSaveAndRead);
        pTTree->Branch("MomentumJet2", &momentumJet2_ToSaveAndRead);
        pTTree->Branch("MomentumJet3", &momentumJet3_ToSaveAndRead);
        pTTree->Branch("MomentumJet4", &momentumJet4_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumJet1", &transverseMomentumJet1_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumJet2", &transverseMomentumJet2_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumJet3", &transverseMomentumJet3_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumJet4", &transverseMomentumJet4_ToSaveAndRead);
        pTTree->Branch("CosThetaJet1", &cosThetaJet1_ToSaveAndRead);
        pTTree->Branch("CosThetaJet2", &cosThetaJet2_ToSaveAndRead);
        pTTree->Branch("CosThetaJet3", &cosThetaJet3_ToSaveAndRead);
        pTTree->Branch("CosThetaJet4", &cosThetaJet4_ToSaveAndRead);
        pTTree->Branch("CosThetaStarWJet1", &cosThetaStarWJet1_ToSaveAndRead);
        pTTree->Branch("CosThetaStarWJet2", &cosThetaStarWJet2_ToSaveAndRead);
        pTTree->Branch("CosThetaStarZJet1", &cosThetaStarZJet1_ToSaveAndRead);
        pTTree->Branch("CosThetaStarZJet2", &cosThetaStarZJet2_ToSaveAndRead);
        pTTree->Branch("CosThetaStarSynJet1", &cosThetaStarSynJet1_ToSaveAndRead);
        pTTree->Branch("CosThetaStarSynJet2", &cosThetaStarSynJet2_ToSaveAndRead);
        pTTree->Branch("BTagForJet1", &bTagForJet1_ToSaveAndRead);
        pTTree->Branch("BTagForJet2", &bTagForJet2_ToSaveAndRead);
        pTTree->Branch("BTagForJet3", &bTagForJet3_ToSaveAndRead);
        pTTree->Branch("BTagForJet4", &bTagForJet4_ToSaveAndRead);
        pTTree->Branch("CTagForJet1", &cTagForJet1_ToSaveAndRead);
        pTTree->Branch("CTagForJet2", &cTagForJet2_ToSaveAndRead);
        pTTree->Branch("CTagForJet3", &cTagForJet3_ToSaveAndRead);
        pTTree->Branch("CTagForJet4", &cTagForJet4_ToSaveAndRead);
        pTTree->Branch("MaxBTagForBosonW1", &maxBTagForBosonW1_ToSaveAndRead);
        pTTree->Branch("MinBTagForBosonW1", &minBTagForBosonW1_ToSaveAndRead);
        pTTree->Branch("MaxBTagForBosonW2", &maxBTagForBosonW2_ToSaveAndRead);
        pTTree->Branch("MinBTagForBosonW2", &minBTagForBosonW2_ToSaveAndRead);
        pTTree->Branch("MaxCTagForBosonW1", &maxCTagForBosonW1_ToSaveAndRead);
        pTTree->Branch("MinCTagForBosonW1", &minCTagForBosonW1_ToSaveAndRead);
        pTTree->Branch("MaxCTagForBosonW2", &maxCTagForBosonW2_ToSaveAndRead);
        pTTree->Branch("MinCTagForBosonW2", &minCTagForBosonW2_ToSaveAndRead);
        pTTree->Branch("MaxBTagForBosonZ1", &maxBTagForBosonZ1_ToSaveAndRead);
        pTTree->Branch("MinBTagForBosonZ1", &minBTagForBosonZ1_ToSaveAndRead);
        pTTree->Branch("MaxBTagForBosonZ2", &maxBTagForBosonZ2_ToSaveAndRead);
        pTTree->Branch("MinBTagForBosonZ2", &minBTagForBosonZ2_ToSaveAndRead);
        pTTree->Branch("MaxCTagForBosonZ1", &maxCTagForBosonZ1_ToSaveAndRead);
        pTTree->Branch("MinCTagForBosonZ1", &minCTagForBosonZ1_ToSaveAndRead);
        pTTree->Branch("MaxCTagForBosonZ2", &maxCTagForBosonZ2_ToSaveAndRead);
        pTTree->Branch("MinCTagForBosonZ2", &minCTagForBosonZ2_ToSaveAndRead);
        pTTree->Branch("MaxBTagForBosonSyn1", &maxBTagForBosonSyn1_ToSaveAndRead);
        pTTree->Branch("MinBTagForBosonSyn1", &minBTagForBosonSyn1_ToSaveAndRead);
        pTTree->Branch("MaxBTagForBosonSyn2", &maxBTagForBosonSyn2_ToSaveAndRead);
        pTTree->Branch("MinBTagForBosonSyn2", &minBTagForBosonSyn2_ToSaveAndRead);
        pTTree->Branch("MaxCTagForBosonSyn1", &maxCTagForBosonSyn1_ToSaveAndRead);
        pTTree->Branch("MinCTagForBosonSyn1", &minCTagForBosonSyn1_ToSaveAndRead);
        pTTree->Branch("MaxCTagForBosonSyn2", &maxCTagForBosonSyn2_ToSaveAndRead);
        pTTree->Branch("MinCTagForBosonSyn2", &minCTagForBosonSyn2_ToSaveAndRead);
        pTTree->Branch("NeutrinoEnergy1", &neutrinoEnergy1_ToSaveAndRead);
        pTTree->Branch("NeutrinoPx1", &neutrinoPx1_ToSaveAndRead);
        pTTree->Branch("NeutrinoPy1", &neutrinoPy1_ToSaveAndRead);
        pTTree->Branch("NeutrinoPz1", &neutrinoPz1_ToSaveAndRead);
        pTTree->Branch("NeutrinoEnergy2", &neutrinoEnergy2_ToSaveAndRead);
        pTTree->Branch("NeutrinoPx2", &neutrinoPx2_ToSaveAndRead);
        pTTree->Branch("NeutrinoPy2", &neutrinoPy2_ToSaveAndRead);
        pTTree->Branch("NeutrinoPz2", &neutrinoPz2_ToSaveAndRead);
        pTTree->Branch("QuarkEnergy1", &quarkEnergy1_ToSaveAndRead);
        pTTree->Branch("QuarkPx1", &quarkPx1_ToSaveAndRead);
        pTTree->Branch("QuarkPy1", &quarkPy1_ToSaveAndRead);
        pTTree->Branch("QuarkPz1", &quarkPz1_ToSaveAndRead);
        pTTree->Branch("QuarkEnergy2", &quarkEnergy2_ToSaveAndRead);
        pTTree->Branch("QuarkPx2", &quarkPx2_ToSaveAndRead);
        pTTree->Branch("QuarkPy2", &quarkPy2_ToSaveAndRead);
        pTTree->Branch("QuarkPz2", &quarkPz2_ToSaveAndRead);
        pTTree->Branch("QuarkEnergy3", &quarkEnergy3_ToSaveAndRead);
        pTTree->Branch("QuarkPx3", &quarkPx3_ToSaveAndRead);
        pTTree->Branch("QuarkPy3", &quarkPy3_ToSaveAndRead);
        pTTree->Branch("QuarkPz3", &quarkPz3_ToSaveAndRead);
        pTTree->Branch("QuarkEnergy4", &quarkEnergy4_ToSaveAndRead);
        pTTree->Branch("QuarkPx4", &quarkPx4_ToSaveAndRead);
        pTTree->Branch("QuarkPy4", &quarkPy4_ToSaveAndRead);
        pTTree->Branch("QuarkPz4", &quarkPz4_ToSaveAndRead);
        pTTree->Branch("CheatedInvariantMass1", &cheatedInvariantMass1_ToSaveAndRead);
        pTTree->Branch("CheatedInvariantMass2", &cheatedInvariantMass2_ToSaveAndRead);
        pTTree->Branch("CheatedMCInvariantMass1", &cheatedMCInvariantMass1_ToSaveAndRead);
        pTTree->Branch("CheatedMCInvariantMass2", &cheatedMCInvariantMass2_ToSaveAndRead);

        const Process *pProcess(*itPro);
        TChain *pTChain = pProcess->GetTChain();

        // To Read
        pTChain->SetBranchAddress("IsAppropriateEvent", &appropriateEvent_ToSaveAndRead);
        pTChain->SetBranchAddress("IsEventWW", &isEventWW_ToSaveAndRead);
        pTChain->SetBranchAddress("IsMCEventWW", &isEventWWMC_ToSaveAndRead);
        pTChain->SetBranchAddress("IsEventZZ", &isEventZZ_ToSaveAndRead);
        pTChain->SetBranchAddress("IsMCEventZZ", &isEventZZMC_ToSaveAndRead);
        pTChain->SetBranchAddress("NPfosBosonW1", &nPfosBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("NPfosBosonW2", &nPfosBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("NPfosBosonZ1", &nPfosBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("NPfosBosonZ2", &nPfosBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("NPfosBosonSyn1", &nPfosBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("NPfosBosonSyn2", &nPfosBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonJet1Is", &combinationWJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonJet2Is", &combinationWJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonJet3Is", &combinationWJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonJet4Is", &combinationWJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet1Is", &combinationZJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet2Is", &combinationZJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet3Is", &combinationZJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet4Is", &combinationZJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonJet1Is", &combinationSynJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonJet2Is", &combinationSynJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonJet3Is", &combinationSynJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonJet4Is", &combinationSynJets4_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonQuark1Is", &combinationWQuark1_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonQuark2Is", &combinationWQuark2_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonQuark3Is", &combinationWQuark3_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonQuark4Is", &combinationWQuark4_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonQuark1Is", &combinationZQuark1_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonQuark2Is", &combinationZQuark2_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonQuark3Is", &combinationZQuark3_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonQuark4Is", &combinationZQuark4_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonQuark1Is", &combinationSynQuarks1_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonQuark2Is", &combinationSynQuarks2_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonQuark3Is", &combinationSynQuarks3_ToSaveAndRead);
        pTChain->SetBranchAddress("SynBosonQuark4Is", &combinationSynQuarks4_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet1", &nParticlesJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet2", &nParticlesJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet3", &nParticlesJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet4", &nParticlesJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet1", &nChargedParticlesJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet2", &nChargedParticlesJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet3", &nChargedParticlesJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet4", &nChargedParticlesJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoPDG", &highestEnergyPfoPDG_ToSaveAndRead);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonPDG", &highestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonPDG", &secondHighestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("MCTransverseMomentum", &transverseMomentumMC_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergy", &transverseEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("MCTransverseEnergy", &transverseEnergyMC_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyBosonW1", &energyBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyBosonW2", &energyBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyBosonZ1", &energyBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyBosonZ2", &energyBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyBosonSyn1", &energyBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyBosonSyn2", &energyBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumBosonW1", &momentumBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumBosonW2", &momentumBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumBosonZ1", &momentumBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumBosonZ2", &momentumBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumBosonSyn1", &momentumBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumBosonSyn2", &momentumBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonW1", &transverseMomentumBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonW2", &transverseMomentumBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonZ1", &transverseMomentumBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonZ2", &transverseMomentumBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonSyn1", &transverseMomentumBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonSyn2", &transverseMomentumBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaBosonW1", &cosThetaBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaBosonW2", &cosThetaBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaBosonZ1", &cosThetaBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaBosonZ2", &cosThetaBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaBosonSyn1", &cosThetaBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaBosonSyn2", &cosThetaBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonW1", &transverseEnergyBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonW2", &transverseEnergyBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonZ1", &transverseEnergyBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonZ2", &transverseEnergyBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonSyn1", &transverseEnergyBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonSyn2", &transverseEnergyBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaMissing", &cosThetaMissing_ToSaveAndRead);
        pTChain->SetBranchAddress("MCCosThetaMissing", &cosThetaMissingMC_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaMostEnergeticTrack", &cosThetaMostEnergeticTrack_ToSaveAndRead);
        pTChain->SetBranchAddress("RecoilMass", &recoilMass_ToSaveAndRead);
        pTChain->SetBranchAddress("MCRecoilMass", &recoilMassMC_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyAroundMostEnergeticTrack", &energyAroundMostEnergeticPfo_ToSaveAndRead);
        pTChain->SetBranchAddress("y12", &y12_ToSaveAndRead);
        pTChain->SetBranchAddress("y23", &y23_ToSaveAndRead);
        pTChain->SetBranchAddress("y34", &y34_ToSaveAndRead);
        pTChain->SetBranchAddress("y45", &y45_ToSaveAndRead);
        pTChain->SetBranchAddress("y56", &y56_ToSaveAndRead);
        pTChain->SetBranchAddress("y67", &y67_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassSystem", &invariantMassSystemMC_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarWBosons_ToSaveAndRead);
        pTChain->SetBranchAddress("MCCosThetaStarWBosons", &cosThetaStarWBosonsMC_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarZBosons", &cosThetaStarZBosons_ToSaveAndRead);
        pTChain->SetBranchAddress("MCCosThetaStarZBosons", &cosThetaStarZBosonsMC_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarSynBosons", &cosThetaStarSynBosons_ToSaveAndRead);
        pTChain->SetBranchAddress("MCCosThetaStarSynBosons", &cosThetaStarSynBosonsMC_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsW1", &acolinearityJetsW1_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsW2", &acolinearityJetsW2_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsZ1", &acolinearityJetsZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsZ2", &acolinearityJetsZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsSyn1", &acolinearityJetsSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsSyn2", &acolinearityJetsSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityBosonsW", &acolinearityBosonsW_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityBosonsZ", &acolinearityBosonsZ_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityBosonsSyn", &acolinearityBosonsSyn_ToSaveAndRead);
        pTChain->SetBranchAddress("PrincipleThrustValue", &principleThrustValue_ToSaveAndRead);
        pTChain->SetBranchAddress("MajorThrustValue", &majorThrustValue_ToSaveAndRead);
        pTChain->SetBranchAddress("MinorThrustValue", &minorThrustValue_ToSaveAndRead);
        pTChain->SetBranchAddress("XThrustAxis", &xThrustAxis_ToSaveAndRead);
        pTChain->SetBranchAddress("YThrustAxis", &yThrustAxis_ToSaveAndRead);
        pTChain->SetBranchAddress("ZThrustAxis", &zThrustAxis_ToSaveAndRead);
        pTChain->SetBranchAddress("Sphericity", &sphericity_ToSaveAndRead);
        pTChain->SetBranchAddress("Aplanarity", &aplanarity_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronEnergy", &highestEnergyElectronEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronMomentum", &highestEnergyElectronMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronTransverseMomentum", &highestEnergyElectronTransverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronCosTheta", &highestEnergyElectronCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonEnergy", &highestEnergyMuonEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonMomentum", &highestEnergyMuonMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonTransverseMomentum", &highestEnergyMuonTransverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonCosTheta", &highestEnergyMuonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonEnergy", &highestEnergyPhotonEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonMomentum", &highestEnergyPhotonMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonTransverseMomentum", &highestEnergyPhotonTransverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonCosTheta", &highestEnergyPhotonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoEnergy", &highestEnergyPfoEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoMomentum", &highestEnergyPfoMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoTransverseMomentum", &highestEnergyPfoTransverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoCosTheta", &highestEnergyPfoCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonEnergy", &highestEnergyIsolatedLeptonEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonMomentum", &highestEnergyIsolatedLeptonMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonTransverseMomentum", &highestEnergyIsolatedLeptonTransverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonCosTheta", &highestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonEnergy", &secondHighestEnergyIsolatedLeptonEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonMomentum", &secondHighestEnergyIsolatedLeptonMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonTransverseMomentum", &secondHighestEnergyIsolatedLeptonTransverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonCosTheta", &secondHighestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassWBoson1", &invariantMassWBosons1_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassWBoson2", &invariantMassWBosons2_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassZBoson1", &invariantMassZBosons1_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassZBoson2", &invariantMassZBosons2_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassSynBoson1", &invariantMassSynBoson1_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassSynBoson2", &invariantMassSynBoson2_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassWBoson1", &invariantMassWBosonsMC1_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassWBoson2", &invariantMassWBosonsMC2_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassZBoson1", &invariantMassZBosonsMC1_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassZBoson2", &invariantMassZBosonsMC2_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassSynBoson1", &invariantMassSynBosonsMC1_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassSynBoson2", &invariantMassSynBosonsMC2_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassBoson1Pairing0123", &invariantMassBoson1Pairing0123_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassBoson2Pairing0123", &invariantMassBoson2Pairing0123_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassBoson1Pairing0213", &invariantMassBoson1Pairing0213_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassBoson2Pairing0213", &invariantMassBoson2Pairing0213_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassBoson1Pairing0312", &invariantMassBoson1Pairing0312_ToSaveAndRead);
        pTChain->SetBranchAddress("InvariantMassBoson2Pairing0312", &invariantMassBoson2Pairing0312_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassBoson1Pairing0123", &invariantMassBosonMC1Pairing0123_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassBoson2Pairing0123", &invariantMassBosonMC2Pairing0123_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassBoson1Pairing0213", &invariantMassBosonMC1Pairing0213_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassBoson2Pairing0213", &invariantMassBosonMC2Pairing0213_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassBoson1Pairing0312", &invariantMassBosonMC1Pairing0312_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvariantMassBoson2Pairing0312", &invariantMassBosonMC2Pairing0312_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet1", &energyJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet2", &energyJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet3", &energyJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet4", &energyJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumJet1", &momentumJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumJet2", &momentumJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumJet3", &momentumJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("MomentumJet4", &momentumJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumJet1", &transverseMomentumJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumJet2", &transverseMomentumJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumJet3", &transverseMomentumJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumJet4", &transverseMomentumJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaJet1", &cosThetaJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaJet2", &cosThetaJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaJet3", &cosThetaJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaJet4", &cosThetaJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarWJet1", &cosThetaStarWJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarWJet2", &cosThetaStarWJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarZJet1", &cosThetaStarZJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarZJet2", &cosThetaStarZJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarSynJet1", &cosThetaStarSynJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarSynJet2", &cosThetaStarSynJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet1", &bTagForJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet2", &bTagForJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet3", &bTagForJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet4", &bTagForJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet1", &cTagForJet1_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet2", &cTagForJet2_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet3", &cTagForJet3_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet4", &cTagForJet4_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxBTagForBosonW1", &maxBTagForBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("MinBTagForBosonW1", &minBTagForBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxBTagForBosonW2", &maxBTagForBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("MinBTagForBosonW2", &minBTagForBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxCTagForBosonW1", &maxCTagForBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("MinCTagForBosonW1", &minCTagForBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxCTagForBosonW2", &maxCTagForBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("MinCTagForBosonW2", &minCTagForBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxBTagForBosonZ1", &maxBTagForBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("MinBTagForBosonZ1", &minBTagForBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxBTagForBosonZ2", &maxBTagForBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("MinBTagForBosonZ2", &minBTagForBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxCTagForBosonZ1", &maxCTagForBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("MinCTagForBosonZ1", &minCTagForBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxCTagForBosonZ2", &maxCTagForBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("MinCTagForBosonZ2", &minCTagForBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxBTagForBosonSyn1", &maxBTagForBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("MinBTagForBosonSyn1", &minBTagForBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxBTagForBosonSyn2", &maxBTagForBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("MinBTagForBosonSyn2", &minBTagForBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxCTagForBosonSyn1", &maxCTagForBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("MinCTagForBosonSyn1", &minCTagForBosonSyn1_ToSaveAndRead);
        pTChain->SetBranchAddress("MaxCTagForBosonSyn2", &maxCTagForBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("MinCTagForBosonSyn2", &minCTagForBosonSyn2_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoEnergy1", &neutrinoEnergy1_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoPx1", &neutrinoPx1_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoPy1", &neutrinoPy1_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoPz1", &neutrinoPz1_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoEnergy2", &neutrinoEnergy2_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoPx2", &neutrinoPx2_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoPy2", &neutrinoPy2_ToSaveAndRead);
        pTChain->SetBranchAddress("NeutrinoPz2", &neutrinoPz2_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkEnergy1", &quarkEnergy1_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPx1", &quarkPx1_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPy1", &quarkPy1_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPz1", &quarkPz1_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkEnergy2", &quarkEnergy2_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPx2", &quarkPx2_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPy2", &quarkPy2_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPz2", &quarkPz2_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkEnergy3", &quarkEnergy3_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPx3", &quarkPx3_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPy3", &quarkPy3_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPz3", &quarkPz3_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkEnergy4", &quarkEnergy4_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPx4", &quarkPx4_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPy4", &quarkPy4_ToSaveAndRead);
        pTChain->SetBranchAddress("QuarkPz4", &quarkPz4_ToSaveAndRead);
        pTChain->SetBranchAddress("CheatedInvariantMass1", &cheatedInvariantMass1_ToSaveAndRead);
        pTChain->SetBranchAddress("CheatedInvariantMass2", &cheatedInvariantMass2_ToSaveAndRead);
        pTChain->SetBranchAddress("CheatedMCInvariantMass1", &cheatedMCInvariantMass1_ToSaveAndRead);
        pTChain->SetBranchAddress("CheatedMCInvariantMass2", &cheatedMCInvariantMass2_ToSaveAndRead);

        std::cout << "Number of TChain entries: " << pTChain->GetEntries() << std::endl;
        std::cout << "Number of TrainingTChain entries: " << pProcess->GetTrainingTChain()->GetEntries() << std::endl;

        int jobEventNumber(0), simulationEventNumber(std::numeric_limits<int>::max());
        IntVector readInSGN;

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);

            ///< From filename access the global event number
            TFile *pTFileActive = pTChain->GetCurrentFile();
            std::string activeFileName(pTFileActive->GetName());

            if (pProcess->GetEventType() == "ee_nunuqqqq")
            {
                simulationEventNumber = atoi(this->GetGeneratorSerialNumber(activeFileName).c_str());

                if (std::find(readInSGN.begin(), readInSGN.end(), simulationEventNumber) == readInSGN.end())
                {
                    readInSGN.push_back(simulationEventNumber);
                    jobEventNumber = 0;
                }
            }
            else
            {
                simulationEventNumber = 0;
            }

            jobEventNumber++;

            globalEventNumber_ToSave = pEventNumbers->SetGlobalEventNumber(simulationEventNumber, jobEventNumber);

            // Set all variables needed by MVA reader
            // Event
            nPFOs_ToSaveAndRead = nParticlesJet1_ToSaveAndRead + nParticlesJet2_ToSaveAndRead + nParticlesJet3_ToSaveAndRead + nParticlesJet4_ToSaveAndRead;
            nPFOs = (Float_t)(nPFOs_ToSaveAndRead);
            highestEnergyPfoPDG = (Float_t)(highestEnergyPfoPDG_ToSaveAndRead);
            transverseMomentum = (Float_t)(transverseMomentum_ToSaveAndRead);
            cosThetaMissing = (Float_t)(cosThetaMissing_ToSaveAndRead);
            cosThetaMostEnergeticTrack = (Float_t)(cosThetaMostEnergeticTrack_ToSaveAndRead);
            y12 = (Float_t)(y12_ToSaveAndRead);
            y23 = (Float_t)(y23_ToSaveAndRead);
            y34 = (Float_t)(y34_ToSaveAndRead);
            y45 = (Float_t)(y45_ToSaveAndRead);
            y56 = (Float_t)(y56_ToSaveAndRead);
            y67 = (Float_t)(y67_ToSaveAndRead);
            principleThrustValue = (Float_t)(principleThrustValue_ToSaveAndRead);
            sphericity = (Float_t)(sphericity_ToSaveAndRead);
            aplanarity = (Float_t)(aplanarity_ToSaveAndRead);
            highestEnergyElectronEnergy = (Float_t)(highestEnergyElectronEnergy_ToSaveAndRead);
            highestEnergyPfoEnergy = (Float_t)(highestEnergyPfoEnergy_ToSaveAndRead);
            // Bosons
            energyBosonSyn1 = (Float_t)(energyBosonSyn1_ToSaveAndRead);
            energyBosonSyn2 = (Float_t)(energyBosonSyn2_ToSaveAndRead);
            acolinearityBosonsSyn = (Float_t)(acolinearityBosonsSyn_ToSaveAndRead);
            invariantMassSynBoson1 = (Float_t)(invariantMassSynBoson1_ToSaveAndRead);
            invariantMassSynBoson2 = (Float_t)(invariantMassSynBoson2_ToSaveAndRead);
            // Jets
            acolinearityJetsSyn1 = (Float_t)(acolinearityJetsSyn1_ToSaveAndRead);
            acolinearityJetsSyn2 = (Float_t)(acolinearityJetsSyn2_ToSaveAndRead);

            if (!perfect)
            {
                bdt = (Double_t)(reader->EvaluateMVA("BDT method"));
//            cuts = reader->EvaluateMVA("Cuts method");
//            likelihood = reader->EvaluateMVA("Likelihood method");
//            pders = reader->EvaluateMVA("PDERS method");
//            knn = reader->EvaluateMVA("KNN method");
//            cfmlpann = reader->EvaluateMVA("CFMlpANN method");
            }

            else
            {
                bdt = 42.0;
            }

            pTTree->Fill();
        }

        TString filename = "/r06/lc/sg568/PhysicsAnalysis/Analysis/RootFilesPostMVA/RootFiles_Multivariant_" + pProcess->GetEventType() + "_" + this->NumberToString(pProcess->GetEnergy()) + "GeV_" + pProcess->GetRootSuffix() + "_AnalysisTag" + this->NumberToString(pProcess->GetAnalysisTag());

        if (perfect)
        {
            filename = filename + "_NoMVA.root";
        }
        else
        {
            filename = filename + ".root";
        }

        TFile *pTFile = new TFile(filename, "recreate");
        pTTree->SetDirectory(pTFile);

        pTFile->cd();
        pTTree->Write();

        pTFile->Close();
        delete pTFile;
    }
    delete pEventNumbers;
}

//=====================================================================

std::string TMVAClassificationApplication3000::GetGeneratorSerialNumber(std::string filename)
{
    std::size_t position = filename.find("GenN");
    std::string substring = filename.substr(position+5);
    std::size_t position2 = substring.find("_");
    std::string substring2 = substring.substr(0,position2);
    return substring2;
}

//=====================================================================

template <class T>
std::string TMVAClassificationApplication3000::NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
