#ifndef INTERFACE_TO_CPP_LANDSCAPE
#define INTERFACE_TO_CPP_LANDSCAPE
#include <vector>
#include "PersistenceLandscape.h"

using namespace std;

PersistenceLandscape constructLandscape(double *landscape, double *k_dims, int k_max){
    int s = 0;
        vector< vector< pair<double,double> > > land(k_max);
        for(int i = 0; i<k_max; ++i){
            vector< pair<double,double> > lambda_k(k_dims[i]);
            for(int j = 0;j<k_dims[i];++j){
                lambda_k[j] = make_pair(landscape[s],landscape[s+1]);
                s = s + 2;
            }
            land[i] = lambda_k;
        }
    PersistenceLandscape persland = PersistenceLandscape(land);
    return persland;
}
#endif 