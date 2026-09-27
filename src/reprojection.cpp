#include "reprojection.h"

// 实现重投影计算
Point2D projectPoint(const Point3D& pw, const CameraIntrinsics& K, const CameraExtrinsics& ext) {
    // 1. 外参变换：Pc = R * Pw + t
    double Xc = ext.R[0][0]*pw.x + ext.R[0][1]*pw.y + ext.R[0][2]*pw.z + ext.t[0];
    double Yc = ext.R[1][0]*pw.x + ext.R[1][1]*pw.y + ext.R[1][2]*pw.z + ext.t[1];
    double Zc = ext.R[2][0]*pw.x + ext.R[2][1]*pw.y + ext.R[2][2]*pw.z + ext.t[2];

    // 2. 异常处理：如果点在相机后方，抛出异常
    if (Zc <= 0.0) {
        throw std::runtime_error("Error: 深度 Zc <= 0,该点位于相机后方,无法投影!");
    }

    // 3. 归一化：透视除法
    double x = Xc / Zc;
    double y = Yc / Zc;

    // 4. 像素坐标计算
    Point2D pixel;
    pixel.u = K.fx * x + K.cx;
    pixel.v = K.fy * y + K.cy;

    return pixel;
}

// 实现计算欧氏距离
double calculatePixelError(const Point2D& projected, const Point2D& observed) {
    double du = projected.u - observed.u;
    double dv = projected.v - observed.v;
    return std::sqrt(du * du + dv * dv);
}