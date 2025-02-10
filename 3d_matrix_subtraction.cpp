#include "utils.h"
void matrix_sub_optimized(int row,int col,int depth,int16_t *aIdx,int16_t *bIdx,int16_t *rIdx,int &iteration){
    int times = (row * col * depth) / 32;
    for(int t = 0;t < times ;t++){
        short_vec vOutC = (short_vec)(0);
        short_vec vE1 = *(short_vec *)aIdx;
        short_vec vE2 = *(short_vec *)bIdx;
        vOutC = vE1 - vE2;
        *(short_vec *) (rIdx) = vOutC;
        rIdx+=32;
        aIdx+=32;
        bIdx+=32;
        iteration++;
    }
    for(int idx = times * 32;idx < row*col;idx++){
        rIdx[idx - times * 32] = aIdx[idx - times * 32] - bIdx[idx - times * 32];
        iteration++;
    }
}
void matrix_sub_scalar(int row,int col,int depth,int16_t *aIdx,int16_t *bIdx,int16_t *rIdx,int &iteration){
    for(int idx = 0;idx < (row * col * depth);idx++){
        *(rIdx + idx) = *(aIdx + idx) - *(bIdx + idx);
        iteration++;
    }
}
int main(){
	int row,col,depth;
    cout<<"Enter Row Size : ";
    cin>>row;
    cout<<"Enter Column Size : ";
    cin>>col;
    cout<<"Enter Depth Size : ";
    cin>>depth;
    int16_t mat1[row][col][depth];
    int16_t mat2[row][col][depth];
    int16_t res[row][col][depth];
    int16_t res2[row][col][depth];
    int16_t *mat1Idx=&mat1[0][0][0];
    int16_t *mat2Idx=&mat2[0][0][0];
    int16_t *resIdx=&res[0][0][0];
    int16_t *res2Idx=&res2[0][0][0];
    int iteration1 = 0,iteration2 = 0;
    get_random_value_for_2d_int16_t(row,col,mat1Idx);
    get_random_value_for_2d_int16_t(row,col,mat2Idx);
    matrix_sub_scalar(row,col,depth,mat1Idx,mat2Idx,resIdx,iteration1);
    matrix_sub_optimized(row,col,depth,mat1Idx,mat2Idx,res2Idx,iteration2);
    validate_3d_int16_t(row,col,depth,resIdx,res2Idx);
    validate(iteration1,iteration2);
}