# MAKEFILES (vec)

T= vec

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


DEFS=

INCS= vec.h

LIBS=


INCDIRS += 

LIBDIRS= -L$(LIBDIR)


RUNINFO= -rpath $(RUNDIR)

LIBINFO= $(LIBDIRS) $(LIBS)

# flag setting
CPPFLAGS	?= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS		?= $(MAKECFLAGS)
CXXFLAGS	?= $(MAKECXXFLAGS)
ARFLAGS		?= $(MAKEARFLAGS)
LDFLAGS		?= $(MAKELDFLAGS)


# vecstr
OBJA_VECSTR= vecstr.o vecstr_ext.o
OBJB_VECSTR= vecstr_adduniqs.o vecstr_addpath.o
OBJC_VECSTR= vecstr_loadfile.o vecstr_env.o vecstr_envfile.o 
OBJD_VECSTR= vecstr_adds.o vecstr_addsyms.o vecstr_foilcmp.o
OBJE_VECSTR= vecstr_srvargs.o vecstr_svcargs.o
OBJF_VECSTR= vecstr_loadgrusers.o vecstr_addsubdirs.o

OBJ_VECSTR+= obja_vecstr.o
#OBJ_VECSTR+= obja_vecstr.o objb_vecstr.o objc_vecstr.o
#OBJ_VECSTR+= objd_vecstr.o obje_vecstr.o objf_vecstr.o

# vecpstr
OBJA_VECPSTR= vecpstr.o vecpstr_ext.o
OBJB_VECPSTR= vecpstr_adduniqs.o vecpstr_addpath.o
OBJC_VECPSTR= vecpstr_loadfile.o vecpstr_env.o vecpstr_envfile.o 
OBJD_VECPSTR= vecpstr_adds.o vecpstr_addsyms.o vecpstr_foilcmp.o
OBJE_VECPSTR= vecpstr_srvargs.o vecpstr_svcargs.o
OBJF_VECPSTR= vecpstr_loadgrusers.o vecpstr_addsubdirs.o

OBJ_VECPSTR+= obja_vecpstr.o
#OBJ_VECPSTR+= obja_vecpstr.o objb_vecpstr.o objc_vecpstr.o 
#OBJ_VECPSTR+= objd_vecpstr.o obje_vecpstr.o objf_vecpstr.o 

# VECSTRX
OBJA_VECSTRX= vecstrx_addpath.o vecstrx_adds.o vecstrx_addsubdirs.o
OBJB_VECSTRX= vecstrx_addsyms.o vecstrx_adduniqs.o
OBJC_VECSTRX= vecstrx_env.o vecstrx_envfile.o vecstrx_foilcmp.o
OBJD_VECSTRX= vecstrx_loadgrusers.o vecstrx_loadpjusers.o
OBJE_VECSTRX= vecstrx_srvargs.o vecstrx_svcargs.o
OBJF_VECSTRX= vecstrx_loadfile.o 

OBJ_VECSTRX+= obja_vecstrx.o objb_vecstrx.o objc_vecstrx.o 
OBJ_VECSTRX+= objd_vecstrx.o obje_vecstrx.o objf_vecstrx.o 

# vecobj
OBJA_VECOBJ= vecobj.o
OBJB_VECOBJ= vecobj_recip.o vecobj_strsort.o

OBJ_VECOBJ+= obja_vecobj.o objb_vecobj.o


# vecxx
OBJA_VEC= obj_vecstr.o obj_vecpstr.o obj_vecstrx.o
OBJB_VEC= vechand.o vecitem.o vecsorthand.o
OBJC_VEC= vecint.o veclong.o
OBJD_VEC= recarr.o raqhand.o obj_vecobj.o


OBJ_VEC= obja_vec.o objb_vec.o objc_vec.o objd_vec.o


.SUFFIXES:		.hh .ii


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


$(T).o:			$(OBJ_VEC)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ_VEC)

$(T).nm:		$(T).o
	$(NM) $(NMFLAGS) $(T).so > $(T).nm

$(T).order:		$(OBJ_VEC) $(T).a
	$(LORDER) $(T).a | $(TSORT) > $(T).order
	$(RM) $(T).a
	while read O ; do $(AR) $(ARFLAGS) -cr $(T).a $${O} ; done < $(T).order

again:
	rm -f $(ALL)

clean:
	makeclean $(ALL)

control:
	(uname -n ; date) > Control


obja_vecstr.o:	$(OBJA_VECSTR)
	$(LD) -r -o $@ $(OBJA_VECSTR)
objb_vecstr.o:	$(OBJB_VECSTR)
	$(LD) -r -o $@ $(OBJB_VECSTR)
objc_vecstr.o:	$(OBJC_VECSTR)
	$(LD) -r -o $@ $(OBJC_VECSTR)
objd_vecstr.o:	$(OBJD_VECSTR)
	$(LD) -r -o $@ $(OBJD_VECSTR)
obje_vecstr.o:	$(OBJE_VECSTR)
	$(LD) -r -o $@ $(OBJE_VECSTR)
objf_vecstr.o:	$(OBJF_VECSTR)
	$(LD) -r -o $@ $(OBJF_VECSTR)

obj_vecstr.o:	$(OBJ_VECSTR)
	$(LD) -r -o $@ $(OBJ_VECSTR)

obja_vecpstr.o:	$(OBJA_VECPSTR)
	$(LD) -r -o $@ $(OBJA_VECPSTR)
objb_vecpstr.o:	$(OBJB_VECPSTR)
	$(LD) -r -o $@ $(OBJB_VECPSTR)
objc_vecpstr.o:	$(OBJC_VECPSTR)
	$(LD) -r -o $@ $(OBJC_VECPSTR)
objd_vecpstr.o:	$(OBJD_VECPSTR)
	$(LD) -r -o $@ $(OBJD_VECPSTR)
obje_vecpstr.o:	$(OBJE_VECPSTR)
	$(LD) -r -o $@ $(OBJE_VECPSTR)
objf_vecpstr.o:	$(OBJF_VECPSTR)
	$(LD) -r -o $@ $(OBJF_VECPSTR)

obj_vecpstr.o:	$(OBJ_VECPSTR)
	$(LD) -r -o $@ $(OBJ_VECPSTR)

obja_vecstrx.o:	$(OBJA_VECSTRX)
	$(LD) -r -o $@ $(OBJA_VECSTRX)
objb_vecstrx.o:	$(OBJB_VECSTRX)
	$(LD) -r -o $@ $(OBJB_VECSTRX)
objc_vecstrx.o:	$(OBJC_VECSTRX)
	$(LD) -r -o $@ $(OBJC_VECSTRX)
objd_vecstrx.o:	$(OBJD_VECSTRX)
	$(LD) -r -o $@ $(OBJD_VECSTRX)
obje_vecstrx.o:	$(OBJE_VECSTRX)
	$(LD) -r -o $@ $(OBJE_VECSTRX)
objf_vecstrx.o:	$(OBJF_VECSTRX)
	$(LD) -r -o $@ $(OBJF_VECSTRX)

obj_vecstrx.o:	$(OBJ_VECSTRX)
	$(LD) -r -o $@ $(OBJ_VECSTRX)

obja_vecobj.o:	$(OBJA_VECOBJ)
	$(LD) -r -o $@ $(OBJA_VECOBJ)
objb_vecobj.o:	$(OBJB_VECOBJ)
	$(LD) -r -o $@ $(OBJB_VECOBJ)

obj_vecobj.o:	$(OBJ_VECOBJ)
	$(LD) -r -o $@ $(OBJ_VECOBJ)

obja_vec.o:	$(OBJA_VEC)
	$(LD) -r -o $@ $(OBJA_VEC)
objb_vec.o:	$(OBJB_VEC)
	$(LD) -r -o $@ $(OBJB_VEC)
objc_vec.o:	$(OBJC_VEC)
	$(LD) -r -o $@ $(OBJC_VEC)
objd_vec.o:	$(OBJD_VEC)
	$(LD) -r -o $@ $(OBJD_VEC)


vecstr.o:		vecstr.cc		vecstr.h
vecstr_ext.o:		vecstr_ext.cc		vecstr.h

vecstr_addpath.o:	vecstr_addpath.cc	vecstr.h
vecstr_adds.o:		vecstr_adds.cc		vecstr.h
vecstr_addsubdirs.o:	vecstr_addsubdirs.cc	vecstr.h
vecstr_adduniqs.o:	vecstr_adduniqs.cc	vecstr.h
vecstr_env.o:		vecstr_env.cc		vecstr.h
vecstr_envfile.o:	vecstr_envfile.cc	vecstr.h
vecstr_foilcmp.o:	vecstr_foilcmp.cc	vecstr.h
vecstr_loadfile.o:	vecstr_loadfile.cc	vecstr.h
vecstr_loadgrusers.o:	vecstr_loadgrusers.cc	vecstr.h
vecstr_srvargs.o:	vecstr_srvargs.cc	vecstr.h
vecstr_svcargs.o:	vecstr_svcargs.cc	vecstr.h
vecstr_addsyms.o:	vecstr_addsyms.cc	vecstr.h

vecpstr.o:		vecpstr.cc		vecpstr.h
vecpstr_ext.o:		vecpstr_ext.cc		vecstr.h

vecpstr_addpath.o:	vecpstr_addpath.cc	vecpstr.h
vecpstr_adds.o:		vecpstr_adds.cc		vecpstr.h
vecpstr_addsubdirs.o:	vecpstr_addsubdirs.cc	vecpstr.h
vecpstr_adduniqs.o:	vecpstr_adduniqs.cc	vecpstr.h
vecpstr_env.o:		vecpstr_env.cc		vecpstr.h
vecpstr_envfile.o:	vecpstr_envfile.cc	vecpstr.h
vecpstr_foilcmp.o:	vecpstr_foilcmp.cc	vecpstr.h
vecpstr_loadfile.o:	vecpstr_loadfile.cc	vecpstr.h
vecpstr_loadgrusers.o:	vecpstr_loadgrusers.cc	vecpstr.h
vecpstr_srvargs.o:	vecpstr_srvargs.cc	vecpstr.h
vecpstr_svcargs.o:	vecpstr_svcargs.cc	vecpstr.h
vecpstr_addsyms.o:	vecpstr_addsyms.cc	vecpstr.h

vecstrx_addpath.o:	vecstrx_addpath.cc	vecstrx.hh
vecstrx_adds.o:		vecstrx_adds.cc		vecstrx.hh
vecstrx_addsubdirs.o:	vecstrx_addsubdirs.cc	vecstrx.hh
vecstrx_addsyms.o:	vecstrx_addsyms.cc	vecstrx.hh
vecstrx_adduniqs.o:	vecstrx_adduniqs.cc	vecstrx.hh
vecstrx_env.o:		vecstrx_env.cc		vecstrx.hh
vecstrx_envfile.o:	vecstrx_envfile.cc	vecstrx.hh
vecstrx_foilcmp.o:	vecstrx_foilcmp.cc	vecstrx.hh
vecstrx_loadfile.o:	vecstrx_loadfile.cc	vecstrx.hh
vecstrx_loadgrusers.o:	vecstrx_loadgrusers.cc	vecstrx.hh
vecstrx_loadpjusers.o:	vecstrx_loadpjusers.cc	vecstrx.hh
vecstrx_srvargs.o:	vecstrx_srvargs.cc	vecstrx.hh
vecstrx_svcargs.o:	vecstrx_svcargs.cc	vecstrx.hh

vecobj.o:		vecobj.cc		vecobj.h
vecobj_hsort.o:		vecobj_hsort.cc		vecobj.h
vecobj_recip.o:		vecobj_recip.cc		vecobj.h
vecobj_strsort.o:	vecobj_strsort.cc	vecobj.h

vechand.o:		vechand.cc vechand.h
vecint.o:		vecint.cc vecint.h
veclong.o:		veclong.cc veclong.h
vecitem.o:		vecitem.cc vecitem.h
vecsorthand.o:		vecsorthand.cc vecsorthand.h

raqhand.o:		raqhand.cc raqhand.h
recarr.o:		recarr.cc recarr.h


