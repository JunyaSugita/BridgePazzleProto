#include "DxLib.h"
#include "Field.h"
#include "Generator.h"
#include "GrovalSetting.h"
#include "Player.h"
#include "KeyboardInput.h"
#include "MapCSVLoader.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "BridgePazzleProto";

// ウィンドウ横幅
const int WIN_WIDTH = gridX * panelX * 50;

// ウィンドウ縦幅
const int WIN_HEIGHT = gridY * panelY * 50;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	SetFontSize(24);

	// ゲームループで使う変数の宣言
	MapCSVLoader::GetInstance().LoadCSV("Map");
	SetGraphMode(gridX * panelX * 50, gridY * panelY * 50, 32);

	Field* field = new Field();
	field->Initialize();
	Generator* generator = new Generator();
	generator->Initialize(field);

	Player::GetInstance().Initialize();


	// ゲームループ
	while (true) {
		//キー
		KeyboardInput::Getinstance().Update();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		Player::GetInstance().Update();
		field->Update();
		generator->Update(field);

		// 描画処理
		field->Draw();
		generator->Draw();
		Player::GetInstance().Draw();

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	//delete処理
	delete field;
	delete generator;

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
