#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer infot, nunit;
    logical ok, lerr;
} infoc_;

#define infoc_1 infoc_

struct {
    char srnamt[6];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static integer c__0 = 0;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__1 = 1;
static integer c__8 = 8;

/* Subroutine */ int zchkhp_(logical *dotype, integer *nn, integer *nval, 
	integer *nns, integer *nsval, doublereal *thresh, logical *tsterr, 
	integer *nmax, doublecomplex *a, doublecomplex *afac, doublecomplex *
	ainv, doublecomplex *b, doublecomplex *x, doublecomplex *xact, 
	doublecomplex *work, doublereal *rwork, integer *iwork, integer *nout)
{
    /* Initialized data */

    static integer iseedy[4] = { 1988,1989,1990,1991 };
    static char uplos[1*2] = "U" "L";

    /* Format strings */
    static char fmt_9999[] = "(\002 UPLO = '\002,a1,\002', N =\002,i5,\002, "
	    "type \002,i2,\002, test \002,i2,\002, ratio =\002,g12.5)";
    static char fmt_9998[] = "(\002 UPLO = '\002,a1,\002', N =\002,i5,\002, "
	    "NRHS=\002,i3,\002, type \002,i2,\002, test(\002,i2,\002) =\002,g"
	    "12.5)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5;

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer ioff, mode, imat, info;
    static char path[3], dist[1];
    static integer irhs, nrhs;
    static char uplo[1], type__[1];
    static integer nrun, i__, j, k;
    extern /* Subroutine */ int alahd_(integer *, char *);
    static integer n, nfail, iseed[4];
    extern doublereal dget06_(doublereal *, doublereal *);
    extern logical lsame_(char *, char *);
    static doublereal rcond;
    static integer nimat;
    static doublereal anorm;
    extern /* Subroutine */ int zget04_(integer *, integer *, doublecomplex *,
	     integer *, doublecomplex *, integer *, doublereal *, doublereal *
	    ), zhpt01_(char *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublereal *, doublereal *);
    static integer iuplo, izero, i1, i2, nerrs;
    extern /* Subroutine */ int zppt02_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublereal *, doublereal *), zppt03_(char *, 
	    integer *, doublecomplex *, doublecomplex *, doublecomplex *, 
	    integer *, doublereal *, doublereal *, doublereal *);
    static logical zerot;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zppt05_(char *, integer *, integer *,
	     doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublereal *, doublereal *,
	     doublereal *);
    static char xtype[1];
    extern /* Subroutine */ int zlatb4_(char *, integer *, integer *, integer 
	    *, char *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, char *);
    static integer in, kl;
    extern /* Subroutine */ int alaerh_(char *, char *, integer *, integer *, 
	    char *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    static integer ku, nt;
    static doublereal rcondc;
    static char packit[1];
    extern /* Subroutine */ int alasum_(char *, integer *, integer *, integer 
	    *, integer *);
    static doublereal cndnum;
    extern /* Subroutine */ int zlaipd_(integer *, doublecomplex *, integer *,
	     integer *);
    static logical trfcon;
    extern doublereal zlanhp_(char *, char *, integer *, doublecomplex *, 
	    doublereal *);
    extern /* Subroutine */ int zhpcon_(char *, integer *, doublecomplex *, 
	    integer *, doublereal *, doublereal *, doublecomplex *, integer *), zlacpy_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *), zlarhs_(char *, 
	    char *, char *, char *, integer *, integer *, integer *, integer *
	    , integer *, doublecomplex *, integer *, doublecomplex *, integer 
	    *, doublecomplex *, integer *, integer *, integer *), zlatms_(integer *, integer *, char *, 
	    integer *, char *, doublereal *, integer *, doublereal *, 
	    doublereal *, integer *, integer *, char *, doublecomplex *, 
	    integer *, doublecomplex *, integer *), 
	    zhprfs_(char *, integer *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublereal *, doublereal *, 
	    doublecomplex *, doublereal *, integer *), zhptrf_(char *,
	     integer *, doublecomplex *, integer *, integer *);
    static doublereal result[8];
    extern /* Subroutine */ int zhptri_(char *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *), zhptrs_(char *, 
	    integer *, integer *, doublecomplex *, integer *, doublecomplex *,
	     integer *, integer *), zerrsy_(char *, integer *)
	    ;
    static integer lda, npp;

    /* Fortran I/O blocks */
    static cilist io___38 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___41 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_9999, 0 };



/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    ZCHKHP tests ZHPTRF, -TRI, -TRS, -RFS, and -CON   

    Arguments   
    =========   

    DOTYPE  (input) LOGICAL array, dimension (NTYPES)   
            The matrix types to be used for testing.  Matrices of type j   
            (for 1 <= j <= NTYPES) are used for testing if DOTYPE(j) =   
            .TRUE.; if DOTYPE(j) = .FALSE., then type j is not used.   

    NN      (input) INTEGER   
            The number of values of N contained in the vector NVAL.   

    NVAL    (input) INTEGER array, dimension (NN)   
            The values of the matrix dimension N.   

    NNS     (input) INTEGER   
            The number of values of NRHS contained in the vector NSVAL.   

    NSVAL   (input) INTEGER array, dimension (NNS)   
            The values of the number of right hand sides NRHS.   

    THRESH  (input) DOUBLE PRECISION   
            The threshold value for the test ratios.  A result is   
            included in the output file if RESULT >= THRESH.  To have   
            every test ratio printed, use THRESH = 0.   

    TSTERR  (input) LOGICAL   
            Flag that indicates whether error exits are to be tested.   

    NMAX    (input) INTEGER   
            The maximum value permitted for N, used in dimensioning the   
            work arrays.   

    A       (workspace) COMPLEX*16 array, dimension   
                        (NMAX*(NMAX+1)/2)   

    AFAC    (workspace) COMPLEX*16 array, dimension   
                        (NMAX*(NMAX+1)/2)   

    AINV    (workspace) COMPLEX*16 array, dimension   
                        (NMAX*(NMAX+1)/2)   

    B       (workspace) COMPLEX*16 array, dimension (NMAX*NSMAX)   
            where NSMAX is the largest entry in NSVAL.   

    X       (workspace) COMPLEX*16 array, dimension (NMAX*NSMAX)   

    XACT    (workspace) COMPLEX*16 array, dimension (NMAX*NSMAX)   

    WORK    (workspace) COMPLEX*16 array, dimension   
                        (NMAX*max(2,NSMAX))   

    RWORK   (workspace) DOUBLE PRECISION array,   
                                   dimension (NMAX+2*NSMAX)   

    IWORK   (workspace) INTEGER array, dimension (NMAX)   

    NOUT    (input) INTEGER   
            The unit number for output.   

    =====================================================================   

       Parameter adjustments */
    --iwork;
    --rwork;
    --work;
    --xact;
    --x;
    --b;
    --ainv;
    --afac;
    --a;
    --nsval;
    --nval;
    --dotype;

    /* Function Body   

       Initialize constants and the random number seed. */

    s_copy(path, "Zomplex precision", (ftnlen)1, (ftnlen)17);
    s_copy(path + 1, "HP", (ftnlen)2, (ftnlen)2);
    nrun = 0;
    nfail = 0;
    nerrs = 0;
    for (i__ = 1; i__ <= 4; ++i__) {
	iseed[i__ - 1] = iseedy[i__ - 1];
/* L10: */
    }

/*     Test the error exits */

    if (*tsterr) {
	zerrsy_(path, nout);
    }
    infoc_1.infot = 0;

/*     Do for each value of N in NVAL */

    i__1 = *nn;
    for (in = 1; in <= i__1; ++in) {
	n = nval[in];
	lda = max(n,1);
	*(unsigned char *)xtype = 'N';
	nimat = 10;
	if (n <= 0) {
	    nimat = 1;
	}

	izero = 0;
	i__2 = nimat;
	for (imat = 1; imat <= i__2; ++imat) {

/*           Do the tests only if DOTYPE( IMAT ) is true. */

	    if (! dotype[imat]) {
		goto L160;
	    }

/*           Skip types 3, 4, 5, or 6 if the matrix size is too small. */

	    zerot = imat >= 3 && imat <= 6;
	    if (zerot && n < imat - 2) {
		goto L160;
	    }

/*           Do first for UPLO = 'U', then for UPLO = 'L' */

	    for (iuplo = 1; iuplo <= 2; ++iuplo) {
		*(unsigned char *)uplo = *(unsigned char *)&uplos[iuplo - 1];
		if (lsame_(uplo, "U")) {
		    *(unsigned char *)packit = 'C';
		} else {
		    *(unsigned char *)packit = 'R';
		}

/*              Set up parameters with ZLATB4 and generate a test matrix   
                with ZLATMS. */

		zlatb4_(path, &imat, &n, &n, type__, &kl, &ku, &anorm, &mode, 
			&cndnum, dist);

		s_copy(srnamc_1.srnamt, "ZLATMS", (ftnlen)6, (ftnlen)6);
		zlatms_(&n, &n, dist, iseed, type__, &rwork[1], &mode, &
			cndnum, &anorm, &kl, &ku, packit, &a[1], &lda, &work[
			1], &info);

/*              Check error code from ZLATMS. */

		if (info != 0) {
		    alaerh_(path, "ZLATMS", &info, &c__0, uplo, &n, &n, &c_n1,
			     &c_n1, &c_n1, &imat, &nfail, &nerrs, nout);
		    goto L150;
		}

/*              For types 3-6, zero one or more rows and columns of   
                the matrix to test that INFO is returned correctly. */

		if (zerot) {
		    if (imat == 3) {
			izero = 1;
		    } else if (imat == 4) {
			izero = n;
		    } else {
			izero = n / 2 + 1;
		    }

		    if (imat < 6) {

/*                    Set row and column IZERO to zero. */

			if (iuplo == 1) {
			    ioff = (izero - 1) * izero / 2;
			    i__3 = izero - 1;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				i__4 = ioff + i__;
				a[i__4].r = 0., a[i__4].i = 0.;
/* L20: */
			    }
			    ioff += izero;
			    i__3 = n;
			    for (i__ = izero; i__ <= i__3; ++i__) {
				i__4 = ioff;
				a[i__4].r = 0., a[i__4].i = 0.;
				ioff += i__;
/* L30: */
			    }
			} else {
			    ioff = izero;
			    i__3 = izero - 1;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				i__4 = ioff;
				a[i__4].r = 0., a[i__4].i = 0.;
				ioff = ioff + n - i__;
/* L40: */
			    }
			    ioff -= izero;
			    i__3 = n;
			    for (i__ = izero; i__ <= i__3; ++i__) {
				i__4 = ioff + i__;
				a[i__4].r = 0., a[i__4].i = 0.;
/* L50: */
			    }
			}
		    } else {
			ioff = 0;
			if (iuplo == 1) {

/*                       Set the first IZERO rows and columns to zero. */

			    i__3 = n;
			    for (j = 1; j <= i__3; ++j) {
				i2 = min(j,izero);
				i__4 = i2;
				for (i__ = 1; i__ <= i__4; ++i__) {
				    i__5 = ioff + i__;
				    a[i__5].r = 0., a[i__5].i = 0.;
/* L60: */
				}
				ioff += j;
/* L70: */
			    }
			} else {

/*                       Set the last IZERO rows and columns to zero. */

			    i__3 = n;
			    for (j = 1; j <= i__3; ++j) {
				i1 = max(j,izero);
				i__4 = n;
				for (i__ = i1; i__ <= i__4; ++i__) {
				    i__5 = ioff + i__;
				    a[i__5].r = 0., a[i__5].i = 0.;
/* L80: */
				}
				ioff = ioff + n - j;
/* L90: */
			    }
			}
		    }
		} else {
		    izero = 0;
		}

/*              Set the imaginary part of the diagonals. */

		if (iuplo == 1) {
		    zlaipd_(&n, &a[1], &c__2, &c__1);
		} else {
		    zlaipd_(&n, &a[1], &n, &c_n1);
		}

/*              Compute the L*D*L' or U*D*U' factorization of the matrix. */

		npp = n * (n + 1) / 2;
		zcopy_(&npp, &a[1], &c__1, &afac[1], &c__1);
		s_copy(srnamc_1.srnamt, "ZHPTRF", (ftnlen)6, (ftnlen)6);
		zhptrf_(uplo, &n, &afac[1], &iwork[1], &info);

/*              Adjust the expected value of INFO to account for   
                pivoting. */

		k = izero;
		if (k > 0) {
L100:
		    if (iwork[k] < 0) {
			if (iwork[k] != -k) {
			    k = -iwork[k];
			    goto L100;
			}
		    } else if (iwork[k] != k) {
			k = iwork[k];
			goto L100;
		    }
		}

/*              Check error code from ZHPTRF. */

		if (info != k) {
		    alaerh_(path, "ZHPTRF", &info, &k, uplo, &n, &n, &c_n1, &
			    c_n1, &c_n1, &imat, &nfail, &nerrs, nout);
		}
		if (info != 0) {
		    trfcon = TRUE_;
		} else {
		    trfcon = FALSE_;
		}

/* +    TEST 1   
                Reconstruct matrix from factors and compute residual. */

		zhpt01_(uplo, &n, &a[1], &afac[1], &iwork[1], &ainv[1], &lda, 
			&rwork[1], result);
		nt = 1;

/* +    TEST 2   
                Form the inverse and compute the residual. */

		if (! trfcon) {
		    zcopy_(&npp, &afac[1], &c__1, &ainv[1], &c__1);
		    s_copy(srnamc_1.srnamt, "ZHPTRI", (ftnlen)6, (ftnlen)6);
		    zhptri_(uplo, &n, &ainv[1], &iwork[1], &work[1], &info);

/*              Check error code from ZHPTRI. */

		    if (info != 0) {
			alaerh_(path, "ZHPTRI", &info, &c__0, uplo, &n, &n, &
				c_n1, &c_n1, &c_n1, &imat, &nfail, &nerrs, 
				nout);
		    }

		    zppt03_(uplo, &n, &a[1], &ainv[1], &work[1], &lda, &rwork[
			    1], &rcondc, &result[1]);
		    nt = 2;
		}

/*              Print information about the tests that did not pass   
                the threshold. */

		i__3 = nt;
		for (k = 1; k <= i__3; ++k) {
		    if (result[k - 1] >= *thresh) {
			if (nfail == 0 && nerrs == 0) {
			    alahd_(nout, path);
			}
			io___38.ciunit = *nout;
			s_wsfe(&io___38);
			do_fio(&c__1, uplo, (ftnlen)1);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[k - 1], (ftnlen)sizeof(
				doublereal));
			e_wsfe();
			++nfail;
		    }
/* L110: */
		}
		nrun += nt;

/*              Do only the condition estimate if INFO is not 0. */

		if (trfcon) {
		    rcondc = 0.;
		    goto L140;
		}

		i__3 = *nns;
		for (irhs = 1; irhs <= i__3; ++irhs) {
		    nrhs = nsval[irhs];

/* +    TEST 3   
                Solve and compute residual for  A * X = B. */

		    s_copy(srnamc_1.srnamt, "ZLARHS", (ftnlen)6, (ftnlen)6);
		    zlarhs_(path, xtype, uplo, " ", &n, &n, &kl, &ku, &nrhs, &
			    a[1], &lda, &xact[1], &lda, &b[1], &lda, iseed, &
			    info);
		    *(unsigned char *)xtype = 'C';
		    zlacpy_("Full", &n, &nrhs, &b[1], &lda, &x[1], &lda);

		    s_copy(srnamc_1.srnamt, "ZHPTRS", (ftnlen)6, (ftnlen)6);
		    zhptrs_(uplo, &n, &nrhs, &afac[1], &iwork[1], &x[1], &lda,
			     &info);

/*              Check error code from ZHPTRS. */

		    if (info != 0) {
			alaerh_(path, "ZHPTRS", &info, &c__0, uplo, &n, &n, &
				c_n1, &c_n1, &nrhs, &imat, &nfail, &nerrs, 
				nout);
		    }

		    zlacpy_("Full", &n, &nrhs, &b[1], &lda, &work[1], &lda);
		    zppt02_(uplo, &n, &nrhs, &a[1], &x[1], &lda, &work[1], &
			    lda, &rwork[1], &result[2]);

/* +    TEST 4   
                Check solution from generated exact solution. */

		    zget04_(&n, &nrhs, &x[1], &lda, &xact[1], &lda, &rcondc, &
			    result[3]);

/* +    TESTS 5, 6, and 7   
                Use iterative refinement to improve the solution. */

		    s_copy(srnamc_1.srnamt, "ZHPRFS", (ftnlen)6, (ftnlen)6);
		    zhprfs_(uplo, &n, &nrhs, &a[1], &afac[1], &iwork[1], &b[1]
			    , &lda, &x[1], &lda, &rwork[1], &rwork[nrhs + 1], 
			    &work[1], &rwork[(nrhs << 1) + 1], &info);

/*              Check error code from ZHPRFS. */

		    if (info != 0) {
			alaerh_(path, "ZHPRFS", &info, &c__0, uplo, &n, &n, &
				c_n1, &c_n1, &nrhs, &imat, &nfail, &nerrs, 
				nout);
		    }

		    zget04_(&n, &nrhs, &x[1], &lda, &xact[1], &lda, &rcondc, &
			    result[4]);
		    zppt05_(uplo, &n, &nrhs, &a[1], &b[1], &lda, &x[1], &lda, 
			    &xact[1], &lda, &rwork[1], &rwork[nrhs + 1], &
			    result[5]);

/*                 Print information about the tests that did not pass   
                   the threshold. */

		    for (k = 3; k <= 7; ++k) {
			if (result[k - 1] >= *thresh) {
			    if (nfail == 0 && nerrs == 0) {
				alahd_(nout, path);
			    }
			    io___41.ciunit = *nout;
			    s_wsfe(&io___41);
			    do_fio(&c__1, uplo, (ftnlen)1);
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&nrhs, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&result[k - 1], (ftnlen)
				    sizeof(doublereal));
			    e_wsfe();
			    ++nfail;
			}
/* L120: */
		    }
		    nrun += 5;
/* L130: */
		}

/* +    TEST 8   
                Get an estimate of RCOND = 1/CNDNUM. */

L140:
		anorm = zlanhp_("1", uplo, &n, &a[1], &rwork[1]);
		s_copy(srnamc_1.srnamt, "ZHPCON", (ftnlen)6, (ftnlen)6);
		zhpcon_(uplo, &n, &afac[1], &iwork[1], &anorm, &rcond, &work[
			1], &info);

/*              Check error code from ZHPCON. */

		if (info != 0) {
		    alaerh_(path, "ZHPCON", &info, &c__0, uplo, &n, &n, &c_n1,
			     &c_n1, &c_n1, &imat, &nfail, &nerrs, nout);
		}

		result[7] = dget06_(&rcond, &rcondc);

/*              Print the test ratio if it is .GE. THRESH. */

		if (result[7] >= *thresh) {
		    if (nfail == 0 && nerrs == 0) {
			alahd_(nout, path);
		    }
		    io___43.ciunit = *nout;
		    s_wsfe(&io___43);
		    do_fio(&c__1, uplo, (ftnlen)1);
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&c__8, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&result[7], (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		    ++nfail;
		}
		++nrun;
L150:
		;
	    }
L160:
	    ;
	}
/* L170: */
    }

/*     Print a summary of the results. */

    alasum_(path, nout, &nfail, &nrun, &nerrs);

    return 0;

/*     End of ZCHKHP */

} /* zchkhp_ */

