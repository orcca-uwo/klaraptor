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

static complex c_b1 = {0.f,0.f};
static integer c__1 = 1;

/* Subroutine */ int clarrv_(integer *n, real *d__, real *l, integer *isplit, 
	integer *m, real *w, integer *iblock, real *gersch, real *tol, 
	complex *z__, integer *ldz, integer *isuppz, real *work, integer *
	iwork, integer *info)
{
    /* System generated locals */
    integer z_dim1, z_offset, i__1, i__2, i__3, i__4, i__5, i__6;
    real r__1, r__2;
    complex q__1, q__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer iend, jblk, iter, temp[1], ktot, itmp1, itmp2, i__, j, k, 
	    p, q, indld;
    static real sigma;
    static integer ndone, iinfo, iindr;
    static real resid;
    extern /* Complex */ VOID cdotu_(complex *, integer *, complex *, integer 
	    *, complex *, integer *);
    static integer nclus;
    extern /* Subroutine */ int caxpy_(integer *, complex *, complex *, 
	    integer *, complex *, integer *), scopy_(integer *, real *, 
	    integer *, real *, integer *);
    static integer iindc1, iindc2, indin1, indin2;
    extern /* Subroutine */ int clar1v_(integer *, integer *, integer *, real 
	    *, real *, real *, real *, real *, real *, complex *, real *, 
	    real *, integer *, integer *, real *);
    extern doublereal scnrm2_(integer *, complex *, integer *);
    static real lambda;
    static integer im, in, ibegin, indgap, indlld;
    extern doublereal slamch_(char *);
    static real mingma;
    extern /* Subroutine */ int csscal_(integer *, real *, complex *, integer 
	    *);
    static integer oldien, oldncl;
    static real relgap;
    extern /* Subroutine */ int claset_(char *, integer *, integer *, complex 
	    *, complex *, complex *, integer *);
    static integer oldcls, ndepth, inderr, iindwk;
    extern /* Subroutine */ int cstein_(integer *, real *, real *, integer *, 
	    real *, integer *, integer *, complex *, integer *, real *, 
	    integer *, integer *, integer *), slarrb_(integer *, real *, real 
	    *, real *, real *, integer *, integer *, real *, real *, real *, 
	    real *, real *, real *, integer *, integer *);
    static logical mgscls;
    static integer lsbdpt, newcls, oldfst;
    static real minrgp;
    static integer indwrk;
    extern /* Subroutine */ int slarrf_(integer *, real *, real *, real *, 
	    real *, integer *, integer *, real *, real *, real *, real *, 
	    integer *, integer *);
    static integer oldlst;
    static real reltol;
    static integer maxitr, newfrs, newftt;
    static real mgstol;
    static integer nsplit;
    static real nrminv, rqcorr;
    static integer newlst, newsiz;
    static real gap, eps, ztz, tmp1;


#define z___subscr(a_1,a_2) (a_2)*z_dim1 + a_1
#define z___ref(a_1,a_2) z__[z___subscr(a_1,a_2)]


/*  -- LAPACK auxiliary routine (instru to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   

       Common block to return operation count ..   

    Purpose   
    =======   

    CLARRV computes the eigenvectors of the tridiagonal matrix   
    T = L D L^T given L, D and the eigenvalues of L D L^T.   
    The input eigenvalues should have high relative accuracy with   
    respect to the entries of L and D. The desired accuracy of the   
    output can be specified by the input parameter TOL.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The order of the matrix.  N >= 0.   

    D       (input/output) REAL array, dimension (N)   
            On entry, the n diagonal elements of the diagonal matrix D.   
            On exit, D may be overwritten.   

    L       (input/output) REAL array, dimension (N-1)   
            On entry, the (n-1) subdiagonal elements of the unit   
            bidiagonal matrix L in elements 1 to N-1 of L. L(N) need   
            not be set. On exit, L is overwritten.   

    ISPLIT  (input) INTEGER array, dimension (N)   
            The splitting points, at which T breaks up into submatrices.   
            The first submatrix consists of rows/columns 1 to   
            ISPLIT( 1 ), the second of rows/columns ISPLIT( 1 )+1   
            through ISPLIT( 2 ), etc.   

    TOL     (input) REAL   
            The absolute error tolerance for the   
            eigenvalues/eigenvectors.   
            Errors in the input eigenvalues must be bounded by TOL.   
            The eigenvectors output have residual norms   
            bounded by TOL, and the dot products between different   
            eigenvectors are bounded by TOL. TOL must be at least   
            N*EPS*|T|, where EPS is the machine precision and |T| is   
            the 1-norm of the tridiagonal matrix.   

    M       (input) INTEGER   
            The total number of eigenvalues found.  0 <= M <= N.   
            If RANGE = 'A', M = N, and if RANGE = 'I', M = IU-IL+1.   

    W       (input) REAL array, dimension (N)   
            The first M elements of W contain the eigenvalues for   
            which eigenvectors are to be computed.  The eigenvalues   
            should be grouped by split-off block and ordered from   
            smallest to largest within the block ( The output array   
            W from SLARRE is expected here ).   
            Errors in W must be bounded by TOL (see above).   

    IBLOCK  (input) INTEGER array, dimension (N)   
            The submatrix indices associated with the corresponding   
            eigenvalues in W; IBLOCK(i)=1 if eigenvalue W(i) belongs to   
            the first submatrix from the top, =2 if W(i) belongs to   
            the second submatrix, etc.   

    Z       (output) COMPLEX array, dimension (LDZ, max(1,M) )   
            If JOBZ = 'V', then if INFO = 0, the first M columns of Z   
            contain the orthonormal eigenvectors of the matrix T   
            corresponding to the selected eigenvalues, with the i-th   
            column of Z holding the eigenvector associated with W(i).   
            If JOBZ = 'N', then Z is not referenced.   
            Note: the user must ensure that at least max(1,M) columns are   
            supplied in the array Z; if RANGE = 'V', the exact value of M   
            is not known in advance and an upper bound must be used.   

    LDZ     (input) INTEGER   
            The leading dimension of the array Z.  LDZ >= 1, and if   
            JOBZ = 'V', LDZ >= max(1,N).   

    ISUPPZ  (output) INTEGER ARRAY, dimension ( 2*max(1,M) )   
            The support of the eigenvectors in Z, i.e., the indices   
            indicating the nonzero elements in Z. The i-th eigenvector   
            is nonzero only in elements ISUPPZ( 2*i-1 ) through   
            ISUPPZ( 2*i ).   

    WORK    (workspace) REAL array, dimension (13*N)   

    IWORK   (workspace) INTEGER array, dimension (6*N)   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   
            > 0:  if INFO = 1, internal error in SLARRB   
                  if INFO = 2, internal error in CSTEIN   

    Further Details   
    ===============   

    Based on contributions by   
       Inderjit Dhillon, IBM Almaden, USA   
       Osni Marques, LBNL/NERSC, USA   
       Ken Stanley, Computer Science Division, University of   
         California at Berkeley, USA   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    --d__;
    --l;
    --isplit;
    --w;
    --iblock;
    --gersch;
    z_dim1 = *ldz;
    z_offset = 1 + z_dim1 * 1;
    z__ -= z_offset;
    --isuppz;
    --work;
    --iwork;

    /* Function Body */
    inderr = *n + 1;
    indld = *n << 1;
    indlld = *n * 3;
    indgap = *n << 2;
    indin1 = *n * 5 + 1;
    indin2 = *n * 6 + 1;
    indwrk = *n * 7 + 1;

    iindr = *n;
    iindc1 = *n << 1;
    iindc2 = *n * 3;
    iindwk = (*n << 2) + 1;

    eps = slamch_("Precision");

    i__1 = *n << 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	iwork[i__] = 0;
/* L10: */
    }
    latime_1.ops += (real) (*m + 1);
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	work[inderr + i__ - 1] = eps * (r__1 = w[i__], dabs(r__1));
/* L20: */
    }
    claset_("Full", n, n, &c_b1, &c_b1, &z__[z_offset], ldz);
    mgstol = eps * 5.f;

    nsplit = iblock[*m];
    ibegin = 1;
    i__1 = nsplit;
    for (jblk = 1; jblk <= i__1; ++jblk) {
	iend = isplit[jblk];

/*        Find the eigenvectors of the submatrix indexed IBEGIN   
          through IEND. */

	if (ibegin == iend) {
	    i__2 = z___subscr(ibegin, ibegin);
	    z__[i__2].r = 1.f, z__[i__2].i = 0.f;
	    isuppz[(ibegin << 1) - 1] = ibegin;
	    isuppz[ibegin * 2] = ibegin;
	    ibegin = iend + 1;
	    goto L170;
	}
	oldien = ibegin - 1;
	in = iend - oldien;
	latime_1.ops += 1.f;
/* Computing MIN */
	r__1 = .01f, r__2 = 1.f / (real) in;
	reltol = dmin(r__1,r__2);
	im = in;
	scopy_(&im, &w[ibegin], &c__1, &work[1], &c__1);
	latime_1.ops += (real) (in - 1);
	i__2 = in - 1;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    work[indgap + i__] = work[i__ + 1] - work[i__];
/* L30: */
	}
/* Computing MAX */
	r__2 = (r__1 = work[in], dabs(r__1));
	work[indgap + in] = dmax(r__2,eps);
	ndone = 0;

	ndepth = 0;
	lsbdpt = 1;
	nclus = 1;
	iwork[iindc1 + 1] = 1;
	iwork[iindc1 + 2] = in;

/*        While( NDONE.LT.IM ) do */

L40:
	if (ndone < im) {
	    oldncl = nclus;
	    nclus = 0;
	    lsbdpt = 1 - lsbdpt;
	    i__2 = oldncl;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (lsbdpt == 0) {
		    oldcls = iindc1;
		    newcls = iindc2;
		} else {
		    oldcls = iindc2;
		    newcls = iindc1;
		}

/*              If NDEPTH > 1, retrieve the relatively robust   
                representation (RRR) and perform limited bisection   
                (if necessary) to get approximate eigenvalues. */

		j = oldcls + (i__ << 1);
		oldfst = iwork[j - 1];
		oldlst = iwork[j];
		if (ndepth > 0) {
		    j = oldien + oldfst;
		    i__3 = in;
		    for (k = 1; k <= i__3; ++k) {
			i__4 = z___subscr(ibegin + k - 1, oldien + oldfst);
			d__[ibegin + k - 1] = z__[i__4].r;
			i__4 = z___subscr(ibegin + k - 1, oldien + oldfst + 1)
				;
			l[ibegin + k - 1] = z__[i__4].r;
/* L45: */
		    }
		    sigma = l[iend];
		}
		k = ibegin;
		latime_1.ops += (real) (in - 1 << 1);
		i__3 = in - 1;
		for (j = 1; j <= i__3; ++j) {
		    work[indld + j] = d__[k] * l[k];
		    work[indlld + j] = work[indld + j] * l[k];
		    ++k;
/* L50: */
		}
		if (ndepth > 0) {
		    slarrb_(&in, &d__[ibegin], &l[ibegin], &work[indld + 1], &
			    work[indlld + 1], &oldfst, &oldlst, &sigma, &
			    reltol, &work[1], &work[indgap + 1], &work[inderr]
			    , &work[indwrk], &iwork[iindwk], &iinfo);
		    if (iinfo != 0) {
			*info = 1;
			return 0;
		    }
		}

/*              Classify eigenvalues of the current representation (RRR)   
                as (i) isolated, (ii) loosely clustered or (iii) tightly   
                clustered */

		newfrs = oldfst;
		i__3 = oldlst;
		for (j = oldfst; j <= i__3; ++j) {
		    latime_1.ops += 1.f;
		    if (j == oldlst || work[indgap + j] >= reltol * (r__1 = 
			    work[j], dabs(r__1))) {
			newlst = j;
		    } else {

/*                    continue (to the next loop) */

			latime_1.ops += 1.f;
			relgap = work[indgap + j] / (r__1 = work[j], dabs(
				r__1));
			if (j == newfrs) {
			    minrgp = relgap;
			} else {
			    minrgp = dmin(minrgp,relgap);
			}
			goto L140;
		    }
		    newsiz = newlst - newfrs + 1;
		    maxitr = 10;
		    newftt = oldien + newfrs;
		    if (newsiz > 1) {
			mgscls = newsiz <= 20 && minrgp >= mgstol;
			if (! mgscls) {
			    i__4 = in;
			    for (k = 1; k <= i__4; ++k) {
				i__5 = z___subscr(ibegin + k - 1, newftt);
				work[indin1 + k - 1] = z__[i__5].r;
				i__5 = z___subscr(ibegin + k - 1, newftt + 1);
				work[indin2 + k - 1] = z__[i__5].r;
/* L55: */
			    }
			    slarrf_(&in, &d__[ibegin], &l[ibegin], &work[
				    indld + 1], &work[indlld + 1], &newfrs, &
				    newlst, &work[1], &work[indin1], &work[
				    indin2], &work[indwrk], &iwork[iindwk], 
				    info);
			    if (*info == 0) {
				++nclus;
				k = newcls + (nclus << 1);
				iwork[k - 1] = newfrs;
				iwork[k] = newlst;
			    } else {
				*info = 0;
				if (minrgp >= mgstol) {
				    mgscls = TRUE_;
				} else {

/*                             Call CSTEIN to process this tight cluster.   
                               This happens only if MINRGP <= MGSTOL   
                               and SLARRF returns INFO = 1. The latter   
                               means that a new RRR to "break" the   
                               cluster could not be found. */

				    work[indwrk] = d__[ibegin];
				    latime_1.ops += (real) (in - 1);
				    i__4 = in - 1;
				    for (k = 1; k <= i__4; ++k) {
					work[indwrk + k] = d__[ibegin + k] + 
						work[indlld + k];
/* L60: */
				    }
				    i__4 = newsiz;
				    for (k = 1; k <= i__4; ++k) {
					iwork[iindwk + k - 1] = 1;
/* L70: */
				    }
				    i__4 = newlst;
				    for (k = newfrs; k <= i__4; ++k) {
					isuppz[(ibegin + k << 1) - 3] = 1;
					isuppz[(ibegin + k << 1) - 2] = in;
/* L80: */
				    }
				    temp[0] = in;
				    cstein_(&in, &work[indwrk], &work[indld + 
					    1], &newsiz, &work[newfrs], &
					    iwork[iindwk], temp, &z___ref(
					    ibegin, newftt), ldz, &work[
					    indwrk + in], &iwork[iindwk + in],
					     &iwork[iindwk + (in << 1)], &
					    iinfo);
				    if (iinfo != 0) {
					*info = 2;
					return 0;
				    }
				    ndone += newsiz;
				}
			    }
			}
		    } else {
			mgscls = FALSE_;
		    }
		    if (newsiz == 1 || mgscls) {
			ktot = newftt;
			i__4 = newlst;
			for (k = newfrs; k <= i__4; ++k) {
			    iter = 0;
L90:
			    lambda = work[k];
			    clar1v_(&in, &c__1, &in, &lambda, &d__[ibegin], &
				    l[ibegin], &work[indld + 1], &work[indlld 
				    + 1], &gersch[(oldien << 1) + 1], &
				    z___ref(ibegin, ktot), &ztz, &mingma, &
				    iwork[iindr + ktot], &isuppz[(ktot << 1) 
				    - 1], &work[indwrk]);
			    latime_1.ops += 4.f;
			    tmp1 = 1.f / ztz;
			    nrminv = sqrt(tmp1);
			    resid = dabs(mingma) * nrminv;
			    rqcorr = mingma * tmp1;
			    if (k == in) {
				gap = work[indgap + k - 1];
			    } else if (k == 1) {
				gap = work[indgap + k];
			    } else {
/* Computing MIN */
				r__1 = work[indgap + k - 1], r__2 = work[
					indgap + k];
				gap = dmin(r__1,r__2);
			    }
			    ++iter;
			    latime_1.ops += 3.f;
			    if (resid > *tol * gap && dabs(rqcorr) > eps * 
				    4.f * dabs(lambda)) {
				latime_1.ops += 1.f;
				work[k] = lambda + rqcorr;
				if (iter < maxitr) {
				    goto L90;
				}
			    }
			    iwork[ktot] = 1;
			    if (newsiz == 1) {
				++ndone;
			    }
			    latime_1.ops += (real) (in << 1);
			    csscal_(&in, &nrminv, &z___ref(ibegin, ktot), &
				    c__1);
			    ++ktot;
/* L100: */
			}
			if (newsiz > 1) {
			    itmp1 = isuppz[(newftt << 1) - 1];
			    itmp2 = isuppz[newftt * 2];
			    ktot = oldien + newlst;
			    i__4 = ktot;
			    for (p = newftt + 1; p <= i__4; ++p) {
				i__5 = p - 1;
				for (q = newftt; q <= i__5; ++q) {
				    latime_1.ops += (real) (in * 10);
				    cdotu_(&q__2, &in, &z___ref(ibegin, p), &
					    c__1, &z___ref(ibegin, q), &c__1);
				    q__1.r = -q__2.r, q__1.i = -q__2.i;
				    tmp1 = q__1.r;
				    q__1.r = tmp1, q__1.i = 0.f;
				    caxpy_(&in, &q__1, &z___ref(ibegin, q), &
					    c__1, &z___ref(ibegin, p), &c__1);
/* L110: */
				}
				latime_1.ops += (real) ((in << 3) + 1);
				tmp1 = 1.f / scnrm2_(&in, &z___ref(ibegin, p),
					 &c__1);
				csscal_(&in, &tmp1, &z___ref(ibegin, p), &
					c__1);
/* Computing MIN */
				i__5 = itmp1, i__6 = isuppz[(p << 1) - 1];
				itmp1 = min(i__5,i__6);
/* Computing MAX */
				i__5 = itmp2, i__6 = isuppz[p * 2];
				itmp2 = max(i__5,i__6);
/* L120: */
			    }
			    i__4 = ktot;
			    for (p = newftt; p <= i__4; ++p) {
				isuppz[(p << 1) - 1] = itmp1;
				isuppz[p * 2] = itmp2;
/* L130: */
			    }
			    ndone += newsiz;
			}
		    }
		    newfrs = j + 1;
L140:
		    ;
		}
/* L150: */
	    }
	    ++ndepth;
	    goto L40;
	}
	j = ibegin << 1;
	i__2 = iend;
	for (i__ = ibegin; i__ <= i__2; ++i__) {
	    isuppz[j - 1] += oldien;
	    isuppz[j] += oldien;
	    j += 2;
/* L160: */
	}
	ibegin = iend + 1;
L170:
	;
    }

    return 0;

/*     End of CLARRV */

} /* clarrv_ */

#undef z___ref
#undef z___subscr


