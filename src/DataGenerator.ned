
package smart3p;

simple DataGenerator
{
    parameters:
        @display("i=block/source");
	//double per = default(0.8); //unused
        double freqOfSendingData = 5; //in seconds
    gates:
        inout smLine[];
}
