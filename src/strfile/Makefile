# MAKEFILE (strfile)

T= strfile

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

INCS += strfile.h

MODS +=

LIBS +=


OBJ0= strfilemk.o strfilemks.o
OBJ1= 
OBJ2= 
OBJ3= 

OBJA= obj0.o 

OBJ= obja.o 


INCDIRS +=
LIBDIRS += -L lib

RUNINFO= -rpath $(RUNDIR)
LIBINFO= $(LIBDIRS) $(LIBS)

# flag setting
CPPFLAGS	?= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS		?= $(MAKECFLAGS)
CXXFLAGS	?= $(MAKECXXFLAGS)
ARFLAGS		?= $(MAKEARFLAGS)
LDFLAGS		?= $(MAKELDFLAGS)


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
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<


$(T).o:			$(OBJ)
	$(LD) -r $(LDFLAGS) -o $@ $^

$(T).nm:		$(T).o
	$(NM) $(NMFLAGS) $(T).o > $(T).nm

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

obj6.o:			$(OBJ6)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ6)

obj7.o:			$(OBJ7)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJ7)


obja.o:			$(OBJA)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJA)

objb.o:			$(OBJB)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJB)


srfilemk.o:		strfilemk.cc	strfilemk.h	$(INCS)
srfilemks.o:		strfilemks.cc	strfilemks.h	$(INCS)


