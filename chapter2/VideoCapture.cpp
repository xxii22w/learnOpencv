#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main1()
{
	system("color F0");	// 更改输出界面颜色
	//VideoCapture video("1.mp4");	// 视频播放
	VideoCapture video(0);			// 调用摄像头

	if (video.isOpened())
	{
		cout << "视频中图像的宽度=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
		cout << "视频中图像的高度=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
		cout << "视频帧率=" << video.get(CAP_PROP_FPS) << endl;
		cout << "视频的总帧数=" << video.get(CAP_PROP_FRAME_COUNT);
	}
	else
	{
		cout << "请确定视频文件名称是否正确" << endl;
		return -1;
	}
	while (1)
	{
		Mat frame;
		video >> frame;
		if (frame.empty())
		{
			break;
		}
		imshow("video", frame);
		waitKey(1000 / video.get(CAP_PROP_FPS));
	}
	waitKey(0);
	return 0;
}