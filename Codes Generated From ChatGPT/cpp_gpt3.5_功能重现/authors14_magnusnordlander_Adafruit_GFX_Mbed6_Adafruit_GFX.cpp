#include <Arduino.h>

class Adafruit_GFX {
public:
	Adafruit_GFX(int16_t w, int16_t h); // 构造函数，传入宽度和高度
	virtual ~Adafruit_GFX(); // 析构函数
	virtual void drawPixel(int16_t x, int16_t y, uint16_t color); // 绘制单个像素点
	virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color); // 绘制直线
	virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color); // 绘制矩形
	virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color); // 填充矩形
	virtual void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color); // 绘制圆形
	virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color); // 填充圆形
	virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color); // 绘制圆角矩形
	virtual void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color); // 填充圆角矩形
	virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color); // 绘制三角形
	virtual void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color); // 填充三角形
	virtual void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color); // 绘制位图
	virtual void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size); // 绘制单个字符
	virtual void setCursor(int16_t x, int16_t y); // 设置光标位置
	virtual void setTextColor(uint16_t color); // 设置文本颜色
	virtual void setTextSize(uint8_t size); // 设置文本大小
	virtual void setTextWrap(bool wrap); // 设置文本是否自动换行
	virtual void setRotation(uint8_t r); // 设置屏幕旋
private:
	int16_t _width; // 屏幕宽度
	int16_t _height; // 屏幕高度
	int16_t cursor_x; // 光标x坐标
	int16_t cursor_y; // 光标y坐标
	uint16_t textcolor; // 文本颜色
	uint8_t textsize; // 文本大小
	bool wrap; // 是否自动换行
	uint8_t rotation; // 屏幕旋转角度
	// 以下是一些辅助函数
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
	void drawRoundRectHelper(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
	void fillRoundRectHelper(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
	void drawTriangleHelper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void fillTriangleHelper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
};

Adafruit_GFX::Adafruit_GFX(int16_t w, int16_t h) {
	_width = w;
	_height = h;
	cursor_x = 0;
	cursor_y = 0;
	textcolor = 0xFFFF;
	textsize = 1;
	wrap = true;
	rotation = 0;
}

Adafruit_GFX::~Adafruit_GFX() {}

void Adafruit_GFX::drawPixel(int16_t x, int16_t y, uint16_t color) {
	// 绘制单个像素点
	// 具体实现根据不同的显示设备来决定
}

void Adafruit_GFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
	// 绘制直线
	// Bresenham算法实现
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx = x1 - x0, dy = abs(y1 - y0);

	int16_t err = dx / 2, ystep;

	if (y0 < y1) {
		ystep = 1;
	}
	else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			drawPixel(y0, x0, color);
		}
		else {
			drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void Adafruit_GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	// 绘制矩形
	drawLine(x, y, x + w - 1, y, color);
	drawLine(x, y, x, y + h - 1, color);
	drawLine(x + w - 1, y, x + w - 1, y + h - 1, color);
	drawLine(x, y + h - 1, x + w - 1, y + h - 1, color);
}

void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	// 填充矩形
	for (int16_t i = x; i < x + w; i++) {
		for (int16_t j = y; j < y + h; j++) {
			drawPixel(i, j, color);
		}
	}
}

void Adafruit_GFX::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
	// 绘制圆形
	drawCircleHelper(x0, y0, r, 0x01, color);
}

void Adafruit_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
	// 填充圆形
	drawCircleHelper(x0, y0, r, 0x01, color);
	fillCircleHelper(x0, y0, r, 0x01, 0, color);
}

void Adafruit_GFX::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color) {
	// 绘制圆角矩形
	drawRoundRectHelper(x, y, w, h, radius, color);
}

void Adafruit_GFX::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color) {
	// 填充圆角矩形
	drawRoundRectHelper(x, y, w, h, radius, color);
	fillRoundRectHelper(x, y, w, h, radius, color);
}

void Adafruit_GFX::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	// 绘制三角形
	drawTriangleHelper(x0, y0, x1, y1, x2, y2, color);
}

void Adafruit_GFX::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	// 填充三角形
	drawTriangleHelper(x0, y0, x1, y1, x2, y2, color);
	fillTriangleHelper(x0, y0, x1, y1, x2, y2, color);
}

void Adafruit_GFX::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap, int16_t w, int16_t h, uint16_t color) {
	// 绘制位图
	for (int16_t j = 0; j < h; j++) {
		for (int16_t i = 0; i < w; i++) {
			if ((bitmap + i + j * w)) {
				drawPixel(x + i, y + j, color);
			}
		}
	}
}

void Adafruit_GFX::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
	// 绘制单个字符
	// 具体实现根据不同的显示设备和字体库来决定
}

void Adafruit_GFX::setCursor(int16_t x, int16_t y) {
	// 设置光标位置
	cursor_x = x;
	cursor_y = y;
}

void Adafruit_GFX::setTextColor(uint16_t color) {
	// 设置文本颜色
	textcolor = color;
}

void Adafruit_GFX::setTextSize(uint8_t size) {
	// 设置文本大小
	textsize = size;
}

void Adafruit_GFX::setTextWrap(bool wrap) {
	// 设置文本是否自动换行
	wrap = wrap;
}

void Adafruit_GFX::setRotation(uint8_t r) {
	// 设置屏幕旋转角度
	rotation = r % 4;
	switch (rotation) {
	case 0:
	case 2:
		_width = 128;
		_height = 64;
		break;
	case 1:
	case 3:
		_width = 64;
		_height = 128;
		break;
	}
}

void Adafruit_GFX::drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
	// 绘制圆形的某个部分
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x4) {
			drawPixel(x0 + x, y0 + y, color);
			drawPixel(x0 + y, y0 + x, color);
		}

		if (cornername & 0x2) {
			drawPixel(x0 + x, y0 - y, color);
			drawPixel(x0 + y, y0 - x, color);
		}

		if (cornername & 0x8) {
			drawPixel(x0 - y, y0 + x, color);
			drawPixel(x0 - x, y0 + y, color);
		}

		if (cornername & 0x1) {
			drawPixel(x0 - y, y0 - x, color);
			drawPixel(x0 - x, y0 - y, color);
		}
	}
}

void Adafruit_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
	// 填充圆形的某个部分
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x1) {
			drawLine(x0 + x, y0 - y + delta, x0 + x, y0 - delta, color);
			drawLine(x0 + y, y0 - x + delta, x0 + y, y0 - delta, color);
		}

		if (cornername & 0x2) {
			drawLine(x0 - x, y0 - y + delta, x0 - x, y0 - delta, color);
			drawLine(x0 - y, y0 - x + delta, x0 - y, y0 - delta, color);
		}
	}
}

void Adafruit_GFX::drawRoundRectHelper(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
	// 绘制圆角矩形的边框
	drawLine(x + r, y, x + w - r - 1, y, color);
	drawLine(x + r, y + h - 1, x + w - r - 1, y + h - 1, color);
	drawLine(x, y + r, x, y + h - r - 1, color);
	drawLine(x + w - 1, y + r, x + w - 1, y + h - r - 1, color);
	drawCircleHelper(x + r, y + r, r, 0x1, color);
	drawCircleHelper(x + w - r - 1, y + r, r, 0x2, color);
	drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 0x4, color);
	drawCircleHelper(x + r, y + h - r - 1, r, 0x8, color);
}

void Adafruit_GFX::fillRoundRectHelper(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
	// 填充圆角矩形的中间部分
	for (int16_t i = x + r; i < x + w - r; i++) {
		for (int16_t j = y + r; j < y + h - r; j++) {
			drawPixel(i, j, color);
		}
	}

	fillCircleHelper(x + w - r - 1, y + r, r, 0x2, h - 2 * r - 1, color);
	fillCircleHelper(x + r, y + r, r, 0x1, h - 2 * r - 1, color);
	fillCircleHelper(x + r, y + h - r - 1, r, 0x8, w - 2 * r - 1, color);
}

void Adafruit_GFX::drawTriangleHelper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	// 绘制三角形的边框
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}

void Adafruit_GFX::fillTriangleHelper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	// 填充三角形的中间部分
	int16_t a, b, y, last;
	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1);
		swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}

	if (y0 == y2) {
		a = b = x0;
		if (x1 < a) {
			a = x1;
		}
		else if (x1 > b) {
			b = x1;
		}
		if (x2 < a) {
			a = x2;
		}
		else if (x2 > b) {
			b = x2;
		}
		drawFastHLine(a, y0, b - a + 1, color);
		return;
	}

	int16_t dx01 = x1 - x0;
	int16_t dy01 = y1 - y0;
	int16_t dx02 = x2 - x0;
	int16_t dy02 = y2 - y0;
	int16_t dx12 = x2 - x1;
	int16_t dy12 = y2 - y1;
	int32_t sa = 0;
	int32_t sb = 0;

	if (y1 == y2) {
		last = y1;
	}
	else {
		last = y1 - 1;
	}

	for (y = y0; y <= last; y++) {
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		if (a > b) {
			swap(a, b);
		}
		drawFastHLine(a, y, b - a + 1, color);
	}

	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);

	for (; y <= y2; y++) {
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if (a > b) {
			swap(a, b);
		}
		drawFastHLine(a, y, b - a + 1, color);
	}
}
void Adafruit_GFX::setFont(const uint8_t* font) {
	// 设置字体库
	currentFont = font;
}

void Adafruit_GFX::drawCharAtPos(int16_t x, int16_t y, uint8_t c, uint16_t color) {
	// 绘制单个字符，指定位置和颜色
	uint8_t width = pgm_read_byte(currentFont + FONT_WIDTH_OFFSET);
	uint8_t height = pgm_read_byte(currentFont + FONT_HEIGHT_OFFSET);
	uint8_t firstChar = pgm_read_byte(currentFont + FONT_FIRST_CHAR_OFFSET);
	uint16_t index = (c - firstChar) * ((width + 7) / 8) * height + FONT_DATA_OFFSET;
	uint8_t bits = 0, bitCount = 0;

	for (int16_t j = 0; j < height; j++) {
		for (int16_t i = 0; i < width; i++) {
			if (bitCount == 0) {
				bits = pgm_read_byte(currentFont + index++);
				bitCount = 8;
			}
			if (bits & 0x80) {
				drawPixel(x + i, y + j, color);
			}
			bits <<= 1;
			bitCount--;
		}
	}
}

void Adafruit_GFX::drawString(const char* string, uint16_t color) {
	// 绘制字符串
	uint8_t width = pgm_read_byte(currentFont + FONT_WIDTH_OFFSET);
	uint8_t height = pgm_read_byte(currentFont + FONT_HEIGHT_OFFSET);
	int16_t x = cursor_x, y = cursor_y;
	while (*string) {
		if (wrap && (x + width * textsize >= _width)) {
			x = 0;
			y += height * textsize;
		}
		drawCharAtPos(x, y, *string++, color);
		x += width * textsize;
	}
	cursor_x = x;
	cursor_y = y;
}

void Adafruit_GFX::drawStringAtPos(int16_t x, int16_t y, const char* string, uint16_t color) {
	// 绘制字符串，指定位置和颜色
	setCursor(x, y);
	drawString(string, color);
}

uint8_t Adafruit_GFX::getRotation(void) const {
	// 获取屏幕旋转角度
	return rotation;
}

int16_t Adafruit_GFX::getWidth(void) const {
	// 获取屏幕宽度
	return _width;
}

int16_t Adafruit_GFX::getHeight(void) const {
	// 获取屏幕高度
	return _height;
}