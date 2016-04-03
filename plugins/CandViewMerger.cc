// -*- C++ -*-
//
// Package:    RecoBTag/PerformanceMeasurements
// Class:      CandViewMerger
// 
/**\class CandViewMerger CandViewMerger.cc RecoBTag/PerformanceMeasurements/plugins/CandViewMerger.cc

 Description: merges multiple collections (even of different types) into a single one, produces collection of reco::LeafCandidate

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  mauro verzetti
//         Created:  Sun, 03 Apr 2016 08:41:48 GMT
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

#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/Common/interface/View.h"
#include <vector>
#include <memory>

using namespace reco;
using namespace std;
using namespace edm;
//
// class declaration
//

class CandViewMerger : public edm::stream::EDProducer<> {
public:
  explicit CandViewMerger(const edm::ParameterSet&);
  ~CandViewMerger();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginStream(edm::StreamID) override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endStream() override;

  vector<EDGetTokenT< View<LeafCandidate> > > srcs_;
  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

  // ----------member data ---------------------------
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
CandViewMerger::CandViewMerger(const edm::ParameterSet& iConfig)
{
  for(auto &tag : iConfig.getParameter<vector<InputTag> >("src")) {
    srcs_.push_back(consumes<View<LeafCandidate> >(tag));
  }
  produces<vector<LeafCandidate> >();  
}


CandViewMerger::~CandViewMerger()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
CandViewMerger::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  auto_ptr< vector<LeafCandidate> > output ( new std::vector<LeafCandidate>() );

  for(auto &token : srcs_) {
    Handle< View<LeafCandidate> > collection;
    iEvent.getByToken(token, collection);
    for(auto& obj : *collection) {
      output->push_back(obj);
    }
  }
  iEvent.put(output);
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
CandViewMerger::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
CandViewMerger::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
CandViewMerger::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
CandViewMerger::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
CandViewMerger::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
CandViewMerger::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CandViewMerger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CandViewMerger);
