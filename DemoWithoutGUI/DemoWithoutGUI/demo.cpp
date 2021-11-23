
#include "stdio.h"

#include "Inter.h"
#pragma comment(lib, "AIWZQDll.lib")

void Show()
{
	int nBoardWidth = 0;	//棋盘宽度
	int nBoardHeight = 0;	//棋盘高度
	TBOARD* pData = GetBoardData(&nBoardWidth, &nBoardHeight);
	if (pData == NULL || nBoardWidth < 1 || nBoardHeight < 1)
	{
		printf("无效数据\n");
		return;
	}

	printf("=============================================================================\n");
	for (int h = 0; h < nBoardHeight; h++)
	{
		for (int w = 0; w < nBoardWidth; w++)
		{
			switch (pData[h*nBoardWidth + w])
			{
			case -1:	//黑子
				printf("X ");
				break;
			case 1:		//白子
				printf("O ");
				break;
			case 0:		//空白，该位置尚未落子
				printf("- ");
				break;
			default:	//无效数据
				break;
			}
		}
		printf("\n");
	}
	printf("===============================================================================\n");
}

void main()
{
	if (!Login("user", "password"))
	{
		printf("登录失败\n");
		getchar();
		return;
	}

	if (!InitWithoutModelFile(15, 15, 5))
	{
		printf("初始化失败\n");
		getchar();
		return;
	}

	//使用模型文件初始化
	//if (!InitFromModelFile("model.mod"))
	//{
	//	printf("初始化失败\n");
	//	getchar();
	//	return;
	//}

	if (!StartNewGame())
	{
		printf("游戏开始失败\n");
		getchar();
		return;
	}

	while (!IsGameOver())
	{
		if (!SetPieceByAI())
		{
			printf("积分不足或网络问题，请确保网络畅通且积分充足（若是积分不足，充值后可继续本次对局\n");
			printf("当前积分为：%d\n", GetPoint());
			break;
		}
		Show();
		getchar();	//等待用户按键盘落下一子
	}

	switch (GetWinner())
	{
	case -1:
		printf("黑棋获胜\n");
		break;
	case 1:
		printf("白棋获胜\n");
		break;
	case 0:
		printf("平局\n");
		break;
	}
	getchar();

	SaveModel("model.mod");
	SaveSteps("data.txt");
}