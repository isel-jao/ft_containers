#include "ft_containers.hpp"

#define waza() std::cout << "WAZAAAAAAAA,\t\tline: " << __LINE__ << ",\tfunc: " << __FUNCTION__ << std::endl

template <typename ctnr>
void print_container(ctnr const &container, std::string sep = "\n")
{
	std::cout << "size: " << container.size() << sep;
	try
	{
		std::cout << "capacity: " << container.capacity() << "\t" << sep;
	}
	catch (const std::exception &e)
	{
	}

	typedef typename ctnr::const_iterator it;
	it first = container.begin();
	it last = container.end();
	while (first != last)
	{
		std::cout << *first;
		std::cout << sep;
		first++;
	}
	if (sep != "\n")
		std::cout << std::endl;
	else
		std::cout << std::flush;
}

int main()
{
	std::cout << "=========== testing constructors ==============" << std::endl;
	try
	{
		int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		NAMESPACE::vector<int> v1, v2(10, 1337), v3(arr1, arr1 + 10);
		print_container(v1, " ");
		print_container(v2, " ");
		print_container(v3, " ");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "=========== testing assign ==============" << std::endl;
	try
	{
		/* code */
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}