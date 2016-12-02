/*
 * Copyright 2016 CREATE-NET
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @ingroup
 * @{
 *
 * @file        IoTivityProtocol.cpp
 * @brief       IoTivity protocol implementation for AGILE
 *
 * @author      Mattia Antonini <mattia.antonini1@studenti.unipr.it>
 *                              <m.antonini@create-net.org>
 *
 * @}
 */

#include "IoTivityProtocol.h"

using namespace std;
using namespace OC;

//Attributes
const string IoTivityProtocol::TAG = "IoTivityProtocol";
OCConnectivityType connectivityType(CT_ADAPTER_IP);
//End Attributes

IoTivityProtocol::IoTivityProtocol() : AGILE::Protocol()
{
    BUS_NAME = "iot.agile.protocol.iotivity";
    BUS_PATH = "/iot/agile/protocol/iotivity";
    PROTOCOL_NAME = "IoTivity";
    DRIVER_NAME = "iotivity";

    log = new Logger(&std::cout, Logger::LEVEL_DEBUG);

}

IoTivityProtocol* IoTivityProtocol::getInstance()
{
    if(!instance)
    {
        instance = new IoTivityProtocol();
    }

    return (IoTivityProtocol*) instance;
}

void IoTivityProtocol::startProtocol(string da)
{
    int ret = 0;

    log->i(TAG, "Protocol starting...");
    log->d(TAG, "Initializing DBus");
   
    ret = initBus();
    if(ret == PROTOCOL_DBUS_INIT_ERROR)
    {
        log->c(TAG, "DBus Initialization failed!");
        return;
    }

    log->d(TAG, "Initializing IoTivity");
    /* Configure Platform */
    platformConfig = new PlatformConfig(ServiceType::InProc, //
                        ModeType::Client, //
                        "0.0.0.0", //
                        0, //
                        OC::QualityOfService::HighQos);
    OCPlatform::Configure(*platformConfig);
    log->d(TAG, "Platform configured");
    log->v(TAG, "Multicast Destination address is: " + da);

    destinationAddress = da;

    log->i(TAG, "IoTivity initialized!");
    log->i(TAG, "Press CTRL+C to exit...");
    keepAliveProtocol();
}

void IoTivityProtocol::onBusAcquiredCb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    log->d(TAG, "Bus Acquired!");
}

void IoTivityProtocol::onNameAcquiredCb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    log->d(TAG, "Name " + string(name) + " acquired!");
    log->i(TAG, "DBus initialized!");
}

void IoTivityProtocol::onNameLostCb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    log->c(TAG, "Name " + string(name) + " lost!");
    exit(1);
}

void IoTivityProtocol::Connect(string deviceId)
{
    log->e(TAG, "Connect not implemented yet! DevID: " + deviceId);
}

void IoTivityProtocol::Disconnect(string deviceId)
{
    log->e(TAG, "Disconnect not implemented yet DevID: " + deviceId);
}

void IoTivityProtocol::StartDiscovery()
{
    log->v(TAG, "StartDiscovery invoked");
    if(discoveryPeriodicCallback)
    {
        log->w(TAG, "Discovery is already started");
        return;
    }
    discoveryPeriodicCallback = new PeriodicCallback(DISCOVERY_DELAY*1000, false, bind(&IoTivityProtocol::doDiscovery, this));
    //TODO: discovery should be done every 15-60 secs
}

void IoTivityProtocol::StopDiscovery()
{
    log->v(TAG, "StopDiscovery invoked");
    if(!discoveryPeriodicCallback)
    {
        log->w(TAG, "StopDiscovery invoked when discovery is not running");
        return;
    }
    discoveryPeriodicCallback->stopThread();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    delete discoveryPeriodicCallback;
    discoveryPeriodicCallback = nullptr;
    log->d(TAG, "DiscoveryPeriodicCallback removed");
}

string IoTivityProtocol::DiscoveryStatus()
{
    if(discoveryPeriodicCallback) return PROTOCOL_DISCOVERY_STATUS_RUNNING;
    else return PROTOCOL_DISCOVERY_STATUS_NONE;
}

void IoTivityProtocol::doDiscovery()
{
    log->v(TAG, "Performing discovery...");
    OCPlatform::findResource(destinationAddress.c_str(),
                             string(OC_RSRVD_WELL_KNOWN_URI).c_str(),
                             connectivityType,
                             bind(&IoTivityProtocol::onDiscovery, this, placeholders::_1),
                             OC::QualityOfService::HighQos);
}

void IoTivityProtocol::onDiscovery(std::shared_ptr<OC::OCResource> resource)
{
    log->v(TAG, "Resource Discovered");
}
/************************************************************************************************/

void print_usage(char* program_name)
{
    cout << "TODO: usage" << endl;
}


int main(int argc, char** argv)
{
    IoTivityProtocol::getInstance()->startProtocol("ff03::158");
    return 0;
}
