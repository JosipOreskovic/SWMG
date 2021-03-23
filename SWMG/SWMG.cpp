#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Sprite3d.hpp"
#include "MemoryGame.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	MemoryGame game;
	game.Start();
	return EXIT_SUCCESS;
}