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

static integer c__2 = 2;
static integer c__1 = 1;
static integer c_n1 = -1;

/* Subroutine */ int sstein_(integer *n, real *d__, real *e, integer *m, real 
	*w, integer *iblock, integer *isplit, real *z__, integer *ldz, real *
	work, integer *iwork, integer *ifail, integer *info)
{
    /* System generated locals */
    integer z_dim1, z_offset, i__1, i__2, i__3;
    real r__1, r__2, r__3, r__4, r__5;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer jblk, nblk, jmax;
    extern doublereal sdot_(integer *, real *, integer *, real *, integer *), 
	    snrm2_(integer *, real *, integer *);
    static integer i__, j, iseed[4], gpind, iinfo;
    extern /* Subroutine */ int sscal_(integer *, real *, real *, integer *);
    static integer b1;
    extern doublereal sasum_(integer *, real *, integer *);
    static integer j1;
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *);
    static real ortol;
    extern /* Subroutine */ int saxpy_(integer *, real *, real *, integer *, 
	    real *, integer *);
    static integer indrv1, indrv2, indrv3, indrv4, indrv5, bn;
    static real xj;
    extern doublereal slamch_(char *);
    extern /* Subroutine */ int xerbla_(char *, integer *), slagtf_(
	    integer *, real *, real *, real *, real *, real *, real *, 
	    integer *, integer *);
    static integer nrmchk;
    extern integer isamax_(integer *, real *, integer *);
    extern /* Subroutine */ int slagts_(integer *, integer *, real *, real *, 
	    real *, real *, integer *, real *, real *, integer *);
    static integer blksiz;
    static real onenrm, pertol;
    extern /* Subroutine */ int slarnv_(integer *, integer *, integer *, real 
	    *);
    static real stpcrt, scl, eps, ctr, sep, nrm, tol;
    static integer its;
    static real xjm, eps1;


#define z___ref(a_1,a_2) z__[(a_2)*z_dim1 + a_1]


/*  -- LAPACK routine (instrumented to count operations, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   

       Common block to return operation count and iteration count   
       ITCNT is initialized to 0, OPS is only incremented   

    Purpose   
    =======   

    SSTEIN computes the eigenvectors of a real symmetric tridiagonal   
    matrix T corresponding to specified eigenvalues, using inverse   
    iteration.   

    The maximum number of iterations allowed for each eigenvector is   
    specified by an internal parameter MAXITS (currently set to 5).   

    Arguments   
    =========   

    N       (input) INTEGER   
            The order of the matrix.  N >= 0.   

    D       (input) REAL array, dimension (N)   
            The n diagonal elements of the tridiagonal matrix T.   

    E       (input) REAL array, dimension (N)   
            The (n-1) subdiagonal elements of the tridiagonal matrix   
            T, in elements 1 to N-1.  E(N) need not be set.   

    M       (input) INTEGER   
            The number of eigenvectors to be found.  0 <= M <= N.   

    W       (input) REAL array, dimension (N)   
            The first M elements of W contain the eigenvalues for   
            which eigenvectors are to be computed.  The eigenvalues   
            should be grouped by split-off block and ordered from   
            smallest to largest within the block.  ( The output array   
            W from SSTEBZ with ORDER = 'B' is expected here. )   

    IBLOCK  (input) INTEGER array, dimension (N)   
            The submatrix indices associated with the corresponding   
            eigenvalues in W; IBLOCK(i)=1 if eigenvalue W(i) belongs to   
            the first submatrix from the top, =2 if W(i) belongs to   
            the second submatrix, etc.  ( The output array IBLOCK   
            from SSTEBZ is expected here. )   

    ISPLIT  (input) INTEGER array, dimension (N)   
            The splitting points, at which T breaks up into submatrices.   
            The first submatrix consists of rows/columns 1 to   
            ISPLIT( 1 ), the second of rows/columns ISPLIT( 1 )+1   
            through ISPLIT( 2 ), etc.   
            ( The output array ISPLIT from SSTEBZ is expected here. )   

    Z       (output) REAL array, dimension (LDZ, M)   
            The computed eigenvectors.  The eigenvector associated   
            with the eigenvalue W(i) is stored in the i-th column of   
            Z.  Any vector which fails to converge is set to its current   
            iterate after MAXITS iterations.   

    LDZ     (input) INTEGER   
            The leading dimension of the array Z.  LDZ >= max(1,N).   

    WORK    (workspace) REAL array, dimension (5*N)   

    IWORK   (workspace) INTEGER array, dimension (N)   

    IFAIL   (output) INTEGER array, dimension (M)   
            On normal exit, all elements of IFAIL are zero.   
            If one or more eigenvectors fail to converge after   
            MAXITS iterations, then their indices are stored in   
            array IFAIL.   

    INFO    (output) INTEGER   
            = 0: successful exit.   
            < 0: if INFO = -i, the i-th argument had an illegal value   
            > 0: if INFO = i, then i eigenvectors failed to converge   
                 in MAXITS iterations.  Their indices are stored in   
                 array IFAIL.   

    Internal Parameters   
    ===================   

    MAXITS  INTEGER, default = 5   
            The maximum number of iterations performed.   

    EXTRA   INTEGER, default = 2   
            The number of iterations performed after norm growth   
            criterion is satisfied, should be at least 1.   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    --d__;
    --e;
    --w;
    --iblock;
    --isplit;
    z_dim1 = *ldz;
    z_offset = 1 + z_dim1 * 1;
    z__ -= z_offset;
    --work;
    --iwork;
    --ifail;

    /* Function Body */
    *info = 0;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ifail[i__] = 0;
/* L10: */
    }

    if (*n < 0) {
	*info = -1;
    } else if (*m < 0 || *m > *n) {
	*info = -4;
    } else if (*ldz < max(1,*n)) {
	*info = -9;
    } else {
	i__1 = *m;
	for (j = 2; j <= i__1; ++j) {
	    if (iblock[j] < iblock[j - 1]) {
		*info = -6;
		goto L30;
	    }
	    if (iblock[j] == iblock[j - 1] && w[j] < w[j - 1]) {
		*info = -5;
		goto L30;
	    }
/* L20: */
	}
L30:
	;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SSTEIN", &i__1);
	return 0;
    }

/*     Initialize iteration count. */

    latime_1.itcnt = 0.f;

/*     Quick return if possible */

    if (*n == 0 || *m == 0) {
	return 0;
    } else if (*n == 1) {
	z___ref(1, 1) = 1.f;
	return 0;
    }

/*     Get machine constants. */

    eps = slamch_("Precision");

/*     Initialize seed for random number generator SLARNV. */

    for (i__ = 1; i__ <= 4; ++i__) {
	iseed[i__ - 1] = 1;
/* L40: */
    }

/*     Initialize pointers. */

    indrv1 = 0;
    indrv2 = indrv1 + *n;
    indrv3 = indrv2 + *n;
    indrv4 = indrv3 + *n;
    indrv5 = indrv4 + *n;

/*     Compute eigenvectors of matrix blocks. */

    j1 = 1;
    i__1 = iblock[*m];
    for (nblk = 1; nblk <= i__1; ++nblk) {

/*        Find starting and ending indices of block nblk. */

	if (nblk == 1) {
	    b1 = 1;
	} else {
	    b1 = isplit[nblk - 1] + 1;
	}
	bn = isplit[nblk];
	blksiz = bn - b1 + 1;
	if (blksiz == 1) {
	    goto L60;
	}
	gpind = b1;

/*        Compute reorthogonalization criterion and stopping criterion. */

	onenrm = (r__1 = d__[b1], dabs(r__1)) + (r__2 = e[b1], dabs(r__2));
/* Computing MAX */
	r__3 = onenrm, r__4 = (r__1 = d__[bn], dabs(r__1)) + (r__2 = e[bn - 1]
		, dabs(r__2));
	onenrm = dmax(r__3,r__4);
	i__2 = bn - 1;
	for (i__ = b1 + 1; i__ <= i__2; ++i__) {
/* Computing MAX */
	    r__4 = onenrm, r__5 = (r__1 = d__[i__], dabs(r__1)) + (r__2 = e[
		    i__ - 1], dabs(r__2)) + (r__3 = e[i__], dabs(r__3));
	    onenrm = dmax(r__4,r__5);
/* L50: */
	}
	ortol = onenrm * .001f;

	stpcrt = sqrt(.1f / blksiz);

/*        Increment opcount for computing criteria. */

	latime_1.ops = latime_1.ops + (bn - b1 << 1) + 3;

/*        Loop through eigenvalues of block nblk. */

L60:
	jblk = 0;
	i__2 = *m;
	for (j = j1; j <= i__2; ++j) {
	    if (iblock[j] != nblk) {
		j1 = j;
		goto L160;
	    }
	    ++jblk;
	    xj = w[j];

/*           Skip all the work if the block size is one. */

	    if (blksiz == 1) {
		work[indrv1 + 1] = 1.f;
		goto L120;
	    }

/*           If eigenvalues j and j-1 are too close, add a relatively   
             small perturbation. */

	    if (jblk > 1) {
		eps1 = (r__1 = eps * xj, dabs(r__1));
		pertol = eps1 * 10.f;
		sep = xj - xjm;
		if (sep < pertol) {
		    xj = xjm + pertol;
		}
	    }

	    its = 0;
	    nrmchk = 0;

/*           Get random starting vector. */

	    slarnv_(&c__2, iseed, &blksiz, &work[indrv1 + 1]);

/*           Increment opcount for getting random starting vector.   
             ( SLARND(2,.) requires 9 flops. ) */

	    latime_1.ops += blksiz * 9;

/*           Copy the matrix T so it won't be destroyed in factorization. */

	    scopy_(&blksiz, &d__[b1], &c__1, &work[indrv4 + 1], &c__1);
	    i__3 = blksiz - 1;
	    scopy_(&i__3, &e[b1], &c__1, &work[indrv2 + 2], &c__1);
	    i__3 = blksiz - 1;
	    scopy_(&i__3, &e[b1], &c__1, &work[indrv3 + 1], &c__1);

/*           Compute LU factors with partial pivoting  ( PT = LU ) */

	    tol = 0.f;
	    slagtf_(&blksiz, &work[indrv4 + 1], &xj, &work[indrv2 + 2], &work[
		    indrv3 + 1], &tol, &work[indrv5 + 1], &iwork[1], &iinfo);

/*           Increment opcount for computing LU factors.   
             ( SLAGTF(BLKSIZ,...) requires about 8*BLKSIZ flops. ) */

	    latime_1.ops += blksiz << 3;

/*           Update iteration count. */

L70:
	    ++its;
	    if (its > 5) {
		goto L100;
	    }

/*           Normalize and scale the righthand side vector Pb.   

   Computing MAX */
	    r__2 = eps, r__3 = (r__1 = work[indrv4 + blksiz], dabs(r__1));
	    scl = blksiz * onenrm * dmax(r__2,r__3) / sasum_(&blksiz, &work[
		    indrv1 + 1], &c__1);
	    sscal_(&blksiz, &scl, &work[indrv1 + 1], &c__1);

/*           Solve the system LU = Pb. */

	    slagts_(&c_n1, &blksiz, &work[indrv4 + 1], &work[indrv2 + 2], &
		    work[indrv3 + 1], &work[indrv5 + 1], &iwork[1], &work[
		    indrv1 + 1], &tol, &iinfo);

/*           Increment opcount for scaling and solving linear system.   
             ( SLAGTS(-1,BLKSIZ,...) requires about 8*BLKSIZ flops. ) */

	    latime_1.ops = latime_1.ops + 3 + blksiz * 10;

/*           Reorthogonalize by modified Gram-Schmidt if eigenvalues are   
             close enough. */

	    if (jblk == 1) {
		goto L90;
	    }
	    if ((r__1 = xj - xjm, dabs(r__1)) > ortol) {
		gpind = j;
	    }
	    if (gpind != j) {
		i__3 = j - 1;
		for (i__ = gpind; i__ <= i__3; ++i__) {
		    ctr = -sdot_(&blksiz, &work[indrv1 + 1], &c__1, &z___ref(
			    b1, i__), &c__1);
		    saxpy_(&blksiz, &ctr, &z___ref(b1, i__), &c__1, &work[
			    indrv1 + 1], &c__1);
/* L80: */
		}

/*              Increment opcount for reorthogonalizing. */

		latime_1.ops += (j - gpind) * blksiz << 2;

	    }

/*           Check the infinity norm of the iterate. */

L90:
	    jmax = isamax_(&blksiz, &work[indrv1 + 1], &c__1);
	    nrm = (r__1 = work[indrv1 + jmax], dabs(r__1));

/*           Continue for additional iterations after norm reaches   
             stopping criterion. */

	    if (nrm < stpcrt) {
		goto L70;
	    }
	    ++nrmchk;
	    if (nrmchk < 3) {
		goto L70;
	    }

	    goto L110;

/*           If stopping criterion was not satisfied, update info and   
             store eigenvector number in array ifail. */

L100:
	    ++(*info);
	    ifail[*info] = j;

/*           Accept iterate as jth eigenvector. */

L110:
	    scl = 1.f / snrm2_(&blksiz, &work[indrv1 + 1], &c__1);
	    jmax = isamax_(&blksiz, &work[indrv1 + 1], &c__1);
	    if (work[indrv1 + jmax] < 0.f) {
		scl = -scl;
	    }
	    sscal_(&blksiz, &scl, &work[indrv1 + 1], &c__1);

/*           Increment opcount for scaling. */

	    latime_1.ops += blksiz * 3;

L120:
	    i__3 = *n;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		z___ref(i__, j) = 0.f;
/* L130: */
	    }
	    i__3 = blksiz;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		z___ref(b1 + i__ - 1, j) = work[indrv1 + i__];
/* L140: */
	    }

/*           Save the shift to check eigenvalue spacing at next   
             iteration. */

	    xjm = xj;

/* L150: */
	}
L160:
	;
    }

    return 0;

/*     End of SSTEIN */

} /* sstein_ */

#undef z___ref


