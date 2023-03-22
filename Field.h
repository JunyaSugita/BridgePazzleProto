#pragma once
#include "DxLib.h"
#include "GrovalSetting.h"

class Field
{
public:
	Field();
	~Field();

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
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
	//�}�b�v
	int map[gridY][gridX];
};

