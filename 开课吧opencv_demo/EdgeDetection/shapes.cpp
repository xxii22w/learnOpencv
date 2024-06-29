#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

int main2()
{
	Mat srcImg = imread("../3.jpg");

	// (1) 图片的预处理 均衡，灰度化，二值化，降噪，滤波......
	Mat grayImg;
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);

	// (2) 使用检测函数 统计相关的形状信息
#if 0	
	vector<Vec3f> circles; // 圆 圆心（x,y) 半径 r
	/*
		参数3：HOUGH_GRADIENT 霍夫梯度算法
		参数4: 累加器的比值
		参数5: 最小圆心距离
		参数6  用于第三个参数算法的边缘检测阈值
		参数7  用于第三个参数算法的累加器阈值
	*/
	HoughCircles(grayImg, circles, HOUGH_GRADIENT, 1, 10, 100, 100);
	cout << circles.size() << endl;

	// (3) 收集信息计算.....
	Mat outImg = srcImg.clone();
	// 将识别出的信息绘制出来
	for (int i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = circles[i][2];

		circle(outImg, center, 3, Scalar(0),-1);

		circle(outImg, center, radius, Scalar(0),3);
	}

	imshow("outImg", outImg);
#endif

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	/*
		参数1：需要二值图或灰度图，之前通过阈值处理，canny检测等等产生结果
		参数2：轮廓的点向量集合，contours.size 轮廓的个数 contouurs[i].size() 轮廓的边数
		参数3：hierarchy 前一个轮廓，后一个轮廓，外部轮廓，内部轮廓，如果不存在，则输出-1
		参数4：模式
			RETR_EXTERNAL	只计算外部轮廓
			RETR_LIST		检测所有轮廓，所有轮廓存在关系 是否存在内外关系
			RETR_CCOMP		检测所有轮廓，只建立两个等级关系，只有最外和内部
			RETR_TREE		检测所有轮廓，建立等级树关系
		参数5：近似方法
			CHAIN_APPROX_NONE		保存轮廓上的所有的点
			CHAIN_APPROX_SIMPLE		只保存拐点信息

	*/
	Mat cannyImg;
	Canny(grayImg, cannyImg, 100, 200);
	// imshow("cannyImg", cannyImg);

	findContours(cannyImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	cout << contours.size() << endl;
	cout << hierarchy.size() << endl;
	if (hierarchy.size() > 0)
	{
		cout << hierarchy[0][0] << "," << hierarchy[1][0] << "," << hierarchy[2][0] << "," << hierarchy[3][0] << endl;
	}

	Mat outImg = srcImg.clone();
	drawContours(outImg, contours, -1, Scalar(0), 5);

	vector<vector<Point>> approxPoly(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		// 判断多边形
		approxPolyDP(contours[i], approxPoly[i], 0.01 * arcLength(contours[i], true), true);
		cout << approxPoly[i].size() << endl;

		// 画出中心点
		Moments momResult = moments(approxPoly[i]);
		int x = (int)(momResult.m10 / momResult.m00);
		int y = (int)(momResult.m01 / momResult.m00);
		cout << x << "," << y << endl;
		circle(outImg, Point(x,y), 3, Scalar(i * 255 / contours.size()), -1);
	}
	

	imshow("outImg", outImg);
	waitKey(0);
	return 0;
}