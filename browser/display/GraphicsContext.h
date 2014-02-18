#ifndef __GRAPHICSCONTEXT_H__
#define __GRAPHICSCONTEXT_H__

namespace pt {

class GraphicsContext
{
public:
	GraphicsContext();
private:
	GraphicsContextImpl *mImpl;
};

}
