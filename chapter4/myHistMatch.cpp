#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void drawHist2(Mat& hist, int type, string name)  //归一化并绘制直方图函数
{
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(hist, hist, 1, 0, type, -1, Mat());
	for (int i = 1; i <= hist.rows; i++)
	{
		rectangle(histImage, Point(width * (i - 1), hist_h - 1),
			Point(width * i - 1, hist_h - cvRound(20 * hist_h * hist.at<float>(i - 1)) - 1),
			Scalar(255, 255, 255), -1);
	}
	imshow(name, histImage);
}

int main5()
{
	Mat img1 = imread("../data/histMatch.png");
	Mat img2 = imread("../data/equalLena.png");
	Mat hist1, hist2;
	//计算两张图像直方图
	const int channels[1] = { 0 };
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };
	const int bins[1] = { 256 };
	calcHist(&img1, 1, channels, Mat(), hist1, 1, bins, ranges);
	calcHist(&img2, 1, channels, Mat(), hist2, 1, bins, ranges);
	// 归一化两张图像的直方图
	drawHist2(hist1, NORM_L1, "hist1");
	drawHist2(hist2, NORM_L1, "hist1");
	//计算两张图像直方图的累积概率
	float hist1_cdf[256] = { hist1.at<float>(0) };
	float hist2_cdf[256] = { hist2.at<float>(0) };
	for (int i = 1; i < 256; i++)
	{
		hist1_cdf[i] = hist1_cdf[i - 1] + hist1.at<float>(i);
		hist2_cdf[i] = hist2_cdf[i - 1] + hist2.at<float>(i);

	}
	//构建累积概率误差矩阵
	float diff_cdf[256][256];
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			diff_cdf[i][j] = fabs(hist1_cdf[i] - hist2_cdf[j]);
		}
	}

	// 生成LUT映射表
	Mat lut(1, 256,CV_8U);
	for (int i = 0; i < 256; i++)
	{
		//	查找源灰度级为i的映射灰度
		//	和i的累积概率差值最小的规定化灰度
		float min = diff_cdf[i][0];
		int index = 0;
		// 寻找累积概率误差矩阵中每一行中的最小值
		for (int j = 1; j < 256; j++)
		{
			if (min > diff_cdf[i][j])
			{
				min = diff_cdf[i][j];
				index = j;
			}
		}
		lut.at<uchar>(i) = (uchar)index;
	}
	Mat result, hist3;
	LUT(img1, lut, result);
	imshow("待匹配图像", img1);
	imshow("匹配的模板图像", img2);
	imshow("直方图匹配结果", result);
	calcHist(&result, 1, channels, Mat(), hist3, 1, bins, ranges);
	drawHist2(hist3, NORM_L1, "hist3");  //绘制匹配后的图像直方图
	waitKey(0);
	return 0;
}