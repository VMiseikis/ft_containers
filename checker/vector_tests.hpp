#ifndef VECTOR_TESTS_HPP
# define VECTOR_TESTS_HPP

#include <iostream>
#include <iomanip> 
#include <sys/time.h>


#include <vector>
#include "checker.hpp"
#include "../vector.hpp"

bool compare_vectors(ft::vector<int> &v1, std::vector<int> &v2)
{ return (v1.size() == v2.size() && std::equal(v1.begin(), v1.end(), v2.begin())); }

void vector_assign()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1;
	ft::vector<int> fv2;
	std::vector<int> sv1;
	std::vector<int> sv2;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	fv1.assign(ratio, 9);
	fv2.assign(ratio + ratio, 1);
	fv1.assign(fv2.begin(), fv2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sv1.assign(ratio, 9);
	sv2.assign(ratio + ratio, 1);
	sv1.assign(sv2.begin(), sv2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1) && compare_vectors(fv2, sv2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_push_back()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1;
	std::vector<int> sv1;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	for (int i = 0; i < ratio; i++)
		fv1.push_back(i);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	for (int i = 0; i < ratio; i++)
		sv1.push_back(i);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_resize()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1;
	std::vector<int> sv1;

	std::cout << std::setw(20) << std::left << __func__;

	fv1.assign(ratio, 1);
	start = timer();
	fv1.resize(ratio + ratio);
	fv1.resize(ratio + ratio + ratio);
	fv1.resize(10);
	fv1.resize(ratio);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	sv1.assign(ratio, 1);
	start = timer();
	sv1.resize(ratio + ratio);
	sv1.resize(ratio + ratio + ratio);
	sv1.resize(10);
	sv1.resize(ratio);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_reserve()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1;
	std::vector<int> sv1;

	std::cout << std::setw(20) << std::left << __func__;

	fv1.assign(ratio, 1);
	start = timer();
	fv1.reserve(ratio + ratio);
	fv1.reserve(ratio + ratio + ratio);
	fv1.reserve(10);
	fv1.reserve(ratio);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	sv1.assign(ratio, 1);
	start = timer();
	sv1.reserve(ratio + ratio);
	sv1.reserve(ratio + ratio + ratio);
	sv1.reserve(10);
	sv1.reserve(ratio);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_constructor()
{
	time_t start;
	time_t end;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	ft::vector<int>fv1;
	ft::vector<int>fv2(ratio, 1);
	ft::vector<int>fv3(fv2.begin(), fv2.end());
	ft::vector<int>fv4(fv2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	std::vector<int>sv1;
	std::vector<int>sv2(ratio, 1);
	std::vector<int>sv3(sv2.begin(), sv2.end());
	std::vector<int>sv4(sv2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1) && compare_vectors(fv2, sv2)
		&& compare_vectors(fv3, sv3) && compare_vectors(fv4, sv4))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_pop_back()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1;
	std::vector<int> sv1;

	std::cout << std::setw(20) << std::left << __func__;

	fv1.assign(ratio, 1);
	start = timer();
	for (int i = 0; i < ratio / 2; i++)
		fv1.pop_back();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	sv1.assign(ratio, 1);
	start = timer();
	for (int i = 0; i < ratio / 2; i++)
		sv1.pop_back();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_erase()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1;
	ft::vector<int> fv2(ratio, 1);
	std::vector<int> sv1;
	std::vector<int> sv2(ratio, 1);

	std::cout << std::setw(20) << std::left << __func__;

	for (int i = 0; i < ratio; i++)
	{
		fv1.push_back(i);
		sv1.push_back(i);
	}
	
	start = timer();
	fv1.erase(fv1.begin());
	fv1.erase(fv1.end() - 1);
	fv1.erase(fv1.begin() + 10);
	fv1.erase(fv1.begin() + 100);
	fv1.erase(fv1.begin() + 1000);
	fv2.erase(fv2.begin(), fv2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";
	
	start = timer();
	sv1.erase(sv1.begin());
	sv1.erase(sv1.end() - 1);
	sv1.erase(sv1.begin() + 10);
	sv1.erase(sv1.begin() + 100);
	sv1.erase(sv1.begin() + 1000);
	sv2.erase(sv2.begin(), sv2.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1) && compare_vectors(fv2, sv2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_clear()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1(ratio, 1);
	ft::vector<int> fv2(ratio + ratio, 2);
	std::vector<int> sv1(ratio, 1);
	std::vector<int> sv2(ratio + ratio, 2);

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	fv1.clear();
	fv2.clear();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sv1.clear();
	sv2.clear();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1) && compare_vectors(fv2, sv2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_insert()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1(ratio, 1);
	ft::vector<int> fv2(ratio + ratio, 2);
	std::vector<int> sv1(ratio, 1);
	std::vector<int> sv2(ratio + ratio, 2);

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	fv1.insert(fv1.begin() + ratio / 10, 9);
	fv1.insert(fv1.begin() + ratio / 4, 4);
	fv2.insert(fv2.end() - 1, fv1.begin(), fv1.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sv1.insert(sv1.begin() + ratio / 10, 9);
	sv1.insert(sv1.begin() + ratio / 4, 4);
	sv2.insert(sv2.end() - 1, sv1.begin(), sv1.end());
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1) && compare_vectors(fv2, sv2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_swap()
{
	time_t start;
	time_t end;
	ft::vector<int> fv1;
	ft::vector<int> fv2;
	std::vector<int> sv1;
	std::vector<int> sv2;

	std::cout << std::setw(20) << std::left << __func__;

	for (int i = 0; i < ratio; i++)
	{
		fv1.push_back(i);
		fv2.push_back(ratio - i);
		sv1.push_back(i);
		sv2.push_back(ratio - i);
	}

	start = timer();
	fv1.swap(fv2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	sv1.swap(sv2);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_vectors(fv1, sv1) && compare_vectors(fv2, sv2))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void vector_tests()
{
	vector_assign();
	vector_constructor();
	vector_clear();
	vector_erase();
	vector_insert();
	vector_pop_back();
	vector_push_back();
	vector_reserve();
	vector_resize();
	vector_swap();
}

#endif
