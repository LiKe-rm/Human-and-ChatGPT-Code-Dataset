#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>
#include <string>

using namespace std;

class LicenseStoreSchema {
public:
    template <typename T1, typename T2>
    static vector<T2> processPair(const pair<T1, vector<T2>>& input_pair) {
        vector<T2> result;
        for (const auto& item : input_pair.second) {
            result.push_back(process(item));
        }
        return result;
    }

    static string process(const string& input) {
        stringstream ss(input);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '_')) {
            tokens.push_back(token);
        }

        return tokens[1];
    }

    static pair<int, vector<string>> makePair(const vector<string>& input_list) {
        pair<int, vector<string>> result = {static_cast<int>(input_list.size()), input_list};
        return result;
    }

    static vector<string> getTransformedList(pair<int, vector<string>>& input_pair) {
        vector<string> output_list;
        for (const auto& item : input_pair.second) {
            output_list.push_back("Transformed_" + item);
        }
        return output_list;
    }

    static void printVector(const vector<string>& vec) {
        copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }
};

int main() {
    vector<string> input_list = {"item1", "item2", "item3", "item4"};
    pair<int, vector<string>> input_pair = LicenseStoreSchema::makePair(input_list);
    vector<string> transformed_list = LicenseStoreSchema::getTransformedList(input_pair);
    vector<string> result_list = LicenseStoreSchema::processPair(input_pair);

    LicenseStoreSchema::printVector(input_list);
    LicenseStoreSchema::printVector(transformed_list);
    LicenseStoreSchema::printVector(result_list);

    return 0;
}
