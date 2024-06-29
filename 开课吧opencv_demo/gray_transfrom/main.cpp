#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*
*                                                   对于类间方差的了解
* 一种自适合于双峰情况的自动求取阈值的方法,又叫大津法,简称Otsu。它是按图像的灰度特性,将图像分成背景和目标2部分。
* 背景和目标之间的类间方差越大,说明构成图像的2部分的差别越大,当部分目标错分为背景或部分背景错分为目标都会导致2部分差别变小。因此,使类间方差最大的分割意味着错分概率最小。
* 为什么要最大化这个值？因为在Otsu算法中，类间方差越大，表示根据当前阈值划分得到的前景和背景之间的区分度越高，
* 也就是说，二值化的效果越好。因此，遍历所有可能的阈值，找到使得这个类间方差最大的那个阈值，就被认为是最优的二值化阈值。
*/

int my_otsu(Mat inputImg)
{
    // 初始化
    int rows = inputImg.rows;
    int cols = inputImg.cols;
    int sumPixel[256] = { 0 };  // 统计图像中每个灰度级出现的次数
    float proDis[256] = { 0 };  // 根据这些统计数据计算每个灰度级的概率，计算类间方差的基础
    int result_threshold;
    // 拿到灰度值的统计信息
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sumPixel[(int)inputImg.at<uchar>(i, j)]++;
        }
    }
    // 计算概率比分布
    for (int i = 0; i < 256; i++)
    {
        proDis[i] = sumPixel[i] / (float)(rows * cols);
    }

    // 计算最大方差 (正态分布的左右边)
    float all_left, all_right, avg_left, avg_right, temp_left, temp_right, temp_delta;
    float max_delta = 0.0;
    for (int i = 0; i < 255; i++)
    {
        all_left = all_right = avg_left = avg_right = temp_left = temp_right = temp_delta = 0;
        for (int j = 0; j < 255; j++)
        {
            if (j <= i)
            {
                all_left += proDis[j];
                temp_left += j * proDis[j];
            }
            else
            {
                all_right += proDis[j];
                temp_right += j * proDis[j];
            }
        }
        // 在二值化处理中，这两个平均值可以被看作是背景和前景的“代表”灰度值。计算这两类的均值有助于评估分割效果的好坏。
        avg_left = temp_left / all_left;
        avg_right = temp_right / all_right;
        // pow((avg_left - avg_right), 2) 计算的是两类平均灰度值之差的平方。这个表达式反映了两类像素灰度分布的差异程度：差异越大，该值越大。
        // all_left * all_right 乘以两类的比例因子，这是因为类间方差的计算需要考虑每一类的占比。
        // 相乘 得到的就是当前阈值下两类之间的加权类间方差
        temp_delta = (float)(all_left * all_right * pow((avg_left - avg_right), 2));
        if (temp_delta > max_delta)
        {
            max_delta = temp_delta;
            result_threshold = i;
        }
    }

    // 计算结果
    return result_threshold;
}

int main()
{
    // 读入图片
    Mat srcImg = imread("./1.jpg");
    // 转换为灰度图
    Mat grayImg;
    cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
    imshow("src", srcImg);
    imshow("gray", grayImg);
    // 进行阈值计算
    int otsu = my_otsu(grayImg);
    cout << otsu << endl;
    // 通过阈值进行二值化
    Mat resultImg = grayImg.clone();

    for (int i = 0; i < grayImg.rows; i++)
    {
        for (int j = 0; j < grayImg.cols; j++)
        {
            if (grayImg.at<uchar>(i, j) >= otsu)
            {
                resultImg.at<uchar>(i, j) = 255;
            }
            else
            {
                resultImg.at<uchar>(i, j) = 0;
            }
        }

    }

    imshow("result", resultImg);

    waitKey(0);
    return 0;
}

