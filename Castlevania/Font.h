#include "Animations.h"
#include <stdlib.h>

class CFont
{
private:
	LPANIMATION_SET ani_set;
	CSprite *font;
public:
	CFont();
	~CFont();
	void Render(string string, int x, int y, int maxLength);
};