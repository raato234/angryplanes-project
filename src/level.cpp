#pragma once
#include "level.hpp"
#include <algorithm>

using namespace std;

void Level::Load(int slot) {
    boxCoords_.clear();
    enemyCoords_.clear();
    planeData_.clear();
    stringstream filename;
    filename << "resources/levels/level_" << slot << ".txt";
    string line;
    ifstream file(filename.str());

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line != "") {
                if (line.front() == 'S') //score line    S;<name>;<score>
                {
                    int chooser = 0;
                    string score, name;
                    for (int i = 0; i < line.length();i++) {
                        if (line[i] == ';') chooser++;
                        else if (chooser == 1) name.push_back(line[i]);
                        else if (chooser == 2) score.push_back(line[i]);
                    }
                    scores_.push_back(pair(name, stoi(score)));
                }
                else if (line.front() == 'E') //enemy line  E;<Xpos>;<Ypos>
                {
                    int chooser = 0;
                    string x, y;
                    for (int i = 0; i < line.length();i++) {
                        if (line[i] == ';') chooser++;
                        else if (chooser == 1) x.push_back(line[i]);
                        else if (chooser == 2) y.push_back(line[i]);
                    }
                    enemyCoords_.push_back(pair(stoi(x), stoi(y)));
                }
                else if (line.front() == 'B') //Box line   B;<Xpos>;<Ypos>
                {
                    int chooser = 0;
                    string x, y;
                    for (int i = 0; i < line.length();i++) {
                        if (line[i] == ';') chooser++;
                        else if (chooser == 1) x.push_back(line[i]);
                        else if (chooser == 2) y.push_back(line[i]);
                    }
                    boxCoords_.push_back(pair(stoi(x), stoi(y)));
                }
                else if (line.front() == 'P') //Player line   P;<type>;<hasAbility>
                {
                    int chooser = 0;
                    string x, y;
                    for (int i = 0; i < line.length();i++) {
                        if (line[i] == ';') chooser++;
                        else if (chooser == 1) x.push_back(line[i]);
                        else if (chooser == 2) y.push_back(line[i]);
                    }
                    planeData_.push_back(pair(stoi(x), stoi(y)));
                }
            }

        }
        file.close();
    }
    else throw new exception();

    return;
}

void Level::Write(int slot, vector<pair<std::string, int>> scores) { // writes the scores to the end of the file
    stringstream filename;
    filename << "resources/levels/level_" << slot << ".txt";
    ofstream file;
    file.open(filename.str(), ios::app);

    if (file.is_open())
    {
        for (auto score : scores) {
            file << "S;" << score.first << ";" << score.second << "\n";
        }
        file.close();
    }
    else throw new exception();
}

bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) // helper function to keep the scores sorted
{
    return (a.second < b.second);
}

void Level::addScore(std::string& name, int score) {
    scores_.push_back(std::pair(name, score));
    std::sort(scores_.begin(), scores_.end(), sortbysec);
}

std::vector<std::string> Level::getScores() {
    std::vector<std::string> temp;
    for (auto score : scores_) {
        temp.push_back(score.first + "   " + std::to_string(score.second));
    }
    return temp;
}
vector<pair<int, int>> Level::boxCoords() {
    return boxCoords_;
}

vector<pair<int, int>> Level::enemyCoords() {
    return enemyCoords_;
}
vector<pair<string, int>> Level::scores() {
    return scores_;
}

vector<pair<int, int>> Level::planeData() {
    return planeData_;
}







