class ScrollBar;
class Window;

class WidgetFactory
{
public:
	virtual ScrollBar createScrollBar() = 0;
	virtual Window createWindow() = 0;
};

class MotifWidgetFactory : public WidgetFactory
{
public:
	virtual ScrollBar createScrollBar();
	virtual Window createWindow();
};

class PMWidgetFactory : public WidgetFactory
{
public:
	virtual ScrollBar createScrollBar();
	virtual Window createWindow();
};
