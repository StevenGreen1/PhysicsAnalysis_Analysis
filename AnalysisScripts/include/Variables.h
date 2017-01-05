/**
 *  @file   AnalysisScripts/include/Variables.h
 * 
 *  @brief  Header file for the variables class.
 * 
 *  $Log: $
 */

#ifndef VARIABLES_H
#define VARIABLES_H 1

#include <iostream>
#include <limits>
#include <vector>

#include "TChain.h"
#include "TInterpreter.h"
#include "TTree.h"

namespace variables_namespace
{
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
}

using namespace variables_namespace;

class Variables
{
    public:
        /**
         *  @brief Constructor
         */
        Variables();

        /**
         *  @brief Destructor
         */
        ~Variables();

        /**
         *  @brief Set branch addresses for variables of interest
         *
         *  @param pTChain root tree to read variables from
         *  @param postMVA bool asking if loading TChain with post MVA data
         */
        void SetBranchAddresses(TChain *pTChain, bool postMVA);

        /**
         *  @brief Print to screen all bool, int, double and selected vector member variables
         */
        void Print();

        /**
         *  @brief Reset all variables for next event
         */
        void Clear();

        /**
         *  @brief Find flavour tagging information for combinations of W paired jets
         *
         *  @param bTagW11 b tag value for jet 1 of W boson 1
         *  @param bTagW12 b tag value for jet 2 of W boson 1
         *  @param bTagW21 b tag value for jet 1 of W boson 2
         *  @param bTagW22 b tag value for jet 2 of W boson 2
         *  @param cTagW11 b tag value for jet 1 of W boson 1
         *  @param cTagW12 b tag value for jet 2 of W boson 1
         *  @param cTagW21 b tag value for jet 1 of W boson 2
         *  @param cTagW22 b tag value for jet 2 of W boson 2
         */
        void SplitJetsForFlavourTaggingW(double &bTagW11, double &bTagW12, double &bTagW21, double &bTagW22, double &cTagW11, double &cTagW12, double &cTagW21, double &cTagW22) const;

        /**
         *  @brief Set b tag values for jets in W pairing
         *
         *  @param highestBTagW1 higest b tag value of jet in W boson 1
         *  @param lowestBTagW1 lowest b tag value of jet in W boson 1
         *  @param highestBTagW2 higest b tag value of jet in W boson 2
         *  @param lowestBTagW2 lowest b tag value of jet in W boson 2
         *  @param highestCTagW1 higest c tag value of jet in W boson 1
         *  @param lowestCTagW1 lowest c tag value of jet in W boson 1
         *  @param highestCTagW2 higest c tag value of jet in W boson 2
         *  @param lowestCTagW2 lowest c tag value of jet in W boson 2
         */
        void FlavourTagSettingW(double &highestBTagW1, double &lowestBTagW1, double &highestBTagW2, double &lowestBTagW2, double &highestCTagW1, double &lowestCTagW1, double &highestCTagW2, double &lowestCTagW2) const;

        /**
         *  @brief Find flavour tagging information for combinations of Z paired jets
         *
         *  @param bTagZ11 b tag value for jet 1 of Z boson 1
         *  @param bTagZ12 b tag value for jet 2 of Z boson 1
         *  @param bTagZ21 b tag value for jet 1 of Z boson 2
         *  @param bTagZ22 b tag value for jet 2 of Z boson 2
         *  @param cTagZ11 b tag value for jet 1 of Z boson 1
         *  @param cTagZ12 b tag value for jet 2 of Z boson 1
         *  @param cTagZ21 b tag value for jet 1 of Z boson 2
         *  @param cTagZ22 b tag value for jet 2 of Z boson 2
         */
        void SplitJetsForFlavourTaggingZ(double &bTagZ11, double &bTagZ12, double &bTagZ21, double &bTagZ22, double &cTagZ11, double &cTagZ12, double &cTagZ21, double &cTagZ22) const;

        /**
         *  @brief Set b tag values for jets in Z pairing
         *
         *  @param highestBTagZ1 higest b tag value of jet in Z boson 1
         *  @param lowestBTagZ1 lowest b tag value of jet in Z boson 1
         *  @param highestBTagZ2 higest b tag value of jet in Z boson 2
         *  @param lowestBTagZ2 lowest b tag value of jet in Z boson 2
         *  @param highestCTagZ1 higest c tag value of jet in Z boson 1
         *  @param lowestCTagZ1 lowest c tag value of jet in Z boson 1
         *  @param highestCTagZ2 higest c tag value of jet in Z boson 2
         *  @param lowestCTagZ2 lowest c tag value of jet in Z boson 2
         */
        void FlavourTagSettingZ(double &highestBTagZ1, double &lowestBTagZ1, double &highestBTagZ2, double &lowestBTagZ2, double &highestCTagZ1, double &lowestCTagZ1, double &highestCTagZ2, double &lowestCTagZ2) const;

        /**
         *  @brief Set jet energies for bosons in W pairing
         *
         *  @param jetEW11 jet energy of jet 1 in W boson 1
         *  @param jetEW12 jet energy of jet 2 in W boson 1
         *  @param jetEW21 jet energy of jet 1 in W boson 2
         *  @param jetEW22 jet energy of jet 2 in W boson 2
         */
        void SplitJetsForBosonEnergiesW(double &jetEW11, double &JetEW12, double &jetEW21, double &jetEW22) const;

        /**
         *  @brief Set jet energies for bosons in Z pairing
         *
         *  @param jetEZ11 jet energy of jet 1 in Z boson 1
         *  @param jetEZ12 jet energy of jet 2 in Z boson 1
         *  @param jetEZ21 jet energy of jet 1 in Z boson 2
         *  @param jetEZ22 jet energy of jet 2 in Z boson 2
         */
        void SplitJetsForBosonEnergiesZ(double &jetEZ11, double &JetEZ12, double &jetEZ21, double &jetEZ22) const;

        /**
         *  @brief Set
         *
         *  @param
         */
//        void Set(DoubleVector );

        /**
         *  @brief Get
         */
//        DoubleVector Get();

        bool             m_appropriateEvent;                             ///< Does event pass a series of cuts suggesting it has a vvqqqq final state? - JetAnalysis
        bool             m_isEventWW;                                    ///< Are the invariant masses of the jets close to the W boson mass? - JetAnalysis
        bool             m_isEventWWMC;                                  ///< Are the invariant masses of the quark pairs close to the W boson mass? - MCAnalysis
        bool             m_isEventZZ;                                    ///< Are the invariant masses of the jets close to the Z boson mass? - JetAnalysis
        bool             m_isEventZZMC;                                  ///< Are the invariant masses of the quark pairs close to the Z boson mass? - MCAnalysis
        int              m_nPfosBosonW1;                                 ///< Number of pfos in boson 1 in W pairing - JetAnalysis
        int              m_nPfosBosonW2;                                 ///< Number of pfos in boson 2 in W pairing - JetAnalysis
        int              m_nPfosBosonZ1;                                 ///< Number of pfos in boson 1 in Z pairing - JetAnalysis
        int              m_nPfosBosonZ2;                                 ///< Number of pfos in boson 2 in Z pairing - JetAnalysis
        int              m_nPfosBosonSyn1;                               ///< Number of pfos in boson 1 in Synergy pairing - JetAnalysis
        int              m_nPfosBosonSyn2;                               ///< Number of pfos in boson 2 in Synergy pairing - JetAnalysis
        int              m_combinationWJets1;                            ///< Combination of jets to form W bosons - JetAnalysis
        int              m_combinationWJets2;                            ///< Combination of jets to form W bosons - JetAnalysis
        int              m_combinationWJets3;                            ///< Combination of jets to form W bosons - JetAnalysis
        int              m_combinationWJets4;                            ///< Combination of jets to form W bosons - JetAnalysis
        int              m_combinationZJets1;                            ///< Combination of jets to form Z bosons - JetAnalysis
        int              m_combinationZJets2;                            ///< Combination of jets to form Z bosons - JetAnalysis
        int              m_combinationZJets3;                            ///< Combination of jets to form Z bosons - JetAnalysis
        int              m_combinationZJets4;                            ///< Combination of jets to form Z bosons - JetAnalysis
        int              m_combinationSynJets1;                          ///< Combination of jets to form Synergy bosons - JetAnalysis
        int              m_combinationSynJets2;                          ///< Combination of jets to form Synergy bosons - JetAnalysis
        int              m_combinationSynJets3;                          ///< Combination of jets to form Synergy bosons - JetAnalysis
        int              m_combinationSynJets4;                          ///< Combination of jets to form Synergy bosons - JetAnalysis
        int              m_combinationWQuarks1;                          ///< Combination of quarks to form W bosons - JetAnalysis
        int              m_combinationWQuarks2;                          ///< Combination of quarks to form W bosons - JetAnalysis
        int              m_combinationWQuarks3;                          ///< Combination of quarks to form W bosons - JetAnalysis
        int              m_combinationWQuarks4;                          ///< Combination of quarks to form W bosons - JetAnalysis
        int              m_combinationZQuarks1;                          ///< Combination of quarks to form Z bosons - JetAnalysis
        int              m_combinationZQuarks2;                          ///< Combination of quarks to form Z bosons - JetAnalysis
        int              m_combinationZQuarks3;                          ///< Combination of quarks to form Z bosons - JetAnalysis
        int              m_combinationZQuarks4;                          ///< Combination of quarks to form Z bosons - JetAnalysis
        int              m_combinationSynQuarks1;                        ///< Combination of quarks to form Synergy bosons - JetAnalysis
        int              m_combinationSynQuarks2;                        ///< Combination of quarks to form Synergy bosons - JetAnalysis
        int              m_combinationSynQuarks3;                        ///< Combination of quarks to form Synergy bosons - JetAnalysis
        int              m_combinationSynQuarks4;                        ///< Combination of quarks to form Synergy bosons - JetAnalysis
        int              m_nParticlesJets1;                              ///< Number of particles in reconstructed jet - JetAnalysis
        int              m_nParticlesJets2;                              ///< Number of particles in reconstructed jet - JetAnalysis
        int              m_nParticlesJets3;                              ///< Number of particles in reconstructed jet - JetAnalysis
        int              m_nParticlesJets4;                              ///< Number of particles in reconstructed jet - JetAnalysis
        int              m_nChargedParticlesJets1;                       ///< Number of charged particles in reconstructed jet - JetAnalysis
        int              m_nChargedParticlesJets2;                       ///< Number of charged particles in reconstructed jet - JetAnalysis
        int              m_nChargedParticlesJets3;                       ///< Number of charged particles in reconstructed jet - JetAnalysis
        int              m_nChargedParticlesJets4;                       ///< Number of charged particles in reconstructed jet - JetAnalysis
        int              m_highestEnergyPfoPDG;                          ///< PDG of highest energy PFO - RawPfoAnalysis
        int              m_nIsolatedLeptons;                             ///< Number of isolated leptons identified in isolated lepton finder - IsolatedLeptonPfoAnalysis
        int              m_highestEnergyIsolatedLeptonPDG;               ///< PDG of highest energy PFO from isolated lepton finder - IsolatedLeptonPfoAnalysis
        int              m_secondHighestEnergyIsolatedLeptonPDG;         ///< PDG of second highest energy PFO from isolated lepton finder - IsolatedLeptonPfoAnalysis
        int              m_globalEventNumber;                            ///< Global event number for event
        double           m_transverseMomentum;                           ///< Transverse momentum of reconstructed system - JetAnalysis
        double           m_transverseMomentumMC;                         ///< Transverse momentum of quark system - MCAnalysis
        double           m_transverseEnergy;                             ///< Transverse energy of reconstructed system - JetAnalysis
        double           m_transverseEnergyMC;                           ///< Transverse energy of quark system - MCAnalysis
        double           m_energyBosonW1;                                ///< Energy of boson 1 in W pairing - JetAnalysis
        double           m_energyBosonW2;                                ///< Energy of boson 2 in W pairing - JetAnalysis
        double           m_energyBosonZ1;                                ///< Energy of boson 1 in Z pairing - JetAnalysis
        double           m_energyBosonZ2;                                ///< Energy of boson 2 in Z pairing - JetAnalysis
        double           m_energyBosonSyn1;                              ///< Energy of boson 1 in Synergy pairing - JetAnalysis
        double           m_energyBosonSyn2;                              ///< Energy of boson 2 in Synergy pairing - JetAnalysis
        double           m_momentumBosonW1;                              ///< Momentum of boson 1 in W pairing - JetAnalysis
        double           m_momentumBosonW2;                              ///< Momentum of boson 2 in W pairing - JetAnalysis
        double           m_momentumBosonZ1;                              ///< Momentum of boson 1 in Z pairing - JetAnalysis
        double           m_momentumBosonZ2;                              ///< Momentum of boson 2 in Z pairing - JetAnalysis
        double           m_momentumBosonSyn1;                            ///< Momentum of boson 1 in Synergy pairing - JetAnalysis
        double           m_momentumBosonSyn2;                            ///< Momentum of boson 2 in Synergy pairing - JetAnalysis
        double           m_transverseMomentumBosonW1;                    ///< Transverse momentum of boson 1 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonW2;                    ///< Transverse momentum of boson 2 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonZ1;                    ///< Transverse momentum of boson 1 in Z pairing - JetAnalysis
        double           m_transverseMomentumBosonZ2;                    ///< Transverse momentum of boson 2 in Z pairing - JetAnalysis
        double           m_transverseMomentumBosonSyn1;                  ///< Transverse momentum of boson 1 in Synergy pairing - JetAnalysis
        double           m_transverseMomentumBosonSyn2;                  ///< Transverse momentum of boson 2 in Synergy pairing - JetAnalysis
        double           m_cosThetaBosonW1;                              ///< Cosine theta of boson 1 in W pairing - JetAnalysis
        double           m_cosThetaBosonW2;                              ///< Cosine theta of boson 2 in W pairing - JetAnalysis
        double           m_cosThetaBosonZ1;                              ///< Cosine theta of boson 1 in Z pairing - JetAnalysis
        double           m_cosThetaBosonZ2;                              ///< Cosine theta of boson 2 in Z pairing - JetAnalysis
        double           m_cosThetaBosonSyn1;                            ///< Cosine theta of boson 1 in Synergy pairing - JetAnalysis
        double           m_cosThetaBosonSyn2;                            ///< Cosine theta of boson 2 in Synergy pairing - JetAnalysis
        double           m_transverseEnergyBosonW1;                      ///< Transverse energy of boson 1 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonW2;                      ///< Transverse energy of boson 2 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonZ1;                      ///< Transverse energy of boson 1 in Z pairing - JetAnalysis
        double           m_transverseEnergyBosonZ2;                      ///< Transverse energy of boson 2 in Z pairing - JetAnalysis
        double           m_transverseEnergyBosonSyn1;                    ///< Transverse energy of boson 1 in Synergy pairing - JetAnalysis
        double           m_transverseEnergyBosonSyn2;                    ///< Transverse energy of boson 2 in Synergy pairing - JetAnalysis
        double           m_cosThetaMissing;                              ///< Cosine theta of missing energy - JetAnalysis
        double           m_cosThetaMissingMC;                            ///< Cosine theta of neutrino energy - MCAnalysis
        double           m_cosThetaMostEnergeticTrack;                   ///< Cosine theta of highest energy track in system - JetAnalysis
        double           m_recoilMass;                                   ///< Recoil mass of reconstructed system - JetAnalysis
        double           m_recoilMassMC;                                 ///< Recoil mass of quark system - MCAnalysis
        double           m_energyAroundMostEnergeticPfo;                 ///< Energy in cone around most energetic pfo - JetAnalysis
        double           m_y12;                                          ///< Jet grouping parameter
        double           m_y23;                                          ///< Jet grouping parameter
        double           m_y34;                                          ///< Jet grouping parameter
        double           m_y45;                                          ///< Jet grouping parameter
        double           m_y56;                                          ///< Jet grouping parameter
        double           m_y67;                                          ///< Jet grouping parameter
        double           m_invariantMassSystem;                          ///< Invariant mass of the jet system - JetAnalysis
        double           m_invariantMassSystemMC;                        ///< Invariant mass of the quark system - MCAnalysis
        double           m_cosThetaStarWBosons;                          ///< Cosine of the polar angle of the bosons in the reference frame of the WW boson pairs - JetAnalysis
        double           m_cosThetaStarWBosonsMC;                        ///< Cosine of the polar angle of the bosons in the reference frame of the WW boson pairs - MCAnalysis
        double           m_cosThetaStarZBosons;                          ///< Cosine of the polar angle of the bosons in the reference frame of the ZZ boson pairs - JetAnalysis
        double           m_cosThetaStarZBosonsMC;                        ///< Cosine of the polar angle of the bosons in the reference frame of the ZZ boson pairs - MCAnalysis
        double           m_cosThetaStarSynBosons;                        ///< Cosine of the polar angle of the bosons in the reference frame of the Synergy boson pairs - JetAnalysis
        double           m_cosThetaStarSynBosonsMC;                      ///< Cosine of the polar angle of the bosons in the reference frame of the Synergy boson pairs - MCAnalysis
        double           m_acolinearityJetsW1;                           ///< Acolinearity of the jets from boson 1 in W pairing - JetAnalysis
        double           m_acolinearityJetsW2;                           ///< Acolinearity of the jets from boson 2 in W pairing - JetAnalysis
        double           m_acolinearityJetsZ1;                           ///< Acolinearity of the jets from boson 1 in Z pairing - JetAnalysis
        double           m_acolinearityJetsZ2;                           ///< Acolinearity of the jets from boson 2 in Z pairing - JetAnalysis
        double           m_acolinearityJetsSyn1;                         ///< Acolinearity of the jets from boson 1 in Z pairing - JetAnalysis
        double           m_acolinearityJetsSyn2;                         ///< Acolinearity of the jets from boson 2 in Z pairing - JetAnalysis
        double           m_acolinearityBosonsW;                          ///< Acolinearity of the bosons in W pairing - SelectionProcessor
        double           m_acolinearityBosonsZ;                          ///< Acolinearity of the bosons in Z pairing - SelectionProcessor
        double           m_acolinearityBosonsSyn;                        ///< Acolinearity of the bosons in Synergy pairing - SelectionProcessor
        double           m_principleThrustValue;                         ///< Principle thrust value from ThrustReconstruction processor- SelectionProcessor
        double           m_majorThrustValue;                             ///< Major thrust value from ThrustReconstruction processor- SelectionProcessor
        double           m_minorThrustValue;                             ///< Minor thrust value from ThrustReconstruction processor - SelectionProcessor
        double           m_xThrustAxis;                                  ///< X Thrust axis value from ThrustReconstruction processor - SelectionProcessor
        double           m_yThrustAxis;                                  ///< Y Thrust axis value from ThrustReconstruction processor  - SelectionProcessor
        double           m_zThrustAxis;                                  ///< Z Thrust axis value from ThrustReconstruction processor - SelectionProcessor
        double           m_sphericity;                                   ///< Sphericity from Sphere processor - SelectionProcessor
        double           m_aplanarity;                                   ///< Aplnarity from Sphere processor - SelectionProcessor
        double           m_highestEnergyElectronE;                       ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyElectronP;                       ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyElectronPt;                      ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyElectronCosTheta;                ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonE;                           ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonP;                           ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonPt;                          ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonCosTheta;                    ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonE;                         ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonP;                         ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonPt;                        ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonCosTheta;                  ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoE;                            ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoP;                            ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoPt;                           ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoCosTheta;                     ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyIsolatedLeptonE;                 ///< Energy of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_highestEnergyIsolatedLeptonP;                 ///< Magnitude of momentum of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_highestEnergyIsolatedLeptonPt;                ///< Transverse momentum of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_highestEnergyIsolatedLeptonCosTheta;          ///< Consine theta of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonE;           ///< Energy of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonP;           ///< Magnitude of momentum of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonPt;          ///< Transverse momentum of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonCosTheta;    ///< Consine theta of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_invariantMassWBosons1;                        ///< Invariant mass of first and second pair of W paired jets - JetAnalysis
        double           m_invariantMassWBosons2;                        ///< Invariant mass of first and second pair of W paired jets - JetAnalysis
        double           m_invariantMassZBosons1;                        ///< Invariant mass of first and second pair of Z paired jets - JetAnalysis
        double           m_invariantMassZBosons2;                        ///< Invariant mass of first and second pair of Z paired jets - JetAnalysis
        double           m_invariantMassSynBosons1;                      ///< Invariant mass of first and second pair of Synergy paired jets - JetAnalysis
        double           m_invariantMassSynBosons2;                      ///< Invariant mass of first and second pair of Synergy paired jets - JetAnalysis
        double           m_invariantMassWBosonsMC1;                      ///< Invariant mass of first and second pair of W paired quarks - MCAnalysis
        double           m_invariantMassWBosonsMC2;                      ///< Invariant mass of first and second pair of W paired quarks - MCAnalysis
        double           m_invariantMassZBosonsMC1;                      ///< Invariant mass of first and second pair of Z paired quarks - MCAnalysis
        double           m_invariantMassZBosonsMC2;                      ///< Invariant mass of first and second pair of Z paired quarks - MCAnalysis
        double           m_invariantMassSynBosonsMC1;                    ///< Invariant mass of first and second pair of Synergy paired quarks - MCAnalysis
        double           m_invariantMassSynBosonsMC2;                    ///< Invariant mass of first and second pair of Synergy paired quarks - MCAnalysis
        double           m_invariantMassBoson1Pairing0123;               ///< Invariant mass of boson 1 with pairing 01 and 23 of jets - JetAnalysis
        double           m_invariantMassBoson2Pairing0123;               ///< Invariant mass of boson 2 with pairing 01 and 23 of jets - JetAnalysis
        double           m_invariantMassBoson1Pairing0213;               ///< Invariant mass of boson 1 with pairing 02 and 13 of jets - JetAnalysis
        double           m_invariantMassBoson2Pairing0213;               ///< Invariant mass of boson 2 with pairing 02 and 13 of jets - JetAnalysis
        double           m_invariantMassBoson1Pairing0312;               ///< Invariant mass of boson 1 with pairing 03 and 12 of jets - JetAnalysis
        double           m_invariantMassBoson2Pairing0312;               ///< Invariant mass of boson 2 with pairing 03 and 12 of jets - JetAnalysis
        double           m_mcInvariantMassBoson1Pairing0123;             ///< Invariant mass of boson 1 with pairing 01 and 23 of quarks - MCAnalysis
        double           m_mcInvariantMassBoson2Pairing0123;             ///< Invariant mass of boson 2 with pairing 01 and 23 of quarks - MCAnalysis
        double           m_mcInvariantMassBoson1Pairing0213;             ///< Invariant mass of boson 1 with pairing 02 and 13 of quarks - MCAnalysis
        double           m_mcInvariantMassBoson2Pairing0213;             ///< Invariant mass of boson 2 with pairing 02 and 13 of quarks - MCAnalysis
        double           m_mcInvariantMassBoson1Pairing0312;             ///< Invariant mass of boson 1 with pairing 03 and 12 of quarks - MCAnalysis
        double           m_mcInvariantMassBoson2Pairing0312;             ///< Invariant mass of boson 2 with pairing 03 and 12 of quarks - MCAnalysis
        double           m_energyJets1;                                  ///< Energy of reconstructed jets - JetAnalysis
        double           m_energyJets2;                                  ///< Energy of reconstructed jets - JetAnalysis
        double           m_energyJets3;                                  ///< Energy of reconstructed jets - JetAnalysis
        double           m_energyJets4;                                  ///< Energy of reconstructed jets - JetAnalysis
        double           m_momentumJets1;                                ///< Momentum of reconstructed jets - JetAnalysis
        double           m_momentumJets2;                                ///< Momentum of reconstructed jets - JetAnalysis
        double           m_momentumJets3;                                ///< Momentum of reconstructed jets - JetAnalysis
        double           m_momentumJets4;                                ///< Momentum of reconstructed jets - JetAnalysis
        double           m_transverseMomentumJets1;                      ///< Transverse momentum of reconstructed jets - JetAnalysis
        double           m_transverseMomentumJets2;                      ///< Transverse momentum of reconstructed jets - JetAnalysis
        double           m_transverseMomentumJets3;                      ///< Transverse momentum of reconstructed jets - JetAnalysis
        double           m_transverseMomentumJets4;                      ///< Transverse momentum of reconstructed jets - JetAnalysis
        double           m_cosThetaJets1;                                ///< Cosine theta of reconstructed jets - JetAnalysis
        double           m_cosThetaJets2;                                ///< Cosine theta of reconstructed jets - JetAnalysis
        double           m_cosThetaJets3;                                ///< Cosine theta of reconstructed jets - JetAnalysis
        double           m_cosThetaJets4;                                ///< Cosine theta of reconstructed jets - JetAnalysis
        double           m_cosThetaStarWJets1;                           ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons - JetAnalysis
        double           m_cosThetaStarWJets2;                           ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons - JetAnalysis
        double           m_cosThetaStarZJets1;                           ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons - JetAnalysis
        double           m_cosThetaStarZJets2;                           ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons - JetAnalysis
        double           m_cosThetaStarSynJets1;                         ///< Cosine of the polar angle of the q jets in the reference frome of the Synergy bosons - JetAnalysis
        double           m_cosThetaStarSynJets2;                         ///< Cosine of the polar angle of the q jets in the reference frome of the Synergy bosons - JetAnalysis
        double           m_bTagForJets1;                                 ///< B tag value for the jets in the event - JetAnalysis
        double           m_bTagForJets2;                                 ///< B tag value for the jets in the event - JetAnalysis
        double           m_bTagForJets3;                                 ///< B tag value for the jets in the event - JetAnalysis
        double           m_bTagForJets4;                                 ///< B tag value for the jets in the event - JetAnalysis
        double           m_cTagForJets1;                                 ///< C tag value for the jets in the event - JetAnalysis
        double           m_cTagForJets2;                                 ///< C tag value for the jets in the event - JetAnalysis
        double           m_cTagForJets3;                                 ///< C tag value for the jets in the event - JetAnalysis
        double           m_cTagForJets4;                                 ///< C tag value for the jets in the event - JetAnalysis
        double           m_maxBTagForBosonW1;                            ///< Max B tag for boson 1 in W pairing - JetAnalysis
        double           m_minBTagForBosonW1;                            ///< Min B tag for boson 1 in W pairing - JetAnalysis
        double           m_maxBTagForBosonW2;                            ///< Max B tag for boson 2 in W pairing - JetAnalysis
        double           m_minBTagForBosonW2;                            ///< Min B tag for boson 2 in W pairing - JetAnalysis
        double           m_maxCTagForBosonW1;                            ///< Max C tag for boson 1 in W pairing - JetAnalysis
        double           m_minCTagForBosonW1;                            ///< Min C tag for boson 1 in W pairing - JetAnalysis
        double           m_maxCTagForBosonW2;                            ///< Max C tag for boson 2 in W pairing - JetAnalysis
        double           m_minCTagForBosonW2;                            ///< Min C tag for boson 2 in W pairing - JetAnalysis
        double           m_maxBTagForBosonZ1;                            ///< Max B tag for boson 1 in Z pairing - JetAnalysis
        double           m_minBTagForBosonZ1;                            ///< Min B tag for boson 1 in Z pairing - JetAnalysis
        double           m_maxBTagForBosonZ2;                            ///< Max B tag for boson 2 in Z pairing - JetAnalysis
        double           m_minBTagForBosonZ2;                            ///< Min B tag for boson 2 in Z pairing - JetAnalysis
        double           m_maxCTagForBosonZ1;                            ///< Max C tag for boson 1 in Z pairing - JetAnalysis
        double           m_minCTagForBosonZ1;                            ///< Min C tag for boson 1 in Z pairing - JetAnalysis
        double           m_maxCTagForBosonZ2;                            ///< Max C tag for boson 2 in Z pairing - JetAnalysis
        double           m_minCTagForBosonZ2;                            ///< Min C tag for boson 2 in Z pairing - JetAnalysis
        double           m_maxBTagForBosonSyn1;                          ///< Max B tag for boson 1 in Synergy pairing - JetAnalysis
        double           m_minBTagForBosonSyn1;                          ///< Min B tag for boson 1 in Synergy pairing - JetAnalysis
        double           m_maxBTagForBosonSyn2;                          ///< Max B tag for boson 2 in Synergy pairing - JetAnalysis
        double           m_minBTagForBosonSyn2;                          ///< Min B tag for boson 2 in Synergy pairing - JetAnalysis
        double           m_maxCTagForBosonSyn1;                          ///< Max C tag for boson 1 in Synergy pairing - JetAnalysis
        double           m_minCTagForBosonSyn1;                          ///< Min C tag for boson 1 in Synergy pairing - JetAnalysis
        double           m_maxCTagForBosonSyn2;                          ///< Max C tag for boson 2 in Synergy pairing - JetAnalysis
        double           m_minCTagForBosonSyn2;                          ///< Min C tag for boson 2 in Synergy pairing - JetAnalysis
        double           m_neutrinoEnergy1;                              ///< Neutrino 1 energy for vvqqqq final state - MCAnalysis
        double           m_neutrinoPx1;                                  ///< Neutrino 1 px for vvqqqq final state - MCAnalysis
        double           m_neutrinoPy1;                                  ///< Neutrino 1 py for vvqqqq final state - MCAnalysis
        double           m_neutrinoPz1;                                  ///< Neutrino 1 pz for vvqqqq final state - MCAnalysis
        double           m_neutrinoEnergy2;                              ///< Neutrino 2 energy for vvqqqq final state - MCAnalysis
        double           m_neutrinoPx2;                                  ///< Neutrino 2 px for vvqqqq final state - MCAnalysis
        double           m_neutrinoPy2;                                  ///< Neutrino 2 py for vvqqqq final state - MCAnalysis
        double           m_neutrinoPz2;                                  ///< Neutrino 2 pz for vvqqqq final state - MCAnalysis
        double           m_quarkEnergy1;                                 ///< Quark 1 energy for vvqqqq final state - MCAnalysis
        double           m_quarkPx1;                                     ///< Quark 1 px for vvqqqq final state - MCAnalysis
        double           m_quarkPy1;                                     ///< Quark 1 py for vvqqqq final state - MCAnalysis
        double           m_quarkPz1;                                     ///< Quark 1 pz for vvqqqq final state - MCAnalysis
        double           m_quarkEnergy2;                                 ///< Quark 2 energy for vvqqqq final state - MCAnalysis
        double           m_quarkPx2;                                     ///< Quark 2 px for vvqqqq final state - MCAnalysis
        double           m_quarkPy2;                                     ///< Quark 2 py for vvqqqq final state - MCAnalysis
        double           m_quarkPz2;                                     ///< Quark 2 pz for vvqqqq final state - MCAnalysis
        double           m_quarkEnergy3;                                 ///< Quark 3 energy for vvqqqq final state - MCAnalysis
        double           m_quarkPx3;                                     ///< Quark 3 px for vvqqqq final state - MCAnalysis
        double           m_quarkPy3;                                     ///< Quark 3 py for vvqqqq final state - MCAnalysis
        double           m_quarkPz3;                                     ///< Quark 3 pz for vvqqqq final state - MCAnalysis
        double           m_quarkEnergy4;                                 ///< Quark 4 energy for vvqqqq final state - MCAnalysis
        double           m_quarkPx4;                                     ///< Quark 4 px for vvqqqq final state - MCAnalysis
        double           m_quarkPy4;                                     ///< Quark 4 py for vvqqqq final state - MCAnalysis
        double           m_quarkPz4;                                     ///< Quark 4 pz for vvqqqq final state - MCAnalysis
        double           m_cheatedInvariantMass1;                        ///< Boson 1 invariant mass cheated pairing of jets - JetAnalysis
        double           m_cheatedInvariantMass2;                        ///< Boson 2 invariant mass cheated pairing of jets - JetAnalysis
        double           m_cheatedMCInvariantMass1;                      ///< Boson 1 invariant mass cheated pairing of quarks - MCAnalysis
        double           m_cheatedMCInvariantMass2;                      ///< Boson 2 invariant mass cheated pairing of quarks - MCAnalysis
        double           m_bdt;                                          ///< BDT response for event
    private:
};

#endif // #ifndef VARIABLES_H
