MAKEFLAGS+= --no-print-directory
DEFAULT_OS=linux

all:
	@$(MAKE) -f Makefile.$(DEFAULT_OS)

linux:
	@$(MAKE) -f Makefile.linux

windows:
	@$(MAKE) -f Makefile.windows

clean:
	-rm -f obj/*
	-rm -f obj-win/*

%:
	$(MAKE) -f Makefile.$(DEFAULT_OS) $@
