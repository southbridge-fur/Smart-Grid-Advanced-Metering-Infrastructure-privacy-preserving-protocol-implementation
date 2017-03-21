namespace smart3p;

//
// Payload Packet
//
packet PayloadPacket {
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
	int privateSize;
	string privateBytes;
	int publicSize;
	string publicBytes;
	
}
