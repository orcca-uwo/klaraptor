#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal ops, itcnt;
} latime_;

#define latime_1 latime_

struct {
    doublereal opcnt[6], timng[6];
} lstime_;

#define lstime_1 lstime_

/* Table of constant values */

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__6 = 6;
static integer c_n1 = -1;
static integer c__1 = 1;
static integer c__0 = 0;
static doublereal c_b78 = 0.;

/* Subroutine */ int zgelss_(integer *m, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublereal *s, doublereal *rcond, integer *rank, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info)
{
    /* Initialized data */

    static integer bdsqr = 5;
    static integer unmlq = 6;
    static integer unmqr = 2;
    static integer gebrd = 3;
    static integer gelqf = 2;
    static integer gelss = 1;
    static integer gemm = 6;
    static integer gemv = 6;
    static integer geqrf = 2;
    static integer ungbr = 4;
    static integer unmbr = 4;

    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Local variables */
    static doublereal anrm, bnrm;
    static integer itau;
    static doublecomplex vdum[1];
    static integer i__, iascl, ibscl;
    extern doublereal dopla_(char *, integer *, integer *, integer *, integer 
	    *, integer *);
    static integer chunk;
    static doublereal sfmin;
    static integer minmn, maxmn, itaup, itauq, mnthr;
    extern /* Subroutine */ int zgemm_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *), zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *);
    static integer iwork;
    static doublereal t1, t2;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *);
    extern doublereal dopla2_(char *, char *, integer *, integer *, integer *,
	     integer *, integer *), dopbl2_(char *, integer *,
	     integer *, integer *, integer *), dopbl3_(char *, 
	    integer *, integer *, integer *);
    extern /* Subroutine */ int dlabad_(doublereal *, doublereal *);
    static integer bl, ie, nb, il;
    extern doublereal dlamch_(char *);
    static integer mm;
    extern doublereal dsecnd_(void);
    extern /* Subroutine */ int dlascl_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    integer *, integer *), dlaset_(char *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *, integer *), 
	    xerbla_(char *, integer *), zgebrd_(integer *, integer *, 
	    doublecomplex *, integer *, doublereal *, doublereal *, 
	    doublecomplex *, doublecomplex *, doublecomplex *, integer *, 
	    integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern doublereal zlange_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublereal *);
    static doublereal bignum;
    extern /* Subroutine */ int zgelqf_(integer *, integer *, doublecomplex *,
	     integer *, doublecomplex *, doublecomplex *, integer *, integer *
	    ), zlascl_(char *, integer *, integer *, doublereal *, doublereal 
	    *, integer *, integer *, doublecomplex *, integer *, integer *), zgeqrf_(integer *, integer *, doublecomplex *, integer *,
	     doublecomplex *, doublecomplex *, integer *, integer *), zdrscl_(
	    integer *, doublereal *, doublecomplex *, integer *);
    static integer ldwork;
    extern /* Subroutine */ int zlacpy_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), 
	    zlaset_(char *, integer *, integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, integer *), zbdsqr_(
	    char *, integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublereal *, integer *);
    static integer minwrk, maxwrk;
    extern /* Subroutine */ int zungbr_(char *, integer *, integer *, integer 
	    *, doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, integer *);
    static doublereal smlnum;
    static integer irwork;
    extern /* Subroutine */ int zunmbr_(char *, char *, char *, integer *, 
	    integer *, integer *, doublecomplex *, integer *, doublecomplex *,
	     doublecomplex *, integer *, doublecomplex *, integer *, integer *
	    );
    static logical lquery;
    extern /* Subroutine */ int zunmlq_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, integer *), zunmqr_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, integer *);
    static doublereal eps, thr;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]


/*  -- LAPACK driver routine (instrumented to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1999   

       Common blocks to return operation counts and timings   

    Purpose   
    =======   

    ZGELSS computes the minimum norm solution to a complex linear   
    least squares problem:   

    Minimize 2-norm(| b - A*x |).   

    using the singular value decomposition (SVD) of A. A is an M-by-N   
    matrix which may be rank-deficient.   

    Several right hand side vectors b and solution vectors x can be   
    handled in a single call; they are stored as the columns of the   
    M-by-NRHS right hand side matrix B and the N-by-NRHS solution matrix   
    X.   

    The effective rank of A is determined by treating as zero those   
    singular values which are less than RCOND times the largest singular   
    value.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A. M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A. N >= 0.   

    NRHS    (input) INTEGER   
            The number of right hand sides, i.e., the number of columns   
            of the matrices B and X. NRHS >= 0.   

    A       (input/output) COMPLEX*16 array, dimension (LDA,N)   
            On entry, the M-by-N matrix A.   
            On exit, the first min(m,n) rows of A are overwritten with   
            its right singular vectors, stored rowwise.   

    LDA     (input) INTEGER   
            The leading dimension of the array A. LDA >= max(1,M).   

    B       (input/output) COMPLEX*16 array, dimension (LDB,NRHS)   
            On entry, the M-by-NRHS right hand side matrix B.   
            On exit, B is overwritten by the N-by-NRHS solution matrix X.   
            If m >= n and RANK = n, the residual sum-of-squares for   
            the solution in the i-th column is given by the sum of   
            squares of elements n+1:m in that column.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,M,N).   

    S       (output) DOUBLE PRECISION array, dimension (min(M,N))   
            The singular values of A in decreasing order.   
            The condition number of A in the 2-norm = S(1)/S(min(m,n)).   

    RCOND   (input) DOUBLE PRECISION   
            RCOND is used to determine the effective rank of A.   
            Singular values S(i) <= RCOND*S(1) are treated as zero.   
            If RCOND < 0, machine precision is used instead.   

    RANK    (output) INTEGER   
            The effective rank of A, i.e., the number of singular values   
            which are greater than RCOND*S(1).   

    WORK    (workspace/output) COMPLEX*16 array, dimension (LWORK)   
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK. LWORK >= 1, and also:   
            LWORK >=  2*min(M,N) + max(M,N,NRHS)   
            For good performance, LWORK should generally be larger.   

            If LWORK = -1, then a workspace query is assumed; the routine   
            only calculates the optimal size of the WORK array, returns   
            this value as the first entry of the WORK array, and no error   
            message related to LWORK is issued by XERBLA.   

    RWORK   (workspace) DOUBLE PRECISION array, dimension (5*min(M,N))   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   
            > 0:  the algorithm for computing the SVD failed to converge;   
                  if INFO = i, i off-diagonal elements of an intermediate   
                  bidiagonal form did not converge to zero.   

    =====================================================================   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    --s;
    --work;
    --rwork;

    /* Function Body   

       Test the input arguments */

    *info = 0;
    minmn = min(*m,*n);
    maxmn = max(*m,*n);
    mnthr = ilaenv_(&c__6, "ZGELSS", " ", m, n, nrhs, &c_n1, (ftnlen)6, (
	    ftnlen)1);
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    } else if (*ldb < max(1,maxmn)) {
	*info = -7;
    }

/*     Compute workspace   
        (Note: Comments in the code beginning "Workspace:" describe the   
         minimal amount of workspace needed at that point in the code,   
         as well as the preferred amount for good performance.   
         CWorkspace refers to complex workspace, and RWorkspace refers   
         to real workspace. NB refers to the optimal block size for the   
         immediately following subroutine, as returned by ILAENV.) */

    minwrk = 1;
    if (*info == 0 && (*lwork >= 1 || lquery)) {
	maxwrk = 0;
	mm = *m;
	if (*m >= *n && *m >= mnthr) {

/*           Path 1a - overdetermined, with many more rows than columns   

             Space needed for ZBDSQR is BDSPAC = 5*N */

	    mm = *n;
/* Computing MAX */
	    i__1 = maxwrk, i__2 = *n + *n * ilaenv_(&c__1, "ZGEQRF", " ", m, 
		    n, &c_n1, &c_n1, (ftnlen)6, (ftnlen)1);
	    maxwrk = max(i__1,i__2);
/* Computing MAX */
	    i__1 = maxwrk, i__2 = *n + *nrhs * ilaenv_(&c__1, "ZUNMQR", "LC", 
		    m, nrhs, n, &c_n1, (ftnlen)6, (ftnlen)2);
	    maxwrk = max(i__1,i__2);
	}
	if (*m >= *n) {

/*           Path 1 - overdetermined or exactly determined   

             Space needed for ZBDSQR is BDSPC = 7*N+12   

   Computing MAX */
	    i__1 = maxwrk, i__2 = (*n << 1) + (mm + *n) * ilaenv_(&c__1, 
		    "ZGEBRD", " ", &mm, n, &c_n1, &c_n1, (ftnlen)6, (ftnlen)1)
		    ;
	    maxwrk = max(i__1,i__2);
/* Computing MAX */
	    i__1 = maxwrk, i__2 = (*n << 1) + *nrhs * ilaenv_(&c__1, "ZUNMBR",
		     "QLC", &mm, nrhs, n, &c_n1, (ftnlen)6, (ftnlen)3);
	    maxwrk = max(i__1,i__2);
/* Computing MAX */
	    i__1 = maxwrk, i__2 = (*n << 1) + (*n - 1) * ilaenv_(&c__1, "ZUN"
		    "GBR", "P", n, n, n, &c_n1, (ftnlen)6, (ftnlen)1);
	    maxwrk = max(i__1,i__2);
/* Computing MAX */
	    i__1 = maxwrk, i__2 = *n * *nrhs;
	    maxwrk = max(i__1,i__2);
	    minwrk = (*n << 1) + max(*nrhs,*m);
	}
	if (*n > *m) {
	    minwrk = (*m << 1) + max(*nrhs,*n);
	    if (*n >= mnthr) {

/*              Path 2a - underdetermined, with many more columns   
                than rows   

                Space needed for ZBDSQR is BDSPAC = 5*M */

		maxwrk = *m + *m * ilaenv_(&c__1, "ZGELQF", " ", m, n, &c_n1, 
			&c_n1, (ftnlen)6, (ftnlen)1);
/* Computing MAX */
		i__1 = maxwrk, i__2 = *m * 3 + *m * *m + (*m << 1) * ilaenv_(&
			c__1, "ZGEBRD", " ", m, m, &c_n1, &c_n1, (ftnlen)6, (
			ftnlen)1);
		maxwrk = max(i__1,i__2);
/* Computing MAX */
		i__1 = maxwrk, i__2 = *m * 3 + *m * *m + *nrhs * ilaenv_(&
			c__1, "ZUNMBR", "QLC", m, nrhs, m, &c_n1, (ftnlen)6, (
			ftnlen)3);
		maxwrk = max(i__1,i__2);
/* Computing MAX */
		i__1 = maxwrk, i__2 = *m * 3 + *m * *m + (*m - 1) * ilaenv_(&
			c__1, "ZUNGBR", "P", m, m, m, &c_n1, (ftnlen)6, (
			ftnlen)1);
		maxwrk = max(i__1,i__2);
		if (*nrhs > 1) {
/* Computing MAX */
		    i__1 = maxwrk, i__2 = *m * *m + *m + *m * *nrhs;
		    maxwrk = max(i__1,i__2);
		} else {
/* Computing MAX */
		    i__1 = maxwrk, i__2 = *m * *m + (*m << 1);
		    maxwrk = max(i__1,i__2);
		}
/* Computing MAX */
		i__1 = maxwrk, i__2 = *m + *nrhs * ilaenv_(&c__1, "ZUNMLQ", 
			"LC", n, nrhs, m, &c_n1, (ftnlen)6, (ftnlen)2);
		maxwrk = max(i__1,i__2);
	    } else {

/*              Path 2 - underdetermined   

                Space needed for ZBDSQR is BDSPAC = 5*M */

		maxwrk = (*m << 1) + (*n + *m) * ilaenv_(&c__1, "ZGEBRD", 
			" ", m, n, &c_n1, &c_n1, (ftnlen)6, (ftnlen)1);
/* Computing MAX */
		i__1 = maxwrk, i__2 = (*m << 1) + *nrhs * ilaenv_(&c__1, 
			"ZUNMBR", "QLC", m, nrhs, m, &c_n1, (ftnlen)6, (
			ftnlen)3);
		maxwrk = max(i__1,i__2);
/* Computing MAX */
		i__1 = maxwrk, i__2 = (*m << 1) + *m * ilaenv_(&c__1, "ZUNGBR"
			, "P", m, n, m, &c_n1, (ftnlen)6, (ftnlen)1);
		maxwrk = max(i__1,i__2);
/* Computing MAX */
		i__1 = maxwrk, i__2 = *n * *nrhs;
		maxwrk = max(i__1,i__2);
	    }
	}
	minwrk = max(minwrk,1);
	maxwrk = max(minwrk,maxwrk);
	work[1].r = (doublereal) maxwrk, work[1].i = 0.;
    }

    if (*lwork < minwrk && ! lquery) {
	*info = -12;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZGELSS", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	*rank = 0;
	return 0;
    }

/*     Get machine parameters */

    eps = dlamch_("P");
    sfmin = dlamch_("S");
    lstime_1.opcnt[gelss - 1] += 2.;
    smlnum = sfmin / eps;
    bignum = 1. / smlnum;
    dlabad_(&smlnum, &bignum);

/*     Scale A if max element outside range [SMLNUM,BIGNUM] */

    anrm = zlange_("M", m, n, &a[a_offset], lda, &rwork[1]);
    iascl = 0;
    if (anrm > 0. && anrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	lstime_1.opcnt[gelss - 1] += (doublereal) (*m * 6 * *n);
	zlascl_("G", &c__0, &c__0, &anrm, &smlnum, m, n, &a[a_offset], lda, 
		info);
	iascl = 1;
    } else if (anrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	lstime_1.opcnt[gelss - 1] += (doublereal) (*m * 6 * *n);
	zlascl_("G", &c__0, &c__0, &anrm, &bignum, m, n, &a[a_offset], lda, 
		info);
	iascl = 2;
    } else if (anrm == 0.) {

/*        Matrix all zero. Return zero solution. */

	i__1 = max(*m,*n);
	zlaset_("F", &i__1, nrhs, &c_b1, &c_b1, &b[b_offset], ldb);
	dlaset_("F", &minmn, &c__1, &c_b78, &c_b78, &s[1], &minmn);
	*rank = 0;
	goto L70;
    }

/*     Scale B if max element outside range [SMLNUM,BIGNUM] */

    bnrm = zlange_("M", m, nrhs, &b[b_offset], ldb, &rwork[1]);
    ibscl = 0;
    if (bnrm > 0. && bnrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	lstime_1.opcnt[gelss - 1] += (doublereal) (*m * 6 * *nrhs);
	zlascl_("G", &c__0, &c__0, &bnrm, &smlnum, m, nrhs, &b[b_offset], ldb,
		 info);
	ibscl = 1;
    } else if (bnrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	lstime_1.opcnt[gelss - 1] += (doublereal) (*m * 6 * *nrhs);
	zlascl_("G", &c__0, &c__0, &bnrm, &bignum, m, nrhs, &b[b_offset], ldb,
		 info);
	ibscl = 2;
    }

/*     Overdetermined case */

    if (*m >= *n) {

/*        Path 1 - overdetermined or exactly determined */

	mm = *m;
	if (*m >= mnthr) {

/*           Path 1a - overdetermined, with many more rows than columns */

	    mm = *n;
	    itau = 1;
	    iwork = itau + *n;

/*           Compute A=Q*R   
             (CWorkspace: need 2*N, prefer N+N*NB)   
             (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZGEQRF", " ", m, n, &c_n1, &c_n1, (ftnlen)6, 
		    (ftnlen)1);
	    lstime_1.opcnt[geqrf - 1] += dopla_("ZGEQRF", m, n, &c__0, &c__0, 
		    &nb);
	    t1 = dsecnd_();
	    i__1 = *lwork - iwork + 1;
	    zgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork], &i__1,
		     info);
	    t2 = dsecnd_();
	    lstime_1.timng[geqrf - 1] += t2 - t1;

/*           Multiply B by transpose(Q)   
             (CWorkspace: need N+NRHS, prefer N+NRHS*NB)   
             (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZUNMQR", "LC", m, nrhs, n, &c_n1, (ftnlen)6, 
		    (ftnlen)2);
	    lstime_1.opcnt[unmqr - 1] += dopla_("ZUNMQR", m, nrhs, n, &c__0, &
		    nb);
	    t1 = dsecnd_();
	    i__1 = *lwork - iwork + 1;
	    zunmqr_("L", "C", m, nrhs, n, &a[a_offset], lda, &work[itau], &b[
		    b_offset], ldb, &work[iwork], &i__1, info);
	    t2 = dsecnd_();
	    lstime_1.timng[unmqr - 1] += t2 - t1;

/*           Zero out below R */

	    if (*n > 1) {
		i__1 = *n - 1;
		i__2 = *n - 1;
		zlaset_("L", &i__1, &i__2, &c_b1, &c_b1, &a_ref(2, 1), lda);
	    }
	}

	ie = 1;
	itauq = 1;
	itaup = itauq + *n;
	iwork = itaup + *n;

/*        Bidiagonalize R in A   
          (CWorkspace: need 2*N+MM, prefer 2*N+(MM+N)*NB)   
          (RWorkspace: need N) */

	nb = ilaenv_(&c__1, "ZGEBRD", " ", &mm, n, &c_n1, &c_n1, (ftnlen)6, (
		ftnlen)1);
	lstime_1.opcnt[gebrd - 1] += dopla_("ZGEBRD", &mm, n, &c__0, &c__0, &
		nb);
	t1 = dsecnd_();
	i__1 = *lwork - iwork + 1;
	zgebrd_(&mm, n, &a[a_offset], lda, &s[1], &rwork[ie], &work[itauq], &
		work[itaup], &work[iwork], &i__1, info);
	t2 = dsecnd_();
	lstime_1.timng[gebrd - 1] += t2 - t1;

/*        Multiply B by transpose of left bidiagonalizing vectors of R   
          (CWorkspace: need 2*N+NRHS, prefer 2*N+NRHS*NB)   
          (RWorkspace: none) */

	nb = ilaenv_(&c__1, "ZUNMBR", "QLC", &mm, nrhs, n, &c_n1, (ftnlen)6, (
		ftnlen)3);
	lstime_1.opcnt[unmbr - 1] += dopla2_("ZUNMBR", "QLC", &mm, nrhs, n, &
		c__0, &nb);
	t1 = dsecnd_();
	i__1 = *lwork - iwork + 1;
	zunmbr_("Q", "L", "C", &mm, nrhs, n, &a[a_offset], lda, &work[itauq], 
		&b[b_offset], ldb, &work[iwork], &i__1, info);
	t2 = dsecnd_();
	lstime_1.timng[unmbr - 1] += t2 - t1;

/*        Generate right bidiagonalizing vectors of R in A   
          (CWorkspace: need 3*N-1, prefer 2*N+(N-1)*NB)   
          (RWorkspace: none) */

	nb = ilaenv_(&c__1, "ZUNGBR", "P", n, n, n, &c_n1, (ftnlen)6, (ftnlen)
		1);
	lstime_1.opcnt[ungbr - 1] += dopla2_("ZUNGBR", "P", n, n, n, &c__0, &
		nb);
	t1 = dsecnd_();
	i__1 = *lwork - iwork + 1;
	zungbr_("P", n, n, n, &a[a_offset], lda, &work[itaup], &work[iwork], &
		i__1, info);
	t2 = dsecnd_();
	lstime_1.timng[ungbr - 1] += t2 - t1;
	irwork = ie + *n;

/*        Perform bidiagonal QR iteration   
            multiply B by transpose of left singular vectors   
            compute right singular vectors in A   
          (CWorkspace: none)   
          (RWorkspace: need BDSPAC) */

	latime_1.ops = 0.;
	t1 = dsecnd_();
	zbdsqr_("U", n, n, &c__0, nrhs, &s[1], &rwork[ie], &a[a_offset], lda, 
		vdum, &c__1, &b[b_offset], ldb, &rwork[irwork], info);
	t2 = dsecnd_();
	lstime_1.timng[bdsqr - 1] += t2 - t1;
	lstime_1.opcnt[bdsqr - 1] += latime_1.ops;
	if (*info != 0) {
	    goto L70;
	}

/*        Multiply B by reciprocals of singular values */

	lstime_1.opcnt[gelss - 1] += 1.;
/* Computing MAX */
	d__1 = *rcond * s[1];
	thr = max(d__1,sfmin);
	if (*rcond < 0.) {
	    lstime_1.opcnt[gelss - 1] += 1.;
/* Computing MAX */
	    d__1 = eps * s[1];
	    thr = max(d__1,sfmin);
	}
	*rank = 0;
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (s[i__] > thr) {
		lstime_1.opcnt[gelss - 1] += (doublereal) (*nrhs * 6 + 3);
		zdrscl_(nrhs, &s[i__], &b_ref(i__, 1), ldb);
		++(*rank);
	    } else {
		zlaset_("F", &c__1, nrhs, &c_b1, &c_b1, &b_ref(i__, 1), ldb);
	    }
/* L10: */
	}

/*        Multiply B by right singular vectors   
          (CWorkspace: need N, prefer N*NRHS)   
          (RWorkspace: none) */

	if (*lwork >= *ldb * *nrhs && *nrhs > 1) {
	    lstime_1.opcnt[gemm - 1] += dopbl3_("ZGEMM ", n, nrhs, n);
	    t1 = dsecnd_();
	    zgemm_("C", "N", n, nrhs, n, &c_b2, &a[a_offset], lda, &b[
		    b_offset], ldb, &c_b1, &work[1], ldb);
	    t2 = dsecnd_();
	    lstime_1.timng[gemm - 1] += t2 - t1;
	    zlacpy_("G", n, nrhs, &work[1], ldb, &b[b_offset], ldb)
		    ;
	} else if (*nrhs > 1) {
	    chunk = *lwork / *n;
	    i__1 = *nrhs;
	    i__2 = chunk;
	    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
		i__3 = *nrhs - i__ + 1;
		bl = min(i__3,chunk);
		lstime_1.opcnt[gemm - 1] += dopbl3_("ZGEMM ", n, &bl, n);
		t1 = dsecnd_();
		zgemm_("C", "N", n, &bl, n, &c_b2, &a[a_offset], lda, &b_ref(
			1, i__), ldb, &c_b1, &work[1], n);
		t2 = dsecnd_();
		lstime_1.timng[gemm - 1] += t2 - t1;
		zlacpy_("G", n, &bl, &work[1], n, &b_ref(1, i__), ldb);
/* L20: */
	    }
	} else {
	    lstime_1.opcnt[gemv - 1] += dopbl2_("ZGEMV ", n, n, &c__0, &c__0);
	    t1 = dsecnd_();
	    zgemv_("C", n, n, &c_b2, &a[a_offset], lda, &b[b_offset], &c__1, &
		    c_b1, &work[1], &c__1);
	    t2 = dsecnd_();
	    lstime_1.timng[gemv - 1] += t2 - t1;
	    zcopy_(n, &work[1], &c__1, &b[b_offset], &c__1);
	}

    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__2 = max(*m,*nrhs), i__1 = *n - (*m << 1);
	if (*n >= mnthr && *lwork >= *m * 3 + *m * *m + max(i__2,i__1)) {

/*        Underdetermined case, M much less than N   

          Path 2a - underdetermined, with many more columns than rows   
          and sufficient workspace for an efficient algorithm */

	    ldwork = *m;
/* Computing MAX */
	    i__2 = max(*m,*nrhs), i__1 = *n - (*m << 1);
	    if (*lwork >= *m * 3 + *m * *lda + max(i__2,i__1)) {
		ldwork = *lda;
	    }
	    itau = 1;
	    iwork = *m + 1;

/*        Compute A=L*Q   
          (CWorkspace: need 2*M, prefer M+M*NB)   
          (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZGELQF", " ", m, n, &c_n1, &c_n1, (ftnlen)6, 
		    (ftnlen)1);
	    lstime_1.opcnt[gelqf - 1] += dopla_("ZGELQF", m, n, &c__0, &c__0, 
		    &nb);
	    t1 = dsecnd_();
	    i__2 = *lwork - iwork + 1;
	    zgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork], &i__2,
		     info);
	    t2 = dsecnd_();
	    lstime_1.timng[gelqf - 1] += t2 - t1;
	    il = iwork;

/*        Copy L to WORK(IL), zeroing out above it */

	    zlacpy_("L", m, m, &a[a_offset], lda, &work[il], &ldwork);
	    i__2 = *m - 1;
	    i__1 = *m - 1;
	    zlaset_("U", &i__2, &i__1, &c_b1, &c_b1, &work[il + ldwork], &
		    ldwork);
	    ie = 1;
	    itauq = il + ldwork * *m;
	    itaup = itauq + *m;
	    iwork = itaup + *m;

/*        Bidiagonalize L in WORK(IL)   
          (CWorkspace: need M*M+4*M, prefer M*M+3*M+2*M*NB)   
          (RWorkspace: need M) */

	    nb = ilaenv_(&c__1, "ZGEBRD", " ", m, m, &c_n1, &c_n1, (ftnlen)6, 
		    (ftnlen)1);
	    lstime_1.opcnt[gebrd - 1] += dopla_("ZGEBRD", m, m, &c__0, &c__0, 
		    &nb);
	    t1 = dsecnd_();
	    i__2 = *lwork - iwork + 1;
	    zgebrd_(m, m, &work[il], &ldwork, &s[1], &rwork[ie], &work[itauq],
		     &work[itaup], &work[iwork], &i__2, info);
	    t2 = dsecnd_();
	    lstime_1.timng[gebrd - 1] += t2 - t1;

/*        Multiply B by transpose of left bidiagonalizing vectors of L   
          (CWorkspace: need M*M+3*M+NRHS, prefer M*M+3*M+NRHS*NB)   
          (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZUNMBR", "QLC", m, nrhs, m, &c_n1, (ftnlen)6,
		     (ftnlen)3);
	    lstime_1.opcnt[unmbr - 1] += dopla2_("ZUNMBR", "QLC", m, nrhs, m, 
		    &c__0, &nb);
	    t1 = dsecnd_();
	    i__2 = *lwork - iwork + 1;
	    zunmbr_("Q", "L", "C", m, nrhs, m, &work[il], &ldwork, &work[
		    itauq], &b[b_offset], ldb, &work[iwork], &i__2, info);
	    t2 = dsecnd_();
	    lstime_1.timng[unmbr - 1] += t2 - t1;

/*        Generate right bidiagonalizing vectors of R in WORK(IL)   
          (CWorkspace: need M*M+4*M-1, prefer M*M+3*M+(M-1)*NB)   
          (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZUNGBR", "P", m, m, m, &c_n1, (ftnlen)6, (
		    ftnlen)1);
	    lstime_1.opcnt[ungbr - 1] += dopla2_("ZUNGBR", "P", m, m, m, &
		    c__0, &nb);
	    t1 = dsecnd_();
	    i__2 = *lwork - iwork + 1;
	    zungbr_("P", m, m, m, &work[il], &ldwork, &work[itaup], &work[
		    iwork], &i__2, info);
	    t2 = dsecnd_();
	    lstime_1.timng[ungbr - 1] += t2 - t1;
	    irwork = ie + *m;

/*        Perform bidiagonal QR iteration, computing right singular   
          vectors of L in WORK(IL) and multiplying B by transpose of   
          left singular vectors   
          (CWorkspace: need M*M)   
          (RWorkspace: need BDSPAC) */

	    latime_1.ops = 0.;
	    t1 = dsecnd_();
	    zbdsqr_("U", m, m, &c__0, nrhs, &s[1], &rwork[ie], &work[il], &
		    ldwork, &a[a_offset], lda, &b[b_offset], ldb, &rwork[
		    irwork], info);
	    t2 = dsecnd_();
	    lstime_1.timng[bdsqr - 1] += t2 - t1;
	    lstime_1.opcnt[bdsqr - 1] += latime_1.ops;
	    if (*info != 0) {
		goto L70;
	    }

/*        Multiply B by reciprocals of singular values */

	    lstime_1.opcnt[gelss - 1] += 1.;
/* Computing MAX */
	    d__1 = *rcond * s[1];
	    thr = max(d__1,sfmin);
	    if (*rcond < 0.) {
		lstime_1.opcnt[gelss - 1] += 1.;
/* Computing MAX */
		d__1 = eps * s[1];
		thr = max(d__1,sfmin);
	    }
	    *rank = 0;
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (s[i__] > thr) {
		    lstime_1.opcnt[gelss - 1] += (doublereal) (*nrhs * 6 + 3);
		    zdrscl_(nrhs, &s[i__], &b_ref(i__, 1), ldb);
		    ++(*rank);
		} else {
		    zlaset_("F", &c__1, nrhs, &c_b1, &c_b1, &b_ref(i__, 1), 
			    ldb);
		}
/* L30: */
	    }
	    iwork = il + *m * ldwork;

/*        Multiply B by right singular vectors of L in WORK(IL)   
          (CWorkspace: need M*M+2*M, prefer M*M+M+M*NRHS)   
          (RWorkspace: none) */

	    if (*lwork >= *ldb * *nrhs + iwork - 1 && *nrhs > 1) {
		lstime_1.opcnt[gemm - 1] += dopbl3_("ZGEMM ", m, nrhs, m);
		zgemm_("C", "N", m, nrhs, m, &c_b2, &work[il], &ldwork, &b[
			b_offset], ldb, &c_b1, &work[iwork], ldb);
		zlacpy_("G", m, nrhs, &work[iwork], ldb, &b[b_offset], ldb);
	    } else if (*nrhs > 1) {
		chunk = (*lwork - iwork + 1) / *m;
		i__2 = *nrhs;
		i__1 = chunk;
		for (i__ = 1; i__1 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += 
			i__1) {
/* Computing MIN */
		    i__3 = *nrhs - i__ + 1;
		    bl = min(i__3,chunk);
		    lstime_1.opcnt[gemm - 1] += dopbl3_("ZGEMM ", m, &bl, m);
		    t1 = dsecnd_();
		    zgemm_("C", "N", m, &bl, m, &c_b2, &work[il], &ldwork, &
			    b_ref(1, i__), ldb, &c_b1, &work[iwork], n);
		    t2 = dsecnd_();
		    lstime_1.timng[gemm - 1] += t2 - t1;
		    zlacpy_("G", m, &bl, &work[iwork], n, &b_ref(1, i__), ldb);
/* L40: */
		}
	    } else {
		lstime_1.opcnt[gemv - 1] += dopbl2_("ZGEMV ", m, m, &c__0, &
			c__0);
		t1 = dsecnd_();
		zgemv_("C", m, m, &c_b2, &work[il], &ldwork, &b_ref(1, 1), &
			c__1, &c_b1, &work[iwork], &c__1);
		t2 = dsecnd_();
		lstime_1.timng[gemv - 1] += t2 - t1;
		zcopy_(m, &work[iwork], &c__1, &b_ref(1, 1), &c__1);
	    }

/*        Zero out below first M rows of B */

	    i__1 = *n - *m;
	    zlaset_("F", &i__1, nrhs, &c_b1, &c_b1, &b_ref(*m + 1, 1), ldb);
	    iwork = itau + *m;

/*        Multiply transpose(Q) by B   
          (CWorkspace: need M+NRHS, prefer M+NHRS*NB)   
          (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZUNMLQ", "LC", n, nrhs, m, &c_n1, (ftnlen)6, 
		    (ftnlen)2);
	    lstime_1.opcnt[unmlq - 1] += dopla_("ZUNMLQ", n, nrhs, m, &c__0, &
		    nb);
	    t1 = dsecnd_();
	    i__1 = *lwork - iwork + 1;
	    zunmlq_("L", "C", n, nrhs, m, &a[a_offset], lda, &work[itau], &b[
		    b_offset], ldb, &work[iwork], &i__1, info);
	    t2 = dsecnd_();
	    lstime_1.timng[unmlq - 1] += t2 - t1;

	} else {

/*        Path 2 - remaining underdetermined cases */

	    ie = 1;
	    itauq = 1;
	    itaup = itauq + *m;
	    iwork = itaup + *m;

/*        Bidiagonalize A   
          (CWorkspace: need 3*M, prefer 2*M+(M+N)*NB)   
          (RWorkspace: need N) */

	    nb = ilaenv_(&c__1, "ZGEBRD", " ", m, n, &c_n1, &c_n1, (ftnlen)6, 
		    (ftnlen)1);
	    lstime_1.opcnt[gebrd - 1] += dopla_("ZGEBRD", m, n, &c__0, &c__0, 
		    &nb);
	    t1 = dsecnd_();
	    i__1 = *lwork - iwork + 1;
	    zgebrd_(m, n, &a[a_offset], lda, &s[1], &rwork[ie], &work[itauq], 
		    &work[itaup], &work[iwork], &i__1, info);
	    t2 = dsecnd_();
	    lstime_1.timng[gebrd - 1] += t2 - t1;

/*        Multiply B by transpose of left bidiagonalizing vectors   
          (CWorkspace: need 2*M+NRHS, prefer 2*M+NRHS*NB)   
          (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZUNMBR", "QLC", m, nrhs, n, &c_n1, (ftnlen)6,
		     (ftnlen)3);
	    lstime_1.opcnt[unmbr - 1] += dopla2_("ZUNMBR", "QLC", m, nrhs, n, 
		    &c__0, &nb);
	    t1 = dsecnd_();
	    i__1 = *lwork - iwork + 1;
	    zunmbr_("Q", "L", "C", m, nrhs, n, &a[a_offset], lda, &work[itauq]
		    , &b[b_offset], ldb, &work[iwork], &i__1, info);
	    t2 = dsecnd_();
	    lstime_1.timng[unmbr - 1] += t2 - t1;

/*        Generate right bidiagonalizing vectors in A   
          (CWorkspace: need 3*M, prefer 2*M+M*NB)   
          (RWorkspace: none) */

	    nb = ilaenv_(&c__1, "ZUNGBR", "P", m, n, m, &c_n1, (ftnlen)6, (
		    ftnlen)1);
	    lstime_1.opcnt[ungbr - 1] += dopla2_("ZUNGBR", "P", m, n, m, &
		    c__0, &nb);
	    t1 = dsecnd_();
	    i__1 = *lwork - iwork + 1;
	    zungbr_("P", m, n, m, &a[a_offset], lda, &work[itaup], &work[
		    iwork], &i__1, info);
	    t2 = dsecnd_();
	    lstime_1.timng[ungbr - 1] += t2 - t1;
	    irwork = ie + *m;

/*        Perform bidiagonal QR iteration,   
             computing right singular vectors of A in A and   
             multiplying B by transpose of left singular vectors   
          (CWorkspace: none)   
          (RWorkspace: need BDSPAC) */

	    latime_1.ops = 0.;
	    t1 = dsecnd_();
	    zbdsqr_("L", m, n, &c__0, nrhs, &s[1], &rwork[ie], &a[a_offset], 
		    lda, vdum, &c__1, &b[b_offset], ldb, &rwork[irwork], info);
	    t2 = dsecnd_();
	    lstime_1.timng[bdsqr - 1] += t2 - t1;
	    lstime_1.opcnt[bdsqr - 1] += latime_1.ops;
	    if (*info != 0) {
		goto L70;
	    }

/*        Multiply B by reciprocals of singular values */

	    lstime_1.opcnt[gelss - 1] += 1.;
/* Computing MAX */
	    d__1 = *rcond * s[1];
	    thr = max(d__1,sfmin);
	    if (*rcond < 0.) {
		lstime_1.opcnt[gelss - 1] += 1.;
/* Computing MAX */
		d__1 = eps * s[1];
		thr = max(d__1,sfmin);
	    }
	    *rank = 0;
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (s[i__] > thr) {
		    lstime_1.opcnt[gelss - 1] += (doublereal) (*nrhs * 6 + 3);
		    zdrscl_(nrhs, &s[i__], &b_ref(i__, 1), ldb);
		    ++(*rank);
		} else {
		    zlaset_("F", &c__1, nrhs, &c_b1, &c_b1, &b_ref(i__, 1), 
			    ldb);
		}
/* L50: */
	    }

/*        Multiply B by right singular vectors of A   
          (CWorkspace: need N, prefer N*NRHS)   
          (RWorkspace: none) */

	    if (*lwork >= *ldb * *nrhs && *nrhs > 1) {
		lstime_1.opcnt[gemm - 1] += dopbl3_("ZGEMM ", n, nrhs, m);
		t1 = dsecnd_();
		zgemm_("C", "N", n, nrhs, m, &c_b2, &a[a_offset], lda, &b[
			b_offset], ldb, &c_b1, &work[1], ldb);
		t2 = dsecnd_();
		lstime_1.timng[gemm - 1] += t2 - t1;
		zlacpy_("G", n, nrhs, &work[1], ldb, &b[b_offset], ldb);
	    } else if (*nrhs > 1) {
		chunk = *lwork / *n;
		i__1 = *nrhs;
		i__2 = chunk;
		for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += 
			i__2) {
/* Computing MIN */
		    i__3 = *nrhs - i__ + 1;
		    bl = min(i__3,chunk);
		    lstime_1.opcnt[gemm - 1] += dopbl3_("ZGEMM ", n, &bl, n);
		    t1 = dsecnd_();
		    zgemm_("C", "N", n, &bl, m, &c_b2, &a[a_offset], lda, &
			    b_ref(1, i__), ldb, &c_b1, &work[1], n);
		    t2 = dsecnd_();
		    lstime_1.timng[gemm - 1] += t2 - t1;
		    zlacpy_("F", n, &bl, &work[1], n, &b_ref(1, i__), ldb);
/* L60: */
		}
	    } else {
		lstime_1.opcnt[gelss - 1] += dopbl2_("ZGEMV ", m, n, &c__0, &
			c__0);
		t1 = dsecnd_();
		zgemv_("C", m, n, &c_b2, &a[a_offset], lda, &b[b_offset], &
			c__1, &c_b1, &work[1], &c__1);
		t2 = dsecnd_();
		lstime_1.timng[gemv - 1] += t2 - t1;
		zcopy_(n, &work[1], &c__1, &b[b_offset], &c__1);
	    }
	}
    }

/*     Undo scaling */

    if (iascl == 1) {
	lstime_1.opcnt[gelss - 1] += (doublereal) ((*n * *nrhs + minmn) * 6);
	zlascl_("G", &c__0, &c__0, &anrm, &smlnum, n, nrhs, &b[b_offset], ldb,
		 info);
	dlascl_("G", &c__0, &c__0, &smlnum, &anrm, &minmn, &c__1, &s[1], &
		minmn, info);
    } else if (iascl == 2) {
	lstime_1.opcnt[gelss - 1] += (doublereal) ((*n * *nrhs + minmn) * 6);
	zlascl_("G", &c__0, &c__0, &anrm, &bignum, n, nrhs, &b[b_offset], ldb,
		 info);
	dlascl_("G", &c__0, &c__0, &bignum, &anrm, &minmn, &c__1, &s[1], &
		minmn, info);
    }
    if (ibscl == 1) {
	lstime_1.opcnt[gelss - 1] += (doublereal) (*n * 6 * *nrhs);
	zlascl_("G", &c__0, &c__0, &smlnum, &bnrm, n, nrhs, &b[b_offset], ldb,
		 info);
    } else if (ibscl == 2) {
	lstime_1.opcnt[gelss - 1] += (doublereal) (*n * 6 * *nrhs);
	zlascl_("G", &c__0, &c__0, &bignum, &bnrm, n, nrhs, &b[b_offset], ldb,
		 info);
    }
L70:
    work[1].r = (doublereal) maxwrk, work[1].i = 0.;
    return 0;

/*     End of ZGELSS */

} /* zgelss_ */

#undef b_ref
#undef b_subscr
#undef a_ref
#undef a_subscr


