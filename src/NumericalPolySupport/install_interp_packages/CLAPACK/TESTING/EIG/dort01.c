#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublereal c_b7 = 0.;
static doublereal c_b8 = 1.;
static doublereal c_b10 = -1.;
static integer c__1 = 1;

/* Subroutine */ int dort01_(char *rowcol, integer *m, integer *n, doublereal 
	*u, integer *ldu, doublereal *work, integer *lwork, doublereal *resid)
{
    /* System generated locals */
    integer u_dim1, u_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Local variables */
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer i__, j, k;
    extern logical lsame_(char *, char *);
    static integer mnmin;
    extern /* Subroutine */ int dsyrk_(char *, char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     integer *);
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int dlaset_(char *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *);
    extern doublereal dlansy_(char *, char *, integer *, doublereal *, 
	    integer *, doublereal *);
    static integer ldwork;
    static char transu[1];
    static doublereal eps, tmp;


#define u_ref(a_1,a_2) u[(a_2)*u_dim1 + a_1]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DORT01 checks that the matrix U is orthogonal by computing the ratio   

       RESID = norm( I - U*U' ) / ( n * EPS ), if ROWCOL = 'R',   
    or   
       RESID = norm( I - U'*U ) / ( m * EPS ), if ROWCOL = 'C'.   

    Alternatively, if there isn't sufficient workspace to form   
    I - U*U' or I - U'*U, the ratio is computed as   

       RESID = abs( I - U*U' ) / ( n * EPS ), if ROWCOL = 'R',   
    or   
       RESID = abs( I - U'*U ) / ( m * EPS ), if ROWCOL = 'C'.   

    where EPS is the machine precision.  ROWCOL is used only if m = n;   
    if m > n, ROWCOL is assumed to be 'C', and if m < n, ROWCOL is   
    assumed to be 'R'.   

    Arguments   
    =========   

    ROWCOL  (input) CHARACTER   
            Specifies whether the rows or columns of U should be checked   
            for orthogonality.  Used only if M = N.   
            = 'R':  Check for orthogonal rows of U   
            = 'C':  Check for orthogonal columns of U   

    M       (input) INTEGER   
            The number of rows of the matrix U.   

    N       (input) INTEGER   
            The number of columns of the matrix U.   

    U       (input) DOUBLE PRECISION array, dimension (LDU,N)   
            The orthogonal matrix U.  U is checked for orthogonal columns   
            if m > n or if m = n and ROWCOL = 'C'.  U is checked for   
            orthogonal rows if m < n or if m = n and ROWCOL = 'R'.   

    LDU     (input) INTEGER   
            The leading dimension of the array U.  LDU >= max(1,M).   

    WORK    (workspace) DOUBLE PRECISION array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The length of the array WORK.  For best performance, LWORK   
            should be at least N*(N+1) if ROWCOL = 'C' or M*(M+1) if   
            ROWCOL = 'R', but the test will be done even if LWORK is 0.   

    RESID   (output) DOUBLE PRECISION   
            RESID = norm( I - U * U' ) / ( n * EPS ), if ROWCOL = 'R', or   
            RESID = norm( I - U' * U ) / ( m * EPS ), if ROWCOL = 'C'.   

    =====================================================================   


       Parameter adjustments */
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1 * 1;
    u -= u_offset;
    --work;

    /* Function Body */
    *resid = 0.;

/*     Quick return if possible */

    if (*m <= 0 || *n <= 0) {
	return 0;
    }

    eps = dlamch_("Precision");
    if (*m < *n || *m == *n && lsame_(rowcol, "R")) {
	*(unsigned char *)transu = 'N';
	k = *n;
    } else {
	*(unsigned char *)transu = 'T';
	k = *m;
    }
    mnmin = min(*m,*n);

    if ((mnmin + 1) * mnmin <= *lwork) {
	ldwork = mnmin;
    } else {
	ldwork = 0;
    }
    if (ldwork > 0) {

/*        Compute I - U*U' or I - U'*U. */

	dlaset_("Upper", &mnmin, &mnmin, &c_b7, &c_b8, &work[1], &ldwork);
	dsyrk_("Upper", transu, &mnmin, &k, &c_b10, &u[u_offset], ldu, &c_b8, 
		&work[1], &ldwork);

/*        Compute norm( I - U*U' ) / ( K * EPS ) . */

	*resid = dlansy_("1", "Upper", &mnmin, &work[1], &ldwork, &work[
		ldwork * mnmin + 1]);
	*resid = *resid / (doublereal) k / eps;
    } else if (*(unsigned char *)transu == 'T') {

/*        Find the maximum element in abs( I - U'*U ) / ( m * EPS ) */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = j;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (i__ != j) {
		    tmp = 0.;
		} else {
		    tmp = 1.;
		}
		tmp -= ddot_(m, &u_ref(1, i__), &c__1, &u_ref(1, j), &c__1);
/* Computing MAX */
		d__1 = *resid, d__2 = abs(tmp);
		*resid = max(d__1,d__2);
/* L10: */
	    }
/* L20: */
	}
	*resid = *resid / (doublereal) (*m) / eps;
    } else {

/*        Find the maximum element in abs( I - U*U' ) / ( n * EPS ) */

	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = j;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (i__ != j) {
		    tmp = 0.;
		} else {
		    tmp = 1.;
		}
		tmp -= ddot_(n, &u_ref(j, 1), ldu, &u_ref(i__, 1), ldu);
/* Computing MAX */
		d__1 = *resid, d__2 = abs(tmp);
		*resid = max(d__1,d__2);
/* L30: */
	    }
/* L40: */
	}
	*resid = *resid / (doublereal) (*n) / eps;
    }
    return 0;

/*     End of DORT01 */

} /* dort01_ */

#undef u_ref


