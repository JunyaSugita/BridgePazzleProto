#include "Generator.h"

Generator::Generator()
{
}

Generator::~Generator()
{
}

void Generator::Initialize(Field* field)
{
	field_ = field;
	have_ = false;
	haveNum_ = 0;
}

void Generator::Update(Field* field)
{
	field_ = field;
	GetMousePoint(&mouseX, &mouseY);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (have_ == false) {
			haveNum_ = field_->GetMapNum(mouseX, mouseY);
			have_ = true;
		}
	}
	else if(have_ == true){
		field_->SetMapNum(mouseX,mouseY,haveNum_);
		haveNum_ = 0;
		have_ = false;
	}
}

void Generator::Draw()
{
	if (have_ == true) {
		DrawCircle(mouseX ,mouseY, 50, GetColor(255, 255, 255));
		DrawFormatString(mouseX, mouseY, GetColor(0, 0, 0), "%d", haveNum_);
	}
}
