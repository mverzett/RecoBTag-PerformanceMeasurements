// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include <unordered_set>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;
//
// class declaration
//

class LHEParticleFilter : public edm::EDFilter {
public:
	explicit LHEParticleFilter(const edm::ParameterSet&);
	~LHEParticleFilter() {}

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
     
private:
	virtual void beginJob() {}
	virtual bool filter(edm::Event&, const edm::EventSetup&);
	virtual void endJob() {}
      
	virtual bool beginRun(edm::Run&, edm::EventSetup const&) {return true;}
	virtual bool endRun(edm::Run&, edm::EventSetup const&) {return true;}
	virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {return true;}
	virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {return true;}

	// ----------member data ---------------------------
	edm::EDGetTokenT<LHEEventProduct> src_;
	unordered_set<int> exclude_ids_; //if these IDs are in the LHE exclude the events
	unordered_set<int> exclude_mom_ids_; //check if the moms of the excluded IDs is this. If empty exclude in any case
	bool flag_mode_;
};

LHEParticleFilter::LHEParticleFilter(const edm::ParameterSet& cfg):
	src_(consumes<LHEEventProduct>(cfg.getParameter<edm::InputTag>("src"))),
	flag_mode_(cfg.getParameter<bool>("flagMode")) {
	typedef vector<int> vint;
	for(auto id : cfg.getParameter<vint>("reject"))
		exclude_ids_.insert(id);
	for(auto id : cfg.getParameter<vint>("reject_moms"))
		exclude_mom_ids_.insert(id);
	if(flag_mode_) produces<bool>();
}

bool LHEParticleFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {
	edm::Handle<LHEEventProduct> lhes;
	iEvent.getByToken(src_, lhes);
	
	//get LHE particles (hard scattering only)
	const lhef::HEPEUP& hepeup = lhes->hepeup();

	//loop over the particles
	for(size_t idx = 0 ; idx < hepeup.IDUP.size() ; ++idx) {
		int pdgid = hepeup.IDUP[idx];
		if(exclude_ids_.find(pdgid) != exclude_ids_.end()) {
			//get first mom pdgid
			int mom_pdgid = (hepeup.MOTHUP[idx].first > 1) ? hepeup.IDUP[hepeup.MOTHUP[idx].first-1] : 0; //indexes start from 1...
			if(exclude_mom_ids_.size() == 0 || exclude_mom_ids_.find(mom_pdgid) != exclude_mom_ids_.end()) {
				if(flag_mode_) {
					iEvent.put(make_unique<bool>(false));
					return true;
				}
				else return false;
			}
		}
	}
	iEvent.put(make_unique<bool>(true));
	return true;
}

void LHEParticleFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(LHEParticleFilter);
