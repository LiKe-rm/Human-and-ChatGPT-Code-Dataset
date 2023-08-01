#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct anag
{
    string name;
    short age;
};

template <typename T>
void insert_data(T arr[], int& len, const T& data)
{
    arr[len++] = data;
}

template <typename T>
void delete_data(T arr[], int& len, int index)
{
    for (int i = index; i < len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    len--;
}

template <typename T>
T read_data(const T arr[], int index)
{
    return arr[index];
}

template <typename T>
void write_data(T arr[], int index, const T& data)
{
    arr[index] = data;
}

template <typename T>
void init_data(T arr[], int& len)
{
    len = 0;
}

template <typename T, typename Compare>
void sort_data(T arr[], int len, Compare comp)
{
    sort(arr, arr + len, comp);
}

template <typename T, typename Match>
int search_data(const T arr[], int len, const T& key, Match match)
{
    for (int i = 0; i < len; i++)
    {
        if (match(arr[i], key))
        {
            return i;
        }
    }
    return -1;
}

bool anag_comp1(const anag& a, const anag& b)
{
    return a.name < b.name;
}

bool anag_comp2(const anag& a, const anag& b)
{
    return a.age < b.age;
}

bool anag_match1(const anag& a, const anag& b)
{
    return a.name == b.name;
}

bool anag_match2(const anag& a, const anag& b)
{
    return a.age == b.age;
}

int main()
{
    const int MAX_SIZE = 100;
    anag elenco[MAX_SIZE];
    int len = 0;

    anag p1 = {"Alice", 30};
    anag p2 = {"Bob", 25};
    anag p3 = {"Charlie", 35};
    anag p4 = {"David", 28};

    insert_data(elenco, len, p1);
    insert_data(elenco, len, p2);
    insert_data(elenco, len, p3);
    insert_data(elenco, len, p4);

    cout << "Array after insertion:\n";
    for (int i = 0; i < len; i++)
    {
        cout << elenco[i].name << ", " << elenco[i].age << endl;
    }

    anag search_key = {"Bob", 25};
    int index = search_data(elenco, len, search_key, anag_match1);
    if (index != -1)
    {
        cout << "Found " << elenco[index].name << " at index " << index << endl;
    } else
    {
        cout << "Not found\n";
    }

    sort_data(elenco, len, anag_comp1);

    cout << "Array after sorting by name:\n";
    for (int i = 0; i < len; i++)
    {
        cout << elenco[i].name << ", " << elenco[i].age << endl;
    }

    sort_data(elenco, len, anag_comp2);

    cout << "Array after sorting by age:\n";
    for (int i = 0; i < len; i++)
    {
        cout << elenco[i].name << ", " << elenco[i].age << endl;
    }

    anag search_key_fuzzy = {"B", 0};
    auto fuzzy_match = [](const anag& a, const anag& b) -> bool
    {
        return a.name.find(b.name) != string::npos;
    };

    int fuzzy_index = search_data(elenco, len, search_key_fuzzy, fuzzy_match);
    if (fuzzy_index != -1)
    {
        cout << "Fuzzy search found " << elenco[fuzzy_index].name << " at index " << fuzzy_index << endl;
    } else
    {
        cout << "Fuzzy search not found\n";
    }

    delete_data(elenco, len, fuzzy_index);

    cout << "Array after deletion:\n";
    for (int i = 0; i < len; i++)
    {
        cout << elenco[i].name << ", " << elenco[i].age << endl;
    }

    init_data(elenco, len);

    cout << "Array after initialization:\n";
    for (int i = 0; i < len; i++)
    {
        cout << elenco[i].name << ", " << elenco[i].age << endl;
    }

    return 0;

}
