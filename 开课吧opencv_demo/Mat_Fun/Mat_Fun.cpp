#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

int trackbarvalue;
Mat image;

// adjustBrightness函数，它接收原始图像和亮度调整值作为输入，然后返回调整亮度后的图像。
Mat adjustBrightness(const Mat& src, int brightness)
{
    // 创建一个新的图像矩阵用于存储吊装亮度后的结果
    Mat dst = src.clone();
    // 对每个像素的每个通道值进行亮度调整
    dst.forEach<uchar>([brightness](uchar& pixel, const int* position) -> void {
        pixel = saturate_cast<uchar>(pixel + brightness);   // 防止溢出
        });
    return dst;
}


void trackbarcallback(int value, void* data)
{
    cout << value << endl;

    // 调用亮度调整函数并显示结果
    Mat adjustedImage = adjustBrightness(image, value - 127);   // // 减127是为了让调整范围从-127到127，对应完全变暗到完全变亮

    imshow("window_name", adjustedImage);
}

void mouseEventCallBack(int event, int x, int y, int flags, void* userdata)
{
    cout << event << endl;
    cout << x << ":" << y << endl;
}

int main()
{
    /*
        * 图像存相关函数
    */
    // (1) 图片的绝对路径或相对路径 (2) 读入图片到Mat容器当中的存放方式
    Mat srcImage = imread("./logo.png", IMREAD_GRAYSCALE);  // 存放方式为灰度图
    //resize(srcImage, srcImage, Size(800, 800));
    image = srcImage;

    // autosize 在部分的环境下，可以无法改变窗口的大小 normal可以改变
    namedWindow("window_name", WINDOW_NORMAL);

    // 添加进度条，注意使用回调函数
    createTrackbar("trackbar", "window_name", &trackbarvalue, 255, trackbarcallback);

    // 鼠标操作
    setMouseCallback("window_name", mouseEventCallBack, (void*)&srcImage);

    // (1) 显示的图片名称 (2) 图片的容器
    imshow("window_name", srcImage);
    
    /*
    * 1. 保存的图片名称，注意需要带后缀名
    * 2. 保存的源图像容器
    * 3. 存储过程中的编码处理 比如:压缩处理
    */
    vector<int> comparession;
    comparession.push_back(IMWRITE_PNG_COMPRESSION);
    comparession.push_back(8);
    imwrite("gray_logo1.png", srcImage, comparession);

    // 键盘组操作 等待一个任意字符，参数为延迟时间
    waitKey(0);

    return 0;
}

