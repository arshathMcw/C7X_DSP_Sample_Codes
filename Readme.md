# Hi All , In this repo i learned about C7x DSP code which have scalar,vectorization and intrinsics
## Scalar Addition
```cpp
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace c7x;
using namespace std;
#define ARRAY_SIZE (96)
int main(){
	cout<<"Scalar Addition : "<<endl;
	int16_t arr1[ARRAY_SIZE];
	int16_t arr2[ARRAY_SIZE];
	int16_t res[ARRAY_SIZE];
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		arr1[idx] = idx+1;
		arr2[idx] = idx+1;
	}
	cout<<"Input Array A : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr1[idx]<<" ";
	}
	cout<<"\nInput Array B : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr2[idx]<<" ";
	}
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		int16_t a = arr1[idx];
		int16_t b = arr2[idx];
		int16_t c = a + b;
		res[idx] = c;
	}
	cout<<"\nOutput Array C : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<res[idx]<<" ";
	}
	cout<<endl;
	return 0;
}

```
## Addition with the vector
```cpp
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace c7x;
using namespace std;
#define ARRAY_SIZE (96)
int main(){
	cout<<"Vector Addition : "<<endl;
	int16_t arr1[ARRAY_SIZE];
	int16_t arr2[ARRAY_SIZE];
	int16_t res[ARRAY_SIZE];
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		arr1[idx] = idx+1;
		arr2[idx] = idx+1;
	}
	cout<<"Input Array A : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr1[idx]<<" ";
	}
	cout<<"\n\nInput Array B : ";
	for(int8_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr2[idx]<<" ";
	}
	cout<<endl<<endl;
	int16_t *ptrArr1 = &arr1[0];
	int16_t *ptrArr2 = &arr2[0];
	int16_t *ptrRes = &res[0];
	int vectorLength = element_count_of<short_vec>::value;
	for(int idx = 0;idx < ARRAY_SIZE;idx +=vectorLength){
		short_vec arr1Val = *(short_vec *)(ptrArr1 + idx);
		short_vec arr2Val = *(short_vec *)(ptrArr2 + idx);
		short_vec result = arr1Val + arr2Val;
		*(short_vec *)(ptrRes + idx) = result;
		result.print();
	}
	return 0;
}
```
## Scalar Subtraction
```cpp
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace c7x;
using namespace std;
#define ARRAY_SIZE (96)
int main(){
	cout<<"Scalar Subtraction"<<endl;
	int16_t arr1[ARRAY_SIZE];
	int16_t arr2[ARRAY_SIZE];
	int16_t res[ARRAY_SIZE];
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		arr1[idx] = idx+1;
		arr2[idx] = (idx+1) * -1;
	}
	cout<<"Input Array A : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr1[idx]<<" ";
	}
	cout<<"\n\nInput Array B : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr2[idx]<<" ";
	}
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		int16_t a = arr1[idx];
		int16_t b = arr2[idx];
		int16_t c = a - b;
		res[idx] = c;
	}
	cout<<"\n\nOutput Array C : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<res[idx]<<" ";
	}
	cout<<endl;
	return 0;
}
```
## Vector Subtraction
```cpp
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace c7x;
using namespace std;
#define ARRAY_SIZE (96)
int main(){
	cout<<"Vector Subtraction"<<endl;
	int16_t arr1[ARRAY_SIZE];
	int16_t arr2[ARRAY_SIZE];
	int16_t res[ARRAY_SIZE];
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		arr1[idx] = idx+1;
		arr2[idx] = (idx+1) * -1;
	}
	cout<<"Input Array A : ";
	for(int16_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr1[idx]<<" ";
	}
	cout<<"\n\nInput Array B : ";
	for(int8_t idx = 0;idx < ARRAY_SIZE;idx++){
		cout<<arr2[idx]<<" ";
	}
	cout<<endl<<endl;
	int16_t *ptrArr1 = &arr1[0];
	int16_t *ptrArr2 = &arr2[0];
	int16_t *ptrRes = &res[0];
	int vectorLength = element_count_of<short_vec>::value;
	for(int idx = 0;idx < ARRAY_SIZE;idx +=vectorLength){
		short_vec arr1Val = *(short_vec *)(ptrArr1 + idx);
		short_vec arr2Val = *(short_vec *)(ptrArr2 + idx);
		short_vec result = arr1Val - arr2Val;
		*(short_vec *)(ptrRes + idx) = result;
		result.print();
	}
	return 0;
}
```
## Matrix Multiplication using Vectorization
```cpp
int main(){
    int rsize = 32;
    int csize = 32;
    vector<vector<int16_t>> mat1(rsize,vector<int16_t>(csize,0));
    vector<vector<int16_t>> mat2(rsize,vector<int16_t>(csize,0));
    vector<vector<int16_t>> res(rsize,vector<int16_t>(csize,0)),res2(rsize,vector<int16_t>(csize,0));
    int32_t val = 0;
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
        }
        vOutC.print();
    }
    

    cout<<dec;
}
```
## Other Vectorization and intrinsics codes
* 1D FIR Operation : [click here](./1D_FIR.cpp)
* Matrix Addition : [click here](./matrix_addition.cpp)
* 3D Matrix Addition : [click here](./3d_matrix_addition.cpp)
* Matrix Subtraction : [click here](./matrix_subtraction.cpp)
* 3D Matrix Subtraction : [click here](./3d_matrix_subtraction.cpp)
* Matrix Multiplication : [click here](./matrix_multiplication.cpp)
* RGB to GrayScale : [click here](./rgb_to_grayscale.cpp)
* Brightness Conversion : [click here](./brightness.cpp )