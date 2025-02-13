/*
To run
cd scripts
./mat_mul.sh
*/
#include "utils.h"
int main(){
    int row1 = 100;
    int col1 = 96;
    int row2 = 96;
    int col2 = 320;
    int16_t mat1[row1][col1];
    int16_t mat2[row2][col2];
    int16_t res[row1][col2];
    int16_t res2[row1][col2];
    int16_t *mat1Idx=&mat1[0][0];
    int16_t *mat2Idx=&mat2[0][0];
    int16_t *res2Idx=&res2[0][0];
    int iteration1, iteration2;
    for(int r = 0;r < row1;r++){
        for(int c =0;c < col1;c++){
            mat1[r][c] =  2;
        }
    }
    for(int r = 0;r < row2;r++){
        for(int c =0;c < col2;c++){
            mat2[r][c] =  3;
        }
    }
    for(int r = 0;r < row1;r++){
        for(int c = 0;c < col2;c++){
            res[r][c] = 0;
            res2[r][c] = 0;
        }
    }
    for(int r = 0;r < row1;r++){
        for(int c =0;c < col2;c++){
            for(int k = 0;k < col1;k++){
                res[r][c] += mat1[r][k] * mat2[k][c];
                iteration1++;
            }
        }
    }
    int outr = row1;
    int ourc = col2;
    for(int r = 0;r < row1;r++){
        mat2Idx = &mat2[0][0];
        for(int c = 0;c < col2;c+=32){
            short_vec vOutC = (short_vec)(0);
            for(int c = 0;c < col1;c+=1){
                short_vec pp = (short_vec)(mat1[r][c]);
                short_vec vE1 = *(short_vec *)mat2Idx;
                short_vec resw = pp * vE1;
                vOutC = vOutC + resw;
                iteration2++;
                mat2Idx+=32;
            }
            *(short_vec *) (res2Idx) = vOutC;
            res2Idx += 32;
        }
    }
    for(int r = 0;r < row1;r++){
        for(int c = 0;c < col2;c++){
            if(res[r][c] != res2[r][c] ){
                cout<<"False :(";
                return 0;
            }
        }
    }
    cout<<"Iteration 1 : "<<iteration1<<endl;
    cout<<"Iteration 2 : "<<iteration2<<endl;
}