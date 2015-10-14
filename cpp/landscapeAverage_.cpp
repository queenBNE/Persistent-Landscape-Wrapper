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
#include "mex.h"
#include "interfaceToCppLandscape.h"
#include "cppToInterfaceLandscape.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <set>
#include <vector>

using namespace std;

vector< double > getLengths(PersistenceLandscape l);
vector< double > getPoints(PersistenceLandscape l);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    /* Check Input */
    //TODO 
    vectorSpaceOfPersistenceLandscapes v;
    
    mxArray *landscape_arr, *k_dims_arr;
    double *landscape, *k_dims;
    
    for(int k=0; k<nrhs/2; ++k){
        /* Declare and load vars */
        landscape_arr = mxDuplicateArray(prhs[k*2]);
        landscape = mxGetPr(landscape_arr);

        k_dims_arr = mxDuplicateArray(prhs[k*2+1]);
        k_dims = mxGetPr(k_dims_arr);
        int k_max = mxGetN(prhs[k*2+1]);
        
        PersistenceLandscape persland = constructLandscape(landscape, k_dims, k_max);
        v.addLandscape( persland );
    }  
    
   
    PersistenceLandscape l = v.average();
    
    // Convert to output 
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

