#include <iostream>
#include "reprojection.h"

int main() {
    std::cout << "--- 开始重投影测试 ---" << std::endl;

    // 1. 构造相机内参 (理想值)
    CameraIntrinsics K;
    K.fx = 800.0; K.fy = 800.0;
    K.cx = 320.0; K.cy = 240.0;

    // 2. 构造外参 (简单设为无旋转、无平移，相机就在原点看向 Z 轴正方向)
    CameraExtrinsics ext;
    ext.R[0][0]=1; ext.R[0][1]=0; ext.R[0][2]=0;
    ext.R[1][0]=0; ext.R[1][1]=1; ext.R[1][2]=0;
    ext.R[2][0]=0; ext.R[2][1]=0; ext.R[2][2]=1;
    ext.t[0]=0; ext.t[1]=0; ext.t[2]=0;

    // 3. 构造一个真实的三维点 (在相机前方 Z=5 处)
    Point3D pw{1.0, 2.0, 5.0};

    // 4. 调用函数
    Point2D projected = projectPoint(pw, K, ext);
    std::cout << "投影后的像素坐标: (" << projected.u << ", " << projected.v << ")" << std::endl;

    // 手动验算：x=1/5=0.2, y=2/5=0.4
    // u = 800*0.2 + 320 = 480
    // v = 800*0.4 + 240 = 560
    std::cout << "理论预期坐标: (480, 560)" << std::endl;

    // 5. 构造观测值并计算误差
    Point2D observed{481.0, 559.0}; // 假设真实观测有微小偏差
    double error = calculatePixelError(projected, observed);
    std::cout << "重投影误差 (欧氏距离): " << error << " 像素" << std::endl;

    // 6. 测试异常处理 (故意给一个相机背后的点 Z=-5)
    try {
        Point3D behind_pw{1.0, 2.0, -5.0};
        projectPoint(behind_pw, K, ext);
    } catch (const std::exception& e) {
        std::cout << "成功捕获异常: " << e.what() << std::endl;
    }

    std::cout << "--- 测试结束 ---" << std::endl;
    return 0;
}