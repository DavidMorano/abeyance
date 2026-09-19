# MAKEFILE (libu)

T= libu

ALL= $(T).o $(T).so


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

INCS += libu.h

MODS += valuelims.o digbufsizes.o uconstants.o 
MODS += libutil.o chrset.o bitgrp.o
MODS += digtab.o xxtostr.o
MODS += usigsets.o usigblock.o umisc.o
MODS += constdiv.o
MODS += usysbasic.o ureserve.cmm vecbool.o

LIBS += -lf -liconv -lproc


OBJ00= syshas.o mailvalues.o endian.o 
OBJ01= aflag.o usysdefs.o
OBJ02= clanguage.o
OBJ03= libutil.o usysconf.o umods.o utimezone.o

OBJ04= utimeutil.o
OBJ05= ulogerror.o ischx.o ulimits.o
OBJ06= ulibvals.o uconstants.o usupport.o
OBJ07= umem.o usigsets.o usigblock.o umisc.o

OBJ08= usys.o usyscallbase.o usysutility.o 
OBJ09= uregfork.o uatfork.o uopen.o 
OBJ10= uipc.o 
OBJ11= ustr.o uobjlock.o ureserve.o

OBJ12= usysflag.o usysdata.o usysauxinfo.o 
OBJ13= ufileop.o ufiledesc.o 
OBJ14= um.o uproc.o ucodenames.o
OBJ15= usysop.o uchartype.o

OBJ16= syswords.o varnames.o
OBJ17= ptx.o sigblocker.o
OBJ18= stdclib.o
OBJ19= stdfnames.o stdfiles.o

OBJ20= uinet.o ustream.o
OBJ21= strnul.o intx.o chrset.o 
OBJ22= ugetloadavg.o uiconv.o bitgrp.o
OBJ23= syscontain.o 

OBJ24= posixdir.o nulstr.o vecbool.o
OBJ25= fonce.o filerec.o
OBJ26= ustd.o ugetx.o
OBJ27= ucomposite.o upt.o ucmpx.o

OBJ28= bitmanip.o findbit.o baops.o
OBJ29= clockids.o filetypes.o funcodes.o 
OBJ30= binchunk.o conintx.o udiv.o stdintx.o
OBJ31= ccfile.o readln.o dprint.o

OBJ32= muldigs.o varithmetic.o xxtostr.o
OBJ33= intext.o cmporders.o localmisc.o
OBJ34= exitcodes.o stacktypes.o sysconfcmds.o
OBJ35= utmptypes.o utmpsizes.o usyscalls.o

OBJ36= mapex.o deb.o
OBJ37= syspredefined.o
OBJ38= typecodes.o charnames.o
OBJ39= strtox.o atox.o

OBJ40= ascii.o ubufdefs.o vardefs.o
OBJ41= memord.o
OBJ42=
OBJ43=

OBJA= obj00.o obj01.o obj02.o obj03.o
OBJB= obj04.o obj05.o obj06.o obj07.o
OBJC= obj08.o obj09.o obj10.o obj11.o
OBJD= obj12.o obj13.o obj14.o obj15.o
OBJE= obj16.o obj17.o obj18.o obj19.o
OBJF= obj20.o obj21.o obj22.o obj23.o
OBJG= obj24.o obj25.o obj26.o obj27.o
OBJH= obj28.o obj29.o obj30.o obj31.o
OBJI= obj32.o obj33.o obj34.o obj35.o
OBJJ= obj36.o obj37.o obj38.o obj39.o
OBJK= obj40.o

OBJ += obja.o objb.o objc.o objd.o 
OBJ += obje.o objf.o objg.o objh.o
OBJ += obji.o objj.o


INCDIRS=
LIBDIRS= -L lib

RUNINFO= -rpath $(RUNDIR)
LIBINFO= $(LIBDIRS) $(LIBS)

# flag setting
CPPFLAGS	?= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS		?= $(MAKECFLAGS)
CXXFLAGS	?= $(MAKECXXFLAGS)
ARFLAGS		?= $(MAKEARFLAGS)
LDFLAGS		?= $(MAKELDFLAGS)

#SOFL= -shared -Xlinker -flat_namespace -Xlinker -undefined -Xlinker suppress
#SOFL= -shared -Xlinker -undefined -Xlinker dynamic_lookup
SOFL= -shared


.SUFFIXES:		.hh .ii .iim .ccm


default:		$(T).o

all:			$(ALL)

so:			$(T).so


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
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<


$(T).o:			$(OBJ) Makefile $(INCS)
	$(LD) -r -o $@ $(LDFLAGS) $(OBJ)

$(T).so:		$(OBJ) Makefile $(INCS)
	$(LD) -o $@ $(SOFL) $(LDFLAGS) $(OBJ) $(LIBINFO)

$(T).nm:		$(T).o
	$(NM) $(NMFLAGS) $(T).o > $(T).nm

install-pre:
	filefind . -s h | makenewer -af - -d $(INCDIR)

install:		$(ALL) Makefile
	install -S -p -m 0775 $(T).so $(LIBDIR)

install-incs:		$(INSTALLINCS)
	makenewer $(INSTALLINCS) $(INCDIR)

safe:
	makesafe -v=3 -I $(INCDIR) $(OBJ)

again:
	rm -f $(ALL)

clean:
	makeclean $(ALL)
	rmsubpat ischx findbit typecodes bitmanip bitgrp chrset
	rmobj

control:
	(uname -n ; date) > Control


obj00.o:		$(OBJ00)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj01.o:		$(OBJ01)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj02.o:		$(OBJ02)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj03.o:		$(OBJ03)
	$(LD) -r -o $@ $(LDFLAGS) $^


obj04.o:		$(OBJ04)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj05.o:		$(OBJ05)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj06.o:		$(OBJ06)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj07.o:		$(OBJ07)
	$(LD) -r -o $@ $(LDFLAGS) $^


obj08.o:		$(OBJ08)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj09.o:		$(OBJ09)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj10.o:		$(OBJ10)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj11.o:		$(OBJ11)
	$(LD) -r -o $@ $(LDFLAGS) $^


obj12.o:		$(OBJ12)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj13.o:		$(OBJ13)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj14.o:		$(OBJ14)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj15.o:		$(OBJ15)
	$(LD) -r -o $@ $(LDFLAGS) $^


obj16.o:		$(OBJ16)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj17.o:		$(OBJ17)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj18.o:		$(OBJ18)
	$(LD) -r -o $@ $(LDFLAGS) $^

obj19.o:		$(OBJ19)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj20.o:		$(OBJ20)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj21.o:		$(OBJ21)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj22.o:		$(OBJ22)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj23.o:		$(OBJ23)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj24.o:		$(OBJ24)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj25.o:		$(OBJ25)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj26.o:		$(OBJ26)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj27.o:		$(OBJ27)
	$(LD) -r $(LDFLAGS) -o $@ $^


obj28.o:		$(OBJ28)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj29.o:		$(OBJ29)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj30.o:		$(OBJ30)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj31.o:		$(OBJ31)
	$(LD) -r $(LDFLAGS) -o $@ $^


obj32.o:		$(OBJ32)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj33.o:		$(OBJ33)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj34.o:		$(OBJ34)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj35.o:		$(OBJ35)
	$(LD) -r $(LDFLAGS) -o $@ $^


obj36.o:		$(OBJ36)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj37.o:		$(OBJ37)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj38.o:		$(OBJ38)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj39.o:		$(OBJ39)
	$(LD) -r $(LDFLAGS) -o $@ $^


obja.o:			$(OBJA)
	$(LD) -r -o $@ $(LDFLAGS) $^

objb.o:			$(OBJB)
	$(LD) -r -o $@ $(LDFLAGS) $^

objc.o:			$(OBJC)
	$(LD) -r -o $@ $(LDFLAGS) $^

objd.o:			$(OBJD)
	$(LD) -r -o $@ $(LDFLAGS) $^

obje.o:			$(OBJE)
	$(LD) -r -o $@ $(LDFLAGS) $^

objf.o:			$(OBJF)
	$(LD) -r -o $@ $(LDFLAGS) $^

objg.o:			$(OBJG)
	$(LD) -r -o $@ $(LDFLAGS) $^

objh.o:			$(OBJH)
	$(LD) -r -o $@ $(LDFLAGS) $^

obji.o:			$(OBJI)
	$(LD) -r -o $@ $(LDFLAGS) $^

objj.o:			$(OBJJ)
	$(LD) -r -o $@ $(LDFLAGS) $^

objk.o:			$(OBJK)
	$(LD) -r -o $@ $(LDFLAGS) $^

objl.o:			$(OBJL)
	$(LD) -r -o $@ $(LDFLAGS) $^

objm.o:			$(OBJM)
	$(LD) -r -o $@ $(LDFLAGS) $^

objn.o:			$(OBJN)
	$(LD) -r -o $@ $(LDFLAGS) $^


# SUPPORT objects
syshas.o:		syshas.cc	syshas.h		$(INCS)
usyscalls.o:		usyscalls.cc	usyscalls.h		$(INCS)
ustsdefs.o:		usysdefs.cc	usysdefs.h		$(INCS)
clanguage.o:		clanguage.cc	clanguage.h		$(INCS)
exitcodes.o:		exitcodes.cc	exitcodes.h		$(INCS)
stacktypes.o:		stacktypes.cc	stacktypes.h		$(INCS)
aflag.o:		aflag.cc	aflag.hh		$(INCS)

# SUPPORT helpers
usysflag.o:		usysflag.cc	usysflag.h		$(INCS)
ulimits.o:		ulimits.cc	ulimits.h		$(INCS)
utimeout.o:		utimeout.c	utimeout.h		$(INCS)
utimeouts.o:		utimeouts.cc	utimeouts.h		$(INCS)
utimeoutdefs.o:		utimeoutdefs.cc	utimeoutdefs.h		$(INCS)
usyscallbase.o:		usyscallbase.cc	usyscallbase.hh		$(INCS)
usysutility.o:		usysutility.cc	usysutility.hh		$(INCS)
usysdata.o:		usysdata.cc	usysdata.h		$(INCS)
ulogerror.o:		ulogerror.cc	ulogerror.h		$(INCS)

# requires USYSBASIC
uatfork.o:		umods.o usigblock.o
uatfork.o:		uatfork.cc uatfork.h umods.o		$(INCS)
uregfork.o:		umods.o uregfork.cc uregfork.hh		$(INCS)
uobjlock.o:		umods.o uobjlock.cc uobjlock.cc		$(INCS)

# UTIMEUTIL
utimeutil.o:		utimeutil.dir
utimeutil.dir:
	makesubdir $@

# UCONSTANTS
uconstants.o:		uconstants.dir
uconstants.dir:
	makesubdir $@

# USYS
usys.o:			usys.dir
usys.dir:
	makesubdir $@

# USTD
ustd.o:			ustd.dir
ustd.dir:
	makesubdir $@

# USYSCONF
usysconf.o:		usysconf.dir
usysconf.dir:
	makesubdir $@

# UTIMEZONE
utimezone.o:		utimezone.dir
utimezone.dir:
	makesubdir $@

# UPROC
uproc.o:		uproc.dir
uproc.dir:
	makesubdir $@

# UFDLOCK
uopen.o:		uopen.dir
uopen.dir:
	makesubdir $@

# UFILEDESC
ufiledesc.o:		ufiledesc.dir
ufiledesc.dir:
	makesubdir $@

# UFILEOP
ufileop.o:		ufileop.dir
ufileop.dir:
	makesubdir $@

# UIPC
uipc.o:			uipc.dir
uipc.dir:
	makesubdir $@

# USYSAUXINFO
usysauxinfo.o:		usysauxinfo.dir
usysauxinfo.dir:
	makesubdir $@

# UPT
upt.o:		upt.dir
upt.dir:
	makesubdir $@

# USYNC
ugetx.o:		ugetx.dir
ugetx.dir:
	makesubdir $@

# INTX
intx.o:			intx.dir
intx.dir:
	makesubdir $@

# UCONTAIN
syscontain.o:		syscontain.dir
syscontain.dir:
	makesubdir $@

# UMODS
umods.o:		umods.dir
umods.dir:
	makesubdir $@

# UMISC
umisc.o:		umisc.dir
umisc.dir:
	makesubdir $@

# URESERVE
ureserve.o:		ureserve.dir
ureserve.dir:
	makesubdir $@

# USUPPORT
usupport.o:		usupport.dir ischx.o
usupport.dir:
	makesubdir $@

# ULIBVALS
ulibvals.o:		ulibvals.dir
ulibvals.dir:
	makesubdir $@

# UCOMPOSITE
ucomposite.o:		ucomposite.dir
ucomposite.dir:
	makesubdir $@

# USIGSET
usigsets.o:		usigsets.dir
usigsets.dir:
	makesubdir $@

# USIREAM
ustream.o:		ustream.dir
ustream.dir:
	makesubdir $@

# UCMPX
ucmpx.o:		ucmpx.dir
ucmpx.dir:
	makesubdir $@

usigblock.o:		usigblock.ccm			$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

ucodenames.o:		ucodenames.cc	ucodenames.h	$(INCS)

# POSIX® synchronization mechanisms
ptx.o:			ptx.dir
ptx.dir:
	makesubdir $@

# LIBUTIL
libutil.o:		libutil.dir
libutil.dir:
	makesubdir $@

# VARITHMETIC
varithmetic.o:		varithmetic.dir 
varithmetic.dir:	bitmanip.o muldigs.o
	makesubdir $@

# INREXT
intext.o:		intext.dir	
intext.dir:		varithmetic.o loadvals.o
	makesubdir $@

# DEBUG
deb.o:			deb.dir
deb.dir:
	makesubdir $@

# VECBOOL
vecbool.o:		vecbool.dir
vecbool.dir:
	makesubdir $@

# POSIXDIR
posixdir.o:		posixdir.dir
posixdir.dir:
	makesubdir $@

# FONCE
fonce.o:		fonce.dir
fonce.dir:
	makesubdir $@

# FILEREC
filerec.o:		filerec.dir
filerec.dir:
	makesubdir $@

# misc-objects
chrset.o:		chrset.ccm					$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

bitgrp.o:		bitgrp.ccm					$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

nulstr.o:		nulstr.cc	nulstr.h			$(INCS)
binchunk.o:		binchunk.cc	binchunk.hh			$(INCS)
sigblocker.o:		sigblocker.cc	sigblocker.h			$(INCS)

# OTHER subroutine-groups
umem.o:			umem.cc		umem.hh				$(INCS)
um.o:			um.cc		um.h				$(INCS)
usysop.o:		usysop.cc	usysop.h			$(INCS)
ugetloadavg.o:		ugetloadavg.cc	ugetloadavg.h			$(INCS)
uinet.o:		uinet.cc	uinet.h				$(INCS)
uiconv.o:		uiconv.cc	uiconv.h			$(INCS)
uchartype.o:		uchartype.cc	uchartype.h			${INCS}

# CONSTANTS
endian.o:		endian.cc	endian.h			$(INCS)
syswords.o:		syswords.cc	syswords.hh			$(INCS)
varnames.o:		varnames.cc	varnames.hh			$(INCS)
stdfiles.o:		stdfiles.cc	stdfiles.h			$(INCS)
stdfnames.o:		stdfnames.cc	stdfnames.h			$(INCS)
mailvalues.o:		mailvalues.cc	mailvalues.hh			$(INCS)

# IDS of-various-sorts
clockids.o:		clockids.cc	clockids.hh			$(INCS)
filetypes.o:		filetypes.cc	filetypes.h			$(INCS)
funcodes.o:		funcodes.cc	funcodes.h			$(INCS)

# BITS
baops.o:		baops.c		baops.h				$(INCS)

bitmanip.o:		bitmanip.ccm					$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

findbit.o:		findbit.ccm					$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

# STRING handling
strtox.o:		strtox.cc	strtox.h bitmanip.o		$(INCS)
strnul.o:		strnul.cc	strnul.hh			$(INCS)
atox.o:			atox.cc		atox.h				$(INCS)

# MISC
stdclib.o:		stdclib.cc	stdclib.hh			$(INCS)
ccfile.o:		ccfile.cc	ccfile.hh			$(INCS)
readln.o:		readln.cc	readln.hh			$(INCS)
dprint.o:		dprint.cc	dprint.hh			$(INCS)

# ARITHMETIC
muldigs.o:		muldigs.ccm
loadvals.o:		loadvals.ccm

ischx.o:		ischx0.o ischx1.o
	$(LD) -r $(LDFLAGS) -o $@ $^

ischx0.o:		ischx.ccm	ischx.hh			$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

ischx1.o:		ischx1.cc	ischx0.o			$(INCS)
	$(COMPILE.cc) $<

udiv.o:			udiv.ccm	udiv.hh				$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

typecodes.o:		typecodes.ccm	ffbs.h				$(INCS)
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

# singles
conintx.o:		conintx.cc		conintx.hh		$(INCS)
stdintx.o:		stdintx.cc		stdintx.h		$(INCS)
xxtostr.o:		xxtostr.cc		xxtostr.h		$(INCS)
getbyte.o:		getbyte.ccm		getbyte.hh		$(INCS)

# various types
utmptypes.o:		utmptypes.cc		utmptypes.hh		$(INCS)
utmpsizes.o:		utmpsizes.cc		utmpsizes.hh		$(INCS)
cmporders.o:		cmporders.cc		cmporders.h		$(INCS)
localmisc.o:		localmisc.cc		localmisc.h		$(INCS)
mapex.o:		mapex.cc		mapex.h			$(INCS)
sysconfcmds.o:		sysconfcmds.cc		sysconfcmds.h		$(INCS)
charnames.o:		charnames.cc		charnames.h		$(INCS)
syspredefined.o:	syspredefined.cc	syspredefined.h		$(INCS)

ascii.o:		ascii.cc		ascii.h			$(INCS)
ubufdefs.o:		ubufdefs.cc		ubufdefs.h		$(INCS)
vardefs.o:		vardefs.cc		vardefs.h		$(INCS)
memord.o:		memord.cc		memord.hh		$(INCS)


