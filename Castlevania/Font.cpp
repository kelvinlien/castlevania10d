#include "Font.h"


CFont::CFont()
{
	ani_set = CAnimationSets::GetInstance()->Get(8);
}

CFont::~CFont()
{

}

void CFont::Render(string str, int x, int y, int maxLength)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str.length() < maxLength)
		{
			int n = maxLength - str.length();
			for (int j = 0; j < n; j++)
			{
				ani_set->at(26)->Render(x + j * 15, y);
			}
			switch (str[i])
			{
			case '0':
				ani_set->at(26)->Render(x + (n + i) * 15, y);
				break;
			case '1':
				ani_set->at(27)->Render(x + (n + i) * 15, y);
				break;
			case '2':
				ani_set->at(28)->Render(x + (n + i) * 15, y);
				break;
			case '3':
				ani_set->at(29)->Render(x + (n + i) * 15, y);
				break;
			case '4':
				ani_set->at(30)->Render(x + (n + i) * 15, y);
				break;
			case '5':
				ani_set->at(31)->Render(x + (n + i) * 15, y);
				break;
			case '6':
				ani_set->at(32)->Render(x + (n + i) * 15, y);
				break;
			case '7':
				ani_set->at(33)->Render(x + (n + i) * 15, y);
				break;
			case '8':
				ani_set->at(34)->Render(x + (n + i) * 15, y);
				break;
			case '9':
				ani_set->at(35)->Render(x + (n + i) * 15, y);
				break;
			default:
				break;
			}
		}
		else
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
}
