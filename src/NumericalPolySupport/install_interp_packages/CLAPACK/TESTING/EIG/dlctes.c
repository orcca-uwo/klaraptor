#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublereal c_b2 = 1.;

logical dlctes_(doublereal *zr, doublereal *zi, doublereal *d__)
{
    /* System generated locals */
    logical ret_val;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    DLCTES returns .TRUE. if the eigenvalue (ZR/D) + sqrt(-1)*(ZI/D)   
    is to be selected (specifically, in this subroutine, if the real   
    part of the eigenvalue is negative), and otherwise it returns   
    .FALSE..   

    It is used by the test routine DDRGES to test whether the driver   
    routine DGGES succesfully sorts eigenvalues.   

    Arguments   
    =========   

    ZR      (input) DOUBLE PRECISION   
            The numerator of the real part of a complex eigenvalue   
            (ZR/D) + i*(ZI/D).   

    ZI      (input) DOUBLE PRECISION   
            The numerator of the imaginary part of a complex eigenvalue   
            (ZR/D) + i*(ZI).   

    D       (input) DOUBLE PRECISION   
            The denominator part of a complex eigenvalue   
            (ZR/D) + i*(ZI/D).   

    ===================================================================== */


    if (*d__ == 0.) {
	ret_val = *zr < 0.;
    } else {
	ret_val = d_sign(&c_b2, zr) != d_sign(&c_b2, d__);
    }

    return ret_val;

/*     End of DLCTES */

} /* dlctes_ */

