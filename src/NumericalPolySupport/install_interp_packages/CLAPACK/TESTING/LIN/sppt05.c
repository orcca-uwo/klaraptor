#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int sppt05_(char *uplo, integer *n, integer *nrhs, real *ap, 
	real *b, integer *ldb, real *x, integer *ldx, real *xact, integer *
	ldxact, real *ferr, real *berr, real *reslts)
{
    /* System generated locals */
    integer b_dim1, b_offset, x_dim1, x_offset, xact_dim1, xact_offset, i__1, 
	    i__2, i__3;
    real r__1, r__2, r__3;

    /* Local variables */
    static real diff, axbi;
    static integer imax;
    static real unfl, ovfl;
    static integer i__, j, k;
    extern logical lsame_(char *, char *);
    static logical upper;
    static real xnorm;
    static integer jc;
    extern doublereal slamch_(char *);
    static real errbnd;
    extern integer isamax_(integer *, real *, integer *);
    static real eps, tmp;


#define xact_ref(a_1,a_2) xact[(a_2)*xact_dim1 + a_1]
#define b_ref(a_1,a_2) b[(a_2)*b_dim1 + a_1]
#define x_ref(a_1,a_2) x[(a_2)*x_dim1 + a_1]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    SPPT05 tests the error bounds from iterative refinement for the   
    computed solution to a system of equations A*X = B, where A is a   
    symmetric matrix in packed storage format.   

    RESLTS(1) = test of the error bound   
              = norm(X - XACT) / ( norm(X) * FERR )   

    A large value is returned if this ratio is not less than one.   

    RESLTS(2) = residual from the iterative refinement routine   
              = the maximum of BERR / ( (n+1)*EPS + (*) ), where   
                (*) = (n+1)*UNFL / (min_i (abs(A)*abs(X) +abs(b))_i )   

    Arguments   
    =========   

    UPLO    (input) CHARACTER*1   
            Specifies whether the upper or lower triangular part of the   
            symmetric matrix A is stored.   
            = 'U':  Upper triangular   
            = 'L':  Lower triangular   

    N       (input) INTEGER   
            The number of rows of the matrices X, B, and XACT, and the   
            order of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of columns of the matrices X, B, and XACT.   
            NRHS >= 0.   

    AP      (input) REAL array, dimension (N*(N+1)/2)   
            The upper or lower triangle of the symmetric matrix A, packed   
            columnwise in a linear array.  The j-th column of A is stored   
            in the array AP as follows:   
            if UPLO = 'U', AP(i + (j-1)*j/2) = A(i,j) for 1<=i<=j;   
            if UPLO = 'L', AP(i + (j-1)*(2n-j)/2) = A(i,j) for j<=i<=n.   

    B       (input) REAL array, dimension (LDB,NRHS)   
            The right hand side vectors for the system of linear   
            equations.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    X       (input) REAL array, dimension (LDX,NRHS)   
            The computed solution vectors.  Each vector is stored as a   
            column of the matrix X.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.  LDX >= max(1,N).   

    XACT    (input) REAL array, dimension (LDX,NRHS)   
            The exact solution vectors.  Each vector is stored as a   
            column of the matrix XACT.   

    LDXACT  (input) INTEGER   
            The leading dimension of the array XACT.  LDXACT >= max(1,N).   

    FERR    (input) REAL array, dimension (NRHS)   
            The estimated forward error bounds for each solution vector   
            X.  If XTRUE is the true solution, FERR bounds the magnitude   
            of the largest entry in (X - XTRUE) divided by the magnitude   
            of the largest entry in X.   

    BERR    (input) REAL array, dimension (NRHS)   
            The componentwise relative backward error of each solution   
            vector (i.e., the smallest relative change in any entry of A   
            or B that makes X an exact solution).   

    RESLTS  (output) REAL array, dimension (2)   
            The maximum over the NRHS solution vectors of the ratios:   
            RESLTS(1) = norm(X - XACT) / ( norm(X) * FERR )   
            RESLTS(2) = BERR / ( (n+1)*EPS + (*) )   

    =====================================================================   


       Quick exit if N = 0 or NRHS = 0.   

       Parameter adjustments */
    --ap;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1 * 1;
    x -= x_offset;
    xact_dim1 = *ldxact;
    xact_offset = 1 + xact_dim1 * 1;
    xact -= xact_offset;
    --ferr;
    --berr;
    --reslts;

    /* Function Body */
    if (*n <= 0 || *nrhs <= 0) {
	reslts[1] = 0.f;
	reslts[2] = 0.f;
	return 0;
    }

    eps = slamch_("Epsilon");
    unfl = slamch_("Safe minimum");
    ovfl = 1.f / unfl;
    upper = lsame_(uplo, "U");

/*     Test 1:  Compute the maximum of   
          norm(X - XACT) / ( norm(X) * FERR )   
       over all the vectors X and XACT using the infinity-norm. */

    errbnd = 0.f;
    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	imax = isamax_(n, &x_ref(1, j), &c__1);
/* Computing MAX */
	r__2 = (r__1 = x_ref(imax, j), dabs(r__1));
	xnorm = dmax(r__2,unfl);
	diff = 0.f;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
	    r__2 = diff, r__3 = (r__1 = x_ref(i__, j) - xact_ref(i__, j), 
		    dabs(r__1));
	    diff = dmax(r__2,r__3);
/* L10: */
	}

	if (xnorm > 1.f) {
	    goto L20;
	} else if (diff <= ovfl * xnorm) {
	    goto L20;
	} else {
	    errbnd = 1.f / eps;
	    goto L30;
	}

L20:
	if (diff / xnorm <= ferr[j]) {
/* Computing MAX */
	    r__1 = errbnd, r__2 = diff / xnorm / ferr[j];
	    errbnd = dmax(r__1,r__2);
	} else {
	    errbnd = 1.f / eps;
	}
L30:
	;
    }
    reslts[1] = errbnd;

/*     Test 2:  Compute the maximum of BERR / ( (n+1)*EPS + (*) ), where   
       (*) = (n+1)*UNFL / (min_i (abs(A)*abs(X) +abs(b))_i ) */

    i__1 = *nrhs;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    tmp = (r__1 = b_ref(i__, k), dabs(r__1));
	    if (upper) {
		jc = (i__ - 1) * i__ / 2;
		i__3 = i__;
		for (j = 1; j <= i__3; ++j) {
		    tmp += (r__1 = ap[jc + j], dabs(r__1)) * (r__2 = x_ref(j, 
			    k), dabs(r__2));
/* L40: */
		}
		jc += i__;
		i__3 = *n;
		for (j = i__ + 1; j <= i__3; ++j) {
		    tmp += (r__1 = ap[jc], dabs(r__1)) * (r__2 = x_ref(j, k), 
			    dabs(r__2));
		    jc += j;
/* L50: */
		}
	    } else {
		jc = i__;
		i__3 = i__ - 1;
		for (j = 1; j <= i__3; ++j) {
		    tmp += (r__1 = ap[jc], dabs(r__1)) * (r__2 = x_ref(j, k), 
			    dabs(r__2));
		    jc = jc + *n - j;
/* L60: */
		}
		i__3 = *n;
		for (j = i__; j <= i__3; ++j) {
		    tmp += (r__1 = ap[jc + j - i__], dabs(r__1)) * (r__2 = 
			    x_ref(j, k), dabs(r__2));
/* L70: */
		}
	    }
	    if (i__ == 1) {
		axbi = tmp;
	    } else {
		axbi = dmin(axbi,tmp);
	    }
/* L80: */
	}
/* Computing MAX */
	r__1 = axbi, r__2 = (*n + 1) * unfl;
	tmp = berr[k] / ((*n + 1) * eps + (*n + 1) * unfl / dmax(r__1,r__2));
	if (k == 1) {
	    reslts[2] = tmp;
	} else {
	    reslts[2] = dmax(reslts[2],tmp);
	}
/* L90: */
    }

    return 0;

/*     End of SPPT05 */

} /* sppt05_ */

#undef x_ref
#undef b_ref
#undef xact_ref


