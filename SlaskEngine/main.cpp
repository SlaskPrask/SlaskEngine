#include "include/Slask.h"

void techGameStart();
void techGameEnd();

int main(int argc, char *argv[])
{
	using namespace slask;
	setGameStartFunction(&techGameStart);
	setGameEndFunction(&techGameEnd);

	delete new SlaskEngine(argc,argv);

	return 0;
}