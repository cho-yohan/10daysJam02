#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector2.h"

const char kWindowTitle[] = "5065_LINE_UP";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//============================================================================================================================
	//画像読み込み
	//============================================================================================================================

	int titleGhd =
		Novice::LoadTexture("./resources/title/titleScreen.png");

	int startText[2] = {
	Novice::LoadTexture("./resources/title/startText0.png"),
	Novice::LoadTexture("./resources/title/startText1.png") };

	int playerGhd =
		Novice::LoadTexture("./resources/player/player.png");

	int playerDiedGhd[5] = {
	Novice::LoadTexture("./resources/player/playerDied0.png"),
	Novice::LoadTexture("./resources/player/playerDied1.png"),
	Novice::LoadTexture("./resources/player/playerDied2.png"),
	Novice::LoadTexture("./resources/player/playerDied3.png"),
	Novice::LoadTexture("./resources/player/playerDied4.png") };

	int handGhd[1] = {
	Novice::LoadTexture("./resources/player/hand.png") };

	int backGhd1[2] = {
	Novice::LoadTexture("./resources/background/stage1background1.png"),
	Novice::LoadTexture("./resources/background/stage1background2.png") };

	int backGhd2[2] = {
	Novice::LoadTexture("./resources/background/stage2background1.png"),
	Novice::LoadTexture("./resources/background/stage2background2.png") };

	int backGhd3[2] = {
	Novice::LoadTexture("./resources/background/stage3background1.png"),
	Novice::LoadTexture("./resources/background/stage3background2.png") };

	int backGhd4[2] = {
	Novice::LoadTexture("./resources/background/stage10background1.png"),
	Novice::LoadTexture("./resources/background/stage10background2.png") };

	int memo[10] = {
	Novice::LoadTexture("./resources/memorize/memorize1.png"),
	Novice::LoadTexture("./resources/memorize/memorize2.png"),
	Novice::LoadTexture("./resources/memorize/memorize3.png"),
	Novice::LoadTexture("./resources/memorize/memorize4.png"),
	Novice::LoadTexture("./resources/memorize/memorize5.png"),
	Novice::LoadTexture("./resources/memorize/memorize6.png"),
	Novice::LoadTexture("./resources/memorize/memorize7.png"),
	Novice::LoadTexture("./resources/memorize/memorize8.png"),
	Novice::LoadTexture("./resources/memorize/memorize9.png"),
	Novice::LoadTexture("./resources/memorize/memorize10.png") };

	int boxGhd[16] = {
	Novice::LoadTexture("./resources/stage1box/box1.png"),
	Novice::LoadTexture("./resources/stage1box/box2.png"),
	Novice::LoadTexture("./resources/stage1box/box3.png"),
	Novice::LoadTexture("./resources/stage1box/box4.png"),
	Novice::LoadTexture("./resources/stage1box/box5.png"),
	Novice::LoadTexture("./resources/stage1box/box6.png"),
	Novice::LoadTexture("./resources/stage1box/box7.png"),
	Novice::LoadTexture("./resources/stage1box/box8.png"),
	Novice::LoadTexture("./resources/stage1box/box9.png"),
	Novice::LoadTexture("./resources/stage1box/box10.png"),
	Novice::LoadTexture("./resources/stage1box/box11.png"),
	Novice::LoadTexture("./resources/stage1box/box12.png"),
	Novice::LoadTexture("./resources/stage1box/box13.png"),
	Novice::LoadTexture("./resources/stage1box/box14.png"),
	Novice::LoadTexture("./resources/stage1box/box15.png"),
	Novice::LoadTexture("./resources/stage1box/box16.png") };

	int stageGhd[10] = {
	Novice::LoadTexture("./resources/stage/stageSelect1.png"),
	Novice::LoadTexture("./resources/stage/stageSelect2.png"),
	Novice::LoadTexture("./resources/stage/stageSelect3.png"),
	Novice::LoadTexture("./resources/stage/stageSelect4.png"),
	Novice::LoadTexture("./resources/stage/stageSelect5.png"),
	Novice::LoadTexture("./resources/stage/stageSelect6.png"),
	Novice::LoadTexture("./resources/stage/stageSelect7.png"),
	Novice::LoadTexture("./resources/stage/stageSelect8.png"),
	Novice::LoadTexture("./resources/stage/stageSelect9.png"),
	Novice::LoadTexture("./resources/stage/stageSelect10.png") };

	int clear[2] = {
	Novice::LoadTexture("./resources/stageClear/stageClear.png"),
	Novice::LoadTexture("./resources/stageClear/stageClearMax.png") };

	int cnt[5] = {
	Novice::LoadTexture("./resources/count/count5.png"),
	Novice::LoadTexture("./resources/count/count4.png"),
	Novice::LoadTexture("./resources/count/count3.png"),
	Novice::LoadTexture("./resources/count/count2.png"),
	Novice::LoadTexture("./resources/count/count1.png") };

	int cntScr =
		Novice::LoadTexture("./resources/count/countScreen1.png");


	int soundHandle1 = Novice::LoadAudio("./sound/MusMus-BGM-021.mp3");

	int voiceHandle1 = 0;

	//===========================================================================================================================

	typedef struct Player {
		float x;
		float y;
		bool isAlive;
	}Player;


	typedef struct Box {
		float x;
		float y;
		bool isAlive;
	}Box;

	struct panel {
		int posX;
		int posY;
		int type;
		bool get;
		int textureHandle;
	};

	//===========================================================================================================================

	Vector2 title;
	title.x = 0, title.y = 0;

	Vector2 mainText;
	mainText.x = 230, mainText.y = 180;

	Vector2 text;
	text.x = 400, text.y = 500;

	Vector2 stage1Background[2]{ 0, 0, 1000, 0 };
	Vector2 stage2Background[2]{ 0, 0, 1000, 0 };
	Vector2 stage3Background[2]{ 0, 0, 1000, 0 };

	Vector2 memorizingScreen;
	memorizingScreen.x = 0, memorizingScreen.y = 0;

	Vector2 count;
	count.x = 600, count.y = 300;

	Vector2 memoCount;
	memoCount.x = 0, memoCount.y = 0;

	Vector2 countScreen;
	countScreen.x = 0, countScreen.y = 0;

	Vector2 stage;
	stage.x = 0, stage.y = 0;

	//==========================================================================
	//クリア画面座標
	//==========================================================================
	Vector2 clearScreen;
	clearScreen.x = 0, clearScreen.y = 0;

	//====================================================================
	//ゲームオーバー画面座標
	//====================================================================
	Vector2 gameOverScreen;
	gameOverScreen.x = 0;
	gameOverScreen.y = 0;

	//==================================================================
	//プレイヤーの座標
	//==================================================================
	Player player;
	player.x = 550;
	player.y = 570;
	player.isAlive = true;

	//=================================================================
	//プレイヤーから出る線の座標(四角形に当たってないとき)
	//=================================================================
	Vector2 hand;
	hand.x = 4000;
	hand.y = 4000;

	//======================================================================================
	//box1～box10の座標
	//======================================================================================
	panel stage1box[6]; //stage1の四角形座標位置
	stage1box[0].posX = 120, stage1box[0].posY = 100;
	stage1box[1].posX = 450, stage1box[1].posY = 100;
	stage1box[2].posX = 790, stage1box[2].posY = 100;
	stage1box[3].posX = 120, stage1box[3].posY = 500;
	stage1box[4].posX = 450, stage1box[4].posY = 500;
	stage1box[5].posX = 790, stage1box[5].posY = 500;

	panel stage2box[6]; //stage1の四角形座標位置
	stage2box[0].posX = 120, stage2box[0].posY = 100;
	stage2box[1].posX = 450, stage2box[1].posY = 100;
	stage2box[2].posX = 790, stage2box[2].posY = 100;
	stage2box[3].posX = 120, stage2box[3].posY = 500;
	stage2box[4].posX = 450, stage2box[4].posY = 500;
	stage2box[5].posX = 790, stage2box[5].posY = 500;

	panel stage3box[6]; //stage1の四角形座標位置
	stage3box[0].posX = 120, stage3box[0].posY = 100;
	stage3box[1].posX = 450, stage3box[1].posY = 100;
	stage3box[2].posX = 790, stage3box[2].posY = 100;
	stage3box[3].posX = 120, stage3box[3].posY = 500;
	stage3box[4].posX = 450, stage3box[4].posY = 500;
	stage3box[5].posX = 790, stage3box[5].posY = 500;

	panel stage4box[9]; //stage2の四角形座標位置
	stage4box[0].posX = 120, stage4box[0].posY = 70;
	stage4box[1].posX = 450, stage4box[1].posY = 70;
	stage4box[2].posX = 790, stage4box[2].posY = 70;
	stage4box[3].posX = 120, stage4box[3].posY = 320;
	stage4box[4].posX = 450, stage4box[4].posY = 320;
	stage4box[5].posX = 790, stage4box[5].posY = 320;
	stage4box[6].posX = 120, stage4box[6].posY = 560;
	stage4box[7].posX = 450, stage4box[7].posY = 560;
	stage4box[8].posX = 790, stage4box[8].posY = 560;

	panel stage5box[9]; //stage2の四角形座標位置
	stage5box[0].posX = 120, stage5box[0].posY = 70;
	stage5box[1].posX = 450, stage5box[1].posY = 70;
	stage5box[2].posX = 790, stage5box[2].posY = 70;
	stage5box[3].posX = 120, stage5box[3].posY = 320;
	stage5box[4].posX = 450, stage5box[4].posY = 320;
	stage5box[5].posX = 790, stage5box[5].posY = 320;
	stage5box[6].posX = 120, stage5box[6].posY = 560;
	stage5box[7].posX = 450, stage5box[7].posY = 560;
	stage5box[8].posX = 790, stage5box[8].posY = 560;

	panel stage6box[9]; //stage2の四角形座標位置
	stage6box[0].posX = 120, stage6box[0].posY = 70;
	stage6box[1].posX = 450, stage6box[1].posY = 70;
	stage6box[2].posX = 790, stage6box[2].posY = 70;
	stage6box[3].posX = 120, stage6box[3].posY = 320;
	stage6box[4].posX = 450, stage6box[4].posY = 320;
	stage6box[5].posX = 790, stage6box[5].posY = 320;
	stage6box[6].posX = 120, stage6box[6].posY = 560;
	stage6box[7].posX = 450, stage6box[7].posY = 560;
	stage6box[8].posX = 790, stage6box[8].posY = 560;

	panel stage7box[12]; //stage2の四角形座標位置
	stage7box[0].posX = 100, stage7box[0].posY = 85;
	stage7box[1].posX = 350, stage7box[1].posY = 85;
	stage7box[2].posX = 600, stage7box[2].posY = 85;
	stage7box[3].posX = 855, stage7box[3].posY = 85;
	stage7box[4].posX = 100, stage7box[4].posY = 325;
	stage7box[5].posX = 350, stage7box[5].posY = 325;
	stage7box[6].posX = 600, stage7box[6].posY = 325;
	stage7box[7].posX = 855, stage7box[7].posY = 325;
	stage7box[8].posX = 100, stage7box[8].posY = 570;
	stage7box[9].posX = 350, stage7box[9].posY = 570;
	stage7box[10].posX = 600, stage7box[10].posY = 570;
	stage7box[11].posX = 855, stage7box[11].posY = 570;

	panel stage8box[12]; //stage2の四角形座標位置
	stage8box[0].posX = 100, stage8box[0].posY = 85;
	stage8box[1].posX = 350, stage8box[1].posY = 85;
	stage8box[2].posX = 600, stage8box[2].posY = 85;
	stage8box[3].posX = 855, stage8box[3].posY = 85;
	stage8box[4].posX = 100, stage8box[4].posY = 325;
	stage8box[5].posX = 350, stage8box[5].posY = 325;
	stage8box[6].posX = 600, stage8box[6].posY = 325;
	stage8box[7].posX = 855, stage8box[7].posY = 325;
	stage8box[8].posX = 100, stage8box[8].posY = 570;
	stage8box[9].posX = 350, stage8box[9].posY = 570;
	stage8box[10].posX = 600, stage8box[10].posY = 570;
	stage8box[11].posX = 855, stage8box[11].posY = 570;

	panel stage9box[12]; //stage2の四角形座標位置
	stage9box[0].posX = 100, stage9box[0].posY = 85;
	stage9box[1].posX = 350, stage9box[1].posY = 85;
	stage9box[2].posX = 600, stage9box[2].posY = 85;
	stage9box[3].posX = 855, stage9box[3].posY = 85;
	stage9box[4].posX = 100, stage9box[4].posY = 325;
	stage9box[5].posX = 350, stage9box[5].posY = 325;
	stage9box[6].posX = 600, stage9box[6].posY = 325;
	stage9box[7].posX = 855, stage9box[7].posY = 325;
	stage9box[8].posX = 100, stage9box[8].posY = 570;
	stage9box[9].posX = 350, stage9box[9].posY = 570;
	stage9box[10].posX = 600, stage9box[10].posY = 570;
	stage9box[11].posX = 855, stage9box[11].posY = 570;

	panel stage10box[16]; //stage2の四角形座標位置
	stage10box[0].posX = 100, stage10box[0].posY = 70;
	stage10box[1].posX = 350, stage10box[1].posY = 70;
	stage10box[2].posX = 600, stage10box[2].posY = 70;
	stage10box[3].posX = 855, stage10box[3].posY = 70;
	stage10box[4].posX = 100, stage10box[4].posY = 260;
	stage10box[5].posX = 350, stage10box[5].posY = 260;
	stage10box[6].posX = 600, stage10box[6].posY = 260;
	stage10box[7].posX = 855, stage10box[7].posY = 260;
	stage10box[8].posX = 100, stage10box[8].posY = 430;
	stage10box[9].posX = 350, stage10box[9].posY = 430;
	stage10box[10].posX = 600, stage10box[10].posY = 430;
	stage10box[11].posX = 855, stage10box[11].posY = 430;
	stage10box[12].posX = 100, stage10box[12].posY = 610;
	stage10box[13].posX = 350, stage10box[13].posY = 610;
	stage10box[14].posX = 600, stage10box[14].posY = 610;
	stage10box[15].posX = 855, stage10box[15].posY = 610;

	//======================================================================================
	//box1
	//======================================================================================
	for (int i = 0; i <= 6; i++) {
		stage1box[i - 1].type = i;
	}

	for (int i = 0; i <= 6; i++) {
		stage2box[i - 1].type = i;
	}

	for (int i = 0; i <= 6; i++) {
		stage3box[i - 1].type = i;
	}

	for (int i = 0; i <= 9; i++)
	{
		stage4box[i - 1].type = i;
	}

	for (int i = 0; i <= 9; i++)
	{
		stage5box[i - 1].type = i;
	}

	for (int i = 0; i <= 9; i++)
	{
		stage6box[i - 1].type = i;
	}

	for (int i = 1; i <= 12; i++)
	{
		stage7box[i - 1].type = i;
	}

	for (int i = 1; i <= 12; i++)
	{
		stage8box[i - 1].type = i;
	}

	for (int i = 1; i <= 12; i++)
	{
		stage9box[i - 1].type = i;
	}

	for (int i = 0; i <= 16; i++)
	{
		stage10box[i - 1].type = i;
	}

	//===================================================================================
	//クリア条件
	//===================================================================================

	int goalPanes1[] = { 6, 1, 5 };
	int goalPanes2[] = { 3, 2, 4 };
	int goalPanes3[] = { 2, 3, 6 };
	int goalPanes4[] = { 5, 2, 1, 9, 8 };
	int goalPanes5[] = { 4, 6, 7, 1, 3 };
	int goalPanes6[] = { 1, 8, 9, 2, 7 };
	int goalPanes7[] = { 12, 5, 6, 8, 11, 1, 10 };
	int goalPanes8[] = { 4, 10, 3, 11, 2, 12, 9 };
	int goalPanes9[] = { 11, 4, 6, 7, 5, 9, 3 };
	int goalPanes10[] = { 12, 15, 13, 4, 3, 5, 16, 8, 10, 14 };


	//===================================================================================
	//box1～box9が右下に格納されているかの判定
	//===================================================================================
	for (int i = 0; i < 6; i++) {
		stage1box[i].get = false;
	}

	for (int i = 0; i < 6; i++) {
		stage2box[i].get = false;
	}

	for (int i = 0; i < 6; i++) {
		stage3box[i].get = false;
	}

	for (int i = 0; i < 9; i++) {
		stage4box[i].get = false;
	}

	for (int i = 0; i < 9; i++) {
		stage5box[i].get = false;
	}

	for (int i = 0; i < 9; i++) {
		stage6box[i].get = false;
	}

	for (int i = 0; i < 12; i++) {
		stage7box[i].get = false;
	}

	for (int i = 0; i < 12; i++) {
		stage8box[i].get = false;
	}

	for (int i = 0; i < 12; i++) {
		stage9box[i].get = false;
	}

	for (int i = 0; i < 16; i++) {
		stage10box[i].get = false;
	}


	int t = 0;
	int textTimer = 30;
	int d = 0;
	int diedTimer = 30;

	int c = 2;
	int countTimer = 50;
	int mc = 0;
	int memoCountTimer = 50;

	int enter = 0;

	int nextBox = 0;

	bool isHand = true;
	bool isTrans = false;

	float X = 0, Y = 0;

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

		//=========================================================================
		//プレイヤーの移動
		//=========================================================================

		X = 0, Y = 0;

		float length = sqrtf(X * X + Y * Y);
		if ((int)length != 0.0f) {
			X /= (int)length;
		}

		if (Novice::IsPlayingAudio(voiceHandle1) == 0) {
			voiceHandle1 = Novice::PlayAudio(soundHandle1, true, 1.0f);
		}

		enum Scane {
			TITLE,

			STAGE1,
			STAGE2,
			STAGE3,
			STAGE4,
			STAGE5,
			STAGE6,
			STAGE7,
			STAGE8,
			STAGE9,
			STAGE10,

			COUNT1,
			COUNT2,
			COUNT3,
			COUNT4,
			COUNT5,
			COUNT6,
			COUNT7,
			COUNT8,
			COUNT9,
			COUNT10,

			MEMORIZE1,
			MEMORIZE2,
			MEMORIZE3,
			MEMORIZE4,
			MEMORIZE5,
			MEMORIZE6,
			MEMORIZE7,
			MEMORIZE8,
			MEMORIZE9,
			MEMORIZE10,

			GAME1,
			GAME2,
			GAME3,
			GAME4,
			GAME5,
			GAME6,
			GAME7,
			GAME8,
			GAME9,
			GAME10,

			GAMECLEAR1,
			GAMECLEAR2,
			GAMECLEAR3,
			GAMECLEAR4,
			GAMECLEAR5,
			GAMECLEAR6,
			GAMECLEAR7,
			GAMECLEAR8,
			GAMECLEAR9,
			GAMECLEAR10

		};

		switch (enter) {
		case TITLE:
			Novice::DrawSprite((int)title.x, (int)title.y, titleGhd, 1, 1, 0.0f, WHITE);

			if (enter == 0) {
				Novice::DrawSprite((int)text.x, (int)text.y, startText[t], 1, 1, 0.0f, WHITE);
				textTimer = textTimer - 1;
				if (textTimer <= 0) {
					t = t + 1;
					textTimer = 30;
					if (t >= 2) {
						t = 0;
					}
				}
			}

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE1;
			}

			break;


		case STAGE1:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[0], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT1;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 6; i++) {
					stage1box[i].get = false;
				}
			}

			break;

		case STAGE2:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[1], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT2;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 6; i++) {
					stage2box[i].get = false;
				}
			}

			break;

		case STAGE3:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[2], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT3;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 6; i++) {
					stage3box[i].get = false;
				}
			}

			break;

		case STAGE4:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[3], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT4;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 9; i++) {
					stage4box[i].get = false;
				}
			}

			break;

		case STAGE5:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[4], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT5;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 9; i++) {
					stage5box[i].get = false;
				}
			}

			break;

		case STAGE6:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[5], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT6;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 9; i++) {
					stage6box[i].get = false;
				}
			}

			break;

		case STAGE7:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[6], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT7;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 12; i++) {
					stage7box[i].get = false;
				}
			}

			break;

		case STAGE8:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[7], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT8;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 12; i++) {
					stage8box[i].get = false;
				}
			}

			break;

		case STAGE9:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[8], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT9;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 12; i++) {
					stage9box[i].get = false;
				}
			}

			break;

		case STAGE10:
			Novice::DrawSprite((int)stage.x, (int)stage.y, stageGhd[9], 1, 1, 0.0f, WHITE);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = COUNT10;
				diedTimer = 0;
				d = 0;
				c = 2;

				isTrans = false;
				player.isAlive = true;
				for (int i = 0; i < 16; i++) {
					stage10box[i].get = false;
				}
			}

			break;


		case COUNT1:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT1) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE1;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT2:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT2) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE2;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT3:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT3) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE3;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT4:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT4) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE4;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT5:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT5) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE5;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT6:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT6) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE6;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT7:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT7) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE7;
				mc = 0;
				nextBox = 0;
			}
			break;

		case COUNT8:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT8) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE8;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT9:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT9) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE9;
				mc = 0;
				nextBox = 0;
			}

			break;

		case COUNT10:
			Novice::DrawSprite((int)countScreen.x, (int)countScreen.y, cntScr, 1, 1, 0.0f, WHITE);

			if (enter == COUNT10) {
				Novice::DrawSprite((int)count.x, (int)count.y, cnt[c], 1, 1, 0.0f, WHITE);
				countTimer = countTimer - 1;
				if (countTimer <= 0) {
					c = c + 1;
					countTimer = 50;
					if (c >= 5) {
						c = 5;
					}
				}
			}
			if (c == 5) {
				enter = MEMORIZE10;
				mc = 0;
				nextBox = 0;
			}
			break;

		case MEMORIZE1:

			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[0], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE1) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME1;
			}

			break;

		case MEMORIZE2:

			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[1], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE2) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME2;
			}

			break;

		case MEMORIZE3:

			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[2], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE3) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME3;
			}

			break;

		case MEMORIZE4:
			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[3], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE4) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME4;
			}

			break;

		case MEMORIZE5:
			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[4], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE5) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME5;
			}

			break;

		case MEMORIZE6:
			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[5], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE6) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME6;
			}

			break;

		case MEMORIZE7:
			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[6], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE7) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME7;
			}

			break;

		case MEMORIZE8:
			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[7], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE8) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME8;
			}

			break;

		case MEMORIZE9:
			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[8], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE9) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME9;
			}

			break;

		case MEMORIZE10:
			Novice::DrawSprite((int)memorizingScreen.x, (int)memorizingScreen.y, memo[9], 1, 1, 0.0f, WHITE);

			if (enter == MEMORIZE10) {
				Novice::DrawSprite((int)memoCount.x, (int)memoCount.y, cnt[mc], 1, 1, 0.0f, WHITE);
				memoCountTimer = memoCountTimer - 1;
				if (memoCountTimer <= 0) {
					mc = mc + 1;
					memoCountTimer = 50;
					if (mc >= 5) {
						mc = 5;
					}
				}
			}
			if (mc == 5) {
				enter = GAME10;
			}

			break;


		case GAME1:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd1[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd1[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 6; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes1) / sizeof(goalPanes1[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage1box[i].type == goalPanes1[j]) { goalNum = j; }
				}

				if (stage1box[i].get)
				{
					x = 1100;
					y = 550 - 250 * goalNum;
					if (i == 4) {
						enter = GAMECLEAR1;
					}
				}
				else
				{
					x = stage1box[i].posX;
					y = stage1box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 1, 1, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE1;
			}

			for (int i = 0; i < 6; i++)
			{
				if (stage1box[i].get) { continue; }
				if (hand.x + 27 < stage1box[i].posX + 100 && stage1box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage1box[i].posY + 100 && stage1box[i].posY < hand.y - 22 + 32)
				{
					if (stage1box[i].type == goalPanes1[nextBox])
					{
						stage1box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;


		case GAME2:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd1[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd1[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 6; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes2) / sizeof(goalPanes2[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage2box[i].type == goalPanes2[j]) { goalNum = j; }
				}

				if (stage2box[i].get)
				{
					x = 1100;
					y = 550 - 250 * goalNum;
					if (i == 3) {
						enter = GAMECLEAR2;
					}
				}
				else
				{
					x = stage2box[i].posX;
					y = stage2box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 1, 1, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE2;
			}

			for (int i = 0; i < 6; i++)
			{
				if (stage2box[i].get) { continue; }
				if (hand.x + 27 < stage2box[i].posX + 100 && stage2box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage2box[i].posY + 100 && stage2box[i].posY < hand.y - 22 + 32)
				{
					if (stage2box[i].type == goalPanes2[nextBox])
					{
						stage2box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;


		case GAME3:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd1[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd1[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 6; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes3) / sizeof(goalPanes3[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage3box[i].type == goalPanes3[j]) { goalNum = j; }
				}

				if (stage3box[i].get)
				{
					x = 1100;
					y = 550 - 250 * goalNum;
					if (i == 5) {
						enter = GAMECLEAR3;
					}
				}
				else
				{
					x = stage3box[i].posX;
					y = stage3box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 1, 1, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE3;
			}

			for (int i = 0; i < 6; i++)
			{
				if (stage3box[i].get) { continue; }
				if (hand.x + 27 < stage3box[i].posX + 100 && stage3box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage3box[i].posY + 100 && stage3box[i].posY < hand.y - 22 + 32)
				{
					if (stage3box[i].type == goalPanes3[nextBox])
					{
						stage3box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;


		case GAME4:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd2[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd2[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 9; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes4) / sizeof(goalPanes4[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage4box[i].type == goalPanes4[j]) { goalNum = j; }
				}

				if (stage4box[i].get)
				{
					x = 1100;
					y = 600 - 140 * goalNum;
					if (i == 7) {
						enter = GAMECLEAR4;
					}
				}
				else
				{
					x = stage4box[i].posX;
					y = stage4box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 1, 1, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE4;
			}

			for (int i = 0; i < 9; i++)
			{
				if (stage4box[i].get) { continue; }
				if (hand.x + 27 < stage4box[i].posX + 100 && stage4box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage4box[i].posY + 100 && stage4box[i].posY < hand.y - 22 + 32)
				{
					if (stage4box[i].type == goalPanes4[nextBox])
					{
						stage4box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;


		case GAME5:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd2[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd2[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 9; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes5) / sizeof(goalPanes5[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage5box[i].type == goalPanes5[j]) { goalNum = j; }
				}

				if (stage5box[i].get)
				{
					x = 1100;
					y = 600 - 140 * goalNum;
					if (i == 2) {
						enter = GAMECLEAR5;
					}
				}
				else
				{
					x = stage5box[i].posX;
					y = stage5box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 1, 1, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE5;
			}

			for (int i = 0; i < 9; i++)
			{
				if (stage5box[i].get) { continue; }
				if (hand.x + 27 < stage5box[i].posX + 100 && stage5box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage5box[i].posY + 100 && stage5box[i].posY < hand.y - 22 + 32)
				{
					if (stage5box[i].type == goalPanes5[nextBox])
					{
						stage5box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;

		case GAME6:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd2[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd2[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 9; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes6) / sizeof(goalPanes6[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage6box[i].type == goalPanes6[j]) { goalNum = j; }
				}

				if (stage6box[i].get)
				{
					x = 1100;
					y = 600 - 140 * goalNum;
					if (i == 6) {
						enter = GAMECLEAR6;
					}
				}
				else
				{
					x = stage6box[i].posX;
					y = stage6box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 1, 1, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE6;
			}

			for (int i = 0; i < 9; i++)
			{
				if (stage6box[i].get) { continue; }
				if (hand.x + 27 < stage6box[i].posX + 100 && stage6box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage6box[i].posY + 100 && stage6box[i].posY < hand.y - 22 + 32)
				{
					if (stage6box[i].type == goalPanes6[nextBox])
					{
						stage6box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;


		case GAME7:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd3[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd3[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 12; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes7) / sizeof(goalPanes7[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage7box[i].type == goalPanes7[j]) { goalNum = j; }
				}

				if (stage7box[i].get)
				{
					x = 1120;
					y = 650 - 103 * goalNum;
					if (i == 9) {
						enter = GAMECLEAR7;
					}
				}
				else
				{
					x = stage7box[i].posX;
					y = stage7box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 0.5, 0.5, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE7;
			}

			for (int i = 0; i < 12; i++)
			{
				if (stage7box[i].get) { continue; }
				if (hand.x + 27 < stage7box[i].posX + 50 && stage7box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage7box[i].posY + 50 && stage7box[i].posY < hand.y - 22 + 32)
				{
					if (stage7box[i].type == goalPanes7[nextBox])
					{
						stage7box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;


		case GAME8:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd3[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd3[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 12; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes8) / sizeof(goalPanes8[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage8box[i].type == goalPanes8[j]) { goalNum = j; }
				}

				if (stage8box[i].get)
				{
					x = 1120;
					y = 650 - 103 * goalNum;
					if (i == 8) {
						enter = GAMECLEAR8;
					}
				}
				else
				{
					x = stage8box[i].posX;
					y = stage8box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 0.5, 0.5, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE8;
			}

			for (int i = 0; i < 12; i++)
			{
				if (stage8box[i].get) { continue; }
				if (hand.x + 27 < stage8box[i].posX + 50 && stage8box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage8box[i].posY + 50 && stage8box[i].posY < hand.y - 22 + 32)
				{
					if (stage8box[i].type == goalPanes8[nextBox])
					{
						stage8box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;


		case GAME9:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd3[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd3[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 12; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes9) / sizeof(goalPanes9[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage9box[i].type == goalPanes9[j]) { goalNum = j; }
				}

				if (stage9box[i].get)
				{
					x = 1120;
					y = 650 - 103 * goalNum;
					if (i == 2) {
						enter = GAMECLEAR9;
					}
				}
				else
				{
					x = stage9box[i].posX;
					y = stage9box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 0.5, 0.5, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE9;
			}

			for (int i = 0; i < 12; i++)
			{
				if (stage9box[i].get) { continue; }
				if (hand.x + 27 < stage9box[i].posX + 50 && stage9box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage9box[i].posY + 50 && stage9box[i].posY < hand.y - 22 + 32)
				{
					if (stage9box[i].type == goalPanes9[nextBox])
					{
						stage9box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;

		case GAME10:

			X = 0, Y = 0;

			if (keys[DIK_W]) {
				Y = -1;
				if (player.y <= 0) {
					Y = 0;
				}
			}
			if (keys[DIK_S]) {
				Y = 1;
				if (player.y >= 651) {
					Y = 0;
				}
			}
			if (keys[DIK_A]) {
				X = -1;
				if (player.x <= 0) {
					X = 0;
				}
			}
			if (keys[DIK_D]) {
				X = 1;
				if (player.x >= 936) {
					X = 0;
				}
			}

			player.x += (int)X * 10;
			player.y += (int)Y * 10;

			Novice::DrawSprite((int)stage1Background[0].x, (int)stage1Background[0].y, backGhd4[0], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)stage1Background[1].x, (int)stage1Background[1].y, backGhd4[1], 1, 1, 0.0f, 0xFFFFFFFF);
			//==================================================================================================
			//敵画像の座標＋描画処理
			//==================================================================================================
			for (int i = 0; i < 16; i++) {
				int x, y, goalNum = 0;
				int goalSize = sizeof(goalPanes10) / sizeof(goalPanes10[0]);
				for (int j = 0; j < goalSize; j++)
				{
					if (stage10box[i].type == goalPanes10[j]) { goalNum = j; }
				}

				if (stage10box[i].get)
				{
					x = 1120;
					y = 659 - 73 * goalNum;
					if (i == 13) {
						enter = GAMECLEAR10;
					}
				}
				else
				{
					x = stage10box[i].posX;
					y = stage10box[i].posY;
				}
				Novice::DrawSprite(x, y, boxGhd[i], 0.5, 0.5, 0.0f, WHITE);
			}


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				isHand = true;
				hand.x = player.x;
				hand.y = player.y;
				if (isHand == true) {
					Novice::DrawSprite((int)hand.x + 27, (int)hand.y - 22, handGhd[0], 1, 1, 0.0f, WHITE);
					isHand = false;
				}
			}
			else { hand.x = 4000; hand.y = 4000; }

			if (isTrans == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerGhd, 1, 1, 0.0f, WHITE);
			}

			if (player.isAlive == false) {
				Novice::DrawSprite((int)player.x, (int)player.y, playerDiedGhd[d], 1, 1, 0.0f, WHITE);
				diedTimer = diedTimer - 1;
				if (diedTimer <= 0) {
					d = d + 1;
					diedTimer = 30;

					isTrans = true;

					player.x += X = 0;
					player.y += Y = 0;

					if (d >= 5) {
						d = 5;
					}
				}
			}
			if (d == 5) {
				enter = STAGE10;
			}

			for (int i = 0; i < 16; i++)
			{
				if (stage10box[i].get) { continue; }
				if (hand.x + 27 < stage10box[i].posX + 50 && stage10box[i].posX < hand.x + 27 + 10 &&
					hand.y - 22 < stage10box[i].posY + 50 && stage10box[i].posY < hand.y - 22 + 32)
				{
					if (stage10box[i].type == goalPanes10[nextBox])
					{
						stage10box[i].get = true;
						nextBox++;
					}
					else { player.isAlive = false; }
				}
			}

			break;

		case GAMECLEAR1://ステージ1クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE2;
			}
			break;

		case GAMECLEAR2://ステージ1クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE3;
			}
			break;

		case GAMECLEAR3://ステージ1クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE4;
			}
			break;

		case GAMECLEAR4://ステージ2クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE5;
			}
			break;

		case GAMECLEAR5://ステージ1クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE6;
			}
			break;

		case GAMECLEAR6://ステージ1クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE7;
			}
			break;

		case GAMECLEAR7://ステージ2クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE8;
			}
			break;

		case GAMECLEAR8://ステージ1クリア画面表示＋ステージセレクトへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE9;
			}
			break;

		case GAMECLEAR9:
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[0], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = STAGE10;
			}
			break;

		case GAMECLEAR10://ステージ3クリア画面表示＋タイトルへ戻る
			Novice::DrawSprite((int)clearScreen.x, (int)clearScreen.y, clear[1], 1, 1, 0.0f, WHITE);
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				enter = TITLE;

				Novice::StopAudio(voiceHandle1);
				if (Novice::IsPlayingAudio(voiceHandle1) == 0) {
					voiceHandle1 = Novice::PlayAudio(soundHandle1, true, 1.0f);
				}
				//=============================================================================================
				//初期化
				//=============================================================================================
				stage1box[0].posX = 120, stage1box[0].posY = 100;
				stage1box[1].posX = 450, stage1box[1].posY = 100;
				stage1box[2].posX = 790, stage1box[2].posY = 100;
				stage1box[3].posX = 120, stage1box[3].posY = 500;
				stage1box[4].posX = 450, stage1box[4].posY = 500;
				stage1box[5].posX = 790, stage1box[5].posY = 500;

				stage2box[0].posX = 120, stage2box[0].posY = 100;
				stage2box[1].posX = 450, stage2box[1].posY = 100;
				stage2box[2].posX = 790, stage2box[2].posY = 100;
				stage2box[3].posX = 120, stage2box[3].posY = 500;
				stage2box[4].posX = 450, stage2box[4].posY = 500;
				stage2box[5].posX = 790, stage2box[5].posY = 500;

				stage3box[0].posX = 120, stage3box[0].posY = 100;
				stage3box[1].posX = 450, stage3box[1].posY = 100;
				stage3box[2].posX = 790, stage3box[2].posY = 100;
				stage3box[3].posX = 120, stage3box[3].posY = 500;
				stage3box[4].posX = 450, stage3box[4].posY = 500;
				stage3box[5].posX = 790, stage3box[5].posY = 500;

				stage4box[0].posX = 120, stage4box[0].posY = 70;
				stage4box[1].posX = 450, stage4box[1].posY = 70;
				stage4box[2].posX = 790, stage4box[2].posY = 70;
				stage4box[3].posX = 120, stage4box[3].posY = 320;
				stage4box[4].posX = 450, stage4box[4].posY = 320;
				stage4box[5].posX = 790, stage4box[5].posY = 320;
				stage4box[6].posX = 120, stage4box[6].posY = 560;
				stage4box[7].posX = 450, stage4box[7].posY = 560;
				stage4box[8].posX = 790, stage4box[8].posY = 560;

				stage5box[0].posX = 120, stage5box[0].posY = 70;
				stage5box[1].posX = 450, stage5box[1].posY = 70;
				stage5box[2].posX = 790, stage5box[2].posY = 70;
				stage5box[3].posX = 120, stage5box[3].posY = 320;
				stage5box[4].posX = 450, stage5box[4].posY = 320;
				stage5box[5].posX = 790, stage5box[5].posY = 320;
				stage5box[6].posX = 120, stage5box[6].posY = 560;
				stage5box[7].posX = 450, stage5box[7].posY = 560;
				stage5box[8].posX = 790, stage5box[8].posY = 560;

				stage6box[0].posX = 120, stage6box[0].posY = 70;
				stage6box[1].posX = 450, stage6box[1].posY = 70;
				stage6box[2].posX = 790, stage6box[2].posY = 70;
				stage6box[3].posX = 120, stage6box[3].posY = 320;
				stage6box[4].posX = 450, stage6box[4].posY = 320;
				stage6box[5].posX = 790, stage6box[5].posY = 320;
				stage6box[6].posX = 120, stage6box[6].posY = 560;
				stage6box[7].posX = 450, stage6box[7].posY = 560;
				stage6box[8].posX = 790, stage6box[8].posY = 560;

				stage7box[0].posX = 100, stage7box[0].posY = 85;
				stage7box[1].posX = 350, stage7box[1].posY = 85;
				stage7box[2].posX = 600, stage7box[2].posY = 85;
				stage7box[3].posX = 855, stage7box[3].posY = 85;
				stage7box[4].posX = 100, stage7box[4].posY = 325;
				stage7box[5].posX = 350, stage7box[5].posY = 325;
				stage7box[6].posX = 600, stage7box[6].posY = 325;
				stage7box[7].posX = 855, stage7box[7].posY = 325;
				stage7box[8].posX = 100, stage7box[8].posY = 570;
				stage7box[9].posX = 350, stage7box[9].posY = 570;
				stage7box[10].posX = 600, stage7box[10].posY = 570;
				stage7box[11].posX = 855, stage7box[11].posY = 570;

				stage8box[0].posX = 100, stage8box[0].posY = 85;
				stage8box[1].posX = 350, stage8box[1].posY = 85;
				stage8box[2].posX = 600, stage8box[2].posY = 85;
				stage8box[3].posX = 855, stage8box[3].posY = 85;
				stage8box[4].posX = 100, stage8box[4].posY = 325;
				stage8box[5].posX = 350, stage8box[5].posY = 325;
				stage8box[6].posX = 600, stage8box[6].posY = 325;
				stage8box[7].posX = 855, stage8box[7].posY = 325;
				stage8box[8].posX = 100, stage8box[8].posY = 570;
				stage8box[9].posX = 350, stage8box[9].posY = 570;
				stage8box[10].posX = 600, stage8box[10].posY = 570;
				stage8box[11].posX = 855, stage8box[11].posY = 570;

				stage9box[0].posX = 100, stage9box[0].posY = 85;
				stage9box[1].posX = 350, stage9box[1].posY = 85;
				stage9box[2].posX = 600, stage9box[2].posY = 85;
				stage9box[3].posX = 855, stage9box[3].posY = 85;
				stage9box[4].posX = 100, stage9box[4].posY = 325;
				stage9box[5].posX = 350, stage9box[5].posY = 325;
				stage9box[6].posX = 600, stage9box[6].posY = 325;
				stage9box[7].posX = 855, stage9box[7].posY = 325;
				stage9box[8].posX = 100, stage9box[8].posY = 570;
				stage9box[9].posX = 350, stage9box[9].posY = 570;
				stage9box[10].posX = 600, stage9box[10].posY = 570;
				stage9box[11].posX = 855, stage9box[11].posY = 570;

				stage10box[0].posX = 100, stage10box[0].posY = 70;
				stage10box[1].posX = 350, stage10box[1].posY = 70;
				stage10box[2].posX = 600, stage10box[2].posY = 70;
				stage10box[3].posX = 855, stage10box[3].posY = 70;
				stage10box[4].posX = 100, stage10box[4].posY = 260;
				stage10box[5].posX = 350, stage10box[5].posY = 260;
				stage10box[6].posX = 600, stage10box[6].posY = 260;
				stage10box[7].posX = 855, stage10box[7].posY = 260;
				stage10box[8].posX = 100, stage10box[8].posY = 430;
				stage10box[9].posX = 350, stage10box[9].posY = 430;
				stage10box[10].posX = 600, stage10box[10].posY = 430;
				stage10box[11].posX = 855, stage10box[11].posY = 430;
				stage10box[12].posX = 100, stage10box[12].posY = 610;
				stage10box[13].posX = 350, stage10box[13].posY = 610;
				stage10box[14].posX = 600, stage10box[14].posY = 610;
				stage10box[15].posX = 855, stage10box[15].posY = 610;

				for (int i = 0; i < 6; i++) {
					stage1box[i].get = false;
				}

				for (int i = 0; i < 6; i++) {
					stage2box[i].get = false;
				}

				for (int i = 0; i < 6; i++) {
					stage3box[i].get = false;
				}

				for (int i = 0; i < 9; i++) {
					stage4box[i].get = false;
				}

				for (int i = 0; i < 9; i++) {
					stage5box[i].get = false;
				}

				for (int i = 0; i < 9; i++) {
					stage6box[i].get = false;
				}

				for (int i = 0; i < 12; i++) {
					stage7box[i].get = false;
				}

				for (int i = 0; i < 12; i++) {
					stage8box[i].get = false;
				}

				for (int i = 0; i < 12; i++) {
					stage9box[i].get = false;
				}

				for (int i = 0; i < 16; i++) {
					stage10box[i].get = false;
				}

				nextBox = 0;

				enter = 0;
				c = 2;
				mc = 0;
			}
			break;

		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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
