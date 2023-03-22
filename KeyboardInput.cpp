#include "KeyboardInput.h"
#include "DxLib.h"

KeyboardInput& KeyboardInput::Getinstance()
{
	static KeyboardInput inst;
	return inst;
}

void KeyboardInput::Update()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}

	// 最新のキーボード情報を取得
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
