/**
 *  @file   AnalysisScripts/src/TMVAClassificationApplication.cxx 
 * 
 *  @brief  Implementation of the TMVA classifier class.
 * 
 *  $Log: $
 */

#include "TMVAClassificationApplication.h"

//=====================================================================

int main(int argc, char **argv)
{

    typedef std::vector<const Process*> ProcessVector;

//    const Process *pProcess_ee_nunuqqqq_1 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.5","ee_nunuqqqq",22.16,1500,1400,11);
//    const Process *pProcess_ee_nunuqqqq_2 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11);
//    const Process *pProcess_ee_nunuqqqq_3 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.9","ee_nunuqqqq",22.16,1500,1400,11);
//    const Process *pProcess_ee_nunuqqqq_4 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.0","ee_nunuqqqq",22.16,1500,1400,11);
//    const Process *pProcess_ee_nunuqqqq_5 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","1.1","ee_nunuqqqq",22.16,1500,1400,11);
    const Process *pProcess_ee_nunuqqqq_6 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","TightSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,13);
    const Process *pProcess_ee_nunuqqqq_7 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","LooseSelectedPandoraPFANewPFOs","ExclusiveNJets",2,"kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,13);
//    const Process *pProcess_ee_nunuqqqq_8 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"ee_kt_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11);
//    const Process *pProcess_ee_nunuqqqq_9 = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","SelectedPandoraPFANewPFOs","ExclusiveNJets",2,"cambridge_algorithm","0.7","ee_nunuqqqq",22.16,1500,1400,11);

////////
//
/*
    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",22.16,1500,1400,9);

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqqqq",115.3,1500,1400,9);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_llqqqq",71.7,1500,1400,9);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqqq",1328.1,1500,1400,9);

    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqq",933.9,1500,1400,9);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqq",4309.7,1500,1400,9);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqll",2725.8,1500,1400,9);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qq",4009.5,1500,1400,9);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_EPA",287.1,1500,1400,9);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_BS",1160.7,1500,1400,9);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_EPA",286.9,1500,1400,9);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_BS",1156.3,1500,1400,9);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_EPA",32.6,1500,1400,9);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_BS",136.9,1500,1400,9);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_EPA",32.6,1500,1400,9);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_BS",136.4,1500,1400,9);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_EPA",753.0,1500,1400,9);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_BS",4034.8,1500,1400,9);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_EPA",4018.7,1500,1400,9);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_BS",4009.5,1500,1400,9);

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
*/
//
///////

    ProcessVector processes;

//    processes.push_back(pProcess_ee_nunuqqqq_1);
//    processes.push_back(pProcess_ee_nunuqqqq_2);
//    processes.push_back(pProcess_ee_nunuqqqq_3);
//    processes.push_back(pProcess_ee_nunuqqqq_4);
//    processes.push_back(pProcess_ee_nunuqqqq_5);
    processes.push_back(pProcess_ee_nunuqqqq_6);
    processes.push_back(pProcess_ee_nunuqqqq_7);
//    processes.push_back(pProcess_ee_nunuqqqq_8);
//    processes.push_back(pProcess_ee_nunuqqqq_9);

    TMVAClassificationApplication *pTMVAClassificationApplication = new TMVAClassificationApplication(processes, true);
}

//=====================================================================

TMVAClassificationApplication::TMVAClassificationApplication(ProcessVector processes, bool perfect)
{
    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    EventNumbers *pEventNumbers = new EventNumbers();

    Float_t nPFOs(std::numeric_limits<float>::max());
    Float_t numberOfIsolatedLeptons(std::numeric_limits<float>::max());
    Float_t invMassWVector1(std::numeric_limits<float>::max());
    Float_t invMassWVector2(std::numeric_limits<float>::max());
    Float_t invMassZVector1(std::numeric_limits<float>::max());
    Float_t invMassZVector2(std::numeric_limits<float>::max());
    Float_t transverseMomentum(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonW1(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonW2(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonZ1(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonZ2(std::numeric_limits<float>::max());
    Float_t transverseEnergy(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonW1(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonW2(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonZ1(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonZ2(std::numeric_limits<float>::max());
    Float_t cosThetaMissing(std::numeric_limits<float>::max());
    Float_t cosThetaMostEnergeticTrack(std::numeric_limits<float>::max());
    Float_t y12(std::numeric_limits<float>::max());
    Float_t y23(std::numeric_limits<float>::max());
    Float_t y34(std::numeric_limits<float>::max());
    Float_t y45(std::numeric_limits<float>::max());
    Float_t y56(std::numeric_limits<float>::max());
    Float_t y67(std::numeric_limits<float>::max());
    Float_t invariantMassSystem(std::numeric_limits<float>::max());
    Float_t cosThetaStarWBosons(std::numeric_limits<float>::max());
    Float_t cosThetaStarZBosons(std::numeric_limits<float>::max());
    Float_t cosThetaStarWJet1(std::numeric_limits<float>::max());
    Float_t cosThetaStarWJet2(std::numeric_limits<float>::max());
    Float_t cosThetaStarZJet1(std::numeric_limits<float>::max());
    Float_t cosThetaStarZJet2(std::numeric_limits<float>::max());
    Float_t acolinearityJetsW1(std::numeric_limits<float>::max());
    Float_t acolinearityJetsW2(std::numeric_limits<float>::max());
    Float_t acolinearityJetsZ1(std::numeric_limits<float>::max());
    Float_t acolinearityJetsZ2(std::numeric_limits<float>::max());
    Float_t acolinearityBosonsW(std::numeric_limits<float>::max());
    Float_t acolinearityBosonsZ(std::numeric_limits<float>::max());
    Float_t principleThrustValue(std::numeric_limits<float>::max());
    Float_t majorThrustValue(std::numeric_limits<float>::max());
    Float_t minorThrustValue(std::numeric_limits<float>::max());
    Float_t sphericity(std::numeric_limits<float>::max());
    Float_t aplanarity(std::numeric_limits<float>::max());

    if (!perfect)
    {
        reader->AddVariable("NPfos := NParticlesJet1+NParticlesJet2+NParticlesJet3+NParticlesJet4", &nPFOs);
        reader->AddVariable("InvMassWVector1", &invMassWVector1);
        reader->AddVariable("InvMassWVector2", &invMassWVector2);
        reader->AddVariable("InvMassZVector1", &invMassZVector1);
        reader->AddVariable("InvMassZVector2", &invMassZVector2);
        reader->AddVariable("TransverseMomentum", &transverseMomentum);
        reader->AddVariable("TransverseMomentumBosonW1", &transverseMomentumBosonW1);
        reader->AddVariable("TransverseMomentumBosonW2", &transverseMomentumBosonW2);
        reader->AddVariable("TransverseMomentumBosonZ1", &transverseMomentumBosonZ1);
        reader->AddVariable("TransverseMomentumBosonZ2", &transverseMomentumBosonZ2);
        reader->AddVariable("TransverseEnergy", &transverseEnergy);
        reader->AddVariable("TransverseEnergyBosonW1", &transverseEnergyBosonW1);
        reader->AddVariable("TransverseEnergyBosonW2", &transverseEnergyBosonW2);
        reader->AddVariable("TransverseEnergyBosonZ1", &transverseEnergyBosonZ1);
        reader->AddVariable("TransverseEnergyBosonZ2", &transverseEnergyBosonZ2);
        reader->AddVariable("CosThetaMissing", &cosThetaMissing);
        reader->AddVariable("CosThetaMostEnergeticTrack", &cosThetaMostEnergeticTrack);
        reader->AddVariable("y12", &y12);
        reader->AddVariable("y23", &y23);
        reader->AddVariable("y34", &y34);
        reader->AddVariable("y45", &y45);
        reader->AddVariable("y56", &y56);
        reader->AddVariable("y67", &y67);
        reader->AddVariable("InvariantMassSystem", &invariantMassSystem);
        reader->AddVariable("CosThetaStarWBosons", &cosThetaStarWBosons);
        reader->AddVariable("CosThetaStarZBosons", &cosThetaStarZBosons);
        reader->AddVariable("CosThetaStarWJet1", &cosThetaStarWJet1);
        reader->AddVariable("CosThetaStarWJet2", &cosThetaStarWJet2);
        reader->AddVariable("CosThetaStarZJet1", &cosThetaStarZJet1);
        reader->AddVariable("CosThetaStarZJet2", &cosThetaStarZJet2);
        reader->AddVariable("AcolinearityJetsW1", &acolinearityJetsW1);
        reader->AddVariable("AcolinearityJetsW2", &acolinearityJetsW2);
        reader->AddVariable("AcolinearityJetsZ1", &acolinearityJetsZ1);
        reader->AddVariable("AcolinearityJetsZ2", &acolinearityJetsZ2);
        reader->AddVariable("AcolinearityBosonsW", &acolinearityBosonsW);
        reader->AddVariable("AcolinearityBosonsZ", &acolinearityBosonsZ);
        reader->AddVariable("PrincipleThrustValue", &principleThrustValue);
        reader->AddVariable("MajorThrustValue", &majorThrustValue);
        reader->AddVariable("MinorThrustValue", &minorThrustValue);
        reader->AddVariable("Sphericity", &sphericity);
        reader->AddVariable("Aplanarity", &aplanarity);

        reader->BookMVA("BDT method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_BDT.weights.xml");
//    reader->BookMVA("Cuts method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_Cuts.weights.xml");
//    reader->BookMVA("Likelihood method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_Likelihood.weights.xml");
//    reader->BookMVA("PDERS method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_PDERS.weights.xml");
//    reader->BookMVA("KNN method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_KNN.weights.xml");
//    reader->BookMVA("CFMlpANN method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_CFMlpANN.weights.xml");
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
        Int_t combinationWJets1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWJets2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWJets3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationWJets4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJets1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJets2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJets3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t combinationZJets4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJets1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJets2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJets3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nParticlesJets4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJets1_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJets2_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJets3_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nChargedParticlesJets4_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t highestEnergyPfoPDG_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t highestEnergyIsolatedLeptonPDG_ToSaveAndRead(std::numeric_limits<int>::max());
        Int_t secondHighestEnergyIsolatedLeptonPDG_ToSaveAndRead(std::numeric_limits<int>::max());

        Double_t transverseMomentum_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumMC_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergy_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyMC_ToSaveAndRead(std::numeric_limits<double>::max());
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
        Double_t acolinearityJetsW1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsW2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsZ1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsZ2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityBosonsW_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t acolinearityBosonsZ_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t principleThrustValue_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t majorThrustValue_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t minorThrustValue_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t xThrustAxis_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t yThrustAxis_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t zThrustAxis_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t sphericity_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t aplanarity_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronE_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronP_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronPt_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyElectronCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonE_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonP_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonPt_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyMuonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonE_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonP_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonPt_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPhotonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoE_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoP_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoPt_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyPfoCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonE_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonP_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonPt_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t highestEnergyIsolatedLeptonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonE_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonP_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonPt_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t secondHighestEnergyIsolatedLeptonCosTheta_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosons1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosons2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosonsMC1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassWBosonsMC2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosons1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosons2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosonsMC1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t invariantMassZBosonsMC2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJets1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJets2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJets3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t energyJets4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWJets1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWJets2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZJets1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZJets2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJets1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJets2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJets3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t bTagForJets4_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJets1_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJets2_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJets3_ToSaveAndRead(std::numeric_limits<double>::max());
        Double_t cTagForJets4_ToSaveAndRead(std::numeric_limits<double>::max());

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
        pTTree->Branch("WBosonJet1Is", &combinationWJets1_ToSaveAndRead);
        pTTree->Branch("WBosonJet2Is", &combinationWJets2_ToSaveAndRead);
        pTTree->Branch("WBosonJet3Is", &combinationWJets3_ToSaveAndRead);
        pTTree->Branch("WBosonJet4Is", &combinationWJets4_ToSaveAndRead);
        pTTree->Branch("ZBosonJet1Is", &combinationZJets1_ToSaveAndRead);
        pTTree->Branch("ZBosonJet2Is", &combinationZJets2_ToSaveAndRead);
        pTTree->Branch("ZBosonJet3Is", &combinationZJets3_ToSaveAndRead);
        pTTree->Branch("ZBosonJet4Is", &combinationZJets4_ToSaveAndRead);
        pTTree->Branch("NParticlesJet1", &nParticlesJets1_ToSaveAndRead);
        pTTree->Branch("NParticlesJet2", &nParticlesJets2_ToSaveAndRead);
        pTTree->Branch("NParticlesJet3", &nParticlesJets3_ToSaveAndRead);
        pTTree->Branch("NParticlesJet4", &nParticlesJets4_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet1", &nChargedParticlesJets1_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet2", &nChargedParticlesJets2_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet3", &nChargedParticlesJets3_ToSaveAndRead);
        pTTree->Branch("NChargedParticlesJet4", &nChargedParticlesJets4_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoPDG", &highestEnergyPfoPDG_ToSaveAndRead);
        pTTree->Branch("NumberOfIsolatedLeptons", &nIsolatedLeptons_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonPDG", &highestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonPDG", &secondHighestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTTree->Branch("TransverseMomentum", &transverseMomentum_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonW1", &transverseMomentumBosonW1_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonW2", &transverseMomentumBosonW2_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonZ1", &transverseMomentumBosonZ1_ToSaveAndRead);
        pTTree->Branch("TransverseMomentumBosonZ2", &transverseMomentumBosonZ2_ToSaveAndRead);
        pTTree->Branch("MCTransverseMomentum", &transverseMomentumMC_ToSaveAndRead);
        pTTree->Branch("TransverseEnergy", &transverseEnergy_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonW1", &transverseEnergyBosonW1_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonW2", &transverseEnergyBosonW2_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonZ1", &transverseEnergyBosonZ1_ToSaveAndRead);
        pTTree->Branch("TransverseEnergyBosonZ2", &transverseEnergyBosonZ2_ToSaveAndRead);
        pTTree->Branch("MCTransverseEnergy", &transverseEnergyMC_ToSaveAndRead);
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
        pTTree->Branch("AcolinearityJetsW1", &acolinearityJetsW1_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsW2", &acolinearityJetsW2_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsZ1", &acolinearityJetsZ1_ToSaveAndRead);
        pTTree->Branch("AcolinearityJetsZ2", &acolinearityJetsZ2_ToSaveAndRead);
        pTTree->Branch("AcolinearityBosonsW", &acolinearityBosonsW_ToSaveAndRead);
        pTTree->Branch("AcolinearityBosonsZ", &acolinearityBosonsZ_ToSaveAndRead);
        pTTree->Branch("PrincipleThrustValue", &principleThrustValue_ToSaveAndRead);
        pTTree->Branch("MajorThrustValue", &majorThrustValue_ToSaveAndRead);
        pTTree->Branch("MinorThrustValue", &minorThrustValue_ToSaveAndRead);
        pTTree->Branch("XThrustAxis", &xThrustAxis_ToSaveAndRead);
        pTTree->Branch("YThrustAxis", &yThrustAxis_ToSaveAndRead);
        pTTree->Branch("ZThrustAxis", &zThrustAxis_ToSaveAndRead);
        pTTree->Branch("Sphericity", &sphericity_ToSaveAndRead);
        pTTree->Branch("Aplanarity", &aplanarity_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronEnergy", &highestEnergyElectronE_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronMomentum", &highestEnergyElectronP_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronTransverseMomentum", &highestEnergyElectronPt_ToSaveAndRead);
        pTTree->Branch("HighestEnergyElectronCosTheta", &highestEnergyElectronCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonEnergy", &highestEnergyMuonE_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonMomentum", &highestEnergyMuonP_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonTransverseMomentum", &highestEnergyMuonPt_ToSaveAndRead);
        pTTree->Branch("HighestEnergyMuonCosTheta", &highestEnergyMuonCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonEnergy", &highestEnergyPhotonE_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonMomentum", &highestEnergyPhotonP_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonTransverseMomentum", &highestEnergyPhotonPt_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPhotonCosTheta", &highestEnergyPhotonCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoEnergy", &highestEnergyPfoE_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoMomentum", &highestEnergyPfoP_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoTransverseMomentum", &highestEnergyPfoPt_ToSaveAndRead);
        pTTree->Branch("HighestEnergyPfoCosTheta", &highestEnergyPfoCosTheta_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonEnergy", &highestEnergyIsolatedLeptonE_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonMomentum", &highestEnergyIsolatedLeptonP_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonTransverseMomentum", &highestEnergyIsolatedLeptonPt_ToSaveAndRead);
        pTTree->Branch("HighestEnergyIsolatedLeptonCosTheta", &highestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonEnergy", &secondHighestEnergyIsolatedLeptonE_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonMomentum", &secondHighestEnergyIsolatedLeptonP_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonTransverseMomentum", &secondHighestEnergyIsolatedLeptonPt_ToSaveAndRead);
        pTTree->Branch("SecondHighestEnergyIsolatedLeptonCosTheta", &secondHighestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTTree->Branch("InvMassWVector1", &invariantMassWBosons1_ToSaveAndRead);
        pTTree->Branch("InvMassWVector2", &invariantMassWBosons2_ToSaveAndRead);
        pTTree->Branch("MCInvMassWVector1", &invariantMassWBosonsMC1_ToSaveAndRead);
        pTTree->Branch("MCInvMassWVector2", &invariantMassWBosonsMC2_ToSaveAndRead);
        pTTree->Branch("InvMassZVector1", &invariantMassZBosons1_ToSaveAndRead);
        pTTree->Branch("InvMassZVector2", &invariantMassZBosons2_ToSaveAndRead);
        pTTree->Branch("MCInvMassZVector1", &invariantMassZBosonsMC1_ToSaveAndRead);
        pTTree->Branch("MCInvMassZVector2", &invariantMassZBosonsMC2_ToSaveAndRead);
        pTTree->Branch("EnergyJet1", &energyJets1_ToSaveAndRead);
        pTTree->Branch("EnergyJet2", &energyJets2_ToSaveAndRead);
        pTTree->Branch("EnergyJet3", &energyJets3_ToSaveAndRead);
        pTTree->Branch("EnergyJet4", &energyJets4_ToSaveAndRead);
        pTTree->Branch("CosThetaStarWJet1", &cosThetaStarWJets1_ToSaveAndRead);
        pTTree->Branch("CosThetaStarWJet2", &cosThetaStarWJets2_ToSaveAndRead);
        pTTree->Branch("CosThetaStarZJet1", &cosThetaStarZJets1_ToSaveAndRead);
        pTTree->Branch("CosThetaStarZJet2", &cosThetaStarZJets2_ToSaveAndRead);
        pTTree->Branch("BTagForJet1", &bTagForJets1_ToSaveAndRead);
        pTTree->Branch("BTagForJet2", &bTagForJets2_ToSaveAndRead);
        pTTree->Branch("BTagForJet3", &bTagForJets3_ToSaveAndRead);
        pTTree->Branch("BTagForJet4", &bTagForJets4_ToSaveAndRead);
        pTTree->Branch("CTagForJet1", &cTagForJets1_ToSaveAndRead);
        pTTree->Branch("CTagForJet2", &cTagForJets2_ToSaveAndRead);
        pTTree->Branch("CTagForJet3", &cTagForJets3_ToSaveAndRead);
        pTTree->Branch("CTagForJet4", &cTagForJets4_ToSaveAndRead);

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
        pTChain->SetBranchAddress("WBosonJet1Is", &combinationWJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonJet2Is", &combinationWJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonJet3Is", &combinationWJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("WBosonJet4Is", &combinationWJets4_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet1Is", &combinationZJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet2Is", &combinationZJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet3Is", &combinationZJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("ZBosonJet4Is", &combinationZJets4_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet1", &nParticlesJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet2", &nParticlesJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet3", &nParticlesJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("NParticlesJet4", &nParticlesJets4_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet1", &nChargedParticlesJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet2", &nChargedParticlesJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet3", &nChargedParticlesJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("NChargedParticlesJet4", &nChargedParticlesJets4_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoPDG", &highestEnergyPfoPDG_ToSaveAndRead);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonPDG", &highestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonPDG", &secondHighestEnergyIsolatedLeptonPDG_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonW1", &transverseMomentumBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonW2", &transverseMomentumBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonZ1", &transverseMomentumBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonZ2", &transverseMomentumBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("MCTransverseMomentum", &transverseMomentumMC_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergy", &transverseEnergy_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonW1", &transverseEnergyBosonW1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonW2", &transverseEnergyBosonW2_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonZ1", &transverseEnergyBosonZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonZ2", &transverseEnergyBosonZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("MCTransverseEnergy", &transverseEnergyMC_ToSaveAndRead);
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
        pTChain->SetBranchAddress("AcolinearityJetsW1", &acolinearityJetsW1_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsW2", &acolinearityJetsW2_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsZ1", &acolinearityJetsZ1_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityJetsZ2", &acolinearityJetsZ2_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityBosonsW", &acolinearityBosonsW_ToSaveAndRead);
        pTChain->SetBranchAddress("AcolinearityBosonsZ", &acolinearityBosonsZ_ToSaveAndRead);
        pTChain->SetBranchAddress("PrincipleThrustValue", &principleThrustValue_ToSaveAndRead);
        pTChain->SetBranchAddress("MajorThrustValue", &majorThrustValue_ToSaveAndRead);
        pTChain->SetBranchAddress("MinorThrustValue", &minorThrustValue_ToSaveAndRead);
        pTChain->SetBranchAddress("XThrustAxis", &xThrustAxis_ToSaveAndRead);
        pTChain->SetBranchAddress("YThrustAxis", &yThrustAxis_ToSaveAndRead);
        pTChain->SetBranchAddress("ZThrustAxis", &zThrustAxis_ToSaveAndRead);
        pTChain->SetBranchAddress("Sphericity", &sphericity_ToSaveAndRead);
        pTChain->SetBranchAddress("Aplanarity", &aplanarity_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronEnergy", &highestEnergyElectronE_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronMomentum", &highestEnergyElectronP_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronTransverseMomentum", &highestEnergyElectronPt_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyElectronCosTheta", &highestEnergyElectronCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonEnergy", &highestEnergyMuonE_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonMomentum", &highestEnergyMuonP_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonTransverseMomentum", &highestEnergyMuonPt_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyMuonCosTheta", &highestEnergyMuonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonEnergy", &highestEnergyPhotonE_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonMomentum", &highestEnergyPhotonP_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonTransverseMomentum", &highestEnergyPhotonPt_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPhotonCosTheta", &highestEnergyPhotonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoEnergy", &highestEnergyPfoE_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoMomentum", &highestEnergyPfoP_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoTransverseMomentum", &highestEnergyPfoPt_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyPfoCosTheta", &highestEnergyPfoCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonEnergy", &highestEnergyIsolatedLeptonE_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonMomentum", &highestEnergyIsolatedLeptonP_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonTransverseMomentum", &highestEnergyIsolatedLeptonPt_ToSaveAndRead);
        pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonCosTheta", &highestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonEnergy", &secondHighestEnergyIsolatedLeptonE_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonMomentum", &secondHighestEnergyIsolatedLeptonP_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonTransverseMomentum", &secondHighestEnergyIsolatedLeptonPt_ToSaveAndRead);
        pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonCosTheta", &secondHighestEnergyIsolatedLeptonCosTheta_ToSaveAndRead);
        pTChain->SetBranchAddress("InvMassWVector1", &invariantMassWBosons1_ToSaveAndRead);
        pTChain->SetBranchAddress("InvMassWVector2", &invariantMassWBosons2_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvMassWVector1", &invariantMassWBosonsMC1_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvMassWVector2", &invariantMassWBosonsMC2_ToSaveAndRead);
        pTChain->SetBranchAddress("InvMassZVector1", &invariantMassZBosons1_ToSaveAndRead);
        pTChain->SetBranchAddress("InvMassZVector2", &invariantMassZBosons2_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvMassZVector1", &invariantMassZBosonsMC1_ToSaveAndRead);
        pTChain->SetBranchAddress("MCInvMassZVector2", &invariantMassZBosonsMC2_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet1", &energyJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet2", &energyJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet3", &energyJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("EnergyJet4", &energyJets4_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarWJet1", &cosThetaStarWJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarWJet2", &cosThetaStarWJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarZJet1", &cosThetaStarZJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("CosThetaStarZJet2", &cosThetaStarZJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet1", &bTagForJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet2", &bTagForJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet3", &bTagForJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("BTagForJet4", &bTagForJets4_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet1", &cTagForJets1_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet2", &cTagForJets2_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet3", &cTagForJets3_ToSaveAndRead);
        pTChain->SetBranchAddress("CTagForJet4", &cTagForJets4_ToSaveAndRead);

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
            //std::cout << "simulationEventNumber : " << simulationEventNumber << std::endl;
            //std::cout << "jobEventNumber : " << jobEventNumber << std::endl;
            //std::cout << "globalEventNumber_ToSave : " << globalEventNumber_ToSave << std::endl;

            ///< Set all variables needed by MVA reader
            nPFOs_ToSaveAndRead = nParticlesJets1_ToSaveAndRead + nParticlesJets2_ToSaveAndRead + nParticlesJets3_ToSaveAndRead + nParticlesJets4_ToSaveAndRead;
            nPFOs = (Float_t)(nPFOs_ToSaveAndRead);
            numberOfIsolatedLeptons = (Float_t)(nIsolatedLeptons_ToSaveAndRead);
            invMassWVector1 = (Float_t)(invariantMassWBosons1_ToSaveAndRead);
            invMassWVector2 = (Float_t)(invariantMassWBosons2_ToSaveAndRead);
            invMassZVector1 = (Float_t)(invariantMassZBosons1_ToSaveAndRead);
            invMassZVector2 = (Float_t)(invariantMassZBosons2_ToSaveAndRead);
            transverseMomentum = (Float_t)(transverseMomentum_ToSaveAndRead);
            transverseMomentumBosonW1 = (Float_t)(transverseMomentumBosonW1_ToSaveAndRead);
            transverseMomentumBosonW2 = (Float_t)(transverseMomentumBosonW2_ToSaveAndRead);
            transverseMomentumBosonZ1 = (Float_t)(transverseMomentumBosonZ1_ToSaveAndRead);
            transverseMomentumBosonZ2 = (Float_t)(transverseMomentumBosonZ2_ToSaveAndRead);
            transverseEnergy = (Float_t)(transverseEnergy_ToSaveAndRead);
            transverseEnergyBosonW1 = (Float_t)(transverseEnergyBosonW1_ToSaveAndRead);
            transverseEnergyBosonW2 = (Float_t)(transverseEnergyBosonW2_ToSaveAndRead);
            transverseEnergyBosonZ1 = (Float_t)(transverseEnergyBosonZ1_ToSaveAndRead);
            transverseEnergyBosonZ2 = (Float_t)(transverseEnergyBosonZ2_ToSaveAndRead);
            cosThetaMissing = (Float_t)(cosThetaMissing_ToSaveAndRead);
            cosThetaMostEnergeticTrack = (Float_t)(cosThetaMostEnergeticTrack_ToSaveAndRead);
            y12 = (Float_t)(y12_ToSaveAndRead);
            y23 = (Float_t)(y23_ToSaveAndRead);
            y34 = (Float_t)(y34_ToSaveAndRead);
            y45 = (Float_t)(y45_ToSaveAndRead);
            y56 = (Float_t)(y56_ToSaveAndRead);
            y67 = (Float_t)(y67_ToSaveAndRead);
            invariantMassSystem = (Float_t)(invariantMassSystem_ToSaveAndRead);
            cosThetaStarWBosons = (Float_t)(cosThetaStarWBosons_ToSaveAndRead);
            cosThetaStarZBosons = (Float_t)(cosThetaStarZBosons_ToSaveAndRead);
            cosThetaStarWJet1 = (Float_t)(cosThetaStarWJets1_ToSaveAndRead);
            cosThetaStarWJet2 = (Float_t)(cosThetaStarWJets2_ToSaveAndRead);
            cosThetaStarZJet1 = (Float_t)(cosThetaStarZJets1_ToSaveAndRead);
            cosThetaStarZJet2 = (Float_t)(cosThetaStarZJets2_ToSaveAndRead);
            acolinearityJetsW1 = (Float_t)(acolinearityJetsW1_ToSaveAndRead);
            acolinearityJetsW2 = (Float_t)(acolinearityJetsW2_ToSaveAndRead);
            acolinearityJetsZ1 = (Float_t)(acolinearityJetsZ1_ToSaveAndRead);
            acolinearityJetsZ2 = (Float_t)(acolinearityJetsZ2_ToSaveAndRead);
            acolinearityBosonsW = (Float_t)(acolinearityBosonsW_ToSaveAndRead);
            acolinearityBosonsZ = (Float_t)(acolinearityBosonsZ_ToSaveAndRead);
            principleThrustValue = (Float_t)(principleThrustValue_ToSaveAndRead);
            majorThrustValue = (Float_t)(majorThrustValue_ToSaveAndRead);
            minorThrustValue = (Float_t)(minorThrustValue_ToSaveAndRead);
            sphericity = (Float_t)(sphericity_ToSaveAndRead);
            aplanarity = (Float_t)(aplanarity_ToSaveAndRead);

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

        TString filename = "RootFiles_Multivariant_" + pProcess->GetEventType() + "_" + this->NumberToString(pProcess->GetEnergy()) + "GeV_" + pProcess->GetRootSuffix() + "_AnalysisTag" + this->NumberToString(pProcess->GetAnalysisTag()) + ".root";
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

std::string TMVAClassificationApplication::GetGeneratorSerialNumber(std::string filename)
{
    std::size_t position = filename.find("GenN");
    std::string substring = filename.substr(position+5);
    std::size_t position2 = substring.find("_");
    std::string substring2 = substring.substr(0,position2);
    return substring2;
}

//=====================================================================

template <class T>
std::string TMVAClassificationApplication::NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
