#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct Student {
    string id;
    int level;
    int room;
    int date;
    int score;
};

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    map<int, set<Student>> level_students;
    map<int, pair<int, int>> room_students;
    map<int, map<int, int>> date_students;

    for (int i = 0; i < n; ++i) {
        cin >> students[i].id >> students[i].level >> students[i].room >> students[i].date >> students[i].score;
        level_students[students[i].level].insert(students[i]);
        room_students[students[i].room].first++;
        room_students[students[i].room].second += students[i].score;
        date_students[students[i].date][students[i].room]++;
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int query_type;
        cin >> query_type;

        if (query_type == 1) {
            int query_level;
            cin >> query_level;
            cout << "查询等级: " << query_level << endl;
            for (const auto &student : level_students[query_level]) {
                cout << student.id << " " << student.score << endl;
            }
        } else if (query_type == 2) {
            int query_room;
            cin >> query_room;
            cout << "查询考场: " << query_room << endl;
            cout << room_students[query_room].first << " " << room_students[query_room].second << endl;
        } else if (query_type == 3) {
            int query_date;
            cin >> query_date;
            cout << "查询日期: " << query_date << endl;
            for (const auto &room_count : date_students[query_date]) {
                cout << room_count.first << " " << room_count.second << endl;
            }
        }
    }

    return 0;
}
