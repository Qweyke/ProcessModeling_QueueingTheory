#include "model.h"

Model::Model(uint32_t cashboxesQnty, uint32_t handlingTime, uint32_t newCustomerAvgTime, uint32_t totalTime)
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
	uint32_t accumulativeTime = 0;
	uint32_t allBusy = true;

	while (accumulativeTime <= totalTime)
	{
		accumulativeTime += generateNextCustomerTime();
		for (int i = 0; i < cashboxesQnty; i++)
		{
			if (cashboxesTime[i] <= accumulativeTime)
			{
				cashboxes[i]++;
				cashboxesTime[i] = accumulativeTime + handlingTime;
				allBusy = false;
			}
		}
		if (allBusy)
			unhandledCustomers++;
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
