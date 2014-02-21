#include "Application.h"
#include "browser/display/PtDisplay.h"

using namespace pt;

Application::Application()
{}

Application::~Application()
{}

int Application::main(int argc, char* argv[])
{
	PtDisplay *display = new PtDisplay();
	display->connect();
	PtWindow *window = display->createWindow(50, 50);
	display->eventLoop();
	display->close();
	return 0;
}
