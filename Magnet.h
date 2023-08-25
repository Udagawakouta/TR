#pragma once

enum MagnetType
{
	magnetS,
	magnetN
};

//構造体
struct Vector2  {
	float x = 0.0f;
	float y = 0.0f;
};
//磁石
struct Magnet {
	Vector2 pos;
	Vector2 speed;
	Vector2 velocity;
	MagnetType type;
	float radius = 0.0f;
	float theta = 0.0f;
	float power = 0.0f;
	float isAlive = 0.0f;
	bool isS;
	unsigned int color = 0;
};

//設計
void MagnetSetting(Magnet& magnet);
void MagnetUpdate(Magnet& magnetS, Magnet& magnetN, float force, float forceDistance);
void MagnetDraw(Magnet& magnet, unsigned int color);