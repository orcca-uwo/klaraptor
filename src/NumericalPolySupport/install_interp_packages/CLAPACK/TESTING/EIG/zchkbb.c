#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__0 = 0;
static integer c__6 = 6;
static doublereal c_b33 = 1.;
static integer c__1 = 1;
static doublereal c_b41 = 0.;
static integer c__4 = 4;
static integer c_n1 = -1;

/* Subroutine */ int zchkbb_(integer *nsizes, integer *mval, integer *nval, 
	integer *nwdths, integer *kk, integer *ntypes, logical *dotype, 
	integer *nrhs, integer *iseed, doublereal *thresh, integer *nounit, 
	doublecomplex *a, integer *lda, doublecomplex *ab, integer *ldab, 
	doublereal *bd, doublereal *be, doublecomplex *q, integer *ldq, 
	doublecomplex *p, integer *ldp, doublecomplex *c__, integer *ldc, 
	doublecomplex *cc, doublecomplex *work, integer *lwork, doublereal *
	rwork, doublereal *result, integer *info)
{
    /* Initialized data */

    static integer ktype[15] = { 1,2,4,4,4,4,4,6,6,6,6,6,9,9,9 };
    static integer kmagn[15] = { 1,1,1,1,1,2,3,1,1,1,2,3,1,2,3 };
    static integer kmode[15] = { 0,0,4,3,1,4,4,4,3,1,4,4,0,0,0 };

    /* Format strings */
    static char fmt_9999[] = "(\002 ZCHKBB: \002,a,\002 returned INFO=\002,i"
	    "5,\002.\002,/9x,\002M=\002,i5,\002 N=\002,i5,\002 K=\002,i5,\002"
	    ", JTYPE=\002,i5,\002, ISEED=(\002,3(i5,\002,\002),i5,\002)\002)";
    static char fmt_9998[] = "(\002 M =\002,i4,\002 N=\002,i4,\002, K=\002,i"
	    "3,\002, seed=\002,4(i4,\002,\002),\002 type \002,i2,\002, test"
	    "(\002,i2,\002)=\002,g10.3)";

    /* System generated locals */
    integer a_dim1, a_offset, ab_dim1, ab_offset, c_dim1, c_offset, cc_dim1, 
	    cc_offset, p_dim1, p_offset, q_dim1, q_offset, i__1, i__2, i__3, 
	    i__4, i__5, i__6, i__7, i__8, i__9;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal cond;
    static integer jcol, kmax, mmax, nmax;
    static doublereal unfl, ovfl;
    static integer i__, j, k, m, n;
    static logical badmm, badnn;
    static integer imode, iinfo;
    extern /* Subroutine */ int zbdt01_(integer *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublereal *, doublereal *, doublecomplex *, integer *, 
	    doublecomplex *, doublereal *, doublereal *), zbdt02_(integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, integer *,
	     doublecomplex *, integer *, doublecomplex *, doublereal *, 
	    doublereal *);
    static doublereal anorm;
    static integer mnmin, mnmax, nmats, jsize, nerrs, itype, jtype, ntest;
    extern /* Subroutine */ int dlahd2_(integer *, char *), zunt01_(
	    char *, integer *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublereal *, doublereal *);
    static logical badnnb;
    static integer kl;
    extern doublereal dlamch_(char *);
    static integer jr, ku;
    extern /* Subroutine */ int zgbbrd_(char *, integer *, integer *, integer 
	    *, integer *, integer *, doublecomplex *, integer *, doublereal *,
	     doublereal *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, 
	    doublereal *, integer *);
    static integer idumma[1];
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static integer ioldsd[4];
    extern /* Subroutine */ int dlasum_(char *, integer *, integer *, integer 
	    *);
    static doublereal amninv;
    static integer jwidth;
    extern /* Subroutine */ int zlacpy_(char *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), 
	    zlaset_(char *, integer *, integer *, doublecomplex *, 
	    doublecomplex *, doublecomplex *, integer *), zlatmr_(
	    integer *, integer *, char *, integer *, char *, doublecomplex *, 
	    integer *, doublereal *, doublecomplex *, char *, char *, 
	    doublecomplex *, integer *, doublereal *, doublecomplex *, 
	    integer *, doublereal *, char *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, char *, doublecomplex *, integer *, 
	    integer *, integer *);
    static doublereal rtunfl, rtovfl, ulpinv;
    extern /* Subroutine */ int zlatms_(integer *, integer *, char *, integer 
	    *, char *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, integer *, char *, doublecomplex *, integer *, 
	    doublecomplex *, integer *);
    static integer mtypes, ntestt;
    static doublereal ulp;

    /* Fortran I/O blocks */
    static cilist io___41 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___45 = { 0, 0, 0, fmt_9998, 0 };



#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define ab_subscr(a_1,a_2) (a_2)*ab_dim1 + a_1
#define ab_ref(a_1,a_2) ab[ab_subscr(a_1,a_2)]


/*  -- LAPACK test routine (new routine for release 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    ZCHKBB tests the reduction of a general complex rectangular band   
    matrix to real bidiagonal form.   

    ZGBBRD factors a general band matrix A as  Q B P* , where * means   
    conjugate transpose, B is upper bidiagonal, and Q and P are unitary;   
    ZGBBRD can also overwrite a given matrix C with Q* C .   

    For each pair of matrix dimensions (M,N) and each selected matrix   
    type, an M by N matrix A and an M by NRHS matrix C are generated.   
    The problem dimensions are as follows   
       A:          M x N   
       Q:          M x M   
       P:          N x N   
       B:          min(M,N) x min(M,N)   
       C:          M x NRHS   

    For each generated matrix, 4 tests are performed:   

    (1)   | A - Q B PT | / ( |A| max(M,N) ulp ), PT = P'   

    (2)   | I - Q' Q | / ( M ulp )   

    (3)   | I - PT PT' | / ( N ulp )   

    (4)   | Y - Q' C | / ( |Y| max(M,NRHS) ulp ), where Y = Q' C.   

    The "types" are specified by a logical array DOTYPE( 1:NTYPES );   
    if DOTYPE(j) is .TRUE., then matrix type "j" will be generated.   
    Currently, the list of possible types is:   

    The possible matrix types are   

    (1)  The zero matrix.   
    (2)  The identity matrix.   

    (3)  A diagonal matrix with evenly spaced entries   
         1, ..., ULP  and random signs.   
         (ULP = (first number larger than 1) - 1 )   
    (4)  A diagonal matrix with geometrically spaced entries   
         1, ..., ULP  and random signs.   
    (5)  A diagonal matrix with "clustered" entries 1, ULP, ..., ULP   
         and random signs.   

    (6)  Same as (3), but multiplied by SQRT( overflow threshold )   
    (7)  Same as (3), but multiplied by SQRT( underflow threshold )   

    (8)  A matrix of the form  U D V, where U and V are orthogonal and   
         D has evenly spaced entries 1, ..., ULP with random signs   
         on the diagonal.   

    (9)  A matrix of the form  U D V, where U and V are orthogonal and   
         D has geometrically spaced entries 1, ..., ULP with random   
         signs on the diagonal.   

    (10) A matrix of the form  U D V, where U and V are orthogonal and   
         D has "clustered" entries 1, ULP,..., ULP with random   
         signs on the diagonal.   

    (11) Same as (8), but multiplied by SQRT( overflow threshold )   
    (12) Same as (8), but multiplied by SQRT( underflow threshold )   

    (13) Rectangular matrix with random entries chosen from (-1,1).   
    (14) Same as (13), but multiplied by SQRT( overflow threshold )   
    (15) Same as (13), but multiplied by SQRT( underflow threshold )   

    Arguments   
    =========   

    NSIZES  (input) INTEGER   
            The number of values of M and N contained in the vectors   
            MVAL and NVAL.  The matrix sizes are used in pairs (M,N).   
            If NSIZES is zero, ZCHKBB does nothing.  NSIZES must be at   
            least zero.   

    MVAL    (input) INTEGER array, dimension (NSIZES)   
            The values of the matrix row dimension M.   

    NVAL    (input) INTEGER array, dimension (NSIZES)   
            The values of the matrix column dimension N.   

    NWDTHS  (input) INTEGER   
            The number of bandwidths to use.  If it is zero,   
            ZCHKBB does nothing.  It must be at least zero.   

    KK      (input) INTEGER array, dimension (NWDTHS)   
            An array containing the bandwidths to be used for the band   
            matrices.  The values must be at least zero.   

    NTYPES  (input) INTEGER   
            The number of elements in DOTYPE.   If it is zero, ZCHKBB   
            does nothing.  It must be at least zero.  If it is MAXTYP+1   
            and NSIZES is 1, then an additional type, MAXTYP+1 is   
            defined, which is to use whatever matrix is in A.  This   
            is only useful if DOTYPE(1:MAXTYP) is .FALSE. and   
            DOTYPE(MAXTYP+1) is .TRUE. .   

    DOTYPE  (input) LOGICAL array, dimension (NTYPES)   
            If DOTYPE(j) is .TRUE., then for each size in NN a   
            matrix of that size and of type j will be generated.   
            If NTYPES is smaller than the maximum number of types   
            defined (PARAMETER MAXTYP), then types NTYPES+1 through   
            MAXTYP will not be generated.  If NTYPES is larger   
            than MAXTYP, DOTYPE(MAXTYP+1) through DOTYPE(NTYPES)   
            will be ignored.   

    NRHS    (input) INTEGER   
            The number of columns in the "right-hand side" matrix C.   
            If NRHS = 0, then the operations on the right-hand side will   
            not be tested. NRHS must be at least 0.   

    ISEED   (input/output) INTEGER array, dimension (4)   
            On entry ISEED specifies the seed of the random number   
            generator. The array elements should be between 0 and 4095;   
            if not they will be reduced mod 4096.  Also, ISEED(4) must   
            be odd.  The random number generator uses a linear   
            congruential sequence limited to small integers, and so   
            should produce machine independent random numbers. The   
            values of ISEED are changed on exit, and can be used in the   
            next call to ZCHKBB to continue the same random number   
            sequence.   

    THRESH  (input) DOUBLE PRECISION   
            A test will count as "failed" if the "error", computed as   
            described above, exceeds THRESH.  Note that the error   
            is scaled to be O(1), so THRESH should be a reasonably   
            small multiple of 1, e.g., 10 or 100.  In particular,   
            it should not depend on the precision (single vs. double)   
            or the size of the matrix.  It must be at least zero.   

    NOUNIT  (input) INTEGER   
            The FORTRAN unit number for printing out error messages   
            (e.g., if a routine returns IINFO not equal to 0.)   

    A       (input/workspace) DOUBLE PRECISION array, dimension   
                              (LDA, max(NN))   
            Used to hold the matrix A.   

    LDA     (input) INTEGER   
            The leading dimension of A.  It must be at least 1   
            and at least max( NN ).   

    AB      (workspace) DOUBLE PRECISION array, dimension (LDAB, max(NN))   
            Used to hold A in band storage format.   

    LDAB    (input) INTEGER   
            The leading dimension of AB.  It must be at least 2 (not 1!)   
            and at least max( KK )+1.   

    BD      (workspace) DOUBLE PRECISION array, dimension (max(NN))   
            Used to hold the diagonal of the bidiagonal matrix computed   
            by ZGBBRD.   

    BE      (workspace) DOUBLE PRECISION array, dimension (max(NN))   
            Used to hold the off-diagonal of the bidiagonal matrix   
            computed by ZGBBRD.   

    Q       (workspace) COMPLEX*16 array, dimension (LDQ, max(NN))   
            Used to hold the unitary matrix Q computed by ZGBBRD.   

    LDQ     (input) INTEGER   
            The leading dimension of Q.  It must be at least 1   
            and at least max( NN ).   

    P       (workspace) COMPLEX*16 array, dimension (LDP, max(NN))   
            Used to hold the unitary matrix P computed by ZGBBRD.   

    LDP     (input) INTEGER   
            The leading dimension of P.  It must be at least 1   
            and at least max( NN ).   

    C       (workspace) COMPLEX*16 array, dimension (LDC, max(NN))   
            Used to hold the matrix C updated by ZGBBRD.   

    LDC     (input) INTEGER   
            The leading dimension of U.  It must be at least 1   
            and at least max( NN ).   

    CC      (workspace) COMPLEX*16 array, dimension (LDC, max(NN))   
            Used to hold a copy of the matrix C.   

    WORK    (workspace) COMPLEX*16 array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The number of entries in WORK.  This must be at least   
            max( LDA+1, max(NN)+1 )*max(NN).   

    RWORK   (workspace) DOUBLE PRECISION array, dimension (max(NN))   

    RESULT  (output) DOUBLE PRECISION array, dimension (4)   
            The values computed by the tests described above.   
            The values are currently limited to 1/ulp, to avoid   
            overflow.   

    INFO    (output) INTEGER   
            If 0, then everything ran OK.   

   -----------------------------------------------------------------------   

         Some Local Variables and Parameters:   
         ---- ----- --------- --- ----------   
         ZERO, ONE       Real 0 and 1.   
         MAXTYP          The number of types defined.   
         NTEST           The number of tests performed, or which can   
                         be performed so far, for the current matrix.   
         NTESTT          The total number of tests performed so far.   
         NMAX            Largest value in NN.   
         NMATS           The number of matrices generated so far.   
         NERRS           The number of tests which have exceeded THRESH   
                         so far.   
         COND, IMODE     Values to be passed to the matrix generators.   
         ANORM           Norm of A; passed to matrix generators.   

         OVFL, UNFL      Overflow and underflow thresholds.   
         ULP, ULPINV     Finest relative precision and its inverse.   
         RTOVFL, RTUNFL  Square roots of the previous 2 values.   
                 The following four arrays decode JTYPE:   
         KTYPE(j)        The general type (1-10) for type "j".   
         KMODE(j)        The MODE value to be passed to the matrix   
                         generator for type "j".   
         KMAGN(j)        The order of magnitude ( O(1),   
                         O(overflow^(1/2) ), O(underflow^(1/2) )   

    =====================================================================   

       Parameter adjustments */
    --mval;
    --nval;
    --kk;
    --dotype;
    --iseed;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    ab_dim1 = *ldab;
    ab_offset = 1 + ab_dim1 * 1;
    ab -= ab_offset;
    --bd;
    --be;
    q_dim1 = *ldq;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    p_dim1 = *ldp;
    p_offset = 1 + p_dim1 * 1;
    p -= p_offset;
    cc_dim1 = *ldc;
    cc_offset = 1 + cc_dim1 * 1;
    cc -= cc_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;
    --work;
    --rwork;
    --result;

    /* Function Body   

       Check for errors */

    ntestt = 0;
    *info = 0;

/*     Important constants */

    badmm = FALSE_;
    badnn = FALSE_;
    mmax = 1;
    nmax = 1;
    mnmax = 1;
    i__1 = *nsizes;
    for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	i__2 = mmax, i__3 = mval[j];
	mmax = max(i__2,i__3);
	if (mval[j] < 0) {
	    badmm = TRUE_;
	}
/* Computing MAX */
	i__2 = nmax, i__3 = nval[j];
	nmax = max(i__2,i__3);
	if (nval[j] < 0) {
	    badnn = TRUE_;
	}
/* Computing MAX   
   Computing MIN */
	i__4 = mval[j], i__5 = nval[j];
	i__2 = mnmax, i__3 = min(i__4,i__5);
	mnmax = max(i__2,i__3);
/* L10: */
    }

    badnnb = FALSE_;
    kmax = 0;
    i__1 = *nwdths;
    for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	i__2 = kmax, i__3 = kk[j];
	kmax = max(i__2,i__3);
	if (kk[j] < 0) {
	    badnnb = TRUE_;
	}
/* L20: */
    }

/*     Check for errors */

    if (*nsizes < 0) {
	*info = -1;
    } else if (badmm) {
	*info = -2;
    } else if (badnn) {
	*info = -3;
    } else if (*nwdths < 0) {
	*info = -4;
    } else if (badnnb) {
	*info = -5;
    } else if (*ntypes < 0) {
	*info = -6;
    } else if (*nrhs < 0) {
	*info = -8;
    } else if (*lda < nmax) {
	*info = -13;
    } else if (*ldab < (kmax << 1) + 1) {
	*info = -15;
    } else if (*ldq < nmax) {
	*info = -19;
    } else if (*ldp < nmax) {
	*info = -21;
    } else if (*ldc < nmax) {
	*info = -23;
    } else if ((max(*lda,nmax) + 1) * nmax > *lwork) {
	*info = -26;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZCHKBB", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*nsizes == 0 || *ntypes == 0 || *nwdths == 0) {
	return 0;
    }

/*     More Important constants */

    unfl = dlamch_("Safe minimum");
    ovfl = 1. / unfl;
    ulp = dlamch_("Epsilon") * dlamch_("Base");
    ulpinv = 1. / ulp;
    rtunfl = sqrt(unfl);
    rtovfl = sqrt(ovfl);

/*     Loop over sizes, widths, types */

    nerrs = 0;
    nmats = 0;

    i__1 = *nsizes;
    for (jsize = 1; jsize <= i__1; ++jsize) {
	m = mval[jsize];
	n = nval[jsize];
	mnmin = min(m,n);
/* Computing MAX */
	i__2 = max(1,m);
	amninv = 1. / (doublereal) max(i__2,n);

	i__2 = *nwdths;
	for (jwidth = 1; jwidth <= i__2; ++jwidth) {
	    k = kk[jwidth];
	    if (k >= m && k >= n) {
		goto L150;
	    }
/* Computing MAX   
   Computing MIN */
	    i__5 = m - 1;
	    i__3 = 0, i__4 = min(i__5,k);
	    kl = max(i__3,i__4);
/* Computing MAX   
   Computing MIN */
	    i__5 = n - 1;
	    i__3 = 0, i__4 = min(i__5,k);
	    ku = max(i__3,i__4);

	    if (*nsizes != 1) {
		mtypes = min(15,*ntypes);
	    } else {
		mtypes = min(16,*ntypes);
	    }

	    i__3 = mtypes;
	    for (jtype = 1; jtype <= i__3; ++jtype) {
		if (! dotype[jtype]) {
		    goto L140;
		}
		++nmats;
		ntest = 0;

		for (j = 1; j <= 4; ++j) {
		    ioldsd[j - 1] = iseed[j];
/* L30: */
		}

/*              Compute "A".   

                Control parameters:   

                    KMAGN  KMODE        KTYPE   
                =1  O(1)   clustered 1  zero   
                =2  large  clustered 2  identity   
                =3  small  exponential  (none)   
                =4         arithmetic   diagonal, (w/ singular values)   
                =5         random log   (none)   
                =6         random       nonhermitian, w/ singular values   
                =7                      (none)   
                =8                      (none)   
                =9                      random nonhermitian */

		if (mtypes > 15) {
		    goto L90;
		}

		itype = ktype[jtype - 1];
		imode = kmode[jtype - 1];

/*              Compute norm */

		switch (kmagn[jtype - 1]) {
		    case 1:  goto L40;
		    case 2:  goto L50;
		    case 3:  goto L60;
		}

L40:
		anorm = 1.;
		goto L70;

L50:
		anorm = rtovfl * ulp * amninv;
		goto L70;

L60:
		anorm = rtunfl * max(m,n) * ulpinv;
		goto L70;

L70:

		zlaset_("Full", lda, &n, &c_b1, &c_b1, &a[a_offset], lda);
		zlaset_("Full", ldab, &n, &c_b1, &c_b1, &ab[ab_offset], ldab);
		iinfo = 0;
		cond = ulpinv;

/*              Special Matrices -- Identity & Jordan block   

                   Zero */

		if (itype == 1) {
		    iinfo = 0;

		} else if (itype == 2) {

/*                 Identity */

		    i__4 = n;
		    for (jcol = 1; jcol <= i__4; ++jcol) {
			i__5 = a_subscr(jcol, jcol);
			a[i__5].r = anorm, a[i__5].i = 0.;
/* L80: */
		    }

		} else if (itype == 4) {

/*                 Diagonal Matrix, singular values specified */

		    zlatms_(&m, &n, "S", &iseed[1], "N", &rwork[1], &imode, &
			    cond, &anorm, &c__0, &c__0, "N", &a[a_offset], 
			    lda, &work[1], &iinfo);

		} else if (itype == 6) {

/*                 Nonhermitian, singular values specified */

		    zlatms_(&m, &n, "S", &iseed[1], "N", &rwork[1], &imode, &
			    cond, &anorm, &kl, &ku, "N", &a[a_offset], lda, &
			    work[1], &iinfo);

		} else if (itype == 9) {

/*                 Nonhermitian, random entries */

		    zlatmr_(&m, &n, "S", &iseed[1], "N", &work[1], &c__6, &
			    c_b33, &c_b2, "T", "N", &work[n + 1], &c__1, &
			    c_b33, &work[(n << 1) + 1], &c__1, &c_b33, "N", 
			    idumma, &kl, &ku, &c_b41, &anorm, "N", &a[
			    a_offset], lda, idumma, &iinfo);

		} else {

		    iinfo = 1;
		}

/*              Generate Right-Hand Side */

		zlatmr_(&m, nrhs, "S", &iseed[1], "N", &work[1], &c__6, &
			c_b33, &c_b2, "T", "N", &work[m + 1], &c__1, &c_b33, &
			work[(m << 1) + 1], &c__1, &c_b33, "N", idumma, &m, 
			nrhs, &c_b41, &c_b33, "NO", &c__[c_offset], ldc, 
			idumma, &iinfo);

		if (iinfo != 0) {
		    io___41.ciunit = *nounit;
		    s_wsfe(&io___41);
		    do_fio(&c__1, "Generator", (ftnlen)9);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		    *info = abs(iinfo);
		    return 0;
		}

L90:

/*              Copy A to band storage. */

		i__4 = n;
		for (j = 1; j <= i__4; ++j) {
/* Computing MAX */
		    i__5 = 1, i__6 = j - ku;
/* Computing MIN */
		    i__8 = m, i__9 = j + kl;
		    i__7 = min(i__8,i__9);
		    for (i__ = max(i__5,i__6); i__ <= i__7; ++i__) {
			i__5 = ab_subscr(ku + 1 + i__ - j, j);
			i__6 = a_subscr(i__, j);
			ab[i__5].r = a[i__6].r, ab[i__5].i = a[i__6].i;
/* L100: */
		    }
/* L110: */
		}

/*              Copy C */

		zlacpy_("Full", &m, nrhs, &c__[c_offset], ldc, &cc[cc_offset],
			 ldc);

/*              Call ZGBBRD to compute B, Q and P, and to update C. */

		zgbbrd_("B", &m, &n, nrhs, &kl, &ku, &ab[ab_offset], ldab, &
			bd[1], &be[1], &q[q_offset], ldq, &p[p_offset], ldp, &
			cc[cc_offset], ldc, &work[1], &rwork[1], &iinfo);

		if (iinfo != 0) {
		    io___43.ciunit = *nounit;
		    s_wsfe(&io___43);
		    do_fio(&c__1, "ZGBBRD", (ftnlen)6);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		    do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		    *info = abs(iinfo);
		    if (iinfo < 0) {
			return 0;
		    } else {
			result[1] = ulpinv;
			goto L120;
		    }
		}

/*              Test 1:  Check the decomposition A := Q * B * P'   
                     2:  Check the orthogonality of Q   
                     3:  Check the orthogonality of P   
                     4:  Check the computation of Q' * C */

		zbdt01_(&m, &n, &c_n1, &a[a_offset], lda, &q[q_offset], ldq, &
			bd[1], &be[1], &p[p_offset], ldp, &work[1], &rwork[1],
			 &result[1]);
		zunt01_("Columns", &m, &m, &q[q_offset], ldq, &work[1], lwork,
			 &rwork[1], &result[2]);
		zunt01_("Rows", &n, &n, &p[p_offset], ldp, &work[1], lwork, &
			rwork[1], &result[3]);
		zbdt02_(&m, nrhs, &c__[c_offset], ldc, &cc[cc_offset], ldc, &
			q[q_offset], ldq, &work[1], &rwork[1], &result[4]);

/*              End of Loop -- Check for RESULT(j) > THRESH */

		ntest = 4;
L120:
		ntestt += ntest;

/*              Print out tests which fail. */

		i__4 = ntest;
		for (jr = 1; jr <= i__4; ++jr) {
		    if (result[jr] >= *thresh) {
			if (nerrs == 0) {
			    dlahd2_(nounit, "ZBB");
			}
			++nerrs;
			io___45.ciunit = *nounit;
			s_wsfe(&io___45);
			do_fio(&c__1, (char *)&m, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__1, (char *)&jr, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[jr], (ftnlen)sizeof(
				doublereal));
			e_wsfe();
		    }
/* L130: */
		}

L140:
		;
	    }
L150:
	    ;
	}
/* L160: */
    }

/*     Summary */

    dlasum_("ZBB", nounit, &nerrs, &ntestt);
    return 0;


/*     End of ZCHKBB */

} /* zchkbb_ */

#undef ab_ref
#undef ab_subscr
#undef a_ref
#undef a_subscr


