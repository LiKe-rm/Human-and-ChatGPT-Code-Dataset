#include <iostream>
#include <vector>
#include <string>

class Airplane {
public:
    // 静态成员变量
    static const std::string SHAPE_LEFT;
    static const std::string SHAPE_RIGHT;

    // 构造函数
    Airplane(int x, int y, const std::string& direction)
        : x_(x), y_(y), direction_(direction) {
        initSoundAndBomb();
    }

    // 成员函数1：根据实例对象的位置绘制飞机
    void draw() const {
        std::string shape = (direction_ == "left") ? SHAPE_LEFT : SHAPE_RIGHT;
        for (int i = 0; i < shape.size(); ++i) {
            if (shape[i] != ' ') {
                std::cout << shape[i];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }

    // 成员函数2：初始化飞行音效和轰炸对象
    void initSoundAndBomb() {
        // 初始化音效和轰炸对象的代码
    }

    // 成员函数3：使飞机对象发射导弹并检测轰炸结果
    bool fireMissile() {
        // 发射导弹并检测轰炸结果的代码
        return true;  // 假设总是成功击中目标
    }

    // 静态方法4：将击落飞机后的飞机炸成碎片
    static void explode(const Airplane& airplane) {
        // 将飞机炸成碎片的代码
    }

private:
    int x_;
    int y_;
    std::string direction_;
};

const std::string Airplane::SHAPE_LEFT = "  <==";
const std::string Airplane::SHAPE_RIGHT = "==>";

int main() {
    Airplane airplane1(10, 10, "left");
    Airplane airplane2(20, 20, "right");

    airplane1.draw();
    airplane2.draw();

    if (airplane1.fireMissile()) {
        std::cout << "Airplane 1 hit the target!" << std::endl;
        Airplane::explode(airplane1);
    }

    if (airplane2.fireMissile()) {
        std::cout << "Airplane 2 hit the target!" << std::endl;
        Airplane::explode(airplane2);
    }

    return 0;
}
