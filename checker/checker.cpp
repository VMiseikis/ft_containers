#include "checker.hpp"
#include "vector_tests.hpp"
#include "stack_tests.hpp"
#include "map_tests.hpp"
#include "set_tests.hpp"

int main()
{
	std::cout << "################################################" << std::endl;
	std::cout << "#      Basic project FT_Containers tester      #" << std::endl;
	std::cout << "################################################" << std::endl;
	std::cout << "                     VECTOR                     " << std::endl;
	std::cout << "FUNKTION               FT_TIME   STD_TIME Result" << std::endl;
	vector_tests();
	std::cout << "\n                     STACK                      " << std::endl;
	std::cout << "FUNKTION               FT_TIME   STD_TIME Result" << std::endl;
	stack_tests();
	std::cout << "\n                       MAP                      " << std::endl;
	std::cout << "FUNKTION               FT_TIME   STD_TIME Result" << std::endl;
	map_tests();
	std::cout << "\n                       SET                      " << std::endl;
	std::cout << "FUNKTION               FT_TIME   STD_TIME Result" << std::endl;
	set_tests();
	std::cout << "################################################" << std::endl;
	std::cout << "Link for more serious testers:" << std::endl;
	std::cout << "https://github.com/mli42/containers_test.git" << std::endl;
	std::cout << "https://github.com/Mikastiv/ft_containers-terminator.git" << std::endl;
	std::cout << "################################################" << std::endl;
	
	return 0;
}
