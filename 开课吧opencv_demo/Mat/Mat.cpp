#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void printMat(Mat& mat)
{
    cout << "Mat:" << mat << endl;
    cout << "flags:" << mat.flags << endl;
    cout << "dims:" << mat.dims << endl;    // 维数
    cout << "rows:" << mat.rows << "cols:" << mat.cols << endl;
    if (mat.data)
    {
        cout << "data:存在" << endl;
    }
    cout << "存储相关" << endl;
    cout << "umatdata:" << mat.u << endl;
    if (mat.u)
    {
        cout << "refcount" << mat.u->refcount << endl;
    }
}

int main()
{
    // 创建对应的矩阵头信息，没有包含真正的矩阵内部数据
    Mat m;

    // cv_8uc1 8指数据位数，u指是否带符号，c指channel信道数，1一个信道
    Mat m_size(10, 10, CV_8UC1);
    // zeros 进行元素数据清零操作
    m_size.zeros(10, 10, CV_8UC1);
    imshow("test", m_size);
    printMat(m_size);

    m = m_size;
    printMat(m);

    Mat m1 = m;
    printMat(m1);
    // 上述两种方式，都是浅拷贝，只会增加对应的refcount，而不会产生新的内容

    Mat mat_clone = m.clone();
    Mat mat_copy_to_mat;
    m.copyTo(mat_copy_to_mat);

    printMat(mat_clone);
    printMat(mat_copy_to_mat);
    // 上述两种方式，都是深拷贝，会产生新的内容，对应的refcount不会增加

    Mat scalar_mat(100, 100, CV_8UC1, Scalar(128, 255, 0));
    imshow("scalar", scalar_mat);

    // 获取对角线上的数据
    cout << scalar_mat.diag(0) << endl;

    // create 方法，进行数据的填充处理了，create之前的对象就被销毁
    Mat uncreate;
    printMat(uncreate);

    uncreate.create(10, 10, CV_8UC1);
    printMat(uncreate);

    waitKey(0);

    // (1) 用于数学上的矩阵运算 (2) 进行图像数据的存储和相关的运算操作
    return 0;
}


