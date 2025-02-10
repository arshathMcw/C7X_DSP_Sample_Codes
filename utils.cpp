#include "utils.h"
void get_random_value_for_2d_int16_t(int row,int col,int16_t *mIdx){
	for(int idx = 0;idx < row * col;idx++){
		*(mIdx + idx) = rand()/1000000000;
	}
}
void get_random_value_for_3d_int16_t(int row,int col,int depth,int16_t *mIdx){
	for(int idx = 0;idx < row * col * depth;idx++){
		*(mIdx + idx) = rand()/1000000000;
	}
}
void validate(int iteration,int iteration2){
    cout<<"Iteration Count for Scalar : "<<iteration<<endl;
	cout<<"Iteration Count for Vector : "<<iteration2<<endl;
    int times = iteration / iteration2;
	cout<<"Vector Operation is "<<times<<" times faster than the Scalar"<<endl;
}
void validate_2d_int16_t(int row,int col,int16_t *res1Idx,int16_t *res2Idx){
	for(int idx = 0;idx < row * col;idx++){
		if(*(res1Idx + idx) != *(res2Idx + idx)){
			cout<<"Both Not Same"<<endl;
			return;
		}
	}
	cout<<"Both Matrix Are same"<<endl;
}

void validate_3d_int16_t(int row,int col,int depth,int16_t *res1Idx,int16_t *res2Idx){
	for(int idx = 0;idx < row * col * depth;idx++){
		if(*(res1Idx + idx) != *(res2Idx + idx)){
			cout<<"Both Not Same"<<endl;
			return;
		}
	}
	cout<<"Both Matrix Are same"<<endl;
}
