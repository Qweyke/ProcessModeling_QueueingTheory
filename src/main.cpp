#include "model.h"
#include <iostream>

double calculateDensity(uint32_t timeForCustomerToAppear)
{
	return static_cast<double>(1) / static_cast<double>(timeForCustomerToAppear);
}

void simulateWork(uint32_t cashboxes, double handlingTime, uint32_t timeForCustomerToAppear, uint32_t totalTime, std::string name, uint32_t experienceQnty)
{
	uint32_t unhandledSum = 0;
	std::vector<uint32_t> modelCashBoxesSum(cashboxes, 0);

	for (int i = 0; i < experienceQnty; i++)
	{
		Model model(cashboxes, handlingTime, calculateDensity(timeForCustomerToAppear), totalTime);
		model.calculate();
		unhandledSum += model.getUnhandledCustomers();
		std::vector<uint32_t> modelCashboxes = model.getCashboxes();
		for (int j = 0; j < modelCashboxes.size(); j++)
		{
			modelCashBoxesSum[j] += modelCashboxes[j];
		}
	}
	std::cout << name << " unhandled customers: " << (1.0 / experienceQnty * unhandledSum) << "\n";
	std::cout << name << " cashboxes statistics: "
	          << "\n";
	for (int i = 0; i < cashboxes; i++)
	{
		std::cout << i + 1 << ". point: " << (1.0 / experienceQnty * modelCashBoxesSum[i]) << "\n";
	}
	std::cout << "\n";
}

int main()
{
	constexpr uint32_t EXPERIENCE_QNTY = 1000;

	simulateWork(10, 2.0, 1.8, 720, "Supermarket checkout", EXPERIENCE_QNTY);
	simulateWork(5, 1.2, 2, 480, "Fast food restaurant", EXPERIENCE_QNTY);
	simulateWork(8, 3.0, 2.5, 720, "Airport check-in desks", EXPERIENCE_QNTY);
	simulateWork(2, 5.0, 4.0, 540, "Hospital reception", EXPERIENCE_QNTY);
	simulateWork(4, 30.0, 25.0, 600, "Car service station", EXPERIENCE_QNTY);
}