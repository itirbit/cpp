module;
#include <string_view>
#include <iostream>

export module hello;
export namespace hello
{
	void say_hello(const std::string_view& name)
	{
		std::cout << "Hello, " << name << "!\n"; 
	}
}
