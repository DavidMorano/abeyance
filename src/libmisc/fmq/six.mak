# MAKEFILES (six)

T= six

ALL= $(T).o


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
CXX		?= gpp
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

INCS += six.h

MODS +=

LIBS +=


OBJ0= sichar.o sicasechr.o 
OBJ1= sicite.o sibasename.o
OBJ2= sihyphen.o silbrace.o sileader.o
OBJ3= sispan.o sispanwht.o 
OBJ4= sifext.o sinext.o sinon.o
OBJ5= sidquote.o sixterm.o siext.o
OBJ6= sixchr.o sixbrk.o sixsub.o siwht.o
OBJ7= sileadzero.o

OBJA= obj0.o obj1.o obj2.o obj3.o 
OBJB= obj4.o obj5.o obj6.o obj7.o

OBJ= obja.o objb.o


INCDIRS +=

LIBDIRS += -L$(LIBDIR)


RUNINFO= -rpath $(RUNDIR)
LIBINFO= $(LIBDIRS) $(LIBS)

# flag setting
CPPFLAGS	?= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS		?= $(MAKECFLAGS)
CXXFLAGS	?= $(MAKECXXFLAGS)
ARFLAGS		?= $(MAKEARFLAGS)
LDFLAGS		?= $(MAKELDFLAGS)


.SUFFIXES:		.hh .ii .iim .ccm


default:		$(T).o

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


$(T).o:			$(OBJ)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ)

$(T).nm:		$(T).o
	$(NM) $(NMFLAGS) $(T).o > $(T).nm

again:
	$(RM) $(ALL)

clean:
	makeclean $(ALL)

control:
	(uname -n ; date) > Control


obj0.o:			$(OBJ0)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj1.o:			$(OBJ1)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj2.o:			$(OBJ2)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj3.o:			$(OBJ3)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj4.o:			$(OBJ4)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj5.o:			$(OBJ5)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj6.o:			$(OBJ6)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj7.o:			$(OBJ7)
	$(LD) -r $(LDFLAGS) -o $@ $^


obja.o:			$(OBJA)
	$(LD) -r $(LDFLAGS) -o $@ $^

objb.o:			$(OBJB)
	$(LD) -r $(LDFLAGS) -o $@ $^


sifext.o:		sifext.cc sifext.h		$(INCS)
sibasename.o:		sibasename.cc			$(INCS)
sicite.o:		sicite.cc			$(INCS)
sidquote.o:		sidquote.cc			$(INCS)
sihyphen.o:		sihyphen.cc			$(INCS)
silbrace.o:		silbrace.cc			$(INCS)
sileader.o:		sileader.cc			$(INCS)
sinext.o:		sinext.cc			$(INCS)
sileadzero.o:		sileadzero.cc			$(INCS)
sispan.o:		sispan.cc	sispan.h	$(INCS)
sispanwht.o:		sispanwht.cc	sispanwht.h	$(INCS)

siext.o:		siext.cc	siext.h		$(INCS)
sixchr.o:		sixchr.cc	sixchr.h	$(INCS)
sixbrk.o:		sixbrk.cc	sixbrk.h	$(INCS)
sixterm.o:		sixterm.cc	sixterm.h	$(INCS)
sixsub.o:		sixsub.cc	sixsub.h	$(INCS)
sicasechr.o:		sicasechr.cc	sicasechr.h	$(INCS)
sinon.o:		sinon.cc	sinon.h		$(INCS)
sichar.o:		sichar.cc	sichar.h	$(INCS)

# SIWHT
siwht.o:		siwht0.o siwht1.o
	$(LD) -r $(LDFLAGS) -o $@ $^

siwht0.o:		siwht.ccm			$(INCS)
	makemodule siwht

siwht1.o:		siwht1.cc siwht.ccm		$(INCS)
	makemodule siwht
	$(COMPILE.cc) $<


