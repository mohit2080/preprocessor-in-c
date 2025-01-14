// main.c

#include"header.h"
int main(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("usage: ./a.out file.c");
		return 0;
	}
	comment_remove(argv[1]);
	macro_substitute(argv[1]);
	header_include(argv[1]);
}
