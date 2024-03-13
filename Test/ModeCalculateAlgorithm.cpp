#include "ModeCalculateAlgorithm.h"
#include <exception>
#include <Windows.h>
#include <map>



ModeCalculateAlgorithm::ModeCalculateAlgorithm() : IAlgoritm()
{

}

ModeCalculateAlgorithm::~ModeCalculateAlgorithm()
{

}

bool ModeCalculateAlgorithm::Execute(std::vector<std::vector<double>> matrix, std::vector<double>& result)
{
	std::vector<std::map<double, int>> intermediateResult;
	std::map<double, int> numericCounter;

	try
	{
		// Цикл заполения вектора содержащего словари, каждый из которых
		// содержит пары число - кол-во встреченных раз в отдельном столбце.
		for (size_t column = 0; column < matrix.size(); column++)
		{
			std::map<double, int> columnModes;

			for (size_t row = 0; row < matrix[column].size(); row++)
			{
				if (columnModes.find(matrix[column][row]) == columnModes.end())
				{
					columnModes.insert(std::make_pair(matrix[column][row], 1));
				}
				else
				{
					columnModes[matrix[column][row]] += 1;
				}
			}

			intermediateResult.push_back(columnModes);
		}

		// Цикл заполения словаря, содержащего пары число - кол-во встреченных раз во всей матрице.
		for (size_t mapNumber = 0; mapNumber < intermediateResult.size(); mapNumber++)
		{
			for (auto mapIterator = intermediateResult[mapNumber].begin(); mapIterator != intermediateResult[mapNumber].end(); mapIterator++)
			{
				if (numericCounter.find(intermediateResult[mapNumber][mapIterator->first]) == numericCounter.end())
				{
					numericCounter.insert(std::make_pair(mapIterator->first, mapIterator->second));
				}
				else
				{
					numericCounter[mapIterator->first] += mapIterator->second;
				}
			}
		}

		intermediateResult.clear();

		int maxMode = 0;

		for (auto iter = numericCounter.begin(); iter != numericCounter.end(); iter++)
		{
			if (iter->second > maxMode)
			{
				maxMode = iter->second;
			}
		}

		if (maxMode == 1)
			return true;

		for (auto iter = numericCounter.begin(); iter != numericCounter.end(); iter++)
		{
			if (iter->second == maxMode)
			{
				result.push_back(iter->first);
			}
		}
	}
	catch (std::exception ex)
	{
		return false;
	}

	return true;
}