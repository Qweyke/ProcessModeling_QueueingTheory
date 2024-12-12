#pragma once
#include <cstdint>
#include <random>
#include <vector>

class Model
{
  public:
	Model(uint32_t cashboxesQnty, uint32_t handlingTime, uint32_t newCustomerAvgTime, uint32_t totalTime);
	void calculate();
	uint32_t getUnhandledCustomers();
	std::vector<uint32_t> getCashboxes();

  private:
	const uint32_t cashboxesQnty;
	const uint32_t handlingTime;
	const uint32_t newCustomerAvgTime;
	const uint32_t totalTime;

	uint32_t unhandledCustomers;

	std::vector<uint32_t> cashboxes;
	std::vector<uint32_t> cashboxesTime;

	std::mt19937 gen;
	std::uniform_real_distribution<> dist;

	double generateNextCustomerTime();
};
