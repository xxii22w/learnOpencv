#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;

// 更改图片颜色

int main()
{
    Mat srcImg = imread("./kai.png", IMREAD_UNCHANGED);
    Mat srcImg1 = imread("./kai.png", 0);
    Mat srcImg2 = imread("./kai.png", 1);

    cout << srcImg.channels() << endl;
    cout << srcImg1.channels() << endl;
    cout << srcImg2.channels() << endl; 

    imshow("-1", srcImg);
    imshow("0", srcImg1);
    imshow("1", srcImg2);

    // 颜色有控件RGB(1) RGBA(-1) 透明度 灰色空间(0)

    // 存储阶段的颜色值
    vector<Vec3d> colors;
    unsigned long index = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 6; k++)
            {
                colors.push_back(Vec3d());
                colors[index][0] = i / 5.0 * 255;   // 将范围从0-5线性映射到0-255
                colors[index][1] = j / 5.0 * 255;
                colors[index][2] = k / 5.0 * 255;
                index++;
            }
        }
    }

    // 更改对应的颜色值
    index = 0;
    Mat temp = srcImg.clone();
    while (index < colors.size())
    {
        for (int r = 0; r < srcImg.rows; r++)
        {
            for (int c = 0; c < srcImg.cols; c++)
            {
                // 获取像素点的颜色值
                //Vec4b& pixel = srcImg.at<Vec4b>(r, c);
                Vec4b& pexel_temp = temp.at<Vec4b>(r, c);
                // 如果当前点的透明度为0
                if (pexel_temp[3] == 0)
                {
                    continue;
                }
                else
                {
                    for (int i = 0; i < 3; i++)
                    {
                        pexel_temp[i] = colors[index][i];
                    }
                }
            }
        }

        char outImagePath[64] = {};
        sprintf(outImagePath,"./out_img/out_img_%.0f_%.0f_%.0f.png", colors[index][0], colors[index][1], colors[index][2]);
        imwrite(outImagePath, temp);
        index++;
    }

    // waitKey(0);
    return 0;
}


