# MAKEFILE (libdigest)

T= libdigest

ALL= $(T).o $(T).a


BINDIR= $(REPOROOT)/bin
INCDIR= $(REPOROOT)/include
LIBDIR= $(REPOROOT)/lib
MANDIR= $(REPOROOT)/man
INFODIR= $(REPOROOT)/info
HELPDIR= $(REPOROOT)/share/help


CRTDIR= $(CGS_CRTDIR)
VALDIR= $(CGS_VALDIR)
LIBDIR= $(CGS_LIBDIR)

CPP= cpp
CC= gcc
CXX= gpp
LD= gld
RANLIB= granlib
AR= gar
NM= gnm
COV= gcov

LORDER= lorder
TSORT= tsort
LINT= lint
RM= rm -f
TOUCH= touch
LINT= lint


DEFS=

LDRPATH= $(EXTRA)/lib

LIBDIRS= -L$(LIBDIR)

LIBS=


# flag setting
CPPFLAGS= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS= $(MAKECFLAGS)
CCFLAGS= $(MAKECCFLAGS)
ARFLAGS= $(MAKEARFLAGS)
LDFLAGS= $(MAKELDFLAGS)


INCS= six.h


OBJ0_SIX= sialnum.o sialpha.o sibasename.o sibreak.o
OBJ1_SIX= sixchr.o sicasechr.o sicite.o sidigit.o sidquote.o
OBJ2_SIX= sihyphen.o silbrace.o sileader.o sinext.o
OBJ3_SIX= siskipwhite.o sispan.o sisub.o sicasesub.o siterm.o


OBJA_SIX= obj0_six.o obj1_six.o
OBJB_SIX= obj2_six.o obj3_six.o

OBJ_SIX= $(OBJA_SIX) $(OBJB_SIX)


default:		$(T).a

all:			$(ALL)

.c.ln:
	$(LINT) -c $(LINTFLAGS) $(CPPFLAGS) $<

.c.ls:
	$(LINT) $(LINTFLAGS) $(CPPFLAGS) $<

.c.i:
	$(CPP) $(CPPFLAGS) $< > $(*).i

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

.cc.o:
	$(CXX)  $(CPPFLAGS) $(CCFLAGS) -c $<


$(T).o:			$(OBJ_SIX)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ_SIX)

$(T).a:			$(OBJ_SIX)
	$(AR) $(ARFLAGS) -rc $@ $?

$(T).nm:		$(T).so
	$(NM) $(NMFLAGS) $(T).so > $(T).nm

$(T).order:		$(OBJ) $(T).a
	$(LORDER) $(T).a | $(TSORT) > $(T).order
	$(RM) $(T).a
	while read O ; do $(AR) $(ARFLAGS) -cr $(T).a $${O} ; done < $(T).order

again:
	rm -f $(ALL)

clean:
	makeclean $(ALL)

control:
	(uname -n ; date) > Control

obj0_six.o:	$(OBJ0_SIX)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ0_SIX)

obj1_six.o:	$(OBJ1_SIX)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ1_SIX)

obj2_six.o:	$(OBJ2_SIX)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ2_SIX)

obj3_six.o:	$(OBJ3_SIX)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ3_SIX)


