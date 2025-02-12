#include "opencv2/opencv.hpp"
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>
using namespace std;
using namespace cv;
using namespace c7x;
int main() {
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
    cout << "Image Dimensions: " << height << " x " << width << endl;
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            input[0][r][c] = (int)pixel[0];
            input[1][r][c] = (int)pixel[1];
            input[2][r][c] = (int)pixel[2];
        }
    }
    float *rIdx=&input[0][0][0];
    float *gIdx=&input[1][0][0];
    float *bIdx=&input[2][0][0];
    float *outIdx=&output[0][0];
    int times = (height * width) / 32;
    for(int t = 0;t < times;t++){
        float_vec vOutC = (float_vec)(0);
        float_vec R = (float_vec)(0.299);
        float_vec G = (float_vec)(0.587);
        float_vec B = (float_vec)(0.114);
        float_vec vE1 = *(float_vec *)rIdx;
        float_vec vE2 = *(float_vec *)gIdx;
        float_vec vE3 = *(float_vec *)bIdx;
        vOutC = (vE1*R) + (vE2*G) + (vE3*B);
        *(float_vec *) (outIdx) = vOutC;
        rIdx+=vec_len;
        gIdx+=vec_len;
        bIdx+=vec_len;
        outIdx+=vec_len;
    }
    // For remainng index values
    for(int idx = times * vec_len;idx < height*width;idx++){
        outIdx[idx - times * vec_len] = (rIdx[idx - times * vec_len] * 0.299) + (gIdx[idx - times * vec_len] * 0.587) + (bIdx[idx - times * vec_len] * 0.114);
    }
    Mat gray_image(height, width, CV_32F, output);  
    normalize(gray_image, gray_image, 0, 255, NORM_MINMAX);
    gray_image.convertTo(gray_image, CV_8U);
    imwrite("output.jpg", gray_image);
}

// http://www.codebind.com/cpp-tutorial/install-opencv-ubuntu-cpp/