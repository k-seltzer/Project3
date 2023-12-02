#include <iostream>
using namespace std;
#include <vector>
#include <list>

class HashMap
{
    struct value
    {
        pair<vector<int>, string> delay;

        value(vector<int> stats, string airlines)
        {
            delay.first = stats;
            delay.second = airlines;
        }
    };

private:
    vector<list<pair<string, value>>> map;
    int capacity;
    int size;
    double loadFactor;

    HashMap(int cap, double loadFactor = 1.5)
    {
        capacity = cap;
        vector<list<pair<string, value>>> newMap(capacity);
        map = newMap;
        size = 0;
    }

    int hash(string key)
    {
        int prod = 0;
        for (auto c : key)
            prod *= int(c);
        return prod % capacity;
    }

    void rehash(int newCap)
    {
        vector<list<pair<string, value>>> newMap(newCap);
        for (auto bucket : map)
        {
            for (auto pair : bucket)
            {
                int index = hash(pair.first);
                newMap[index].push_back({pair.first, pair.second});
            }
        }
        map = newMap;
        capacity = newCap;
    }

public:
    void insert(string key, vector<int> stats, string airlines)
    {
        value delay(stats, airlines);
        if (size >= capacity * loadFactor)
            rehash(capacity * 2);
        int index = hash(key);
        for (auto element : map[index])
        {
            if (element.first == key)
                return;
        }
        map[index].push_back({key, delay});
        size++;
    }

    string search(string key)
    {
        int index = hash(key);
        for (auto element : map[index])
        {
            if (element.first == key)
                return element.second.delay.second;
        }
        return "Data not in map";
    }
    vector<list<pair<string, value>>>::iterator begin() {
        return map.begin();
    }
    vector<list<pair<string, value>>>::iterator end() {
        return map.end();
    }
};