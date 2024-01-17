#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Level {
public:


    void Write(int slot, vector<pair<std::string, int>> scores);
    void addScore(std::string& name, int score);
    std::vector<std::string> getScores();			// returns a vector with strings in <name>"  "<score> format

    vector<pair<int, int>> boxCoords();
    vector<pair<int, int>> enemyCoords();
    vector<pair<int, int>> planeData();
    vector<pair<string, int>> scores();


    void Load(int slot);
private:
    vector<pair<int, int>> boxCoords_;
    vector<pair<int, int>> enemyCoords_;
    vector<pair<int, int>>planeData_;
    vector<pair<string, int>> scores_;
};