#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

class TGAImg {
public:
    TGAImg();
    ~TGAImg();
    int Load(const std::string& filename);
    int GetBPP();
    int GetWidth();
    int GetHeight();
    unsigned char* GetImg();
    unsigned char* GetPalette();

private:
    short int iWidth, iHeight, iBPP;
    unsigned long lImageSize;
    char bEnc;
    unsigned char *pImage, *pPalette, *pData;
    int ReadHeader();
    int LoadRawData();
    int LoadTgaRLEData();
    int LoadTgaPalette();
    void BGRtoRGB();
    void FlipImg();
    void InvertImage();
};

TGAImg::TGAImg()
    : iWidth(0), iHeight(0), iBPP(0), lImageSize(0),
    bEnc(0), pImage(nullptr), pPalette(nullptr), pData(nullptr) {}

TGAImg::~TGAImg() {
    if (pImage) {
        delete[] pImage;
        pImage = nullptr;
    }

    if (pPalette) {
        delete[] pPalette;
        pPalette = nullptr;
    }

    if (pData) {
        delete[] pData;
        pData = nullptr;
    }
}

int TGAImg::Load(const std::string& filename) {
    std::ifstream fIn(filename.c_str(), std::ios::binary);
    if (!fIn) return false;

    if (!ReadHeader()) return false;

    if (!pData) {
        pData = new unsigned char[lImageSize];
        if (!pData) return false;
    }

    if (bEnc == 2 || bEnc == 3) {
        if (!LoadRawData()) return false;
    } else {
        if (!LoadTgaRLEData()) return false;
    }

    if (iBPP == 8) {
        if (!LoadTgaPalette()) return false;
    }

    BGRtoRGB();
    FlipImg();

    return true;
}

int TGAImg::ReadHeader() {
    unsigned char cGarbage;
    short int iInfo;

    fIn.read(&cGarbage, 1);
    fIn.read(&bEnc, 1);
    if (bEnc > 3) return false;

    fIn.read(reinterpret_cast<char*>(&iInfo), sizeof(iInfo));
    fIn.read(reinterpret_cast<char*>(&iInfo), sizeof(iInfo));
    fIn.read(&cGarbage, 1);
    fIn.read(reinterpret_cast<char*>(&iInfo), sizeof(iInfo));
    fIn.read(reinterpret_cast<char*>(&iInfo), sizeof(iInfo));

    fIn.read(reinterpret_cast<char*>(&iWidth), sizeof(iWidth));
    fIn.read(reinterpret_cast<char*>(&iHeight), sizeof(iHeight));
    fIn.read(reinterpret_cast<char*>(&iBPP), sizeof(iBPP));
    fIn.read(&cGarbage, 1);

    lImageSize = iWidth * iHeight * (iBPP / 8);
    return true;
}

int TGAImg::LoadRawData() {
    fIn.read(reinterpret_cast<char*>(pData), lImageSize);
    if (fIn.fail()) return false;

    if (iBPP == 24 || iBPP == 32) pImage = pData;
    else pImage = new unsigned char[lImageSize * 3];

    return true;
}

int TGAImg::LoadTgaRLEData() {
    //...省略了实
    int TGAImg::LoadTgaRLEData() {
        unsigned long ulCounter = 0;
        unsigned long ulPixelCount = iHeight * iWidth;
        unsigned char* pCur = pData;
        unsigned char bLength, bColor;

        do {
            fIn.read(reinterpret_cast<char*>(&bLength), 1);

            if (bLength < 128) {
                ++bLength;
                for (int i = 0; i < bLength; ++i) {
                    fIn.read(reinterpret_cast<char*>(pCur), (iBPP / 8));
                    pCur += (iBPP / 8);
                }
            } else {
                bLength -= 127;
                fIn.read(reinterpret_cast<char*>(&bColor), 1);
                for (int i = 0; i < bLength; ++i) {
                    *pCur = bColor;
                    pCur += (iBPP / 8);
                }
            }
            ulCounter += bLength;
        } while (ulCounter < ulPixelCount);

        pImage = pData;

        return true;
    }

    int TGAImg::LoadTgaPalette() {
        unsigned char bOrigColor;

        pPalette = new unsigned char[768];
        if (!pPalette) return false;

        fIn.read(reinterpret_cast<char*>(pPalette), 768);

        for (int i = 0; i < 768; i += 3) {
            bOrigColor = pPalette[i];
            pPalette[i] = pPalette[i + 2];
            pPalette[i + 2] = bOrigColor;
        }

        return true;
    }

    void TGAImg::BGRtoRGB() {
        unsigned long lSwap;
        unsigned char bTemp;

        if (iBPP == 8) return;

        for (unsigned long i = 0; i < lImageSize; i += (iBPP / 8)) {
            bTemp = pData[i];
            pData[i] = pData[i + 2];
            pData[i + 2] = bTemp;
        }
    }

    void TGAImg::FlipImg() {
        unsigned char *pTmp;
        int iLineBytes = iWidth * (iBPP / 8);

        pTmp = new unsigned char[iLineBytes];
        if (!pTmp) return;

        int iHalf = iHeight / 2;
        for (int i = 0; i < iHalf; ++i) {
            std::memcpy(pTmp, &pData[iLineBytes * i], iLineBytes);
            std::memcpy(&pData[iLineBytes * i], &pData[iLineBytes * (iHeight - i - 1)], iLineBytes);
            std::memcpy(&pData[iLineBytes * (iHeight - i - 1)], pTmp, iLineBytes);
        }

        delete[] pTmp;
    }

    int TGAImg::GetBPP() { return iBPP; }

    int TGAImg::GetWidth() { return iWidth; }

    int TGAImg::GetHeight() { return iHeight; }

    unsigned char* TGAImg::GetImg() { return pImage; }

    unsigned char* TGAImg::GetPalette() { return pPalette; }
