
# files
# ---------------------------------------------------------------
AUXFILES := Makefile README.md LICENSE
PROJDIRS := lib

SRCFILES := $(shell find $(PROJDIRS) -type f -name "\*.cc")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "\*.h")

OBJFILES := $(pathsubst %.cc,%.o,$(SRCFILES))
TSTFILES := $(pathsubst %.cc,%_t,$(SRCFILES))

DEPFILES := $(pathsubst %.cc,%.d,$(SRCFILES))
TDPFILES := $(pathsubst %,%.d,$(TSTFILES))

ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)


# compiler
# ---------------------------------------------------------------
CCWARN := -Wall -Wextra
CCFLAGS := -

# rules
# ---------------------------------------------------------------
.PHONY: all clean dist check testdrivers todolist
