#include <iostream>
#include <boost/bind.hpp>
#include "Function.hpp"

class	Ftor
{
public:
  int	operator()(char c)
  {
    std::cout << "argument is '" << c << "'" << std::endl;
    return 0;
  }
};

int	test()
{
  std::cout << "there is no argument" << std::endl;
  return 0;
}

int	test1(char a)
{
  std::cout << "argument is '" << a << "'" << std::endl;
  return 0;
}

int	test2(char a, char b)
{
  std::cout << "argument is " << a << " + " << b << std::endl;
  return 0;
}

int	test3(char a, char b, char c)
{
  std::cout << "argument is " << a << " + " << b << " + " << c << std::endl;
  return 0;
}

void	test4(char a, int b, long c, const char* d)
{
  std::cout << "argument is " << a << " + " << b << " + " << c << " + " << d << std::endl;
}

int	main()
{
  // Ftor	ftor;

  Function<int (char)> f = &test1;
  f('a');
  Function<int (char, char)> f1 = &test2;
  f1('a', 'b');
  Function<int (char, char, char)> f3 = &test3;
  f3('a', 'b', 'c');
  Function<void (char, int, long, const char*)> f4 = &test4;
  f4('a', 1, 12345, "test");

  // Function<int (char)> f2 = boost::bind(&test1, _1);
  // f2('b');
  // Function<int (char)> f3 = &ftor;
  // f3('c');

  // Function<int (char)> f;
  // (void)f;
  // Function<int (char, int)> f2;
  // (void)f2;
  // Function<int (int, char, char)> f3;
  // (void)f3;

  return 0;
}
