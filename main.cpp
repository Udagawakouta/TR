#include <Novice.h>
#include"Magnet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "ImGuiManager.h"

const char kWindowTitle[] = "TR";

//物体の距離を計算する式
float mag(float& magnetSx, float& magnetSy, float& magnetNx, float& magnetNy) {
	float distance;
	Vector2 magnet;

	magnet.x = magnetNx - magnetSx;
	magnet.y = magnetNy - magnetSy;

	distance = sqrtf(magnet.x * magnet.x + magnet.y * magnet.y);
	return distance;
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//N極
	Magnet magnetN;
	MagnetSetting(magnetN);
	//S極
	Magnet magnetS;
	MagnetSetting(magnetS);
	magnetS.pos.x = 1000;


	float force  = 0.0f;

	//距離
	float distance = 300.0f;

	enum MyEnum
	{
		kSouthPole,
		kNorthPole,
	};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//操作
		if (keys[DIK_W])
		{
			magnetS.pos.y -= magnetS.speed.y;
		}
		if (keys[DIK_S])
		{
			magnetS.pos.y += magnetS.speed.y;
		}
		if (keys[DIK_A])
		{
			magnetS.pos.x -= magnetS.speed.x;
		}
		if (keys[DIK_D])
		{
			magnetS.pos.x += magnetS.speed.x;
		}

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
		{
			if(magnetS.isS)
			{
				magnetS.isS = false;
			}
			else {
				magnetS.isS = true;
			}
		}

		MagnetUpdate(magnetS, magnetN, force, distance);
		//distance = mag(magnetN.pos.x, magnetN.pos.y, magnetS.pos.x, magnetS.pos.y);

		ImGui::Begin("MagnetS");
		//ImGui::Text("pos.x:%f  pos.y:%f", magnetS.pos.x, magnetS.pos.y);
		//ImGui::InputFloat("pos.x", &magnetS.pos.x);
		ImGui::SliderFloat("distance", &distance, 0, 640);
		ImGui::SliderFloat("magnetPower", &magnetS.power, 0, 200);
		ImGui::SliderFloat2("pos", &magnetS.pos.x, -640, 640);
		ImGui::Checkbox("isN",&magnetS.isS);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MagnetDraw(magnetN,RED);
		MagnetDraw(magnetS, BLUE);
		//Novice::ScreenPrintf(0, 0, "distance %f", distance);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
