#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImg = imread("./salt_pepper.png");

	// 方框滤波（盒滤波)
	Mat boxOutImg;
	boxFilter(srcImg, boxOutImg, -1, Size(5, 5), Point(-1, -1), true);

	// 均值滤波 盒滤波进行均值处理就是均值滤波
	Mat blurOutImg;
	blur(srcImg, blurOutImg, Size(5, 5));
	// blur, bilateralFilter, GaussianBlur, medianBlur

	// 高斯滤波
	Mat gaussianBlurOutImg;
	GaussianBlur(srcImg, gaussianBlurOutImg, Size(5, 5), 3, 5);

	// medianblur 对于椒盐滤波非常有效
	Mat midOutImg;
	medianBlur(srcImg, midOutImg, 7);

	// bilaterlFilter 双边滤波，如果针对于普通的图片处理，有一定的美颜效果
	Mat bilateralOutImg;
	bilateralFilter(srcImg, bilateralOutImg, 0, 100, 5);

	// 用于去噪的函数
	Mat denosising;
	fastNlMeansDenoisingColored(srcImg, denosising, 10, 10);

	imshow("srcImg", srcImg);
	imshow("boxOutImg", boxOutImg);
	imshow("blurOutImg", blurOutImg);
	imshow("gaussianBlurOutImg", gaussianBlurOutImg);
	imshow("midOutImg", midOutImg);
	imshow("bilateralOutImg", bilateralOutImg);
	imshow("denosising", denosising);

	waitKey(0);
	return 0;
}