# MAKEFILE (who)

T= who

ALL= $(T).x
EXTRA ?= /usr/extra
LOCAL ?= /opt/local


BINDIR		?= $(REPOROOT)/bin
INCDIR		?= $(REPOROOT)/include
LIBDIR		?= $(REPOROOT)/lib
MANDIR		?= $(REPOROOT)/man
INFODIR		?= $(REPOROOT)/info
HELPDIR		?= $(REPOROOT)/share/help
CRTDIR		?= $(CGS_CRTDIR)
VALDIR		?= $(CGS_VALDIR)
RUNDIR		?= $(CGS_RUNDIR)

CPP		?= cpp
CC		?= gcc
CXX		?= gxx
LD		?= gld
RANLIB		?= granlib
AR		?= gar
NM		?= gnm
COV		?= gcov
LORDER		?= lorder
TSORT		?= tsort
LINT		?= lint
RM		?= rm -f
TOUCH		?= touch
LINT		?= lint


DEFS +=

INCS +=

MODS +=

LIBS += -luo -lu

ELIBS += -luo -lproc -liconv


DEPMODS += libutil.o
DEPMODS += umisc.o ureserve.o

OBJ= who_main.o


INCDIRS= -I$(LOCAL)/include
LIBDIRS= -L lib

RUNINFO= -rpath $(RUNDIR)
LIBINFO= $(LIBDIRS) $(LIBS)
ELIBINFO= $(EXTRA)/lib/libu.o -L$(EXTRA)/lib $(ELIBS)

# flag setting
CPPFLAGS	?= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS		?= $(MAKECFLAGS)
CXXFLAGS	?= $(MAKECXXFLAGS)
ARFLAGS		?= $(MAKEARFLAGS)
LDFLAGS		?= $(MAKELDFLAGS)


.SUFFIXES:		.hh .ii .iim .ccm


default:		$(T).x

all:			$(ALL)


.c.i:
	$(CPP) $(CPPFLAGS) $< > $(*).i

.cc.ii:
	$(CPP) $(CPPFLAGS) $< > $(*).ii

.ccm.iim:
	$(CPP) $(CPPFLAGS) $< > $(*).iim

.c.s:
	$(CC) -S $(CPPFLAGS) $(CFLAGS) $<

.cc.s:
	$(CXX) -S $(CPPFLAGS) $(CXXFLAGS) $<

.c.o:
	$(COMPILE.c) $<

.cc.o:
	$(COMPILE.cc) $<

.ccm.o:
	makemodule $(*)


consoleid.x:		$(OBJ) Makefile
	$(LD) -o $@ $(LDFLAGS) $(RUNINFO) $(OBJ) $(ELIBINFO)

$(T).x:			$(OBJ) Makefile
	$(LD) -o $@ $(LDFLAGS) $(RUNINFO) $(OBJ) $(LIBINFO)

$(T).o:			$(OBJ) Makefile
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ)

$(T).nm:		$(T).o
	$(NM) $(NMFLAGS) $(T).o > $(T).nm

again:
	rm -f $(ALL)

clean:
	makeclean $(ALL)

control:
	(uname -n ; date) > Control

install:		$(T).x
	makeinstall $(T).x


obj00.o:		$(OBJ00)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj01.o:		$(OBJ01)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj02.o:		$(OBJ02)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj03.o:		$(OBJ03)
	$(LD) -r $(LDFLAGS) -o $@ $^


obja.o:		$(OBJA)
	$(LD) -r $(LDFLAGS) -o $@ $^

objb.o:		$(OBJB)
	$(LD) -r $(LDFLAGS) -o $@ $^

objc.o:		$(OBJC)
	$(LD) -r $(LDFLAGS) -o $@ $^

objd.o:		$(OBJD)
	$(LD) -r $(LDFLAGS) -o $@ $^


who_main.o:		who_main.cc $(DEPMODS)

who_support.o:		who_support.cc

libutil.o:		libutil.dir
libutil.dir:
	makesubdir $@

umisc.o:		umisc.dir
umisc.dir:
	makesubdir $@

ureserve.o:		ureserve.dir
ureserve.dir:
	makesubdir $@


