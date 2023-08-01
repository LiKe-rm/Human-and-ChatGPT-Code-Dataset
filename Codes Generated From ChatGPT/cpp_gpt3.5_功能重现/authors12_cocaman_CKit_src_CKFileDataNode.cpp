#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CKDataNode.h"

class CKFileDataNode : public CKDataNode {
public:
	CKFileDataNode() : m_fileName(""), m_separator(','), m_lastHeaderRow(-1) {}
	CKFileDataNode(const std::string& fileName, char separator, int lastHeaderRow = -1) : m_fileName(fileName), m_separator(separator), m_lastHeaderRow(lastHeaderRow) {}
	CKFileDataNode(const CKFileDataNode& other) : m_fileName(other.m_fileName), m_separator(other.m_separator), m_lastHeaderRow(other.m_lastHeaderRow), m_dataNodes(other.m_dataNodes) {}
	~CKFileDataNode() {}

	void setFileName(const std::string& fileName) { m_fileName = fileName; }
	void setSeparator(char separator) { m_separator = separator; }
	void setLastHeaderRow(int lastHeaderRow) { m_lastHeaderRow = lastHeaderRow; }
	void processData();

	void loadAsync();
	void waitForLoad();

private:
	static const int MAX_LINE_LENGTH = 1024;
	static const int MAX_NUM_COLUMNS = 256;

	std::string m_fileName;
	char m_separator;
	int m_lastHeaderRow;
	std::vector<std::vector<std::string>> m_dataNodes;

	void loadFile();
	void splitLine(const std::string& line, std::vector<std::string>& tokens);
};

void CKFileDataNode::processData() {
	// clear any existing data nodes
	m_dataNodes.clear();

	// load the file data into memory
	loadFile();

	// create the data nodes
	int numHeaderRows = (m_lastHeaderRow < 0) ? 1 : m_lastHeaderRow + 1;
	int numColumns = 0;
	for (int i = numHeaderRows; i < m_dataNodes.size(); ++i) {
		if (m_dataNodes[i].size() > numColumns) {
			numColumns = m_dataNodes[i].size();
		}
	}

	for (int i = numHeaderRows; i < m_dataNodes.size(); ++i) {
		CKDataNode* node = new CKDataNode();

		for (int j = 0; j < numColumns; ++j) {
			std::string value = (j < m_dataNodes[i].size()) ? m_dataNodes[i][j] : "";
			node->addAttribute("Column_" + std::to_string(j), value);
		}

		addSubNode(node);
	}
}

void CKFileDataNode::loadAsync() {
	std::thread t(&CKFileDataNode::loadFile, this);
	t.detach();
}

void CKFileDataNode::waitForLoad() {
	// wait for the data to finish loading
	while (m_dataNodes.empty()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void CKFileDataNode::loadFile() {
	std::ifstream inputFile(m_fileName);

	if (!inputFile.is_open()) {
		std::cerr << "Unable to open file: " << m_fileName << std::endl;
		return;
	}

	std::string line;
	int lineNumber = 0;
	while (std::getline(inputFile, line)) {
		++lineNumber;
		if (lineNumber <= m_lastHeaderRow) {
			continue;
		}

		std::vector<std::string> tokens;
		splitLine(line, tokens);
		m_dataNodes.push_back(tokens);
	}
	inputFile.close();
}

void CKFileDataNode::splitLine(const std::string& line, std::vectorstd::string& tokens) {
	std::stringstream ss(line);
	std::string token;
	while (std::getline(ss, token, m_separator)) {
		tokens.push_back(token);
	}
}
