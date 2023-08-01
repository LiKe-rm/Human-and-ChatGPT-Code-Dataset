#include <iostream>
#include <cstdint>
#include <vector>

const uint32_t CRCTable[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
    0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
    0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
    0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
    0x5530d8cd, 0xe26d6a3e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce,
    0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc,
    0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f, 0x5edef90e, 0x29d9c998,
    0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6,
    0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1, 0xf00f9344, 0x8708a3d2,
    0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0,
    0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d5ada, 0xafa64379,
    0xde71e4ff, 0xa9b67221, 0x38d03670, 0x4fde7766, 0xd6d930ac, 0xa1d1553a, 0xf762575d, 0x60b08ed5,
    0x6d930a62, 0x7e5f9080, 0xe05e9b51, 0x90dc208f, 0x6ab067a3, 0x7dbf60c4, 0xe0b85746, 0x97bf4ad0,
    0x2ad7d2bb, 0x5dd0e27d, 0xc4d5db33, 0xb1d510d5, 0x29024b64, 0x5e075b92, 0xc7091b28, 0xb0052bbe,
    0x2aced51, 0x57f1c87e7, 0xcee8f8f7, 0xb9e99f61, 0x21b3d9d0, 0x56b4c946, 0xcfb0d8bc, 0xb8b7e92a,
    0x1d661643, 0x6a6b36d5, 0xf307026f, 0x840063f9, 0x1a65c682, 0x6d62f614, 0xf4a6b7ae, 0x83a18738,
    0x1406ad69, 0x6301d7ff, 0xfa0a8645, 0x8d0db6d3, 0x1308a340, 0x640f93d6, 0xfd66a46c, 0x8a61d4fa,
    0x3b6eaa77, 0x4c69da01, 0xd5024bbb, 0xa2077b2d, 0x3c61286e, 0x4b6158f8, 0xd26a4022, 0xa56d70b4,
    0x3f684425, 0x486f74b3, 0xd1680f29, 0xa66f3f5f, 0x38d8a5fc, 0x4fdf956a, 0xd6d6cfb0, 0xa1d1ff26
};

uint32_t GetCRC32(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < length; ++i) {
        uint8_t index = (crc ^ data[i]) & 0xFF;
        crc = (crc >> 8) ^ CRCTable[index];
    }

    return ~crc;
}

int main() {
    std::vector<uint8_t> message = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21}; // "Hello, World!"
    uint32_t crc32 = GetCRC32(message.data(), message.size());

    std::cout << "CRC32: 0x" << std::hex << std::uppercase << crc32 << std::endl;
    return 0;
}


