#include "Wake.h"

Wake::Wake() {

    magicPacketLength = 102;

    magicPacket = new unsigned char[magicPacketLength];
    MACAddress = new unsigned char[6];


    // my mac: e0:d5:5e:a1:4a:7b
    MACAddress[0] = 0xE0;
    MACAddress[1] = 0xD5;
    MACAddress[2] = 0x5E;
    MACAddress[3] = 0xA1;
    MACAddress[4] = 0x4A;
    MACAddress[5] = 0x7B;

    setUpMagicPacket();
}

Wake::~Wake(){
    delete magicPacket;
    delete MACAddress;
}


void Wake::setUpMagicPacket(){

    // fill with null
    for(int i = 0; i < 6; i++){
        magicPacket[i] = 0xFF;
    }

    // fill the rest with mac address
    for(int i = 6; i < magicPacketLength; i++){
        magicPacket[i] = MACAddress[i%6];
    }

}

unsigned char* Wake::getMagicPacket(){
    return magicPacket;
}

int Wake::getPacketLength(){
    return magicPacketLength;
}
