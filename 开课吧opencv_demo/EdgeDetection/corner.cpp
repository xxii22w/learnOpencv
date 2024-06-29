#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImg = imread("../2.jpg");

	imshow("srcImg", srcImg);
	// 图片的预处理 滤波，二值化
	Mat tempImg = srcImg.clone();
	Mat grayImg;
	cvtColor(tempImg, grayImg, COLOR_RGB2GRAY);

	// 角点检测
	/*Mat outImg;
	cornerHarris(grayImg, outImg, 5, 9, 0.05);
	imshow("outImg", outImg);

	Mat normalOutImg;
	normalize(outImg, normalOutImg,0,255,NORM_MINMAX,CV_32FC1);
	Mat afterConvertImg;
	convertScaleAbs(normalOutImg, afterConvertImg);

	for (int i = 0; i < normalOutImg.rows; i++)
	{
		for (int j = 0; j < normalOutImg.cols; j++)
		{
			if (normalOutImg.at<float>(i, j) > 180)
			{
				circle(tempImg, Point(j, i), 10, Scalar(0, 0, 255), 2);
			}

		}
	}

	imshow("tempImg", tempImg);

	waitKey(0);*/

	vector<Point2f> corners;
	double quality = 0.01;
	double mindistance = 10;

	goodFeaturesToTrack(grayImg, corners, 10000, quality, mindistance);
	cout << corners.size() << endl;

	for (int i = 0; i < corners.size(); i++)
	{
		circle(tempImg, corners[i], 2, Scalar(0, 0, 255), 0.5);
	}
	imshow("tempImg", tempImg);
	waitKey(0);
	return 0;
}