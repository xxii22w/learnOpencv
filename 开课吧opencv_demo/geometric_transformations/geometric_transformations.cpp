#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


/*
*   几何变换
    平移    translation
    缩放    scale
    旋转    rotate

    仿射变换
*/

int main()
{
    Mat srcImg = imread("./dog.jpg");
    // 缩放
    /*
        1 1 1
        0 1 0
        0 1 0
        插值处理
        1 1 1 1 1 1
        1 1 1 1 1 1
        0 0 1 1 0 0
        0 0 1 1 0 0
        0 0 1 1 0 0
        0 0 1 1 0 0

        1 1 1 1 1 1
        0 0 1 1 0 0
        0 0 1 1 0 0

        1 1 1
        0 1 0
        0 1 0
    */
    Mat result1;
    Mat result2;
    // 如果是缩小，可以选取area，从区域内选取相似值
    // 放大，可以选取linear，Nearest
    // CUBIC会使得运算时间变长
    /*
    临值插法
    INTER_NEAREST        = 0,
    双线性插法
    INTER_LINEAR         = 1,
    双三次插值
    INTER_CUBIC          = 2,
    区域采样处理
    INTER_AREA           = 3,
    */

    resize(srcImg, result1, Size(300, 300), INTER_NEAREST);
    resize(srcImg, result2, Size(),0.7,0.7,INTER_AREA);

    // 平移
    /*
        1 0 0
        0 0 0
        0 0 0

        0 0 1
        0 0 0
        0 0 0

        0 0 0
        0 0 0
        1 0 0

        0 0 0
        0 0 0
        0 0 1

        [a1 a2 bx
         a3 a4 by]
        a组影响图片的大小和位置
        b组对应的偏移量

        平移操作
        1 0 deltax
        0 1 deltay
        deltax x轴的平移效果 正数往右，负数往左
        deltay 正数往下，负数往上

        缩放
        W 0 0
        0 H 0
        W 为宽值
        H 为高值

        旋转
        cos$ sin$ 0
        -sin$ cos$ 0
        其中$就是对应的角度

        斜切
        1 deltaX 0
        deltaY 1 0
        如上,就是将一个矩形向右拉成一个平行四边形,拉的偏移量就是deltaX
        deltaY就是向下拉取的偏移量

        翻转
        1 0 0
        0 1 0
        这个是原始图片 假设处于第一象限
        -1 0 0
        0 1 0
        翻转到第二象限
        -1 0 0
        0 -1 0
        翻转到第三象限
    */

    Mat translate1;
    Mat delta = Mat::zeros(2, 3, CV_32FC1);
    // 直接定义对于的变化原则
    delta.at<float>(0, 0) = 1;
    delta.at<float>(1, 1) = 1;
    delta.at<float>(0, 2) = 30;
    delta.at<float>(1, 2) = 50;
    /*
    * wrapAffine 通过2 * 3 矩阵变换
    * wrapPerspective 通过 3 * 3矩阵变换
    */
    warpAffine(srcImg, translate1, delta, srcImg.size());

    // 通过对应的变换函数获取 一般都是以get开头 getRotationMatrix2D 旋转使用
    // getAffineTransform 适合两个图像之间建立对应的映射关系计算
    Mat delta_rotate = getRotationMatrix2D(Point2f(srcImg.cols / 2, srcImg.rows / 2), 45, 1.0);

    Mat rotate;
    warpAffine(srcImg, rotate, delta_rotate, srcImg.size());

    Point2f srcAff[3] = { Point2f(0,0), Point2f(srcImg.cols / 2, 0), Point2f(0,srcImg.rows + 20) };
    Point2f desAff[3] = { Point2f(srcImg.cols * 0, srcImg.rows * 0.33),Point2f(srcImg.cols * 0.8, srcImg.rows * 0.2),\
    Point2f(srcImg.cols * 0.4, srcImg.rows * 0.7) };

    Mat delta_custom = getAffineTransform(srcAff, desAff);
    Mat custom;
    warpAffine(srcImg, custom, delta_custom, srcImg.size());

    imshow("src", srcImg);
    // imshow("result1", result1);
    // imshow("result2", result2);
    imshow("custom", custom);
    waitKey(0);
}

