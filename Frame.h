#pragma once
#include "Field.h"
#include <memory>
#include <vector>
#include "Vector2.h"
#include "GrovalSetting.h"
#include "Generator.h"

class Frame
{
private:
	//��g�̏c�Ɖ��̐��i���j
	int fieldFrameWidth = 3;
	int fieldFrameHeight = 3;
	//��g�̑���
	int fieldFrameNum = fieldFrameWidth * fieldFrameHeight;

	//�g�̉��̍ő吔
	static const int MaxFrameX = 3;
	//�g�̏c�̍ő吔
	static const int MaxFrameY = 3;


	/*static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;
	static const int layerFrameNum = layerFrameWidth * layerFrameHeight;*/

public:

	//�f�X�g���N�^
	~Frame();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	//�t�B�[���h�̒��g���Z�b�g����֐�

public:

	void SetFreamLayerNum();
	bool GetisSelect();

private:

	//�t���[���̒��̃t�B�[���h�̔z��
	std::vector<std::vector<std::unique_ptr <Field>>> fields_;
	std::vector<std::unique_ptr <Field>> fieldInTheFrame[MaxFrameY][MaxFrameX] = {};

	std::vector<std::vector<std::unique_ptr <Generator>>> generators_;
	//std::vector<std::unique_ptr <Generator>> fieldInTheFrame[MaxFrameY][MaxFrameX] = {};


	Generator* generator_;

	int mouseX, mouseY;
	


public: //�Q�b�^�[

	const int GetFieldFrameWidth() { return fieldFrameWidth; }
	const int GetFieldFrameHeight() { return fieldFrameHeight; }
	const int GetFieldFrameNum() { return fieldFrameNum; }


};

