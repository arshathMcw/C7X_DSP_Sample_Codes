#include "utils.h"
void get_random_value_for_2d_int16_t(int row,int col,vector<vector<int16_t>>& mat){
    for(int r = 0;r < row;r++){
        for(int c = 0;c < col;c++){
            mat[r][c] = rand()/100000000;
        }
    }
}
void validate(int iteration,int iteration2){
    cout<<"Iteration Count for Scalar : "<<iteration<<endl;
	cout<<"Iteration Count for Vector : "<<iteration2<<endl;
    int times = iteration / iteration2;
	cout<<"Vector Operation is "<<times<<" times faster than the Scalar"<<endl;
}
void validate_2d_int16_t(int row,int col,vector<vector<int16_t>> mat1,vector<vector<int16_t>> mat2){
    for(int r = 0;r < row;r++){
		for(int c = 0;c < col;c++){
			if(mat1[r][c] != mat2[r][c]) {
				cout<<"Both Not Same"<<endl;
				return;
			}
		}
	}
	cout<<"Both Matrix Are same"<<endl;
}
