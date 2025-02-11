#include "stdafx.h"
#include "MyGame.h"

CMyGame game;
CGameApp app;

int main(int argc, char* argv[])
{
	//app.DebugMemoryLeaks();
	app.OpenWindow(800, 600, "Saint Swordsman");
	//app.OpenFullScreen(800, 600, 32);
	//app.OpenConsole();
	app.SetClearColor(CColor::LightBlue());
	app.Run(&game);
	return(0);
}
