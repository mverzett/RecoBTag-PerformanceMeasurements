import FWCore.ParameterSet.Config as cms
loosemuons = cms.EDFilter(
   'PATMuonSelector',
   src = cms.InputTag("FIXME"),
   cut = cms.string('pt > 15. & abs(eta) < 2.1 & isPFMuon & (isGlobalMuon || isTrackerMuon) & trackIso/pt < 0.1')
   )
tightmuons = cms.EDProducer(
   'TTTightMuonProducer',
   src = cms.InputTag("loosemuons"),
   vtx = cms.InputTag("offlineSlimmedPrimaryVertices"),
   ptmin = cms.double(30),
   etamax = cms.double(2.1)
   )

looseelectrons = cms.EDFilter(
   'PATElectronSelector',
   src = cms.InputTag("FIXME"),
   cut = cms.string('pt > 15. & abs(eta) < 2.1 & electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-loose")')
   )   
tightelectrons = cms.EDFilter(
   'PATElectronSelector',
   src = cms.InputTag("looseelectrons"),
   cut = cms.string('pt > 30. & abs(eta) < 2.1 & electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-medium")')
   )

from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import cleanPatJets
ttjets = cleanPatJets.clone()
ttjets.src = 'FIXME'
ttjets.preselection = cms.string('pt > 25 & abs(eta) < 2.4')
ttjets.checkOverlaps.muons.src = 'loosemuons'
ttjets.checkOverlaps.electrons.src = 'looseelectrons'
del ttjets.checkOverlaps.photons
del ttjets.checkOverlaps.taus
del ttjets.checkOverlaps.tkIsoElectrons

countjets = cms.EDFilter(
  "PATCandViewCountFilter",
  src       = cms.InputTag( 'ttjets' ),
  minNumber = cms.uint32( 4 ),
  maxNumber = cms.uint32( 4 ),
)

#
# checking for only one lepton in the event
#
countmus = cms.EDFilter(
  "PATCandViewCountFilter",
  src       = cms.InputTag('loosemuons'),
  minNumber = cms.uint32(0),
  maxNumber = cms.uint32(1),
)
countels = cms.EDFilter(
  "PATCandViewCountFilter",
  src       = cms.InputTag('looseelectrons'),
  minNumber = cms.uint32(0),
  maxNumber = cms.uint32(1),
)
leptons = cms.EDProducer(
  "CandViewMerger",
  src = cms.VInputTag(
      'tightmuons',
      'tightelectrons'
      ),
)
countleps = cms.EDFilter(
  "PATCandViewCountFilter",
  src       = cms.InputTag('leptons'),
  minNumber = cms.uint32(1),
  maxNumber = cms.uint32(1),
)


semilepFilterSequence = cms.Sequence(
   loosemuons *
   tightmuons *
   countmus *
   looseelectrons *
   tightelectrons *
   countels *
   leptons *
   countleps *
   ttjets *
   countjets
)
