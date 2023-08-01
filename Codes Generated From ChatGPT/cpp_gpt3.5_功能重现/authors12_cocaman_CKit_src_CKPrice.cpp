#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

class CKPrice {
public:
	// 三个构造函数
	CKPrice() : usd_(0.0), local_(0.0), exchange_rate_(1.0) {}
	CKPrice(double usd) : usd_(usd), local_(usd), exchange_rate_(1.0) {}
	CKPrice(double usd, double local, double exchange_rate) : usd_(usd), local_(local), exchange_rate_(exchange_rate) {}

	// 设置价格函数
	void setUSD(double usd) { usd_ = usd; local_ = usd * exchange_rate_; }
	void setUSD(double usd) const { throw std::logic_error("Cannot modify const object."); }
	void setLocal(double local) { local_ = local; usd_ = local / exchange_rate_; }
	void setLocal(double local) const { throw std::logic_error("Cannot modify const object."); }

	// 数学运算函数
	CKPrice operator+(const CKPrice& other) const { return CKPrice(usd_ + other.usd_, local_ + other.local_, exchange_rate_); }
	CKPrice operator-(const CKPrice& other) const { return CKPrice(usd_ - other.usd_, local_ - other.local_, exchange_rate_); }
	CKPrice operator*(double factor) const { return CKPrice(usd_ * factor, local_ * factor, exchange_rate_); }
	CKPrice operator/(double divisor) const { return CKPrice(usd_ / divisor, local_ / divisor, exchange_rate_); }

	// 赋值运算符重载
	CKPrice& operator=(const CKPrice& other) {
		usd_ = other.usd_;
		local_ = other.local_;
		exchange_rate_ = other.exchange_rate_;
		return *this;
	}

	// 将价格转换为字符串并输出
	friend std::ostream& operator<<(std::ostream& os, const CKPrice& price) {
		os << price.toString();
		return os;
	}

	// 将价格编码为字符串
	std::string generateCodeFromValues() const {
		std::ostringstream ss;
		ss << usd_ << "|" << local_ << "|" << exchange_rate_;
		return ss.str();
	}

	// 从编码的字符串中提取价格值
	void takeValuesFromCode(const std::string& code) {
		std::istringstream ss(code);
		std::string token;
		if (!std::getline(ss, token, '|') || !isDouble(token))
			throw std::invalid_argument("Invalid USD value in code.");
		usd_ = std::stod(token);
		if (!std::getline(ss, token, '|') || !isDouble(token))
			throw std::invalid_argument("Invalid local value in code.");
		local_ = std::stod(token);
		if (!std::getline(ss, token, '|') || !isDouble(token))
			throw std::invalid_argument("Invalid exchange rate in code.");
		exchange_rate_ = std::stod(token);
	}

	// 将价格值格式化为字符串
	std::string toString() const {
		std::ostringstream ss;
		ss << "USD " << usd_ << ", Local " << local_;
		return ss.str();
	}

private:
	double usd_;
	double local_;
	double exchange_rate_;

};

// 判断字符串是否表示一个浮点数
bool isDouble(const std::string& s) {
	std::istringstream ss(s);
	double d;
	return (ss >> d) && ss.eof();
}

int main() {
	try {
		CKPrice price1; // 默认构造函数
		std::cout << "Price 1: " << price1 << std::endl;
		CKPrice price2(50.0); // 使用美元构造函数
		std::cout << "Price 2: " << price2 << std::endl;

		CKPrice price3(50.0, 300.0, 6.0); // 使用美元和本地价格构造函数
		std::cout << "Price 3: " << price3 << std::endl;

		price1.setUSD(25.0); // 设置美元价格
		std::cout << "Price 1 after setUSD: " << price1 << std::endl;

		price1.setLocal(150.0); // 设置本地价格
		std::cout << "Price 1 after setLocal: " << price1 << std::endl;

		CKPrice price4 = price2 + price3; // 加法运算
		std::cout << "Price 4: " << price4 << std::endl;

		CKPrice price5 = price3 - price2; // 减法运算
		std::cout << "Price 5: " << price5 << std::endl;

		CKPrice price6 = price3 * 2.0; // 乘法运算
		std::cout << "Price 6: " << price6 << std::endl;

		CKPrice price7 = price3 / 3.0; // 除法运算
		std::cout << "Price 7: " << price7 << std::endl;

		std::string code = price3.generateCodeFromValues(); // 将价格编码为字符串
		std::cout << "Code: " << code << std::endl;

		CKPrice price8;
		price8.takeValuesFromCode(code); // 从编码的字符串中提取价格值
		std::cout << "Price 8: " << price8 << std::endl;

		price1.setUSD(25.0); // 尝试修改const对象
		price1.setUSD(25.0) const; // 尝试修改const对象
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}