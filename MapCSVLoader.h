#pragma once
#include <string>

class MapCSVLoader
{
public:
	static MapCSVLoader& GetInstance();

	void LoadCSV(std::string fileName);

};

