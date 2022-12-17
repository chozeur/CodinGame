#include <iostream>
#include <cctype>

int	main(void)
{
	int			count=0;
	std::string	str;
	getline(std::cin,str);

	std::string::iterator it = str.begin();
	while (it != str.end())
	{
		while (it != str.end() && *it == ' ')
			++it;
		while (it != str.end() && isdigit(*it))
			++it;
		if (it != str.end() && *it != ' ')
			++count;
		while (it != str.end() && *it != ' ')
			++it;
	}

	std::cout << count << std::endl;

	return (0);
}
