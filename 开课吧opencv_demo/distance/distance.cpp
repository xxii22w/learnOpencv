#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat srcImg = imread("../poker.jpg");
    Mat grayImg;
    cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);

    Mat binaryImg;
    threshold(grayImg, binaryImg, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    Mat distanceImg;
    distanceTransform(binaryImg, distanceImg, DIST_L1, DIST_MASK_3);
    normalize(distanceImg, distanceImg, 0, 1, NORM_MINMAX);

    imshow("grayImg", grayImg);
    imshow("binary", binaryImg);
    imshow("distanceImg", distanceImg);

    waitKey(0);
    return 0;
}


