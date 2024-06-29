#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat srcImg = imread("../house.jpg");

    Mat outImg;
    // 定义结构元（卷积核，掩码）
    // 矩形 交叉 椭圆 三种结构元
    Mat structEle = getStructuringElement(MORPH_RECT, Size(15, 15));

    Mat binaryImg;
    cvtColor(srcImg, binaryImg, COLOR_RGB2GRAY);
    threshold(binaryImg, binaryImg, 0, 255, THRESH_BINARY | THRESH_OTSU);


    // 进行腐蚀操作
    // erode(srcImg, outImg, structEle);

    // 进行膨胀操作
    // dilate(srcImg, outImg, structEle);

    /*
        形态学操作函数
        MORPH_ERODE    = 0  腐蚀
        MORPH_DILATE   = 1  膨胀
        MORPH_OPEN     = 2  开运算
        MORPH_CLOSE    = 3  闭运算
        MORPH_GRADIENT = 4  形态学梯度
        MORPH_TOPHAT   = 5  顶帽
        MORPH_BLACKHAT = 6  黑帽
        MORPH_HITMISS  = 7  击中不击中
    */
    Mat openImg;
    morphologyEx(srcImg, openImg,MORPH_OPEN,structEle);

    Mat closeImg;
    morphologyEx(srcImg, closeImg, MORPH_CLOSE, structEle);

    Mat gradImg;
    morphologyEx(srcImg, gradImg, MORPH_GRADIENT, structEle);

    Mat topHatImg;
    morphologyEx(srcImg, topHatImg, MORPH_TOPHAT, structEle);

    Mat blackHatImg;
    morphologyEx(srcImg, blackHatImg, MORPH_BLACKHAT, structEle);

    Mat hitMissImg;
    morphologyEx(binaryImg, hitMissImg, MORPH_HITMISS, structEle);


    imshow("srcImg", srcImg);
    imshow("openImg", openImg);
    imshow("closeImg", closeImg);
    imshow("gradImg", gradImg);
    imshow("topHatImg", topHatImg);
    imshow("blackHatImg", blackHatImg);
    imshow("hitMissImg", hitMissImg);


    waitKey(0);
    return 0;
}

