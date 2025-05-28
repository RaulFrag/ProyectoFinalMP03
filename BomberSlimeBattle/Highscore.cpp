#include "Highscore.h"
#include <cstring>

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

	for (int i = 0; i < cSize - 1; ++i)
	{
		for (int j = 0; j < cSize - i - 1; ++j)
		{
			if (pointSave[j] < pointSave[j + 1])
			{
				std::swap(pointSave[j], pointSave[j + 1]);
				std::swap(nameSave[j], nameSave[j + 1]);
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

std::vector<std::pair<std::string, UINT_32>> Highscore::getScores()
{
	std::vector<std::pair<std::string, UINT_32>> scores;

	for (size_t i = 0; i < cSize - 1; i++) {
		if (pointSave[i] > 0) {
			scores.emplace_back(nameSave[i], pointSave[i]);
		}
	}
	return scores;
}

void Highscore::write(std::fstream& file)
{
	bubbleSort();

	for (size_t i = 0; i < cSize - 1; i++)
	{
		if (pointSave[i] > 0)
		{
			char nameBuffer[9] = { '\0' };
			strncpy_s(nameBuffer, sizeof(nameBuffer), nameSave[i].c_str(), _TRUNCATE);
			file.write(nameBuffer, 8);
			file.write(reinterpret_cast<const char*>(&pointSave[i]), sizeof(UINT_32));
		}
	}
}

void Highscore::readStart(std::fstream& file)
{
	for (size_t i = 1; i < cSize; i++)
	{
		char buffer[9] = { '\0' };
		file.read(buffer, 8);
		nameSave[i] = std::string(buffer);
		file.read(reinterpret_cast<char*>(&pointSave[i]), sizeof(UINT_32));
	}
}

void Highscore::readEnd(std::fstream& file)
{
    for (size_t i = 0; i < cSize - 1; i++)
    {
        char buffer[9] = { '\0' };
        file.read(buffer, 8);
        nameSave[i] = std::string(buffer);
        file.read(reinterpret_cast<char*>(&pointSave[i]), sizeof(UINT_32));
    }
}

void Highscore::doHighScore(std::string playerIdentity)
{
	std::string stmp = "PLAYER " + playerIdentity;

	// Leer los puntos actuales
	std::fstream readf1("HighScore.bin", std::ios::in | std::ios::binary);
	if (readf1.is_open()) {
		readStart(readf1);
		readf1.close();
	}

	// Buscar si el jugador ya existe y le suma 1 punto
	bool found = false;
	for (size_t i = 0; i < cSize; i++) {
		if (nameSave[i] == stmp) {
			pointSave[i] += 1;
			found = true;
			break;
		}
	}

	// Si no lo encontra, lo agrega en la posición 0
	if (!found) {
		SetName(stmp);
		SetP(1);
		nameSave[0] = name;
		pointSave[0] = point;
	}

	// Escribir los datos ordenados
	std::fstream writef("HighScore.bin", std::ios::out | std::ios::binary);
	if (writef.is_open()) {
		bubbleSort();
		write(writef);
		writef.close();
	}
}

// Esto muestra el HighScore por consola
void Highscore::showHighScore()
{
	// Leer para mostrar resultados
	std::fstream readf2("HighScore.bin", std::ios::in | std::ios::binary);
	if (readf2.is_open()) {
		readEnd(readf2);
		readf2.close();
	}

	// Mostrar puntos
	for (size_t i = 0; i < cSize - 1; i++) {
		if (pointSave[i] > 0) {
			std::cout << nameSave[i].c_str() << " : " << pointSave[i] << std::endl;
		}
	}
}
