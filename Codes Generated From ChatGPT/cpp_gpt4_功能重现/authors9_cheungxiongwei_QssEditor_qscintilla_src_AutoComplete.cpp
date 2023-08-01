#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "ListBox.h"

class AutoComplete {
public:
    AutoComplete();
    ~AutoComplete();

    void Start();
    void SetList(const std::vector<std::string>& list);
    void Show(bool show);
    void Cancel();
    void Move(int direction);
    void Select(const std::string& input);

private:
    void updateSortMatrix();
    std::string toLower(const std::string& str) const;
    bool isPrefix(const std::string& prefix, const std::string& str) const;

    ListBox listBox;
    std::vector<std::string> items;
    std::vector<std::vector<int>> sortMatrix;
    int selectedItem;
    bool caseSensitive;
};

AutoComplete::AutoComplete()
    : selectedItem(-1), caseSensitive(false) {
}

AutoComplete::~AutoComplete() {
    Cancel();
}

void AutoComplete::Start() {
    listBox.Create();
    listBox.SetPosition(0, 0);
    listBox.SetItemHeight(20);
    listBox.SetSeparator(true);
    listBox.SetCaseSensitive(caseSensitive);
}

void AutoComplete::SetList(const std::vector<std::string>& list) {
    items = list;
    listBox.SetItems(items);
    updateSortMatrix();
}

void AutoComplete::Show(bool show) {
    listBox.Show(show);
}

void AutoComplete::Cancel() {
    listBox.Clear();
    listBox.Release();
}

void AutoComplete::Move(int direction) {
    selectedItem += direction;
    if (selectedItem < 0) {
        selectedItem = 0;
    } else if (selectedItem >= static_cast<int>(items.size())) {
        selectedItem = static_cast<int>(items.size()) - 1;
    }
    listBox.SelectItem(selectedItem);
}

void AutoComplete::Select(const std::string& input) {
    std::string searchStr = caseSensitive ? input : toLower(input);

    for (size_t i = 0; i < sortMatrix.size(); ++i) {
        if (isPrefix(searchStr, items[sortMatrix[i][0]])) {
            listBox.SelectItem(sortMatrix[i][0]);
            break;
        }
    }
}

void AutoComplete::updateSortMatrix() {
    sortMatrix.resize(items.size());
    for (size_t i = 0; i < items.size(); ++i) {
        sortMatrix[i].resize(2);
        sortMatrix[i][0] = i;
        sortMatrix[i][1] = 0;
    }

    std::sort(sortMatrix.begin(), sortMatrix.end(),
              [this](const std::vector<int>& a, const std::vector<int>& b) {
                  return this->caseSensitive ? (this->items[a[0]] < this->items[b[0]])
                      : (this->toLower(this->items[a[0]]) < this->toLower(this->items[b[0]]));
              });
}

std::string AutoComplete::toLower(const std::string& str) const {
    std::string lowerStr = str;
    for (char& ch : lowerStr) {
        ch = std::tolower(static_cast<unsigned char>(ch));
    }
    return lowerStr;
}

bool AutoComplete::isPrefix(const std::string& prefix, const std::string& str) const {
    if (prefix.length() > str.length()) {
        return false;
    }

    for (size_t i = 0;i < prefix.length(); ++i) {
        if (prefix[i] != str[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    AutoComplete autoComplete;
    autoComplete.Start();

    std::vector<std::string> itemList = {"apple", "banana", "cherry", "date", "fig", "grape"};
    autoComplete.SetList(itemList);

    autoComplete.Show(true);

    autoComplete.Select("ap");

    autoComplete.Move(1);
    autoComplete.Move(-1);

    autoComplete.Cancel();

    return 0;
}
