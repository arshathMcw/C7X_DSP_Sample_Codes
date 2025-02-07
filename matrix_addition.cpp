#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace c7x;
using namespace std;
void matrix_addition(int row,int col,vector<vector<int16_t>> mat1,vector<vector<int16_t>> mat2){
	int iteration1 = 0,iteration2 = 0;
	int16_t res[row][col],res2[row][col];
	for(int r = 0;r < row;r++){
        for(int c =0;c < col;c++){
			res[r][c] = 0;
			res2[r][c] = 0;
        }
    }
	for(int r = 0;r < row;r++){
        for(int c =0;c < col;c++){
			iteration1++;
            res[r][c] += mat1[r][c] + mat2[r][c];
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
					res2[r][c] = mat1[r][c] + mat2[r][c];
					iteration2++;
				}
				break;
            }
            int16_t *m1Vec = &mat1[r][c];
            int16_t *m2Vec = &mat2[r][c];
			short_vec vE1 = *(short_vec *)m1Vec;
			short_vec vE2 = *(short_vec *)m2Vec;
            vOutC = vE1 + vE2;
			*(short_vec *) (rIdx + c) = vOutC;
			iteration2++;
        }
    }
    for(int r = 0;r < row;r++){
		for(int c = 0;c < col;c++){
			if(res[r][c] != res2[r][c]) {
				cout<<"Both Not Same"<<endl;
				return;
			}
		}
	}
	cout<<"Both Matrix Are same"<<endl;
	cout<<"Iteration Count for Scalar : "<<iteration1<<endl;
	cout<<"Iteration Count for Vector : "<<iteration2<<endl;
	int times = iteration1 / iteration2;
	cout<<"Vector Operation is "<<times<<" times faster than the Scalar"<<endl;
}
int main(){
	int row = 1000,col = 1000;
    vector<vector<int16_t>> mat1(row,vector<int16_t>(col,0));
    vector<vector<int16_t>> mat2(row,vector<int16_t>(col,0));	
    int32_t val = 0;
    for(int r = 0;r < row;r++){
        val++;
        for(int c =0;c < col;c++){
            mat1[r][c] =  val;
        }
    }
	val = 0;
	for(int r = 0;r < row;r++){
        val++;
        for(int c =0;c < col;c++){
            mat2[r][c] =  val;
        }
    }
	
	matrix_addition(row,col,mat1,mat2);
}