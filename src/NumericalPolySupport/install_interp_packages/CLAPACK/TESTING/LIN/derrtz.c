#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer infot, nout;
    logical ok, lerr;
} infoc_;

#define infoc_1 infoc_

struct {
    char srnamt[6];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static integer c__2 = 2;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;

/* Subroutine */ int derrtz_(char *path, integer *nunit)
{
    /* Builtin functions */
    integer s_wsle(cilist *), e_wsle(void);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static integer info;
    static doublereal a[4]	/* was [2][2] */, w[2];
    static char c2[2];
    extern /* Subroutine */ int alaesm_(char *, logical *, integer *);
    extern logical lsamen_(integer *, char *, char *);
    extern /* Subroutine */ int chkxer_(char *, integer *, integer *, logical 
	    *, logical *), dtzrqf_(integer *, integer *, doublereal *,
	     integer *, doublereal *, integer *), dtzrzf_(integer *, integer *
	    , doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    integer *);
    static doublereal tau[2];

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, 0, 0 };



#define a_ref(a_1,a_2) a[(a_2)*2 + a_1 - 3]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    DERRTZ tests the error exits for DTZRQF and STZRZF.   

    Arguments   
    =========   

    PATH    (input) CHARACTER*3   
            The LAPACK path name for the routines to be tested.   

    NUNIT   (input) INTEGER   
            The unit number for output.   

    ===================================================================== */


    infoc_1.nout = *nunit;
    io___1.ciunit = infoc_1.nout;
    s_wsle(&io___1);
    e_wsle();
    s_copy(c2, path + 1, (ftnlen)2, (ftnlen)2);
    a_ref(1, 1) = 1.;
    a_ref(1, 2) = 2.;
    a_ref(2, 2) = 3.;
    a_ref(2, 1) = 4.;
    w[0] = 0.;
    w[1] = 0.;
    infoc_1.ok = TRUE_;

    if (lsamen_(&c__2, c2, "TZ")) {

/*        Test error exits for the trapezoidal routines.   

          DTZRQF */

	s_copy(srnamc_1.srnamt, "DTZRQF", (ftnlen)6, (ftnlen)6);
	infoc_1.infot = 1;
	dtzrqf_(&c_n1, &c__0, a, &c__1, tau, &info);
	chkxer_("DTZRQF", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
		infoc_1.ok);
	infoc_1.infot = 2;
	dtzrqf_(&c__1, &c__0, a, &c__1, tau, &info);
	chkxer_("DTZRQF", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
		infoc_1.ok);
	infoc_1.infot = 4;
	dtzrqf_(&c__2, &c__2, a, &c__1, tau, &info);
	chkxer_("DTZRQF", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
		infoc_1.ok);

/*        DTZRZF */

	s_copy(srnamc_1.srnamt, "DTZRZF", (ftnlen)6, (ftnlen)6);
	infoc_1.infot = 1;
	dtzrzf_(&c_n1, &c__0, a, &c__1, tau, w, &c__1, &info);
	chkxer_("DTZRZF", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
		infoc_1.ok);
	infoc_1.infot = 2;
	dtzrzf_(&c__1, &c__0, a, &c__1, tau, w, &c__1, &info);
	chkxer_("DTZRZF", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
		infoc_1.ok);
	infoc_1.infot = 4;
	dtzrzf_(&c__2, &c__2, a, &c__1, tau, w, &c__1, &info);
	chkxer_("DTZRZF", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
		infoc_1.ok);
	infoc_1.infot = 7;
	dtzrzf_(&c__2, &c__2, a, &c__2, tau, w, &c__1, &info);
	chkxer_("DTZRZF", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
		infoc_1.ok);
    }

/*     Print a summary line. */

    alaesm_(path, &infoc_1.ok, &infoc_1.nout);

    return 0;

/*     End of DERRTZ */

} /* derrtz_ */

#undef a_ref


