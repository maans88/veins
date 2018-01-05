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

#ifndef __VEINS_MYVEINSAPP_H_
#define __VEINS_MYVEINSAPP_H_

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mac/ieee80211p/Mac1609_4.h"
typedef std::vector<int> IntVector;
using namespace omnetpp;

/**
 * @brief
 * This is a stub for a typical Veins application layer.
 * Most common functions are overloaded.
 * See MyVeinsApp.cc for hints
 *
 * @author David Eckhoff
 *
 */

class MyVeinsApp : public BaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
        virtual void finish();
    protected:
        double local_tx;
        TraCIMobility* mobility;
        TraCICommandInterface* traci;
        TraCICommandInterface::Vehicle* traciVehicle;
        Mac1609_4 *mac;
        simtime_t lastSent, lastRec;
        simtime_t InterPacketDelay, time1;
        cMessage * event;
        BasicSafetyMessage* bsm;
        simtime_t IPD_VEC[30];
        simtime_t IPD_TIME[30];
        bool startSending;
        virtual void onBSM(BasicSafetyMessage* bsm);
        virtual void onData(BasicSafetyMessage* bsm);
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);
        void AdaptiveTX();
        void broadcastBSM();
        simtime_t getLastTime(float distance);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);
    };

#endif
