#include <mpi.h>
#include <vector>
#include <map>
#include <time.h>

const int rows = 3;
const int columns = 3;

double matrix[columns][rows] =
							{
								{1.0,2.0,1.0},
								{4.0,1.0,4.0},
								{7.0,4.0,9.0}
							};

double matrix1[columns][rows] =
							{
								{1.0,2.0,3.0},
								{4.0,5.0,6.0},
								{7.0,8.0,9.0}
							};

void HarmonicMean(double& result, double* matrix);
void Mode(std::vector<double>& result, double* matrix);



int main(int argc, char** argv)
{
	int thread, thread_size, processor_name_length;
	double cpu_time_start =0, cpu_time_fini =0 ;
	char* processor_name = new char[MPI_MAX_PROCESSOR_NAME * sizeof(char)];
	MPI_Status status = {0};

	// Инициализируем работу MPI
	MPI_Init(&argc, &argv);

	// Получаем имя физического процессора
	MPI_Get_processor_name(processor_name, &processor_name_length);

	// Получаем номер конкретного процесса на котором запущена программа
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);

	// Получаем количество запущенных процессов
	MPI_Comm_size(MPI_COMM_WORLD, &thread_size);
	

	if(thread == 0)
		cpu_time_start = MPI_Wtime();

	double hm = 0;
	std::vector<double> mode;

	HarmonicMean(hm, matrix[thread]);

	printf("Harmonic mean of %d column = %f\n", thread, hm);

	Mode(mode, matrix[thread]);

	printf("Modes of %d column = ", thread);
	for (size_t i = 0; i < mode.size(); i++)
	{
		printf(" %f", mode[i]);
	}
	printf("\n");
	

	if (thread == thread_size - 1)
	{
		cpu_time_fini = MPI_Wtime();
		printf("CPU Time: %lf ms\n", (cpu_time_fini - cpu_time_start) * 1000);
	}

	MPI_Finalize();

	return 0;
}


void HarmonicMean(double& result, double* matrix)
{
	double intermediateResult = 0;

	for (size_t i = 0; i < rows; i++)
	{
		intermediateResult += 1 / matrix[i];
	}

	result = rows / intermediateResult;
}

void Mode(std::vector<double>& result, double* matrix)
{
	std::map<double, int> numericCounter;

	for (size_t i = 0; i < rows; i++)
	{
		if (numericCounter.find(matrix[i]) == numericCounter.end())
		{
			numericCounter.insert(std::make_pair(matrix[i], 1));
		}
		else
		{
			numericCounter[matrix[i]] += 1;
		}
	}

	int maxMode = 0;

	for (auto iter = numericCounter.begin(); iter != numericCounter.end(); iter++)
	{
		if (iter->second > maxMode)
		{
			maxMode = iter->second;
		}
	}

	if (maxMode == 1)
		return;

	for (auto iter = numericCounter.begin(); iter != numericCounter.end(); iter++)
	{
		if (iter->second == maxMode)
		{
			result.push_back(iter->first);
		}
	}
}