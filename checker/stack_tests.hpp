#ifndef STACK_TESTS_HPP
# define STACK_TESTS_HPP

#include <iostream>
#include <iomanip> 
#include <sys/time.h>

#include <stack>
#include "checker.hpp"
#include "../stack.hpp"


bool compare_stacks(ft::stack<int> &stack1, std::stack<int> &stack2)
{
    while (!stack1.empty() && !stack2.empty())
    {
      if (stack1.top() != stack2.top())
        return false;
      stack1.pop();
      stack2.pop();
    }
    return (stack1.empty() && stack2.empty());
}

void stack_push()
{
	time_t start;
	time_t end;
	ft::stack<int> fst;
	std::stack<int> sst;

	std::cout << std::setw(20) << std::left << __func__;

	start = timer();
	for (int i = 0; i < ratio; i++)
		fst.push(i);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	start = timer();
	for (int i = 0; i < ratio; i++)
		sst.push(i);
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_stacks(fst, sst))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void stack_pop()
{
	time_t start;
	time_t end;
	ft::stack<int> fst;
	std::stack<int> sst;

	std::cout << std::setw(20) << std::left << __func__;

	for (int i = 0; i < ratio; i++)
		fst.push(i);

	start = timer();
	for (int i = 0; i < ratio / 2; i++)
		fst.pop();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	for (int i = 0; i < ratio; i++)
		sst.push(i);

	start = timer();
	for (int i = 0; i < ratio / 2; i++)
		sst.pop();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_stacks(fst, sst))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void stack_top()
{
	time_t start;
	time_t end;
	ft::stack<int> fst;
	std::stack<int> sst;

	std::cout << std::setw(20) << std::left << __func__;

	for (int i = 0; i < ratio; i++)
		fst.push(i);
	
	start = timer();
	fst.top();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	for (int i = 0; i < ratio; i++)
		sst.push(i);

	start = timer();
	sst.top();
	end = timer();

	std::cout << std::setw(7) << std::right << end - start << " ms ";

	if (compare_stacks(fst, sst))
		std::cout << std::setw(8) << std::right << GREEN << "   OK" << RESET << std::endl;
	else
		std::cout << std::setw(8) << std::right << RED_C << "   FAIL" << RESET  << std::endl;
}

void stack_tests()
{
	stack_pop();
	stack_push();
	stack_top();
}

#endif
