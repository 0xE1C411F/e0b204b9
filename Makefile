# files
# ---------------------------------------------------------------
AUXFILES := Makefile README.md LICENSE

SRCDIR := src
TSTDIR := tests
HELPTSTDIR := $(TSTDIR)/helpers
UNITTSTDIR := $(TSTDIR)/unit
PERFTSTDIR := $(TSTDIR)/perf

SRCFILES := $(shell find $(SRCDIR) -type f -name "*.cc")
HDRFILES := $(shell find $(SRCDIR) -type f -name "*.h")

SRCTSTFILES := $(shell find $(TSTDIR) -type f -name "*.cc")
HDRTSTFILES := $(shell find $(TSTDIR) -type f -name "*.h")

SRCHELPTSTFILES := $(shell find $(HELPTSTDIR) -type f -name "*.cc")
SRCUNITTSTFILES := $(shell find $(UNITTSTDIR) -type f -name "*.cc")
SRCPERFTSTFILES := $(shell find $(PERFTSTDIR) -type f -name "*.cc")

OBJFILES := $(patsubst %.cc,%.o,$(SRCFILES))
HELPTSTFILES := $(patsubst %.cc,%_ht,$(SRCHELPTSTFILES))
UNITTSTFILES := $(patsubst %.cc,%_ut,$(SRCUNITTSTFILES))
PERFTSTFILES := $(patsubst %.cc,%_pt,$(SRCPERFTSTFILES))
TSTFILES := $(HELPTSTFILES) $(UNITTSTFILES) $(PERFTSTFILES)

DEPFILES := $(patsubst %.cc,%.d,$(SRCFILES))
TDPFILES := $(patsubst %,%.d,$(TSTFILES))
-include $(DEPFILES) $(TDPFILES)

ALLFILES := $(SRCFILES) $(SRCTSTFILES) $(HDRFILES) $(HDRTSTFILES) $(AUXFILES)


# compiler
# ---------------------------------------------------------------
CC := clang++
CCWARN := -Wall -Wextra
CCFLAGS := --std=c++20 $(CCWARN) -I$(SRCDIR)
CCTESTFLAGS := -I$(TSTDIR)
CCUNITTSTFLAGS := $(CCTESTFLAGS) -fsanitize=address
CCPERFTSTFLAGS := $(CCTESTFLAGS)

# rules
# ---------------------------------------------------------------
.PHONY: all config dependencies clean dist unittests perftests unittstfiles perftstfiles todolist

all: e0b204b9.a

config:
	@$(RM) -f compile_commands.json; $(MAKE) -s clean; bear -- $(MAKE) -s dependencies

dependencies: all unittstfiles perftstfiles
	
e0b204b9.a: $(OBJFILES)
	@ar r e0b204b9.a $?

$(HELPTSTDIR)/e0b204b9_th.a: $(HELPTSTFILES)
	@ar r $(HELPTSTDIR)/e0b204b9_th.a $?

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) $(TDPFILES) e0b204b9.a $(HELPTSTDIR)/e0b204b9_th.a e0b204b9.tgz)

dist:
	@tar czf e0b204b9.tgz $(ALLFILES)

unittests: unittstfiles
	-@rc=0; count=0;\
		echo; echo "[UNIT TEST SESSION]"; echo;\
		for file in $(UNITTSTFILES);\
		do echo -n " > ";\
		echo -n "$$file ";\
		./$$file; outcome=`expr $$?`;\
		[[ $$outcome == 0 ]] && echo -n "(passed)" || { echo -n "FAILED $$outcome error"; rc=`expr $$rc + 1`; };\
		[[ $$outcome -le 1 ]] && echo || echo s;\
		count=`expr $$count + 1`;\
		done;\
		echo; echo "[ERRORS] $$rc / $$count"

perftests: perftstfiles
	-@rc=0; count=0;\
		echo; echo "[PERF TEST SESSION]"; echo;\
		for file in $(PERFTSTFILES);\
		do echo -n " > ";\
		echo -n "$$file ";\
		./$$file; outcome=`expr $$?`;\
		[[ $$outcome == 0 ]] && echo -n "(passed)" || { echo -n "FAILED $$outcome error"; rc=`expr $$rc + 1`; };\
		[[ $$outcome -le 1 ]] && echo || echo s;\
		count=`expr $$count + 1`;\
		done;\
		echo; echo "[ERRORS] $$rc / $$count"

unittstfiles: $(UNITTSTFILES) $(HELPTSTFILES)

perftstfiles: $(PERFTSTFILES) $(HELPTSTFILES)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO $$file; done; true

%.o: %.cc Makefile
	@$(CC) $(CCFLAGS) -MMD -MP -c $< -o $@

%_ut: %.cc Makefile e0b204b9.a $(HELPTSTDIR)/e0b204b9_th.a
	@$(CC) $(CCFLAGS) $(CCUNITTSTFLAGS) -MMD -MP $< e0b204b9.a $(HELPTSTDIR)/e0b204b9_th.a -o $@

%_pt: %.cc Makefile e0b204b9.a $(HELPTSTDIR)/e0b204b9_th.a
	@$(CC) $(CCFLAGS) $(CCPERFTSTFLAGS) -MMD -MP $< e0b204b9.a $(HELPTSTDIR)/e0b204b9_th.a -o $@

%_ht: %.cc Makefile e0b204b9.a
	@$(CC) $(CCFLAGS) $(CCPERFTSTFLAGS) -MMD -MP -c $< e0b204b9.a -o $@
