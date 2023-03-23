#pragma once
#include "DxLib.h"
#include "Field.h"

class Generator {
public:
	Generator();
	~Generator();

public:
	void Initialize(Field* field);
	void Update(Field* field,int mouseX, int mouseY, int mouseMapPointX, int mouseMapPointY, int i, int j);
	void Draw(int mouseX, int mouseY);

	/// <summary>
	/// ���d�@���m���q����
	/// </summary>
	void ConnectGenerator();

	//���������d�@�̔z��������
	void Disconnectgenerator(int mouseMapPointX, int mouseMapPointY);

public:
	Field* field_;
	//int mouseX_, mouseY_;
	//int mouseMapPointX, mouseMapPointY;
	
	int haveNum_;
	bool have_;
	int oldHavePosX_, oldHavePosY_;

	//�X�V�t���O
	bool isUpdate = false;
};