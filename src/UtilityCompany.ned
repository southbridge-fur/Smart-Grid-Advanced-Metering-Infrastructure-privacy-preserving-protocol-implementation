
package smart3p;

simple UtilityCompany
{
    parameters:
    	volatile double sendInterval @unit(s) = default(exponential(20s));
        @display("i=block/source");
    gates:
    	inout radio[];
        inout ttpLine;
}
