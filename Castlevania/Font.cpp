#include "Font.h"


CFont::CFont()
{
	ani_set = CAnimationSets::GetInstance()->Get(8);
}

CFont::~CFont()
{

}

void CFont::Render(string str, int x, int y)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		
		switch (str[i])
		{
		case '0':
			ani_set->at(26)->Render(x + i * 15, y);
			break;
		case '1':
			ani_set->at(27)->Render(x + i * 15, y);
			break;
		case '2':
			ani_set->at(28)->Render(x + i * 15, y);
			break;
		case '3':
			ani_set->at(29)->Render(x + i * 15, y);
			break;
		case '4':
			ani_set->at(30)->Render(x + i * 15, y);
			break;
		case '5':
			ani_set->at(31)->Render(x + i * 15, y);
			break;
		case '6':
			ani_set->at(32)->Render(x + i * 15, y);
			break;
		case '7':
			ani_set->at(33)->Render(x + i * 15, y);
			break;
		case '8':
			ani_set->at(34)->Render(x + i * 15, y);
			break;
		case '9':
			ani_set->at(35)->Render(x + i * 15, y);
			break;
		default:
			break;
		}
	}
}
