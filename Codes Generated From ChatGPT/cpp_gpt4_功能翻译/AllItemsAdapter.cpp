#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

struct ViewHolder {
    std::string title;
    std::string result;
};

class AllItemsAdapter {
private:
    std::vector<std::string> allItemsList;
    std::vector<int> totalListTemp;
    std::vector<bool> boolList;
    std::shared_ptr<ViewHolder> holder = nullptr;
    int maxAllListValue;

public:
    AllItemsAdapter(const std::vector<std::string>& list, int maxAllListValue) : allItemsList(list), maxAllListValue(maxAllListValue) {}
    
    int getCount() const {
        return allItemsList.size();
    }

    std::string getItem(int position) const {
        return allItemsList[position];
    }

    std::shared_ptr<ViewHolder> getView(int position) {
        bool getview_flag = false;
        bool refresh_flag = false;
        
        if (position == 0){
            totalListTemp = boolList;
        }

        holder = std::make_shared<ViewHolder>();
        holder->title = allItemsList[position];
        
        int index = 0;
        for (auto tList : totalListTemp) {
            if (index == boolList.size()) {
                break;
            }
            refresh_flag = boolList[index];
            index++;
            if ((tList == position) && refresh_flag && (position+1) == index) {
                holder->result = "PASS";
            } else if ((tList == position) && !refresh_flag && (position+1) == index) {
                holder->result = "FAIL";
            }
        }
        
        if (maxAllListValue == (position + 1) || allItemsList.size() == (position + 1)) {
            getview_flag = true;
        }
        
        return holder;
    }

    std::shared_ptr<ViewHolder> getViewHolder() {
        return holder;
    }
};

int main() {
    std::vector<std::string> items = {"Item1", "Item2", "Item3"};
    AllItemsAdapter adapter(items, 2);

    for (int i = 0; i < adapter.getCount(); ++i) {
        auto view = adapter.getView(i);
        std::cout << view->title << " - " << view->result << std::endl;
    }

    return 0;
}
