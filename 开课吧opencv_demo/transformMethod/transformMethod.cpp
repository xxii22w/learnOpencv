#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat srcImg = imread("../cat.jpg");
    resize(srcImg, srcImg, Size(800, 600));
    Mat grayImg;
    cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);

    // 线性函数变换
    float k = 1.2;
    int b = 20;

    Mat outPut(grayImg.size(), grayImg.type());
    for (int i = 0; i < grayImg.rows; i++)
    {
        for (int j = 0; j < grayImg.cols; j++)
        {
            // 如果是对比度拉伸技术，就是在这里多个函数控制
            outPut.at<uchar>(i, j) = grayImg.ptr<uchar>(i)[j] * k + b;
        }
    }

    // 对数函数变换
    Mat LogOutPutImg = Mat::zeros(grayImg.size(), grayImg.type());
    grayImg.convertTo(LogOutPutImg, CV_32F);
    LogOutPutImg = LogOutPutImg + 1;            // 在进行对数变换之前，将图像中的所有像素值加
    log(LogOutPutImg, LogOutPutImg);    
    LogOutPutImg = LogOutPutImg * 1.3;          // 对得到的对数图像进行缩放，乘以1.3。这是为了增强对比度
    // NORM_MINMAX参数确保了像素值的最小值被映射到新的区间最小值（这里是0），最大值映射到新的区间最大值（这里是255）
    normalize(LogOutPutImg, LogOutPutImg, 0, 255, NORM_MINMAX);     // 将对数变换并缩放后的图像像素值重新映射到0到255的范围内
    // 将浮点型的图像转换回8位无符号整型，并取绝对值，以确保所有像素值非负且适合大多数图像显示和处理的需要
    convertScaleAbs(LogOutPutImg, LogOutPutImg);

    // gama矫正
    Mat gammaOutPutImg = grayImg.clone();
    float gammaValue = 3;
    uchar LUT[256] = { 0 };
    for (int i = 0; i < 256; i++)
    {
        LUT[i] = pow((i / 255.0), gammaValue) * 255.0;
    }
    MatIterator_<uchar> ite = gammaOutPutImg.begin<uchar>();
    MatIterator_<uchar> iteEnd = gammaOutPutImg.end<uchar>();
    for (; ite != iteEnd; ite++)
    {
        *ite = LUT[(*ite)];
    }


    // 灰度比特平面显示
    Mat bitsOutPutImg[8];
    for (int i = 0; i < 8; i++)
    {
        bitsOutPutImg[i] = grayImg.clone();
    }

    for (int n = 1; n <= 8; n++)
    {
        for (int i = 0; i < grayImg.rows; i++)
        {
            uchar* ptrSrc = grayImg.ptr<uchar>(i);
            uchar* ptrResult = bitsOutPutImg[n - 1].ptr<uchar>(i);
            for (int j = 0; j < grayImg.cols; j++)
            {
                if (ptrSrc[j] >= pow(2, n - 1) && ptrSrc[j] < pow(2, n))
                {
                    ptrResult[j] = 255;
                }
                else
                {
                    ptrResult[j] = 0;
                }
            }
        }
    }

    for (int n = 0; n < 8; n++)
    {
        imshow("level" + to_string(n + 1), bitsOutPutImg[n]);
    }

    //imshow("grayImg", grayImg);
    //imshow("outPut", outPut);
    //imshow("logOutPut", LogOutPutImg);
    //imshow("gammaOut", gammaOutPutImg);
    waitKey(0);
    return 0;
}


