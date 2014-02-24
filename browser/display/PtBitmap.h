#ifndef __PTBITMAP_H__
#define __PTBITMAP_H__

namespace pt {

class BitmapImpl;
class PtGc;

class PtBitmap
{
public:
	PtBitmap(int width, int height, int format);
	virtual ~PtBitmap();
public:
	virtual int getWidth();
	virtual int getHeight();
	virtual PtGc* gc();
	//
	virtual BitmapImpl* impl();
public:
	static const int ARGB_8888 = 1;
	static const int RGB_565 = 2;
private:
	BitmapImpl *mImpl;
};

}

#endif
