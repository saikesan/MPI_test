#pragma once

#include "IAlgorithm.h"

class HarmonicMeanAlgorithm : IAlgoritm
{
public:
	HarmonicMeanAlgorithm();
	~HarmonicMeanAlgorithm();

	virtual bool Execute(std::vector<std::vector<double>> matrix, std::vector<double>& result) override;
};