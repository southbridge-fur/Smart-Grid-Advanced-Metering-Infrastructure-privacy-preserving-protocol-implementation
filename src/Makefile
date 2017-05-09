#
# OMNeT++/OMNEST Makefile for Smart3P
#
# This file was generated with the command:
#  opp_makemake -f --deep -d crypto -I/usr/include/cryptopp -Icrypto -L/home/daniel/omnetpp-5.0/samples/Smart3P/src/crypto -lpthread -lcryptopp -- $$O/crypto/*.o
#

# Name of target to be created (-o option)
TARGET = Smart3P$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = -I/usr/include/cryptopp -Icrypto -I.

# Additional object and library files to link with
EXTRA_OBJS = $O/crypto/*.o

# Additional libraries (-L, -l options)
LIBS = -Lcrypto  -lpthread -lcryptopp
LIBS += -Wl,-rpath,`abspath crypto`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/DataGenerator.o \
    $O/TrustedThirdParty.o \
    $O/Adapter.o \
    $O/UtilityCompany.o \
    $O/cInteger.o \
    $O/SmartMeter.o \
    $O/TTPAdapter.o \
    $O/UCAdapter.o \
    $O/Unit.o \
    $O/Collector.o \
    $O/SMAdapter.o \
    $O/SMPacket_m.o

# Message files
MSGFILES = \
    SMPacket.msg

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

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

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
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS) submakedirs $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

submakedirs:  crypto_dir

.PHONY: all clean cleanall depend msgheaders smheaders  crypto
crypto: crypto_dir

crypto_dir:
	cd crypto && $(MAKE) all

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
	$(Q)cd crypto && $(MAKE) msgheaders

smheaders: $(SMFILES:.sm=_sm.h)
	$(Q)cd crypto && $(MAKE) smheaders

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f Smart3P Smart3P.exe libSmart3P.so libSmart3P.a libSmart3P.dll libSmart3P.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h

	-$(Q)cd crypto && $(MAKE) clean

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc
	$(Q)-cd crypto && if [ -f Makefile ]; then $(MAKE) depend; fi

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Adapter.o: Adapter.cc \
	Adapter.h \
	Unit.h \
	cInteger.h \
	crypto/examples.h \
	crypto/list.h
$O/Collector.o: Collector.cc \
	Collector.h \
	SMPacket_m.h \
	Unit.h
$O/DataGenerator.o: DataGenerator.cc \
	DataGenerator.h \
	SMPacket_m.h
$O/SMAdapter.o: SMAdapter.cc \
	Adapter.h \
	SMAdapter.h \
	SMPacket_m.h \
	SmartMeter.h \
	Unit.h \
	cInteger.h \
	crypto/Requester.h \
	crypto/SmartMeter.h \
	crypto/examples.h \
	crypto/list.h
$O/SMPacket_m.o: SMPacket_m.cc \
	SMPacket_m.h
$O/SmartMeter.o: SmartMeter.cc \
	Adapter.h \
	SMAdapter.h \
	SMPacket_m.h \
	SmartMeter.h \
	Unit.h \
	cInteger.h \
	crypto/Requester.h \
	crypto/SmartMeter.h \
	crypto/examples.h \
	crypto/list.h
$O/TTPAdapter.o: TTPAdapter.cc \
	Adapter.h \
	SMPacket_m.h \
	TTPAdapter.h \
	cInteger.h \
	crypto/Requester.h \
	crypto/TrustedParty.h \
	crypto/examples.h \
	crypto/list.h
$O/TrustedThirdParty.o: TrustedThirdParty.cc \
	Adapter.h \
	SMPacket_m.h \
	TTPAdapter.h \
	TrustedThirdParty.h \
	Unit.h \
	cInteger.h \
	crypto/examples.h \
	crypto/list.h
$O/UCAdapter.o: UCAdapter.cc \
	Adapter.h \
	SMPacket_m.h \
	UCAdapter.h \
	cInteger.h \
	crypto/Requester.h \
	crypto/UtilityCompany.h \
	crypto/examples.h \
	crypto/list.h
$O/Unit.o: Unit.cc \
	Unit.h
$O/UtilityCompany.o: UtilityCompany.cc \
	Adapter.h \
	SMPacket_m.h \
	UCAdapter.h \
	Unit.h \
	UtilityCompany.h \
	cInteger.h \
	crypto/Requester.h \
	crypto/UtilityCompany.h \
	crypto/examples.h \
	crypto/list.h
$O/cInteger.o: cInteger.cc \
	cInteger.h

