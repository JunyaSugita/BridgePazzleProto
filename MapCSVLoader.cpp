#include "MapCSVLoader.h"
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include "GrovalSetting.h"

using namespace std;

MapCSVLoader& MapCSVLoader::GetInstance()
{
	static MapCSVLoader instance;
	return instance;
}

void MapCSVLoader::LoadCSV(string fileName)
{
	//ファイル開く
	ifstream file;

	std::string filePath = "Resources/MapCSV/";
	std::string extension = ".csv";

	std::string fileFullPath = filePath + fileName + extension;
	file.open(fileFullPath.c_str());

	assert(file.is_open(), "MapCSVファイルが開けませんでした");

	// 1行ずつ読み込む
	std::string line;
	while (getline(file, line)) {

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スペース区切りで行の先頭文字列を取得
		std::string key;
		getline(line_stream, key, ' ');

		// //から始まる行はコメント
		if (key.find("//") == 0)
		{
			continue;
		}

		//格納用
		std::string word;

		if (key == "map")
		{
			//"map"から改行
			getline(file, line);
			// 1行分の文字列をストリームに変換して解析しやすくする
			std::istringstream line_stream(line);

			getline(line_stream, word, ' ');


		}
	}
}
