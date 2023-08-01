#include <iostream>
#include <cmath>
#include <vector>

class Quaternion {
public:
    float w, x, y, z;

    // 默认构造函数
    Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

    // 从标量和向量构造四元数
    Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

    // 从角轴构造四元数
    Quaternion(float angle, const std::vector<float>& axis) {
        float half_angle = angle / 2.0f;
        float sin_half_angle = std::sin(half_angle);
        w = std::cos(half_angle);
        x = axis[0] * sin_half_angle;
        y = axis[1] * sin_half_angle;
        z = axis[2] * sin_half_angle;
    }

    // 四元数的模长
    float magnitude() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    // 四元数的共轭
    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    // 四元数的逆
    Quaternion inverse() const {
        float mag_square = magnitude() * magnitude();
        return conjugate() * (1.0f / mag_square);
    }

    // 四元数的标准化
    Quaternion normalized() const {
        float mag = magnitude();
        return Quaternion(w / mag, x / mag, y / mag, z / mag);
    }

    // 四元数乘法
    Quaternion operator*(const Quaternion& q) const {
        float nw = w * q.w - x * q.x - y * q.y - z * q.z;
        float nx = w * q.x + x * q.w + y * q.z - z * q.y;
        float ny = w * q.y - x * q.z + y * q.w + z * q.x;
        float nz = w * q.z + x * q.y - y * q.x + z * q.w;
        return Quaternion(nw, nx, ny, nz);
    }

    // 标量乘法
    Quaternion operator*(float scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    // 向量旋转
    std::vector<float> rotate_vector(const std::vector<float>& vec) const {
        Quaternion vec_quat(0, vec[0], vec[1], vec[2]);
        Quaternion result = (*this) * vec_quat * this->inverse();
        return {result.x, result.y, result.z};
    }

    // 转为旋转矩阵
    std::vector<std::vector<float>> to_rotation_matrix() const {
        float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
        x2 = x + x;
        y2 = y + y;
        z2 = z + z;
        xx = x * x2;
        xy = x * y2;
        xz = x * z2;
        yy = y * y2;
        yz = y * z2;
        zz = z * z2;
        wx = w * x2;
        wy = w * y2;
        wz = w * z2;

        std::vector<std::vector<float>> matrix(3, std::vector<float>(3));
        matrix[0][0] = 1.0f - (yy + zz);
        matrix[0][1] = xy - wz;
        matrix[0][2] = xz + wy;

        matrix[1][0] = xy + wz;
        matrix[1][1] = 1.0f - (xx + zz);
        matrix[1][2] = yz - wx;

        matrix[2][0] = xz - wy;
        matrix[2][1] = yz + wx;
        matrix[2][2] = 1.0f - (xx + yy);

        return matrix;
    }

    // 输出四元数的字符串表示
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
        os << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
        return os;
    }
};

