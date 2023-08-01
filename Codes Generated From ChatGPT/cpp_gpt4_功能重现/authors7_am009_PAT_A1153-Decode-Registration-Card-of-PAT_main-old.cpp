#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <map>

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#define DEBUG(X) std::cout << (X) << std::endl;
#else
#define DEBUG(X)
#endif

struct total {
    int people;
    int score;
};

struct compare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    }
};

typedef std::set<std::pair<int, int>, compare> student_set;

std::map<int, total> site2total;
std::map<std::string, std::map<int, int>> date2t3;
student_set top, adv, bas;

void input_students(int n) {
    for (int i = 0; i < n; i++) {
        int id, score;
        std::string date;
        std::cin >> id >> score >> date;

        int site = id / 1000;
        site2total[site].people++;
        site2total[site].score += score;

        date2t3[date][site]++;

        if (score >= 90) {
            top.emplace(id, score);
        } else if (score >= 80) {
            adv.emplace(id, score);
        } else {
            bas.emplace(id, score);
        }
    }
}

void query_by_level(char c) {
    student_set* level_set;
    switch (c) {
        case 'T':
            level_set = &top;
            break;
        case 'A':
            level_set = &adv;
            break;
        case 'B':
            level_set = &bas;
            break;
    }
    for (const auto& student : *level_set) {
        printf("%d %d\n", student.first, student.second);
    }
}

void query_by_site(int site) {
    if (site2total.count(site) == 0) {
        printf("NA\n");
    } else {
        printf("%d %d\n", site2total[site].people, site2total[site].score);
    }
}

void query_by_date(const std::string& date) {
    if (date2t3.count(date) == 0) {
        printf("NA\n");
    } else {
        for (const auto& site_info : date2t3[date]) {
            printf("%d %d\n", site_info.first, site_info.second);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    input_students(n);

    for (int i = 0; i < m; i++) {
        int type;
        std::cin >> type;
        if (type == 1) {
            char c;
            std::cin >> c;
            query_by_level(c);
        } else if (type == 2) {
            int site;
            std::cin >> site;
            query_by_site(site);
        } else if (type == 3) {
            std::string date;
            std::cin >> date;
            query_by_date(date);
        }
    }
    return 0;
}
