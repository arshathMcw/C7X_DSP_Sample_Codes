#include "utils.h"
void matrix_subtraction(int row,int col,vector<vector<int16_t>> mat1,vector<vector<int16_t>> mat2){
	int iteration1 = 0,iteration2 = 0;
    vector<vector<int16_t>> res(row,vector<int16_t>(col,0));
    vector<vector<int16_t>> res2(row,vector<int16_t>(col,0));
	for(int r = 0;r < row;r++){
        for(int c =0;c < col;c++){
			res[r][c] = 0;
			res2[r][c] = 0;
        }
    }
	for(int r = 0;r < row;r++){
        for(int c =0;c < col;c++){
			iteration1++;
            res[r][c] += mat1[r][c] - mat2[r][c];
        }
    }
	int16_t *rIdx=&res2[0][0];
	int rem = col % 32;
	int chcol = col - rem;
    for(int r = 0;r < row;r++){
        rIdx=&res2[r][0];
        short_vec vOutC = (short_vec)(0);
        for(int c = 0;c < col;c+=32){
            if(c + 32 > col) {
                for(int c = chcol;c < col;c++){
					res2[r][c] = mat1[r][c] - mat2[r][c];
					iteration2++;
				}
				break;
            }
            int16_t *m1Vec = &mat1[r][c];
            int16_t *m2Vec = &mat2[r][c];
			short_vec vE1 = *(short_vec *)m1Vec;
			short_vec vE2 = *(short_vec *)m2Vec;
            vOutC = vE1 - vE2;
			*(short_vec *) (rIdx + c) = vOutC;
			iteration2++;
        }
    }
    validate_2d_int16_t(row,col,res,res2);
	validate(iteration1,iteration2);
}
int main(){
	int row,col;
    cout<<"Enter Row Size : ";
    cin>>row;
    cout<<"Enter Column Size : ";
    cin>>col;
    vector<vector<int16_t>> mat1(row,vector<int16_t>(col,0));
    vector<vector<int16_t>> mat2(row,vector<int16_t>(col,0));	
    get_random_value_for_2d_int16_t(row,col,mat1);
    get_random_value_for_2d_int16_t(row,col,mat2);
	matrix_subtraction(row,col,mat1,mat2);
}