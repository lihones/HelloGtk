#include <stdio.h>
#include "tutorial/start.h"
#include "tutorial/PtWidget.h"
#include "tutorial/listview.h"
#include "tutorial/controller.h"
#include "primary/xwindow/x_main.h"
#include "browser/app/Application.h"

int main(int argc, char* argv[])
{
	int ret = 0;
	Application *app = new Application();
	ret = app->main(argc, argv);
	return ret;
}
