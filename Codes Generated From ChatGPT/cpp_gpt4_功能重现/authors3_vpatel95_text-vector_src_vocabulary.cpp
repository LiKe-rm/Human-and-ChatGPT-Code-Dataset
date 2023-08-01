#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>

namespace wordvec {

class file_mapper_t {
  // Assume this class is already implemented.
};

class vocabulary_t {
 public:
  using progress_callback_t = void (*)(double);
  using stats_callback_t = void (*)(const std::string&);

  vocabulary_t(std::shared_ptr<file_mapper_t> _trainWordsMapper,
               std::shared_ptr<file_mapper_t> _stopWordsMapper,
               const std::string& _delims,
               const std::string& _eos = "</s>",
               uint16_t _minFreq = 5,
               progress_callback_t _progressCallback = nullptr,
               stats_callback_t _statsCallback = nullptr);

 private:
  struct tmpWordData_t {
    std::string word;
    size_t freq;
  };

  void loadStopWords(std::shared_ptr<file_mapper_t> stopWordsMapper);
  void loadWordsAndCalculateFrequency(std::shared_ptr<file_mapper_t> trainWordsMapper,
                                      const std::string& delims);
  void filterAndSortVocabulary(uint16_t minFreq);
  void assignWordIndices();

  std::unordered_map<std::string, tmpWordData_t> tmpWordData;
  std::vector<tmpWordData_t> sortedWords;
  std::unordered_map<std::string, size_t> stopWords;
  std::unordered_map<std::string, size_t> wordIndices;
  progress_callback_t progressCallback;
  stats_callback_t statsCallback;
};

vocabulary_t::vocabulary_t(std::shared_ptr<file_mapper_t> _trainWordsMapper,
                           std::shared_ptr<file_mapper_t> _stopWordsMapper,
                           const std::string& _delims,
                           const std::string& _eos,
                           uint16_t _minFreq,
                           progress_callback_t _progressCallback,
                           stats_callback_t _statsCallback)
    : progressCallback(_progressCallback), statsCallback(_statsCallback) {
  loadStopWords(_stopWordsMapper);
  loadWordsAndCalculateFrequency(_trainWordsMapper, _delims);
  filterAndSortVocabulary(_minFreq);
  assignWordIndices();

  if (statsCallback) {
    std::stringstream ss;
    ss << "Vocabulary size: " << sortedWords.size();
    statsCallback(ss.str().c_str());
  }
}

void vocabulary_t::loadStopWords(std::shared_ptr<file_mapper_t> stopWordsMapper) {
  std::istringstream iss(stopWordsMapper->data());
  std::string word;

  while (std::getline(iss, word)) {
    stopWords[word] = 1;
  }
}

void vocabulary_t::loadWordsAndCalculateFrequency(std::shared_ptr<file_mapper_t> trainWordsMapper,
                                                   const std::string& delims) {
  std::istringstream iss(trainWordsMapper->data());
  std::string line;
  std::string word;

  while (std::getline(iss, line)) {
    size_t start = 0;
    size_t end = line.find_first_of(delims);

    while (end != std::string::npos) {
      word = line.substr(start, end - start);
      if (!word.empty()) {
        tmpWordData[word].word = word;
        tmpWordData[word].freq++;
      }
      start = end + 1;
      end = line.find_first_of(delims, start);
    }

    word = line.substr(start);
    if (!word.empty()) {
      tmpWordData[word].word = word;
      tmpWordData[word].freq++;
    }

    if (progressCallback) {
      progressCallback(static_cast<double>(iss.tellg()) / trainWordsMapper->size());
    }
  }
}

void vocabulary_t::filterAndSortVocabulary(uint16_t minFreq) {
  for (const auto& wordData : tmpWordData) {
    if (wordData.second.freq >= minFreq &&
        stopWords.find(wordData.first) == stopWords.end()) {
      sortedWords.push_back(wordData.second);
    }
  }

  std::sort(sortedWords.begin(), sortedWords.end(),
  [](const tmpWordData_t& a, const tmpWordData_t& b) {
    return a.freq > b.freq;
  });
}
  
void vocabulary_t::assignWordIndices() {
  for (size_t i = 0; i < sortedWords.size(); ++i) {
    wordIndices[sortedWords[i].word] = i;
  }
}

} // namespace wordvec

int main() {
  // Example usage of the vocabulary_t class.
  auto trainWordsMapper = std::make_sharedwordvec::file_mapper_t("path/to/train/words.txt");
  auto stopWordsMapper = std::make_sharedwordvec::file_mapper_t("path/to/stop/words.txt");
  
  wordvec::vocabulary_t vocab(trainWordsMapper, stopWordsMapper, " ,;.!?",
  "</s>", 5,
  [](double progress) { std::cout << "Progress: " << progress << std::endl; },
  [](const std::string& stats) { std::cout << "Stats: " << stats << std::endl; });
  
  return 0;
}
