// Copyright (c) 2023, Your Institute. All rights reserved.
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

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <functional>
#include <map>

class MoteInterface {
public:
    virtual ~MoteInterface() = default;
};

class MoteID : public MoteInterface {
public:
    virtual int getMoteID() const = 0;
    virtual void setMoteID(int newID) = 0;
};

class SimpleMoteID : public MoteID {
    int id;

public:
    explicit SimpleMoteID() : id(-1) {}
    int getMoteID() const override { return id; }
    void setMoteID(int newID) override { id = newID; }
};

class MoteType {
public:
    virtual ~MoteType() = default;
    virtual std::string getIdentifier() const = 0;
    virtual void setIdentifier(const std::string& identifier) = 0;
};

class AbstractMspMoteType : public MoteType {
protected:
    std::string identifier;
    std::string description;

public:
    AbstractMspMoteType() = default;
    explicit AbstractMspMoteType(const std::string& identifier) : identifier(identifier) {
        this->description = "Msp Mote Type #" + identifier;
    }

    std::string getIdentifier() const override { return identifier; }
    void setIdentifier(const std::string& identifier) override { this->identifier = identifier; }

    bool configureAndInit() {
        if (identifier.empty()) {
            int counter = 0;
            bool identifierOK = false;
            while (!identifierOK) {
                counter++;
                identifier = "msp" + std::to_string(counter);
                identifierOK = true;

                // Check if identifier is already used by some other type
                for (const auto& existingMoteType : getMoteTypes()) {
                    if (existingMoteType != this && existingMoteType->getIdentifier() == identifier) {
                        identifierOK = false;
                        break;
                    }
                }
            }
        }

        if (description.empty()) {
description = "Msp Mote Type #" + identifier;
}
    return compileContikiFirmware();
}

// Dummy compile function for the example
bool compileContikiFirmware() {
    // Implement Contiki firmware compilation logic here
    std::cout << "Compiling Contiki firmware for mote type: " << identifier << std::endl;
    return true;
}

static std::vector<AbstractMspMoteType*>& getMoteTypes() {
    static std::vector<AbstractMspMoteType*> moteTypes;
    return moteTypes;
}
};

class Msp430MoteType : public AbstractMspMoteType {
public:
Msp430MoteType() : AbstractMspMoteType("msp430") {}
};

class Msp432MoteType : public AbstractMspMoteType {
public:
Msp432MoteType() : AbstractMspMoteType("msp432") {}
};

int main() {
Msp430MoteType msp430Mote;
Msp432MoteType msp432Mote;
AbstractMspMoteType::getMoteTypes().push_back(&msp430Mote);
AbstractMspMoteType::getMoteTypes().push_back(&msp432Mote);

for (auto& moteType : AbstractMspMoteType::getMoteTypes()) {
    moteType->configureAndInit();
}

return 0;
}