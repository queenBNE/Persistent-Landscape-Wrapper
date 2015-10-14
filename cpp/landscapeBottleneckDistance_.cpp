/*
 * bottleneckDistanceOfLandscapes.cpp - use MATLAB External Interfaces to 
 * integrate with Persistence Landscapes Toolbox 
 * 
 * Computes the Bottleneck distance (distance) 
 * between two input barcodes (barcode1, barcode2)
 * barcode1 and barcode2 should be a 2xN1 and 2xN2 matrix of doubles 
 * 
 * The calling syntax is:
 *
 *          distance = bottleneckDistanceOfLandscapes(barcode1, barcode2)
 *
 * This is a MEX-file for MATLAB.
 *
*/

#include "PersistenceBarcode.h"
#include "PersistenceLandscape.h"
#include "VectorSpaceOfPersistenceLandscapes.h"
#include "mex.h"
#include "interfaceToCppLandscape.h"
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
    double distance = computeMaxNormDiscanceOfLandscapes(landscapes[0],landscapes[1]);
    
    /*******************************************
     *                                         *
     *   Constructing interface landscape      *
     *   object from C++                       * 
     *                                         * 
     *******************************************/
    plhs[0] = mxCreateDoubleScalar(distance);
}

