#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__7 = 7;
static integer c__5 = 5;
static integer c__20 = 20;

/* Subroutine */ int zchkbl_(integer *nin, integer *nout)
{
    /* Format strings */
    static char fmt_9999[] = "(1x,\002.. test output of ZGEBAL .. \002)";
    static char fmt_9998[] = "(1x,\002value of largest test error           "
	    " = \002,d12.3)";
    static char fmt_9997[] = "(1x,\002example number where info is not zero "
	    " = \002,i4)";
    static char fmt_9996[] = "(1x,\002example number where ILO or IHI wrong "
	    " = \002,i4)";
    static char fmt_9995[] = "(1x,\002example number having largest error   "
	    " = \002,i4)";
    static char fmt_9994[] = "(1x,\002number of examples where info is not 0"
	    " = \002,i4)";
    static char fmt_9993[] = "(1x,\002total number of examples tested       "
	    " = \002,i4)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3, d__4, d__5, d__6;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    integer s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);
    double d_imag(doublecomplex *);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer info, lmax[3];
    static doublereal meps, temp, rmax, vmax;
    static doublecomplex a[400]	/* was [20][20] */;
    static integer i__, j, n;
    static doublereal scale[20];
    static integer ihiin, ninfo, iloin;
    static doublereal anorm, sfmin, dummy[1];
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int zgebal_(char *, integer *, doublecomplex *, 
	    integer *, integer *, integer *, doublereal *, integer *);
    static doublereal scalin[20];
    extern doublereal zlange_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublereal *);
    static doublecomplex ain[400]	/* was [20][20] */;
    static integer ihi, ilo, knt;

    /* Fortran I/O blocks */
    static cilist io___8 = { 0, 0, 0, 0, 0 };
    static cilist io___11 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };
    static cilist io___19 = { 0, 0, 0, 0, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___32 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___33 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___34 = { 0, 0, 0, fmt_9993, 0 };



#define a_subscr(a_1,a_2) (a_2)*20 + a_1 - 21
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define ain_subscr(a_1,a_2) (a_2)*20 + a_1 - 21
#define ain_ref(a_1,a_2) ain[ain_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    ZCHKBL tests ZGEBAL, a routine for balancing a general complex   
    matrix and isolating some of its eigenvalues.   

    Arguments   
    =========   

    NIN     (input) INTEGER   
            The logical unit number for input.  NIN > 0.   

    NOUT    (input) INTEGER   
            The logical unit number for output.  NOUT > 0.   

   ====================================================================== */


    lmax[0] = 0;
    lmax[1] = 0;
    lmax[2] = 0;
    ninfo = 0;
    knt = 0;
    rmax = 0.;
    vmax = 0.;
    sfmin = dlamch_("S");
    meps = dlamch_("E");

L10:

    io___8.ciunit = *nin;
    s_rsle(&io___8);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    e_rsle();
    if (n == 0) {
	goto L70;
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___11.ciunit = *nin;
	s_rsle(&io___11);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&a_ref(i__, j), (ftnlen)sizeof(
		    doublecomplex));
	}
	e_rsle();
/* L20: */
    }

    io___14.ciunit = *nin;
    s_rsle(&io___14);
    do_lio(&c__3, &c__1, (char *)&iloin, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&ihiin, (ftnlen)sizeof(integer));
    e_rsle();
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___17.ciunit = *nin;
	s_rsle(&io___17);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&ain_ref(i__, j), (ftnlen)sizeof(
		    doublecomplex));
	}
	e_rsle();
/* L30: */
    }
    io___19.ciunit = *nin;
    s_rsle(&io___19);
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_lio(&c__5, &c__1, (char *)&scalin[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsle();

    anorm = zlange_("M", &n, &n, a, &c__20, dummy);
    ++knt;
    zgebal_("B", &n, a, &c__20, &ilo, &ihi, scale, &info);

    if (info != 0) {
	++ninfo;
	lmax[0] = knt;
    }

    if (ilo != iloin || ihi != ihiin) {
	++ninfo;
	lmax[1] = knt;
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
/* Computing MAX */
	    i__3 = a_subscr(i__, j);
	    i__4 = ain_subscr(i__, j);
	    d__5 = (d__1 = a[i__3].r, abs(d__1)) + (d__2 = d_imag(&a_ref(i__, 
		    j)), abs(d__2)), d__6 = (d__3 = ain[i__4].r, abs(d__3)) + 
		    (d__4 = d_imag(&ain_ref(i__, j)), abs(d__4));
	    temp = max(d__5,d__6);
	    temp = max(temp,sfmin);
	    i__3 = a_subscr(i__, j);
	    i__4 = ain_subscr(i__, j);
	    z__2.r = a[i__3].r - ain[i__4].r, z__2.i = a[i__3].i - ain[i__4]
		    .i;
	    z__1.r = z__2.r, z__1.i = z__2.i;
/* Computing MAX */
	    d__3 = vmax, d__4 = ((d__1 = z__1.r, abs(d__1)) + (d__2 = d_imag(&
		    z__1), abs(d__2))) / temp;
	    vmax = max(d__3,d__4);
/* L40: */
	}
/* L50: */
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__1 = scale[i__ - 1], d__2 = scalin[i__ - 1];
	temp = max(d__1,d__2);
	temp = max(temp,sfmin);
/* Computing MAX */
	d__2 = vmax, d__3 = (d__1 = scale[i__ - 1] - scalin[i__ - 1], abs(
		d__1)) / temp;
	vmax = max(d__2,d__3);
/* L60: */
    }

    if (vmax > rmax) {
	lmax[2] = knt;
	rmax = vmax;
    }

    goto L10;

L70:

    io___28.ciunit = *nout;
    s_wsfe(&io___28);
    e_wsfe();

    io___29.ciunit = *nout;
    s_wsfe(&io___29);
    do_fio(&c__1, (char *)&rmax, (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___30.ciunit = *nout;
    s_wsfe(&io___30);
    do_fio(&c__1, (char *)&lmax[0], (ftnlen)sizeof(integer));
    e_wsfe();
    io___31.ciunit = *nout;
    s_wsfe(&io___31);
    do_fio(&c__1, (char *)&lmax[1], (ftnlen)sizeof(integer));
    e_wsfe();
    io___32.ciunit = *nout;
    s_wsfe(&io___32);
    do_fio(&c__1, (char *)&lmax[2], (ftnlen)sizeof(integer));
    e_wsfe();
    io___33.ciunit = *nout;
    s_wsfe(&io___33);
    do_fio(&c__1, (char *)&ninfo, (ftnlen)sizeof(integer));
    e_wsfe();
    io___34.ciunit = *nout;
    s_wsfe(&io___34);
    do_fio(&c__1, (char *)&knt, (ftnlen)sizeof(integer));
    e_wsfe();

    return 0;

/*     End of ZCHKBL */

} /* zchkbl_ */

#undef ain_ref
#undef ain_subscr
#undef a_ref
#undef a_subscr


