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

	for (size_t i = 0; i < cSize; i++) 
	{
		if (pointSave[i] > 0) {
			scores.emplace_back(nameSave[i], pointSave[i]);
		}
	}
	return scores;
}

void Highscore::write(std::fstream& file)
{
	for (size_t i = 0; i < cSize; i++)
	{
		char nameBuffer[9] = {};
		std::copy_n(nameSave[i].begin(), std::min<size_t>(8, nameSave[i].size()), nameBuffer);
		file.write(nameBuffer, 8);

		file.write(reinterpret_cast<const char*>(&pointSave[i]), sizeof(UINT_32));
	}
}

void Highscore::readStart(std::fstream& file)
{
	for (size_t i = 0; i < cSize; i++)
	{
		char buffer[9] = { '\0' };
		file.read(buffer, 8);
		buffer[8] = '\0';
		nameSave[i] = std::string(buffer);

		file.read(reinterpret_cast<char*>(&pointSave[i]), sizeof(UINT_32));
	}
}

void Highscore::readEnd(std::fstream& file)
{
	for (size_t i = 0; i < cSize; i++)
	{
		char buffer[9] = { '\0' };
		file.read(buffer, 8);
		buffer[8] = '\0';
		nameSave[i] = std::string(buffer);

		file.read(reinterpret_cast<char*>(&pointSave[i]), sizeof(UINT_32));
	}
}

void Highscore::doHighScore(std::string playerIdentity)
{
	std::string stmp = "PLAYER " + playerIdentity;
	std::string shortName = stmp.substr(0, 8);

	// Leer los puntos actuales
	std::fstream readf1("HighScore.bin", std::ios::in | std::ios::binary);
	if (readf1.is_open()) {
		readStart(readf1);
		readf1.close();
	}

	// Buscar si el jugador ya existe y sumarle 1 punto
	bool found = false;
	for (size_t i = 0; i < cSize; i++) {
		if (nameSave[i].substr(0, 8) == shortName) {
			pointSave[i] += 1;
			found = true;
			break;
		}
	}

	// Si no lo encuentra, añadir nuevo jugador en el primer slot vacío
	if (!found) {
		for (size_t i = 0; i < cSize; i++) {
			if (pointSave[i] == 0) {
				nameSave[i] = shortName;
				pointSave[i] = 1;
				found = true;
				break;
			}
		}

		// Si está lleno, reemplaza al peor (último después del ordenamiento)
		if (!found) {
			bubbleSort(); // asegúrate que estén ordenados
			nameSave[cSize - 1] = shortName;
			pointSave[cSize - 1] = 1;
		}
	}

	// Escribir los datos ordenados
	std::fstream writef("HighScore.bin", std::ios::out | std::ios::binary | std::ios::trunc);
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
	for (size_t i = 0; i < cSize; i++)
	{
		if (pointSave[i] > 0) {
			std::cout << nameSave[i].c_str() << " : " << pointSave[i] << std::endl;
		}
	}
}
