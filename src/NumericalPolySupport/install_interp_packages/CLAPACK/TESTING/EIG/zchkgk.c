#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__3 = 3;
static integer c__1 = 1;
static integer c__7 = 7;
static integer c__50 = 50;

/* Subroutine */ int zchkgk_(integer *nin, integer *nout)
{
    /* Format strings */
    static char fmt_9999[] = "(1x,\002.. test output of ZGGBAK .. \002)";
    static char fmt_9998[] = "(\002 value of largest test error             "
	    "     =\002,d12.3)";
    static char fmt_9997[] = "(\002 example number where ZGGBAL info is not "
	    "0    =\002,i4)";
    static char fmt_9996[] = "(\002 example number where ZGGBAK(L) info is n"
	    "ot 0 =\002,i4)";
    static char fmt_9995[] = "(\002 example number where ZGGBAK(R) info is n"
	    "ot 0 =\002,i4)";
    static char fmt_9994[] = "(\002 example number having largest error     "
	    "     =\002,i4)";
    static char fmt_9992[] = "(\002 number of examples where info is not 0  "
	    "     =\002,i4)";
    static char fmt_9991[] = "(\002 total number of examples tested         "
	    "     =\002,i4)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3, d__4;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    integer s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);
    double d_imag(doublecomplex *);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer info, lmax[4];
    static doublereal rmax, vmax;
    static doublecomplex work[2500]	/* was [50][50] */, a[2500]	/* 
	    was [50][50] */, b[2500]	/* was [50][50] */, e[2500]	/* 
	    was [50][50] */, f[2500]	/* was [50][50] */;
    static integer i__, j, m, n, ninfo;
    static doublereal anorm, bnorm;
    extern /* Subroutine */ int zgemm_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *);
    static doublereal rwork[300];
    static doublecomplex af[2500]	/* was [50][50] */, bf[2500]	/* 
	    was [50][50] */;
    extern doublereal dlamch_(char *);
    static doublecomplex vl[2500]	/* was [50][50] */;
    static doublereal lscale[50];
    extern /* Subroutine */ int zggbak_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, integer *, doublecomplex *,
	     integer *, integer *), zggbal_(char *, integer *,
	     doublecomplex *, integer *, doublecomplex *, integer *, integer *
	    , integer *, doublereal *, doublereal *, doublereal *, integer *);
    static doublecomplex vr[2500]	/* was [50][50] */;
    static doublereal rscale[50];
    extern doublereal zlange_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublereal *);
    extern /* Subroutine */ int zlacpy_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static integer ihi, ilo;
    static doublereal eps;
    static doublecomplex vlf[2500]	/* was [50][50] */;
    static integer knt;
    static doublecomplex vrf[2500]	/* was [50][50] */;

    /* Fortran I/O blocks */
    static cilist io___6 = { 0, 0, 0, 0, 0 };
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___13 = { 0, 0, 0, 0, 0 };
    static cilist io___15 = { 0, 0, 0, 0, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___39 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___41 = { 0, 0, 0, fmt_9992, 0 };
    static cilist io___42 = { 0, 0, 0, fmt_9991, 0 };



#define a_subscr(a_1,a_2) (a_2)*50 + a_1 - 51
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define b_subscr(a_1,a_2) (a_2)*50 + a_1 - 51
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]
#define e_subscr(a_1,a_2) (a_2)*50 + a_1 - 51
#define e_ref(a_1,a_2) e[e_subscr(a_1,a_2)]
#define f_subscr(a_1,a_2) (a_2)*50 + a_1 - 51
#define f_ref(a_1,a_2) f[f_subscr(a_1,a_2)]
#define vl_subscr(a_1,a_2) (a_2)*50 + a_1 - 51
#define vl_ref(a_1,a_2) vl[vl_subscr(a_1,a_2)]
#define vr_subscr(a_1,a_2) (a_2)*50 + a_1 - 51
#define vr_ref(a_1,a_2) vr[vr_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    ZCHKGK tests ZGGBAK, a routine for backward balancing  of   
    a matrix pair (A, B).   

    Arguments   
    =========   

    NIN     (input) INTEGER   
            The logical unit number for input.  NIN > 0.   

    NOUT    (input) INTEGER   
            The logical unit number for output.  NOUT > 0.   

    ===================================================================== */


    lmax[0] = 0;
    lmax[1] = 0;
    lmax[2] = 0;
    lmax[3] = 0;
    ninfo = 0;
    knt = 0;
    rmax = 0.;

    eps = dlamch_("Precision");

L10:
    io___6.ciunit = *nin;
    s_rsle(&io___6);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&m, (ftnlen)sizeof(integer));
    e_rsle();
    if (n == 0) {
	goto L100;
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___10.ciunit = *nin;
	s_rsle(&io___10);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&a_ref(i__, j), (ftnlen)sizeof(
		    doublecomplex));
	}
	e_rsle();
/* L20: */
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___13.ciunit = *nin;
	s_rsle(&io___13);
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&b_ref(i__, j), (ftnlen)sizeof(
		    doublecomplex));
	}
	e_rsle();
/* L30: */
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___15.ciunit = *nin;
	s_rsle(&io___15);
	i__2 = m;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&vl_ref(i__, j), (ftnlen)sizeof(
		    doublecomplex));
	}
	e_rsle();
/* L40: */
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___17.ciunit = *nin;
	s_rsle(&io___17);
	i__2 = m;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__7, &c__1, (char *)&vr_ref(i__, j), (ftnlen)sizeof(
		    doublecomplex));
	}
	e_rsle();
/* L50: */
    }

    ++knt;

    anorm = zlange_("M", &n, &n, a, &c__50, rwork);
    bnorm = zlange_("M", &n, &n, b, &c__50, rwork);

    zlacpy_("FULL", &n, &n, a, &c__50, af, &c__50);
    zlacpy_("FULL", &n, &n, b, &c__50, bf, &c__50);

    zggbal_("B", &n, a, &c__50, b, &c__50, &ilo, &ihi, lscale, rscale, rwork, 
	    &info);
    if (info != 0) {
	++ninfo;
	lmax[0] = knt;
    }

    zlacpy_("FULL", &n, &m, vl, &c__50, vlf, &c__50);
    zlacpy_("FULL", &n, &m, vr, &c__50, vrf, &c__50);

    zggbak_("B", "L", &n, &ilo, &ihi, lscale, rscale, &m, vl, &c__50, &info);
    if (info != 0) {
	++ninfo;
	lmax[1] = knt;
    }

    zggbak_("B", "R", &n, &ilo, &ihi, lscale, rscale, &m, vr, &c__50, &info);
    if (info != 0) {
	++ninfo;
	lmax[2] = knt;
    }

/*     Test of ZGGBAK   

       Check tilde(VL)'*A*tilde(VR) - VL'*tilde(A)*VR   
       where tilde(A) denotes the transformed matrix. */

    zgemm_("N", "N", &n, &m, &n, &c_b2, af, &c__50, vr, &c__50, &c_b1, work, &
	    c__50);
    zgemm_("C", "N", &m, &m, &n, &c_b2, vl, &c__50, work, &c__50, &c_b1, e, &
	    c__50);

    zgemm_("N", "N", &n, &m, &n, &c_b2, a, &c__50, vrf, &c__50, &c_b1, work, &
	    c__50);
    zgemm_("C", "N", &m, &m, &n, &c_b2, vlf, &c__50, work, &c__50, &c_b1, f, &
	    c__50);

    vmax = 0.;
    i__1 = m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = e_subscr(i__, j);
	    i__4 = f_subscr(i__, j);
	    z__2.r = e[i__3].r - f[i__4].r, z__2.i = e[i__3].i - f[i__4].i;
	    z__1.r = z__2.r, z__1.i = z__2.i;
/* Computing MAX */
	    d__3 = vmax, d__4 = (d__1 = z__1.r, abs(d__1)) + (d__2 = d_imag(&
		    z__1), abs(d__2));
	    vmax = max(d__3,d__4);
/* L60: */
	}
/* L70: */
    }
    vmax /= eps * max(anorm,bnorm);
    if (vmax > rmax) {
	lmax[3] = knt;
	rmax = vmax;
    }

/*     Check tilde(VL)'*B*tilde(VR) - VL'*tilde(B)*VR */

    zgemm_("N", "N", &n, &m, &n, &c_b2, bf, &c__50, vr, &c__50, &c_b1, work, &
	    c__50);
    zgemm_("C", "N", &m, &m, &n, &c_b2, vl, &c__50, work, &c__50, &c_b1, e, &
	    c__50);

    zgemm_("n", "n", &n, &m, &n, &c_b2, b, &c__50, vrf, &c__50, &c_b1, work, &
	    c__50);
    zgemm_("C", "N", &m, &m, &n, &c_b2, vlf, &c__50, work, &c__50, &c_b1, f, &
	    c__50);

    vmax = 0.;
    i__1 = m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = e_subscr(i__, j);
	    i__4 = f_subscr(i__, j);
	    z__2.r = e[i__3].r - f[i__4].r, z__2.i = e[i__3].i - f[i__4].i;
	    z__1.r = z__2.r, z__1.i = z__2.i;
/* Computing MAX */
	    d__3 = vmax, d__4 = (d__1 = z__1.r, abs(d__1)) + (d__2 = d_imag(&
		    z__1), abs(d__2));
	    vmax = max(d__3,d__4);
/* L80: */
	}
/* L90: */
    }
    vmax /= eps * max(anorm,bnorm);
    if (vmax > rmax) {
	lmax[3] = knt;
	rmax = vmax;
    }

    goto L10;

L100:

    io___35.ciunit = *nout;
    s_wsfe(&io___35);
    e_wsfe();

    io___36.ciunit = *nout;
    s_wsfe(&io___36);
    do_fio(&c__1, (char *)&rmax, (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___37.ciunit = *nout;
    s_wsfe(&io___37);
    do_fio(&c__1, (char *)&lmax[0], (ftnlen)sizeof(integer));
    e_wsfe();
    io___38.ciunit = *nout;
    s_wsfe(&io___38);
    do_fio(&c__1, (char *)&lmax[1], (ftnlen)sizeof(integer));
    e_wsfe();
    io___39.ciunit = *nout;
    s_wsfe(&io___39);
    do_fio(&c__1, (char *)&lmax[2], (ftnlen)sizeof(integer));
    e_wsfe();
    io___40.ciunit = *nout;
    s_wsfe(&io___40);
    do_fio(&c__1, (char *)&lmax[3], (ftnlen)sizeof(integer));
    e_wsfe();
    io___41.ciunit = *nout;
    s_wsfe(&io___41);
    do_fio(&c__1, (char *)&ninfo, (ftnlen)sizeof(integer));
    e_wsfe();
    io___42.ciunit = *nout;
    s_wsfe(&io___42);
    do_fio(&c__1, (char *)&knt, (ftnlen)sizeof(integer));
    e_wsfe();

    return 0;

/*     End of ZCHKGK */

} /* zchkgk_ */

#undef vr_ref
#undef vr_subscr
#undef vl_ref
#undef vl_subscr
#undef f_ref
#undef f_subscr
#undef e_ref
#undef e_subscr
#undef b_ref
#undef b_subscr
#undef a_ref
#undef a_subscr


