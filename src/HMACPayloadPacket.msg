namespace smart3p;

//
// HMACPayload Packet
//
packet HMACPayloadPacket {
    int id;
    double value;
    int smGateID;
    int collGateID;
	int messageLength;
	int hmacSize;
	string hmac;
	int c1Size;
	string c1Bytes;
	int c21Size;
	string c21Bytes;
	int c22Size;
	string c22Bytes;
	int idSize;
	string idBytes;
	int rSize;
	string rBytes;
	int timeStampSize;
	string timeStampBytes;
	
}
