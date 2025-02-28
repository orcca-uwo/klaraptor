#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    char srnamt[6];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static real c_b4 = -1e10f;
static real c_b10 = 0.f;
static real c_b15 = -1.f;
static real c_b16 = 1.f;

/* Subroutine */ int srqt02_(integer *m, integer *n, integer *k, real *a, 
	real *af, real *q, real *r__, integer *lda, real *tau, real *work, 
	integer *lwork, real *rwork, real *result)
{
    /* System generated locals */
    integer a_dim1, a_offset, af_dim1, af_offset, q_dim1, q_offset, r_dim1, 
	    r_offset, i__1, i__2;

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static integer info;
    static real resid;
    extern /* Subroutine */ int sgemm_(char *, char *, integer *, integer *, 
	    integer *, real *, real *, integer *, real *, integer *, real *, 
	    real *, integer *);
    static real anorm;
    extern /* Subroutine */ int ssyrk_(char *, char *, integer *, integer *, 
	    real *, real *, integer *, real *, real *, integer *);
    extern doublereal slamch_(char *), slange_(char *, integer *, 
	    integer *, real *, integer *, real *);
    extern /* Subroutine */ int slacpy_(char *, integer *, integer *, real *, 
	    integer *, real *, integer *), slaset_(char *, integer *, 
	    integer *, real *, real *, real *, integer *);
    extern doublereal slansy_(char *, char *, integer *, real *, integer *, 
	    real *);
    extern /* Subroutine */ int sorgrq_(integer *, integer *, integer *, real 
	    *, integer *, real *, real *, integer *, integer *);
    static real eps;


#define a_ref(a_1,a_2) a[(a_2)*a_dim1 + a_1]
#define q_ref(a_1,a_2) q[(a_2)*q_dim1 + a_1]
#define r___ref(a_1,a_2) r__[(a_2)*r_dim1 + a_1]
#define af_ref(a_1,a_2) af[(a_2)*af_dim1 + a_1]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    SRQT02 tests SORGRQ, which generates an m-by-n matrix Q with   
    orthonornmal rows that is defined as the product of k elementary   
    reflectors.   

    Given the RQ factorization of an m-by-n matrix A, SRQT02 generates   
    the orthogonal matrix Q defined by the factorization of the last k   
    rows of A; it compares R(m-k+1:m,n-m+1:n) with   
    A(m-k+1:m,1:n)*Q(n-m+1:n,1:n)', and checks that the rows of Q are   
    orthonormal.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix Q to be generated.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix Q to be generated.   
            N >= M >= 0.   

    K       (input) INTEGER   
            The number of elementary reflectors whose product defines the   
            matrix Q. M >= K >= 0.   

    A       (input) REAL array, dimension (LDA,N)   
            The m-by-n matrix A which was factorized by SRQT01.   

    AF      (input) REAL array, dimension (LDA,N)   
            Details of the RQ factorization of A, as returned by SGERQF.   
            See SGERQF for further details.   

    Q       (workspace) REAL array, dimension (LDA,N)   

    R       (workspace) REAL array, dimension (LDA,M)   

    LDA     (input) INTEGER   
            The leading dimension of the arrays A, AF, Q and L. LDA >= N.   

    TAU     (input) REAL array, dimension (M)   
            The scalar factors of the elementary reflectors corresponding   
            to the RQ factorization in AF.   

    WORK    (workspace) REAL array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   

    RWORK   (workspace) REAL array, dimension (M)   

    RESULT  (output) REAL array, dimension (2)   
            The test ratios:   
            RESULT(1) = norm( R - A*Q' ) / ( N * norm(A) * EPS )   
            RESULT(2) = norm( I - Q*Q' ) / ( N * EPS )   

    =====================================================================   


       Quick return if possible   

       Parameter adjustments */
    r_dim1 = *lda;
    r_offset = 1 + r_dim1 * 1;
    r__ -= r_offset;
    q_dim1 = *lda;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    af_dim1 = *lda;
    af_offset = 1 + af_dim1 * 1;
    af -= af_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --tau;
    --work;
    --rwork;
    --result;

    /* Function Body */
    if (*m == 0 || *n == 0 || *k == 0) {
	result[1] = 0.f;
	result[2] = 0.f;
	return 0;
    }

    eps = slamch_("Epsilon");

/*     Copy the last k rows of the factorization to the array Q */

    slaset_("Full", m, n, &c_b4, &c_b4, &q[q_offset], lda);
    if (*k < *n) {
	i__1 = *n - *k;
	slacpy_("Full", k, &i__1, &af_ref(*m - *k + 1, 1), lda, &q_ref(*m - *
		k + 1, 1), lda);
    }
    if (*k > 1) {
	i__1 = *k - 1;
	i__2 = *k - 1;
	slacpy_("Lower", &i__1, &i__2, &af_ref(*m - *k + 2, *n - *k + 1), lda,
		 &q_ref(*m - *k + 2, *n - *k + 1), lda);
    }

/*     Generate the last n rows of the matrix Q */

    s_copy(srnamc_1.srnamt, "SORGRQ", (ftnlen)6, (ftnlen)6);
    sorgrq_(m, n, k, &q[q_offset], lda, &tau[*m - *k + 1], &work[1], lwork, &
	    info);

/*     Copy R(m-k+1:m,n-m+1:n) */

    slaset_("Full", k, m, &c_b10, &c_b10, &r___ref(*m - *k + 1, *n - *m + 1), 
	    lda);
    slacpy_("Upper", k, k, &af_ref(*m - *k + 1, *n - *k + 1), lda, &r___ref(*
	    m - *k + 1, *n - *k + 1), lda);

/*     Compute R(m-k+1:m,n-m+1:n) - A(m-k+1:m,1:n) * Q(n-m+1:n,1:n)' */

    sgemm_("No transpose", "Transpose", k, m, n, &c_b15, &a_ref(*m - *k + 1, 
	    1), lda, &q[q_offset], lda, &c_b16, &r___ref(*m - *k + 1, *n - *m 
	    + 1), lda);

/*     Compute norm( R - A*Q' ) / ( N * norm(A) * EPS ) . */

    anorm = slange_("1", k, n, &a_ref(*m - *k + 1, 1), lda, &rwork[1]);
    resid = slange_("1", k, m, &r___ref(*m - *k + 1, *n - *m + 1), lda, &
	    rwork[1]);
    if (anorm > 0.f) {
	result[1] = resid / (real) max(1,*n) / anorm / eps;
    } else {
	result[1] = 0.f;
    }

/*     Compute I - Q*Q' */

    slaset_("Full", m, m, &c_b10, &c_b16, &r__[r_offset], lda);
    ssyrk_("Upper", "No transpose", m, n, &c_b15, &q[q_offset], lda, &c_b16, &
	    r__[r_offset], lda);

/*     Compute norm( I - Q*Q' ) / ( N * EPS ) . */

    resid = slansy_("1", "Upper", m, &r__[r_offset], lda, &rwork[1]);

    result[2] = resid / (real) max(1,*n) / eps;

    return 0;

/*     End of SRQT02 */

} /* srqt02_ */

#undef af_ref
#undef r___ref
#undef q_ref
#undef a_ref


