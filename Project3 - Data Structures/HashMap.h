#include <iostream>
#include <vector>
#include <list>
#pragma once
using namespace std;

class HashMap {

private:
    vector<list<pair<string, vector<int>>>> map;
    int capacity;
    int size;
    double loadFactor;

    int hash(string key)
    {
        int prod = 1;
        for (auto c : key)
            prod *= int(c);
        return prod % capacity;
    }

    void rehash(int newCap)
    {
        vector<list<pair<string, vector<int>>>> newMap(newCap);
        capacity = newCap;
        for (auto bucket : map)
        {
            for (auto pair : bucket)
            {
                int index = hash(pair.first);
                newMap[index].push_back({pair.first, pair.second});
            }
        }
        map = newMap;
    }

public:
    HashMap(int cap = 10, double loadFactor = 1.5)
    {
        capacity = cap;
        this->loadFactor = loadFactor;
        vector<list<pair<string, vector<int>>>> newMap(capacity);
        map = newMap;
        size = 0;
    }
    void insert(string key, vector<int> stats)
    {
        if (size >= capacity * loadFactor)
            rehash(capacity * 2);
        int index = hash(key);
        for (auto element : map[index])
        {
            if (element.first == key)
                return;
        }
        map[index].push_back({ key, stats });
        size++;
    }

    vector<int> search(string key)
    {
        int index = hash(key);
        for (auto element = map[index].begin(); element != map[index].end(); element++)
        {
            if (element->first == key)
                return element->second;
        }
        return vector<int>(0);
    }
    vector<list<pair<string, vector<int>>>>::iterator begin() {
        return map.begin();
    }
    vector<list<pair<string, vector<int>>>>::iterator end() {
        return map.end();
    }
};