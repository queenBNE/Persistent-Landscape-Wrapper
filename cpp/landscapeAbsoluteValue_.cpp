/*
 * computeIntegralOfLandscape.cpp - use MATLAB External Interfaces to 
 * integrate with Persistence Landscapes Toolbox 
 * 
 * Computes the integral value of a persistence landscape
 *
 * The landscape is a list Lk of pairs (x, lambda_k(x)) corresponding to the 
 * non-differentiable points of the piece-wise linear curves for k=(1,...,n)
 * 
 * Landscape should be represented as a Nx2 matrix (landscape_points)
 * of pairs (x, lambda_k(x))
 * and a nx1 matrix of lengths (landscape_k_dims) 
 * corresponding to the number of such points for each k. 
 * 
 * 
 * The calling syntax is:
 *
 *          distance = bottleneckDistanceOfLandscapes(landscape_points, landscape1_kdims)
 *
 * This is a MEX-file for MATLAB.
 *
*/

#include "PersistenceBarcode.h"
#include "PersistenceLandscape.h"
#include "VectorSpaceOfPersistenceLandscapes.h"
#include "mex.h"
#include "interfaceToCppLandscape.h"
#include "cppToInterfaceLandscape.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <set>
#include <vector>


using namespace std;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    /* Check Input */
    /* make sure there are four input arguments */
    if(nrhs!=2){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs", "Two inputs required.");
    }
    /* make sure the input landscapes are of the right format */
    if( !mxIsDouble(prhs[0]) || mxIsComplex(prhs[0])){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble", "landscape1_points must be type double.");
    }
    if(mxGetM(prhs[0])!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notRowVector", "landscape1_points must have two rows.");
    }
       
    /*******************************************
     *                                         *
     *   Obtaining C++ landscape objects from  *
     *   input interface objects               *
     *                                         * 
     *******************************************/
    
    /* Declare variables */
    mxArray *landscape_arr, *k_dims_arr;
    landscape_arr = mxDuplicateArray(prhs[0]);
    k_dims_arr = mxDuplicateArray(prhs[1]);
    
    double *landscape, *k_dims;
    landscape = mxGetPr(landscape_arr);
    k_dims = mxGetPr(k_dims_arr);
    
    int k_max = mxGetN(prhs[1]); 
    
    PersistenceLandscape persLand = constructLandscape(landscape, k_dims, k_max);
  
       
    /*******************************************
     *                                         *
     *   Actual computation                    *
     *                                         * 
     *******************************************/
    
    PersistenceLandscape l = persLand.abs();
    
    /*******************************************
     *                                         *
     *   Constructing interface landscape      *
     *   object from C++                       * 
     *                                         * 
     *******************************************/

    vector < double > points = getPoints(l);
    double *output;
    plhs[0] = mxCreateDoubleMatrix(2, points.size()/2, mxREAL);
    output = mxGetPr(plhs[0]);
    for(int k = 0; k<points.size();++k){
        output[k] = points[k];
    }
    
    vector < double > lengths = getLengths(l);
    double *k_lengths;
    plhs[1] = mxCreateDoubleMatrix(1,lengths.size(), mxREAL);
    k_lengths = mxGetPr(plhs[1]);
    for(int k = 0; k<lengths.size();++k){
        k_lengths[k] = lengths[k];
    }
    
}

