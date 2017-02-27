
package smart3p;

//
// Generates messages with a configurable interarrival time.
//
simple Collector
{
    parameters:
        volatile double sendInterval @unit(s) = default(1s);
        @display("i=block/source");
    gates:
    	inout radio[];
        inout ucLine;
}
