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
static complex c_b2 = {1.f,0.f};
static integer c__1 = 1;
static integer c__4 = 4;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__8 = 8;
static integer c__15 = 15;
static logical c_false = FALSE_;

/* Subroutine */ int chseqr_(char *job, char *compz, integer *n, integer *ilo,
	 integer *ihi, complex *h__, integer *ldh, complex *w, complex *z__, 
	integer *ldz, complex *work, integer *lwork, integer *info)
{
    /* System generated locals */
    address a__1[2];
    integer h_dim1, h_offset, z_dim1, z_offset, i__1, i__2, i__3, i__4[2], 
	    i__5, i__6;
    real r__1, r__2, r__3, r__4;
    complex q__1;
    char ch__1[2];

    /* Builtin functions */
    double r_imag(complex *);
    void r_cnjg(complex *, complex *);
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    static integer maxb, ierr;
    static real unfl;
    static complex temp;
    static real ovfl, opst;
    static integer i__, j, k, l;
    static complex s[225]	/* was [15][15] */;
    extern /* Subroutine */ int cscal_(integer *, complex *, complex *, 
	    integer *);
    static complex v[16];
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int cgemv_(char *, integer *, integer *, complex *
	    , complex *, integer *, complex *, integer *, complex *, complex *
	    , integer *), ccopy_(integer *, complex *, integer *, 
	    complex *, integer *);
    static integer itemp;
    static real rtemp;
    static integer i1, i2;
    static logical initz, wantt, wantz;
    static real rwork[1];
    extern doublereal slapy2_(real *, real *);
    static integer ii, nh;
    extern /* Subroutine */ int slabad_(real *, real *), clarfg_(integer *, 
	    complex *, complex *, integer *, complex *);
    static integer nr, ns;
    extern integer icamax_(integer *, complex *, integer *);
    static integer nv;
    extern doublereal slamch_(char *), clanhs_(char *, integer *, 
	    complex *, integer *, real *);
    extern /* Subroutine */ int csscal_(integer *, real *, complex *, integer 
	    *), clahqr_(logical *, logical *, integer *, integer *, integer *,
	     complex *, integer *, complex *, integer *, integer *, complex *,
	     integer *, integer *), clacpy_(char *, integer *, integer *, 
	    complex *, integer *, complex *, integer *);
    static complex vv[16];
    extern /* Subroutine */ int claset_(char *, integer *, integer *, complex 
	    *, complex *, complex *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int clarfx_(char *, integer *, integer *, complex 
	    *, complex *, complex *, integer *, complex *), xerbla_(
	    char *, integer *);
    static real smlnum;
    static logical lquery;
    static integer itn;
    static complex tau;
    static integer its;
    static real ulp, tst1;


#define h___subscr(a_1,a_2) (a_2)*h_dim1 + a_1
#define h___ref(a_1,a_2) h__[h___subscr(a_1,a_2)]
#define s_subscr(a_1,a_2) (a_2)*15 + a_1 - 16
#define s_ref(a_1,a_2) s[s_subscr(a_1,a_2)]
#define z___subscr(a_1,a_2) (a_2)*z_dim1 + a_1
#define z___ref(a_1,a_2) z__[z___subscr(a_1,a_2)]


/*  -- LAPACK routine (instrumented to count operations, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   

       Common block to return operation count.   

    Purpose   
    =======   

    CHSEQR computes the eigenvalues of a complex upper Hessenberg   
    matrix H, and, optionally, the matrices T and Z from the Schur   
    decomposition H = Z T Z**H, where T is an upper triangular matrix   
    (the Schur form), and Z is the unitary matrix of Schur vectors.   

    Optionally Z may be postmultiplied into an input unitary matrix Q,   
    so that this routine can give the Schur factorization of a matrix A   
    which has been reduced to the Hessenberg form H by the unitary   
    matrix Q:  A = Q*H*Q**H = (QZ)*T*(QZ)**H.   

    Arguments   
    =========   

    JOB     (input) CHARACTER*1   
            = 'E': compute eigenvalues only;   
            = 'S': compute eigenvalues and the Schur form T.   

    COMPZ   (input) CHARACTER*1   
            = 'N': no Schur vectors are computed;   
            = 'I': Z is initialized to the unit matrix and the matrix Z   
                   of Schur vectors of H is returned;   
            = 'V': Z must contain an unitary matrix Q on entry, and   
                   the product Q*Z is returned.   

    N       (input) INTEGER   
            The order of the matrix H.  N >= 0.   

    ILO     (input) INTEGER   
    IHI     (input) INTEGER   
            It is assumed that H is already upper triangular in rows   
            and columns 1:ILO-1 and IHI+1:N. ILO and IHI are normally   
            set by a previous call to CGEBAL, and then passed to CGEHRD   
            when the matrix output by CGEBAL is reduced to Hessenberg   
            form. Otherwise ILO and IHI should be set to 1 and N   
            respectively.   
            1 <= ILO <= IHI <= N, if N > 0; ILO=1 and IHI=0, if N=0.   

    H       (input/output) COMPLEX array, dimension (LDH,N)   
            On entry, the upper Hessenberg matrix H.   
            On exit, if JOB = 'S', H contains the upper triangular matrix   
            T from the Schur decomposition (the Schur form). If   
            JOB = 'E', the contents of H are unspecified on exit.   

    LDH     (input) INTEGER   
            The leading dimension of the array H. LDH >= max(1,N).   

    W       (output) COMPLEX array, dimension (N)   
            The computed eigenvalues. If JOB = 'S', the eigenvalues are   
            stored in the same order as on the diagonal of the Schur form   
            returned in H, with W(i) = H(i,i).   

    Z       (input/output) COMPLEX array, dimension (LDZ,N)   
            If COMPZ = 'N': Z is not referenced.   
            If COMPZ = 'I': on entry, Z need not be set, and on exit, Z   
            contains the unitary matrix Z of the Schur vectors of H.   
            If COMPZ = 'V': on entry Z must contain an N-by-N matrix Q,   
            which is assumed to be equal to the unit matrix except for   
            the submatrix Z(ILO:IHI,ILO:IHI); on exit Z contains Q*Z.   
            Normally Q is the unitary matrix generated by CUNGHR after   
            the call to CGEHRD which formed the Hessenberg matrix H.   

    LDZ     (input) INTEGER   
            The leading dimension of the array Z.   
            LDZ >= max(1,N) if COMPZ = 'I' or 'V'; LDZ >= 1 otherwise.   

    WORK    (workspace/output) COMPLEX array, dimension (LWORK)   
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.  LWORK >= max(1,N).   

            If LWORK = -1, then a workspace query is assumed; the routine   
            only calculates the optimal size of the WORK array, returns   
            this value as the first entry of the WORK array, and no error   
            message related to LWORK is issued by XERBLA.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   
            > 0:  if INFO = i, CHSEQR failed to compute all the   
                  eigenvalues in a total of 30*(IHI-ILO+1) iterations;   
                  elements 1:ilo-1 and i+1:n of W contain those   
                  eigenvalues which have been successfully computed.   

    =====================================================================   


       Decode and test the input parameters   

       Parameter adjustments */
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1 * 1;
    h__ -= h_offset;
    --w;
    z_dim1 = *ldz;
    z_offset = 1 + z_dim1 * 1;
    z__ -= z_offset;
    --work;

    /* Function Body */
    wantt = lsame_(job, "S");
    initz = lsame_(compz, "I");
    wantz = initz || lsame_(compz, "V");

    *info = 0;
    i__1 = max(1,*n);
    work[1].r = (real) i__1, work[1].i = 0.f;
    lquery = *lwork == -1;
    if (! lsame_(job, "E") && ! wantt) {
	*info = -1;
    } else if (! lsame_(compz, "N") && ! wantz) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*ilo < 1 || *ilo > max(1,*n)) {
	*info = -4;
    } else if (*ihi < min(*ilo,*n) || *ihi > *n) {
	*info = -5;
    } else if (*ldh < max(1,*n)) {
	*info = -7;
    } else if (*ldz < 1 || wantz && *ldz < max(1,*n)) {
	*info = -10;
    } else if (*lwork < max(1,*n) && ! lquery) {
	*info = -12;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CHSEQR", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }
/* **   
       Initialize */
    opst = 0.f;
/* **   

       Initialize Z, if necessary */

    if (initz) {
	claset_("Full", n, n, &c_b1, &c_b2, &z__[z_offset], ldz);
    }

/*     Store the eigenvalues isolated by CGEBAL. */

    i__1 = *ilo - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	i__3 = h___subscr(i__, i__);
	w[i__2].r = h__[i__3].r, w[i__2].i = h__[i__3].i;
/* L10: */
    }
    i__1 = *n;
    for (i__ = *ihi + 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	i__3 = h___subscr(i__, i__);
	w[i__2].r = h__[i__3].r, w[i__2].i = h__[i__3].i;
/* L20: */
    }

/*     Quick return if possible. */

    if (*n == 0) {
	return 0;
    }
    if (*ilo == *ihi) {
	i__1 = *ilo;
	i__2 = h___subscr(*ilo, *ilo);
	w[i__1].r = h__[i__2].r, w[i__1].i = h__[i__2].i;
	return 0;
    }

/*     Set rows and columns ILO to IHI to zero below the first   
       subdiagonal. */

    i__1 = *ihi - 2;
    for (j = *ilo; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = j + 2; i__ <= i__2; ++i__) {
	    i__3 = h___subscr(i__, j);
	    h__[i__3].r = 0.f, h__[i__3].i = 0.f;
/* L30: */
	}
/* L40: */
    }
    nh = *ihi - *ilo + 1;

/*     I1 and I2 are the indices of the first row and last column of H   
       to which transformations must be applied. If eigenvalues only are   
       being computed, I1 and I2 are re-set inside the main loop. */

    if (wantt) {
	i1 = 1;
	i2 = *n;
    } else {
	i1 = *ilo;
	i2 = *ihi;
    }

/*     Ensure that the subdiagonal elements are real. */

    i__1 = *ihi;
    for (i__ = *ilo + 1; i__ <= i__1; ++i__) {
	i__2 = h___subscr(i__, i__ - 1);
	temp.r = h__[i__2].r, temp.i = h__[i__2].i;
	if (r_imag(&temp) != 0.f) {
	    r__1 = temp.r;
	    r__2 = r_imag(&temp);
	    rtemp = slapy2_(&r__1, &r__2);
	    i__2 = h___subscr(i__, i__ - 1);
	    h__[i__2].r = rtemp, h__[i__2].i = 0.f;
	    q__1.r = temp.r / rtemp, q__1.i = temp.i / rtemp;
	    temp.r = q__1.r, temp.i = q__1.i;
	    if (i2 > i__) {
		i__2 = i2 - i__;
		r_cnjg(&q__1, &temp);
		cscal_(&i__2, &q__1, &h___ref(i__, i__ + 1), ldh);
	    }
	    i__2 = i__ - i1;
	    cscal_(&i__2, &temp, &h___ref(i1, i__), &c__1);
	    if (i__ < *ihi) {
		i__2 = h___subscr(i__ + 1, i__);
		i__3 = h___subscr(i__ + 1, i__);
		q__1.r = temp.r * h__[i__3].r - temp.i * h__[i__3].i, q__1.i =
			 temp.r * h__[i__3].i + temp.i * h__[i__3].r;
		h__[i__2].r = q__1.r, h__[i__2].i = q__1.i;
	    }
/* **   
             Increment op count */
	    opst += (i2 - i1 + 2) * 6;
/* ** */
	    if (wantz) {
		cscal_(&nh, &temp, &z___ref(*ilo, i__), &c__1);
/* **   
                Increment op count */
		opst += nh * 6;
/* ** */
	    }
	}
/* L50: */
    }

/*     Determine the order of the multi-shift QR algorithm to be used.   

   Writing concatenation */
    i__4[0] = 1, a__1[0] = job;
    i__4[1] = 1, a__1[1] = compz;
    s_cat(ch__1, a__1, i__4, &c__2, (ftnlen)2);
    ns = ilaenv_(&c__4, "CHSEQR", ch__1, n, ilo, ihi, &c_n1, (ftnlen)6, (
	    ftnlen)2);
/* Writing concatenation */
    i__4[0] = 1, a__1[0] = job;
    i__4[1] = 1, a__1[1] = compz;
    s_cat(ch__1, a__1, i__4, &c__2, (ftnlen)2);
    maxb = ilaenv_(&c__8, "CHSEQR", ch__1, n, ilo, ihi, &c_n1, (ftnlen)6, (
	    ftnlen)2);
    if (ns <= 1 || ns > nh || maxb >= nh) {

/*        Use the standard double-shift algorithm */

	clahqr_(&wantt, &wantz, n, ilo, ihi, &h__[h_offset], ldh, &w[1], ilo, 
		ihi, &z__[z_offset], ldz, info);
	return 0;
    }
    maxb = max(2,maxb);
/* Computing MIN */
    i__1 = min(ns,maxb);
    ns = min(i__1,15);

/*     Now 1 < NS <= MAXB < NH.   

       Set machine-dependent constants for the stopping criterion.   
       If norm(H) <= sqrt(OVFL), overflow should not occur. */

    unfl = slamch_("Safe minimum");
    ovfl = 1.f / unfl;
    slabad_(&unfl, &ovfl);
    ulp = slamch_("Precision");
    smlnum = unfl * (nh / ulp);

/*     ITN is the total number of multiple-shift QR iterations allowed. */

    itn = nh * 30;

/*     The main loop begins here. I is the loop index and decreases from   
       IHI to ILO in steps of at most MAXB. Each iteration of the loop   
       works with the active submatrix in rows and columns L to I.   
       Eigenvalues I+1 to IHI have already converged. Either L = ILO, or   
       H(L,L-1) is negligible so that the matrix splits. */

    i__ = *ihi;
L60:
    if (i__ < *ilo) {
	goto L180;
    }

/*     Perform multiple-shift QR iterations on rows and columns ILO to I   
       until a submatrix of order at most MAXB splits off at the bottom   
       because a subdiagonal element has become negligible. */

    l = *ilo;
    i__1 = itn;
    for (its = 0; its <= i__1; ++its) {

/*        Look for a single small subdiagonal element. */

	i__2 = l + 1;
	for (k = i__; k >= i__2; --k) {
	    i__3 = h___subscr(k - 1, k - 1);
	    i__5 = h___subscr(k, k);
	    tst1 = (r__1 = h__[i__3].r, dabs(r__1)) + (r__2 = r_imag(&h___ref(
		    k - 1, k - 1)), dabs(r__2)) + ((r__3 = h__[i__5].r, dabs(
		    r__3)) + (r__4 = r_imag(&h___ref(k, k)), dabs(r__4)));
	    if (tst1 == 0.f) {
		i__3 = i__ - l + 1;
		tst1 = clanhs_("1", &i__3, &h___ref(l, l), ldh, rwork);
/* **   
                Increment op count */
		latime_1.ops += (i__ - l + 1) * 5 * (i__ - l) / 2;
/* ** */
	    }
	    i__3 = h___subscr(k, k - 1);
/* Computing MAX */
	    r__2 = ulp * tst1;
	    if ((r__1 = h__[i__3].r, dabs(r__1)) <= dmax(r__2,smlnum)) {
		goto L80;
	    }
/* L70: */
	}
L80:
	l = k;
/* **   
          Increment op count */
	opst += (i__ - l + 1) * 5;
/* ** */
	if (l > *ilo) {

/*           H(L,L-1) is negligible. */

	    i__2 = h___subscr(l, l - 1);
	    h__[i__2].r = 0.f, h__[i__2].i = 0.f;
	}

/*        Exit from loop if a submatrix of order <= MAXB has split off. */

	if (l >= i__ - maxb + 1) {
	    goto L170;
	}

/*        Now the active submatrix is in rows and columns L to I. If   
          eigenvalues only are being computed, only the active submatrix   
          need be transformed. */

	if (! wantt) {
	    i1 = l;
	    i2 = i__;
	}

	if (its == 20 || its == 30) {

/*           Exceptional shifts. */

	    i__2 = i__;
	    for (ii = i__ - ns + 1; ii <= i__2; ++ii) {
		i__3 = ii;
		i__5 = h___subscr(ii, ii - 1);
		i__6 = h___subscr(ii, ii);
		r__3 = ((r__1 = h__[i__5].r, dabs(r__1)) + (r__2 = h__[i__6]
			.r, dabs(r__2))) * 1.5f;
		w[i__3].r = r__3, w[i__3].i = 0.f;
/* L90: */
	    }
/* **   
             Increment op count */
	    opst += ns << 1;
/* ** */
	} else {

/*           Use eigenvalues of trailing submatrix of order NS as shifts. */

	    clacpy_("Full", &ns, &ns, &h___ref(i__ - ns + 1, i__ - ns + 1), 
		    ldh, s, &c__15);
	    clahqr_(&c_false, &c_false, &ns, &c__1, &ns, s, &c__15, &w[i__ - 
		    ns + 1], &c__1, &ns, &z__[z_offset], ldz, &ierr);
	    if (ierr > 0) {

/*              If CLAHQR failed to compute all NS eigenvalues, use the   
                unconverged diagonal elements as the remaining shifts. */

		i__2 = ierr;
		for (ii = 1; ii <= i__2; ++ii) {
		    i__3 = i__ - ns + ii;
		    i__5 = s_subscr(ii, ii);
		    w[i__3].r = s[i__5].r, w[i__3].i = s[i__5].i;
/* L100: */
		}
	    }
	}

/*        Form the first column of (G-w(1)) (G-w(2)) . . . (G-w(ns))   
          where G is the Hessenberg submatrix H(L:I,L:I) and w is   
          the vector of shifts (stored in W). The result is   
          stored in the local array V. */

	v[0].r = 1.f, v[0].i = 0.f;
	i__2 = ns + 1;
	for (ii = 2; ii <= i__2; ++ii) {
	    i__3 = ii - 1;
	    v[i__3].r = 0.f, v[i__3].i = 0.f;
/* L110: */
	}
	nv = 1;
	i__2 = i__;
	for (j = i__ - ns + 1; j <= i__2; ++j) {
	    i__3 = nv + 1;
	    ccopy_(&i__3, v, &c__1, vv, &c__1);
	    i__3 = nv + 1;
	    i__5 = j;
	    q__1.r = -w[i__5].r, q__1.i = -w[i__5].i;
	    cgemv_("No transpose", &i__3, &nv, &c_b2, &h___ref(l, l), ldh, vv,
		     &c__1, &q__1, v, &c__1);
	    ++nv;
/* **   
             Increment op count */
	    opst = opst + (nv << 3) * (*n + 1) + (nv + 1) * 6;
/* **   

             Scale V(1:NV) so that max(abs(V(i))) = 1. If V is zero,   
             reset it to the unit vector. */

	    itemp = icamax_(&nv, v, &c__1);
/* **   
             Increment op count */
	    opst += nv << 1;
/* ** */
	    i__3 = itemp - 1;
	    rtemp = (r__1 = v[i__3].r, dabs(r__1)) + (r__2 = r_imag(&v[itemp 
		    - 1]), dabs(r__2));
	    if (rtemp == 0.f) {
		v[0].r = 1.f, v[0].i = 0.f;
		i__3 = nv;
		for (ii = 2; ii <= i__3; ++ii) {
		    i__5 = ii - 1;
		    v[i__5].r = 0.f, v[i__5].i = 0.f;
/* L120: */
		}
	    } else {
		rtemp = dmax(rtemp,smlnum);
		r__1 = 1.f / rtemp;
		csscal_(&nv, &r__1, v, &c__1);
/* **   
                Increment op count */
		opst += nv << 1;
/* ** */
	    }
/* L130: */
	}

/*        Multiple-shift QR step */

	i__2 = i__ - 1;
	for (k = l; k <= i__2; ++k) {

/*           The first iteration of this loop determines a reflection G   
             from the vector V and applies it from left and right to H,   
             thus creating a nonzero bulge below the subdiagonal.   

             Each subsequent iteration determines a reflection G to   
             restore the Hessenberg form in the (K-1)th column, and thus   
             chases the bulge one step toward the bottom of the active   
             submatrix. NR is the order of G.   

   Computing MIN */
	    i__3 = ns + 1, i__5 = i__ - k + 1;
	    nr = min(i__3,i__5);
	    if (k > l) {
		ccopy_(&nr, &h___ref(k, k - 1), &c__1, v, &c__1);
	    }
	    clarfg_(&nr, v, &v[1], &c__1, &tau);
/* **   
             Increment op count */
	    opst = opst + nr * 10 + 12;
/* ** */
	    if (k > l) {
		i__3 = h___subscr(k, k - 1);
		h__[i__3].r = v[0].r, h__[i__3].i = v[0].i;
		i__3 = i__;
		for (ii = k + 1; ii <= i__3; ++ii) {
		    i__5 = h___subscr(ii, k - 1);
		    h__[i__5].r = 0.f, h__[i__5].i = 0.f;
/* L140: */
		}
	    }
	    v[0].r = 1.f, v[0].i = 0.f;

/*           Apply G' from the left to transform the rows of the matrix   
             in columns K to I2. */

	    i__3 = i2 - k + 1;
	    r_cnjg(&q__1, &tau);
	    clarfx_("Left", &nr, &i__3, v, &q__1, &h___ref(k, k), ldh, &work[
		    1]);

/*           Apply G from the right to transform the columns of the   
             matrix in rows I1 to min(K+NR,I).   

   Computing MIN */
	    i__5 = k + nr;
	    i__3 = min(i__5,i__) - i1 + 1;
	    clarfx_("Right", &i__3, &nr, v, &tau, &h___ref(i1, k), ldh, &work[
		    1]);
/* **   
             Increment op count   
   Computing MIN */
	    i__3 = nr, i__5 = i__ - k;
	    latime_1.ops += ((nr << 2) - 2 << 2) * (i2 - i1 + 2 + min(i__3,
		    i__5));
/* ** */

	    if (wantz) {

/*              Accumulate transformations in the matrix Z */

		clarfx_("Right", &nh, &nr, v, &tau, &z___ref(*ilo, k), ldz, &
			work[1]);
/* **   
                Increment op count */
		latime_1.ops += ((nr << 2) - 2 << 2) * nh;
/* ** */
	    }
/* L150: */
	}

/*        Ensure that H(I,I-1) is real. */

	i__2 = h___subscr(i__, i__ - 1);
	temp.r = h__[i__2].r, temp.i = h__[i__2].i;
	if (r_imag(&temp) != 0.f) {
	    r__1 = temp.r;
	    r__2 = r_imag(&temp);
	    rtemp = slapy2_(&r__1, &r__2);
	    i__2 = h___subscr(i__, i__ - 1);
	    h__[i__2].r = rtemp, h__[i__2].i = 0.f;
	    q__1.r = temp.r / rtemp, q__1.i = temp.i / rtemp;
	    temp.r = q__1.r, temp.i = q__1.i;
	    if (i2 > i__) {
		i__2 = i2 - i__;
		r_cnjg(&q__1, &temp);
		cscal_(&i__2, &q__1, &h___ref(i__, i__ + 1), ldh);
	    }
	    i__2 = i__ - i1;
	    cscal_(&i__2, &temp, &h___ref(i1, i__), &c__1);
/* **   
             Increment op count */
	    opst += (i2 - i1 + 1) * 6;
/* ** */
	    if (wantz) {
		cscal_(&nh, &temp, &z___ref(*ilo, i__), &c__1);
/* **   
                Increment op count */
		opst += nh * 6;
/* ** */
	    }
	}

/* L160: */
    }

/*     Failure to converge in remaining number of iterations */

    *info = i__;
    return 0;

L170:

/*     A submatrix of order <= MAXB in rows and columns L to I has split   
       off. Use the double-shift QR algorithm to handle it. */

    clahqr_(&wantt, &wantz, n, &l, &i__, &h__[h_offset], ldh, &w[1], ilo, ihi,
	     &z__[z_offset], ldz, info);
    if (*info > 0) {
	return 0;
    }

/*     Decrement number of remaining iterations, and return to start of   
       the main loop with a new value of I. */

    itn -= its;
    i__ = l - 1;
    goto L60;

L180:
/* **   
       Compute final op count */
    latime_1.ops += opst;
/* ** */
    i__1 = max(1,*n);
    work[1].r = (real) i__1, work[1].i = 0.f;
    return 0;

/*     End of CHSEQR */

} /* chseqr_ */

#undef z___ref
#undef z___subscr
#undef s_ref
#undef s_subscr
#undef h___ref
#undef h___subscr


