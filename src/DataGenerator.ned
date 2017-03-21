
package smart3p;

simple DataGenerator
{
    parameters:
        @display("i=block/source");
	//double per = default(0.8); //unused
        double freqOfSendingData @unit(ms) = default(1ms);
    gates:
        inout smLine[];
}
