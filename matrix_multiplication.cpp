/*
To run
cd scripts
./mat_mul.sh
*/
#include "utils.h"
int main(){
    //  col 1 and row2 need to be same :)
    int row1,col1,row2,col2,vec_len = element_count_of<int_vec>::value,iteration1, iteration2;
    cout<<"Enter the Row Size for Matrix 1 : ";
    cin>>row1;
    cout<<"Enter the Column Size for Matrix 1 : ";
    cin>>col1;
    cout<<"Enter the Row Size for Matrix 2 : ";
    cin>>row2;
    cout<<"Enter the Column Size for Matrix 2 : ";
    cin>>col2;
    if(row2 != col1){
        cout<<"This is not a valid matrix to do multiplication";
        return 0;
    }
    int32_t mat1[row1][col1],mat2[row2][col2],res[row1][col2],res2[row1][col2] ,*mat1Idx=&mat1[0][0],*mat2Idx=&mat2[0][0],*res2Idx=&res2[0][0];
    for(int r = 0;r < row1;r++){
        for(int c =0;c < col1;c++){
            mat1[r][c] =  r+c;
        }
    }
    for(int r = 0;r < row2;r++){
        for(int c =0;c < col2;c++){
            mat2[r][c] =  r+c;
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
    int rem = col2 % vec_len;
    int start = col2 - rem;
    for(int r = 0;r < row1;r++){
        mat2Idx = &mat2[0][0];
        res2Idx = &res2[r][0];
        for(int c = 0;c+vec_len <= col2;c+=vec_len){
            int_vec vOutC = (int_vec)(0);
            mat2Idx = &mat2[0][c];
            for(int cc = 0;cc < col1;cc+=1){
                int_vec resw = __vmpyww_vvv(*(int_vec *)mat2Idx,(int_vec)(mat1[r][cc]));
                vOutC = __vaddw_vvv(vOutC,resw);
                iteration2++;
                mat2Idx = &mat2[cc+1][c];
            }
            *(int_vec *) (res2Idx) = vOutC;
            res2Idx += vec_len;
        }
        //  For Remaining Index
        for(int x = start;x < col2;x++){
            for(int k = 0;k < col1;k++){
                res2[r][x] += mat1[r][k] * mat2[k][x];
                iteration1++;   
            }
        }
    }
    for(int r = 0;r < row1;r++){
        for(int c = 0;c < col2;c++){
            if(res[r][c] != res2[r][c]) {     
                cout<<"They are not equal"<<endl;
            }
        }
    }
    cout<<"Iteration 1 : "<<iteration1<<endl;
    cout<<"Iteration 2 : "<<iteration2<<endl;
    cout<<"Intrinsics Code is "<<(iteration1/iteration2)<<" times better than Scalar Code"<<endl;
}