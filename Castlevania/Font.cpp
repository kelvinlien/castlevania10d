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
				CSprites::GetInstance()->Get(80026)->DrawBoard(x + j * 15, y);
			}
			switch (str[i])
			{
			case '0':
				CSprites::GetInstance()->Get(80026)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '1':
				CSprites::GetInstance()->Get(80027)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '2':
				CSprites::GetInstance()->Get(80028)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '3':
				CSprites::GetInstance()->Get(80029)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '4':
				CSprites::GetInstance()->Get(80030)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '5':
				CSprites::GetInstance()->Get(80031)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '6':
				CSprites::GetInstance()->Get(80032)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '7':
				CSprites::GetInstance()->Get(80033)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '8':
				CSprites::GetInstance()->Get(80034)->DrawBoard(x + (n + i) * 15, y);
				break;
			case '9':
				CSprites::GetInstance()->Get(80035)->DrawBoard(x + (n + i) * 15, y);
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
				CSprites::GetInstance()->Get(80026)->DrawBoard(x + i * 15, y);
				break;
			case '1':
				CSprites::GetInstance()->Get(80027)->DrawBoard(x + i * 15, y);
				break;
			case '2':
				CSprites::GetInstance()->Get(80028)->DrawBoard(x + i * 15, y);
				break;
			case '3':
				CSprites::GetInstance()->Get(80029)->DrawBoard(x + i * 15, y);
				break;
			case '4':
				CSprites::GetInstance()->Get(80030)->DrawBoard(x + i * 15, y);
				break;
			case '5':
				CSprites::GetInstance()->Get(80031)->DrawBoard(x + i * 15, y);
				break;
			case '6':
				CSprites::GetInstance()->Get(80032)->DrawBoard(x + i * 15, y);
				break;
			case '7':
				CSprites::GetInstance()->Get(80033)->DrawBoard(x + i * 15, y);
				break;
			case '8':
				CSprites::GetInstance()->Get(80034)->DrawBoard(x + i * 15, y);
				break;
			case '9':
				CSprites::GetInstance()->Get(80035)->DrawBoard(x + i * 15, y);
				break;
			default:
				break;
			}
		}
	}
}
