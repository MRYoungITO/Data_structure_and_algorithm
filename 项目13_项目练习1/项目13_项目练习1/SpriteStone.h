#pragma once
#include <string>
#include <iostream>

using namespace std;

enum class SpriteStoneLevel
{
	PRIMARY_LEVEL,
	MIDDLE_LEVEL,
	ADVANCE_LEVEL,
	SPRITE_STONE_LEVEL_COUNT
};

// 灵石类
class SpriteStone
{
public:
	SpriteStone(int count = 0, SpriteStoneLevel level = SpriteStoneLevel::MIDDLE_LEVEL);
	string str() const;
	friend ostream& operator<<(ostream& os, SpriteStone& stone);
	SpriteStone operator+(const SpriteStone& stone);
	SpriteStone operator-(const SpriteStone& stone);
	int getCount();
	bool operator>=(const SpriteStone& stone);
private:
	int count; //灵石的数量: xxx块
	SpriteStoneLevel level;  //灵石的等级
};

ostream& operator<<(ostream& os, SpriteStone& stone);