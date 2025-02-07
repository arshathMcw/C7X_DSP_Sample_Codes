/*
To run
cd scripts
./mat_mul.sh
*/
#include "utils.h"
int main(){
    int rsize = 32;
    int csize = 32;
    vector<vector<int16_t>> mat1(rsize,vector<int16_t>(csize,0));
    vector<vector<int16_t>> mat2(rsize,vector<int16_t>(csize,0));
    vector<vector<int16_t>> res(rsize,vector<int16_t>(csize,0)),res2(rsize,vector<int16_t>(csize,0));
    int32_t val = 0;
    int iteration1, iteration2;
    for(int r = 0;r < rsize;r++){
        val++;
        for(int c =0;c < csize;c++){
            mat1[r][c] =  val;
            mat2[r][c] =  val;
        }
    }
    for(int r = 0;r < rsize;r++){
        for(int c =0;c < csize;c++){
            for(int k = 0;k < csize;k++){
                res[r][c] += mat1[r][k] * mat2[k][c];
                iteration1++;
            }
        }
    }
    for(int r = 0;r < 32;r++){
        short_vec vOutC = (short_vec)(0);
        for(int c = 0;c < 32;c++){
            short_vec pp = (short_vec)(mat1[r][c]);
            short_vec * pVec = (short_vec *)&mat2[c][0];
            short_vec vE = *pVec;
            short_vec resw = pp * vE;
            vOutC = vOutC + resw;
            iteration2++;
        }
        // vOutC.print();
    }
    cout<<"Iteration 1 : "<<iteration1<<endl;
    cout<<"Iteration 2 : "<<iteration2<<endl;
}