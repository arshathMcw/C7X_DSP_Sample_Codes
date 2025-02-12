#include "opencv2/opencv.hpp"
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace std;
using namespace cv;
using namespace c7x;
int main() {
    cout<<"RGB To Gray Scale Conversion using Intrinsics"<<endl;
    Mat image = imread("image.jpg");
    if (image.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }
    const int vec_len = element_count_of<float_vec>::value;
    int channel = 3;
    int height = image.rows;
    int width = image.cols;
    float input[channel][height][width];
    float output[height][width];
    cout << "Image Dimensions: " <<channel<<" x "<< height << " x " << width << endl;
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            input[0][r][c] = (int)pixel[0];
            input[1][r][c] = (int)pixel[1];
            input[2][r][c] = (int)pixel[2];
        }
    }
    // transparency - alpha
    //  brightness - r+b , g+b , b+b
    int iteration = 0;
    float *rIdx=&input[0][0][0],*gIdx=&input[1][0][0],*bIdx=&input[2][0][0],*outIdx=&output[0][0];
    int times = (height * width) / vec_len;
    float_vec R = (float_vec)(0.299),G = (float_vec)(0.587),B = (float_vec)(0.114);
    for(int t = 0;t < times;t++,rIdx+=vec_len,gIdx+=vec_len,bIdx+=vec_len,outIdx+=vec_len,iteration++){
        // R*0.299 + G*0.587 + B*0.114
        float_vec res = __vaddsp_vvv(__vmpysp_vvv(R,*(float_vec *)rIdx), __vmpysp_vvv(G,*(float_vec *)gIdx));
        res = __vaddsp_vvv(res,__vmpysp_vvv(B,*(float_vec *)bIdx));
        *(float_vec *) (outIdx) = res;
    }
    for(int idx = times * vec_len;idx < height*width;idx++){
        outIdx[idx - times * vec_len] = (rIdx[idx - times * vec_len] * 0.299) + (gIdx[idx - times * vec_len] * 0.587) + (bIdx[idx - times * vec_len] * 0.114);
        iteration++;
    }
    cout << "Output Dimensions: "<< height << " x " << width << endl;
    Mat gray_image(height, width, CV_32F, output);  
    gray_image.convertTo(gray_image, CV_8U);
    imwrite("output.jpg", gray_image);
    cout<<"Iteration : "<<iteration<<endl;
}

// http://www.codebind.com/cpp-tutorial/install-opencv-ubuntu-cpp/

