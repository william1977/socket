#include <stdio.h>
#include "testc.h"
#include "testcpp.h"
#include <string>
int main()
{
	TestA a;
	int o = a.test(8);
	std::string gg("tt");
	int k = test(9);
	printf("hello.%d,%d,%s\n", o,k,gg.c_str());
        return 0;
}
