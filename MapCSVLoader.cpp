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
	//�t�@�C���J��
	ifstream file;

	std::string filePath = "Resources/MapCSV/";
	std::string extension = ".csv";

	std::string fileFullPath = filePath + fileName + extension;
	file.open(fileFullPath.c_str());

	assert(file.is_open(), "MapCSV�t�@�C�����J���܂���ł���");

	// 1�s���ǂݍ���
	std::string line;
	while (getline(file, line)) {

		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		getline(line_stream, key, ' ');

		// //����n�܂�s�̓R�����g
		if (key.find("//") == 0)
		{
			continue;
		}

		//�i�[�p
		std::string word;

		if (key == "map")
		{
			//"map"������s
			getline(file, line);
			// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
			std::istringstream line_stream(line);

			getline(line_stream, word, ' ');


		}
	}
}
