#include "Highscore.h"

void Highscore::SetP(UINT_32 put)
{
	point = put;
}

void Highscore::SetName(std::string nam)
{
	name = nam;
}

void Highscore::bubbleSort()
{
	nameSave[0] = name;
	pointSave[0] = point;

	// se peta las cosas que modifica
	for (int i = 0; i < cSize - 1; ++i)
	{
		for (int j = 0; j < cSize - i - 1; ++j)
		{
			if (pointSave[j] < pointSave[j + 1])
			{
				int tmp = pointSave[j];
				std::string stmp = nameSave[j];

				pointSave[j] = pointSave[j + 1];
				nameSave[j] = nameSave[j + 1];

				pointSave[j + 1] = tmp;
				nameSave[j + 1] = stmp;
			}
		}
	}
}

Highscore::Highscore()
{
	name = "";
	point = 0;
	for (size_t i = 0; i < cSize; i++)
	{
		nameSave[i] = "";
		pointSave[i] = 0;
	}
}

Highscore::~Highscore()
{
}

void Highscore::write(std::fstream& file)
{
	bubbleSort();

	for (size_t i = 0; i < cSize - 1; i++)
	{
		if (pointSave[i] > 0)
		{
			std::string na = nameSave[i].c_str();
			int val = na.size();
			file.write(nameSave[i].c_str(), val);
			for (size_t j = val; j < 5; j++)
			{
				file.write("\0", 1);
			}
			file.write(reinterpret_cast<const char*>(&pointSave[i]), sizeof(UINT_32));
		}
	}
}

void Highscore::readStart(std::fstream& file)
{
	for (size_t i = 1; i < cSize; i++)
	{
		file.read(nameSave[i].data(), 5);
		file.read(reinterpret_cast<char*>(&pointSave[i]), sizeof(UINT_32));
	}
}

void Highscore::readEnd(std::fstream& file)
{
	for (size_t i = 0; i < cSize - 1; i++)
	{
		file.read(nameSave[i].data(), 5);
		file.read(reinterpret_cast<char*>(&pointSave[i]), sizeof(UINT_32));
	}
}

void Highscore::doHighScore()
{
	std::string stmp;
	int itmp;

	do
	{
		std::cout << "Insert name" << std::endl;
		std::cin >> stmp;
		if (stmp.length() > 5)
		{
			std::cout << "Name too long. Max 5 characters" << std::endl;
		}
	} while (stmp.length() > 5);
	SetName(stmp);

	std::cout << "Insert points" << std::endl;
	std::cin >> itmp;
	SetP(itmp);

	std::fstream readf1("HighScore.bin", std::ios::in | std::ios::binary);
	if (readf1.is_open())
	{
		readStart(readf1);
		readf1.close();
	}

	std::fstream writef("HighScore.bin", std::ios::out | std::ios::binary);
	write(writef);
	writef.close();

	std::fstream readf2("HighScore.bin", std::ios::in | std::ios::binary);
	readEnd(readf2);
	readf2.close();

	for (size_t i = 0; i < cSize - 1; i++)
	{
		if (pointSave[i] > 0)
		{
			std::cout << nameSave[i].c_str() << " : " << pointSave[i] << std::endl;
		}
	}
}
