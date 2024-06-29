#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

Mat histOutImage(Mat hist)
{
    Mat histOutputImg(256, 256, CV_8U, Scalar(255));
    double maxVaule;
    double minValue;
    minMaxLoc(hist, &minValue, &maxVaule);
    int hpt = 0.9 * 256;        // 百分之90 用来放大直方图
    for (int i = 0; i < 256; i++)
    {
        float binVal = hist.at<float>(i);
        int temp = (binVal * hpt / maxVaule);
        line(histOutputImg, Point(i, 256), Point(i, 256 - temp), Scalar::all(0));
    }
    return histOutputImg;
}

int main()
{
    // 灰度图  H-S直方图 RGB 直方图
    Mat srcImg = imread("../cat.jpg");
    resize(srcImg, srcImg, Size(600, 600));

    Mat grayImg;
    cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
    // 计算直方图信息
    /*
        void calcHist( const Mat* images, int nimages,
                         const int* channels, InputArray mask,
                         SparseMat& hist, int dims,
                         const int* histSize, const float** ranges,
                         bool uniform = true, bool accumulate = false );
        images     输入的图片组：图片需要拥有相同的大小，相同的颜色深度
        nimages    图像的个数
        channels   需要计算的直方图的通道个数
        mask       可选的掩码，一半不使用时设置为空。掩码图片必须和输入的图片组大小相同。
        hist       输出的直方图信息
        dims       直方图的维数
        histSize   直方图维度大小
        ranges     直方图统计的范围
        uniform    是否进行归一化处理
        accumulate 累计操作，默认不需要
    */

    int channels[1] = { 0 };
    Mat hist;
    int histSize[1] = { 256 };
    float hrange[2] = { 0,255 };
    const float *ranges[1] = { hrange };
    calcHist(&grayImg, 1, channels, Mat(), hist, 1, histSize, ranges);
    // 绘制直方图

    // 直方图均衡化 将过亮或过暗的图片通过均衡化，细节暴露出来
    Mat equalizeOutImg;
    equalizeHist(grayImg, equalizeOutImg);

    Mat outHist;
    calcHist(&equalizeOutImg, 1, channels, Mat(), outHist, 1, histSize, ranges);

    // 彩色图均衡化处理
    Mat colorImg;
    vector<Mat> BGR_channels;
    split(srcImg, BGR_channels);    // 将输入的彩色图像srcImg分离成三个独立的单通道图像（B、G、R），并将它们存储在BGR_channels这个vector中
    for (unsigned long i = 0; i < BGR_channels.size(); i++)
    {
        equalizeHist(BGR_channels[i], BGR_channels[i]);
    }

    merge(BGR_channels, colorImg);

    // 直方图匹配
    Mat newSrcImg = imread("../sky.jpg");
    resize(newSrcImg, newSrcImg, Size(srcImg.rows, srcImg.cols));
    Mat newGrayImg;
    cvtColor(newSrcImg, newGrayImg, COLOR_RGB2GRAY);
    resize(newGrayImg, newGrayImg, Size(srcImg.rows, srcImg.cols));


    Mat newHist;
    calcHist(&newGrayImg, 1, channels, Mat(), newHist, 1, histSize, ranges);

    // 计算图片的累计概率
    float histOld[256] = { hist.at<float>(0) };
    float histNew[256] = { newHist.at<float>(0) };
    for (int i = 1; i < 256; i++)
    {
        histOld[i] = histOld[i - 1] + hist.at<float>(i);
        histNew[i] = histNew[i - 1] + newHist.at<float>(i);
    }
    
    // 构建累计概率误差矩阵
    float diff[256][256];
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            diff[i][j] = fabs(histOld[i] - histNew[j]);
        }
    }
    
    // 生成LUT （lookuptable) 表
    Mat lut(1, 256, CV_8U);
    for (int i = 0; i < 256; i++)
    {
        float min = diff[i][0];
        int index = 0;
        for (int j = 1; j < 256; j++)
        {
            if (min > diff[i][j])
            {
                min = diff[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = (uchar)index;
    }

    // 应用LUT进行直方图匹配，并计算处理后图像的直方图
    Mat resultOutImg, histOut;
    LUT(grayImg, lut, resultOutImg);

    calcHist(&resultOutImg, 1, channels, Mat(), histOut, 1, histSize, ranges);

    // 直方图对比
    for (int i = 0; i < 6; i++)
    {
        cout << compareHist(hist, newHist, i) << endl;
    }

    // imshow("srcImg", srcImg);
    imshow("grayImg", grayImg);
    imshow("histImg", histOutImage(hist));
    // imshow("equalizeOutImg", equalizeOutImg);
    // imshow("histImg", histOutImage(outHist));
    // imshow("colorImg", colorImg);
    imshow("newSrcImage", newGrayImg);
    imshow("newHist", histOutImage(newHist));

    imshow("outImg", resultOutImg);
    imshow("histOut", histOutImage(histOut));

    waitKey(0);
    return 0;
}

