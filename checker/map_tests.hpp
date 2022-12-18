#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP

#include <iostream>
#include <iomanip> 
#include <sys/time.h>

#include <map>
#include "checker.hpp"
#include "../map.hpp"

bool compare_maps(ft::map<int, int> &lhs, std::map<int, int> &rhs)
{
	ft::map<int, int>::iterator fit = lhs.begin();
	std::map<int, int>::iterator sit = rhs.begin();

	for (; fit != lhs.end() && sit != rhs.end(); fit++, sit++)
	{
		if (fit->first != sit->first
			|| fit->second != sit->second)
			return false;
	}
	if (fit != lhs.end() || sit != rhs.end())
		return false;
	return (lhs.size() == rhs.size());
}

void init_temp_maps(ft::map<int, int> *ftmp, std::map<int, int> *stmp)
{
	for (int i = 0; i < ratio / 10; i++)
	{
		ftmp->insert(ft::make_pair(i * 10, i * 11));
		stmp->insert(std::make_pair(i * 10, i * 11));
	}
}

void map_constructor(ft::map<int, int> &ftmp, std::map<int, int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	ft::map<int, int> fmp1;
	ft::map<int, int> fmp2(ftmp.begin(), ftmp.end());
	ft::map<int, int> fmp3(fmp2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	std::map<int, int> smp1;
	std::map<int, int> smp2(stmp.begin(), stmp.end());
	std::map<int, int> smp3(smp2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";
	
	if (compare_maps(fmp1, smp1) && compare_maps(fmp2, smp2) && compare_maps(fmp3, smp3))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void map_assign(ft::map<int, int> &ftmp, std::map<int, int> &stmp)
{
	time_t start;
	time_t end;
	ft::map<int, int> fmp;
	std::map<int, int> smp;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	fmp = ftmp;
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	smp = stmp;
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_maps(fmp, smp))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void map_insert(ft::map<int, int> &ftmp, std::map<int, int> &stmp)
{
	time_t start;
	time_t end;
	ft::map<int, int> fmp;
	std::map<int, int> smp;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	fmp.insert(ft::make_pair(10, 10));
	fmp.insert(ft::make_pair(1, 1));
	fmp.insert(ft::make_pair(5, 5));
	fmp.insert(ft::make_pair(20, 20));
	fmp.insert(ft::make_pair(7, 7));
	fmp.insert(fmp.begin(), ft::make_pair(8, 8));
	fmp.insert(fmp.end(), ft::make_pair(13, 13));
	fmp.insert(ftmp.begin(), ftmp.end());
	fmp.insert(ft::make_pair(ratio - 1, ratio - 1));
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	smp.insert(std::make_pair(10, 10));
	smp.insert(std::make_pair(1, 1));
	smp.insert(std::make_pair(5, 5));
	smp.insert(std::make_pair(20, 20));
	smp.insert(std::make_pair(7, 7));
	smp.insert(smp.begin(), std::make_pair(8, 8));
	smp.insert(smp.end(), std::make_pair(13, 13));
	smp.insert(stmp.begin(), stmp.end());
	smp.insert(std::make_pair(ratio - 1, ratio - 1));
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_maps(fmp, smp))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void map_clear(ft::map<int, int> &ftmp, std::map<int, int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	ft::map<int, int> fmp(ftmp);
	std::map<int, int> smp(stmp);

	start = timer();
	fmp.clear();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	smp.clear();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_maps(fmp, smp))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void map_erase(ft::map<int, int> &ftmp, std::map<int, int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	ft::map<int, int> fmp1(ftmp);
	ft::map<int, int> fmp2(ftmp);
	std::map<int, int> smp1(stmp);
	std::map<int, int> smp2(stmp);

	start = timer();
	fmp1.erase(10);
	fmp1.erase(fmp1.begin());
	fmp1.erase(1);
	fmp1.erase(5);
	fmp1.erase(20);
	fmp1.erase(fmp1.begin());
	fmp1.erase(fmp1.begin());
	fmp1.erase(fmp1.begin());
	fmp1.erase(7);
	fmp2.erase(fmp2.begin(), fmp2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	smp1.erase(10);
	smp1.erase(smp1.begin());
	smp1.erase(1);
	smp1.erase(5);
	smp1.erase(20);
	smp1.erase(smp1.begin());
	smp1.erase(smp1.begin());
	smp1.erase(smp1.begin());
	smp1.erase(7);
	smp2.erase(smp2.begin(), smp2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_maps(fmp1, smp1) && compare_maps(fmp2, smp2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void map_swap(ft::map<int, int> &ftmp, std::map<int, int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	ft::map<int, int> fmp1(ftmp);
	ft::map<int, int> fmp2;
	std::map<int, int> smp1(stmp);
	std::map<int, int> smp2;

	start = timer();
	fmp2.swap(fmp1);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	smp2.swap(smp1);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_maps(fmp1, smp1) && compare_maps(fmp2, smp2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void map_at(ft::map<int, int> &ftmp, std::map<int, int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	bool is_equal = true;

	start = timer();
	if (ftmp.at(10) != stmp.at(10) || ftmp.at(100) != stmp.at(100)
		|| ftmp.at(1000) != stmp.at(1000) || ftmp.at(500) != stmp.at(500)
		|| ftmp.at(ratio / 2) != stmp.at(ratio / 2))
		is_equal = false;
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";
	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (is_equal)
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void map_tests()
{
	ft::map<int, int> ftmp;
	std::map<int, int> stmp;
	init_temp_maps(&ftmp, &stmp);

	map_assign(ftmp, stmp);
	map_at(ftmp, stmp);
	map_clear(ftmp, stmp);
	map_constructor(ftmp, stmp);
	map_erase(ftmp, stmp);
	map_insert(ftmp, stmp);
	map_swap(ftmp, stmp);
}

#endif
