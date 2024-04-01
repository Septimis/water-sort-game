#include "Board.h"

int main(int argc, char** argv)
{
	for(unsigned short i = 1; i < argc; ++i)
	{
		Board level(argv[i]);
	}

	return 0;
}