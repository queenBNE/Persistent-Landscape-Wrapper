/*
 * toLandscape.cpp - use MATLAB External Interfaces to 
 * integrate with Persistence Landscapes Toolbox 
 * 
 * Computes the sum (sum)
 * of two persistence landscapes (landscape1, landscape2) 
 * landscape1 and landscape2 should be a 2xN1 and 2xN2 matrix of doubles 
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
    /* Check Input */
    /* make sure there is one input argument */
    if(nrhs!=1){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs", "One input required.");
    }
    /* make sure the input barcode is of type double and has two columns */
    if( !mxIsDouble(prhs[0]) || mxIsComplex(prhs[0])){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble", "barcode must be type double.");
    }
    if(mxGetN(prhs[0])!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notRowVector", "barcode must have two colums.");
    }
    
    /* Assigning input to variable */
    //declare variables
    mxArray *barcode_in_m;
    double *barcode_c;

    //associate inputs
    barcode_in_m = mxDuplicateArray(prhs[0]);
     
    //associate pointers
    barcode_c = mxGetPr(barcode_in_m);
     
    // construct barcode from input
    int nrows;
    nrows = mxGetM(prhs[0]); 
    vector < pair < double, double > > v(nrows);
    
    for(int i = 0; i<nrows; ++i){
        v[i] = make_pair(barcode_c[i], barcode_c[nrows+i]);
    }
    PersistenceBarcodes b(v);
    PersistenceLandscape l(b);
    
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

