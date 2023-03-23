#pragma once
#include "DxLib.h"
#include "GrovalSetting.h"

//�i�ޕ����p
enum MoveDirection
{
	NONE,//�i�܂Ȃ�
	LEFT,//��
	UP,//��
	RIGHT,//�E
	DOWN,//��
};


class Field
{
public:
	Field();
	~Field();

public:
	void Initialize();
	void Update();
	void Draw(int wide, int height);

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

	//�i�߂�ꏊ���Ԃ�
	static bool CanMoveGrid(int y, int x, int moveDirection);
	//player���u���b�N�Ƃ������p
	static bool PullBlock(int y, int x, int moveDirection);
	//�����邩�ǂ��������i�ړ�������͂��Ȃ��j
	static bool GetPullBlock(int y, int x, int moveDirection);

	/// <summary>
	/// �t�B�[���h�̍��W���Z�b�g����
	/// </summary>
	void SetPos(int x, int y);

public:
	int map[gridY][gridX];
	bool shortMap[gridY][gridX];

	//�A���h�D�p
	static const int ANDO_MAP_CONST = 50;
	int andoMap[ANDO_MAP_CONST][gridY][gridX];
	bool andoMapActive[ANDO_MAP_CONST];
	bool isAndo;

	//�O���b�h�̒���
	static const int gridLength = 100;

	//�g���ł̍��W
	Vector2 pos;
};

