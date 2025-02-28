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
static real c_b30 = 0.f;

/* Subroutine */ int slasd2_(integer *nl, integer *nr, integer *sqre, integer 
	*k, real *d__, real *z__, real *alpha, real *beta, real *u, integer *
	ldu, real *vt, integer *ldvt, real *dsigma, real *u2, integer *ldu2, 
	real *vt2, integer *ldvt2, integer *idxp, integer *idx, integer *idxc,
	 integer *idxq, integer *coltyp, integer *info)
{
    /* System generated locals */
    integer u_dim1, u_offset, u2_dim1, u2_offset, vt_dim1, vt_offset, 
	    vt2_dim1, vt2_offset, i__1;
    real r__1, r__2;

    /* Local variables */
    static integer idxi, idxj, ctot[4];
    extern /* Subroutine */ int srot_(integer *, real *, integer *, real *, 
	    integer *, real *, real *);
    static real c__;
    static integer i__, j, m, n;
    static real s;
    static integer idxjp, jprev, k2;
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *);
    static real z1;
    extern doublereal slapy2_(real *, real *);
    static integer ct, jp;
    extern doublereal slamch_(char *);
    extern /* Subroutine */ int xerbla_(char *, integer *), slamrg_(
	    integer *, integer *, real *, integer *, integer *, integer *);
    static real hlftol;
    extern /* Subroutine */ int slacpy_(char *, integer *, integer *, real *, 
	    integer *, real *, integer *), slaset_(char *, integer *, 
	    integer *, real *, real *, real *, integer *);
    static real eps, tau, tol;
    static integer psm[4], nlp1, nlp2;


#define u_ref(a_1,a_2) u[(a_2)*u_dim1 + a_1]
#define u2_ref(a_1,a_2) u2[(a_2)*u2_dim1 + a_1]
#define vt_ref(a_1,a_2) vt[(a_2)*vt_dim1 + a_1]
#define vt2_ref(a_1,a_2) vt2[(a_2)*vt2_dim1 + a_1]


/*  -- LAPACK auxiliary routine (instrumented to count ops, version 3.0) --   
       Univ. of Tennessee, Oak Ridge National Lab, Argonne National Lab,   
       Courant Institute, NAG Ltd., and Rice University   
       October 31, 1999   


    Purpose   
    =======   

    SLASD2 merges the two sets of singular values together into a single   
    sorted set.  Then it tries to deflate the size of the problem.   
    There are two ways in which deflation can occur:  when two or more   
    singular values are close together or if there is a tiny entry in the   
    Z vector.  For each such occurrence the order of the related secular   
    equation problem is reduced by one.   

    SLASD2 is called from SLASD1.   

    Arguments   
    =========   

    NL     (input) INTEGER   
           The row dimension of the upper block.  NL >= 1.   

    NR     (input) INTEGER   
           The row dimension of the lower block.  NR >= 1.   

    SQRE   (input) INTEGER   
           = 0: the lower block is an NR-by-NR square matrix.   
           = 1: the lower block is an NR-by-(NR+1) rectangular matrix.   

           The bidiagonal matrix has N = NL + NR + 1 rows and   
           M = N + SQRE >= N columns.   

    K      (output) INTEGER   
           Contains the dimension of the non-deflated matrix,   
           This is the order of the related secular equation. 1 <= K <=N.   

    D      (input/output) REAL array, dimension(N)   
           On entry D contains the singular values of the two submatrices   
           to be combined.  On exit D contains the trailing (N-K) updated   
           singular values (those which were deflated) sorted into   
           increasing order.   

    ALPHA  (input) REAL   
           Contains the diagonal element associated with the added row.   

    BETA   (input) REAL   
           Contains the off-diagonal element associated with the added   
           row.   

    U      (input/output) REAL array, dimension(LDU,N)   
           On entry U contains the left singular vectors of two   
           submatrices in the two square blocks with corners at (1,1),   
           (NL, NL), and (NL+2, NL+2), (N,N).   
           On exit U contains the trailing (N-K) updated left singular   
           vectors (those which were deflated) in its last N-K columns.   

    LDU    (input) INTEGER   
           The leading dimension of the array U.  LDU >= N.   

    Z      (output) REAL array, dimension(N)   
           On exit Z contains the updating row vector in the secular   
           equation.   

    DSIGMA (output) REAL array, dimension (N)   
           Contains a copy of the diagonal elements (K-1 singular values   
           and one zero) in the secular equation.   

    U2     (output) REAL array, dimension(LDU2,N)   
           Contains a copy of the first K-1 left singular vectors which   
           will be used by SLASD3 in a matrix multiply (SGEMM) to solve   
           for the new left singular vectors. U2 is arranged into four   
           blocks. The first block contains a column with 1 at NL+1 and   
           zero everywhere else; the second block contains non-zero   
           entries only at and above NL; the third contains non-zero   
           entries only below NL+1; and the fourth is dense.   

    LDU2   (input) INTEGER   
           The leading dimension of the array U2.  LDU2 >= N.   

    VT     (input/output) REAL array, dimension(LDVT,M)   
           On entry VT' contains the right singular vectors of two   
           submatrices in the two square blocks with corners at (1,1),   
           (NL+1, NL+1), and (NL+2, NL+2), (M,M).   
           On exit VT' contains the trailing (N-K) updated right singular   
           vectors (those which were deflated) in its last N-K columns.   
           In case SQRE =1, the last row of VT spans the right null   
           space.   

    LDVT   (input) INTEGER   
           The leading dimension of the array VT.  LDVT >= M.   

    VT2    (output) REAL array, dimension(LDVT2,N)   
           VT2' contains a copy of the first K right singular vectors   
           which will be used by SLASD3 in a matrix multiply (SGEMM) to   
           solve for the new right singular vectors. VT2 is arranged into   
           three blocks. The first block contains a row that corresponds   
           to the special 0 diagonal element in SIGMA; the second block   
           contains non-zeros only at and before NL +1; the third block   
           contains non-zeros only at and after  NL +2.   

    LDVT2  (input) INTEGER   
           The leading dimension of the array VT2.  LDVT2 >= M.   

    IDXP   (workspace) INTEGER array, dimension(N)   
           This will contain the permutation used to place deflated   
           values of D at the end of the array. On output IDXP(2:K)   
           points to the nondeflated D-values and IDXP(K+1:N)   
           points to the deflated singular values.   

    IDX    (workspace) INTEGER array, dimension(N)   
           This will contain the permutation used to sort the contents of   
           D into ascending order.   

    IDXC   (output) INTEGER array, dimension(N)   
           This will contain the permutation used to arrange the columns   
           of the deflated U matrix into three groups:  the first group   
           contains non-zero entries only at and above NL, the second   
           contains non-zero entries only below NL+2, and the third is   
           dense.   

    COLTYP (workspace/output) INTEGER array, dimension(N)   
           As workspace, this will contain a label which will indicate   
           which of the following types a column in the U2 matrix or a   
           row in the VT2 matrix is:   
           1 : non-zero in the upper half only   
           2 : non-zero in the lower half only   
           3 : dense   
           4 : deflated   

           On exit, it is an array of dimension 4, with COLTYP(I) being   
           the dimension of the I-th type columns.   

    IDXQ   (input) INTEGER array, dimension(N)   
           This contains the permutation which separately sorts the two   
           sub-problems in D into ascending order.  Note that entries in   
           the first hlaf of this permutation must first be moved one   
           position backward; and entries in the second half   
           must first have NL+1 added to their values.   

    INFO   (output) INTEGER   
            = 0:  successful exit.   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   

    Further Details   
    ===============   

    Based on contributions by   
       Ming Gu and Huan Ren, Computer Science Division, University of   
       California at Berkeley, USA   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    --d__;
    --z__;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1 * 1;
    u -= u_offset;
    vt_dim1 = *ldvt;
    vt_offset = 1 + vt_dim1 * 1;
    vt -= vt_offset;
    --dsigma;
    u2_dim1 = *ldu2;
    u2_offset = 1 + u2_dim1 * 1;
    u2 -= u2_offset;
    vt2_dim1 = *ldvt2;
    vt2_offset = 1 + vt2_dim1 * 1;
    vt2 -= vt2_offset;
    --idxp;
    --idx;
    --idxc;
    --idxq;
    --coltyp;

    /* Function Body */
    *info = 0;

    if (*nl < 1) {
	*info = -1;
    } else if (*nr < 1) {
	*info = -2;
    } else if (*sqre != 1 && *sqre != 0) {
	*info = -3;
    }

    n = *nl + *nr + 1;
    m = n + *sqre;

    if (*ldu < n) {
	*info = -10;
    } else if (*ldvt < m) {
	*info = -12;
    } else if (*ldu2 < n) {
	*info = -15;
    } else if (*ldvt2 < m) {
	*info = -17;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SLASD2", &i__1);
	return 0;
    }

    nlp1 = *nl + 1;
    nlp2 = *nl + 2;

/*     Generate the first part of the vector Z; and move the singular   
       values in the first part of D one position backward. */

    latime_1.ops += (real) (*nl + 1);
    z1 = *alpha * vt_ref(nlp1, nlp1);
    z__[1] = z1;
    for (i__ = *nl; i__ >= 1; --i__) {
	z__[i__ + 1] = *alpha * vt_ref(i__, nlp1);
	d__[i__ + 1] = d__[i__];
	idxq[i__ + 1] = idxq[i__] + 1;
/* L10: */
    }

/*     Generate the second part of the vector Z. */

    latime_1.ops += (real) (m - nlp2 + 1);
    i__1 = m;
    for (i__ = nlp2; i__ <= i__1; ++i__) {
	z__[i__] = *beta * vt_ref(i__, nlp2);
/* L20: */
    }

/*     Initialize some reference arrays. */

    i__1 = nlp1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	coltyp[i__] = 1;
/* L30: */
    }
    i__1 = n;
    for (i__ = nlp2; i__ <= i__1; ++i__) {
	coltyp[i__] = 2;
/* L40: */
    }

/*     Sort the singular values into increasing order */

    i__1 = n;
    for (i__ = nlp2; i__ <= i__1; ++i__) {
	idxq[i__] += nlp1;
/* L50: */
    }

/*     DSIGMA, IDXC, IDXC, and the first column of U2   
       are used as storage space. */

    i__1 = n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	dsigma[i__] = d__[idxq[i__]];
	u2_ref(i__, 1) = z__[idxq[i__]];
	idxc[i__] = coltyp[idxq[i__]];
/* L60: */
    }

    slamrg_(nl, nr, &dsigma[2], &c__1, &c__1, &idx[2]);

    i__1 = n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	idxi = idx[i__] + 1;
	d__[i__] = dsigma[idxi];
	z__[i__] = u2_ref(idxi, 1);
	coltyp[i__] = idxc[idxi];
/* L70: */
    }

/*     Calculate the allowable deflation tolerance */

    latime_1.ops += 2.f;
    eps = slamch_("Epsilon");
/* Computing MAX */
    r__1 = dabs(*alpha), r__2 = dabs(*beta);
    tol = dmax(r__1,r__2);
/* Computing MAX */
    r__2 = (r__1 = d__[n], dabs(r__1));
    tol = eps * 8.f * dmax(r__2,tol);

/*     There are 2 kinds of deflation -- first a value in the z-vector   
       is small, second two (or more) singular values are very close   
       together (their difference is small).   

       If the value in the z-vector is small, we simply permute the   
       array so that the corresponding singular value is moved to the   
       end.   

       If two values in the D-vector are close, we perform a two-sided   
       rotation designed to make one of the corresponding z-vector   
       entries zero, and then permute the array so that the deflated   
       singular value is moved to the end.   

       If there are multiple singular values then the problem deflates.   
       Here the number of equal singular values are found.  As each equal   
       singular value is found, an elementary reflector is computed to   
       rotate the corresponding singular subspace so that the   
       corresponding components of Z are zero in this new basis. */

    *k = 1;
    k2 = n + 1;
    i__1 = n;
    for (j = 2; j <= i__1; ++j) {
	if ((r__1 = z__[j], dabs(r__1)) <= tol) {

/*           Deflate due to small z component. */

	    --k2;
	    idxp[k2] = j;
	    coltyp[j] = 4;
	    if (j == n) {
		goto L120;
	    }
	} else {
	    jprev = j;
	    goto L90;
	}
/* L80: */
    }
L90:
    j = jprev;
L100:
    ++j;
    if (j > n) {
	goto L110;
    }
    if ((r__1 = z__[j], dabs(r__1)) <= tol) {

/*        Deflate due to small z component. */

	--k2;
	idxp[k2] = j;
	coltyp[j] = 4;
    } else {

/*        Check if singular values are close enough to allow deflation. */

	latime_1.ops += 1.f;
	if ((r__1 = d__[j] - d__[jprev], dabs(r__1)) <= tol) {

/*           Deflation is possible. */

	    s = z__[jprev];
	    c__ = z__[j];

/*           Find sqrt(a**2+b**2) without overflow or   
             destructive underflow. */

	    latime_1.ops += 7.f;
	    tau = slapy2_(&c__, &s);
	    c__ /= tau;
	    s = -s / tau;
	    z__[j] = tau;
	    z__[jprev] = 0.f;

/*           Apply back the Givens rotation to the left and right   
             singular vector matrices. */

	    idxjp = idxq[idx[jprev] + 1];
	    idxj = idxq[idx[j] + 1];
	    if (idxjp <= nlp1) {
		--idxjp;
	    }
	    if (idxj <= nlp1) {
		--idxj;
	    }
	    latime_1.ops += 12.f;
	    srot_(&n, &u_ref(1, idxjp), &c__1, &u_ref(1, idxj), &c__1, &c__, &
		    s);
	    srot_(&m, &vt_ref(idxjp, 1), ldvt, &vt_ref(idxj, 1), ldvt, &c__, &
		    s);
	    if (coltyp[j] != coltyp[jprev]) {
		coltyp[j] = 3;
	    }
	    coltyp[jprev] = 4;
	    --k2;
	    idxp[k2] = jprev;
	    jprev = j;
	} else {
	    ++(*k);
	    u2_ref(*k, 1) = z__[jprev];
	    dsigma[*k] = d__[jprev];
	    idxp[*k] = jprev;
	    jprev = j;
	}
    }
    goto L100;
L110:

/*     Record the last singular value. */

    ++(*k);
    u2_ref(*k, 1) = z__[jprev];
    dsigma[*k] = d__[jprev];
    idxp[*k] = jprev;

L120:

/*     Count up the total number of the various types of columns, then   
       form a permutation which positions the four column types into   
       four groups of uniform structure (although one or more of these   
       groups may be empty). */

    for (j = 1; j <= 4; ++j) {
	ctot[j - 1] = 0;
/* L130: */
    }
    i__1 = n;
    for (j = 2; j <= i__1; ++j) {
	ct = coltyp[j];
	++ctot[ct - 1];
/* L140: */
    }

/*     PSM(*) = Position in SubMatrix (of types 1 through 4) */

    psm[0] = 2;
    psm[1] = ctot[0] + 2;
    psm[2] = psm[1] + ctot[1];
    psm[3] = psm[2] + ctot[2];

/*     Fill out the IDXC array so that the permutation which it induces   
       will place all type-1 columns first, all type-2 columns next,   
       then all type-3's, and finally all type-4's, starting from the   
       second column. This applies similarly to the rows of VT. */

    i__1 = n;
    for (j = 2; j <= i__1; ++j) {
	jp = idxp[j];
	ct = coltyp[jp];
	idxc[psm[ct - 1]] = j;
	++psm[ct - 1];
/* L150: */
    }

/*     Sort the singular values and corresponding singular vectors into   
       DSIGMA, U2, and VT2 respectively.  The singular values/vectors   
       which were not deflated go into the first K slots of DSIGMA, U2,   
       and VT2 respectively, while those which were deflated go into the   
       last N - K slots, except that the first column/row will be treated   
       separately. */

    i__1 = n;
    for (j = 2; j <= i__1; ++j) {
	jp = idxp[j];
	dsigma[j] = d__[jp];
	idxj = idxq[idx[idxp[idxc[j]]] + 1];
	if (idxj <= nlp1) {
	    --idxj;
	}
	scopy_(&n, &u_ref(1, idxj), &c__1, &u2_ref(1, j), &c__1);
	scopy_(&m, &vt_ref(idxj, 1), ldvt, &vt2_ref(j, 1), ldvt2);
/* L160: */
    }

/*     Determine DSIGMA(1), DSIGMA(2) and Z(1) */

    latime_1.ops += 1.f;
    dsigma[1] = 0.f;
    hlftol = tol / 2.f;
    if (dabs(dsigma[2]) <= hlftol) {
	dsigma[2] = hlftol;
    }
    if (m > n) {
	latime_1.ops += 5.f;
	z__[1] = slapy2_(&z1, &z__[m]);
	if (z__[1] <= tol) {
	    c__ = 1.f;
	    s = 0.f;
	    z__[1] = tol;
	} else {
	    latime_1.ops += 2.f;
	    c__ = z1 / z__[1];
	    s = z__[m] / z__[1];
	}
    } else {
	if (dabs(z1) <= tol) {
	    z__[1] = tol;
	} else {
	    z__[1] = z1;
	}
    }

/*     Move the rest of the updating row to Z. */

    i__1 = *k - 1;
    scopy_(&i__1, &u2_ref(2, 1), &c__1, &z__[2], &c__1);

/*     Determine the first column of U2, the first row of VT2 and the   
       last row of VT. */

    slaset_("A", &n, &c__1, &c_b30, &c_b30, &u2[u2_offset], ldu2);
    u2_ref(nlp1, 1) = 1.f;
    if (m > n) {
	latime_1.ops += (real) (nlp1 << 1);
	i__1 = nlp1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    vt_ref(m, i__) = -s * vt_ref(nlp1, i__);
	    vt2_ref(1, i__) = c__ * vt_ref(nlp1, i__);
/* L170: */
	}
	latime_1.ops += (real) (m - nlp2 + 1 << 1);
	i__1 = m;
	for (i__ = nlp2; i__ <= i__1; ++i__) {
	    vt2_ref(1, i__) = s * vt_ref(m, i__);
	    vt_ref(m, i__) = c__ * vt_ref(m, i__);
/* L180: */
	}
    } else {
	scopy_(&m, &vt_ref(nlp1, 1), ldvt, &vt2_ref(1, 1), ldvt2);
    }
    if (m > n) {
	scopy_(&m, &vt_ref(m, 1), ldvt, &vt2_ref(m, 1), ldvt2);
    }

/*     The deflated singular values and their corresponding vectors go   
       into the back of D, U, and V respectively. */

    if (n > *k) {
	i__1 = n - *k;
	scopy_(&i__1, &dsigma[*k + 1], &c__1, &d__[*k + 1], &c__1);
	i__1 = n - *k;
	slacpy_("A", &n, &i__1, &u2_ref(1, *k + 1), ldu2, &u_ref(1, *k + 1), 
		ldu);
	i__1 = n - *k;
	slacpy_("A", &i__1, &m, &vt2_ref(*k + 1, 1), ldvt2, &vt_ref(*k + 1, 1)
		, ldvt);
    }

/*     Copy CTOT into COLTYP for referencing in SLASD3. */

    for (j = 1; j <= 4; ++j) {
	coltyp[j] = ctot[j - 1];
/* L190: */
    }

    return 0;

/*     End of SLASD2 */

} /* slasd2_ */

#undef vt2_ref
#undef vt_ref
#undef u2_ref
#undef u_ref


