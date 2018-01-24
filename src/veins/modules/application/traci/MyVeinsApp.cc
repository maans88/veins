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
        lastRec = 0;
        InterPacketDelay = 0;
    }
    else if (stage == 1) {
//        std::cout<< "I am: " << mobility->getNode()->getIndex() << endl;
        //Initializing members that require initialized other modules goes here
        EV << "AdaptiveApp\n";
        for (int i = 0; i <344; i++){
            fairness_packet_counter[i] = 0;
        }
    }
}
void MyVeinsApp::writelogfile(std::string filename, int content)
{
         std::ofstream  out;
         out.open(filename.c_str(), std::ios_base::app);
         out << content;
         out.close();
}
void MyVeinsApp::finish() {
    BaseWaveApplLayer::finish();
    recordScalar("IPD_APP_1",IPD_VEC[1]);
    recordScalar("IPD_APP_2",IPD_VEC[2]);
    recordScalar("IPD_APP_3",IPD_VEC[3]);
    recordScalar("IPD_APP_4",IPD_VEC[4]);
    recordScalar("IPD_APP_5",IPD_VEC[5]);
    recordScalar("IPD_APP_6",IPD_VEC[6]);
    recordScalar("IPD_APP_7",IPD_VEC[7]);
    recordScalar("IPD_APP_8",IPD_VEC[8]);
    recordScalar("IPD_APP_9",IPD_VEC[9]);
    recordScalar("IPD_APP_10",IPD_VEC[10]);
    recordScalar("IPD_APP_11",IPD_VEC[11]);
    recordScalar("IPD_APP_12",IPD_VEC[12]);
    recordScalar("IPD_APP_13",IPD_VEC[13]);
    recordScalar("IPD_APP_14",IPD_VEC[14]);
    recordScalar("IPD_APP_15",IPD_VEC[15]);
    recordScalar("IPD_APP_16",IPD_VEC[16]);
    recordScalar("IPD_APP_17",IPD_VEC[17]);

//    std::string Result;          // string which will contain the result
//    std::ostringstream convert;   // stream used for the conversion
//    convert << mobility->getNode()->getIndex();
//    Result = convert.str();
//    // create and open the .csv file
//    fs.open(outputFile,Result.c_str());
//     write the file headers
//    outputFile << "Column A" << "," << "Column B" << "Column C" << std::endl;


    int i = 0;
////    std::cout << "fairness from vehicle: " << mobility->getNode()->getIndex() << " ";
    for (i = 1; i < 344;i++){
        std::cout << fairness_packet_counter[i] << ",";
    }
    std::cout << endl;
//    outputFile.close();
}

void MyVeinsApp::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here
    InterPacketDelay = (InterPacketDelay + (simTime() - lastRec))/2;

//    std::cout<< "I am: " << mobility->getNode()->getIndex() << "received message from: " << bsm->getRandomm() << endl;



    float distance = abs(BaseWaveApplLayer::curPosition.x -  bsm->getSenderPos().x);

    lastRec = simTime();

    int local_index = distance /20;
    WATCH(IPD_VEC);
    if (IPD_VEC[local_index] == 0) {
        IPD_VEC[local_index] = 0.1;
        IPD_TIME[local_index] = simTime();
    }
    else {
        if (local_index > 17){
            local_index = 17;
        }
        IPD_VEC[local_index] = (IPD_VEC[local_index] + (simTime() - getLastTime(distance)))/2;
    }
//    std::cout << IPD_TIME[local_index] << " " << IPD_VEC[local_index] << "<-test: " << local_index << endl;
    fairness_packet_counter[bsm->getRandomm()] +=1;
}

simtime_t MyVeinsApp::getLastTime(float distance){
    int local_index = distance/20;
    if (local_index > 17){
        local_index = 17;
    }
    simtime_t temp = IPD_TIME[local_index];
    IPD_TIME[local_index] = simTime();
    return temp;
}
void MyVeinsApp::onWSM(WaveShortMessage* wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsApp::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsApp::handleSelfMsg(cMessage* msg) {
//    std::cout << "ID: "<< mobility->getNode()->getId() << endl;
    AdaptiveTX();
    BaseWaveApplLayer::handleSelfMsg(msg);
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission
}

void MyVeinsApp::handlePositionUpdate(cObject* obj) {
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class
    BaseWaveApplLayer::handlePositionUpdate(obj);
}

void MyVeinsApp::broadcastBSM(BasicSafetyMessage* bsm) {
//    std::cout << "IN" << bsm->getId() <<endl;


//    while ((simTime() - lastSent) >= 0.1){
//        EV_TRACE << "****" << lastSent << " " << simTime() << endl;
//        bsm = new BasicSafetyMessage();
//        bsm->setSenderPos(mobility->getCurrentPosition());
//        bsm->setSenderSpeed(mobility->getCurrentSpeed());
//        populateWSM(bsm);
//        event = new cMessage("test");
//        sendDown(bsm);
//    }
}
void MyVeinsApp::onData(BasicSafetyMessage* bsm) {
//    Receive a message with a target speed, slow down to that speed
    EV << "x1\n";
}
void MyVeinsApp::AdaptiveTX(){
    float speedFactor = 0;
    int algorithmType = par("algo").longValue();
    double vehicleSpeed ;
    vehicleSpeed = mobility->getSpeed();
//    std::cout << "speed: " << mobility->getSpeed() << endl;
    if (vehicleSpeed > 90) {
        speedFactor = 1.3;
    }
    else if(vehicleSpeed > 60){
        if (vehicleSpeed <= 90){
            speedFactor = 1.15;
        }
    }
    else if (vehicleSpeed > 40){
        if (vehicleSpeed <= 60){
            speedFactor = 1.1;
        }
    }
    else if(vehicleSpeed <= 40){
        speedFactor = 1.05;
    }
    if (algorithmType == 0){
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
        if(local_tx == 5){
                mac->setTxPower(10);
                local_tx = 1;
        }
        else {
            mac->setTxPower(3);
            local_tx++;
        }
    }
}
