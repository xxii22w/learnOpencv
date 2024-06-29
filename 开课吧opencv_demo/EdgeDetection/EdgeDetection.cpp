#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main1()
{
    Mat srcImg = imread("../2.jpg");
    imshow("srcImg", srcImg);

#if 0 //sobel算子
    Mat sobelX, sobelY,sobelAll;
    Sobel(srcImg, sobelX, CV_8U, 1, 0, 3, 1, 1, BORDER_DEFAULT);
    imshow("sobelX", sobelX);

    Sobel(srcImg, sobelY, CV_8U, 0, 1, 3, 1, 1, BORDER_DEFAULT);
    imshow("sobelY", sobelY);

    Sobel(srcImg, sobelAll, CV_8U, 1, 1, 3, 1, 1, BORDER_DEFAULT);
    imshow("sobelAll", sobelAll);

    Mat sobelOut;
    addWeighted(sobelX, 0.5, sobelY, 0.5, 0, sobelOut);
    imshow("sobelOut", sobelOut);
#endif

#if 0 // laplacian算子
    // 常规化操作中，会加上一层高斯滤波
    Mat gaussianTemp;
    GaussianBlur(srcImg, gaussianTemp, Size(5, 5), 0);

    Mat laplacianTemp;
    Laplacian(gaussianTemp, laplacianTemp, CV_16S, 3);
    Mat laplacianOut;
    convertScaleAbs(laplacianTemp, laplacianOut);
    imshow("laplacianOut", laplacianOut);

#endif

#if 1 // canny滤波
    Mat grayImg;
    // 灰度转换
    cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);

    blur(grayImg, grayImg, Size(5, 5));

    Mat cannyOut;
    // 一般一次阈值和二次阈值的比值是3：1或2：1
    Canny(grayImg, cannyOut, 9, 3);
    imshow("cannyOut", cannyOut);

#endif


    waitKey(0);
    return 0;
}

