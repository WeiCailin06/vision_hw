#pragma once
#include <cmath>
#include <stdexcept>
struct Point2D {//定义二维点
    double u, v;
};
struct Point3D {//定义三维点
    double x, y, z;
};
struct CameraIntrinsics {//设置相机内参
    double fx, fy, cx, cy;
};
struct CameraExtrinsics {//设置相机外参
    double R[3][3];
    double t[3];
};
Point2D projectPoint(const Point3D& pw,const CameraIntrinsics& K,const CameraExtrinsics& ext);//重投影函数
double calculatePixelError(const Point2D& projected,const Point2D& observed);//计算误差函数