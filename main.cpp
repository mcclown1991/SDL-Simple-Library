#include "Sources/Core/SDLCore.h"

int main(int argc, char** argv) {
	
	SDLCore::GetSDLCore()->SystemInit();
	SDLCore::GetSDLCore()->SystemRun();

	return 0;
}