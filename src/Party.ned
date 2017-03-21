
package smart3p;
package inet.transportlayer.tcp;
package inet.networklayer.ipv4;
//import inet.transportlayer.tcp.TCP;
//import inet.networklayer.ipv4.IPv4;

simple Agent
{
	gates:
		input tcpIn;
		output tcpOut;
}

module Party
{
	gates:
		input localIn;
		output localOut;
		inout radio[];
	submodules:
		//app: Agent;
		//tcp: TCP;
		//ip: IPv4;
		//wlan: IEEE80211;
	connections:
		//app.tcpOut --> tcp.appIn;
		//app.tcpIn <-- tcp.appOut;
		//tcp.ipOut --> ip.tcpIn;
		//tcp.ipIn <-- ip.tcpOut;
		//ip.nicOut++ --> wlan.ipIn;
		//ip.nicIn++ <-- wlan.ipOut;
		//wlan.radioIn <-- localIn;
		//wlan.radioOut --> localOut;
}
