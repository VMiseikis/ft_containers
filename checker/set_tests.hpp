#ifndef SET_TESTS_HPP
# define SET_TESTS_HPP

#include <iostream>
#include <iomanip> 
#include <sys/time.h>

#include <set>
#include "checker.hpp"
#include "../set.hpp"

bool compare_sets(ft::set<int> &lhs, std::set<int> &rhs)
{
	ft::set<int, int>::iterator fit = lhs.begin();
	std::set<int, int>::iterator sit = rhs.begin();

	for (; fit != lhs.end() && sit != rhs.end(); fit++, sit++)
		if (*fit != *sit)
			return false;
	if (fit != lhs.end() || sit != rhs.end())
		return false;
	return (lhs.size() == rhs.size());
}

void init_temp_sets(ft::set<int> *ftmp, std::set<int> *stmp)
{
	for (int i = 0; i < ratio / 10; i++)
	{
		ftmp->insert(i * 10);
		stmp->insert(i * 10);
	}
}

void set_assign(ft::set<int> &ftmp, std::set<int> &stmp)
{
	time_t start;
	time_t end;
	ft::set<int> fst;
	std::set<int> sst;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	fst = ftmp;
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sst = stmp;
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_sets(fst, sst))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void set_clear(ft::set<int> &ftmp, std::set<int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	ft::set<int> fst(ftmp);
	std::set<int> sst(stmp);

	start = timer();
	fst.clear();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sst.clear();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_sets(fst, sst))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void set_constructor(ft::set<int> &ftmp, std::set<int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	ft::set<int> fst1;
	ft::set<int> fst2(ftmp.begin(), ftmp.end());
	ft::set<int> fst3(fst2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	std::set<int> sst1;
	std::set<int> sst2(stmp.begin(), stmp.end());
	std::set<int> sst3(sst2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";
	
	if (compare_sets(fst1, sst1) && compare_sets(fst2, sst2) && compare_sets(fst3, sst3))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void set_erase(ft::set<int> &ftmp, std::set<int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	ft::set<int>  fst1(ftmp);
	ft::set<int>  fst2(ftmp);
	std::set<int> sst1(stmp);
	std::set<int> sst2(stmp);

	start = timer();
	fst1.erase(10);
	fst1.erase(fst1.begin());
	fst1.erase(1);
	fst1.erase(5);
	fst1.erase(20);
	fst1.erase(fst1.begin());
	fst1.erase(fst1.begin());
	fst1.erase(fst1.begin());
	fst1.erase(7);
	fst2.erase(fst2.begin(), fst2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sst1.erase(10);
	sst1.erase(sst1.begin());
	sst1.erase(1);
	sst1.erase(5);
	sst1.erase(20);
	sst1.erase(sst1.begin());
	sst1.erase(sst1.begin());
	sst1.erase(sst1.begin());
	sst1.erase(7);
	sst2.erase(sst2.begin(), sst2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_sets(fst1, sst1) && compare_sets(fst2, sst2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void set_insert(ft::set<int> &ftmp, std::set<int> &stmp)
{
	time_t start;
	time_t end;
	ft::set<int> fst;
	std::set<int> sst;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	fst.insert(10);
	fst.insert(1);
	fst.insert(5);
	fst.insert(20);
	fst.insert(7);
	fst.insert(fst.begin(), 8);
	fst.insert(fst.end(), 13);
	fst.insert(ftmp.begin(), ftmp.end());
	fst.insert(ratio - 1);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sst.insert(10);
	sst.insert(1);
	sst.insert(5);
	sst.insert(20);
	sst.insert(7);
	sst.insert(sst.begin(), 8);
	sst.insert(sst.end(), 13);
	sst.insert(stmp.begin(), stmp.end());
	sst.insert(ratio - 1);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_sets(fst, sst))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void set_swap(ft::set<int> &ftmp, std::set<int> &stmp)
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	ft::set<int>  fst1(ftmp);
	ft::set<int>  fst2;
	std::set<int> sst1(stmp);
	std::set<int> sst2;

	start = timer();
	fst2.swap(fst1);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sst2.swap(sst1);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_sets(fst1, sst1) && compare_sets(fst2, sst2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void set_tests()
{
	ft::set<int> ftmp;
	std::set<int> stmp;
	init_temp_sets(&ftmp, &stmp);

	set_assign(ftmp, stmp);
	set_clear(ftmp, stmp);
	set_constructor(ftmp, stmp);
	set_erase(ftmp, stmp);
	set_insert(ftmp, stmp);
	set_swap(ftmp, stmp);
}

#endif
