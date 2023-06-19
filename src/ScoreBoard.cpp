#include <string>
#include <format>
#include "ScoreBoard.h"
#include "Pixel.h"

ScoreBoard::ScoreBoard(SnakeStatus& stat)
    : status(stat), TextBox("ScoreBoard")
{
    width = 23;
    height = 12;
}

//scoreboard에 있는 내용들을 texts에 넣어주는 작업
void ScoreBoard::updateText()
{
    // Score Board 텍스트
    std::string s;

    s = "Score board";

    for (size_t i = 0; i < s.length(); i++)
    {
        const char c = s[i];

        Pixel p;

        p.pos = Vector2Int(boxX + i + 1, boxY + 2);//텍스트 써줄 위치 지정해주는 파트
        p.ch = c;//한글자씩 넣어주자!

        texts.push_back(p);//완성된 Pixel texts에 넣어주는 작업
    }

    //Length:Current Length / Max Length
    std::string Length;
    Length = std::format("Length: {} / {}", status.currentLength, status.maxLength);
    for (size_t i = 0; i < Length.length(); i++)
    {
        const char c = Length[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 4);
        p.ch = c;

        texts.push_back(p);
    }
    //wallBounced
    std::string wb;
    wb = std::format("WallBounced: {}", status.wallBounced);
    for (size_t i = 0; i < wb.length(); i++)
    {
        const char c = wb[i];
        Pixel p;
        p.pos = Vector2Int(boxX + i + 1, boxY + 5);
        p.ch = c;

        texts.push_back(p);
    }
    //boosterGets
    std::string bg;
    bg = std::format("BoosterGets: {}", status.boosterGets);
    for (size_t i = 0; i < bg.length(); i++)
    {
        const char c = bg[i];
        Pixel p;
        p.pos = Vector2Int(boxX + i + 1, boxY + 6);
        p.ch = c;

        texts.push_back(p);
    }
    //appleGets
    std::string ag;
    ag = std::format("AppleGets: {}", status.appleGets);
    for (size_t i = 0; i < ag.length(); i++)
    {
        const char c = ag[i];
        Pixel p;
        p.pos = Vector2Int(boxX + i + 1, boxY + 7);
        p.ch = c;

        texts.push_back(p);
    }
    //poisonGets
    std::string pg;
    pg = std::format("PoisonGets: {}", status.poisonGets);
    for (size_t i = 0; i < pg.length(); i++)
    {
        const char c = pg[i];
        Pixel p;
        p.pos = Vector2Int(boxX + i + 1, boxY + 8);
        p.ch = c;

        texts.push_back(p);
    }
    //gatePass
    std::string gp;
    gp = std::format("GatePass: {}", status.gatePass);
    for (size_t i = 0; i < gp.length(); i++)
    {
        const char c = gp[i];
        Pixel p;
        p.pos = Vector2Int(boxX + i + 1, boxY + 9);
        p.ch = c;

        texts.push_back(p);
    }
}


