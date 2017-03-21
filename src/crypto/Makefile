#
# OMNeT++/OMNEST Makefile for Smart3P
#
# This file was generated with the command:
#  opp_makemake -f --deep --nolink -O out -I/usr/include/cryptopp -I.. -L/home/daniel/omnetpp-5.0/samples/Smart3P/src/crypto
#

# C++ include paths (with -I)
INCLUDE_PATH = -I/usr/include/cryptopp -I.. -I.

# Output directory
PROJECT_OUTPUT_DIR = ../../out
PROJECTRELATIVE_PATH = src/crypto
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = $O/Requester.o $O/UtilityCompany.o $O/SmartMeter.o $O/TrustedParty.o

# Message files
MSGFILES =

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target

all: $(OBJS)  Makefile
	@# Do nothing

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f Smart3P Smart3P.exe libSmart3P.so libSmart3P.a libSmart3P.dll libSmart3P.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Requester.o: Requester.cc \
	../Adapter.h \
	../SMPacket_m.h \
	../UCAdapter.h \
	../Unit.h \
	../UtilityCompany.h \
	../cInteger.h \
	Requester.h \
	UtilityCompany.h \
	examples.h \
	list.h
$O/SmartMeter.o: SmartMeter.cc \
	../Adapter.h \
	../SMAdapter.h \
	../SMPacket_m.h \
	../SmartMeter.h \
	../UCAdapter.h \
	../Unit.h \
	../UtilityCompany.h \
	../cInteger.h \
	Requester.h \
	SmartMeter.h \
	TrustedParty.h \
	UtilityCompany.h \
	examples.h \
	list.h
$O/TrustedParty.o: TrustedParty.cc \
	../Adapter.h \
	../SMPacket_m.h \
	../TTPAdapter.h \
	../UCAdapter.h \
	../Unit.h \
	../UtilityCompany.h \
	../cInteger.h \
	Requester.h \
	TrustedParty.h \
	UtilityCompany.h \
	examples.h \
	list.h
$O/UtilityCompany.o: UtilityCompany.cc \
	../Adapter.h \
	../SMPacket_m.h \
	../SmartMeter.h \
	../UCAdapter.h \
	../Unit.h \
	../UtilityCompany.h \
	../cInteger.h \
	Requester.h \
	SmartMeter.h \
	TrustedParty.h \
	UtilityCompany.h \
	examples.h \
	list.h

