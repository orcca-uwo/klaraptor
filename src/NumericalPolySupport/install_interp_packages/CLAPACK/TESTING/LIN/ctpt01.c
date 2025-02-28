#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int ctpt01_(char *uplo, char *diag, integer *n, complex *ap, 
	complex *ainvp, real *rcond, real *rwork, real *resid)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    complex q__1;

    /* Local variables */
    static integer j;
    extern logical lsame_(char *, char *);
    static real anorm;
    static logical unitd;
    extern /* Subroutine */ int ctpmv_(char *, char *, char *, integer *, 
	    complex *, complex *, integer *);
    static integer jc;
    extern doublereal slamch_(char *), clantp_(char *, char *, char *,
	     integer *, complex *, real *);
    static real ainvnm, eps;


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    CTPT01 computes the residual for a triangular matrix A times its   
    inverse when A is stored in packed format:   
       RESID = norm(A*AINV - I) / ( N * norm(A) * norm(AINV) * EPS ),   
    where EPS is the machine epsilon.   

    Arguments   
    ==========   

    UPLO    (input) CHARACTER*1   
            Specifies whether the matrix A is upper or lower triangular.   
            = 'U':  Upper triangular   
            = 'L':  Lower triangular   

    DIAG    (input) CHARACTER*1   
            Specifies whether or not the matrix A is unit triangular.   
            = 'N':  Non-unit triangular   
            = 'U':  Unit triangular   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    AP      (input) COMPLEX array, dimension (N*(N+1)/2)   
            The original upper or lower triangular matrix A, packed   
            columnwise in a linear array.  The j-th column of A is stored   
            in the array AP as follows:   
            if UPLO = 'U', AP((j-1)*j/2 + i) = A(i,j) for 1<=i<=j;   
            if UPLO = 'L',   
               AP((j-1)*(n-j) + j*(j+1)/2 + i-j) = A(i,j) for j<=i<=n.   

    AINVP   (input) COMPLEX array, dimension (N*(N+1)/2)   
            On entry, the (triangular) inverse of the matrix A, packed   
            columnwise in a linear array as in AP.   
            On exit, the contents of AINVP are destroyed.   

    RCOND   (output) REAL   
            The reciprocal condition number of A, computed as   
            1/(norm(A) * norm(AINV)).   

    RWORK   (workspace) REAL array, dimension (N)   

    RESID   (output) REAL   
            norm(A*AINV - I) / ( N * norm(A) * norm(AINV) * EPS )   

    =====================================================================   


       Quick exit if N = 0.   

       Parameter adjustments */
    --rwork;
    --ainvp;
    --ap;

    /* Function Body */
    if (*n <= 0) {
	*rcond = 1.f;
	*resid = 0.f;
	return 0;
    }

/*     Exit with RESID = 1/EPS if ANORM = 0 or AINVNM = 0. */

    eps = slamch_("Epsilon");
    anorm = clantp_("1", uplo, diag, n, &ap[1], &rwork[1]);
    ainvnm = clantp_("1", uplo, diag, n, &ainvp[1], &rwork[1]);
    if (anorm <= 0.f || ainvnm <= 0.f) {
	*rcond = 0.f;
	*resid = 1.f / eps;
	return 0;
    }
    *rcond = 1.f / anorm / ainvnm;

/*     Compute A * AINV, overwriting AINV. */

    unitd = lsame_(diag, "U");
    if (lsame_(uplo, "U")) {
	jc = 1;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (unitd) {
		i__2 = jc + j - 1;
		ainvp[i__2].r = 1.f, ainvp[i__2].i = 0.f;
	    }

/*           Form the j-th column of A*AINV. */

	    ctpmv_("Upper", "No transpose", diag, &j, &ap[1], &ainvp[jc], &
		    c__1);

/*           Subtract 1 from the diagonal to form A*AINV - I. */

	    i__2 = jc + j - 1;
	    i__3 = jc + j - 1;
	    q__1.r = ainvp[i__3].r - 1.f, q__1.i = ainvp[i__3].i;
	    ainvp[i__2].r = q__1.r, ainvp[i__2].i = q__1.i;
	    jc += j;
/* L10: */
	}
    } else {
	jc = 1;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (unitd) {
		i__2 = jc;
		ainvp[i__2].r = 1.f, ainvp[i__2].i = 0.f;
	    }

/*           Form the j-th column of A*AINV. */

	    i__2 = *n - j + 1;
	    ctpmv_("Lower", "No transpose", diag, &i__2, &ap[jc], &ainvp[jc], 
		    &c__1);

/*           Subtract 1 from the diagonal to form A*AINV - I. */

	    i__2 = jc;
	    i__3 = jc;
	    q__1.r = ainvp[i__3].r - 1.f, q__1.i = ainvp[i__3].i;
	    ainvp[i__2].r = q__1.r, ainvp[i__2].i = q__1.i;
	    jc = jc + *n - j + 1;
/* L20: */
	}
    }

/*     Compute norm(A*AINV - I) / (N * norm(A) * norm(AINV) * EPS) */

    *resid = clantp_("1", uplo, "Non-unit", n, &ainvp[1], &rwork[1]);

    *resid = *resid * *rcond / (real) (*n) / eps;

    return 0;

/*     End of CTPT01 */

} /* ctpt01_ */

