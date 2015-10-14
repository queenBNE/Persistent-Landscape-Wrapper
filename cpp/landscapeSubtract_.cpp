/*
 * addLandscapes.cpp - use MATLAB External Interfaces to 
 * integrate with Persistence Landscapes Toolbox 
 * 
 * Computes the sum (sum)
 * of two persistence landscapes (landscape1, landscape2) 
 *
 * Landscapes are lists Lk of pairs (x, lambda_k(x)) corresponding to the 
 * non-differentiable points of piece-wise linear curves for k=(1,...,n)
 * 
 * Landscapes should be represented as a Nx2 matrix (landscape_points)
 * of pairs (x, lambda_k(x))
 * and a nx1 matrix of lengths (landscape_k_dims) 
 * corresponding to the number of such points for each k. 
 * 
 * 
 * The calling syntax is:
 *
 *          distance = bottleneckDistanceOfLandscapes(landscape1_points, landscape1_k_dims, landscape2_points, landscape2_k_dims)
 *
 * This is a MEX-file for MATLAB.
 *
*/

#include "PersistenceBarcode.h"
#include "PersistenceLandscape.h"
#include "VectorSpaceOfPersistenceLandscapes.h"
#include "interfaceToCppLandscape.h"
#include "cppToInterfaceLandscape.h"
#include "mex.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <set>
#include <vector>

using namespace std;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    /*******************************************
     *                                         *
     *   Check input                           *
     *                                         * 
     *******************************************/
    if(nrhs!=4){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs", "Four inputs required.");}
    if( !mxIsDouble(prhs[0]) || mxIsComplex(prhs[0])){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble", "landscape1_points must be type double.");}
    if(mxGetM(prhs[0])!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notRowVector", "landscape1_points must have two rows.");}
    if( !mxIsDouble(prhs[2]) || mxIsComplex(prhs[1])){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble", "landscape2_points must be type double.");}
    if(mxGetM(prhs[2])!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notRowVector", "landscape2_points must have two rows.");}
    
    /*******************************************
     *                                         *
     *   Obtaining C++ landscape objects from  *
     *   input interface objects               *
     *                                         * 
     *******************************************/
    vector < PersistenceLandscape > landscapes(2);
    mxArray *landscape_arr, *k_dims_arr;
    double *landscape, *k_dims;
    
    for(int k=0; k<nrhs/2; ++k){
        landscape_arr = mxDuplicateArray(prhs[k*2]);
        landscape = mxGetPr(landscape_arr);
        k_dims_arr = mxDuplicateArray(prhs[k*2+1]);
        k_dims = mxGetPr(k_dims_arr);
        int k_max = mxGetN(prhs[k*2+1]);
        landscapes[k] = constructLandscape(landscape, k_dims, k_max);
    }  
    
    /*******************************************
     *                                         *
     *   Actual computation                    *
     *                                         * 
     *******************************************/
    PersistenceLandscape l = landscapes[0] - landscapes[1];
    
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

