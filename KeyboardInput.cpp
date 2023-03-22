#include "KeyboardInput.h"
#include "DxLib.h"

KeyboardInput& KeyboardInput::Getinstance()
{
	static KeyboardInput inst;
	return inst;
}

void KeyboardInput::Update()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}

	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

bool KeyboardInput::GetKey(const int& key)
{
	return keys[key];
}

bool KeyboardInput::GetKeyTrigger(const int& key)
{
	return (keys[key] && !oldkeys[key]);
}

bool KeyboardInput::GetKeyReleaced(const int& key)
{
	return (!keys[key] && oldkeys[key]);
}

int KeyboardInput::GetHorizontal()
{
	return (keys[KEY_INPUT_RIGHT] || keys[KEY_INPUT_D]) - (keys[KEY_INPUT_LEFT] || keys[KEY_INPUT_A]);
}

int KeyboardInput::GetVertical()
{
	return (keys[KEY_INPUT_DOWN] || keys[KEY_INPUT_S]) - (keys[KEY_INPUT_UP] || keys[KEY_INPUT_W]);
}
