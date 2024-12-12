#include "model.h"
#include <iostream>

Model::Model(uint32_t cashboxesQnty, double handlingTime, double customerPerTime, uint32_t totalTime)
    : cashboxesQnty(cashboxesQnty), handlingTime(handlingTime), customerPerTime(customerPerTime), totalTime(totalTime), unhandledCustomers(0)
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
	double time = -1.0 / static_cast<double>(customerPerTime) * std::log(dist(gen));
	return time;
}

void Model::calculate()
{
	double accumulativeTime = 0;
	uint32_t allBusy = true;

	while ((accumulativeTime += generateNextCustomerTime()) <= totalTime)
	{
		for (int i = 0; i < cashboxesQnty; i++)
		{
			if (cashboxesTime[i] <= accumulativeTime)
			{
				cashboxes[i]++;
				cashboxesTime[i] = accumulativeTime + handlingTime;
				allBusy = false;
				break;
			}
		}
		if (allBusy)
			unhandledCustomers++;
		allBusy = true;
	}
}

uint32_t Model::getUnhandledCustomers()
{
	return unhandledCustomers;
}
std::vector<uint32_t> Model::getCashboxes()
{
	return cashboxes;
}
