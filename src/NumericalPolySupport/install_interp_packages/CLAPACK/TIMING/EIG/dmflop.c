#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

doublereal dmflop_(doublereal *ops, doublereal *time, integer *info)
{
    /* System generated locals */
    doublereal ret_val, d__1;


/*  -- LAPACK timing routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

       DMFLOP computes the megaflop rate given the number of operations   
       and time in seconds.  This is basically just a divide operation,   
       but care is taken not to divide by zero.   

    Arguments   
    =========   

    OPS    - DOUBLE PRECISION   
             On entry, OPS is the number of floating point operations   
             performed by the timed routine.   

    TIME   - DOUBLE PRECISION   
             On entry, TIME is the total time in seconds used by the   
             timed routine.   

    INFO   - INTEGER   
             On entry, INFO specifies the return code from the timed   
             routine.  If INFO is not 0, then DMFLOP returns a negative   
             value, indicating an error.   

    ===================================================================== */


    if (*time <= 0.) {
	ret_val = 0.;
    } else {
	ret_val = *ops / (*time * 1e6);
    }
    if (*info != 0) {
	ret_val = -(d__1 = (doublereal) (*info), abs(d__1));
    }
    return ret_val;

/*     End of DMFLOP */

} /* dmflop_ */

