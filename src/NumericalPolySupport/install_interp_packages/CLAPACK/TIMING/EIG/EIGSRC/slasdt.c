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

/* Subroutine */ int slasdt_(integer *n, integer *lvl, integer *nd, integer *
	inode, integer *ndiml, integer *ndimr, integer *msub)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static integer maxn;
    static real temp;
    static integer nlvl, llst, i__, ncrnt, il, ir;


/*  -- LAPACK auxiliary routine (instrum to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   

       Common block to return operation count   

    Purpose   
    =======   

    SLASDT creates a tree of subproblems for bidiagonal divide and   
    conquer.   

    Arguments   
    =========   

     N      (input) INTEGER   
            On entry, the number of diagonal elements of the   
            bidiagonal matrix.   

     LVL    (output) INTEGER   
            On exit, the number of levels on the computation tree.   

     ND     (output) INTEGER   
            On exit, the number of nodes on the tree.   

     INODE  (output) INTEGER array, dimension ( N )   
            On exit, centers of subproblems.   

     NDIML  (output) INTEGER array, dimension ( N )   
            On exit, row dimensions of left children.   

     NDIMR  (output) INTEGER array, dimension ( N )   
            On exit, row dimensions of right children.   

     MSUB   (input) INTEGER.   
            On entry, the maximum row dimension each subproblem at the   
            bottom of the tree can be of.   

    Further Details   
    ===============   

    Based on contributions by   
       Ming Gu and Huan Ren, Computer Science Division, University of   
       California at Berkeley, USA   

    =====================================================================   


       Find the number of levels on the tree.   

       Parameter adjustments */
    --ndimr;
    --ndiml;
    --inode;

    /* Function Body */
    latime_1.ops += 2.f;
    maxn = max(1,*n);
    temp = log((real) maxn / (real) (*msub + 1)) / log(2.f);
    *lvl = (integer) temp + 1;

    i__ = *n / 2;
    inode[1] = i__ + 1;
    ndiml[1] = i__;
    ndimr[1] = *n - i__ - 1;
    il = 0;
    ir = 1;
    llst = 1;
    i__1 = *lvl - 1;
    for (nlvl = 1; nlvl <= i__1; ++nlvl) {

/*        Constructing the tree at (NLVL+1)-st level. The number of   
          nodes created on this level is LLST * 2. */

	i__2 = llst - 1;
	for (i__ = 0; i__ <= i__2; ++i__) {
	    il += 2;
	    ir += 2;
	    ncrnt = llst + i__;
	    ndiml[il] = ndiml[ncrnt] / 2;
	    ndimr[il] = ndiml[ncrnt] - ndiml[il] - 1;
	    inode[il] = inode[ncrnt] - ndimr[il] - 1;
	    ndiml[ir] = ndimr[ncrnt] / 2;
	    ndimr[ir] = ndimr[ncrnt] - ndiml[ir] - 1;
	    inode[ir] = inode[ncrnt] + ndiml[ir] + 1;
/* L10: */
	}
	llst <<= 1;
/* L20: */
    }
    *nd = (llst << 1) - 1;

    return 0;

/*     End of SLASDT */

} /* slasdt_ */

