#pragma once
#include <iostream>
#include <fstream>
#include "Types.h"
#include <vector>

const int cSize = 6;

class Highscore
{
    std::string name;
    UINT_32 point;

    std::string nameSave[cSize];
    UINT_32 pointSave[cSize];

    void SetP(UINT_32 put);
    void SetName(std::string nam);

    void bubbleSort();
    
    void write(std::fstream& file);
    void readStart(std::fstream& file);
    void readEnd(std::fstream& file);
public:

    Highscore();
    ~Highscore();

    std::vector<std::pair<std::string, UINT_32>> getScores();

    void doHighScore(std::string playerIdentity);
    void showHighScore();
};

