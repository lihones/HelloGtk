#include "Application.h"
#include "browser/af/AfContext.h"
#include "browser/af/AfFactory.h"
#include "browser/af/AfProxy.h"

using namespace af;

Application::Application()
{}

Application::~Application()
{}

int Application::main(int argc, char* argv[])
{
	AfContext *context = AfFactory::createContext();
	AfProxy *proxy = context->proxy();
	delete context;
	proxy->disconnect();
	return 0;
}
