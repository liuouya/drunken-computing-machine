#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "Function.hpp"

class	Ftor
{
public:
  int	operator()()
  {
    std::cout << "there is no argument" << std::endl;
    return 0;
  }
  int	operator()(char c)
  {
    std::cout << "argument is '" << c << "'" << std::endl;
    return 0;
  }
  int	operator()(char a, char b)
  {
    std::cout << "argument is " << a << " + " << b << std::endl;
    return 0;
  }
  int	operator()(char a, char b, char c)
  {
    std::cout << "argument is " << a << " + " << b << " + " << c << std::endl;
    return 0;
  }
  void	operator()(char a, int b, long c, const char* d)
  {
    std::cout << "argument is " << a << " + " << b << " + " << c << " + " << d << std::endl;
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

struct A {
  int operator()(char) {
    return 0;
  }
};

int	main()
{
  // function pointer tests

  Function<int ()> f = &test;
  f();
  Function<int (char)> f1 = &test1;
  f1('a');
  Function<int (char, char)> f2 = &test2;
  f2('a', 'b');
  Function<int (char, char, char)> f3 = &test3;
  f3('a', 'b', 'c');
  Function<void (char, int, long, const char*)> f4 = &test4;
  f4('a', 1, 12345, "test");

  // boost::bind tests

  Function<int ()> b = boost::bind(&test);
  b();
  Function<int (char)> b1 = boost::bind(&test1, _1);
  b1('b');
  Function<int (char, char)> b2 = boost::bind(&test2, _1, _2);
  b2('b', 'c');
  Function<int (char, char, char)> b3 = boost::bind(&test3, _1, _2, _3);
  b3('a', 'b', 'c');
  Function<void (char, int, long, const char*)> b4 = boost::bind(&test4, _1, _2, _3, _4);
  b4('a', 1, 12345, "test");


  // functor tests

  Ftor ftor;
  Function<int ()> ft = ftor;
  ft();
  Function<int (char)> ft1 = ftor;
  ft1('f');
  Function<int (char, char)> ft2 = ftor;
  ft2('b', 'c');
  Function<int (char, char, char)> ft3 = ftor;
  ft3('a', 'b', 'c');
  Function<void (char, int, long, const char*)> ft4 = ftor;
  ft4('a', 1, 12345, "test");

  // copy tests

  Function<int ()> cft = ft;
  cft();
  Function<int (char)> cft1 = ft1;
  cft1('f');
  Function<int (char, char)> cft2 = ft2;
  cft2('b', 'c');
  Function<int (char, char, char)> cft3 = ft3;
  cft3('a', 'b', 'c');
  Function<void (char, int, long, const char*)> cft4 = ft4;
  cft4('a', 1, 12345, "test");

  // copy tests

  Function<int ()> ccft(ft);
  ccft();
  Function<int (char)> ccft1(ft1);
  ccft1('f');
  Function<int (char, char)> ccft2(ft2);
  ccft2('b', 'c');
  Function<int (char, char, char)> ccft3(ft3);
  ccft3('a', 'b', 'c');
  Function<void (char, int, long, const char*)> ccft4(ft4);
  ccft4('a', 1, 12345, "test");

  return 0;
}
