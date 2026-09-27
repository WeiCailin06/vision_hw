#include <iostream>
#include <cmath>      // 用于 cos、sin 以及 PI
#include "reprojection.h"

const double PI = 3.14159268979;

int main() {
    std::cout << "===========================================\n";
    std::cout << "   相机重投影计算器\n";
    std::cout << "===========================================\n";

    // 1. 输入内参
    CameraIntrinsics K;
    std::cout << "\n[1/4] 请输入相机内参 (fx fy cx cy,用空格隔开): ";
    std::cin >> K.fx >> K.fy >> K.cx >> K.cy;

    // 2. 输入外参平移
    CameraExtrinsics ext;
    std::cout << "\n[2/4] 请输入相机外参平移向量 (t0 t1 t2,用空格隔开): ";
    std::cin >> ext.t[0] >> ext.t[1] >> ext.t[2];

    // 3. 输入外参旋转
    double angle_x, angle_y, angle_z;
    std::cout << "\n[3/4] 请输入相机旋转角度 (单位: 度)。\n";
    std::cout << "  格式: 绕X轴(俯仰) 绕Y轴(偏航) 绕Z轴(翻滚)\n";
    std::cout << "  例如输入 0 0 45 代表只绕Z轴旋转45度: ";
    std::cin >> angle_x >> angle_y >> angle_z;

    // 将三个角度转成弧度
    double rx = angle_x * PI / 180.0;
    double ry = angle_y * PI / 180.0;
    double rz = angle_z * PI / 180.0;

    // 计算三个轴的三角函数
    double cx = std::cos(rx), sx = std::sin(rx);
    double cy = std::cos(ry), sy = std::sin(ry);
    double cz = std::cos(rz), sz = std::sin(rz);

    // 组合三个轴的旋转矩阵 R = Rz * Ry * Rx (Z-Y-X顺序)
    // 直接套用矩阵乘法展开后的结果
    ext.R[0][0] = cy * cz;
    ext.R[0][1] = sx * sy * cz - cx * sz;
    ext.R[0][2] = cx * sy * cz + sx * sz;

    ext.R[1][0] = cy * sz;
    ext.R[1][1] = sx * sy * sz + cx * cz;
    ext.R[1][2] = cx * sy * sz - sx * cz;

    ext.R[2][0] = -sy;
    ext.R[2][1] = sx * cy;
    ext.R[2][2] = cx * cy;

    std::cout << "  提示: 三轴旋转矩阵已根据角度 (" << angle_x << ", " << angle_y << ", " << angle_z << ") 自动生成！\n";

    // 4. 输入三维点
    Point3D pw;
    std::cout << "\n[4/4] 请输入三维点的世界坐标 (Xw Yw Zw,用空格隔开): ";
    std::cin >> pw.x >> pw.y >> pw.z;

    // 开始计算
    std::cout << "\n--- 计算结果 ---\n";
    try {
        Point2D projected = projectPoint(pw, K, ext);
        std::cout << "投影后的像素坐标: (" << projected.u << ", " << projected.v << ")\n";

        Point2D observed;
        std::cout << "\n请输入实际的观测坐标 (u_obs v_obs,用空格隔开): ";
        std::cin >> observed.u >> observed.v;

        double error = calculatePixelError(projected, observed);
        std::cout << "重投影误差 (欧氏距离): " << error << " 像素\n";

    } catch (const std::exception& e) {
        std::cout << "【错误】计算失败: " << e.what() << "\n";
    }

    std::cout << "\n--- 程序结束 ---\n";
    return 0;
}