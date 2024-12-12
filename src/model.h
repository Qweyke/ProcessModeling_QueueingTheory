#pragma once
#include <cstdint>
#include <random>
#include <vector>

class Model
{
  public:
	Model(uint32_t cashboxesQnty, double handlingTime, double customerPerTime, uint32_t totalTime);
	void calculate();
	void clearResults();
	uint32_t getUnhandledCustomers();
	std::vector<uint32_t> getCashboxes();

  private:
	const uint32_t cashboxesQnty;
	const double handlingTime;
	const double customerPerTime;
	const uint32_t totalTime;

	uint32_t unhandledCustomers;

	std::vector<uint32_t> cashboxes;
	std::vector<double> cashboxesTime;

	std::mt19937 gen;
	std::uniform_real_distribution<> dist;

	double generateNextCustomerTime();
};
