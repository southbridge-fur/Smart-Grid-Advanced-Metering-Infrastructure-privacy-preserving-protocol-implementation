
package smart3p;

simple DataGenerator
{
    parameters:
        @display("i=block/source");
	//double per = default(0.8); //unused
        double freqOfSendingData = 5; //in seconds
	dataFileName = "/home/daniel/data.csv"; //datafile path
    gates:
        inout smLine[];
}
