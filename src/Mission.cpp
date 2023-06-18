#include <string>
#include <format>
#include "Mission.h"
#include "Pixel.h"

Mission::Mission(SnakeStatus& staus)
    : status(status), TextBox("Mission")
{}

//Mission board에 있는 내용들을 texts에 넣어주는 작업
void Mission::updateText()
{
    // Mission Board 텍스트
    std::string s;

    s = "Mission Board";

    for (size_t i = 0; i < s.length(); i++)
    {
        const char c = s[i];

        Pixel p;

        p.pos = Vector2Int(boxX + i + 1, boxY + 2);//텍스트 써줄 위치 지정해주는 파트
        p.ch = c;//한글자씩 넣어주자!

        texts.push_back(p);//완성된 Pixel texts에 넣어주는 작업
    }

    //Length 목표달성여부 
    std::string Length;
    if (status.currentLength >= status.maxLength)
        Length = std::format("Length: %hu (v)", status.currentLength);
    else
        Length = std::format("Length: %hu ( )", status.currentLenght);
    for (size_t i = 0; i < Length.length(); i++)
    {
        const char c = Length[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 4);
        p.ch = c;

        texts.push_back(p);
    }
    //wallBounced 목표달성여부
    std::string WB;
    if (status.wallBounced >= wallBounceGoal)
        WB = std::format("WallBounced: %hu (v)", status.wallBounced);
    else
        WB = std::format("WallBounced: %hu ( )", status.wallBounced);
    for (size_t i = 0; i < WB.length(); i++)
    {
        const char c = WB[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 5);
        p.ch = c;

        texts.push_back(p);
    }
    //boosterGets 목표달성여부
    std::string BG;
    if (status.boosterGets >= boosterGoal)
        BG = std::format("boosterGets: %hu (v)", status.boosterGets);
    else
        BG = std::format("boosterGets: %hu ( )", status.boosterGets);
    for (size_t i = 0; i < BG.length(); i++)
    {
        const char c = BG[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 6);
        p.ch = c;

        texts.push_back(p);
    }
    //appleGets
    std::string AG;
    if (status.appleGets >= appleGoal)
        AG = std::format("appleGets: %hu (v)", status.appleGets);
    else
        AG = std::format("appleGets: %hu ( )", status.appleGets);
    for (size_t i = 0; i < AG.length(); i++)
    {
        const char c = AG[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 7);
        p.ch = c;

        texts.push_back(p);
    }
    //poisonGets
    std::string PG;
    if (status.poisonGets >= poisonGoal)
        PG = std::format("poisonGets: %hu (v)", status.poisonGets);
    else
        PG = std::format("poisonGets: %hu ( )", status.poisonGets);
    for (size_t i = 0; i < PG.length(); i++)
    {
        const char c = PG[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 8);
        p.ch = c;

        texts.push_back(p);
    }
    //gatePass
    std::string GP;
    if (status.gatePass >= gatePassGoal)
        GP = std::format("gatePass: %hu (v)", status.gatePass);
    else
        GP = std::format("gatePass: %hu ( )", status.gatePass);
    for (size_t i = 0; i < GP.length(); i++)
    {
        const char c = GP[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 9);
        p.ch = c;

        texts.push_back(p);
    }
}
