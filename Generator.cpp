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
	haveNum_ = 0;

	//すでにあるやつをつなぐ
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			if (field_->map[i][j] > 0 && field_->map[i][j] < 20) {
				//繋がり検索
				//上
				for (int k = i - 1; k >= 0; k--) {
					if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
						for (int l = k + 1; l < i; l++) {
							field_->SetMapNum(j, l, 20);
						}
						break;
					}
					else if (field->map[k][j] != 0) {
						break;
					}
				}
				//下
				for (int k = i + 1; k < gridY; k++) {
					if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
						for (int l = k - 1; l > i; l--) {
							field_->SetMapNum(j, l, 20);
						}
						break;
					}
					else if (field->map[k][j] != 0) {
						break;
					}
				}

				//左
				for (int k = j - 1; k >= 0; k--) {
					if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
						for (int l = k + 1; l < j; l++) {
							field_->SetMapNum(l, i, 21);
						}
						break;
					}
					else if (field->map[i][k] != 0) {
						break;
					}
				}
				//右
				for (int k = j + 1; k < gridX; k++) {
					if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
						for (int l = k - 1; l > j; l--) {
							field_->SetMapNum(l, i, 21);
						}
						break;
					}
					else if (field->map[i][k] != 0) {
						break;
					}
				}
			}
		}
	}
}

void Generator::Update(Field* field,int mouseX, int mouseY, int mouseMapPointX, int mouseMapPointY,int i,int j)
{
	//フィールド情報取得
	field_ = field;

	if(mouseX > field_->pos.x && mouseX < field_->pos.x + 300 && mouseY > field_->pos.y && mouseY  < field_->pos.y + 300)
	{
		isUpdate = true;	
	}
	else
	{
		isUpdate = false;
	}
	
	if(isUpdate == true)
	{
		//ショートしている場所の線を消す
		for(int i = 0; i < gridY; i++)
		{
			for(int j = 0; j < gridX; j++)
			{
				if(field_->shortMap[i][j] == true)
				{
					//繋がり検索
					//上
					for(int k = i - 1; k >= 0; k--)
					{
						if(field_->GetMapNum(j, k) == 20)
						{
							field_->SetMapNum(j, k, 0);
						}
						else
						{
							break;
						}
					}
					//下
					for(int k = i + 1; k < gridY; k++)
					{
						if(field_->GetMapNum(j, k) == 20)
						{
							field_->SetMapNum(j, k, 0);
						}
						else
						{
							break;
						}
					}
					//左
					for(int k = j - 1; k >= 0; k--)
					{
						if(field_->GetMapNum(k, i) == 21)
						{
							field_->SetMapNum(k, i, 0);
						}
						else
						{
							break;
						}
					}
					//下
					for(int k = j + 1; k < gridY; k++)
					{
						if(field_->GetMapNum(k, i) == 21)
						{
							field_->SetMapNum(k, i, 0);
						}
						else
						{
							break;
						}
					}
				}
			}
		}

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
					//持っているフラグを立てる
					have_ = true;
					//マップ情報から持ち上げた情報を削除
					field_->SetMapNum(mouseMapPointX, mouseMapPointY, 0);

					//繋がり検索
					//上
					for(int i = mouseMapPointY - 1; i >= 0; i--)
					{
						if(field_->GetMapNum(mouseMapPointX, i) == 20)
						{
							field_->SetMapNum(mouseMapPointX, i, 0);
						}
						else
						{
							break;
						}
					}
					//下
					for(int i = mouseMapPointY + 1; i < gridY; i++)
					{
						if(field_->GetMapNum(mouseMapPointX, i) == 20)
						{
							field_->SetMapNum(mouseMapPointX, i, 0);
						}
						else
						{
							break;
						}
					}
					//左
					for(int i = mouseMapPointX - 1; i >= 0; i--)
					{
						if(field_->GetMapNum(i, mouseMapPointY) == 21)
						{
							field_->SetMapNum(i, mouseMapPointY, 0);
						}
						else
						{
							break;
						}
					}
					//下
					for(int i = mouseMapPointX + 1; i < gridY; i++)
					{
						if(field_->GetMapNum(i, mouseMapPointY) == 21)
						{
							field_->SetMapNum(i, mouseMapPointY, 0);
						}
						else
						{
							break;
						}
					}

					//すでにあるやつをつなぐ
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
									if(field->map[k][j] < 20 && field->map[k][j] >= 1)
									{
										for(int l = k + 1; l < i; l++)
										{
											field_->SetMapNum(j, l, 20);
										}
										break;
									}
									else if(field->map[k][j] != 0)
									{
										break;
									}
								}
								//下
								for(int k = i + 1; k < gridY; k++)
								{
									if(field->map[k][j] < 20 && field->map[k][j] >= 1)
									{
										for(int l = k - 1; l > i; l--)
										{
											field_->SetMapNum(j, l, 20);
										}
										break;
									}
									else if(field->map[k][j] != 0)
									{
										break;
									}
								}

								//左
								for(int k = j - 1; k >= 0; k--)
								{
									if(field->map[i][k] < 20 && field->map[i][k] >= 1)
									{
										for(int l = k + 1; l < j; l++)
										{
											field_->SetMapNum(l, i, 21);
										}
										break;
									}
									else if(field->map[i][k] != 0)
									{
										break;
									}
								}
								//右
								for(int k = j + 1; k < gridX; k++)
								{
									if(field->map[i][k] < 20 && field->map[i][k] >= 1)
									{
										for(int l = k - 1; l > j; l--)
										{
											field_->SetMapNum(l, i, 21);
										}
										break;
									}
									else if(field->map[i][k] != 0)
									{
										break;
									}
								}
							}
						}
					}

				}
			}
		}
		else if(have_ == true)
		{
			if(field_->GetMapNum(mouseMapPointX, mouseMapPointY) != 0)
			{
				field_->SetMapNum(oldHavePosX_, oldHavePosY_, haveNum_);
				haveNum_ = 0;
				have_ = false;

				//繋がり検索
				//上
				for(int i = oldHavePosY_ - 1; i >= 0; i--)
				{
					if(field->map[i][oldHavePosX_] < 20 && field->map[i][oldHavePosX_] >= 1)
					{
						for(int j = i + 1; j < oldHavePosY_; j++)
						{
							field_->SetMapNum(oldHavePosX_, j, 20);
						}
						break;
					}
					else if(field->map[i][oldHavePosX_] != 0)
					{
						break;
					}
				}
				//下
				for(int i = oldHavePosY_ + 1; i < gridY; i++)
				{
					if(field->map[i][oldHavePosX_] < 20 && field->map[i][oldHavePosX_] >= 1)
					{
						for(int j = i - 1; j > oldHavePosY_; j--)
						{
							field_->SetMapNum(oldHavePosX_, j, 20);
						}
						break;
					}
					else if(field->map[i][oldHavePosX_] != 0)
					{
						break;
					}
				}

				//左
				for(int i = oldHavePosX_ - 1; i >= 0; i--)
				{
					if(field->map[oldHavePosY_][i] < 20 && field->map[oldHavePosY_][i] >= 1)
					{
						for(int j = i + 1; j < oldHavePosX_; j++)
						{
							field_->SetMapNum(j, oldHavePosY_, 21);
						}
						break;
					}
					else if(field->map[oldHavePosY_][i] != 0)
					{
						break;
					}
				}
				//右
				for(int i = oldHavePosX_ + 1; i < gridX; i++)
				{
					if(field->map[oldHavePosY_][i] < 20 && field->map[oldHavePosY_][i] >= 1)
					{
						for(int j = i - 1; j > oldHavePosX_; j--)
						{
							field_->SetMapNum(j, oldHavePosY_, 21);
						}
						break;
					}
					else if(field->map[oldHavePosY_][i] != 0)
					{
						break;
					}
				}
			}
			else
			{
				field_->SetMapNum(mouseMapPointX, mouseMapPointY, haveNum_);
				haveNum_ = 0;
				have_ = false;

				//繋がり検索
				//上
				for(int i = mouseMapPointY - 1; i >= 0; i--)
				{
					if(field->map[i][mouseMapPointX] < 20 && field->map[i][mouseMapPointX] >= 1)
					{
						for(int j = i + 1; j < mouseMapPointY; j++)
						{
							field_->SetMapNum(mouseMapPointX, j, 20);
						}
						break;
					}
					else if(field->map[i][mouseMapPointX] != 0)
					{
						break;
					}
				}
				//下
				for(int i = mouseMapPointY + 1; i < gridY; i++)
				{
					if(field->map[i][mouseMapPointX] < 20 && field->map[i][mouseMapPointX] >= 1)
					{
						for(int j = i - 1; j > mouseMapPointY; j--)
						{
							field_->SetMapNum(mouseMapPointX, j, 20);
						}
						break;
					}
					else if(field->map[i][mouseMapPointX] != 0)
					{
						break;
					}
				}

				//左
				for(int i = mouseMapPointX - 1; i >= 0; i--)
				{
					if(field->map[mouseMapPointY][i] < 20 && field->map[mouseMapPointY][i] >= 1)
					{
						for(int j = i + 1; j < mouseMapPointX; j++)
						{
							field_->SetMapNum(j, mouseMapPointY, 21);
						}
						break;
					}
					else if(field->map[mouseMapPointY][i] != 0)
					{
						break;
					}
				}
				//右
				for(int i = mouseMapPointX + 1; i < gridX; i++)
				{
					if(field->map[mouseMapPointY][i] < 20 && field->map[mouseMapPointY][i] >= 1)
					{
						for(int j = i - 1; j > mouseMapPointX; j--)
						{
							field_->SetMapNum(j, mouseMapPointY, 21);
						}
						break;
					}
					else if(field->map[mouseMapPointY][i] != 0)
					{
						break;
					}
				}
			}
		}
	}
}

void Generator::Draw(int mouseX, int mouseY)
{
	if (have_ == true) {
		DrawCircle(mouseX_ ,mouseY_, 30, GetColor(255, 255, 255));
		DrawFormatString(mouseX_, mouseY_, GetColor(0, 0, 0), "%d", haveNum_);
	}
}
