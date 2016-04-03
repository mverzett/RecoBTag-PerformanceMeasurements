// -*- C++ -*-
//
// Package:    RecoBTag/PerformanceMeasurements
// Class:      TTTightMuonProducer
// 
/**\class TTTightMuonProducer TTTightMuonProducer.cc RecoBTag/PerformanceMeasurements/plugins/TTTightMuonProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  mauro verzetti
//         Created:  Sun, 03 Apr 2016 21:09:11 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include <vector>
#include <memory>
//
// class declaration
//
using namespace edm;
using namespace std;

class TTTightMuonProducer : public edm::stream::EDProducer<> {
public:
  explicit TTTightMuonProducer(const edm::ParameterSet&);
  ~TTTightMuonProducer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginStream(edm::StreamID) override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endStream() override;

  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  // ----------member data ---------------------------
  EDGetTokenT< vector<pat::Muon> > src_;
  EDGetTokenT< vector<reco::Vertex> > vtx_;
  float ptmin_, etamax_;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
TTTightMuonProducer::TTTightMuonProducer(const edm::ParameterSet& iConfig)
{
   //register your products
  produces<vector<pat::Muon> >();
  src_ = consumes< vector<pat::Muon> >(iConfig.getParameter<InputTag>("src"));
  vtx_ = consumes< vector<reco::Vertex> >(iConfig.getParameter<InputTag>("vtx"));
  ptmin_ = iConfig.getParameter<double>("ptmin"); 
  etamax_ = iConfig.getParameter<double>("etamax");
}


TTTightMuonProducer::~TTTightMuonProducer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TTTightMuonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   auto_ptr< vector<pat::Muon> > output ( new std::vector<pat::Muon>() );

   Handle<vector<pat::Muon> > muons; 
   iEvent.getByToken(src_, muons);
   
   Handle<vector<reco::Vertex> > verts;
   iEvent.getByToken(vtx_, verts);
   
   for(auto& muon : *muons) {
     if(muon.pt() > ptmin_ && fabs(muon.eta()) < etamax_ && muon.isTightMuon(verts->at(0))) {
       output->push_back(muon);
     }
   }
   iEvent.put(output);
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
TTTightMuonProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
TTTightMuonProducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
TTTightMuonProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
TTTightMuonProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
TTTightMuonProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
TTTightMuonProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TTTightMuonProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TTTightMuonProducer);
