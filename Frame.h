#pragma once
#include "Field.h"
#include <memory>
#include <vector>
#include "Vector2.h"

class Frame
{
private:
	//��g�̏c�Ɖ��̐��i���j
	int fieldFrameWidth = 3;
	int fieldFrameHeight = 3;
	//��g�̑���
	int fieldFrameNum = fieldFrameWidth * fieldFrameHeight;

	/*static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;
	static const int layerFrameNum = layerFrameWidth * layerFrameHeight;*/

public:

	//�f�X�g���N�^
	~Frame();
	//������
	void Initialize();
	//�X�V
	void Update(char* keys, char* oldkeys, int mouseX, int mouseY, int oldMouseX, int oldMouseY);
	//�`��
	void Draw();

	//�t�B�[���h�̒��g���Z�b�g����֐�
	
	//

	

public:

	void SetFreamLayerNum();
	bool GetisSelect();

private:

	//�t���[���̒��̃t�B�[���h�̔z��
	std::vector<std::vector<std::unique_ptr <Field>>> field_;

public: //�Q�b�^�[

	const int GetFieldFrameWidth() { return fieldFrameWidth; }
	const int GetFieldFrameHeight() { return fieldFrameHeight; }
	const int GetFieldFrameNum() { return fieldFrameNum; }


};

