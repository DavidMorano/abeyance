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

LIBS +=


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


OBJ0= sialnum.o sialpha.o sibasename.o sibreak.o
OBJ1= sixchr.o sicasechr.o sicite.o sidigit.o 
OBJ2= sihyphen.o silbrace.o sileader.o
OBJ3= siskipwhite.o sispan.o sisub.o
OBJ4= sifext.o sinext.o
OBJ5= sidquote.o siterm.o

OBJA= obj0.o obj1.o obj2.o 
OBJB= obj3.o obj4.o obj5.o

OBJ= obja.o objb.o


.SUFFIXES:		.hh .ii .ccm


default:		$(T).o

all:			$(ALL)


.c.i:
	$(CPP) $(CPPFLAGS) $< > $(*).i

.cc.ii:
	$(CPP) $(CPPFLAGS) $< > $(*).ii

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

$(T).nm:		$(T).so
	$(NM) $(NMFLAGS) $(T).so > $(T).nm

$(T).order:		$(OBJ) $(T).a
	$(LORDER) $(T).a | $(TSORT) > $(T).order
	$(RM) $(T).a
	while read O ; do $(AR) $(ARFLAGS) -cr $(T).a $${O} ; done < $(T).order

again:
	$(RM) $(ALL)

clean:
	makeclean $(ALL)

control:
	(uname -n ; date) > Control


obj0.o:			$(OBJ0)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ0)

obj1.o:			$(OBJ1)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ1)

obj2.o:			$(OBJ2)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ2)

obj3.o:			$(OBJ3)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ3)

obj4.o:			$(OBJ4)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ4)

obj5.o:			$(OBJ5)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ5)


obja.o:			$(OBJA)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJA)

objb.o:			$(OBJB)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJB)


sifext.o:		sifext.cc sifext.h	$(INCS)
sialnum.o:		sialnum.cc		$(INCS)
sialpha.o:		sialpha.cc		$(INCS)
sibasename.o:		sibasename.cc		$(INCS)
sibreak.o:		sibreak.cc		$(INCS)
sicasechr.o:		sicasechr.cc		$(INCS)
sicite.o:		sicite.cc		$(INCS)
sidigit.o:		sidigit.cc		$(INCS)
sidquote.o:		sidquote.cc		$(INCS)
sihyphen.o:		sihyphen.cc		$(INCS)
silbrace.o:		silbrace.cc		$(INCS)
sileader.o:		sileader.cc		$(INCS)
sinext.o:		sinext.cc		$(INCS)
siskipwhite.o:		siskipwhite.cc		$(INCS)
sispan.o:		sispan.cc		$(INCS)
sisub.o:		sisub.cc		$(INCS)
siterm.o:		siterm.cc		$(INCS)
sixchr.o:		sixchr.cc		$(INCS)


