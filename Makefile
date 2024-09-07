
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
CC := clang++
CCWARN := -Wall -Wextra
CCFLAGS := --std=c++20 $(CCWARN)

# rules
# ---------------------------------------------------------------
.PHONY: clean package unittest testfiles todolist

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES))

package:
	@tar czf e0b204b9.tgz $(ALLFILES)

unittest: testfiles
	-@rc=0; count=0;
		for file in $(TSTFILES); do \
			echo " UNIT_TEST  $$file"; ./$$file; \
			rc=`expr $$rc + $$?`; count=`expr $$count + 1`; \
		done; \
	echo; echo "ERRORS $$rc / $$count"

testfiles: $(TSTFILES)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

%.o: %.cc Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%_t: %.cc Makefile
	@$(CC) $(CFLAGS) -MMD -MP -DUNIT_TEST $< -o $@

-include $(DEPFILES) $(TDPFILES)
