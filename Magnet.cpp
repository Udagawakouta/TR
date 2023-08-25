#include "Magnet.h"
#include "Novice.h"
#include "math.h"
#define _USE_MATH_DEFINES

//宣言
void MagnetSetting(Magnet& magnet) {
	magnet.pos.x = 640;
	magnet.pos.y = 360;
	magnet.speed.x = 2;
	magnet.speed.y = 2;
	magnet.velocity.x = 2;
	magnet.velocity.y = 2;
	magnet.radius = 32;
	magnet.theta = 0;
	//パワー調整
	magnet.power = 80;
	magnet.isAlive = true;
	magnet.isS = true;
	magnet.color = 0xFF;
}

//更新処理
void MagnetUpdate(Magnet& magnetS,Magnet&magnetN,float force, float forceDistance) {

	float distance;
	Vector2 d;

	d.x = magnetN.pos.x - magnetS.pos.x;
	d.y = magnetN.pos.y - magnetS.pos.y;

	distance = sqrtf(d.x * d.x + d.y * d.y);


	if (distance <= forceDistance) {
		if (magnetS.isS == magnetN.isS)
		{
			if (distance >= magnetN.radius + magnetS.radius) {
				force = 10 * (magnetS.power * magnetN.power) / (distance * distance);
				magnetS.theta = atan2(magnetS.pos.y - magnetN.pos.y, magnetS.pos.x - magnetN.pos.x);
				magnetS.pos.x += force * cosf(magnetS.theta);
				magnetS.pos.y += force * sinf(magnetS.theta);
			}
		}
		else
		{
			if (distance >= magnetN.radius + magnetS.radius) {
				force = 10 * (magnetS.power * magnetN.power) / (distance * distance);
				magnetS.theta = atan2(magnetS.pos.y - magnetN.pos.y, magnetS.pos.x - magnetN.pos.x);
				
					magnetS.pos.x -= force * cosf(magnetS.theta);
					magnetS.pos.y -= force * sinf(magnetS.theta);
			}
		}
	}
	Novice::ScreenPrintf(0, 0, "distance:%f", distance);
}

//描画処理
void MagnetDraw(Magnet& magnet, unsigned int color) {

	if (magnet.isS) {
		Novice::DrawEllipse((int)magnet.pos.x, (int)magnet.pos.y, (int)magnet.radius, (int)magnet.radius, 0.0f, RED, kFillModeSolid);
	}
	else {
		Novice::DrawEllipse((int)magnet.pos.x, (int)magnet.pos.y, (int)magnet.radius, (int)magnet.radius, 0.0f, color, kFillModeSolid);
	}
}