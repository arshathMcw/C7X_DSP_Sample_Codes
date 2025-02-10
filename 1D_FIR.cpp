#include "utils.h"
#define INPUT_SIZE (96)
#define COEFF_SIZE (4)
#define OUTPUT_SIZE (INPUT_SIZE - COEFF_SIZE + 1)
int main(){
    int16_t inArray[INPUT_SIZE];
    int16_t coeffArray[COEFF_SIZE];
    for(int32_t ctr = 0; ctr < INPUT_SIZE; ctr++) {
        inArray[ctr] = ctr;
    }
    for(int32_t ctr = 0; ctr < COEFF_SIZE; ctr++) {
        coeffArray[ctr] = ctr + 1;
    }
    cout << "input array = ";
    for(int32_t ctr = 0; ctr < INPUT_SIZE; ctr++) {
        cout << inArray[ctr] << ", ";
    }
    cout << "\n\n";
    cout << "coeff array = ";
    for(int32_t ctr = 0; ctr < COEFF_SIZE; ctr++) {
        cout << coeffArray[ctr] << ", ";
    }
    int16_t outArray[INPUT_SIZE];
    for(int32_t ctr = 0; ctr < OUTPUT_SIZE; ctr++) {
        outArray[ctr] = 0;
    }
    int16_t *pIn    = &inArray[0];    
    int16_t *pCoeff = &coeffArray[0]; 
    int16_t *pOut   = &outArray[0];   
    int32_t itr = 0;
    const int vec_len = element_count_of<short_vec>::value;
    for(int32_t j = 0; j < OUTPUT_SIZE; j+= vec_len) {
        short_vec vOut = (short_vec)(0);
        for(int32_t i = 0; i < COEFF_SIZE; i++) {
            cout << " Iteration: " << itr++ ;
            cout << " Coeff: "<< i << "\n";
            short_vec vIn = *(short_vec *)(pIn + j + i);
            short_vec vCoeff = short_vec(pCoeff[i]);
            vOut += (vIn * vCoeff);
            cout << "vIn    = ";
            vIn.print();
            cout << "vCoeff = ";
            vCoeff.print();
            cout << "vOut   = ";
            vOut.print();
            cout << "\n\n";
        }
        cout<<"vOut after accumulation = ";
        vOut.print();
        cout<<endl;
        *(short_vec *)(pOut + j) = vOut;
    }
    cout << "output array = ";
    for(int32_t ctr = 0; ctr < OUTPUT_SIZE; ctr++) {
        cout << outArray[ctr] << ", ";
    }
}