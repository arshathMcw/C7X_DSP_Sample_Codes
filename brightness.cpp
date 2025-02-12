#include "opencv2/opencv.hpp"
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace std;
using namespace cv;
using namespace c7x;
int main() {
    Mat image = imread("image.png");
    if (image.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }
    int height = image.rows,width = image.cols,channel = 3,iteration = 0;
    const int vec_len = element_count_of<float_vec>::value;
    float input[channel][height][width],output[channel][height][width]; 
    cout << "Image Dimensions: " << channel << " x " << height << " x " << width << endl;
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            input[0][r][c] = pixel[2] / 255.0f; 
            input[1][r][c] = pixel[1] / 255.0f; 
            input[2][r][c] = pixel[0] / 255.0f; 
        }
    }
    float *rIdx=&input[0][0][0],*gIdx=&input[1][0][0],*bIdx=&input[2][0][0],*rOut=&output[0][0][0],*gOut=&output[1][0][0],*bOut=&output[2][0][0];
    int times = (height * width) / vec_len;
    float_vec R = (float_vec)(2.9),G = (float_vec)(20.587),B = (float_vec)(0.114);
    for(int t = 0;t < times;t++,rIdx+=vec_len,gIdx+=vec_len,bIdx+=vec_len,gOut+=vec_len,rOut+=vec_len,bOut+=vec_len,iteration++){
        float_vec res1 = __vaddsp_vvv(R,*(float_vec *)rIdx);
        float_vec res2 = __vaddsp_vvv(G,*(float_vec *)gIdx);
        float_vec res3 = __vaddsp_vvv(B,*(float_vec *)bIdx);
        *(float_vec *) (rOut) = res1;
        *(float_vec *) (gOut) = res2;
        *(float_vec *) (bOut) = res3;
        res1.print();
    }
    // for(int idx = times * vec_len;idx < height*width;idx++){
    //     outIdx[idx - times * vec_len] = (rIdx[idx - times * vec_len] * 0.299) + (gIdx[idx - times * vec_len] * 0.587) + (bIdx[idx - times * vec_len] * 0.114);
    //     iteration++;
    // }
    // for (int r = 0; r < height; r++) {
    //     for (int c = 0; c < width; c++) {
    //         input[0][r][c]+=0.1;
    //         input[1][r][c]+=0.2;
    //         input[2][r][c]+=0.4;
    //         iteration++;
    //     }
    // }


    Mat image2(height, width, CV_32FC3);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image2.at<Vec3f>(i, j) = Vec3f(input[2][i][j], input[1][i][j], input[0][i][j]); // BGR Order
        }
    }
    Mat image8bit;
    image2.convertTo(image8bit, CV_8UC3, 255.0);
    imwrite("output.jpg", image8bit);
    cout<<"Iteration : "<<iteration<<endl;
    return 0;
}