#include "Generator.h"

Generator::Generator()
{
	//test
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
}

void Generator::Update(Field* field,int mouseX, int mouseY, int mouseMapPointX, int mouseMapPointY,int i,int j)
{
	//フィールド情報取得
	field_ = field;
	

	//マウスが自分の持っているフィールド内にいるかどうか
	if(mouseX > field_->pos.x && mouseX < field_->pos.x + 300 && mouseY > field_->pos.y && mouseY  < field_->pos.y + 300)
	{
		isUpdate = true;	
	}
	else
	{
		isUpdate = false;
	}

	//すでにあるやつをつなぐ
	ConnectGenerator();

	//クリックしている時
	if((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//クリックした瞬間
		if(have_ == false)
		{
			//つかんだ場所を記録
			oldHavePosX_ = mouseMapPointX;
			oldHavePosY_ = mouseMapPointY;

			//持っている数字を記録
			haveNum_ = field_->GetMapNum(mouseMapPointX, mouseMapPointY);

			//動かせる物なら
			if(haveNum_ > 0 && haveNum_ <= 9)
			{
				for(int i = 0; i < field_->ANDO_MAP_CONST; i++)
				{
					if(field_->andoMapActive[i] == false)
					{
						for(int j = 0; j < gridY; j++)
						{
							for(int k = 0; k < gridY; k++)
							{
								field_->andoMap[i][j][k] = field_->map[j][k];
								field_->andoMapActive[i] = true;
							}
						}
						break;
					}
				}
				//持っているフラグを立てる
				have_ = true;
				//マップ情報から持ち上げた情報を削除
				field_->SetMapNum(mouseMapPointX, mouseMapPointY, 0);

				Disconnectgenerator(mouseMapPointX,mouseMapPointY);

			}
		}
	}
	//クリックしていなくて持っているフラグがtrueの時
	//(発電機を置くとき)
	else if(have_ == true)
	{
		//発電機を置く場所が空白の場所では無い時
		if(field_->GetMapNum(mouseMapPointX, mouseMapPointY) != 0)
		{
			for(int i = field_->ANDO_MAP_CONST - 1; i >= 0; i--)
			{
				if(field_->andoMapActive[i] == true)
				{
					field_->andoMapActive[i] = false;
					break;
				}
			}
			//発電機を元の位置に戻す
			field_->SetMapNum(oldHavePosX_, oldHavePosY_, haveNum_);
			//何も持ってないことにする
			haveNum_ = 0;
			//持っているフラグをfalseに
			have_ = false;
		}
		//発電機を置く場所が空白の時
		else
		{

			//クリックをやめた場所に発電機を設置
			field_->SetMapNum(mouseMapPointX, mouseMapPointY, haveNum_);
			//何も持ってないことにする
			haveNum_ = 0;
			//持っているフラグをfalseに
			have_ = false;
		}
	}
}

void Generator::Draw(int mouseX, int mouseY)
{
	/*if (have_ == true) {
		DrawCircle(mouseX ,mouseY, 30, GetColor(255, 255, 255));
		DrawFormatString(mouseX, mouseY, GetColor(0, 0, 0), "%d", haveNum_);
	}
	else
	{
		DrawFormatString(100, 0, GetColor(255, 255, 255), "RIGHT_CLICK : ANDO");
	}*/
}

void Generator::ConnectGenerator()
{
	for(int i = 0; i < gridY; i++)
	{
		for(int j = 0; j < gridX; j++)
		{
			if(field_->map[i][j] > 0 && field_->map[i][j] < 20)
			{
				//繋がり検索
				//上
				for(int k = i - 1; k >= 0; k--)
				{
					//発電機を探す
					if(field_->map[k][j] < 20 && field_->map[k][j] >= 1)
					{
						//あればそこまで線を引く
						for(int l = k + 1; l < i; l++)
						{
							//線の場所が空白なら縦線を入れる
							if(field_->map[l][j] == 0)
							{
								field_->SetMapNum(j, l, 20);
							}
							//すでに横線があれば十字にする
							else if(field_->map[l][j] == 21)
							{
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if(field_->map[k][j] == -1)
					{
						break;
					}
				}
				//下
				for(int k = i + 1; k < gridY; k++)
				{
					//発電機を探す
					if(field_->map[k][j] < 20 && field_->map[k][j] >= 1)
					{
						//あればそこまで線を引く
						for(int l = k - 1; l > i; l--)
						{
							//線の場所が空白なら縦線を入れる
							if(field_->map[l][j] == 0)
							{
								field_->SetMapNum(j, l, 20);
							}
							//すでに横線があれば十字にする
							else if(field_->map[l][j] == 21)
							{
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if(field_->map[k][j] == -1)
					{
						break;
					}
				}

				//左
				for(int k = j - 1; k >= 0; k--)
				{
					//発電機を探す
					if(field_->map[i][k] < 20 && field_->map[i][k] >= 1)
					{
						//あればそこまで線を引く
						for(int l = k + 1; l < j; l++)
						{
							//線の場所が空白なら横線を入れる
							if(field_->map[i][l] == 0)
							{
								field_->SetMapNum(l, i, 21);
							}
							//すでに縦線があれば十字にする
							else if(field_->map[i][l] == 20)
							{
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if(field_->map[i][k] == -1)
					{
						break;
					}
				}
				//右
				for(int k = j + 1; k < gridX; k++)
				{
					//発電機を探す
					if(field_->map[i][k] < 20 && field_->map[i][k] >= 1)
					{
						//あればそこまで線を引く
						for(int l = k - 1; l > j; l--)
						{
							//線の場所が空白なら横線を入れる
							if(field_->map[i][l] == 0)
							{
								field_->SetMapNum(l, i, 21);
							}
							//すでに縦線があれば十字にする
							else if(field_->map[i][l] == 20)
							{
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//壁なら終了
					else if(field_->map[i][k] == -1)
					{
						break;
					}
				}
			}
		}
	}
}

void Generator::Disconnectgenerator(int mouseMapPointX,int mouseMapPointY)
{
	//繋がり検索
	//上
	for(int i = mouseMapPointY - 1; i >= 0; i--)
	{
		//縦線を消す
		if(field_->GetMapNum(mouseMapPointX, i) == 20)
		{
			field_->SetMapNum(mouseMapPointX, i, 0);
		}
		//十字なら横線にする
		else if(field_->GetMapNum(mouseMapPointX, i) == 22)
		{
			field_->SetMapNum(mouseMapPointX, i, 21);
		}
		//線でなければ終了
		else
		{
			break;
		}
	}
	//下
	for(int i = mouseMapPointY + 1; i < gridY; i++)
	{
		//縦線を消す
		if(field_->GetMapNum(mouseMapPointX, i) == 20)
		{
			field_->SetMapNum(mouseMapPointX, i, 0);
		}
		//十字なら横線にする
		else if(field_->GetMapNum(mouseMapPointX, i) == 22)
		{
			field_->SetMapNum(mouseMapPointX, i, 21);
		}
		//線でなければ終了
		else
		{
			break;
		}
	}
	//左
	for(int i = mouseMapPointX - 1; i >= 0; i--)
	{
		//横線を消す
		if(field_->GetMapNum(i, mouseMapPointY) == 21)
		{
			field_->SetMapNum(i, mouseMapPointY, 0);
		}
		//十字なら縦線にする
		else if(field_->GetMapNum(i, mouseMapPointY) == 22)
		{
			field_->SetMapNum(i, mouseMapPointY, 20);
		}
		//線でなければ終了
		else
		{
			break;
		}
	}
	//下
	for(int i = mouseMapPointX + 1; i < gridY; i++)
	{
		//横線を消す
		if(field_->GetMapNum(i, mouseMapPointY) == 21)
		{
			field_->SetMapNum(i, mouseMapPointY, 0);
		}
		//十字なら縦線にする
		else if(field_->GetMapNum(i, mouseMapPointY) == 22)
		{
			field_->SetMapNum(i, mouseMapPointY, 20);
		}
		//線でなければ終了
		else
		{
			break;
		}
	}
}
