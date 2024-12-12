#include "model.h"
#include <iostream>

Model::Model(uint32_t cashboxesQnty, double handlingTime, uint32_t newCustomerAvgTime, double totalTime)
    : cashboxesQnty(cashboxesQnty), handlingTime(handlingTime), newCustomerAvgTime(newCustomerAvgTime), totalTime(totalTime), unhandledCustomers(0)
{
	for (int i = 0; i < cashboxesQnty; i++)
	{
		cashboxes.push_back(0);
		cashboxesTime.push_back(0);
	}

	std::random_device rd;
	gen.seed(rd());
	dist = std::uniform_real_distribution<>(0.0, 1.0);
}

double Model::generateNextCustomerTime()
{
	return (-1 * std::log(dist(gen))) / newCustomerAvgTime;
}

void Model::calculate()
{
	double accumulativeTime = 0;
	uint32_t allBusy = true;
	/*std::cout << totalTime << " total before cycle \n";
	std::cout << accumulativeTime << " accum before cycle \n";*/

	while ((accumulativeTime += generateNextCustomerTime()) <= totalTime)
	{
		for (int i = 0; i < cashboxesQnty; i++)
		{
			if (cashboxesTime[i] <= accumulativeTime)
			{
				cashboxes[i]++;
				cashboxesTime[i] = accumulativeTime + handlingTime;
				allBusy = false;
			}
		}
		/*std::cout << accumulativeTime << " accum in cycle \n";*/
		if (allBusy)
			unhandledCustomers++;
	}
}

void Model::clearResults()
{
	cashboxes = std::vector<uint32_t>(cashboxesQnty, 0);
	cashboxesTime = std::vector<double>(cashboxesQnty, 0);
}

uint32_t Model::getUnhandledCustomers()
{
	return unhandledCustomers;
}
std::vector<uint32_t> Model::getCashboxes()
{
	return cashboxes;
}
