#ifndef AliAnalysisTaskCVEPIDCME_cxx
#define AliAnalysisTaskCVEPIDCME_cxx
#include <vector>
#include <map>
#include <unordered_map>
#include "AliAnalysisTaskSE.h"
#include "AliAODTrack.h"
#include "AliAODv0.h"
#include "AliEventCuts.h"
#include "AliPIDResponse.h"
#include "AliMultSelection.h"
#include "TFile.h"
#include "TList.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "THnSparse.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TProfile3D.h"


class AliAnalysisTaskCVEPIDCME : public AliAnalysisTaskSE
{
 public:
  AliAnalysisTaskCVEPIDCME();
  AliAnalysisTaskCVEPIDCME(const char* name);
  virtual ~AliAnalysisTaskCVEPIDCME();

  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t* option);
  virtual void Terminate(Option_t*);

  // Switch
  void IfDebug(bool bDebug) { this->fDebug = bDebug; }
  void IfUseTPCPlane(bool bUseTPCPlane) { this->isUseTPCPlane = bUseTPCPlane; }
  void IfUseVZEROPlane(bool bUseVZEROPlane) { this->isUseVZEROPlane = bUseVZEROPlane; }
  void IfUseZDCPlane(bool bUseZDCPlane) { this->isUseZDCPlane = bUseZDCPlane; }
  void IfDoNUE(bool bDoNUE) { this->isDoNUE = bDoNUE; }
  void IfDoNUA(bool bDoNUA) { this->isDoNUA = bDoNUA; }
  void IfV0DaughterUseTOF(bool bV0DaughterUseTOF) { this->isV0DaughterUseTOF = bV0DaughterUseTOF; }
  void IfQATPC(bool bQATPC) { this->isQATPC = bQATPC; }
  void IfQAVZERO(bool bQAVZERO) { this->isQAVZERO = bQAVZERO; }
  void IfQAZDC(bool bQAZDC) { this->isQAZDC = bQAZDC; }
  void IfCalculatePIDFlow(bool bCalculatePIDFlow) { this->isCalculatePIDFlow = bCalculatePIDFlow; }
  void IfCalculateDeltaGamma(bool bCalculateDeltaGamma) { this->isCalculateDeltaGamma = bCalculateDeltaGamma; }
  void IfCalculateDiffResult(bool bCalculateDiffResult) { this->isCalculateDiffResult = bCalculateDiffResult; }
  void IfCalculateDeltaPhiSumPhi(bool bCalculateDeltaPhiSumPhi) { this->isCalculateDeltaPhiSumPhi = bCalculateDeltaPhiSumPhi; }
  void IfCalculateLambdaLambda(bool bCalculateLambdaLambda) {this->isCalculateLambdaLambda = bCalculateLambdaLambda; }
  void IfCalculateProtonProton(bool bCalculateProtonProton) {this->isCalculateProtonProton = bCalculateProtonProton; }
  void IfCalculateHadronHadron(bool bCalculateHadronHadron) {this->isCalculateHadronHadron = bCalculateHadronHadron; }
  void IfNarrowDcaCuts768(bool bNarrowDcaCuts768) { this->isNarrowDcaCuts768 = bNarrowDcaCuts768; }
  void IfStrictestProtonCut(bool bStrictestProtonCut) { this->isStrictestProtonCut = bStrictestProtonCut; }
  void IfCheckDaughterProtonPassAllCuts(bool bCheckDaughterProtonPassAllCuts) { this->isCheckDaughterProtonPassAllCuts = bCheckDaughterProtonPassAllCuts; }
  void IfUsePionRejection(bool bUsePionRejection) { this->isUsePionRejection = bUsePionRejection; }
  // read in
  void SetListForNUE(TList* flist) { this->fListNUE = (TList*)flist->Clone(); }
  void SetListForNUA(TList* flist) { this->fListNUA = (TList*)flist->Clone(); }
  void SetListForVZEROCalib(TList* flist) { this->fListVZEROCalib = (TList*)flist->Clone(); }
  void SetListForZDCCalib(TList* flist) { this->fListZDCCalib = (TList*)flist->Clone(); }

  // Global
  void SetTrigger(TString trigger) { this->fTrigger = trigger; }
  void SetPeriod(TString period) { this->fPeriod = period; }
  // Event
  void SetVzCut(double vzCut) { this->fVzCut = vzCut; }
  void SetCentCut(float centDiffCut) { this->fCentDiffCut = centDiffCut; }
  // Plane
  void SetPlanePtMin(float planePtMin) { this->fPlanePtMin = planePtMin; }
  void SetPlanePtMax(float planePtMax) { this->fPlanePtMax = planePtMax; }
  void SetPlaneEtaGapPos(float etaGapPos) { this->fEtaGapPos = etaGapPos; }
  void SetPlaneEtaGapNeg(float etaGapNeg) { this->fEtaGapNeg = etaGapNeg; }
  // Track
  void SetFilterBit(int filterBit) { this->fFilterBit = filterBit; }
  void SetNclsCut(int nclsCut) { this->fNclsCut = nclsCut; }
  void SetChi2Max(float chi2Max) { this->fChi2Max = chi2Max; }
  void SetChi2Min(float chi2Min) { this->fChi2Min = chi2Min; }
  void SetDCAcutXY(float dcaCutxy) { this->fDcaCutXY = dcaCutxy; }
  void SetDCAcutZ(float dcaCutz) { this->fDcaCutZ = dcaCutz; }
  void SetPtMin(float ptMin) { this->fPtMin = ptMin; }
  void SetPtMax(float ptMax) { this->fPtMax = ptMax; }
  void SetEtaCut(float etaCut) { this->fEtaCut = etaCut; }
  void SetDedxCut(float dedxCut) { this->fDedxCut = dedxCut; }
  void SetProtonPtMin(double protonPtMin) { this->fProtonPtMin = protonPtMin; }
  void SetProtonPtMax(double protonPtMax) { this->fProtonPtMax = protonPtMax; }
  void SetAntiProtonPtMin(double protonPtMin) { this->fProtonPtMin = protonPtMin; }
  void SetAntiProtonPtMax(double protonPtMax) { this->fProtonPtMax = protonPtMax; }
  // PID
  void SetNSigmaTPCCut(double nSigmaTPC) { this->fNSigmaTPCCut = nSigmaTPC; }
  void SetNSigmaTOFCut(double nSigmaTOF) { this->fNSigmaTOFCut = nSigmaTOF; }
  // V0
  void SetV0PtMin(double v0PtMin) { this->fV0PtMin = v0PtMin; }
  void SetV0CPAMin(double v0CPAMin) { this->fV0CPAMin = v0CPAMin; }
  void SetV0RapidityMax(double v0RapidityMax) { this->fV0RapidityMax = v0RapidityMax; }
  void SetV0DecayLengthMax(double v0DecayLengthMax) { this->fV0DecayLengthMax = v0DecayLengthMax; }
  void SetV0DecayLengthMin(double v0DecayLengthMin) { this->fV0DecayLengthMin = v0DecayLengthMin; }
  void SetV0DCAToPrimVtxMax(double v0DCAToPrimVtxMax) { this->fV0DCAToPrimVtxMax = v0DCAToPrimVtxMax; }
  void SetV0DcaBetweenDaughtersMax(double v0DcaBetweenDaughtersMax) { this->fV0DcaBetweenDaughtersMax = v0DcaBetweenDaughtersMax; }
  // V0 Daughter Cut
  void SetDaughtersPtMax(double daughtersPtMax) { this->fDaughtersPtMax = daughtersPtMax; }
  void SetDaughtersEtaMax(double daughtersEtaMax) { this->fDaughtersEtaMax = daughtersEtaMax; }
  void SetDaughtersTPCNclsMin(double daughtersTPCNclsMin) { this->fDaughtersTPCNclsMin = daughtersTPCNclsMin; }
  void SetDaughtersDCAToPrimVtxMin(double daughtersDCAToPrimVtxMin) { this->fDaughtersDCAToPrimVtxMin = daughtersDCAToPrimVtxMin; }
  void SetPosProtonTPCNsigma(float V0PosProtonTPCNsigma) { this->fV0PosProtonTPCNsigma = V0PosProtonTPCNsigma; }
  void SetNegPionTPCNsigma(float V0NegPionTPCNsigma) { this->fV0NegPionTPCNsigma = V0NegPionTPCNsigma; }
  void SetNegProtonTPCNsigma(float V0NegProtonTPCNsigma) { this->fV0NegProtonTPCNsigma = V0NegProtonTPCNsigma; }
  void SetPosPionTPCNsigma(float V0PosPionTPCNsigma) { this->fV0PosPionTPCNsigma = V0PosPionTPCNsigma; }
  void SetPosProtonTOFNsigma(float V0PosProtonTOFNsigma) { this->fV0PosProtonTOFNsigma = V0PosProtonTOFNsigma; }
  void SetNegPionTOFNsigma(float V0NegPionTOFNsigma) { this->fV0NegPionTOFNsigma = V0NegPionTOFNsigma; }
  void SetNegProtonTOFNsigma(float V0NegProtonTOFNsigma) { this->fV0NegProtonTOFNsigma = V0NegProtonTOFNsigma; }
  void SetPosPionTOFNsigma(float V0PosPionTOFNsigma) { this->fV0PosPionTOFNsigma = V0PosPionTOFNsigma; }
  // Lambda Mass Cut
  void SetLambdaMassLeftCut(double lambdaMassRightCut) { this->fLambdaMassRightCut = lambdaMassRightCut; }
  void SetLambdaMassRightCut(double lambdaMassLeftCut) { this->fLambdaMassLeftCut = lambdaMassLeftCut; }
  void SetAntiLambdaMassLeftCut(double antiLambdaMassRightCut) { this->fAntiLambdaMassRightCut = antiLambdaMassRightCut; }
  void SetAntiLambdaMassRightCut(double antiLambdaMassLeftCut) { this->fAntiLambdaMassLeftCut = antiLambdaMassLeftCut; }

 private:
  ////////////////////////
  // Procedural function
  ////////////////////////
  bool GetTPCPlane();
  bool GetVZEROPlane();
  bool GetZDCPlane();
  bool GetZDCPlaneLsFit();
  void ResetVectors();
  bool LoopTracks();
  bool LoopV0s();
  bool PairV0Trk();
  bool PairV0V0();
  bool PairTrkTrk();

  ////////////////////////
  // Functional function
  ////////////////////////
  // Read in
  bool LoadCalibHistForThisRun(); //deal with all the readin
  // Pile-up
  bool RejectEvtMultComp();
  bool RejectEvtTFFit();
  bool RejectEvtTPCITSfb32TOF();
  bool AODPileupCheck();
  bool PileUpMultiVertex();
  bool RemovalForRun1();
  double GetWDist(const AliVVertex* v0, const AliVVertex* v1);
  // Track
  bool AcceptAODTrack(AliAODTrack* track);
  bool CheckPIDofParticle(AliAODTrack* ftrack, int pidToCheck);
  double GetNUECor(int charge, double pt);
  double GetNUACor(int charge, double phi, double eta, double vz);
  // V0
  bool IsGoodV0(AliAODv0* aodV0);
  bool IsGoodDaughterTrack(const AliAODTrack* track);
  int GetLambdaCode(const AliAODTrack* pTrack, const AliAODTrack* ntrack);
  // Plane
  double GetTPCPlaneNoAutoCorr(int id_0, int id_1, int id_2, int id_3);
  inline double GetEventPlane(double qx, double qy, double harmonic);
  // Range phi
  inline double RangeDPhi(double dphi);
  // Get DCA
  bool GetDCA(double &dcaxy, double &dcaz, AliAODTrack* track);

  //////////////////////
  // Switch           //
  //////////////////////
  bool isUseTPCPlane;
  bool isUseVZEROPlane;
  bool isUseZDCPlane;
  bool isDoNUE;
  bool isDoNUA;
  bool isV0DaughterUseTOF;
  bool isQATPC;
  bool isQAVZERO; // flag for V0 qn QA
  bool isQAZDC;
  bool isCalculatePIDFlow;        // if fill PID Flow
  bool isCalculateDeltaGamma;     // if fill γ and δ
  bool isCalculateDiffResult;     // if fill Diff Reslut
  bool isCalculateDeltaPhiSumPhi; // if fill C(delta_phi)
  bool isCalculateLambdaLambda;
  bool isCalculateProtonProton;
  bool isCalculateHadronHadron;
  bool isNarrowDcaCuts768;
  bool isStrictestProtonCut;
  bool isCheckDaughterProtonPassAllCuts;
  bool isUsePionRejection;

  //////////////////////
  // Cuts and options //
  //////////////////////
  // Global
  TString fTrigger; //
  TString fPeriod;  // period
  // Event
  double fVzCut;      // vz cut
  float fCentDiffCut; // centrality restriction for V0M and TRK
  // Plane
  float fPlanePtMin;
  float fPlanePtMax;
  float fEtaGapPos; // value for the Eta Gap Pos
  float fEtaGapNeg;
  // Track
  int fFilterBit;          // AOD filter bit selection
  int fNclsCut;            // ncls cut for all tracks
  float fChi2Max;          // upper limmit for chi2
  float fChi2Min;          // lower limmit for chi2
  float fDcaCutXY;            // dcaxy cut for all tracks
  float fDcaCutZ;             // dcaz cut for all tracks
  float fPtMin;            // minimum pt for tracks
  float fPtMax;            // maximum pt for tracks
  float fEtaCut;           // eta cut for tracks
  float fDedxCut;          // dedx cut for tracks
  double fProtonPtMin;     // Min pt for proton
  double fProtonPtMax;     // Max pt for proton
  double fAntiProtonPtMin; // Min pt for anti-proton
  double fAntiProtonPtMax; // Max pt for anti-proton
  // PID
  float fNSigmaTPCCut;
  float fNSigmaTOFCut;
  // V0
  double fV0PtMin;                  //
  double fV0CPAMin;                 //
  double fV0RapidityMax;            //
  double fV0DecayLengthMin;         //
  double fV0DecayLengthMax;         //
  double fV0DCAToPrimVtxMax;        //
  double fV0DcaBetweenDaughtersMax; //
  // V0 Daughter
  double fDaughtersPtMax;           //
  double fDaughtersEtaMax;          //
  double fDaughtersTPCNclsMin;      //
  double fDaughtersDCAToPrimVtxMin; //
  float fV0PosProtonTPCNsigma;      //
  float fV0NegPionTPCNsigma;        //
  float fV0NegProtonTPCNsigma;      //
  float fV0PosPionTPCNsigma;        //
  float fV0PosProtonTOFNsigma;      //
  float fV0NegPionTOFNsigma;        //
  float fV0NegProtonTOFNsigma;      //
  float fV0PosPionTOFNsigma;        //
  // Lambda Mass Cut
  double fLambdaMassMean;
  double fLambdaMassRightCut;     //
  double fLambdaMassLeftCut;      //
  double fAntiLambdaMassRightCut; //
  double fAntiLambdaMassLeftCut;  //

  ///////////////////The following files are from the data//////////////////////////////////
  /////////////
  // Handles //
  /////////////
  AliAODEvent* fAOD;            // aod Event
  AliPIDResponse* fPIDResponse; // PID Handler
  AliAnalysisUtils* fUtils;     // Event Selection Options
  AliMultSelection* fMultSel;

  ////////////////////////////////
  // Global Variables from data //
  ////////////////////////////////
  double fVertex[3]; // vetex
  int fRunNum;       // runnumber
  int fOldRunNum;    // latest runnumber
  int fRunNumBin;    // runnumer bin; 10:139510...; 11:170387...; 15HIR:246994...
  int fVzBin;        // vertex z bin
  float fCent;       // centrality
  int fCentBin;      // centrality bin: 0-10
  float fCentV0M;    // Centrality V0M
  float fCentTRK;    // Centrality TRK
  float fCentSPD0;   // Centrality SPD0
  float fCentSPD1;   // Centrality SPD1
  // Variable to get TPC Plane
  double fSumQ2xTPCPos;
  double fSumQ2yTPCPos;
  double fWgtMultTPCPos;
  double fSumQ2xTPCNeg;
  double fSumQ2yTPCNeg;
  double fWgtMultTPCNeg;
  // Plane
  double fPsi2TPCPos;
  double fPsi2TPCNeg;
  double fPsi2V0C;
  double fPsi2V0A;
  double fPsi1ZNC;
  double fPsi1ZNA;
  // Are we get the right plane?
  bool isRightTPCPlane;
  bool isRightVZEROPlane;
  bool isRightZDCPlane;

  // Plane tracks Map key:id value:(phi,weight)
  std::unordered_map<int, std::vector<double>> mapTPCPosTrksIDPhiWgt;
  std::unordered_map<int, std::vector<double>> mapTPCNegTrksIDPhiWgt;
  
  // Vector for particles from Tracks [pt,eta,phi,id,pdgcode,weight]
  std::vector<std::array<double,6>> vecParticle;
  // Vector for V0s [pt,eta,phi,id,pdgcode,weight,mass,id1,id2]
  std::vector<std::array<double,9>> vecParticleV0;
  // Vector for daughter particles [pt,eta,phi,id,pdgcode,weight]
  std::vector<std::array<double,6>> vecParticleFromDecay;
  // Vector for daughter particles which pass the TOF and DCA [pt,eta,phi,id,pdgcode,weight]
  std::vector<std::array<double,6>> vecParticleFromDecayPassAllCuts;

  ///////////////////The following files are read from external sources////////////////////
  ////////////////////////
  // Pile up Function
  ////////////////////////
  TF1* fSPDCutPU;
  TF1* fV0CutPU;
  TF1* fCenCutLowPU;
  TF1* fCenCutHighPU;
  TF1* fMultCutPU;
  ////////////////////////
  // NUE
  ////////////////////////
  // 10h/15o
  TList* fListNUE; // read list for NUE
  TH1D* hNUEweightPlus;
  TH1D* hNUEweightMinus;
  ////////////////////////
  // NUA
  ////////////////////////
  TList* fListNUA; // read lists for NUA
  // 10h
  TH2D* hNUAweightPlus;
  TH2D* hNUAweightMinus;
  // 15o
  TH3F* hCorrectNUAPos; // Protty
  TH3F* hCorrectNUANeg; // Protty
  ////////////////////////
  // VZERO
  ////////////////////////
  TList* fListVZEROCalib; // read list for V0 Calib
  // 10h
  TH2D* hMultV0Read;
  TProfile3D* pV0XMeanRead[3];
  TProfile3D* pV0YMeanRead[3];
  // 15o
  TH1D* hMultV0; // Dobrin
  AliOADBContainer* contMult;
  AliOADBContainer* contQxncm;
  AliOADBContainer* contQyncm;
  AliOADBContainer* contQxnam;
  AliOADBContainer* contQynam;
  TH1D* hQx2mV0[2];
  TH1D* hQy2mV0[2];
  // 18q
  TH2F* fHCorrectV0ChWeghts;
  ////////////////////////
  // ZDC
  ////////////////////////
  TList* fListZDCCalib;
  // 10h
  TTree* tree;
  float vtxQuant1[3];
  float vtxQuant2[3];
  TProfile* fProfileForZNCGE;
  TProfile* fProfileForZNAGE;
  THnSparseF* fHn4DForZNCQxRC;
  THnSparseF* fHn4DForZNCQyRC;
  THnSparseF* fHn4DForZNCMtRC;
  THnSparseF* fHn4DForZNAQxRC;
  THnSparseF* fHn4DForZNAQyRC;
  THnSparseF* fHn4DForZNAMtRC;
  THnSparseI* fHn4DForZNCCountsRC;
  THnSparseI* fHn4DForZNACountsRC;
  TProfile2D* fProfile2DForCosC;
  TProfile2D* fProfile2DForSinC;
  TProfile2D* fProfile2DForCosA;
  TProfile2D* fProfile2DForSinA;
  // 15o 
  // 18q 18r
  TH1D* fHZDCCparameters;
  TH1D* fHZDCAparameters;

  ///////////////////The following files will be saved//////////////////////////////////
  //////////////
  // QA Plots //
  //////////////
  TList* fQAList;
  // General QA
  // Event-wise
  TH1D* fEvtCount;
  std::map<int, int>* runNumList;
  TH1I* fHistRunNumBin;
  TH1D* fHistCent[2];
  TH1D* fHistVz[2];
  TH2D* fHist2CentQA[8];
  TH2D* fHist2MultCentQA[2]; // need for cheak pile up
  TH2D* fHist2MultMultQA[6]; // need for cheak pile up
  // Track-wise
  TH1D* fHistPt;
  TH1D* fHistEta;
  TH1D* fHistNhits;
  TH2D* fHist2PDedx;
  TH1D* fHistDcaXY;
  TH1D* fHistDcaZ;
  TH1D* fHistPhi[2];
  TH2D* fHist2EtaPhi[2];
  // Psi QA
  // V0C [0]GE [1]RC
  TProfile* fProfileV0CQxCent[2];
  TProfile* fProfileV0CQyCent[2];
  TProfile* fProfileV0CQxVtx[2];
  TProfile* fProfileV0CQyVtx[2];
  TH2D* fHist2CalibPsi2V0CCent[2];
  TProfile* fProfileV0AQxCent[2];
  TProfile* fProfileV0AQyCent[2];
  TProfile* fProfileV0AQxVtx[2];
  TProfile* fProfileV0AQyVtx[2];
  TH2D* fHist2CalibPsi2V0ACent[2];
  // ZNC
  TProfile* fProfileZNCTowerMeanEnegry[2]; // ![0]Raw [1]GE
  TProfile* fProfileZNCQxCent[2];          // ![0]GE  [1]RC
  TProfile* fProfileZNCQyCent[2];          // ![0]GE  [1]RC
  TH2D* fHist2CalibPsi1ZNCCent[3];         // ![0]GE  [1]RC [2]SF
  // ZNA
  TProfile* fProfileZNATowerMeanEnegry[2];
  TProfile* fProfileZNAQxCent[2];
  TProfile* fProfileZNAQyCent[2];
  TH2D* fHist2CalibPsi1ZNACent[3];
  // ZNC-ZNA
  TProfile* fProfileZDCQxAQxCCent[2];
  TProfile* fProfileZDCQxAQyCCent[2];
  TProfile* fProfileZDCQyAQxCCent[2];
  TProfile* fProfileZDCQyAQyCCent[2];

  //Proton QA
  TH1D* fHistProtonPt;
  TH1D* fHistProtonEta;
  TH1D* fHistProtonPhi;
  TH1D* fHistProtonDcaXY;
  TH1D* fHistProtonDcaZ;
  TH2D* fHist2ProtonSigTPC;
  TH2D* fHist2ProtonSigTOF;
  TH1D* fHistAntiProtonPt;
  TH1D* fHistAntiProtonEta;
  TH1D* fHistAntiProtonPhi;
  TH1D* fHistAntiProtonDcaXY;
  TH1D* fHistAntiProtonDcaZ;
  TH2D* fHist2AntiProtonSigTPC;
  TH2D* fHist2AntiProtonSigTOF;

  // V0s QA
  TH1D* fHistV0Pt;              // !Raw V0s' pT
  TH1D* fHistV0Eta;             // !Raw V0s' eta
  TH1D* fHistV0DcatoPrimVertex; // !Raw V0s' DcatoPV
  TH1D* fHistV0CPA;             // !Raw V0s' CPA(cosine pointing angle)
  TH1D* fHistV0DecayLength;     // !Raw V0s' DecayLength
  // Lambda QA
  //[0]:Before the Mass Cut [1]:After the Mass Cut
  TH1D* fHistLambdaPt[2];                  //
  TH1D* fHistLambdaEta[2];                 //
  TH1D* fHistLambdaPhi[2];                 //
  TH1D* fHistLambdaDcaToPrimVertex[2];     //
  TH1D* fHistLambdaCPA[2];                 //
  TH1D* fHistLambdaDecayLength[2];         //
  TH1D* fHistLambdaMass[2];                //
  TH2D* fHist2LambdaMassPtY[2];            //
  TH1D* fHistAntiLambdaPt[2];              //
  TH1D* fHistAntiLambdaEta[2];             //
  TH1D* fHistAntiLambdaPhi[2];             //
  TH1D* fHistAntiLambdaDcaToPrimVertex[2]; //
  TH1D* fHistAntiLambdaCPA[2];             //
  TH1D* fHistAntiLambdaDecayLength[2];     //
  TH1D* fHistAntiLambdaMass[2];            //
  TH2D* fHist2AntiLambdaMassPtY[2];        //


  /////////////
  // Results //
  /////////////
  TList* fResultsList;
  // Plane
  TH2D* fHist2Psi2TPCPosCent;
  TH2D* fHist2Psi2TPCNegCent;
  TH2D* fHist2Psi2V0CCent;
  TH2D* fHist2Psi2V0ACent;
  TH2D* fHist2Psi1ZNCCent;
  TH2D* fHist2Psi1ZNACent;

  // Res
  TProfile* fProfileTPCPsi2Correlation;       // TPCPos-TPCNeg
  TProfile* fProfileV0MPsi2Correlation;       // VOC-VOA
  TProfile* fProfileZDCPsi1Correlation;       // ZNC-ZNA 1st
  TProfile* fProfileZDCPsi2Correlation;       // ZNC-ZNA 2nd
  TProfile* fProfileV0CTPCPosPsi2Correlation; // V0C-TPCPos
  TProfile* fProfileV0ATPCPosPsi2Correlation; // V0A-TPCNeg
  TProfile* fProfileV0CTPCNegPsi2Correlation; // V0C-TPCNeg
  TProfile* fProfileV0ATPCNegPsi2Correlation; // V0A-TPCNeg

  // Flow
  // [0]TPC [1]V0C [2]V0A [3]ZNC [4]ZNA
  // [0]pos [1]neg(anti)
  TProfile2D* fProfile2RawFlowPtCentHadron[5][2];
  TProfile2D* fProfile2RawFlowPtCentProton[5][2];
  TProfile2D* fProfile2RawFlowPtCentLambda[5][2];

  // δ
  TProfile* fProfileDeltaLambdaProton[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile* fProfileDeltaLambdaHadron[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile* fProfileDeltaLambdaLambda[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar
  TProfile* fProfileDeltaProtonProton[4]; //![0]:p-p  [1]:p-pbar [2]:pbar-p  [3]:pbar-pbar
  TProfile* fProfileDeltaHadronHadron[4]; //![0]:h+-h+[1]:h--h-  [2]:h--h+   [3]:h--h-
  // γ [5]:plane type [4]:pair type
  TProfile* fProfileGammaLambdaProton[5][4];
  TProfile* fProfileGammaLambdaHadron[5][4];
  TProfile* fProfileGammaLambdaLambda[5][4];
  TProfile* fProfileGammaProtonProton[5][4];
  TProfile* fProfileGammaHadronHadron[5][4];

  // Diff δ(ΔpT)
  TProfile2D* fProfile2DiffDeltaLambdaProtonDPt[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffDeltaLambdaHadronDPt[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffDeltaLambdaLambdaDPt[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar
  TProfile2D* fProfile2DiffDeltaProtonProtonDPt[4]; //![0]:p-p  [1]:p-pbar [2]:pbar-p  [3]:pbar-pbar
  TProfile2D* fProfile2DiffDeltaHadronHadronDPt[4]; //![0]:h+-h+[1]:h--h-  [2]:h--h+   [3]:h--h-
  // Diff δ(SpT)
  TProfile2D* fProfile2DiffDeltaLambdaProtonSPt[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffDeltaLambdaHadronSPt[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffDeltaLambdaLambdaSPt[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar
  TProfile2D* fProfile2DiffDeltaProtonProtonSPt[4]; //![0]:p-p  [1]:p-pbar [2]:pbar-p  [3]:pbar-pbar
  TProfile2D* fProfile2DiffDeltaHadronHadronSPt[4]; //![0]:h+-h+[1]:h--h-  [2]:h--h+   [3]:h--h-
  // Diff δ(Δη)
  TProfile2D* fProfile2DiffDeltaLambdaProtonDEta[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffDeltaLambdaHadronDEta[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffDeltaLambdaLambdaDEta[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar
  TProfile2D* fProfile2DiffDeltaProtonProtonDEta[4]; //![0]:p-p  [1]:p-pbar [2]:pbar-p  [3]:pbar-pbar
  TProfile2D* fProfile2DiffDeltaHadronHadronDEta[4]; //![0]:h+-h+[1]:h--h-  [2]:h--h+   [3]:h--h-
  // Diff δ(mass)
  TProfile2D* fProfile2DiffDeltaLambdaProtonMass[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffDeltaLambdaHadronMass[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffDeltaLambdaLambdaMass[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar

  // Diff γ(ΔpT)(only TPC Plane)
  TProfile2D* fProfile2DiffGammaLambdaProtonDPt[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffGammaLambdaHadronDPt[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffGammaLambdaLambdaDPt[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar
  TProfile2D* fProfile2DiffGammaProtonProtonDPt[4]; //![0]:p-p  [1]:p-pbar [2]:pbar-p  [3]:pbar-pbar
  TProfile2D* fProfile2DiffGammaHadronHadronDPt[4]; //![0]:h+-h+[1]:h--h-  [2]:h--h+   [3]:h--h-
  // Diff γ(SpT)(only TPC Plane)
  TProfile2D* fProfile2DiffGammaLambdaProtonSPt[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffGammaLambdaHadronSPt[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffGammaLambdaLambdaSPt[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar
  TProfile2D* fProfile2DiffGammaProtonProtonSPt[4]; //![0]:p-p  [1]:p-pbar [2]:pbar-p  [3]:pbar-pbar
  TProfile2D* fProfile2DiffGammaHadronHadronSPt[4]; //![0]:h+-h+[1]:h--h-  [2]:h--h+   [3]:h--h-
  // Diff γ(Δη)
  TProfile2D* fProfile2DiffGammaLambdaProtonDEta[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffGammaLambdaHadronDEta[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffGammaLambdaLambdaDEta[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar
  TProfile2D* fProfile2DiffGammaProtonProtonDEta[4]; //![0]:p-p  [1]:p-pbar [2]:pbar-p  [3]:pbar-pbar
  TProfile2D* fProfile2DiffGammaHadronHadronDEta[4]; //![0]:h+-h+[1]:h--h-  [2]:h--h+   [3]:h--h-
  // Diff δ(mass)
  TProfile2D* fProfile2DiffGammaLambdaProtonMass[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile2D* fProfile2DiffGammaLambdaHadronMass[4]; //![0]:Λ-h+ [1]:Λ-h-   [2]:Λbar-h+ [3]:Λbar-h-
  TProfile2D* fProfile2DiffGammaLambdaLambdaMass[4]; //![0]:Λ-Λ  [1]:Λ-Λbar [2]:Λbar-Λ  [3]:Λbar-Λbar


  // C(Δη,Δφ) [cent][pair type]
  TH2D* fHist2DEtaDPhiLambdaProton[8][4];
  TH2D* fHist2DEtaDPhiLambdaHadron[8][4];
  TH2D* fHist2DEtaDPhiLambdaLambda[8][4];
  TH2D* fHist2DEtaDPhiProtonProton[8][4];
  TH2D* fHist2DEtaDPhiHadronHadron[8][4];

  // C(Δη,sφ) [cent][pair type] only TPC Plane
  TH2D* fHist2DEtaSPhiLambdaProton[8][4];
  TH2D* fHist2DEtaSPhiLambdaHadron[8][4];
  TH2D* fHist2DEtaSPhiLambdaLambda[8][4];
  TH2D* fHist2DEtaSPhiProtonProton[8][4];
  TH2D* fHist2DEtaSPhiHadronHadron[8][4];

  // δ Λ - daughter
  TProfile* fProfileDeltaLambdaProtonDecay[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile* fProfileDeltaLambdaPionDecay[4];   //![0]:Λ-pi+  [1]:Λ-pi- [2]:Λbar-pi+ [3]:Λbar-pi-
  // γ Λ - daughter(only TPC)
  TProfile* fProfileGammaLambdaProtonDecay[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile* fProfileGammaLambdaPionDecay[4];   //![0]:Λ-pi+  [1]:Λ-pi- [2]:Λbar-pi+ [3]:Λbar-pi-

  // δ Λ - daughter (this daughter contribute in the Λ-p)
  TProfile* fProfileDeltaLambdaProtonDecayPassAllCuts[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile* fProfileDeltaLambdaPionDecayPassAllCuts[4];   //![0]:Λ-pi+  [1]:Λ-pi- [2]:Λbar-pi+ [3]:Λbar-pi-
  // γ Λ - daughter(only TPC)
  TProfile* fProfileGammaLambdaProtonDecayPassAllCuts[4]; //![0]:Λ-p  [1]:Λ-pbar [2]:Λbar-p  [3]:Λbar-pbar
  TProfile* fProfileGammaLambdaPionDecayPassAllCuts[4];   //![0]:Λ-pi+  [1]:Λ-pi- [2]:Λbar-pi+ [3]:Λbar-pi-


  AliAnalysisTaskCVEPIDCME(const AliAnalysisTaskCVEPIDCME&);
  AliAnalysisTaskCVEPIDCME& operator=(const AliAnalysisTaskCVEPIDCME&);

  ClassDef(AliAnalysisTaskCVEPIDCME, 1);
};

#endif

