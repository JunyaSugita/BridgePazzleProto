#pragma once

class KeyboardInput
{
private:
	char keys[256];
	char oldkeys[256];


private:
	KeyboardInput() { ; }
	~KeyboardInput() { ; }

public:
	static KeyboardInput& Getinstance();

	KeyboardInput& operator=(const KeyboardInput& other) = delete;
	KeyboardInput(const KeyboardInput& other) = delete;

	void Update();
	bool GetKey(const int& key);
	bool GetKeyTrigger(const int& key);
	bool GetKeyReleaced(const int& key);
	int GetHorizontal();
	int GetVertical();
};