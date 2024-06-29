#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    int image_count = 39;

    // 想要生成的图片
    Mat srcImage = imread("./xihu1.jpg");
    cout << srcImage.size() << endl;

    // 通过resize函数，进行尺寸设置
    resize(srcImage, srcImage, Size(1920, 1080));
    cout << srcImage.size() << endl;

    // 存放资源文件
    vector<Mat> source_images;
    char filenames[20];
    for (int i = 1; i <= 39; i++)
    {
        Mat src_img;
        sprintf(filenames, "./data/cat%d.jpg", i);

        // 根据路径读取文件
        src_img = imread(filenames);
        resize(src_img, src_img, Size(30, 30),0,0,INTER_NEAREST);
        source_images.push_back(src_img);
    }

    //cout << source_images.size() << endl;
    //imshow("first", source_images[0]);

    // 制作相关过程
    int width = srcImage.cols;
    int height = srcImage.rows;

    // 根据宽高 去计算纵横需要的图片个数

    // 根据颜色进行匹配

    // 生成对应的图片

    Mat montageImage;
    resize(srcImage, montageImage, Size(1920, 1080));   // 匹配的复制
    /*
        直方图
            (1) 根据图片的信息统计出直方图信息
            (2) 根据直方图信息进行匹配
            (3) 替换对应位置的图片
    */
    int bins = 128;
    int hist_sizes[] = { bins,bins,bins };
    float range[] = { 0,255 };  // 颜色
    const float* ranges[] = { range,range,range };
    int channels[] = { 0,1,2 }; // 通道数

    vector<MatND> hist_list;

    // 计算每一张图片的直方图信息
    for (int i = 0; i < image_count; i++)
    {
        MatND hist_RGB;
        Mat frame;
        source_images[i].copyTo(frame);

        // 计算直方图
        calcHist(&frame, 1, channels, Mat(),hist_RGB, 3, hist_sizes, ranges);

        hist_list.push_back(hist_RGB);
    }

    int number_order = 0;
    for (int y = 0; y < height; y = y + 30)
    {
        for (int x = 0; x < width; x = x + 30)
        {
            // 引用mentage矩阵中的(x,y)处开始的一个30x30像素大小的矩形区域
            Mat roiImage = montageImage(Rect(x, y, 30, 30));

            MatND hsit_roi;

            double match_max = 0;
            calcHist(&roiImage, 1, channels, Mat(), hsit_roi, 3, hist_sizes, ranges);

            // 找出最佳匹配的图像
            for (int i = 0; i < image_count; i++)
            {
                double match = 0;
                match = compareHist(hsit_roi, hist_list[i], HISTCMP_CORREL);

                if (match > match_max)
                {
                    // 将匹配度最高的值算出来
                    number_order = i;
                    match_max = match;
                }
            }

            // 找出匹配度最高的小图片，并将该图片替换到当前格子上
            source_images[number_order].copyTo(roiImage);
            printf("正在生成中：\033[01;32m %.2f%% \r", (y / (double)1080 + x / (double)1920 / 100) * 100);
            fflush(stdout);
        }
    }

    Mat destImage;
    // 通过addWeighted函数将原始缩放后的srcImage和已填充了小图片的montageImage按一定权重进行混合，得到新的destImage
    addWeighted(montageImage, 0.2, srcImage, 0.8, 3, destImage);
    imwrite("destImage.jpg", destImage);

    imshow("montage", destImage);

    // 等待图片显示
    waitKey(0);

    return 0;
    
}

