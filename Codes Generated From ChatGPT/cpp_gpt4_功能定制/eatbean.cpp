#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

// 定义游戏对象的基本属性
const int mazeWidth = 20;
const int mazeHeight = 20;
const float cellSize = 25.0f;

// 游戏对象
struct Pacman {
    float x, y;
    int direction;
} pacman;

// 函数声明
void display();
void keyboard(unsigned char key, int x, int y);
void timer(int = 0);

int main(int argc, char **argv) {
    srand(static_cast<unsigned int>(time(0)));

    // 初始化Pacman
    pacman.x = mazeWidth / 2 * cellSize;
    pacman.y = mazeHeight / 2 * cellSize;
    pacman.direction = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(mazeWidth * cellSize, mazeHeight * cellSize);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pacman");
    glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, mazeWidth * cellSize, mazeHeight * cellSize, 0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    timer();

    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制Pacman
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 45) {
        float theta = static_cast<float>(i) * 3.14159 / 180.0;
        float x = pacman.x + cellSize / 2 * cos(theta);
        float y = pacman.y + cellSize / 2 * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    // 处理键盘输入
    switch (key) {
        case 'w':
            pacman.direction = 1;
            break;
        case 's':
            pacman.direction = 2;
            break;
        case 'a':
            pacman.direction = 3;
            break;
        case 'd':
            pacman.direction = 4;
            break;
    }
}

void timer(int) {
    // 移动Pacman
    switch (pacman.direction) {
        case 1:
            pacman.y -= 1;
            break;
        case 2:
            pacman.y += 1;
            break;
        case 3:
            pacman.x -= 1;
            break;
        case 4:
            pacman.x += 1;
            break;
    }

    // 边界检查
    if (pacman.x < 0) pacman.x = 0;
    if (pacman.y < 0) pacman.y = 0;
    if (pacman.x > (mazeWidth - 1) * cellSize) pacman.x = (mazeWidth - 1) * cellSize;
    if (pacman.y > (mazeHeight - 1) * cellSize) pacman.y = (mazeHeight - 1) * cellSize;

    // 更新屏幕
    glutPostRedisplay();

    // 设置下一个定时器事件
    glutTimerFunc(15, timer, 0);
}