# files
# ---------------------------------------------------------------
AUXFILES := Makefile README.md LICENSE
PROJDIRS := lib

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cc")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")

OBJFILES := $(patsubst %.cc,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.cc,%_t,$(SRCFILES))

DEPFILES := $(patsubst %.cc,%.d,$(SRCFILES))
TDPFILES := $(patsubst %,%.d,$(TSTFILES))
-include $(DEPFILES) $(TDPFILES)

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
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) $(TDPFILES))

package:
	@tar czf e0b204b9.tgz $(ALLFILES)

unittest: testfiles
	-@rc=0; count=0;\
		echo; echo "[TEST SESSION]"; echo;\
		for file in $(TSTFILES);\
		do echo -n " UNIT_TEST ";\
		sourcename=$${file::-2};\
		echo -n "$$sourcename ";\
		./$$file; outcome=`expr $$?`;\
		[[ $$outcome == 0 ]] && echo "(passed)" || { echo -n "FAILED $$outcome error"; rc=`expr $$rc + 1`; };\
		[[ $$outcome == 1 ]] && echo || echo s;\
		count=`expr $$count + 1`;\
		done;\
		echo; echo "[ERRORS] $$rc / $$count"

testfiles: $(TSTFILES)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

%.o: %.cc Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%_t: %.cc Makefile
	@$(CC) $(CFLAGS) -MMD -MP -DUNIT_TEST $< -o $@

