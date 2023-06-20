#include <string>
#include <format>
#include "Mission.h"
#include "Pixel.h"

Mission::Mission(SnakeStatus& stat)
    : status(stat), TextBox("Mission")
{
    width = 23;
    height = 12;
}

bool Mission::allSuccess() const
{
    return status.currentLength >= status.maxLength &&
        status.appleGets >= appleGoal &&
        status.poisonGets >= poisonGoal &&
        status.boosterGets >= boosterGoal &&
        status.gatePass >= gatePassGoal &&
        status.wallBounced >= wallBounceGoal;
}

//Mission board에 있는 내용들을 texts에 넣어주는 작업
void Mission::updateText()
{
    // Mission Board 텍스트
    std::string s;

    s = "Mission";

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
        Length = std::format("Length: {} (v)", status.currentLength);
    else
        Length = std::format("Length: {} ( )", status.currentLength);
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
        WB = std::format("WallBounced: {} (v)", status.wallBounced);
    else
        WB = std::format("WallBounced: {} ( )", status.wallBounced);
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
        BG = std::format("BoosterGets: {} (v)", status.boosterGets);
    else
        BG = std::format("BoosterGets: {} ( )", status.boosterGets);
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
        AG = std::format("AppleGets: {} (v)", status.appleGets);
    else
        AG = std::format("AppleGets: {} ( )", status.appleGets);
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
        PG = std::format("PoisonGets: {} (v)", status.poisonGets);
    else
        PG = std::format("PoisonGets: {} ( )", status.poisonGets);
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
        GP = std::format("GatePass: {} (v)", status.gatePass);
    else
        GP = std::format("GatePass: {} ( )", status.gatePass);
    for (size_t i = 0; i < GP.length(); i++)
    {
        const char c = GP[i];
        Pixel p;
        p.pos = Vector2Int(boxX + 1 + i, boxY + 9);
        p.ch = c;

        texts.push_back(p);
    }
}
