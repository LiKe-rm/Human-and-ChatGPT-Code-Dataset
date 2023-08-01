// Copyright (c) 2023, Your Name. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer. 2. Redistributions in
// binary form must reproduce the above copyright notice, this list of
// conditions and the following disclaimer in the documentation and/or other
// materials provided with the distribution. 3. Neither the name of the
// Institute nor the names of its contributors may be used to endorse or promote
// products derived from this software without specific prior written
// permission.
//
// THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include <cstdint>
#include <vector>
#include <map>
#include <stdexcept>

class AvrMoteMemory {
public:
    enum class EventType { READ, WRITE };

    class Symbol {
    public:
        enum class Type { VARIABLE };

        Symbol(Type type, const std::string& name, const std::string& section, uint32_t address, int size)
            : type(type), name(name), section(section), address(address), size(size) {}

        Type type;
        std::string name;
        std::string section;
        uint32_t address;
        int size;
    };

    class SegmentMonitor {
    public:
        virtual void memoryChanged(AvrMoteMemory& memory, EventType event, uint32_t address) = 0;
    };

    AvrMoteMemory(uint32_t sramSize) : sramSize(sramSize), coojaIsAccessingMemory(false) {}

    uint32_t getTotalSize() const {
        return sramSize;
    }

    std::vector<uint8_t> getMemorySegment(uint32_t address, uint32_t size) const {
        if (!accessInRange(address, size)) {
            throw std::runtime_error("Getting memory segment failed: Out of range");
        }

        std::vector<uint8_t> data(size);
        for (uint32_t i = 0; i < size; i++) {
            data[i] = memory[address + i];
        }
        return data;
    }

    void setMemorySegment(uint32_t address, const std::vector<uint8_t>& data) {
        if (!accessInRange(address, data.size())) {
            throw std::runtime_error("Writing memory segment failed: Out of range");
        }

        for (uint32_t i = 0; i < data.size(); i++) {
            memory[address + i] = data[i];
        }
    }

    void clearMemory() {
        std::fill(memory.begin(), memory.end(), 0);
    }

    bool accessInRange(uint32_t address, uint32_t size) const {
        return (address >= 0) && (address + size <= sramSize);
    }

    uint32_t getStartAddr() const {
        return 0;
    }

    std::map<std::string, Symbol> getSymbolMap() const {
        return symbols;
    }

    bool addSegmentMonitor(EventType flag, uint32_t address, uint32_t size, SegmentMonitor* mm) {
        // For simplicity, we are not implementing this function in this example.
        return true;
    }

    bool removeSegmentMonitor(uint32_t address, uint32_t size, SegmentMonitor* mm) {
        // For simplicity, we are not implementing this function in this example.
        return true;
    }

private:
    uint32_t sramSize;
    bool coojaIsAccessingMemory;
    std::vector<uint8_t> memory;
    std::map<std::string, Symbol> symbols;
};

