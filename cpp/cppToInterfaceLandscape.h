#ifndef CPP_TO_INTERFACE_LANDSCAPE
#define CPP_TO_INTERFACE_LANDSCAPE
#include <vector>
#include "PersistenceLandscape.h"
using namespace std;

vector< double > getLengths(PersistenceLandscape l){
   vector< double > result(l.size());
   vector< vector< pair<double,double> > > land = l.gimmeProperLandscapePoints();
    for(int i = 0; i<l.size();++i){
        result[i] = land[i].size();
    }
    return result;
}

vector< double > getPoints(PersistenceLandscape l){
   vector< vector< pair<double,double> > > land = l.gimmeProperLandscapePoints();
   int N = 0;
   for(int k = 0; k<l.size();++k){
        N = N + land[k].size();
   }
   vector< double > result(2*N);

   int k = 0;
   for(int i = 0; i<l.size();++i){
        for(int j =0; j<land[i].size(); ++j){
            result[k] = land[i][j].first;
            result[k+1] = land[i][j].second;
            k = k + 2;
        }
   }
   return result;
}
#endif 