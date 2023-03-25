#include "Generator.h"
#include "Player.h"

Generator::Generator()
{
}

Generator::~Generator()
{
}

void Generator::Initialize(Field* field)
{
	field_ = field;
	have_ = false;

	//すでにあるやつをつなぐ
	ConnectGenerator();

	//最初の情報を記録
	field_->andoMapActive[0] = true;
	for (int j = 0; j < gridY * panelY; j++) {
		for (int k = 0; k < gridX * panelX; k++) {
			field_->andoMap[0][j][k] = field_->map[j][k];
			field_->playerPos[0] = Vector2(25, 25);
		}
	}
}

void Generator::Update(Field* field)
{
	//フィールド情報取得
	field_ = field;
	//マウス情報取得
	GetMousePoint(&mouseX, &mouseY);
	//マウス情報をマップチップ座標化
	mouseMapPointX = mouseX / (gridX * 50);
	mouseMapPointY = mouseY / (gridY * 50);

	//繋がりを消す
	Disconnectgenerator();

	//すでにあるやつをつなぐ
	ConnectGenerator();

	//前フレームと発電機の場所が違ったらando用に記録
	bool dif = false;

	//1番新しい情報を探す
	for (int i = field_->ANDO_MAP_CONST - 1; i >= 0; i--) {
		if (field_->andoMapActive[i] == true) {
			for (int j = 0; j < gridY * panelY; j++) {
				for (int k = 0; k < gridX * panelX; k++) {
					//違っているか判定
					if (field_->map[j][k] != field_->andoMap[i][j][k]) {
						dif = true;
					}
				}
			}
			break;
		}
	}
	//違ったら記録
	if (dif) {
		for (int i = 0; i < field_->ANDO_MAP_CONST; i++) {
			if (field_->andoMapActive[i] == false) {
				field_->andoMapActive[i] = true;
				for (int j = 0; j < gridY * panelY; j++) {
					for (int k = 0; k < gridX * panelX; k++) {
						field_->andoMap[i][j][k] = field_->map[j][k];
						field_->playerPos[i] = Player::GetInstance().GetEndPos();
					}
				}
				break;
			}
		}
	}

	//クリックしている時
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		//クリックした瞬間
		if (have_ == false && field_->panelMap[mouseMapPointY][mouseMapPointX] == 1) {
			//つかんだ場所を記録
			oldHavePosX_ = mouseMapPointX;
			oldHavePosY_ = mouseMapPointY;

			//持っている数字を記録
			for (int i = 0; i < gridX; i++) {
				for (int j = 0; j < gridY; j++) {
					haveNum_[j][i] = field_->GetMapNum(mouseMapPointX * gridX + i, mouseMapPointY * gridY + j);
					field_->SetMapNum(mouseMapPointX * gridX + i, mouseMapPointY * gridY + j, -2);
				}
			}

			//持っているフラグを立てる
			have_ = true;
			//パネル操作
			field_->panelMap[mouseMapPointY][mouseMapPointX] = 0;
		}
	}
	//クリックしていなくて持っているフラグがtrueの時
	//(発電機を置くとき)
	else if (have_ == true) {
		//発電機を置く場所が空白の場所では無い時
		if (field_->panelMap[mouseMapPointY][mouseMapPointX] != 0) {
			//発電機を元の位置に戻す
			//何も持ってないことにする

			for (int i = 0; i < gridX; i++) {
				for (int j = 0; j < gridY; j++) {
					field_->SetMapNum(oldHavePosX_ * gridX + i, oldHavePosY_ * gridY + j, haveNum_[j][i]);
					haveNum_[j][i] = 0;
				}
			}

			//持っているフラグをfalseに
			have_ = false;
			//パネル操作
			field_->panelMap[oldHavePosY_][oldHavePosX_] = 1;
		}
		//発電機を置く場所が空白の時
		else {
			//発電機を置く
			//何も持ってないことにする
			for (int i = 0; i < gridX; i++) {
				for (int j = 0; j < gridY; j++) {
					field_->SetMapNum(mouseMapPointX * gridX + i, mouseMapPointY * gridY + j, haveNum_[j][i]);
					haveNum_[j][i] = 0;
				}
			}

			//持っているフラグをfalseに
			have_ = false;
			//パネル操作
			field_->panelMap[mouseMapPointY][mouseMapPointX] = 1;
		}
	}
}

void Generator::Draw()
{
	if (have_ == true) {
		//DrawCircle(mouseX, mouseY, field_->gridLength / 2, GetColor(255, 255, 255));
	}
	else {
		DrawFormatString(100, 0, GetColor(255, 255, 255), "RIGHT_CLICK : ANDO");
	}
}

void Generator::ConnectGenerator()
{
	for (int i = 0; i < gridY * panelY; i++) {
		for (int j = 0; j < gridX * panelX; j++) {
			if (field_->map[i][j] > 0 && field_->map[i][j] < 20) {
				//繋がり検索
				//上
				for (int k = i - 1; k >= 0; k--) {
					//発電機を探す
					if (field_->map[k][j] < 20 && field_->map[k][j] >= 1) {
						//あればそこまで線を引く
						for (int l = k + 1; l < i; l++) {
							//線の場所が空白なら縦線を入れる
							if (field_->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//すでに横線があれば十字にする
							else if (field_->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if (field_->map[k][j] == -1) {
						break;
					}
				}
				//下
				for (int k = i + 1; k < gridY * panelY; k++) {
					//発電機を探す
					if (field_->map[k][j] < 20 && field_->map[k][j] >= 1) {
						//あればそこまで線を引く
						for (int l = k - 1; l > i; l--) {
							//線の場所が空白なら縦線を入れる
							if (field_->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//すでに横線があれば十字にする
							else if (field_->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if (field_->map[k][j] == -1) {
						break;
					}
				}

				//左
				for (int k = j - 1; k >= 0; k--) {
					//発電機を探す
					if (field_->map[i][k] < 20 && field_->map[i][k] >= 1) {
						//あればそこまで線を引く
						for (int l = k + 1; l < j; l++) {
							//線の場所が空白なら横線を入れる
							if (field_->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//すでに縦線があれば十字にする
							else if (field_->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if (field_->map[i][k] == -1) {
						break;
					}
				}
				//右
				for (int k = j + 1; k < gridX * panelX; k++) {
					//発電機を探す
					if (field_->map[i][k] < 20 && field_->map[i][k] >= 1) {
						//あればそこまで線を引く
						for (int l = k - 1; l > j; l--) {
							//線の場所が空白なら横線を入れる
							if (field_->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//すでに縦線があれば十字にする
							else if (field_->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if (field_->map[i][k] == -1) {
						break;
					}
				}
			}
		}
	}
}

void Generator::Disconnectgenerator()
{
	for (int i = 0; i < gridY * panelY; i++) {
		for (int j = 0; j < gridX * panelX; j++) {
			if (field_->GetMapNum(j, i) == 20) {
				field_->SetMapNum(j, i, 0);
			}
			if (field_->GetMapNum(j, i) == 21) {
				field_->SetMapNum(j, i, 0);
			}
			if (field_->GetMapNum(j, i) == 22) {
				field_->SetMapNum(j, i, 0);
			}
		}
	}
}
