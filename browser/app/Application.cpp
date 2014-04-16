#include "Application.h"
#include "browser/af/AfContext.h"
#include "browser/af/AfFactory.h"
#include "browser/af/AfProxy.h"
#include "browser/af/AfWindow.h"

using namespace af;

Application::Application()
{}

Application::~Application()
{}

int Application::main(int argc, char* argv[])
{
	AfContext *context = AfFactory::createContext();
	AfWindow *window = context->createWindow(20, 20, 300, 300);
	window->map();
	window->unmap();
	AfProxy *proxy = context->proxy();
	delete context;
	proxy->disconnect();
	return 0;
}
