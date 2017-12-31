//
//#ifndef LIMERICAPPL_H_
//#define LIMERICAPPL_H_
//
//#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
//#include "veins/modules/mobility/traci/TraCIMobility.h"
//#include "veins/modules/mobility/traci/TraCICommandInterface.h"
//#include "veins/modules/messages/PhyControlMessage_m.h"
//#include "veins/modules/mac/ieee80211p/Mac1609_4.h"
//using Veins::TraCIMobility;
//using Veins::TraCICommandInterface;
//
////using Veins::
////using Veins::AnnotationManager; //add for annotations
//
//class LimericAppl : public BaseWaveApplLayer {
//    public:
//        virtual void initialize(int stage);
//        virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details);
//    protected:
//        double local_tx;
//        TraCIMobility* mobility;
//        TraCICommandInterface* traci;
//        TraCICommandInterface::Vehicle* traciVehicle;
//        simtime_t lastSent; // the last time this sent a message
//        Mac1609_4 *mac;
//        cModule * parent;
//        simtime_t InterPacketDelay, time1;
//        virtual void onData(WaveShortMessage* wsm);
////        virtual void onData(BasicSafetyMessage* bsm);
////        virtual void onBeacon(BasicSafetyMessage* bsm);
//        virtual void onBeacon(WaveShortMessage* wsm);
//        virtual void handlePositionUpdate(cObject* obj);
//        virtual void finish();
//        void sendMessage(std::string blockedRoadId);
//        void AdaptiveTX();
//        virtual void sendWSM(WaveShortMessage* wsm);
//};
//
//#endif /* LIMERICAPPL_H_ */
