#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    /*
        1. 设置需要去除的颜色
        2. 对整个图片进行颜色匹配
        3. 展示效果
    */
    // 只有png是有透明度空间的，jpg是没有透明度的
    Mat srcImage = imread("./lvbu.jpg", 1);

    cout << srcImage.channels() << endl;

    Vec3b color(0, 255,0);
    int tempc = 0;
    // 先把图片放大、做完抠图后，在放小

    Mat temp;
    // 转换图片，增加透明区域
    cvtColor(srcImage, temp, COLOR_RGB2RGBA);
    // 使用相近的颜色
    for (int i = 0; i < srcImage.rows; i++)
    {
        for (int j = 0; j < srcImage.cols; j++)
        {
            Vec3b& pixel = srcImage.at<Vec3b>(i, j);
            Vec4b& pixel_temp = temp.at<Vec4b>(i, j);
            if (pixel[0] <= 30 && pixel[1] >= 210 && pixel[2] <= 30)
            {
                tempc = j + 1;
                pixel_temp[3] = 0;
            }
            else if (tempc == j - 1)
            {
                pixel_temp[3] = 0;
            }
        }
    }

    imshow("result", temp);
    imwrite("result.png", temp);
    waitKey(0);
    return 0;
}

