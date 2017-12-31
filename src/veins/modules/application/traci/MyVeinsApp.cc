//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "MyVeinsApp.h"

Define_Module(MyVeinsApp);

void MyVeinsApp::initialize(int stage) {
    debugEV << "********************************************\n********************************************\n";
    BaseWaveApplLayer::initialize(stage);
    mobility = TraCIMobilityAccess().get(getParentModule());
    traci = mobility->getCommandInterface();
    traciVehicle = mobility->getVehicleCommandInterface();
    mac = FindModule<Mac1609_4 *>::findSubModule(getParentModule());

    if (stage == 0) {
        //Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        local_tx = 1;
        mobility = TraCIMobilityAccess().get(getParentModule());
        traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        lastSent = simTime();
        InterPacketDelay = 0;
    }
    else if (stage == 1) {
        //Initializing members that require initialized other modules goes here
    }
    EV << "AdaptiveApp\n";
}

void MyVeinsApp::finish() {
    BaseWaveApplLayer::finish();
    EV << "BYE\n";
    recordScalar("boolean",local_tx);
    //statistics recording goes here

}

void MyVeinsApp::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here
    EV << "********************************************\n********************************************\n";
}

void MyVeinsApp::onWSM(WaveShortMessage* wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
   EV << "********************************************\n********************************************\n";

}

void MyVeinsApp::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    debugEV << "********************************************\n********************************************\n";
}

void MyVeinsApp::handleSelfMsg(cMessage* msg) {
    BaseWaveApplLayer::handleSelfMsg(msg);
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission
    debugEV << "********************************************\n********************************************\n";

}

void MyVeinsApp::handlePositionUpdate(cObject* obj) {
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class
    BaseWaveApplLayer::handlePositionUpdate(obj);
    EV_TRACE << "Handle Position ********************************************\n********************************************\n";
    EV_FATAL << "TEST*\n";

    BasicSafetyMessage* bsm = new BasicSafetyMessage();
    bsm->setSenderPos(mobility->getCurrentPosition());
    bsm->setSenderSpeed(mobility->getCurrentSpeed());
    populateWSM(bsm);
    sendDown(bsm);
}
void MyVeinsApp::AdaptiveTX(){
    float speedFactor = 0;
    int algorithmType = 0;
    double vehicleSpeed ;
    vehicleSpeed = mobility->getSpeed();
    if (vehicleSpeed > 31.21) {
        speedFactor = 1.6;
    }
    else if(25 < vehicleSpeed <= 31.25){
        speedFactor = 1.4;
    }
    else if (15.625 < vehicleSpeed <= 25.0){
        speedFactor = 1.2;
    }
    else if(vehicleSpeed <= 15.625){
        speedFactor = 1.0;
    }
    if (algorithmType == 0){
        EV << "GOING: " << mobility->getSpeed() << endl;
        if (local_tx == 7){
            mac->setTxPower(10);
            local_tx = 1;
        }
        else {
            mac->setTxPower(local_tx*speedFactor);
            local_tx ++;
        }
    }
    else if (algorithmType == 1){
        EV << "OSC\n";
        mac->setTxPower(2);
        if(local_tx == 7){
                mac->setTxPower(10);
                EV << "10x";
                local_tx = 1;
        }
        local_tx++;
    }
}
