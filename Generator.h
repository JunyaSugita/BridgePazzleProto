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


public:
	Field* field_;
	int mouseX, mouseY;
	int mouseMapPointX, mouseMapPointY;

	int haveNum_;
	bool have_;
	int oldHavePosX_, oldHavePosY_;
};