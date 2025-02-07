#include<iostream>
#include "utils.h"
void fun(int row,int col,int16_t *aIdx,int16_t *bIdx,int16_t *rIdx){
    int times = (row * col) / 32;
    for(int t = 0;t < times ;t++){
        short_vec vOutC = (short_vec)(0);
        short_vec vE1 = *(short_vec *)aIdx;
        short_vec vE2 = *(short_vec *)bIdx;
        vOutC = vE1 + vE2;
        *(short_vec *) (rIdx) = vOutC;
        // rIdx.print();
        rIdx+=32;
        aIdx+=32;
        bIdx+=32;
    }
}
int main(){
    int16_t mat[32][3];
    int16_t mat2[32][3];
    int16_t res[32][3];
    int16_t *aIdx=&mat[0][0];
    int16_t *bIdx=&mat2[0][0];
    for(int r = 0;r < 32;r++){
        for(int c = 0;c < 3;c++){
            mat[r][c] = r * c;
            mat2[r][c] = r * c;
        }
    }
    int16_t *rIdx=&res[0][0];
    fun(32,3,aIdx,bIdx,rIdx);
    for(int r = 0;r < 32;r++){
        for(int c = 0;c < 3;c++){
            cout<<res[r][c]<<" ";
        }
        cout<<endl;
    }
    // fun(res);
}