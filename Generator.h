#pragma once
#include "DxLib.h"
#include "Field.h"

class Generator {
public:
	Generator();
	~Generator();

public:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="field">�t�B�[���h�N���X</param>
	void Initialize(Field* field);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="field">�t�B�[���h�N���X</param>
	void Update(Field* field);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���d�@���m���q����
	/// </summary>
	void ConnectGenerator();

	//���������d�@�̔z��������
	void Disconnectgenerator();

public:
	//�t�B�[���hclass�̏��
	Field* field_;
	//�}�E�X���W
	int mouseX, mouseY;
	//�}�b�v�`�b�v��̃}�E�X���W
	int mouseMapPointX, mouseMapPointY;
	//�������Ă��锭�d�@�̐���(�p�~����1�݂̂�)
	int haveNum_[gridY][gridX];
	//���d�@�������Ă��邩�̃t���O
	bool have_;
	//���d�@�̌��̏ꏊ�̋L���p
	int oldHavePosX_, oldHavePosY_;
};