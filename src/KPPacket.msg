namespace smart3p;

//
// Key Pair Packet
//
packet KPPacket {
    int id;
    double value;
    int smGateID;
    int collGateID;
	int privatePieceSize;
	string privatePieceBytes;
	int privatePartialSize;
	string privatePartialBytes;
	int publicPieceSize;
	string publicPieceBytes;
	int publicPartialSize;
	string publicPartialBytes;


}
