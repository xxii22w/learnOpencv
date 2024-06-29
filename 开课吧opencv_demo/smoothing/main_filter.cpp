#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int main1()
{
    // 读取图片
    Mat srcImg = imread("./house.jpg");
    // 创建卷积核 掩码 如果是在滤波当中选择，一般使用3 5 7
    Mat kernel = (Mat_<double>(3,3) << 
        -2, 0, 2,
        -2, 0, 2,
        -2, 0, 2);

    // 进行卷积处理
    Mat resultImg;
    // opencv提供了一个卷积处理函数filter2D
    filter2D(srcImg, resultImg, srcImg.depth(), kernel);

    imshow("srcImg", srcImg);
    imshow("result", resultImg);
    waitKey(0);
    return 0;
}

