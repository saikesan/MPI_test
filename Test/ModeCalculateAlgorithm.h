#pragma once

#include "IAlgorithm.h"

class ModeCalculateAlgorithm : IAlgoritm
{
public:
	ModeCalculateAlgorithm();
	~ModeCalculateAlgorithm();

	virtual bool Execute(std::vector<std::vector<double>> matrix, std::vector<double>& result) override;
};