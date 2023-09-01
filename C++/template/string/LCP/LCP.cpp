#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
int lcp[N][N];

void build_lcp( const string & _s ){
    int n = _s.size();
    
    for(int i = n - 2; i >= 0; --i){
        lcp[ i ][ n - 1 ] = ( _s[i] == _s[n - 1] );
    }
    for(int i = n - 3; i >= 0; --i){
        for(int j = n - 2; j > i; --j){
            if( _s[i] != _s[j] ){
                lcp[ i ][ j ] = 0;
            }else{
                lcp[ i ][ j ] = lcp[i + 1][j + 1] + 1;
            }
        }
    }
}
