#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__4 = 4;
static doublereal c_b27 = 100.;
static doublereal c_b28 = 1.;
static integer c__0 = 0;
static integer c_n1 = -1;

/* Subroutine */ int dtimbr_(char *line, integer *nm, integer *mval, integer *
	nval, integer *nk, integer *kval, integer *nnb, integer *nbval, 
	integer *nxval, integer *nlda, integer *ldaval, doublereal *timmin, 
	doublereal *a, doublereal *b, doublereal *d__, doublereal *tau, 
	doublereal *work, doublereal *reslts, integer *ldr1, integer *ldr2, 
	integer *ldr3, integer *nout, ftnlen line_len)
{
    /* Initialized data */

    static char subnam[6*3] = "DGEBRD" "DORGBR" "DORMBR";
    static char sides[1*2] = "L" "R";
    static char vects[1*2] = "Q" "P";
    static char transs[1*2] = "N" "T";
    static integer iseed[4] = { 0,0,0,1 };

    /* Format strings */
    static char fmt_9999[] = "(1x,a6,\002 timing run not attempted\002,/)";
    static char fmt_9998[] = "(/\002 *** Speed of \002,a6,\002 in megaflops "
	    "***\002)";
    static char fmt_9997[] = "(5x,\002line \002,i2,\002 with LDA = \002,i5)";
    static char fmt_9996[] = "(/5x,a6,\002 with VECT = '\002,a1,\002', \002,"
	    "a1,\002 = MIN(\002,a1,\002,\002,a1,\002)\002,/)";
    static char fmt_9995[] = "(/5x,a6,\002 with VECT = '\002,a1,\002', SIDE "
	    "= '\002,a1,\002', TRANS = '\002,a1,\002', \002,a1,\002 =\002,i6,"
	    "/)";

    /* System generated locals */
    integer reslts_dim1, reslts_dim2, reslts_dim3, reslts_offset, i__1, i__2, 
	    i__3, i__4, i__5, i__6, i__7;

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void),
	     s_wsle(cilist *), e_wsle(void);

    /* Local variables */
    static char labk[1];
    static integer ilda;
    static char labm[1], labn[1], side[1];
    static integer info;
    static char path[3];
    static doublereal time;
    static char vect[1];
    static integer isub, info2, i__, k, m, n;
    static char cname[6];
    static integer iside;
    extern doublereal dopla_(char *, integer *, integer *, integer *, integer 
	    *, integer *);
    static integer itoff, ivect, itran, minmn;
    extern /* Subroutine */ int icopy_(integer *, integer *, integer *, 
	    integer *, integer *);
    static char trans[1];
    static integer i3, i4, k1, m1, n1;
    static doublereal s1, s2;
    extern /* Subroutine */ int dprtb4_(char *, char *, char *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, integer *, integer *, integer *, ftnlen, ftnlen, 
	    ftnlen), dprtb5_(char *, char *, char *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, integer 
	    *, integer *, integer *, ftnlen, ftnlen, ftnlen);
    static integer ic, nb, ik, im;
    extern /* Subroutine */ int dgebrd_(integer *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *);
    static integer nq;
    extern doublereal dsecnd_(void);
    static integer lw, nx, reseed[4];
    extern /* Subroutine */ int atimck_(integer *, char *, integer *, integer 
	    *, integer *, integer *, integer *, integer *, ftnlen), dlacpy_(
	    char *, integer *, integer *, doublereal *, integer *, doublereal 
	    *, integer *), dorgbr_(char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, integer *);
    extern doublereal dmflop_(doublereal *, doublereal *, integer *);
    extern /* Subroutine */ int atimin_(char *, char *, integer *, char *, 
	    logical *, integer *, integer *, ftnlen, ftnlen, ftnlen), dlatms_(
	    integer *, integer *, char *, integer *, char *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, integer *, char 
	    *, doublereal *, integer *, doublereal *, integer *), dormbr_(char *, char *, char *, integer *, 
	    integer *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, integer *), dtimmg_(integer *, integer *, integer *, 
	    doublereal *, integer *, integer *, integer *), xlaenv_(integer *,
	     integer *);
    static doublereal untime;
    static logical timsub[3];
    static integer lda, icl, inb;
    static doublereal ops;

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___47 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___49 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___50 = { 0, 0, 0, 0, 0 };
    static cilist io___54 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___55 = { 0, 0, 0, fmt_9995, 0 };



#define subnam_ref(a_0,a_1) &subnam[(a_1)*6 + a_0 - 6]
#define reslts_ref(a_1,a_2,a_3,a_4) reslts[(((a_4)*reslts_dim3 + (a_3))*\
reslts_dim2 + (a_2))*reslts_dim1 + a_1]


/*  -- LAPACK timing routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       March 31, 1993   


    Purpose   
    =======   

    DTIMBR times DGEBRD, DORGBR, and DORMBR.   

    Arguments   
    =========   

    LINE    (input) CHARACTER*80   
            The input line that requested this routine.  The first six   
            characters contain either the name of a subroutine or a   
            generic path name.  The remaining characters may be used to   
            specify the individual routines to be timed.  See ATIMIN for   
            a full description of the format of the input line.   

    NM      (input) INTEGER   
            The number of values of M and N contained in the vectors   
            MVAL and NVAL.  The matrix sizes are used in pairs (M,N).   

    MVAL    (input) INTEGER array, dimension (NM)   
            The values of the matrix row dimension M.   

    NVAL    (input) INTEGER array, dimension (NM)   
            The values of the matrix column dimension N.   

    NK      (input) INTEGER   
            The number of values of K contained in the vector KVAL.   

    KVAL    (input) INTEGER array, dimension (NK)   
            The values of the matrix dimension K.   

    NNB     (input) INTEGER   
            The number of values of NB and NX contained in the   
            vectors NBVAL and NXVAL.  The blocking parameters are used   
            in pairs (NB,NX).   

    NBVAL   (input) INTEGER array, dimension (NNB)   
            The values of the blocksize NB.   

    NXVAL   (input) INTEGER array, dimension (NNB)   
            The values of the crossover point NX.   

    NLDA    (input) INTEGER   
            The number of values of LDA contained in the vector LDAVAL.   

    LDAVAL  (input) INTEGER array, dimension (NLDA)   
            The values of the leading dimension of the array A.   

    TIMMIN  (input) DOUBLE PRECISION   
            The minimum time a subroutine will be timed.   

    A       (workspace) DOUBLE PRECISION array, dimension (LDAMAX*NMAX)   
            where LDAMAX and NMAX are the maximum values of LDA and N.   

    B       (workspace) DOUBLE PRECISION array, dimension (LDAMAX*NMAX)   

    D       (workspace) DOUBLE PRECISION array, dimension   
                        (2*max(min(M,N))-1)   

    TAU     (workspace) DOUBLE PRECISION array, dimension   
                        (2*max(min(M,N)))   

    WORK    (workspace) DOUBLE PRECISION array, dimension (LDAMAX*NBMAX)   
            where NBMAX is the maximum value of NB.   

    RESLTS  (output) DOUBLE PRECISION array, dimension (LDR1,LDR2,LDR3,6)   
            The timing results for each subroutine over the relevant   
            values of (M,N), (NB,NX), and LDA.   

    LDR1    (input) INTEGER   
            The first dimension of RESLTS.  LDR1 >= max(1,NNB).   

    LDR2    (input) INTEGER   
            The second dimension of RESLTS.  LDR2 >= max(1,NM).   

    LDR3    (input) INTEGER   
            The third dimension of RESLTS.  LDR3 >= max(1,NLDA).   

    NOUT    (input) INTEGER   
            The unit number for output.   

    Internal Parameters   
    ===================   

    MODE    INTEGER   
            The matrix type.  MODE = 3 is a geometric distribution of   
            eigenvalues.  See ZLATMS for further details.   

    COND    DOUBLE PRECISION   
            The condition number of the matrix.  The singular values are   
            set to values from DMAX to DMAX/COND.   

    DMAX    DOUBLE PRECISION   
            The magnitude of the largest singular value.   

    =====================================================================   

       Parameter adjustments */
    --mval;
    --nval;
    --kval;
    --nbval;
    --nxval;
    --ldaval;
    --a;
    --b;
    --d__;
    --tau;
    --work;
    reslts_dim1 = *ldr1;
    reslts_dim2 = *ldr2;
    reslts_dim3 = *ldr3;
    reslts_offset = 1 + reslts_dim1 * (1 + reslts_dim2 * (1 + reslts_dim3 * 1)
	    );
    reslts -= reslts_offset;

    /* Function Body   

       Extract the timing request from the input line. */

    s_copy(path, "Double precision", (ftnlen)1, (ftnlen)16);
    s_copy(path + 1, "BR", (ftnlen)2, (ftnlen)2);
    atimin_(path, line, &c__3, subnam, timsub, nout, &info, (ftnlen)3, (
	    ftnlen)80, (ftnlen)6);
    if (info != 0) {
	goto L220;
    }

/*     Check that M <= LDA for the input values. */

    s_copy(cname, line, (ftnlen)6, (ftnlen)6);
    atimck_(&c__1, cname, nm, &mval[1], nlda, &ldaval[1], nout, &info, (
	    ftnlen)6);
    if (info > 0) {
	io___10.ciunit = *nout;
	s_wsfe(&io___10);
	do_fio(&c__1, cname, (ftnlen)6);
	e_wsfe();
	goto L220;
    }

/*     Check that N <= LDA and K <= LDA for DORMBR */

    if (timsub[2]) {
	atimck_(&c__2, cname, nm, &nval[1], nlda, &ldaval[1], nout, &info, (
		ftnlen)6);
	atimck_(&c__3, cname, nk, &kval[1], nlda, &ldaval[1], nout, &info2, (
		ftnlen)6);
	if (info > 0 || info2 > 0) {
	    io___12.ciunit = *nout;
	    s_wsfe(&io___12);
	    do_fio(&c__1, subnam_ref(0, 3), (ftnlen)6);
	    e_wsfe();
	    timsub[2] = FALSE_;
	}
    }

/*     Do for each pair of values (M,N): */

    i__1 = *nm;
    for (im = 1; im <= i__1; ++im) {
	m = mval[im];
	n = nval[im];
	minmn = min(m,n);
	icopy_(&c__4, iseed, &c__1, reseed, &c__1);

/*        Do for each value of LDA: */

	i__2 = *nlda;
	for (ilda = 1; ilda <= i__2; ++ilda) {
	    lda = ldaval[ilda];

/*           Do for each pair of values (NB, NX) in NBVAL and NXVAL. */

	    i__3 = *nnb;
	    for (inb = 1; inb <= i__3; ++inb) {
		nb = nbval[inb];
		xlaenv_(&c__1, &nb);
		nx = nxval[inb];
		xlaenv_(&c__3, &nx);
/* Computing MAX */
		i__4 = m + n, i__5 = max(1,nb) * (m + n);
		lw = max(i__4,i__5);

/*              Generate a test matrix of size M by N. */

		icopy_(&c__4, reseed, &c__1, iseed, &c__1);
		dlatms_(&m, &n, "Uniform", iseed, "Nonsym", &tau[1], &c__3, &
			c_b27, &c_b28, &m, &n, "No packing", &b[1], &lda, &
			work[1], &info);

		if (timsub[0]) {

/*                 DGEBRD:  Block reduction to bidiagonal form */

		    dlacpy_("Full", &m, &n, &b[1], &lda, &a[1], &lda);
		    ic = 0;
		    s1 = dsecnd_();
L10:
		    dgebrd_(&m, &n, &a[1], &lda, &d__[1], &d__[minmn], &tau[1]
			    , &tau[minmn + 1], &work[1], &lw, &info);
		    s2 = dsecnd_();
		    time = s2 - s1;
		    ++ic;
		    if (time < *timmin) {
			dlacpy_("Full", &m, &n, &b[1], &lda, &a[1], &lda);
			goto L10;
		    }

/*                 Subtract the time used in DLACPY. */

		    icl = 1;
		    s1 = dsecnd_();
L20:
		    s2 = dsecnd_();
		    untime = s2 - s1;
		    ++icl;
		    if (icl <= ic) {
			dlacpy_("Full", &m, &n, &a[1], &lda, &b[1], &lda);
			goto L20;
		    }

		    time = (time - untime) / (doublereal) ic;
		    ops = dopla_("DGEBRD", &m, &n, &c__0, &c__0, &nb);
		    reslts_ref(inb, im, ilda, 1) = dmflop_(&ops, &time, &info)
			    ;
		} else {

/*                 If DGEBRD was not timed, generate a matrix and reduce   
                   it using DGEBRD anyway so that the orthogonal   
                   transformations may be used in timing the other   
                   routines. */

		    dlacpy_("Full", &m, &n, &b[1], &lda, &a[1], &lda);
		    dgebrd_(&m, &n, &a[1], &lda, &d__[1], &d__[minmn], &tau[1]
			    , &tau[minmn + 1], &work[1], &lw, &info);

		}

		if (timsub[1]) {

/*                 DORGBR:  Generate one of the orthogonal matrices Q or   
                   P' from the reduction to bidiagonal form   
                   A = Q * B * P'. */

		    for (ivect = 1; ivect <= 2; ++ivect) {
			if (ivect == 1) {
			    *(unsigned char *)vect = 'Q';
			    m1 = m;
			    n1 = min(m,n);
			    k1 = n;
			} else {
			    *(unsigned char *)vect = 'P';
			    m1 = min(m,n);
			    n1 = n;
			    k1 = m;
			}
			i3 = (ivect - 1) * *nlda;
/* Computing MAX */
			i__4 = 1, i__5 = max(1,nb) * min(m,n);
			lw = max(i__4,i__5);
			dlacpy_("Full", &m, &n, &a[1], &lda, &b[1], &lda);
			ic = 0;
			s1 = dsecnd_();
L30:
			dorgbr_(vect, &m1, &n1, &k1, &b[1], &lda, &tau[1], &
				work[1], &lw, &info);
			s2 = dsecnd_();
			time = s2 - s1;
			++ic;
			if (time < *timmin) {
			    dlacpy_("Full", &m, &n, &a[1], &lda, &b[1], &lda);
			    goto L30;
			}

/*                    Subtract the time used in DLACPY. */

			icl = 1;
			s1 = dsecnd_();
L40:
			s2 = dsecnd_();
			untime = s2 - s1;
			++icl;
			if (icl <= ic) {
			    dlacpy_("Full", &m, &n, &a[1], &lda, &b[1], &lda);
			    goto L40;
			}

			time = (time - untime) / (doublereal) ic;

/*                    Op count for DORGBR: */

			if (ivect == 1) {
			    if (m1 >= k1) {
				ops = dopla_("DORGQR", &m1, &n1, &k1, &c_n1, &
					nb);
			    } else {
				i__4 = m1 - 1;
				i__5 = m1 - 1;
				i__6 = m1 - 1;
				ops = dopla_("DORGQR", &i__4, &i__5, &i__6, &
					c_n1, &nb);
			    }
			} else {
			    if (k1 < n1) {
				ops = dopla_("DORGLQ", &m1, &n1, &k1, &c_n1, &
					nb);
			    } else {
				i__4 = n1 - 1;
				i__5 = n1 - 1;
				i__6 = n1 - 1;
				ops = dopla_("DORGLQ", &i__4, &i__5, &i__6, &
					c_n1, &nb);
			    }
			}

			reslts_ref(inb, im, i3 + ilda, 2) = dmflop_(&ops, &
				time, &info);
/* L50: */
		    }
		}

		if (timsub[2]) {

/*                 DORMBR:  Multiply an m by n matrix B by one of the   
                   orthogonal matrices Q or P' from the reduction to   
                   bidiagonal form A = Q * B * P'. */

		    for (ivect = 1; ivect <= 2; ++ivect) {
			if (ivect == 1) {
			    *(unsigned char *)vect = 'Q';
			    k1 = n;
			    nq = m;
			} else {
			    *(unsigned char *)vect = 'P';
			    k1 = m;
			    nq = n;
			}
			i3 = (ivect - 1) * *nlda;
			i4 = 2;
			for (iside = 1; iside <= 2; ++iside) {
			    *(unsigned char *)side = *(unsigned char *)&sides[
				    iside - 1];
			    i__4 = *nk;
			    for (ik = 1; ik <= i__4; ++ik) {
				k = kval[ik];
				if (iside == 1) {
				    m1 = nq;
				    n1 = k;
/* Computing MAX */
				    i__5 = 1, i__6 = max(1,nb) * n1;
				    lw = max(i__5,i__6);
				} else {
				    m1 = k;
				    n1 = nq;
/* Computing MAX */
				    i__5 = 1, i__6 = max(1,nb) * m1;
				    lw = max(i__5,i__6);
				}
				itoff = 0;
				for (itran = 1; itran <= 2; ++itran) {
				    *(unsigned char *)trans = *(unsigned char 
					    *)&transs[itran - 1];
				    dtimmg_(&c__0, &m1, &n1, &b[1], &lda, &
					    c__0, &c__0);
				    ic = 0;
				    s1 = dsecnd_();
L60:
				    dormbr_(vect, side, trans, &m1, &n1, &k1, 
					    &a[1], &lda, &tau[1], &b[1], &lda,
					     &work[1], &lw, &info);
				    s2 = dsecnd_();
				    time = s2 - s1;
				    ++ic;
				    if (time < *timmin) {
					dtimmg_(&c__0, &m1, &n1, &b[1], &lda, 
						&c__0, &c__0);
					goto L60;
				    }

/*                             Subtract the time used in DTIMMG. */

				    icl = 1;
				    s1 = dsecnd_();
L70:
				    s2 = dsecnd_();
				    untime = s2 - s1;
				    ++icl;
				    if (icl <= ic) {
					dtimmg_(&c__0, &m1, &n1, &b[1], &lda, 
						&c__0, &c__0);
					goto L70;
				    }

				    time = (time - untime) / (doublereal) ic;
				    if (ivect == 1) {

/*                                Op count for DORMBR, VECT = 'Q': */

					if (nq >= k1) {
					    i__5 = iside - 1;
					    ops = dopla_("DORMQR", &m1, &n1, &
						    k1, &i__5, &nb)
						    ;
					} else if (iside == 1) {
					    i__5 = m1 - 1;
					    i__6 = nq - 1;
					    i__7 = iside - 1;
					    ops = dopla_("DORMQR", &i__5, &n1,
						     &i__6, &i__7, &nb);
					} else {
					    i__5 = n1 - 1;
					    i__6 = nq - 1;
					    i__7 = iside - 1;
					    ops = dopla_("DORMQR", &m1, &i__5,
						     &i__6, &i__7, &nb);
					}
				    } else {

/*                                Op count for DORMBR, VECT = 'P': */

					if (nq > k1) {
					    i__5 = iside - 1;
					    ops = dopla_("DORMLQ", &m1, &n1, &
						    k1, &i__5, &nb)
						    ;
					} else if (iside == 1) {
					    i__5 = m1 - 1;
					    i__6 = nq - 1;
					    i__7 = iside - 1;
					    ops = dopla_("DORMLQ", &i__5, &n1,
						     &i__6, &i__7, &nb);
					} else {
					    i__5 = n1 - 1;
					    i__6 = nq - 1;
					    i__7 = iside - 1;
					    ops = dopla_("DORMLQ", &m1, &i__5,
						     &i__6, &i__7, &nb);
					}
				    }

				    reslts_ref(inb, im, i3 + ilda, i4 + itoff 
					    + ik) = dmflop_(&ops, &time, &
					    info);
				    itoff = *nk;
/* L80: */
				}
/* L90: */
			    }
			    i4 = (*nk << 1) + 2;
/* L100: */
			}
/* L110: */
		    }
		}
/* L120: */
	    }
/* L130: */
	}
/* L140: */
    }

/*     Print a table of results for each timed routine. */

    for (isub = 1; isub <= 3; ++isub) {
	if (! timsub[isub - 1]) {
	    goto L210;
	}
	io___47.ciunit = *nout;
	s_wsfe(&io___47);
	do_fio(&c__1, subnam_ref(0, isub), (ftnlen)6);
	e_wsfe();
	if (*nlda > 1) {
	    i__1 = *nlda;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		io___49.ciunit = *nout;
		s_wsfe(&io___49);
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&ldaval[i__], (ftnlen)sizeof(integer));
		e_wsfe();
/* L150: */
	    }
	}
	if (isub == 1) {
	    io___50.ciunit = *nout;
	    s_wsle(&io___50);
	    e_wsle();
	    dprtb4_("(  NB,  NX)", "M", "N", nnb, &nbval[1], &nxval[1], nm, &
		    mval[1], &nval[1], nlda, &reslts_ref(1, 1, 1, isub), ldr1,
		     ldr2, nout, (ftnlen)11, (ftnlen)1, (ftnlen)1);
	} else if (isub == 2) {
	    for (ivect = 1; ivect <= 2; ++ivect) {
		i3 = (ivect - 1) * *nlda + 1;
		if (ivect == 1) {
		    *(unsigned char *)labk = 'N';
		    *(unsigned char *)labm = 'M';
		    *(unsigned char *)labn = 'K';
		} else {
		    *(unsigned char *)labk = 'M';
		    *(unsigned char *)labm = 'K';
		    *(unsigned char *)labn = 'N';
		}
		io___54.ciunit = *nout;
		s_wsfe(&io___54);
		do_fio(&c__1, subnam_ref(0, isub), (ftnlen)6);
		do_fio(&c__1, vects + (ivect - 1), (ftnlen)1);
		do_fio(&c__1, labk, (ftnlen)1);
		do_fio(&c__1, labm, (ftnlen)1);
		do_fio(&c__1, labn, (ftnlen)1);
		e_wsfe();
		dprtb4_("(  NB,  NX)", labm, labn, nnb, &nbval[1], &nxval[1], 
			nm, &mval[1], &nval[1], nlda, &reslts_ref(1, 1, i3, 
			isub), ldr1, ldr2, nout, (ftnlen)11, (ftnlen)1, (
			ftnlen)1);
/* L160: */
	    }
	} else if (isub == 3) {
	    for (ivect = 1; ivect <= 2; ++ivect) {
		i3 = (ivect - 1) * *nlda + 1;
		i4 = 3;
		for (iside = 1; iside <= 2; ++iside) {
		    if (iside == 1) {
			if (ivect == 1) {
			    *(unsigned char *)labm = 'M';
			    *(unsigned char *)labn = 'K';
			} else {
			    *(unsigned char *)labm = 'K';
			    *(unsigned char *)labn = 'M';
			}
			*(unsigned char *)labk = 'N';
		    } else {
			if (ivect == 1) {
			    *(unsigned char *)labm = 'N';
			    *(unsigned char *)labn = 'K';
			} else {
			    *(unsigned char *)labm = 'K';
			    *(unsigned char *)labn = 'N';
			}
			*(unsigned char *)labk = 'M';
		    }
		    for (itran = 1; itran <= 2; ++itran) {
			i__1 = *nk;
			for (ik = 1; ik <= i__1; ++ik) {
			    io___55.ciunit = *nout;
			    s_wsfe(&io___55);
			    do_fio(&c__1, subnam_ref(0, isub), (ftnlen)6);
			    do_fio(&c__1, vects + (ivect - 1), (ftnlen)1);
			    do_fio(&c__1, sides + (iside - 1), (ftnlen)1);
			    do_fio(&c__1, transs + (itran - 1), (ftnlen)1);
			    do_fio(&c__1, labk, (ftnlen)1);
			    do_fio(&c__1, (char *)&kval[ik], (ftnlen)sizeof(
				    integer));
			    e_wsfe();
			    dprtb5_("NB", labm, labn, nnb, &nbval[1], nm, &
				    mval[1], &nval[1], nlda, &reslts_ref(1, 1,
				     i3, i4), ldr1, ldr2, nout, (ftnlen)2, (
				    ftnlen)1, (ftnlen)1);
			    ++i4;
/* L170: */
			}
/* L180: */
		    }
/* L190: */
		}
/* L200: */
	    }
	}
L210:
	;
    }
L220:
    return 0;

/*     End of DTIMBR */

} /* dtimbr_ */

#undef reslts_ref
#undef subnam_ref


