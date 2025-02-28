#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static doublereal c_b36 = -1.;
static doublereal c_b37 = 1.;
static integer c__1 = 1;

/* Subroutine */ int zgsvts_(integer *m, integer *p, integer *n, 
	doublecomplex *a, doublecomplex *af, integer *lda, doublecomplex *b, 
	doublecomplex *bf, integer *ldb, doublecomplex *u, integer *ldu, 
	doublecomplex *v, integer *ldv, doublecomplex *q, integer *ldq, 
	doublereal *alpha, doublereal *beta, doublecomplex *r__, integer *ldr,
	 integer *iwork, doublecomplex *work, integer *lwork, doublereal *
	rwork, doublereal *result)
{
    /* System generated locals */
    integer a_dim1, a_offset, af_dim1, af_offset, b_dim1, b_offset, bf_dim1, 
	    bf_offset, q_dim1, q_offset, r_dim1, r_offset, u_dim1, u_offset, 
	    v_dim1, v_offset, i__1, i__2, i__3, i__4, i__5, i__6;
    doublereal d__1;
    doublecomplex z__1, z__2;

    /* Local variables */
    static integer info;
    static doublereal unfl, temp;
    static integer i__, j, k, l;
    static doublereal resid, anorm, bnorm;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *), zgemm_(char *, char *, integer *, 
	    integer *, integer *, doublecomplex *, doublecomplex *, integer *,
	     doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *), zherk_(char *, char *, integer *, 
	    integer *, doublereal *, doublecomplex *, integer *, doublereal *,
	     doublecomplex *, integer *);
    extern doublereal dlamch_(char *), zlange_(char *, integer *, 
	    integer *, doublecomplex *, integer *, doublereal *), 
	    zlanhe_(char *, char *, integer *, doublecomplex *, integer *, 
	    doublereal *);
    extern /* Subroutine */ int zlacpy_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), 
	    zlaset_(char *, integer *, integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, integer *), zggsvd_(
	    char *, char *, char *, integer *, integer *, integer *, integer *
	    , integer *, doublecomplex *, integer *, doublecomplex *, integer 
	    *, doublereal *, doublereal *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, doublereal *, integer *, integer *);
    static doublereal ulpinv, ulp;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]
#define r___subscr(a_1,a_2) (a_2)*r_dim1 + a_1
#define r___ref(a_1,a_2) r__[r___subscr(a_1,a_2)]
#define af_subscr(a_1,a_2) (a_2)*af_dim1 + a_1
#define af_ref(a_1,a_2) af[af_subscr(a_1,a_2)]
#define bf_subscr(a_1,a_2) (a_2)*bf_dim1 + a_1
#define bf_ref(a_1,a_2) bf[bf_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    ZGSVTS tests ZGGSVD, which computes the GSVD of an M-by-N matrix A   
    and a P-by-N matrix B:   
                 U'*A*Q = D1*R and V'*B*Q = D2*R.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    P       (input) INTEGER   
            The number of rows of the matrix B.  P >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrices A and B.  N >= 0.   

    A       (input) COMPLEX*16 array, dimension (LDA,M)   
            The M-by-N matrix A.   

    AF      (output) COMPLEX*16 array, dimension (LDA,N)   
            Details of the GSVD of A and B, as returned by ZGGSVD,   
            see ZGGSVD for further details.   

    LDA     (input) INTEGER   
            The leading dimension of the arrays A and AF.   
            LDA >= max( 1,M ).   

    B       (input) COMPLEX*16 array, dimension (LDB,P)   
            On entry, the P-by-N matrix B.   

    BF      (output) COMPLEX*16 array, dimension (LDB,N)   
            Details of the GSVD of A and B, as returned by ZGGSVD,   
            see ZGGSVD for further details.   

    LDB     (input) INTEGER   
            The leading dimension of the arrays B and BF.   
            LDB >= max(1,P).   

    U       (output) COMPLEX*16 array, dimension(LDU,M)   
            The M by M unitary matrix U.   

    LDU     (input) INTEGER   
            The leading dimension of the array U. LDU >= max(1,M).   

    V       (output) COMPLEX*16 array, dimension(LDV,M)   
            The P by P unitary matrix V.   

    LDV     (input) INTEGER   
            The leading dimension of the array V. LDV >= max(1,P).   

    Q       (output) COMPLEX*16 array, dimension(LDQ,N)   
            The N by N unitary matrix Q.   

    LDQ     (input) INTEGER   
            The leading dimension of the array Q. LDQ >= max(1,N).   

    ALPHA   (output) DOUBLE PRECISION array, dimension (N)   
    BETA    (output) DOUBLE PRECISION array, dimension (N)   
            The generalized singular value pairs of A and B, the   
            ``diagonal'' matrices D1 and D2 are constructed from   
            ALPHA and BETA, see subroutine ZGGSVD for details.   

    R       (output) COMPLEX*16 array, dimension(LDQ,N)   
            The upper triangular matrix R.   

    LDR     (input) INTEGER   
            The leading dimension of the array R. LDR >= max(1,N).   

    IWORK   (workspace) INTEGER array, dimension (N)   

    WORK    (workspace) COMPLEX*16 array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The dimension of the array WORK,   
            LWORK >= max(M,P,N)*max(M,P,N).   

    RWORK   (workspace) DOUBLE PRECISION array, dimension (max(M,P,N))   

    RESULT  (output) DOUBLE PRECISION array, dimension (5)   
            The test ratios:   
            RESULT(1) = norm( U'*A*Q - D1*R ) / ( MAX(M,N)*norm(A)*ULP)   
            RESULT(2) = norm( V'*B*Q - D2*R ) / ( MAX(P,N)*norm(B)*ULP)   
            RESULT(3) = norm( I - U'*U ) / ( M*ULP )   
            RESULT(4) = norm( I - V'*V ) / ( P*ULP )   
            RESULT(5) = norm( I - Q'*Q ) / ( N*ULP )   
            RESULT(6) = 0        if ALPHA is in decreasing order;   
                      = ULPINV   otherwise.   

    =====================================================================   


       Parameter adjustments */
    af_dim1 = *lda;
    af_offset = 1 + af_dim1 * 1;
    af -= af_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    bf_dim1 = *ldb;
    bf_offset = 1 + bf_dim1 * 1;
    bf -= bf_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1 * 1;
    u -= u_offset;
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1 * 1;
    v -= v_offset;
    q_dim1 = *ldq;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    --alpha;
    --beta;
    r_dim1 = *ldr;
    r_offset = 1 + r_dim1 * 1;
    r__ -= r_offset;
    --iwork;
    --work;
    --rwork;
    --result;

    /* Function Body */
    ulp = dlamch_("Precision");
    ulpinv = 1. / ulp;
    unfl = dlamch_("Safe minimum");

/*     Copy the matrix A to the array AF. */

    zlacpy_("Full", m, n, &a[a_offset], lda, &af[af_offset], lda);
    zlacpy_("Full", p, n, &b[b_offset], ldb, &bf[bf_offset], ldb);

/* Computing MAX */
    d__1 = zlange_("1", m, n, &a[a_offset], lda, &rwork[1]);
    anorm = max(d__1,unfl);
/* Computing MAX */
    d__1 = zlange_("1", p, n, &b[b_offset], ldb, &rwork[1]);
    bnorm = max(d__1,unfl);

/*     Factorize the matrices A and B in the arrays AF and BF. */

    zggsvd_("U", "V", "Q", m, n, p, &k, &l, &af[af_offset], lda, &bf[
	    bf_offset], ldb, &alpha[1], &beta[1], &u[u_offset], ldu, &v[
	    v_offset], ldv, &q[q_offset], ldq, &work[1], &rwork[1], &iwork[1],
	     &info);

/*     Copy R   

   Computing MIN */
    i__2 = k + l;
    i__1 = min(i__2,*m);
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = k + l;
	for (j = i__; j <= i__2; ++j) {
	    i__3 = r___subscr(i__, j);
	    i__4 = af_subscr(i__, *n - k - l + j);
	    r__[i__3].r = af[i__4].r, r__[i__3].i = af[i__4].i;
/* L10: */
	}
/* L20: */
    }

    if (*m - k - l < 0) {
	i__1 = k + l;
	for (i__ = *m + 1; i__ <= i__1; ++i__) {
	    i__2 = k + l;
	    for (j = i__; j <= i__2; ++j) {
		i__3 = r___subscr(i__, j);
		i__4 = bf_subscr(i__ - k, *n - k - l + j);
		r__[i__3].r = bf[i__4].r, r__[i__3].i = bf[i__4].i;
/* L30: */
	    }
/* L40: */
	}
    }

/*     Compute A:= U'*A*Q - D1*R */

    zgemm_("No transpose", "No transpose", m, n, n, &c_b2, &a[a_offset], lda, 
	    &q[q_offset], ldq, &c_b1, &work[1], lda);

    zgemm_("Conjugate transpose", "No transpose", m, n, m, &c_b2, &u[u_offset]
	    , ldu, &work[1], lda, &c_b1, &a[a_offset], lda);

    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = k + l;
	for (j = i__; j <= i__2; ++j) {
	    i__3 = a_subscr(i__, *n - k - l + j);
	    i__4 = a_subscr(i__, *n - k - l + j);
	    i__5 = r___subscr(i__, j);
	    z__1.r = a[i__4].r - r__[i__5].r, z__1.i = a[i__4].i - r__[i__5]
		    .i;
	    a[i__3].r = z__1.r, a[i__3].i = z__1.i;
/* L50: */
	}
/* L60: */
    }

/* Computing MIN */
    i__2 = k + l;
    i__1 = min(i__2,*m);
    for (i__ = k + 1; i__ <= i__1; ++i__) {
	i__2 = k + l;
	for (j = i__; j <= i__2; ++j) {
	    i__3 = a_subscr(i__, *n - k - l + j);
	    i__4 = a_subscr(i__, *n - k - l + j);
	    i__5 = i__;
	    i__6 = r___subscr(i__, j);
	    z__2.r = alpha[i__5] * r__[i__6].r, z__2.i = alpha[i__5] * r__[
		    i__6].i;
	    z__1.r = a[i__4].r - z__2.r, z__1.i = a[i__4].i - z__2.i;
	    a[i__3].r = z__1.r, a[i__3].i = z__1.i;
/* L70: */
	}
/* L80: */
    }

/*     Compute norm( U'*A*Q - D1*R ) / ( MAX(1,M,N)*norm(A)*ULP ) . */

    resid = zlange_("1", m, n, &a[a_offset], lda, &rwork[1]);
    if (anorm > 0.) {
/* Computing MAX */
	i__1 = max(1,*m);
	result[1] = resid / (doublereal) max(i__1,*n) / anorm / ulp;
    } else {
	result[1] = 0.;
    }

/*     Compute B := V'*B*Q - D2*R */

    zgemm_("No transpose", "No transpose", p, n, n, &c_b2, &b[b_offset], ldb, 
	    &q[q_offset], ldq, &c_b1, &work[1], ldb);

    zgemm_("Conjugate transpose", "No transpose", p, n, p, &c_b2, &v[v_offset]
	    , ldv, &work[1], ldb, &c_b1, &b[b_offset], ldb);

    i__1 = l;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = l;
	for (j = i__; j <= i__2; ++j) {
	    i__3 = b_subscr(i__, *n - l + j);
	    i__4 = b_subscr(i__, *n - l + j);
	    i__5 = k + i__;
	    i__6 = r___subscr(k + i__, k + j);
	    z__2.r = beta[i__5] * r__[i__6].r, z__2.i = beta[i__5] * r__[i__6]
		    .i;
	    z__1.r = b[i__4].r - z__2.r, z__1.i = b[i__4].i - z__2.i;
	    b[i__3].r = z__1.r, b[i__3].i = z__1.i;
/* L90: */
	}
/* L100: */
    }

/*     Compute norm( V'*B*Q - D2*R ) / ( MAX(P,N)*norm(B)*ULP ) . */

    resid = zlange_("1", p, n, &b[b_offset], ldb, &rwork[1]);
    if (bnorm > 0.) {
/* Computing MAX */
	i__1 = max(1,*p);
	result[2] = resid / (doublereal) max(i__1,*n) / bnorm / ulp;
    } else {
	result[2] = 0.;
    }

/*     Compute I - U'*U */

    zlaset_("Full", m, m, &c_b1, &c_b2, &work[1], ldq);
    zherk_("Upper", "Conjugate transpose", m, m, &c_b36, &u[u_offset], ldu, &
	    c_b37, &work[1], ldu);

/*     Compute norm( I - U'*U ) / ( M * ULP ) . */

    resid = zlanhe_("1", "Upper", m, &work[1], ldu, &rwork[1]);
    result[3] = resid / (doublereal) max(1,*m) / ulp;

/*     Compute I - V'*V */

    zlaset_("Full", p, p, &c_b1, &c_b2, &work[1], ldv);
    zherk_("Upper", "Conjugate transpose", p, p, &c_b36, &v[v_offset], ldv, &
	    c_b37, &work[1], ldv);

/*     Compute norm( I - V'*V ) / ( P * ULP ) . */

    resid = zlanhe_("1", "Upper", p, &work[1], ldv, &rwork[1]);
    result[4] = resid / (doublereal) max(1,*p) / ulp;

/*     Compute I - Q'*Q */

    zlaset_("Full", n, n, &c_b1, &c_b2, &work[1], ldq);
    zherk_("Upper", "Conjugate transpose", n, n, &c_b36, &q[q_offset], ldq, &
	    c_b37, &work[1], ldq);

/*     Compute norm( I - Q'*Q ) / ( N * ULP ) . */

    resid = zlanhe_("1", "Upper", n, &work[1], ldq, &rwork[1]);
    result[5] = resid / (doublereal) max(1,*n) / ulp;

/*     Check sorting */

    dcopy_(n, &alpha[1], &c__1, &rwork[1], &c__1);
/* Computing MIN */
    i__2 = k + l;
    i__1 = min(i__2,*m);
    for (i__ = k + 1; i__ <= i__1; ++i__) {
	j = iwork[i__];
	if (i__ != j) {
	    temp = rwork[i__];
	    rwork[i__] = rwork[j];
	    rwork[j] = temp;
	}
/* L110: */
    }

    result[6] = 0.;
/* Computing MIN */
    i__2 = k + l;
    i__1 = min(i__2,*m) - 1;
    for (i__ = k + 1; i__ <= i__1; ++i__) {
	if (rwork[i__] < rwork[i__ + 1]) {
	    result[6] = ulpinv;
	}
/* L120: */
    }

    return 0;

/*     End of ZGSVTS */

} /* zgsvts_ */

#undef bf_ref
#undef bf_subscr
#undef af_ref
#undef af_subscr
#undef r___ref
#undef r___subscr
#undef b_ref
#undef b_subscr
#undef a_ref
#undef a_subscr


