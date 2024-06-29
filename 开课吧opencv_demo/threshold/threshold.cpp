#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*
    固定阈值，进行全局阈值处理，针对亮暗区分明显的使用方法
    自适应阈值，前后景区分不明显，获取轮廓的方式
    双阈值化，通过大小阈值的两次操作，找到图片中的关键信息
    半阈值化，主要用于拿到图片中的诸如文字等特征明显的信息

*/

int main()
{
    Mat srcImg = imread("./1.jpg", IMREAD_GRAYSCALE);
    // 根据填写阈值进行处理，根据输入的type类型进行阈值处理
    Mat resultImg;
    /*
    *   THRESH_BINARY       二值化，超过阈值，保留为白色
        THRESH_BINARY_INV   反二值化，与上面想法
        THRESH_TRUNC        超过阈值的部分，保留到阈值
        THRESH_TOZERO       不足阈值的部分，请0，超过阈值的部分保留
        THRESH_TOZERO_INV   不足阈值的保留，超过，清0
        THRESH_MASK       
        THRESH_OTSU         是否使用otsu方法
        THRESH_TRIANGLE   
    */
    threshold(srcImg, resultImg, 138, 255, THRESH_TOZERO | THRESH_OTSU);

    Mat adaResult;
    /*
    * 自适应阈值化
    * ADAPTIVE_THRESH_MEAN_C    平均计算
    * ADAPTIVE_THRESH_GAUSSIAN_C 高斯算法，计算当前值距离，通过高斯方差拿到结果
    */
    adaptiveThreshold(srcImg, adaResult, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);


    imshow("src", srcImg);
    imshow("result", resultImg);
    imshow("adaResult", adaResult);
    waitKey(0);
    return 0;
}
