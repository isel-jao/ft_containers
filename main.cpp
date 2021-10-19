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



typedef  NAMESPACE::vector<int> vector;
typedef  NAMESPACE::pair<std::string, int> pair;
typedef  NAMESPACE::map<std::string, int>  map;

int main()
{
	
	return 0;
}