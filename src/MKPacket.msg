namespace smart3p;

//
// Master Key Packet
//
packet MKPacket {
    int id;
    double value;
    int smGateID;
    int collGateID;
	int pSize;
	string pBytes;
	int qSize;
	string qBytes;
	int gSize;
	string gBytes;
	int xSize;
	string xBytes;
}
