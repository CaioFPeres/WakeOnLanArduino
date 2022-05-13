class Wake {

private:
    int magicPacketLength;
    unsigned char* magicPacket;
    unsigned char* MACAddress;


public:
    Wake();
	~Wake();

    void setUpMagicPacket();
    unsigned char* getMagicPacket();
    int getPacketLength();
};