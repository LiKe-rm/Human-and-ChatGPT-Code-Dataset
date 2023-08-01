#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <zlib.h>
#include "base64.h"
#include "tmx.h"

class StringUtil {
public:
    // 去除字符串首尾的空格
    static std::string Trim(const std::string &str) {
        std::string whitespace = " \t\n\r";
        std::size_t start = str.find_first_not_of(whitespace);
        std::size_t end = str.find_last_not_of(whitespace);

        if (start == std::string::npos) {
            return "";
        }
        return str.substr(start, end - start + 1);
    }

    // Base64编码
    static std::string EncodeBase64(const std::string &input) {
        std::string encoded_data;
        base64::encode(input, encoded_data);
        return encoded_data;
    }

    // Base64解码
    static std::string DecodeBase64(const std::string &input) {
        std::string decoded_data;
        base64::decode(input, decoded_data);
        return decoded_data;
    }

    // GZIP解压缩
    static std::string DecompressGZIP(const std::string &input) {
        // Prepare the zlib inflate stream
        z_stream stream;
        std::memset(&stream, 0, sizeof(stream));
        int status = inflateInit2(&stream, 16 + MAX_WBITS);
        if (status != Z_OK) {
            throw std::runtime_error("GZIP decompression initialization failed");
        }

        std::string output;
        const char *input_data = input.data();
        std::size_t input_length = input.size();

        // Inflate the compressed data
        const std::size_t buffer_size = 4096;
        char buffer[buffer_size];
        do {
            stream.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(input_data));
            stream.avail_in = static_cast<uInt>(input_length);

            do {
                stream.next_out = reinterpret_cast<Bytef *>(buffer);
                stream.avail_out = buffer_size;

                status = inflate(&stream, Z_NO_FLUSH);
                if (status == Z_STREAM_ERROR) {
                    throw std::runtime_error("GZIP decompression stream error");
                }

                switch (status) {
                    case Z_NEED_DICT:
                        status = Z_DATA_ERROR;
                    case Z_DATA_ERROR:
                    case Z_MEM_ERROR:
                        inflateEnd(&stream);
                        throw std::runtime_error("GZIP decompression error");
                }

                output.append(buffer, buffer_size - stream.avail_out);
            } while (stream.avail_out == 0);
        } while (status != Z_STREAM_END);

        // Clean up the zlib inflate stream
        inflateEnd(&stream);

        return output;
    }
};
