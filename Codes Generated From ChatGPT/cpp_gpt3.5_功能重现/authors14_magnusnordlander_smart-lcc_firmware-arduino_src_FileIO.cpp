#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <algorithm>

#include <FS.h>
#include <PicoQueue.h>

class FileIO {
public:
	FileIO(FS* fs, PicoQueue* picoqueue);
	~FileIO();

	bool readSettings(const char* filename, uint32_t* crc);
	bool writeSettings(const char* filename, const uint32_t crc, const char* data, const size_t len);
	bool readWiFiConfig(const char* filename, uint32_t* crc);
	bool writeWiFiConfig(const char* filename, const uint32_t crc, const char* data, const size_t len);

private:
	FS* m_fs;
	PicoQueue* m_picoqueue;

	uint32_t calculateCRC32(const char* data, const size_t len);
};

FileIO::FileIO(FS* fs, PicoQueue* picoqueue) {
	m_fs = fs;
	m_picoqueue = picoqueue;
}

FileIO::~FileIO() {}

bool FileIO::readSettings(const char* filename, uint32_t* crc) {
	File file = m_fs->open(filename, "r");
	if (!file) {
		std::cout << "FileIO: Failed to open file: " << filename << std::endl;
		return false;
	}

	size_t size = file.size();
	char* data = new char[size];
	if (file.readBytes(data, size) != size) {
		std::cout << "FileIO: Failed to read file: " << filename << std::endl;
		delete[] data;
		return false;
	}

	*crc = calculateCRC32(data, size);
	file.close();
	delete[] data;

	return true;
}

bool FileIO::writeSettings(const char* filename, const uint32_t crc, const char* data, const size_t len) {
	if (crc != calculateCRC32(data, len)) {
		std::cout << "FileIO: Data integrity check failed" << std::endl;
		return false;
	}

	File file = m_fs->open(filename, "w");
	if (!file) {
		std::cout << "FileIO: Failed to open file: " << filename << std::endl;
		return false;
	}

	if (file.write((const uint8_t*)data, len) != len) {
		std::cout << "FileIO: Failed to write file: " << filename << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

bool FileIO::readWiFiConfig(const char* filename, uint32_t* crc) {
	return readSettings(filename, crc);
}

bool FileIO::writeWiFiConfig(const char* filename, const uint32_t crc, const char* data, const size_t len) {
	return writeSettings(filename, crc, data, len);
}

uint32_t FileIO::calculateCRC32(const char* data, const size_t len) {
	const uint32_t POLYNOMIAL = 0xEDB88320;
	uint32_t crc = 0xFFFFFFFF;

	for (size_t i = 0; i < len; i++) {
		crc ^= (uint8_t)data[i];
		for (size_t j = 0; j < 8; j++) {
			if (crc & 0x01) {
				crc = (crc >> 1) ^ POLYNOMIAL;
			}
			else {
				crc >>= 1;
			}
		}
	}

	return ~crc;
}