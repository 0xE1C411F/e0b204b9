# files
# ---------------------------------------------------------------
AUXFILES := Makefile README.md LICENSE

SRCDIR := src
TSTDIR := tst

SRCFILES := $(shell find $(SRCDIR) -type f -name "*.cc")
SRCTSTFILES := $(shell find $(TSTDIR) -type f -name "*.cc")
HDRFILES := $(shell find $(SRCDIR) -type f -name "*.h")

OBJFILES := $(patsubst %.cc,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.cc,%_t,$(SRCTSTFILES))

DEPFILES := $(patsubst %.cc,%.d,$(SRCFILES))
TDPFILES := $(patsubst %,%.d,$(TSTFILES))
-include $(DEPFILES) $(TDPFILES)

ALLFILES := $(SRCFILES) $(SRCTSTFILES) $(HDRFILES) $(AUXFILES)


# compiler
# ---------------------------------------------------------------
CC := clang++
CCWARN := -Wall -Wextra
CCFLAGS := --std=c++20 $(CCWARN) -I$(SRCDIR)

# rules
# ---------------------------------------------------------------
.PHONY: all clean dist unittests testfiles todolist

all: e0b204b9.a

e0b204b9.a: $(OBJFILES)
	@ar r e0b204b9.a $?

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) $(TDPFILES) e0b204b9.a e0b204b9.tgz)

dist:
	@tar czf e0b204b9.tgz $(ALLFILES)

unittests: testfiles
	-@rc=0; count=0;\
		echo; echo "[TEST SESSION]"; echo;\
		for file in $(TSTFILES);\
		do echo -n " UNIT_TEST ";\
		sourcename=$${file::-2};\
		echo -n "$$sourcename ";\
		./$$file; outcome=`expr $$?`;\
		[[ $$outcome == 0 ]] && echo -n "(passed)" || { echo -n "FAILED $$outcome error"; rc=`expr $$rc + 1`; };\
		[[ $$outcome -le 1 ]] && echo || echo s;\
		count=`expr $$count + 1`;\
		done;\
		echo; echo "[ERRORS] $$rc / $$count"

testfiles: $(TSTFILES)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO $$file; done; true

%.o: %.cc Makefile
	@$(CC) $(CCFLAGS) -MMD -MP -c $< -o $@

%_t: %.cc Makefile e0b204b9.a
	@$(CC) $(CCFLAGS) -I$(TSTDIR) -MMD -MP $< e0b204b9.a -o $@

