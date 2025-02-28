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

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int dlaein_(logical *rightv, logical *noinit, integer *n, 
	doublereal *h__, integer *ldh, doublereal *wr, doublereal *wi, 
	doublereal *vr, doublereal *vi, doublereal *b, integer *ldb, 
	doublereal *work, doublereal *eps3, doublereal *smlnum, doublereal *
	bignum, integer *info)
{
    /* System generated locals */
    integer b_dim1, b_offset, h_dim1, h_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3, d__4;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer ierr;
    static doublereal temp, norm, vmax, opst;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    static integer i__, j;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static doublereal scale, w, x, y;
    extern doublereal dasum_(integer *, doublereal *, integer *);
    static char trans[1];
    static doublereal vcrit;
    static integer i1, i2, i3;
    static doublereal rootn, vnorm, w1;
    extern doublereal dlapy2_(doublereal *, doublereal *);
    static doublereal ei, ej, absbii, absbjj, xi;
    extern integer idamax_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dladiv_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal xr;
    extern /* Subroutine */ int dlatrs_(char *, char *, char *, char *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *);
    static char normin[1];
    static doublereal nrmsml, growto, rec;
    static integer its;


#define b_ref(a_1,a_2) b[(a_2)*b_dim1 + a_1]
#define h___ref(a_1,a_2) h__[(a_2)*h_dim1 + a_1]


/*  -- LAPACK auxiliary routine (instrumented to count operations) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   

       Common block to return operation count.   

    Purpose   
    =======   

    DLAEIN uses inverse iteration to find a right or left eigenvector   
    corresponding to the eigenvalue (WR,WI) of a real upper Hessenberg   
    matrix H.   

    Arguments   
    =========   

    RIGHTV   (input) LOGICAL   
            = .TRUE. : compute right eigenvector;   
            = .FALSE.: compute left eigenvector.   

    NOINIT   (input) LOGICAL   
            = .TRUE. : no initial vector supplied in (VR,VI).   
            = .FALSE.: initial vector supplied in (VR,VI).   

    N       (input) INTEGER   
            The order of the matrix H.  N >= 0.   

    H       (input) DOUBLE PRECISION array, dimension (LDH,N)   
            The upper Hessenberg matrix H.   

    LDH     (input) INTEGER   
            The leading dimension of the array H.  LDH >= max(1,N).   

    WR      (input) DOUBLE PRECISION   
    WI      (input) DOUBLE PRECISION   
            The real and imaginary parts of the eigenvalue of H whose   
            corresponding right or left eigenvector is to be computed.   

    VR      (input/output) DOUBLE PRECISION array, dimension (N)   
    VI      (input/output) DOUBLE PRECISION array, dimension (N)   
            On entry, if NOINIT = .FALSE. and WI = 0.0, VR must contain   
            a real starting vector for inverse iteration using the real   
            eigenvalue WR; if NOINIT = .FALSE. and WI.ne.0.0, VR and VI   
            must contain the real and imaginary parts of a complex   
            starting vector for inverse iteration using the complex   
            eigenvalue (WR,WI); otherwise VR and VI need not be set.   
            On exit, if WI = 0.0 (real eigenvalue), VR contains the   
            computed real eigenvector; if WI.ne.0.0 (complex eigenvalue),   
            VR and VI contain the real and imaginary parts of the   
            computed complex eigenvector. The eigenvector is normalized   
            so that the component of largest magnitude has magnitude 1;   
            here the magnitude of a complex number (x,y) is taken to be   
            |x| + |y|.   
            VI is not referenced if WI = 0.0.   

    B       (workspace) DOUBLE PRECISION array, dimension (LDB,N)   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= N+1.   

    WORK   (workspace) DOUBLE PRECISION array, dimension (N)   

    EPS3    (input) DOUBLE PRECISION   
            A small machine-dependent value which is used to perturb   
            close eigenvalues, and to replace zero pivots.   

    SMLNUM  (input) DOUBLE PRECISION   
            A machine-dependent value close to the underflow threshold.   

    BIGNUM  (input) DOUBLE PRECISION   
            A machine-dependent value close to the overflow threshold.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            = 1:  inverse iteration did not converge; VR is set to the   
                  last iterate, and so is VI if WI.ne.0.0.   

    =====================================================================   


       Parameter adjustments */
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1 * 1;
    h__ -= h_offset;
    --vr;
    --vi;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    --work;

    /* Function Body */
    *info = 0;
/* **   
       Initialize */
    opst = 0.;
/* **   

       GROWTO is the threshold used in the acceptance test for an   
       eigenvector. */

    rootn = sqrt((doublereal) (*n));
    growto = .1 / rootn;
/* Computing MAX */
    d__1 = 1., d__2 = *eps3 * rootn;
    nrmsml = max(d__1,d__2) * *smlnum;
/* **   
          Increment op count for computing ROOTN, GROWTO and NRMSML */
    opst += 4;
/* **   

       Form B = H - (WR,WI)*I (except that the subdiagonal elements and   
       the imaginary parts of the diagonal elements are not stored). */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = j - 1;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    b_ref(i__, j) = h___ref(i__, j);
/* L10: */
	}
	b_ref(j, j) = h___ref(j, j) - *wr;
/* L20: */
    }
/* ** */
    opst += *n;
/* ** */

    if (*wi == 0.) {

/*        Real eigenvalue. */

	if (*noinit) {

/*           Set initial vector. */

	    i__1 = *n;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		vr[i__] = *eps3;
/* L30: */
	    }
	} else {

/*           Scale supplied initial vector. */

	    vnorm = dnrm2_(n, &vr[1], &c__1);
	    d__1 = *eps3 * rootn / max(vnorm,nrmsml);
	    dscal_(n, &d__1, &vr[1], &c__1);
/* ** */
	    opst += *n * 3 + 2;
/* ** */
	}

	if (*rightv) {

/*           LU decomposition with partial pivoting of B, replacing zero   
             pivots by EPS3. */

	    i__1 = *n - 1;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		ei = h___ref(i__ + 1, i__);
		if ((d__1 = b_ref(i__, i__), abs(d__1)) < abs(ei)) {

/*                 Interchange rows and eliminate. */

		    x = b_ref(i__, i__) / ei;
		    b_ref(i__, i__) = ei;
		    i__2 = *n;
		    for (j = i__ + 1; j <= i__2; ++j) {
			temp = b_ref(i__ + 1, j);
			b_ref(i__ + 1, j) = b_ref(i__, j) - x * temp;
			b_ref(i__, j) = temp;
/* L40: */
		    }
		} else {

/*                 Eliminate without interchange. */

		    if (b_ref(i__, i__) == 0.) {
			b_ref(i__, i__) = *eps3;
		    }
		    x = ei / b_ref(i__, i__);
		    if (x != 0.) {
			i__2 = *n;
			for (j = i__ + 1; j <= i__2; ++j) {
			    b_ref(i__ + 1, j) = b_ref(i__ + 1, j) - x * b_ref(
				    i__, j);
/* L50: */
			}
		    }
		}
/* L60: */
	    }
	    if (b_ref(*n, *n) == 0.) {
		b_ref(*n, *n) = *eps3;
	    }
/* **   
             Increment op count for LU decomposition */
	    latime_1.ops += (*n - 1) * (*n + 1);
/* ** */

	    *(unsigned char *)trans = 'N';

	} else {

/*           UL decomposition with partial pivoting of B, replacing zero   
             pivots by EPS3. */

	    for (j = *n; j >= 2; --j) {
		ej = h___ref(j, j - 1);
		if ((d__1 = b_ref(j, j), abs(d__1)) < abs(ej)) {

/*                 Interchange columns and eliminate. */

		    x = b_ref(j, j) / ej;
		    b_ref(j, j) = ej;
		    i__1 = j - 1;
		    for (i__ = 1; i__ <= i__1; ++i__) {
			temp = b_ref(i__, j - 1);
			b_ref(i__, j - 1) = b_ref(i__, j) - x * temp;
			b_ref(i__, j) = temp;
/* L70: */
		    }
		} else {

/*                 Eliminate without interchange. */

		    if (b_ref(j, j) == 0.) {
			b_ref(j, j) = *eps3;
		    }
		    x = ej / b_ref(j, j);
		    if (x != 0.) {
			i__1 = j - 1;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b_ref(i__, j - 1) = b_ref(i__, j - 1) - x * b_ref(
				    i__, j);
/* L80: */
			}
		    }
		}
/* L90: */
	    }
	    if (b_ref(1, 1) == 0.) {
		b_ref(1, 1) = *eps3;
	    }
/* **   
             Increment op count for UL decomposition */
	    latime_1.ops += (*n - 1) * (*n + 1);
/* ** */

	    *(unsigned char *)trans = 'T';

	}

	*(unsigned char *)normin = 'N';
	i__1 = *n;
	for (its = 1; its <= i__1; ++its) {

/*           Solve U*x = scale*v for a right eigenvector   
               or U'*x = scale*v for a left eigenvector,   
             overwriting x on v. */

	    dlatrs_("Upper", trans, "Nonunit", normin, n, &b[b_offset], ldb, &
		    vr[1], &scale, &work[1], &ierr);
/* **   
             Increment opcount for triangular solver, assuming that   
             ops DLATRS = ops DTRSV, with no scaling in DLATRS. */
	    latime_1.ops += *n * *n;
/* ** */
	    *(unsigned char *)normin = 'Y';

/*           Test for sufficient growth in the norm of v. */

	    vnorm = dasum_(n, &vr[1], &c__1);
/* ** */
	    opst += *n;
/* ** */
	    if (vnorm >= growto * scale) {
		goto L120;
	    }

/*           Choose new orthogonal starting vector and try again. */

	    temp = *eps3 / (rootn + 1.);
	    vr[1] = *eps3;
	    i__2 = *n;
	    for (i__ = 2; i__ <= i__2; ++i__) {
		vr[i__] = temp;
/* L100: */
	    }
	    vr[*n - its + 1] -= *eps3 * rootn;
/* ** */
	    opst += 4;
/* **   
   L110: */
	}

/*        Failure to find eigenvector in N iterations. */

	*info = 1;

L120:

/*        Normalize eigenvector. */

	i__ = idamax_(n, &vr[1], &c__1);
	d__2 = 1. / (d__1 = vr[i__], abs(d__1));
	dscal_(n, &d__2, &vr[1], &c__1);
/* ** */
	opst += (*n << 1) + 1;
/* ** */
    } else {

/*        Complex eigenvalue. */

	if (*noinit) {

/*           Set initial vector. */

	    i__1 = *n;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		vr[i__] = *eps3;
		vi[i__] = 0.;
/* L130: */
	    }
	} else {

/*           Scale supplied initial vector. */

	    d__1 = dnrm2_(n, &vr[1], &c__1);
	    d__2 = dnrm2_(n, &vi[1], &c__1);
	    norm = dlapy2_(&d__1, &d__2);
	    rec = *eps3 * rootn / max(norm,nrmsml);
	    dscal_(n, &rec, &vr[1], &c__1);
	    dscal_(n, &rec, &vi[1], &c__1);
/* ** */
	    opst += *n * 6 + 5;
/* ** */
	}

	if (*rightv) {

/*           LU decomposition with partial pivoting of B, replacing zero   
             pivots by EPS3.   

             The imaginary part of the (i,j)-th element of U is stored in   
             B(j+1,i). */

	    b_ref(2, 1) = -(*wi);
	    i__1 = *n;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		b_ref(i__ + 1, 1) = 0.;
/* L140: */
	    }

	    i__1 = *n - 1;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		absbii = dlapy2_(&b_ref(i__, i__), &b_ref(i__ + 1, i__));
		ei = h___ref(i__ + 1, i__);
		if (absbii < abs(ei)) {

/*                 Interchange rows and eliminate. */

		    xr = b_ref(i__, i__) / ei;
		    xi = b_ref(i__ + 1, i__) / ei;
		    b_ref(i__, i__) = ei;
		    b_ref(i__ + 1, i__) = 0.;
		    i__2 = *n;
		    for (j = i__ + 1; j <= i__2; ++j) {
			temp = b_ref(i__ + 1, j);
			b_ref(i__ + 1, j) = b_ref(i__, j) - xr * temp;
			b_ref(j + 1, i__ + 1) = b_ref(j + 1, i__) - xi * temp;
			b_ref(i__, j) = temp;
			b_ref(j + 1, i__) = 0.;
/* L150: */
		    }
		    b_ref(i__ + 2, i__) = -(*wi);
		    b_ref(i__ + 1, i__ + 1) = b_ref(i__ + 1, i__ + 1) - xi * *
			    wi;
		    b_ref(i__ + 2, i__ + 1) = b_ref(i__ + 2, i__ + 1) + xr * *
			    wi;
/* ** */
		    opst += (*n - i__ << 2) + 6;
/* ** */
		} else {

/*                 Eliminate without interchanging rows. */

		    if (absbii == 0.) {
			b_ref(i__, i__) = *eps3;
			b_ref(i__ + 1, i__) = 0.;
			absbii = *eps3;
		    }
		    ei = ei / absbii / absbii;
		    xr = b_ref(i__, i__) * ei;
		    xi = -b_ref(i__ + 1, i__) * ei;
		    i__2 = *n;
		    for (j = i__ + 1; j <= i__2; ++j) {
			b_ref(i__ + 1, j) = b_ref(i__ + 1, j) - xr * b_ref(
				i__, j) + xi * b_ref(j + 1, i__);
			b_ref(j + 1, i__ + 1) = -xr * b_ref(j + 1, i__) - xi *
				 b_ref(i__, j);
/* L160: */
		    }
		    b_ref(i__ + 2, i__ + 1) = b_ref(i__ + 2, i__ + 1) - *wi;
/* ** */
		    opst += (*n - i__) * 7 + 4;
/* ** */
		}

/*              Compute 1-norm of offdiagonal elements of i-th row. */

		i__2 = *n - i__;
		i__3 = *n - i__;
		work[i__] = dasum_(&i__2, &b_ref(i__, i__ + 1), ldb) + dasum_(
			&i__3, &b_ref(i__ + 2, i__), &c__1);
/* ** */
		opst += (*n - i__ << 1) + 4;
/* **   
   L170: */
	    }
	    if (b_ref(*n, *n) == 0. && b_ref(*n + 1, *n) == 0.) {
		b_ref(*n, *n) = *eps3;
	    }
	    work[*n] = 0.;

	    i1 = *n;
	    i2 = 1;
	    i3 = -1;
	} else {

/*           UL decomposition with partial pivoting of conjg(B),   
             replacing zero pivots by EPS3.   

             The imaginary part of the (i,j)-th element of U is stored in   
             B(j+1,i). */

	    b_ref(*n + 1, *n) = *wi;
	    i__1 = *n - 1;
	    for (j = 1; j <= i__1; ++j) {
		b_ref(*n + 1, j) = 0.;
/* L180: */
	    }

	    for (j = *n; j >= 2; --j) {
		ej = h___ref(j, j - 1);
		absbjj = dlapy2_(&b_ref(j, j), &b_ref(j + 1, j));
		if (absbjj < abs(ej)) {

/*                 Interchange columns and eliminate */

		    xr = b_ref(j, j) / ej;
		    xi = b_ref(j + 1, j) / ej;
		    b_ref(j, j) = ej;
		    b_ref(j + 1, j) = 0.;
		    i__1 = j - 1;
		    for (i__ = 1; i__ <= i__1; ++i__) {
			temp = b_ref(i__, j - 1);
			b_ref(i__, j - 1) = b_ref(i__, j) - xr * temp;
			b_ref(j, i__) = b_ref(j + 1, i__) - xi * temp;
			b_ref(i__, j) = temp;
			b_ref(j + 1, i__) = 0.;
/* L190: */
		    }
		    b_ref(j + 1, j - 1) = *wi;
		    b_ref(j - 1, j - 1) = b_ref(j - 1, j - 1) + xi * *wi;
		    b_ref(j, j - 1) = b_ref(j, j - 1) - xr * *wi;
/* ** */
		    opst += (j - 1 << 2) + 6;
/* ** */
		} else {

/*                 Eliminate without interchange. */

		    if (absbjj == 0.) {
			b_ref(j, j) = *eps3;
			b_ref(j + 1, j) = 0.;
			absbjj = *eps3;
		    }
		    ej = ej / absbjj / absbjj;
		    xr = b_ref(j, j) * ej;
		    xi = -b_ref(j + 1, j) * ej;
		    i__1 = j - 1;
		    for (i__ = 1; i__ <= i__1; ++i__) {
			b_ref(i__, j - 1) = b_ref(i__, j - 1) - xr * b_ref(
				i__, j) + xi * b_ref(j + 1, i__);
			b_ref(j, i__) = -xr * b_ref(j + 1, i__) - xi * b_ref(
				i__, j);
/* L200: */
		    }
		    b_ref(j, j - 1) = b_ref(j, j - 1) + *wi;
/* ** */
		    opst += (j - 1) * 7 + 4;
/* ** */
		}

/*              Compute 1-norm of offdiagonal elements of j-th column. */

		i__1 = j - 1;
		i__2 = j - 1;
		work[j] = dasum_(&i__1, &b_ref(1, j), &c__1) + dasum_(&i__2, &
			b_ref(j + 1, 1), ldb);
/* ** */
		opst += (j - 1 << 1) + 4;
/* **   
   L210: */
	    }
	    if (b_ref(1, 1) == 0. && b_ref(2, 1) == 0.) {
		b_ref(1, 1) = *eps3;
	    }
	    work[1] = 0.;

	    i1 = 1;
	    i2 = *n;
	    i3 = 1;
	}

	i__1 = *n;
	for (its = 1; its <= i__1; ++its) {
	    scale = 1.;
	    vmax = 1.;
	    vcrit = *bignum;

/*           Solve U*(xr,xi) = scale*(vr,vi) for a right eigenvector,   
               or U'*(xr,xi) = scale*(vr,vi) for a left eigenvector,   
             overwriting (xr,xi) on (vr,vi). */

	    i__2 = i2;
	    i__3 = i3;
	    for (i__ = i1; i__3 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__3) 
		    {

		if (work[i__] > vcrit) {
		    rec = 1. / vmax;
		    dscal_(n, &rec, &vr[1], &c__1);
		    dscal_(n, &rec, &vi[1], &c__1);
		    scale *= rec;
		    vmax = 1.;
		    vcrit = *bignum;
		}

		xr = vr[i__];
		xi = vi[i__];
		if (*rightv) {
		    i__4 = *n;
		    for (j = i__ + 1; j <= i__4; ++j) {
			xr = xr - b_ref(i__, j) * vr[j] + b_ref(j + 1, i__) * 
				vi[j];
			xi = xi - b_ref(i__, j) * vi[j] - b_ref(j + 1, i__) * 
				vr[j];
/* L220: */
		    }
		} else {
		    i__4 = i__ - 1;
		    for (j = 1; j <= i__4; ++j) {
			xr = xr - b_ref(j, i__) * vr[j] + b_ref(i__ + 1, j) * 
				vi[j];
			xi = xi - b_ref(j, i__) * vi[j] - b_ref(i__ + 1, j) * 
				vr[j];
/* L230: */
		    }
		}

		w = (d__1 = b_ref(i__, i__), abs(d__1)) + (d__2 = b_ref(i__ + 
			1, i__), abs(d__2));
		if (w > *smlnum) {
		    if (w < 1.) {
			w1 = abs(xr) + abs(xi);
			if (w1 > w * *bignum) {
			    rec = 1. / w1;
			    dscal_(n, &rec, &vr[1], &c__1);
			    dscal_(n, &rec, &vi[1], &c__1);
			    xr = vr[i__];
			    xi = vi[i__];
			    scale *= rec;
			    vmax *= rec;
			}
		    }

/*                 Divide by diagonal element of B. */

		    dladiv_(&xr, &xi, &b_ref(i__, i__), &b_ref(i__ + 1, i__), 
			    &vr[i__], &vi[i__]);
/* Computing MAX */
		    d__3 = (d__1 = vr[i__], abs(d__1)) + (d__2 = vi[i__], abs(
			    d__2));
		    vmax = max(d__3,vmax);
		    vcrit = *bignum / vmax;
/* ** */
		    opst += 9;
/* ** */
		} else {
		    i__4 = *n;
		    for (j = 1; j <= i__4; ++j) {
			vr[j] = 0.;
			vi[j] = 0.;
/* L240: */
		    }
		    vr[i__] = 1.;
		    vi[i__] = 1.;
		    scale = 0.;
		    vmax = 1.;
		    vcrit = *bignum;
		}
/* L250: */
	    }
/* **   
             Increment op count for loop 260, assuming no scaling */
	    latime_1.ops += (*n << 2) * (*n - 1);
/* **   

             Test for sufficient growth in the norm of (VR,VI). */

	    vnorm = dasum_(n, &vr[1], &c__1) + dasum_(n, &vi[1], &c__1);
/* ** */
	    opst += *n << 1;
/* ** */
	    if (vnorm >= growto * scale) {
		goto L280;
	    }

/*           Choose a new orthogonal starting vector and try again. */

	    y = *eps3 / (rootn + 1.);
	    vr[1] = *eps3;
	    vi[1] = 0.;

	    i__3 = *n;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		vr[i__] = y;
		vi[i__] = 0.;
/* L260: */
	    }
	    vr[*n - its + 1] -= *eps3 * rootn;
/* ** */
	    opst += 4;
/* **   
   L270: */
	}

/*        Failure to find eigenvector in N iterations */

	*info = 1;

L280:

/*        Normalize eigenvector. */

	vnorm = 0.;
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	    d__3 = vnorm, d__4 = (d__1 = vr[i__], abs(d__1)) + (d__2 = vi[i__]
		    , abs(d__2));
	    vnorm = max(d__3,d__4);
/* L290: */
	}
	d__1 = 1. / vnorm;
	dscal_(n, &d__1, &vr[1], &c__1);
	d__1 = 1. / vnorm;
	dscal_(n, &d__1, &vi[1], &c__1);
/* ** */
	opst += (*n << 2) + 1;
/* ** */

    }

/* **   
       Compute final op count */
    latime_1.ops += opst;
/* ** */
    return 0;

/*     End of DLAEIN */

} /* dlaein_ */

#undef h___ref
#undef b_ref


