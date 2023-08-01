#include "CalibrationViewController.h"

// 构造函数
CalibrationViewController::CalibrationViewController(Settings& settings, ScaleWrapper& scaleWrapper)
    : m_settings(settings), m_scaleWrapper(scaleWrapper), m_state(STATE_PRE_TARE) {}

// 渲染界面到指定的显示器对象上
void CalibrationViewController::render(U8G2 display) {
    switch (m_state) {
        case STATE_PRE_TARE:
            renderPreTareScreen(display);
            break;
        case STATE_TARING:
            renderTaringScreen(display);
            break;
        case STATE_TARED:
            renderTaredScreen(display);
            break;
        case STATE_MEASURING:
            renderMeasuringScreen(display);
            break;
        default:
            break;
    }
}

// 视图将被推入导航控制器栈顶时调用的回调函数
void CalibrationViewController::viewWillBePushed(NavigationController* controller) {}

// 视图被从导航控制器栈顶弹出时调用的回调函数
void CalibrationViewController::viewWasPopped(NavigationController* controller) {}

// 更新状态并渲染界面
void CalibrationViewController::tick(U8G2 display) {
    switch (m_state) {
        case STATE_PRE_TARE:
            break;
        case STATE_TARING:
            if (m_scaleWrapper.tare()) {
                m_state = STATE_TARED;
            }
            break;
        case STATE_TARED:
            break;
        case STATE_MEASURING:
            if (m_settings.autoTare && m_scaleWrapper.getWeight() < m_settings.tareThreshold) {
                m_scaleWrapper.tare();
            }
            break;
        default:
            break;
    }
    render(display);
}

// 处理按钮事件
void CalibrationViewController::handleButtonEvent(ButtonEvent event) {
    switch (m_state) {
        case STATE_PRE_TARE:
            if (event == BUTTON_EVENT_SELECT) {
                m_state = STATE_TARING;
            }
            break;
        case STATE_TARING:
            break;
        case STATE_TARED:
            if (event == BUTTON_EVENT_SELECT) {
                m_state = STATE_MEASURING;
            } else if (event == BUTTON_EVENT_BACK) {
                m_state = STATE_PRE_TARE;
            }
            break;
        case STATE_MEASURING:
            if (event == BUTTON_EVENT_BACK) {
                m_state = STATE_TARED;
            }
            break;
        default:
            break;
    }
}

// 渲染校准前的界面
void CalibrationViewController::renderPreTareScreen(U8G2 display) {
    display.setFont(u8g2_font_6x10_tf);
    display.drawStr(0, 10, "Place the scale on a flat");
    display.drawStr(0, 20, "and stable surface.");
    display.drawStr(0, 30, "Press SELECT to tare.");
}

// 渲染正在校准的界面
void CalibrationViewController::renderTaringScreen(U8G2 display) {
    display.setFont(u8g2_font_6x10_tf);
    display.drawStr(0, 10, "Taring...");
}

// 渲染已经校准的界面
void CalibrationViewController::renderTaredScreen(U8G2 display) {
    display.setFont(u8g2_font_6x10_tf);
    display.drawStr(0, 10, "Scale is ready.");
    display.drawStr(0, 20, "Press SELECT to start");
    display.drawStr(0, 30, "measuring or BACK to");
    display.drawStr(0, 40, "retake tare.");
}

// 渲染正在测量的界面
void CalibrationViewController::renderMeasuringScreen(U8G2 display) {
    display.setFont(u8g2_font_6x10_tf);
    display.drawStr(0, 10, "Measuring...");
    display.drawStr(0, 20, "Weight: ");
    display.setCursor(60, 20);
    display.print(m_scaleWrapper.getWeight());
}


