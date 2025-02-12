#include<iostream>
#include<c7x.h>
#include<c7x_scalable.h>
using namespace std;
using namespace c7x;
void cmpGt(){
    long_vec vA, vB;
    __vpred vpC;
    vA = (long_vec) {1,2,3,4,5,6,7,8};
    vB = (long_vec) {0,1,2,3,4,5,6,9};
    cout << "vA = ";
    vA.print();
    cout << "vB = ";
    vB.print();
    vpC = __cmp_gt_pred(vA, vB);
    cout << "vpC = ";
    cout << std::dec;
    vpC.print();
}
void shuffle(){
    uint_vec vA, vB, vC, vD, vE;
    for(int32_t ctr = 0; ctr < 16; ctr++)
        vA.s[ctr] = ctr;
    vA.print();
    vB = __shuffle_stride2(vA);
    vB.print();
    vC = __shuffle_stride2_low_low(vA, vB);
    vC.print();
    vD = __shuffle_stride2_high_high(vA,vB);
    vD.print();
}
void permutate(){
    int_vec vA, vB, vC, vD, vE;
    uchar_vec vTemp;
    uchar_vec vMask;
    for(int32_t ctr = 0; ctr < 16; ctr ++) {
        vA.s[ctr] = ctr - 8;
    }
    for(int32_t ctr = 0; ctr < 16; ctr ++) {
        vB.s[ctr] = (ctr - 8) * 10;
    }
    cout << "vA = ";
    vA.print();
    cout << "vB = ";
    vB.print();
    uint8_t mask[64] = {
        60, 61, 62, 63,  
        56, 57, 58, 59,  
        52, 53, 54, 55,  
        48, 49, 50, 51,  
        44, 45, 46, 47,  
        40, 41, 42, 43,  
        36, 37, 38, 39,  
        32, 33, 34, 35,  
        28, 29, 30, 31,  
        24, 25, 26, 27,  
        20, 21, 22, 23,  
        16, 17, 18, 19,  
        12, 13, 14, 15,  
        8,  9, 10, 11,  
        4,  5,  6,  7,  
        0,  1,  2,  3   
    };
    vMask = *((uchar64_ptr)&mask[0]);
    vTemp = __permute(vMask, __as_uchar64(vA));
    vC = __as_int16(vTemp);
    cout << "vC = ";
    vC.print();
    vTemp = __permute(vMask, __as_uchar64(vB));
    vD = __as_int16(vTemp);
    cout << "vD = ";
    vD.print();
    vTemp = __permute_even_odd_int(vMask, __as_uchar64(vB), __as_uchar64(vA));
    vE = __as_int16(vTemp);
    cout << "vE = ";
    vE.print();
}
void sorting(){
    float_vec vA, vB, vC;
    for(int32_t ctr = 0; ctr < 16; ctr++) {
        vA.s[ctr] = (rand() % 16) * 1.1f;
    }
    cout << "vA = ";
    vA.print();
    vB = __sort_asc(vA);
    cout<< "vB = ";
    vB.print();
    vC = __sort_desc(vA);
    cout<< "vC = ";
    vC.print();
}
void mat_mul(){
    float_vec vA;
    float_vec vB0, vB1;
    float_vec vC0, vC1;
    float_vec vC;
    vA = (float_vec)(0.1);
    cout << "vA = ";
    vA.print();
    for(int32_t i = 0; i < 16;  i++) {
        vB0.s[i] = (i + 1) + 0.2;
        vB1.s[i] = (i + 1) + 0.3;
    }
    cout << "vB0 = ";
    vB0.print();
    cout << "vB1 = ";
    vB1.print();
    __vmatmpysp_vww(vA, vB0, vB1, vC0, vC1);
    cout<< "Partial outputs = \n";
    cout << "vC0 = ";
    vC0.print();
    cout << "vC1 = ";
    vC1.print();
    vC = vC0 + vC1;
    cout<< "\nFinal outputs = \n";
    cout << "vC = ";
    vC.print();
}
void predicate(){
    char_vec vA;
    vpred vpA;
    vpA = vpred(0xFF00FF00FF00FF);
    vA = __expand(vpA);
    cout <<    hex;
    cout << "vpA = ";
    vpA.print();
    cout <<    dec;
    cout << "vA = ";
    vA.print();
}
int main(){
    // cmpGt();
    // shuffle();
    // permutate();
    // sorting();
    // mat_mul();
    predicate();
}