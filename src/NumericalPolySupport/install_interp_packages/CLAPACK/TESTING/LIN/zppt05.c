#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int zppt05_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, doublecomplex *b, integer *ldb, doublecomplex *x, 
	integer *ldx, doublecomplex *xact, integer *ldxact, doublereal *ferr, 
	doublereal *berr, doublereal *reslts)
{
    /* System generated locals */
    integer b_dim1, b_offset, x_dim1, x_offset, xact_dim1, xact_offset, i__1, 
	    i__2, i__3, i__4, i__5;
    doublereal d__1, d__2, d__3, d__4;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    double d_imag(doublecomplex *);

    /* Local variables */
    static doublereal diff, axbi;
    static integer imax;
    static doublereal unfl, ovfl;
    static integer i__, j, k;
    extern logical lsame_(char *, char *);
    static logical upper;
    static doublereal xnorm;
    static integer jc;
    extern doublereal dlamch_(char *);
    static doublereal errbnd;
    extern integer izamax_(integer *, doublecomplex *, integer *);
    static doublereal eps, tmp;


#define xact_subscr(a_1,a_2) (a_2)*xact_dim1 + a_1
#define xact_ref(a_1,a_2) xact[xact_subscr(a_1,a_2)]
#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]
#define x_subscr(a_1,a_2) (a_2)*x_dim1 + a_1
#define x_ref(a_1,a_2) x[x_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    ZPPT05 tests the error bounds from iterative refinement for the   
    computed solution to a system of equations A*X = B, where A is a   
    Hermitian matrix in packed storage format.   

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
            Hermitian matrix A is stored.   
            = 'U':  Upper triangular   
            = 'L':  Lower triangular   

    N       (input) INTEGER   
            The number of rows of the matrices X, B, and XACT, and the   
            order of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of columns of the matrices X, B, and XACT.   
            NRHS >= 0.   

    AP      (input) COMPLEX*16 array, dimension (N*(N+1)/2)   
            The upper or lower triangle of the Hermitian matrix A, packed   
            columnwise in a linear array.  The j-th column of A is stored   
            in the array AP as follows:   
            if UPLO = 'U', AP(i + (j-1)*j/2) = A(i,j) for 1<=i<=j;   
            if UPLO = 'L', AP(i + (j-1)*(2n-j)/2) = A(i,j) for j<=i<=n.   

    B       (input) COMPLEX*16 array, dimension (LDB,NRHS)   
            The right hand side vectors for the system of linear   
            equations.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    X       (input) COMPLEX*16 array, dimension (LDX,NRHS)   
            The computed solution vectors.  Each vector is stored as a   
            column of the matrix X.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.  LDX >= max(1,N).   

    XACT    (input) COMPLEX*16 array, dimension (LDX,NRHS)   
            The exact solution vectors.  Each vector is stored as a   
            column of the matrix XACT.   

    LDXACT  (input) INTEGER   
            The leading dimension of the array XACT.  LDXACT >= max(1,N).   

    FERR    (input) DOUBLE PRECISION array, dimension (NRHS)   
            The estimated forward error bounds for each solution vector   
            X.  If XTRUE is the true solution, FERR bounds the magnitude   
            of the largest entry in (X - XTRUE) divided by the magnitude   
            of the largest entry in X.   

    BERR    (input) DOUBLE PRECISION array, dimension (NRHS)   
            The componentwise relative backward error of each solution   
            vector (i.e., the smallest relative change in any entry of A   
            or B that makes X an exact solution).   

    RESLTS  (output) DOUBLE PRECISION array, dimension (2)   
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
	reslts[1] = 0.;
	reslts[2] = 0.;
	return 0;
    }

    eps = dlamch_("Epsilon");
    unfl = dlamch_("Safe minimum");
    ovfl = 1. / unfl;
    upper = lsame_(uplo, "U");

/*     Test 1:  Compute the maximum of   
          norm(X - XACT) / ( norm(X) * FERR )   
       over all the vectors X and XACT using the infinity-norm. */

    errbnd = 0.;
    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	imax = izamax_(n, &x_ref(1, j), &c__1);
/* Computing MAX */
	i__2 = x_subscr(imax, j);
	d__3 = (d__1 = x[i__2].r, abs(d__1)) + (d__2 = d_imag(&x_ref(imax, j))
		, abs(d__2));
	xnorm = max(d__3,unfl);
	diff = 0.;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = x_subscr(i__, j);
	    i__4 = xact_subscr(i__, j);
	    z__2.r = x[i__3].r - xact[i__4].r, z__2.i = x[i__3].i - xact[i__4]
		    .i;
	    z__1.r = z__2.r, z__1.i = z__2.i;
/* Computing MAX */
	    d__3 = diff, d__4 = (d__1 = z__1.r, abs(d__1)) + (d__2 = d_imag(&
		    z__1), abs(d__2));
	    diff = max(d__3,d__4);
/* L10: */
	}

	if (xnorm > 1.) {
	    goto L20;
	} else if (diff <= ovfl * xnorm) {
	    goto L20;
	} else {
	    errbnd = 1. / eps;
	    goto L30;
	}

L20:
	if (diff / xnorm <= ferr[j]) {
/* Computing MAX */
	    d__1 = errbnd, d__2 = diff / xnorm / ferr[j];
	    errbnd = max(d__1,d__2);
	} else {
	    errbnd = 1. / eps;
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
	    i__3 = b_subscr(i__, k);
	    tmp = (d__1 = b[i__3].r, abs(d__1)) + (d__2 = d_imag(&b_ref(i__, 
		    k)), abs(d__2));
	    if (upper) {
		jc = (i__ - 1) * i__ / 2;
		i__3 = i__ - 1;
		for (j = 1; j <= i__3; ++j) {
		    i__4 = jc + j;
		    i__5 = x_subscr(j, k);
		    tmp += ((d__1 = ap[i__4].r, abs(d__1)) + (d__2 = d_imag(&
			    ap[jc + j]), abs(d__2))) * ((d__3 = x[i__5].r, 
			    abs(d__3)) + (d__4 = d_imag(&x_ref(j, k)), abs(
			    d__4)));
/* L40: */
		}
		i__3 = jc + i__;
		i__4 = x_subscr(i__, k);
		tmp += (d__1 = ap[i__3].r, abs(d__1)) * ((d__2 = x[i__4].r, 
			abs(d__2)) + (d__3 = d_imag(&x_ref(i__, k)), abs(d__3)
			));
		jc = jc + i__ + i__;
		i__3 = *n;
		for (j = i__ + 1; j <= i__3; ++j) {
		    i__4 = jc;
		    i__5 = x_subscr(j, k);
		    tmp += ((d__1 = ap[i__4].r, abs(d__1)) + (d__2 = d_imag(&
			    ap[jc]), abs(d__2))) * ((d__3 = x[i__5].r, abs(
			    d__3)) + (d__4 = d_imag(&x_ref(j, k)), abs(d__4)))
			    ;
		    jc += j;
/* L50: */
		}
	    } else {
		jc = i__;
		i__3 = i__ - 1;
		for (j = 1; j <= i__3; ++j) {
		    i__4 = jc;
		    i__5 = x_subscr(j, k);
		    tmp += ((d__1 = ap[i__4].r, abs(d__1)) + (d__2 = d_imag(&
			    ap[jc]), abs(d__2))) * ((d__3 = x[i__5].r, abs(
			    d__3)) + (d__4 = d_imag(&x_ref(j, k)), abs(d__4)))
			    ;
		    jc = jc + *n - j;
/* L60: */
		}
		i__3 = jc;
		i__4 = x_subscr(i__, k);
		tmp += (d__1 = ap[i__3].r, abs(d__1)) * ((d__2 = x[i__4].r, 
			abs(d__2)) + (d__3 = d_imag(&x_ref(i__, k)), abs(d__3)
			));
		i__3 = *n;
		for (j = i__ + 1; j <= i__3; ++j) {
		    i__4 = jc + j - i__;
		    i__5 = x_subscr(j, k);
		    tmp += ((d__1 = ap[i__4].r, abs(d__1)) + (d__2 = d_imag(&
			    ap[jc + j - i__]), abs(d__2))) * ((d__3 = x[i__5]
			    .r, abs(d__3)) + (d__4 = d_imag(&x_ref(j, k)), 
			    abs(d__4)));
/* L70: */
		}
	    }
	    if (i__ == 1) {
		axbi = tmp;
	    } else {
		axbi = min(axbi,tmp);
	    }
/* L80: */
	}
/* Computing MAX */
	d__1 = axbi, d__2 = (*n + 1) * unfl;
	tmp = berr[k] / ((*n + 1) * eps + (*n + 1) * unfl / max(d__1,d__2));
	if (k == 1) {
	    reslts[2] = tmp;
	} else {
	    reslts[2] = max(reslts[2],tmp);
	}
/* L90: */
    }

    return 0;

/*     End of ZPPT05 */

} /* zppt05_ */

#undef x_ref
#undef x_subscr
#undef b_ref
#undef b_subscr
#undef xact_ref
#undef xact_subscr


