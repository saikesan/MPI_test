#pragma once

#include <vector>

class IAlgoritm
{
public:
	IAlgoritm() = default;

	virtual ~IAlgoritm() = default;

	virtual bool Execute(std::vector<std::vector<double>> matrix, std::vector<double>& result) = 0;
};