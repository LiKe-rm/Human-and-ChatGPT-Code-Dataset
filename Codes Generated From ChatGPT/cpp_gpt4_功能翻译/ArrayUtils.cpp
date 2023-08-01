/*
 * Copyright (c) 2023. All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. 2. Redistributions in
 * binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution. 3. Neither the name of the
 * Institute nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <type_traits>

template <typename T>
std::vector<T> add(const std::vector<T>& array, const T& value) {
  std::vector<T> tmp(array);
  tmp.push_back(value);
  return tmp;
}

template <typename T>
std::vector<T> remove(std::vector<T>& array, int index) {
  if (index < 0 || index >= static_cast<int>(array.size())) {
    throw std::out_of_range("Index out of bounds");
  }

  std::vector<T> tmp;
  tmp.reserve(array.size() - 1);
  tmp.insert(tmp.end(), array.begin(), array.begin() + index);
  tmp.insert(tmp.end(), array.begin() + index + 1, array.end());
  return tmp;
}

template <typename T>
std::vector<T> remove(std::vector<T>& array, const T& element) {
  auto it = std::find(array.begin(), array.end(), element);
  if (it != array.end()) {
    array.erase(it);
  }
  return array;
}

template <typename T>
int indexOf(const std::vector<T>& array, const T& element) {
  auto it = std::find(array.begin(), array.end(), element);
  if (it != array.end()) {
    return std::distance(array.begin(), it);
  }
  return -1;
}

bool writeToFile(const std::string& filename, const std::vector<char>& data) {
  try {
    std::ofstream out(filename, std::ios::binary);
    std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(out));
    out.close();
    return true;
  } catch (const std::exception&) {
    return false;
  }
}

std::vector<char> readFromFile(const std::string& filename) {
  try {
    std::ifstream in(filename, std::ios::binary);
std::vector<char> fileData((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
in.close();
return fileData;
} catch (const std::exception&) {
return {};
}
}

std::vector<char> readFromStream(std::istream& input) {
try {
std::vector<char> streamData((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
return streamData;
} catch (const std::exception&) {
return {};
}
}

int main() {
std::vector<int> numbers = {1, 2, 3, 4, 5};
std::vector<int> newNumbers = add(numbers, 6);
for (int num : newNumbers) {
std::cout << num << " ";
}
std::cout << std::endl;

std::vector<int> removedNumbers = remove(newNumbers, 2);
for (int num : removedNumbers) {
std::cout << num << " ";
}
std::cout << std::endl;

std::vector<int> withoutElement = remove(removedNumbers, 4);
for (int num : withoutElement) {
std::cout << num << " ";
}
std::cout << std::endl;

int elementIndex = indexOf(withoutElement, 5);
std::cout << "Index of 5: " << elementIndex << std::endl;

std::string filename = "example.bin";
std::vector<char> data = {'h', 'e', 'l', 'l', 'o'};
if (writeToFile(filename, data)) {
std::cout << "Data written to file successfully" << std::endl;
}

std::vector<char> fileData = readFromFile(filename);
for (char c : fileData) {
std::cout << c;
}
std::cout << std::endl;

std::string inputStr = "This is a test";
std::istringstream input(inputStr);
std::vector<char> streamData = readFromStream(input);
for (char c : streamData) {
std::cout << c;
}
std::cout << std::endl;

return 0;
}
