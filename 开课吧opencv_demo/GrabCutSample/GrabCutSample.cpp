#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat srcImg = imread("./leifengtower.jpg");
    Mat mask, bgModel, fgModel;
    Rect rect(Point(1, 1), Point(srcImg.cols, srcImg.rows));    // 覆盖整个图像的矩形
    /*
        srcImg：输入图像
        mask：输出掩模，用于存储每个像素点属于背景、前景还是不确定的概率
        rect：初始矩形区域，算法在这个区域内进行前景与背景的估计
        bgModel 和 fgModel：背景和前景的高斯混合模型参数
        5：迭代次数
        GC_INIT_WITH_RECT：表示使用矩形区域初始化分割
    */
    grabCut(srcImg, mask, rect, bgModel, fgModel, 5, GC_INIT_WITH_RECT);
    rectangle(srcImg, rect, Scalar(255), 2, 8);                 // 在原图上绘制出指定的矩形区域

    imshow("src", srcImg);
    imshow("mask", (mask & 1) * 255);                           // 显示处理后的掩模图像 其中 0 表示背景或不确定区域，1 表示前景。然后将结果乘以 255 转为灰度图像以便显示
    Mat resultMask = (mask & 1) * 255;                          // 创建一个新的掩模矩阵 resultMask，只保留前景部分

    // Mat resultImage = Mat(srcImg.rows, srcImg.cols, CV_8UC3);
    // Mat resultImage;
    // resize(resultImage, resultImage, Size(srcImg.rows, srcImg.cols));

    Mat resultImage = imread("./sky.jpg");
    resize(resultImage, resultImage, Size(srcImg.cols, srcImg.rows));

    // for (int i = 0; i < srcImg.rows; i++)
    // {
    //     for (int j = 0; j < srcImg.cols; j++)
    //     {
    //         Vec3b &pixel_src = srcImg.at<Vec3b>(i,j);
    //         Vec3b &pixel_result = resultImage.at<Vec3b>(i,j);
    //         uchar &pixel_mask = resultMask.at<uchar>(i,j);
    //         if (pixel_mask == 255)
    //         {
    //             for (int k = 0; k < 3; k++)
    //             {
    //                 pixel_result[k] = pixel_src[k];
    //             }

    //         }

    //     }

    // }

    srcImg.copyTo(resultImage, resultMask);
    imshow("result", resultImage);
    waitKey(0);
    return 0;
}

