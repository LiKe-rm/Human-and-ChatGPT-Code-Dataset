// Copyright (c) 2023, Your Name
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the Institute nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <cstring>

class MemoryLayout {
public:
  // Add necessary implementation here
};

class Symbol {
public:
  // Add necessary implementation here
};

class MoteMemoryException : public std::runtime_error {
public:
  MoteMemoryException(const std::string& message) : std::runtime_error(message) {}
};

class MemoryInterface {
public:
  virtual std::vector<uint8_t> getMemory() = 0;
  virtual std::vector<uint8_t> getMemorySegment(uint64_t addr, size_t size) = 0;
  virtual void setMemorySegment(uint64_t addr, const std::vector<uint8_t>& data) = 0;
  virtual void clearMemory() = 0;
  virtual uint64_t getStartAddr() const = 0;
  virtual size_t getTotalSize() const = 0;
  virtual std::map<std::string, Symbol> getSymbolMap() const = 0;
  virtual MemoryLayout getLayout() const = 0;
};

class ArrayMemory : public MemoryInterface {
private:
  std::vector<uint8_t> memory;
  uint64_t startAddress;
  MemoryLayout layout;
  bool readonly;
  std::map<std::string, Symbol> symbols;

public:
  ArrayMemory(uint64_t address, size_t size, MemoryLayout layout, std::map<std::string, Symbol> symbols)
      : startAddress(address), layout(layout), readonly(false), symbols(symbols) {
    memory.resize(size);
  }

  ArrayMemory(uint64_t address, MemoryLayout layout, std::vector<uint8_t> memory, std::map<std::string, Symbol> symbols)
      : startAddress(address), layout(layout), memory(memory), readonly(false), symbols(symbols) {}

  ArrayMemory(uint64_t address, MemoryLayout layout, std::vector<uint8_t> memory, bool readonly,
              std::map<std::string,Symbol> symbols)
      : startAddress(address), layout(layout), memory(memory), readonly(readonly), symbols(symbols) {}

  std::vector<uint8_t> getMemory() override {
    return memory;
  }

  std::vector<uint8_t> getMemorySegment(uint64_t addr, size_t size) override {
    if (addr - startAddress + size > memory.size()) {
      throw MoteMemoryException("Invalid memory access");
    }
    std::vector<uint8_t> ret(memory.begin() + (addr - startAddress),
                             memory.begin() + (addr - startAddress) + size);
    return ret;
  }

  void setMemorySegment(uint64_t addr, const std::vector<uint8_t>& data) override {
    if (readonly) {
      throw MoteMemoryException("Invalid write access for readonly memory");
    }
    if (addr - startAddress + data.size() > memory.size()) {
      throw MoteMemoryException("Invalid memory access");
    }
    std::copy(data.begin(), data.end(), memory.begin() + (addr - startAddress));
  }

  void clearMemory() override {
    std::fill(memory.begin(), memory.end(), 0x00);
  }

  uint64_t getStartAddr() const override {
    return startAddress;
  }

  size_t getTotalSize() const override {
    return memory.size();
  }

  std::map<std::string, Symbol> getSymbolMap() const override {
    return symbols;
  }

  MemoryLayout getLayout() const override {
    return layout;
  }
};

int main() {
  // Example usage of ArrayMemory
  MemoryLayout layout;
  std::map<std::string, Symbol> symbols;
  ArrayMemory mem(0x1000, 1024, layout, symbols);

  std::vector<uint8_t> data = {0x01, 0x02, 0x03};
  mem.setMemorySegment(0x1000, data);

  std::vector<uint8_t> readData = mem.getMemorySegment(0x1000, 3);
  for (uint8_t byte : readData) {
    std::cout << "0x" << std::hex << static_cast<int>(byte) << " ";
  }

  return 0;
}

