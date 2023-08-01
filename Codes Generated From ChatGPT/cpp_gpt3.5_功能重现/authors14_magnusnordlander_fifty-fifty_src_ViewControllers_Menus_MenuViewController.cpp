#include <U8g2lib.h>

// 定义菜单项高度和行间距
#define MENU_ITEM_HEIGHT 16
#define MENU_ITEM_SPACING 2

// 菜单项结构体
struct MenuItem {
	const char* title;  // 菜单项标题
	void (*handler)();  // 菜单项点击处理函数
};

class MenuViewController {
public:
	MenuViewController(const char* title, const MenuItem* items, int itemCount);
	void render(U8G2 display);
	void handleRotation(int encoderDiff);
	void handleButtonEvent(ButtonEvent event);
	void viewWillBePopped(NavigationController* controller);

private:
	const char* m_title;          // 菜单标题
	const MenuItem* m_items;      // 菜单项数组
	int m_itemCount;              // 菜单项数量
	int m_selectedIndex;          // 当前选中的菜单项索引
	unsigned short m_scrollOffset;  // 当前滚动偏移量
	unsigned short m_viewHeight;    // 视图高度，用于计算菜单项的 Y 坐标

	unsigned short translateYCoordinate(unsigned short coordinate) const;
};

MenuViewController::MenuViewController(const char* title, const MenuItem* items, int itemCount)
	: m_title(title), m_items(items), m_itemCount(itemCount), m_selectedIndex(0), m_scrollOffset(0), m_viewHeight(0) {
	// 计算视图高度
	m_viewHeight = (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING) * itemCount;
}

unsigned short MenuViewController::translateYCoordinate(unsigned short coordinate) const {
	// 计算菜单项在屏幕上的 Y 坐标
	unsigned short y = (coordinate * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING)) + MENU_ITEM_SPACING - m_scrollOffset;
	return y;
}

void MenuViewController::render(U8G2 display) {
	// 绘制菜单标题
	display.drawStr(0, 0, m_title);

	// 绘制菜单项
	for (int i = 0; i < m_itemCount; i++) {
		// 计算菜单项在屏幕上的位置
		unsigned short y = translateYCoordinate(i);

		// 绘制菜单项的背景
		if (i == m_selectedIndex) {
			display.drawBox(0, y, display.getWidth(), MENU_ITEM_HEIGHT, U8G2_DRAW_XOR);
		}
		else {
			display.drawBox(0, y, display.getWidth(), MENU_ITEM_HEIGHT, U8G2_DRAW_COPY);
		}

		// 绘制菜单项的标题
		display.drawStr(2, y + 12, m_items[i].title);
	}

	// 绘制滚动条
	unsigned short scrollbarHeight = (display.getHeight() * m_viewHeight) / ((MENU_ITEM_HEIGHT + MENU_ITEM_SPACING) * m_itemCount);
	unsigned short scrollbarOffset = (display.getHeight() * m_scrollOffset) / m_viewHeight;
	display.drawBox(display.getWidth() - 2, scrollbarOffset, 2, scrollbarHeight, U8G2_DRAW_COPY);
}

void MenuViewController::handleRotation(int encoderDiff) {
	// 更新选中的菜单项

// 获取当前滚动偏移量
	int maxScrollOffset = m_viewHeight - (display.getHeight() - MENU_ITEM_SPACING);
	if (maxScrollOffset < 0) maxScrollOffset = 0;
}

void MenuViewController::handleButtonEvent(ButtonEvent event) {
	// 处理按键事件
	switch (event) {
	case ButtonEvent::SingleClick:
		// 调用当前选中菜单项的处理函数
		if (m_items[m_selectedIndex].handler) {
			m_items[m_selectedIndex].handler();
		}
		break;
	case ButtonEvent::LongPress:
		// 清空滚动偏移量
		m_scrollOffset = 0;
		break;
	}
}

void MenuViewController::viewWillBePopped(NavigationController* controller) {
	// 清空滚动偏移量
	m_scrollOffset = 0;
}