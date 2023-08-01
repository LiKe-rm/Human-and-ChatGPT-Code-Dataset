#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <filesystem>

using namespace std;

enum UStatus {
    U_SUCCESS = 0,
    U_INVALID_ARGUMENT,
    U_ITEM_NOT_FOUND,
    U_ERROR
};

enum UParseMode {
    U_MODE_SECTION,
    U_MODE_FILE
};

struct UGUID {
    unsigned long data1;
    unsigned short data2;
    unsigned short data3;
    unsigned char data4[8];
};

struct USectionHeader {
    UGUID sectionType;
    unsigned int dataSize;
    unsigned int dataOffset;
    unsigned int attr;
};

struct UFileHeader {
    unsigned int size;
    unsigned short nameLength;
    unsigned short attribute;
    UGUID fileType;
    char name[1];
};

class FfsDumper {
public:
    FfsDumper(const char* filename, const char* outdir, UParseMode mode, UGUID guid);
    ~FfsDumper();
    UStatus dump();
private:
    UStatus parseSection(USectionHeader* section);
    UStatus parseFile(UFileHeader* file, char* fileData);
    void dumpToFile(char* data, int size, const char* filename);
    void dumpToTextFile(const char* message, const char* filename);
    void createDir(const char* path);
    UStatus recursiveDump(char* data, unsigned int size, UParseMode mode);
    UStatus recursiveDumpSection(USectionHeader* section);
    UStatus recursiveDumpFile(UFileHeader* file, char* fileData);

    ifstream m_infile;
    string m_outdir;
    UGUID m_guid;
};

FfsDumper::FfsDumper(const char* filename, const char* outdir, UParseMode mode, UGUID guid) :
    m_infile(filename, ios::in | ios::binary),
    m_outdir(outdir),
    m_guid(guid)
{
}

FfsDumper::~FfsDumper() {
    if (m_infile.is_open()) {
        m_infile.close();
    }
}

UStatus FfsDumper::dump() {
    if (!m_infile.is_open()) {
        return U_INVALID_ARGUMENT;
    }
    if (filesystem::exists(m_outdir)) {
        return U_INVALID_ARGUMENT;
    }

    filesystem::create_directories(m_outdir);

    UStatus status = recursiveDump(nullptr, 0, U_MODE_SECTION);

    if (status != U_SUCCESS) {
        filesystem::remove_all(m_outdir);
        return status;
    }

    if (filesystem::is_empty(m_outdir)) {
        filesystem::remove_all(m_outdir);
        return U_ITEM_NOT_FOUND;
    }

    return U_SUCCESS;
}

UStatus FfsDumper::recursiveDump(char* data, unsigned int size, UParseMode mode) {
    if (data == nullptr) {
        m_infile.seekg(0, ios::end);
        size = (unsigned int)m_infile.tellg();
        m_infile.seekg(0, ios::beg);

        data = new char[size];
        m_infile.read(data, size);
    }

    if (mode == U_MODE_SECTION) {
        USectionHeader* section = reinterpret_cast<USectionHeader*>(data);

        while ((char*)section - data < size) {
            UStatus status = recursiveDumpSection(section);

            if (status != U_SUCCESS) {
                delete[] data;
                return status;
            }

            section = reinterpret_cast<USectionHeader*>((char*)section + sizeof(USectionHeader) + section->dataSize);
        }
    }
    else if (mode == U_MODE_FILE) {
        UFileHeader* file = reinterpret_cast<UFileHeader*>(data);

        while ((char*)file - data < size) {
            UStatus status = recursiveDumpFile(file, data + file->nameLength + sizeof(UFileHeader));

            if (status != U_SUCCESS) {
                delete[] data;
                return status;
            }

            file = reinterpret_cast<UFileHeader*>((char*)file + file->size);
        }
    }

    delete[] data;

    return U_SUCCESS;
}

UStatus FfsDumper::recursiveDumpSection(USectionHeader* section) {
    if (section->dataOffset < sizeof(USectionHeader) || section->dataOffset + section->dataSize > m_infile.tellg()) {
        return U_ERROR;
    }
    if (memcmp(&section->sectionType, &m_guid, sizeof(UGUID)) != 0) {
    return U_SUCCESS;
    }

    char* sectionData = new char[section->dataSize];

    m_infile.seekg(section->dataOffset, ios::beg);
    m_infile.read(sectionData, section->dataSize);

    UStatus status = parseSection(sectionData);

    if (status != U_SUCCESS) {
        delete[] sectionData;
        return status;
    }

    status = recursiveDump(sectionData, section->dataSize, U_MODE_FILE);

    if (status != U_SUCCESS) {
        delete[] sectionData;
        return status;
    }

    delete[] sectionData;

    return U_SUCCESS;
}

UStatus FfsDumper::recursiveDumpFile(UFileHeader* file, char* fileData) {
    if (memcmp(&file->fileType, &m_guid, sizeof(UGUID)) != 0) {
        return U_SUCCESS;
    }
    dumpToFile(fileData, file->size - file->nameLength - sizeof(UFileHeader), file->name);
    dumpToTextFile("additional information", file->name);

    return U_SUCCESS;
}

UStatus FfsDumper::parseSection(USectionHeader* section) {
    // TODO: implement section parsing logic
    return U_SUCCESS;
}

UStatus FfsDumper::parseFile(UFileHeader* file, char* fileData) {
    // TODO: implement file parsing logic
    return U_SUCCESS;
}

void FfsDumper::dumpToFile(char* data, int size, const char* filename) {
    ofstream outfile(m_outdir + "\\" + filename, ios::out | ios::binary);
    if (outfile.is_open()) {
        outfile.write(data, size);
        outfile.close();
    }
}

void FfsDumper::dumpToTextFile(const char* message, const char* filename) {
    ofstream outfile(m_outdir + "\\" + filename + ".txt", ios::out);
    if (outfile.is_open()) {
        outfile << message;
        outfile.close();
    }
}

void FfsDumper::createDir(const char* path) {
    filesystem::create_directory(path);
}



