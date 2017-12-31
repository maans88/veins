//#include <stdlib.h>
//#include "LimericAppl.h"
//#include <iostream>
//#include <cstring>
//
//#define DEFAULT_VEH_SIZE    250
//#define DEFAULT_TARGET_UTIL 0.8
//#define DEFAULT_ITERATIONS 50
//
//using Veins::TraCIMobilityAccess;
////using Veins::AnnotationManagerAccess;
//
//Define_Module(LimericAppl);
//
//void LimericAppl::initialize(int stage) {
//    BaseWaveApplLayer::initialize(stage);
//    EV << "THIS IS MY APP\n";
//    mac = FindModule<Mac1609_4 *>::findSubModule(getParentModule());
//    local_tx = 1;
//    if (stage == 0) {
//        //setup veins pointers
//        mobility = TraCIMobilityAccess().get(getParentModule());
//        traci = mobility->getCommandInterface();
//        traciVehicle = mobility->getVehicleCommandInterface();
//        lastSent = simTime();
////        traciVehicle->setLaneChangeMode(0);
//        //        traciVehicle->setSpeed(7);
//        InterPacketDelay = 0;
//        AdaptiveTX();
//    }
//}
//
//void LimericAppl::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
//    EV << "xcurx " << BaseWaveApplLayer::curPosition << endl;
//    EV << BaseWaveApplLayer::deviceID << endl ;
//    Enter_Method_Silent();
//    if (signalID == mobilityStateChangedSignal) {
//        handlePositionUpdate(obj);
//    }
//}
//
//void LimericAppl::onData(WaveShortMessage* wsm) {
////    Receive a message with a target speed, slow down to that speed
//    EV << "x1\n";
//    float message_speed = atof(wsm->getWsmData());
//    traciVehicle->slowDown(message_speed, 1000); //slow down over 1s
//    EV << "onData: Slow down to: ";// << message_speed << "\n";
//    InterPacketDelay = (InterPacketDelay + (simTime() - time1))/2;
//    time1 = simTime();
//}
//
//void LimericAppl::onBeacon(WaveShortMessage* wsm) {
//    EV << "x2\n";
//    //  do something on receiving a message from a beacon
//    //  EV << "//do something on receiving a message from a beacon" << wsm->getName();
//    //   i do not think we are sending this type of messages.
//    // but let us try something cool
//    EV << "WOW COOOOL\n";
//}
//
//void LimericAppl::handlePositionUpdate(cObject* obj) {
//    //This application is being called the most, it seems like
//    //sends message every 5 seconds
//    //but we don't want to send every five seconds, we want more.
//    BaseWaveApplLayer::handlePositionUpdate(obj);
//    EV << "handle position every 5 seconds----" << mobility->getSpeed() << "\n";
//
//    if (simTime() - lastSent >= 5) {
//        std::string message = std::to_string(mobility->getSpeed());
//        sendMessage(message);
//        lastSent = simTime();
//    }
//}
//
//void LimericAppl::sendWSM(WaveShortMessage* wsm) {
//    EV << "send delayed downwhat????" << wsm->getId() << "\n";
////    sendDelayedDown(wsm, individualOffset);
//}
//
//void LimericAppl::sendMessage(std::string msg) {
////so we set the wsm with "data", then we use setter method here.
//    EV << "We are in sendmessage: " << msg << endl;
//    t_channel channel = dataOnSch ? type_SCH : type_CCH;
//    AdaptiveTX();
////    WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, channel, dataPriority, -1,2);
//
////    wsm->setWsmData(msg.c_str());
////    wsm->setSenderPos(mobility->getCurrentPosition());
////    sendWSM(wsm);
//}
////virtual void onData(BasicSafetyMessage* bsm){
////
////}
////
////virtual void onBeacon(BasicSafetyMessage* bsm){
////
////}
//void LimericAppl::AdaptiveTX(){
//    float speedFactor = 0;
//    int algorithmType = 0;
//    double vehicleSpeed ;
//    vehicleSpeed = mobility->getSpeed();
//    if (vehicleSpeed > 31.21) {
//        speedFactor = 1.6;
//    }
//    else if(25 < vehicleSpeed <= 31.25){
//        speedFactor = 1.4;
//    }
//    else if (15.625 < vehicleSpeed <= 25.0){
//        speedFactor = 1.2;
//    }
//    else if(vehicleSpeed <= 15.625){
//        speedFactor = 1.0;
//    }
//    if (algorithmType == 0){
//        EV << "GOING: " << mobility->getSpeed() << endl;
//        if (local_tx == 7){
//            mac->setTxPower(10);
//            local_tx = 1;
//        }
//        else {
//            mac->setTxPower(local_tx*speedFactor);
//            local_tx ++;
//        }
//    }
//    else if (algorithmType == 1){
//        EV << "OSC\n";
//        mac->setTxPower(2);
//        if(local_tx == 7){
//                mac->setTxPower(10);
//                EV << "10x";
//                local_tx = 1;
//        }
//        local_tx++;
//    }
//}
//
//void LimericAppl::finish(){
//    recordScalar("IPD_APP",InterPacketDelay);
//    EV << "BYEBYE\n";
//}
