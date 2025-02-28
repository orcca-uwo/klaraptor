#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    real ops, itcnt;
} latime_;

#define latime_1 latime_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int slasdq_(char *uplo, integer *sqre, integer *n, integer *
	ncvt, integer *nru, integer *ncc, real *d__, real *e, real *vt, 
	integer *ldvt, real *u, integer *ldu, real *c__, integer *ldc, real *
	work, integer *info)
{
    /* System generated locals */
    integer c_dim1, c_offset, u_dim1, u_offset, vt_dim1, vt_offset, i__1, 
	    i__2;

    /* Local variables */
    static integer isub;
    static real smin;
    static integer sqre1, i__, j;
    static real r__;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int slasr_(char *, char *, char *, integer *, 
	    integer *, real *, real *, real *, integer *);
    static integer iuplo;
    extern /* Subroutine */ int sswap_(integer *, real *, integer *, real *, 
	    integer *);
    static real cs, sn;
    extern /* Subroutine */ int xerbla_(char *, integer *), slartg_(
	    real *, real *, real *, real *, real *);
    static logical rotate;
    extern /* Subroutine */ int sbdsqr_(char *, integer *, integer *, integer 
	    *, integer *, real *, real *, real *, integer *, real *, integer *
	    , real *, integer *, real *, integer *);
    static integer np1;


#define c___ref(a_1,a_2) c__[(a_2)*c_dim1 + a_1]
#define u_ref(a_1,a_2) u[(a_2)*u_dim1 + a_1]
#define vt_ref(a_1,a_2) vt[(a_2)*vt_dim1 + a_1]


/*  -- LAPACK auxiliary routine (instrumented to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1999   


    Purpose   
    =======   

    SLASDQ computes the singular value decomposition (SVD) of a real   
    (upper or lower) bidiagonal matrix with diagonal D and offdiagonal   
    E, accumulating the transformations if desired. Letting B denote   
    the input bidiagonal matrix, the algorithm computes orthogonal   
    matrices Q and P such that B = Q * S * P' (P' denotes the transpose   
    of P). The singular values S are overwritten on D.   

    The input matrix U  is changed to U  * Q  if desired.   
    The input matrix VT is changed to P' * VT if desired.   
    The input matrix C  is changed to Q' * C  if desired.   

    See "Computing  Small Singular Values of Bidiagonal Matrices With   
    Guaranteed High Relative Accuracy," by J. Demmel and W. Kahan,   
    LAPACK Working Note #3, for a detailed description of the algorithm.   

    Arguments   
    =========   

    UPLO  (input) CHARACTER*1   
          On entry, UPLO specifies whether the input bidiagonal matrix   
          is upper or lower bidiagonal, and wether it is square are   
          not.   
             UPLO = 'U' or 'u'   B is upper bidiagonal.   
             UPLO = 'L' or 'l'   B is lower bidiagonal.   

    SQRE  (input) INTEGER   
          = 0: then the input matrix is N-by-N.   
          = 1: then the input matrix is N-by-(N+1) if UPLU = 'U' and   
               (N+1)-by-N if UPLU = 'L'.   

          The bidiagonal matrix has   
          N = NL + NR + 1 rows and   
          M = N + SQRE >= N columns.   

    N     (input) INTEGER   
          On entry, N specifies the number of rows and columns   
          in the matrix. N must be at least 0.   

    NCVT  (input) INTEGER   
          On entry, NCVT specifies the number of columns of   
          the matrix VT. NCVT must be at least 0.   

    NRU   (input) INTEGER   
          On entry, NRU specifies the number of rows of   
          the matrix U. NRU must be at least 0.   

    NCC   (input) INTEGER   
          On entry, NCC specifies the number of columns of   
          the matrix C. NCC must be at least 0.   

    D     (input/output) REAL array, dimension (N)   
          On entry, D contains the diagonal entries of the   
          bidiagonal matrix whose SVD is desired. On normal exit,   
          D contains the singular values in ascending order.   

    E     (input/output) REAL array.   
          dimension is (N-1) if SQRE = 0 and N if SQRE = 1.   
          On entry, the entries of E contain the offdiagonal entries   
          of the bidiagonal matrix whose SVD is desired. On normal   
          exit, E will contain 0. If the algorithm does not converge,   
          D and E will contain the diagonal and superdiagonal entries   
          of a bidiagonal matrix orthogonally equivalent to the one   
          given as input.   

    VT    (input/output) REAL array, dimension (LDVT, NCVT)   
          On entry, contains a matrix which on exit has been   
          premultiplied by P', dimension N-by-NCVT if SQRE = 0   
          and (N+1)-by-NCVT if SQRE = 1 (not referenced if NCVT=0).   

    LDVT  (input) INTEGER   
          On entry, LDVT specifies the leading dimension of VT as   
          declared in the calling (sub) program. LDVT must be at   
          least 1. If NCVT is nonzero LDVT must also be at least N.   

    U     (input/output) REAL array, dimension (LDU, N)   
          On entry, contains a  matrix which on exit has been   
          postmultiplied by Q, dimension NRU-by-N if SQRE = 0   
          and NRU-by-(N+1) if SQRE = 1 (not referenced if NRU=0).   

    LDU   (input) INTEGER   
          On entry, LDU  specifies the leading dimension of U as   
          declared in the calling (sub) program. LDU must be at   
          least max( 1, NRU ) .   

    C     (input/output) REAL array, dimension (LDC, NCC)   
          On entry, contains an N-by-NCC matrix which on exit   
          has been premultiplied by Q'  dimension N-by-NCC if SQRE = 0   
          and (N+1)-by-NCC if SQRE = 1 (not referenced if NCC=0).   

    LDC   (input) INTEGER   
          On entry, LDC  specifies the leading dimension of C as   
          declared in the calling (sub) program. LDC must be at   
          least 1. If NCC is nonzero, LDC must also be at least N.   

    WORK  (workspace) REAL array, dimension (MAX( 1, 4*N ))   
          Workspace. Only referenced if one of NCVT, NRU, or NCC is   
          nonzero, and if N is at least 2.   

    INFO  (output) INTEGER   
          On exit, a value of 0 indicates a successful exit.   
          If INFO < 0, argument number -INFO is illegal.   
          If INFO > 0, the algorithm did not converge, and INFO   
          specifies how many superdiagonals did not converge.   

    Further Details   
    ===============   

    Based on contributions by   
       Ming Gu and Huan Ren, Computer Science Division, University of   
       California at Berkeley, USA   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    --d__;
    --e;
    vt_dim1 = *ldvt;
    vt_offset = 1 + vt_dim1 * 1;
    vt -= vt_offset;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1 * 1;
    u -= u_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    iuplo = 0;
    if (lsame_(uplo, "U")) {
	iuplo = 1;
    }
    if (lsame_(uplo, "L")) {
	iuplo = 2;
    }
    if (iuplo == 0) {
	*info = -1;
    } else if (*sqre < 0 || *sqre > 1) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*ncvt < 0) {
	*info = -4;
    } else if (*nru < 0) {
	*info = -5;
    } else if (*ncc < 0) {
	*info = -6;
    } else if (*ncvt == 0 && *ldvt < 1 || *ncvt > 0 && *ldvt < max(1,*n)) {
	*info = -10;
    } else if (*ldu < max(1,*nru)) {
	*info = -12;
    } else if (*ncc == 0 && *ldc < 1 || *ncc > 0 && *ldc < max(1,*n)) {
	*info = -14;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SBDSQR", &i__1);
	return 0;
    }
    if (*n == 0) {
	return 0;
    }

/*     ROTATE is true if any singular vectors desired, false otherwise */

    rotate = *ncvt > 0 || *nru > 0 || *ncc > 0;
    np1 = *n + 1;
    sqre1 = *sqre;

/*     If matrix non-square upper bidiagonal, rotate to be lower   
       bidiagonal.  The rotations are on the right. */

    if (iuplo == 1 && sqre1 == 1) {
	latime_1.ops += (real) (*n - 1 << 3);
	i__1 = *n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    slartg_(&d__[i__], &e[i__], &cs, &sn, &r__);
	    d__[i__] = r__;
	    e[i__] = sn * d__[i__ + 1];
	    d__[i__ + 1] = cs * d__[i__ + 1];
	    if (rotate) {
		work[i__] = cs;
		work[*n + i__] = sn;
	    }
/* L10: */
	}
	latime_1.ops += 6.f;
	slartg_(&d__[*n], &e[*n], &cs, &sn, &r__);
	d__[*n] = r__;
	e[*n] = 0.f;
	if (rotate) {
	    work[*n] = cs;
	    work[*n + *n] = sn;
	}
	iuplo = 2;
	sqre1 = 0;

/*        Update singular vectors if desired. */

	if (*ncvt > 0) {
	    latime_1.ops += (real) ((np1 - 1) * 6 * *ncvt);
	    slasr_("L", "V", "F", &np1, ncvt, &work[1], &work[np1], &vt[
		    vt_offset], ldvt);
	}
    }

/*     If matrix lower bidiagonal, rotate to be upper bidiagonal   
       by applying Givens rotations on the left. */

    if (iuplo == 2) {
	latime_1.ops += (real) (*n - 1 << 3);
	i__1 = *n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    slartg_(&d__[i__], &e[i__], &cs, &sn, &r__);
	    d__[i__] = r__;
	    e[i__] = sn * d__[i__ + 1];
	    d__[i__ + 1] = cs * d__[i__ + 1];
	    if (rotate) {
		work[i__] = cs;
		work[*n + i__] = sn;
	    }
/* L20: */
	}

/*        If matrix (N+1)-by-N lower bidiagonal, one additional   
          rotation is needed. */

	if (sqre1 == 1) {
	    latime_1.ops += 6.f;
	    slartg_(&d__[*n], &e[*n], &cs, &sn, &r__);
	    d__[*n] = r__;
	    if (rotate) {
		work[*n] = cs;
		work[*n + *n] = sn;
	    }
	}

/*        Update singular vectors if desired. */

	if (*nru > 0) {
	    if (sqre1 == 0) {
		latime_1.ops += (real) ((*n - 1) * 6 * *nru);
		slasr_("R", "V", "F", nru, n, &work[1], &work[np1], &u[
			u_offset], ldu);
	    } else {
		latime_1.ops += (real) (*n * 6 * *nru);
		slasr_("R", "V", "F", nru, &np1, &work[1], &work[np1], &u[
			u_offset], ldu);
	    }
	}
	if (*ncc > 0) {
	    if (sqre1 == 0) {
		latime_1.ops += (real) ((*n - 1) * 6 * *ncc);
		slasr_("L", "V", "F", n, ncc, &work[1], &work[np1], &c__[
			c_offset], ldc);
	    } else {
		latime_1.ops += (real) (*n * 6 * *ncc);
		slasr_("L", "V", "F", &np1, ncc, &work[1], &work[np1], &c__[
			c_offset], ldc);
	    }
	}
    }

/*     Call SBDSQR to compute the SVD of the reduced real   
       N-by-N upper bidiagonal matrix. */

    sbdsqr_("U", n, ncvt, nru, ncc, &d__[1], &e[1], &vt[vt_offset], ldvt, &u[
	    u_offset], ldu, &c__[c_offset], ldc, &work[1], info);

/*     Sort the singular values into ascending order (insertion sort on   
       singular values, but only one transposition per singular vector) */

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        Scan for smallest D(I). */

	isub = i__;
	smin = d__[i__];
	i__2 = *n;
	for (j = i__ + 1; j <= i__2; ++j) {
	    if (d__[j] < smin) {
		isub = j;
		smin = d__[j];
	    }
/* L30: */
	}
	if (isub != i__) {

/*           Swap singular values and vectors. */

	    d__[isub] = d__[i__];
	    d__[i__] = smin;
	    if (*ncvt > 0) {
		sswap_(ncvt, &vt_ref(isub, 1), ldvt, &vt_ref(i__, 1), ldvt);
	    }
	    if (*nru > 0) {
		sswap_(nru, &u_ref(1, isub), &c__1, &u_ref(1, i__), &c__1);
	    }
	    if (*ncc > 0) {
		sswap_(ncc, &c___ref(isub, 1), ldc, &c___ref(i__, 1), ldc);
	    }
	}
/* L40: */
    }

    return 0;

/*     End of SLASDQ */

} /* slasdq_ */

#undef vt_ref
#undef u_ref
#undef c___ref


