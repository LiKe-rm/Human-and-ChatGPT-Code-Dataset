#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 定义邮件消息类
class CKMailMessage {
private:
	vector<string> recipients; // 收件人列表
	string subject; // 邮件主题
	string body; // 邮件正文
	vector<string> attachments; // 附件列表

public:
	// 默认构造函数
	CKMailMessage() {}

	// 构造函数，根据给定的收件人列表，主题和正文创建邮件消息
	CKMailMessage(vector<string> r, string s, string b) {
		recipients = r;
		subject = s;
		body = b;
	}

	// 拷贝构造函数
	CKMailMessage(const CKMailMessage& m) {
		recipients = m.recipients;
		subject = m.subject;
		body = m.body;
		attachments = m.attachments;
	}

	// 析构函数
	~CKMailMessage() {}

	// 赋值运算符
	CKMailMessage& operator=(const CKMailMessage& m) {
		if (this != &m) {
			recipients = m.recipients;
			subject = m.subject;
			body = m.body;
			attachments = m.attachments;
		}
		return *this;
	}

	// 设置邮件消息的收件人列表
	void SetRecipients(vector<string> r) {
		recipients = r;
	}

	// 设置邮件消息的主题
	void SetSubject(string s) {
		subject = s;
	}

	// 设置邮件消息的正文
	void SetBody(string b) {
		body = b;
	}

	// 获取邮件消息的收件人列表
	vector<string> GetRecipients() const {
		return recipients;
	}

	// 获取邮件消息的主题
	string GetSubject() const {
		return subject;
	}

	// 获取邮件消息的正文
	string GetBody() const {
		return body;
	}

	// 向邮件消息的收件人列表中添加一个收件人地址
	void AddRecipient(string r) {
		recipients.push_back(r);
	}

	// 将字符串添加到邮件消息的正文中
	void AppendBody(string b) {
		body += b;
	}

	// 添加附件到邮件消息的正文中
	void AddAttachment(string a) {
		attachments.push_back(a);
		body += "\nAttachment: " + a;
	}

	// 添加另一个邮件消息作为附件到邮件消息的正文中
	void AddAttachment(CKMailMessage m) {
		string mime = m.GetMIME(); // 获取另一个邮件消息的MIME表示
		attachments.push_back(mime);
		body += "\nAttachment: " + mime;
	}

	// 从邮件消息的收件人列表中删除一个收件人地址
	void RemoveRecipient(string r) {
		for (vector<string>::iterator it = recipients.begin(); it != recipients.end(); ++it) {
			if (*it == r) {
				recipients.erase(it);
				break;
			}
		}
	}

	// 判断邮件消息的正文是否为空
	bool IsBodyEmpty() const {
		return body.empty();
	}

	// 判断邮件消息是否可以被发送
	bool CanBeSent() const {
		return !recipients.empty() && !subject.empty() && !body.empty();
	}
	// 判断邮件消息是否为MIME消息
	bool IsMIME() const {
		return !attachments.empty();
	}

	// 获取邮件消息的字符串表示形式
	string ToString() const {
		string str = "To: ";
		for (vector<string>::const_iterator it = recipients.begin(); it != recipients.end(); ++it) {
			str += *it + ", ";
		}
		str = str.substr(0, str.length() - 2) + "\n";
		str += "Subject: " + subject + "\n";
		str += "Body: " + body + "\n";
		if (!attachments.empty()) {
			str += "Attachments: ";
			for (vector<string>::const_iterator it = attachments.begin(); it != attachments.end(); ++it) {
				str += *it + ", ";
			}
			str = str.substr(0, str.length() - 2) + "\n";
		}
		return str;
	}

	// 判断两个邮件消息是否相等
	bool operator==(const CKMailMessage& m) const {
		return recipients == m.recipients && subject == m.subject && body == m.body && attachments == m.attachments;
	}

	// 判断两个邮件消息是否不相等
	bool operator!=(const CKMailMessage& m) const {
		return !(*this == m);
	}

	// 获取消息元素的MIME内容类型
	string GetMIMEType() const {
		return "text/plain";
	}

	// 编码消息元素，以便将其作为附件添加到邮件消息中
	string EncodeMIME() const {
		return body; // 简单地将邮件正文作为MIME内容
	}

	// 获取整个邮件消息的MIME表示形式
	string GetMIME() const {
		string mime = "From: me@example.com\n"; // 假设发件人是me@example.com
		mime += "To: ";
		for (vector<string>::const_iterator it = recipients.begin(); it != recipients.end(); ++it) {
			mime += *it + ", ";
		}
		mime = mime.substr(0, mime.length() - 2) + "\n";
		mime += "Subject: " + subject + "\n";
		if (!attachments.empty()) {
			// 如果存在附件，则设置邮件消息的MIME类型为multipart/mixed
			mime += "MIME-Version: 1.0\n";
			mime += "Content-Type: multipart/mixed; boundary=\"boundary\"\n\n";
			mime += "--boundary\n";
			mime += "Content-Type: text/plain\n\n";
		}
		mime += body;
		if (!attachments.empty()) {
			for (vector<string>::const_iterator it = attachments.begin(); it != attachments.end(); ++it) {
				mime += "\n--boundary\n";
				mime += "Content-Type: " + GetMIMEType() + "\n";
				mime += "Content-Transfer-Encoding: base64\n\n";
				mime += EncodeMIME();
			}
			mime += "\n--boundary--";
		}
		return mime;
	}
};

int main() {
	// 创建邮件消息对象并设置其属性
	CKMailMessage message;
	message.AddRecipient("john@example.com");
	message.SetSubject("Test Message");
	message.SetBody("This is a test message.");
	message.AddAttachment("attachment.txt");
	// 输出邮件消息的字符串表示形式和MIME
	cout << "Message:\n" << message.ToString() << endl;
	cout << "MIME:\n" << message.GetMIME() << endl;

	return 0;
}
