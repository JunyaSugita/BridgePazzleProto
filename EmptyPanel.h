#pragma once
#include "DxLib.h"
#include "GrovalSetting.h"

//��̃p�l��
class EmptyPanel
{
public:
	EmptyPanel();
	~EmptyPanel();

public:
	void Initialize();
	void Update();
	void Draw();

	/// <summary>
	/// �w����W�̃}�b�v�`�b�v�ԍ��̎擾
	/// </summary>
	/// <param name="x">�w����W</param>
	/// <param name="y">�w����W</param>
	/// <returns>�}�b�v�`�b�v�ԍ�</returns>
	int GetMapNum(int x, int y);

	/// <summary>
	/// �w����W�Ƀ}�b�v�`�b�v�ԍ����Z�b�g
	/// </summary>
	/// <param name="x">�w����W</param>
	/// <param name="y">�w����W</param>
	/// <param name="num">�Z�b�g�������}�b�v�`�b�v�ԍ�</param>
	void SetMapNum(int x, int y, int num);

public:
	int map[gridY][gridX];
	bool shortMap[gridY][gridX];
	
	//�g�̒��Ŏg�����W
	Vector2 pos;
};


