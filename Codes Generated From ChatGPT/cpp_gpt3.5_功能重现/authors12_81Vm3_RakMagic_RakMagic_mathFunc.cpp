#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// 生成一个随机字符串
string gen_gpci(int length) {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, chars.length() - 1);
    string result = "";
    for (int i = 0; i < length; i++) {
        result += chars[distr(gen)];
    }
    return result;
}

// 判断一个浮点数是否接近于0
bool near_zero(double x) {
    const double EPSILON = 1e-8;
    return abs(x) < EPSILON;
}

// 将一个二维向量归一化
void vect2_normalize(double &x, double &y) {
    double len = vect2_length(x, y);
    if (len > 0) {
        x /= len;
        y /= len;
    }
}

// 计算一个二维向量的长度
double vect2_length(double x, double y) {
    return sqrt(x * x + y * y);
}

// 判断一个二维向量是否接近于0
bool vect2_near_zero(double x, double y) {
    return near_zero(x) && near_zero(y);
}

// 将一个三维向量清零
void vect3_zero(double &x, double &y, double &z) {
    x = y = z = 0.0;
}

// 复制一个二维向量
void vect2_copy(double x1, double y1, double &x2, double &y2) {
    x2 = x1;
    y2 = y1;
}

// 将一个三维向量归一化
void vect3_normalize(double &x, double &y, double &z) {
    double len = vect3_length(x, y, z);
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}

// 计算一个三维向量的长度
double vect3_length(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

// 将一个三维向量除以一个标量
void vect3_div(double &x, double &y, double &z, double s) {
    if (s != 0.0) {
        x /= s;
        y /= s;
        z /= s;
    }
}

// 将一个三维向量乘以一个标量
void vect3_mult(double &x, double &y, double &z, double s) {
    x *= s;
    y *= s;
    z *= s;
}

// 将两个三维向量对应元素相乘
void vect3_vect3_mult(double &x1, double &y1, double &z1, double x2, double y2, double z2) {
    x1 *= x2;
    y1 *= y2;
    z1 *= z2;
}

// 将两个三维向量相加
void vect3_vect3_add(double &x1, double &y1, double &z1, double x2, double y2, double z2) {
    x1 += x2;
    y1 += y2;
    z1 += z2;
}

int main() {
// 生成一个随机字符串
    string str = gen_gpci(10);
    cout << "Random string: " << str << endl;
    // 测试near_zero函数
    double a = 1.0e-9;
    double b = 1.0e-10;
    double c = 1.0e-11;
    cout << "near_zero(a) = " << near_zero(a) << endl;
    cout << "near_zero(b) = " << near_zero(b) << endl;
    cout << "near_zero(c) = " << near_zero(c) << endl;

    // 测试vect2_normalize函数
    double x1 = 3.0, y1 = 4.0;
    cout << "vect2_normalize(" << x1 << ", " << y1 << ") = ";
    vect2_normalize(x1, y1);
    cout << "(" << x1 << ", " << y1 << ")" << endl;

    // 测试vect2_length函数
    double x2 = 3.0, y2 = 4.0;
    cout << "vect2_length(" << x2 << ", " << y2 << ") = " << vect2_length(x2, y2) << endl;

    // 测试vect2_near_zero函数
    double x3 = 1.0e-10, y3 = 1.0e-10;
    double x4 = 1.0e-9, y4 = 1.0e-10;
    cout << "vect2_near_zero(" << x3 << ", " << y3 << ") = " << vect2_near_zero(x3, y3) << endl;
    cout << "vect2_near_zero(" << x4 << ", " << y4 << ") = " << vect2_near_zero(x4, y4) << endl;

    // 测试vect3_zero函数
    double x5 = 1.0, y5 = 2.0, z5 = 3.0;
    cout << "vect3_zero(" << x5 << ", " << y5 << ", " << z5 << ") = ";
    vect3_zero(x5, y5, z5);
    cout << "(" << x5 << ", " << y5 << ", " << z5 << ")" << endl;

    // 测试vect2_copy函数
    double x6 = 1.0, y6 = 2.0;
    double x7, y7;
    vect2_copy(x6, y6, x7, y7);
    cout << "vect2_copy(" << x6 << ", " << y6 << ") = (" << x7 << ", " << y7 << ")" << endl;

    // 测试vect3_normalize函数
    double x8 = 1.0, y8 = 2.0, z8 = 3.0;
    cout << "vect3_normalize(" << x8 << ", " << y8 << ", " << z8 << ") = ";
    vect3_normalize(x8, y8, z8);
    cout << "(" << x8 << ", " << y8 << ", " << z8 << ")" << endl;

    // 测试vect3_length函数
    double x9 = 1.0, y9 = 2.0, z9 = 3.0;
    cout << "vect3_length(" << x9 << ", " << y9 << ", " << z9<< ") = " << vect3_length(x9, y9, z9) << endl;

    // 测试vect3_div函数
    double x10 = 1.0, y10 = 2.0, z10 = 3.0;
    double s = 2.0;
    cout << "vect3_div(" << x10 << ", " << y10 << ", " << z10 << ", " << s << ") = ";
    vect3_div(x10, y10, z10, s);
    cout << "(" << x10 << ", " << y10 << ", " << z10 << ")" << endl;

    // 测试vect3_mult函数
    double x11 = 1.0, y11 = 2.0, z11 = 3.0;
    double s2 = 2.0;
    cout << "vect3_mult(" << x11 << ", " << y11 << ", " << z11 << ", " << s2 << ") = ";
    vect3_mult(x11, y11, z11, s2);
    cout << "(" << x11 << ", " << y11 << ", " << z11 << ")" << endl;

    // 测试vect3_vect3_mult函数
    double x12 = 1.0, y12 = 2.0, z12 = 3.0;
    double x13 = 2.0, y13 = 3.0, z13 = 4.0;
    cout << "vect3_vect3_mult(" << x12 << ", " << y12 << ", " << z12 << ", " << x13 << ", " << y13 << ", " << z13 << ") = ";
    vect3_vect3_mult(x12, y12, z12, x13, y13, z13);
    cout << "(" << x12 << ", " << y12 << ", " << z12 << ")" << endl;

    // 测试vect3_vect3_add函数
    double x14 = 1.0, y14 = 2.0, z14 = 3.0;
    double x15 = 2.0, y15 = 3.0, z15 = 4.0;
    cout << "vect3_vect3_add(" << x14 << ", " << y14 << ", " << z14 << ", " << x15 << ", " << y15 << ", " << z15 << ") = ";
    vect3_vect3_add(x14, y14, z14, x15, y15, z15);
    cout << "(" << x14 << ", " << y14 << ", " << z14 << ")" << endl;

    return 0;
}