#pragma once // 防止头文件重复包含
#include <cmath>
#include <stdexcept>

// 1. 定义三维点
struct Point3D {
    double x, y, z;
};

// 2. 定义二维像素点
struct Point2D {
    double u, v;
};

// 3. 定义相机内参
struct CameraIntrinsics {
    double fx, fy, cx, cy;
};

// 4. 定义相机外参
struct CameraExtrinsics {
    double R[3][3]; // 旋转矩阵
    double t[3];    // 平移向量
};

// 5. 声明重投影函数
Point2D projectPoint(const Point3D& pw, const CameraIntrinsics& K, const CameraExtrinsics& ext);

// 6. 声明计算误差函数
double calculatePixelError(const Point2D& projected, const Point2D& observed);