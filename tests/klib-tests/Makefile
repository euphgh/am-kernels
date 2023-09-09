.PHONY: all run gdb clean latest $(ALL)

RESULT = .result
$(shell > $(RESULT))

COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

ALL := $(basename $(notdir $(shell find tests/. -name "*.c")))
ALL := $(filter-out $(SUB), $(ALL))

all: $(addprefix Makefile., $(ALL))
	@echo "" $(ALL)

$(ALL): %: Makefile.%

Makefile.%: tests/%.c latest
	@echo -e "NAME = $*\nSRCS = $<\ninclude $${AM_HOME}/Makefile" > $@
	@if make -s -f $@ ARCH=$(ARCH) $(MAKECMDGOALS) -j 8; then \
		printf "[%14s] $(COLOR_GREEN)PASS!$(COLOR_NONE)\n" $* >> $(RESULT); \
	else \
		printf "[%14s] $(COLOR_RED)FAIL!$(COLOR_NONE)\n" $* >> $(RESULT); \
		exit 1;\
	fi
	@if [ "$*" = "sprintf" ]; then rm -f tests/sprintf.c; fi
	-@rm -f Makefile.$*

tests/sprintf.c: tests/GenFmtPrintTest.c
	@mkdir -p build
	@gcc $^ -o build/GenFmtPrintTest.out
	@build/GenFmtPrintTest.out | clang-format > $@

run: all
	@cat $(RESULT)
	@rm $(RESULT)

image: all

gdb: all

clean:
	rm -rf Makefile.* build/

latest:
