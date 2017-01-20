import FWCore.ParameterSet.Config as cms
from SimTracker.TrackHistory.TrackClassifier_cff import *
bTagAnalyzerCommon = cms.PSet(
    trackClassifier,
    runFatJets               = cms.bool(False),
    runSubJets               = cms.bool(False),
    allowJetSkipping         = cms.bool(True),
    useSelectedTracks        = cms.bool(True),
    useTrackHistory          = cms.bool(False),
    produceJetTrackTree      = cms.bool(False),
		produceHelixInfo         = cms.bool(False),
    produceAllTrackTree      = cms.bool(False),
    producePtRelTemplate     = cms.bool(False),
    storeEventInfo           = cms.bool(True),
		storeMCInfo              = cms.bool(True),
    storePatMuons            = cms.bool(False),
    storeTagVariables        = cms.bool(False),
    storeTagVariablesSubJets = cms.bool(False),
    storeCSVTagVariables     = cms.bool(False),
    storeCSVTagVariablesSubJets = cms.bool(False),
    storeCTagVariables       = cms.bool(False),
    doCTag                   = cms.bool(False),
    fillsvTagInfo            = cms.bool(False),
    fillPU                   = cms.bool(False),
    fillGenPruned            = cms.bool(True),
    fillQuarks               = cms.bool(False),
    selTagger                = cms.int32(2),
    MaxEta                   = cms.double(2.5),
    MinPt                    = cms.double(20.0),
    src                      = cms.InputTag('generator'),
    primaryVertexColl        = cms.InputTag('offlinePrimaryVertices'),
    tracksColl               = cms.InputTag('generalTracks'),
    BranchNamePrefix         = cms.string(''),
    Jets                     = cms.InputTag('selectedPatJets'),
    SubJets                  = cms.VInputTag(),
    SubJetLabels             = cms.vstring(),
    muonCollectionName       = cms.InputTag('muons'),
    patMuonCollectionName    = cms.InputTag('selectedPatMuons'),
    triggerTable             = cms.InputTag('TriggerResults'),
    genParticles             = cms.InputTag('genParticles'),
    prunedGenParticles       = cms.InputTag('prunedGenParticlesBoost'),
    candidates               = cms.InputTag("particleFlow"),
    maxDeltaR                = cms.double(0.4),
    explicitJTA              = cms.bool(False),
    subJetMaxDeltaR          = cms.double(0.4),
    subJetExplicitJTA        = cms.bool(True),
    use_ttbar_filter         = cms.bool(False),
    ttbarproducer            = cms.InputTag("ttbarselectionproducer"),
    rho                      = cms.InputTag("fixedGridRhoFastjetAll"),
    beta                     = cms.double(1.0),
    R0                       = cms.double(0.8),
    maxSVDeltaRToJet         = cms.double(0.7),
    weightFile               = cms.FileInPath('RecoBTag/PerformanceMeasurements/data/BoostedDoubleSV_AK8_BDT_v3.weights.xml.gz'),
    trackPairV0Filter        = cms.PSet(k0sMassWindow = cms.double(0.03)),
    distJetAxis              = cms.double(0.07),
    decayLength              = cms.double(5.0),
    deltaR                   = cms.double(0.3),
    distJetAxisSubJets       = cms.double(0.07),
    decayLengthSubJets       = cms.double(5.0),
    deltaRSubJets            = cms.double(0.3),
    TriggerPathNames = cms.vstring(
        "HLT_Jet15U*",
        "HLT_Jet30_v*",
        "HLT_PFJet40_v*",
        "HLT_Jet30U*",
        "HLT_Jet60_v*",
        "HLT_Jet50U*",
        "HLT_Jet80_v*",
        "HLT_PFJet80_v*",
        "HLT_Jet70U*",
        "HLT_Jet110_v*",
        "HLT_Jet100U*",
        "HLT_Jet150_v*",
        "HLT_PFJet140_v*",
        "HLT_Jet140U*",
        "HLT_Jet190_v*",
        "HLT_PFJet200_v*",
        "HLT_Jet240_v*",
        "HLT_PFJet260_v*",
        "HLT_Jet300_v*",
        "HLT_PFJet320_v*",
        "HLT_DiPFJetAve320_v*",
        "HLT_PFJet400_v*",
        "HLT_DiJetAve15U*",
        "HLT_DiJetAve30_v*",
        "HLT_DiPFJetAve40_v*",
        "HLT_DiJetAve30U*",
        "HLT_DiJetAve60_v*",
        "HLT_DiPFJetAve80_v*",
        "HLT_DiJetAve50U*",
        "HLT_DiJetAve80_v*",
        "HLT_DiPFJetAve140_v*",
        "HLT_BTagMu_Jet10U*",
        "HLT_BTagMu_Jet20U*",
        "HLT_BTagMu_DiJet20U*",
        "HLT_BTagMu_DiJet20U_Mu5*",
        "HLT_BTagMu_DiJet20_Mu5*",
        "HLT_BTagMu_DiJet20_L1FastJet_Mu5_v*",
        "HLT_BTagMu_DiJet30U",
        "HLT_BTagMu_DiJet30U_v*",
        "HLT_BTagMu_DiJet30U_Mu5*",
        "HLT_BTagMu_DiJet60_Mu7*",
        "HLT_BTagMu_DiJet40_Mu5*",
        "HLT_BTagMu_DiJet20_L1FastJet_Mu5*",
        "HLT_BTagMu_DiJet80_Mu9*",
        "HLT_BTagMu_DiJet70_Mu5*",
        "HLT_BTagMu_DiJet70_L1FastJet_Mu5*",
        "HLT_BTagMu_DiJet100_Mu9_v*",
        "HLT_BTagMu_DiJet110_Mu5*",
        "HLT_BTagMu_DiJet110_L1FastJet_Mu5*",
        "HLT_BTagMu_Jet300_L1FastJet_Mu5*",
        "HLT_BTagMu_Jet300_Mu5*",
        "HLT_HT200",
        "HLT_HT240",
        "HLT_HT100U",
        "HLT_HT120U",
        "HLT_HT140U",
        "HLT_HT50U_v*",
        "HLT_HT100U_v*",
        "HLT_HT130U_v*",
        "HLT_HT140U_Eta3_v*",
        "HLT_HT140U_J30U_Eta3_v*",
        "HLT_HT150U_Eta3_v*",
        "HLT_HT150U_v*",
        "HLT_HT160U_Eta3_v*",
        "HLT_HT160U_v*",
        "HLT_HT200U_v*",
        "HLT_HT150_v*",
        "HLT_HT160_v*",
        "HLT_HT200_v*",
        "HLT_HT240_v*",
        "HLT_HT250_v*",
        "HLT_HT260_v*",
        "HLT_HT300_v*",
        "HLT_HT350_v*",
        "HLT_HT360_v*",
        "HLT_HT400_v*",
        "HLT_HT440_v*",
        "HLT_HT450_v*",
        "HLT_HT500_v*",
        "HLT_HT520_v*",
        "HLT_HT550_v*",
        "HLT_HT600_v*",
        "HLT_HT650_v*",
        "HLT_HT700_v*",
        "HLT_HT750_L1FastJet_v*",
        "HLT_HT750_v*",
        "HLT_HT2000_v*",
        "HLT_PFJet60_v*",
        "HLT_PFJet450_v*",
        "HLT_PFJet500_v*",
        "HLT_BTagMu_DiJet170_Mu5_v*",
        "HLT_BTagMu_AK8Jet300_Mu5_v*"
    ),
    TTbarTriggerPathNames = cms.vstring(
        # trigger for ttbar: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiTopRefEventSel#Triggers
        "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",  # 2-electron case
        "HLT_Mu17_Mu8_v*",                                                                          # 2-muon case1
        "HLT_Mu17_TkMu8_v*",                                                                        # 2-muon case2
        "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",                                      # muon + electron case1
        "HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"                                       # muon + electron case2
        ),
    PFJet80TriggerPathNames = cms.vstring("HLT_PFJet80_v*")
)
