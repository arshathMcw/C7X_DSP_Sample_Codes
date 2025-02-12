/*
To run
cd scripts
./mat_mul.sh
*/
#include "utils.h"
int main(){
    int row1 = 1;
    int col1 = 32;
    int row2 = 32;
    int col2 = 32;
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
            mat1[r][c] =  r + c;
        }
    }
    for(int r = 0;r < row2;r++){
        for(int c =0;c < col2;c++){
            mat2[r][c] =  r + c;
            // cout<<mat2[r][c]<<" ";
        }
        // cout<<endl;
    }
    for(int r = 0;r < col1;r++){
        for(int c =0;c < row2;c++){
            for(int k = 0;k < row2;k++){
                res[r][c] += mat1[r][k] * mat2[k][c];
                iteration1++;
            }
        }
    }
    for(int r = 0;r < row1;r++){
        short_vec vOutC = (short_vec)(0);
        for(int c = 0;c < col2;c+=1){
            short_vec vE1 = (short_vec)(0);
            // cout<<r <<" "<<c<<endl;
            short_vec pp = (short_vec)(mat1[r][c]);
            // pp.print();
            vE1 = *(short_vec *)mat2Idx;
            // vE1.print();
            short_vec resw = pp * vE1;
            vOutC = vOutC + resw;
            iteration2++;
            cout<<mat2Idx<<endl;
            mat2Idx+=32;
        }
        // vOutC.print();
    }
    // mat2Idx+=32;

    // short_vec vE1 = *(short_vec *)(mat2Idx);
    // vE1.print();
    // cout<<mat2Idx<<endl;
    // mat2Idx+=32;

    // vE1 = (short_vec)(0);
    // vE1 = *(short_vec *)mat2Idx;
    // cout<<mat2Idx<<endl;
    // cout<<&mat2[1][0]<<endl;
    // vE1.print();
    // vE1.print();
    cout<<"Iteration 1 : "<<iteration1<<endl;
    cout<<"Iteration 2 : "<<iteration2<<endl;
}