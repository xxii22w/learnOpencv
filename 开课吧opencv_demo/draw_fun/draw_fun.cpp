#include <opencv2/opencv.hpp>
using namespace cv;
#include <iostream>
using namespace std;

int main()
{
    /*
        1、线 line
        2、矩形 rectangle
        3、圆 circle
        4、椭圆 ellipse
        5、多边形 poly
    */

    /*
        1、Point 点 x,y
        2、Size 尺寸 width height
        3、Rect 矩形 x,y,width,height
        4、Scalar 颜色
    */

    Mat m(600, 400, CV_8UC4);
    m.zeros(600, 400, CV_8UC4);

    cvtColor(m, m, COLOR_BGR2BGRA, 4);

    /*
      Scalar 颜色对象，可以填写对应的颜色
      thickness 线的宽度   对于包围图形，-1代表填充内部空间
      linetype 线的类型
   */
    line(m, Point(100, 100), Point(300, 500), Scalar(0, 0, 255, 128), 5, -1);

    rectangle(m, Point(100, 100), Point(300, 500), Scalar(0, 255, 0, 128), -1, LINE_4);

    circle(m, Point(100, 100), 50, Scalar(255, 0, 0, 0), -1, LINE_4);

    /*
       如果是单信道channel, 单独数值
       如果是多信道呢？
     */
     // uchar single_channel = m.at<uchar>(100,100);
     // Vec2b double_channel = m.at<Vec2d>(100,100);
     // Vec3b
     // Vec4b
    
    imshow("result", m);
    waitKey(0);
    return 0;

}

