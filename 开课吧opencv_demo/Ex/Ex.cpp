#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

// 将彩图转为灰度图
int main()
{
    Mat RGBImage = imread("./leifengtower.jpg");

    int width = RGBImage.cols;
    int height = RGBImage.rows;
    //创建一张单通道的灰度图像
    Mat imageGray(height,width,CV_8UC1);
    //取出存储图像像素的数组的指针
    uchar* pointImage = RGBImage.data;
    uchar* pointImageGray = imageGray.data;
    //取出图像每行所占的字节数
    size_t stepImage = RGBImage.step;
    size_t stepImageGray = imageGray.step;


    // 遍历每一个像素点
    for (int x = 0; x < imageGray.rows; x++) {
        for (int y = 0; y < imageGray.cols; y++) {
            pointImageGray[x * stepImageGray + y] =
                (uchar)(0.144 * pointImage[x * stepImage + 3 * y] +
                    0.587 * pointImage[x * stepImage + 3 * y + 1] +
                    0.299 * pointImage[x * stepImage + 3 * y + 2]);
        }
    }
    
    imshow("RGBImage", RGBImage);
    imshow("grayImage", imageGray);
    waitKey(0);
    return  0;
}
