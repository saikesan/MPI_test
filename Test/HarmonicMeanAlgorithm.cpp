#include "HarmonicMeanAlgorithm.h"
#include <exception>



HarmonicMeanAlgorithm::HarmonicMeanAlgorithm() : IAlgoritm()
{

}

HarmonicMeanAlgorithm::~HarmonicMeanAlgorithm()
{

}

bool HarmonicMeanAlgorithm::Execute(std::vector<std::vector<double>> matrix, std::vector<double>& result)
{
	try
	{
		for (size_t column = 0; column < matrix.size(); column++)
		{
			double intermediateResult = 0;

			for (size_t row = 0; row < matrix[column].size(); row++)
			{
				intermediateResult += 1 / matrix[column][row];
			}

			result.push_back(static_cast<double>(matrix[column].size()) / intermediateResult);
		}
	}
	catch (std::exception ex)
	{
		return false;
	}
	
	return true;
}