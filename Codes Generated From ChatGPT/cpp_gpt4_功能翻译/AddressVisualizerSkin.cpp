// Copyright (c) 2023, Anonymous Institute of Computer Science.
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
//

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <cassert>

class IPAddress {
public:
  virtual std::string getAddressString() const = 0;
};

class RimeAddress {
public:
  virtual std::string getAddressString() const = 0;
};

class Position {
public:
  virtual double getX() const = 0;
  virtual double getY() const = 0;
};

class Mote {
public:
  virtual std::shared_ptr<IPAddress> getIPAddress() = 0;
  virtual std::shared_ptr<RimeAddress> getRimeAddress() = 0;
  virtual std::shared_ptr<Position> getPosition() = 0;
};

class Simulation {
public:
  virtual std::vector<std::shared_ptr<Mote>> getMotes() = 0;
};

class Visualizer {
public:
  virtual void repaint() = 0;
};

class AddressVisualizerSkin {
public:
  AddressVisualizerSkin(Simulation &simulation, Visualizer &visualizer)
      : simulation_(simulation), visualizer_(visualizer) {
    initialize();
  }

  void setActive() {
    for (const auto &mote : simulation_.getMotes()) {
      addMote(mote);
    }
  }

  void setInactive() {
    for (const auto &mote : simulation_.getMotes()) {
      removeMote(mote);
    }
  }

  void paintAfterMotes() {
    for (const auto &mote : simulation_.getMotes()) {
      std::string msg = getMoteString(mote);

      if (!msg.empty()) {
        std::shared_ptr<Position> pos = mote->getPosition();
        // Add rendering code here
      }
    }
  }

private:
  void initialize() {
    // Initialize the visualizer skin
  }

  void addMote(const std::shared_ptr<Mote> &mote) {
    std::shared_ptr<IPAddress> ip_addr = mote->getIPAddress();
    std::shared_ptr<RimeAddress> rime_addr = mote->getRimeAddress();
if (ip_addr) {
  addr_observers_[mote].push_back([this](const std::shared_ptr<IPAddress> &ip_addr) {
    visualizer_.repaint();
  });
}

if (rime_addr) {
  addr_observers_[mote].push_back([this](const std::shared_ptr<RimeAddress> &rime_addr) {
    visualizer_.repaint();
  });
}
}

void removeMote(const std::shared_ptr<Mote> &mote) {
addr_observers_.erase(mote);
}

static std::string getMoteString(const std::shared_ptr<Mote> &mote) {
std::shared_ptr<IPAddress> ip_addr = mote->getIPAddress();
if (ip_addr && !ip_addr->getAddressString().empty()) {
return ip_addr->getAddressString();
}
std::shared_ptr<RimeAddress> rime_addr = mote->getRimeAddress();
if (rime_addr) {
  return rime_addr->getAddressString();
}

return "";
}

Simulation &simulation_;
Visualizer &visualizer_;
std::map<std::shared_ptr<Mote>, std::vector<std::function<void(const std::shared_ptr<IPAddress> &)>>>
addr_observers_;
};

int main() {
// Initialize the simulation, visualizer, and AddressVisualizerSkin objects here
// For example:
// Simulation simulation;
// Visualizer visualizer;
// AddressVisualizerSkin address_skin(simulation, visualizer);

// Call the setActive and setInactive methods as needed
// For example:
// address_skin.setActive();
// address_skin.setInactive();

return 0;
}