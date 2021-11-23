
#include "stdio.h"

#include "Inter.h"
#pragma comment(lib, "AIWZQDll.lib")

void Show()
{
	int nBoardWidth = 0;	//���̿��
	int nBoardHeight = 0;	//���̸߶�
	TBOARD* pData = GetBoardData(&nBoardWidth, &nBoardHeight);
	if (pData == NULL || nBoardWidth < 1 || nBoardHeight < 1)
	{
		printf("��Ч����\n");
		return;
	}

	printf("=============================================================================\n");
	for (int h = 0; h < nBoardHeight; h++)
	{
		for (int w = 0; w < nBoardWidth; w++)
		{
			switch (pData[h*nBoardWidth + w])
			{
			case -1:	//����
				printf("X ");
				break;
			case 1:		//����
				printf("O ");
				break;
			case 0:		//�հף���λ����δ����
				printf("- ");
				break;
			default:	//��Ч����
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
		printf("��¼ʧ��\n");
		getchar();
		return;
	}

	if (!InitWithoutModelFile(15, 15, 5))
	{
		printf("��ʼ��ʧ��\n");
		getchar();
		return;
	}

	//ʹ��ģ���ļ���ʼ��
	//if (!InitFromModelFile("model.mod"))
	//{
	//	printf("��ʼ��ʧ��\n");
	//	getchar();
	//	return;
	//}

	if (!StartNewGame())
	{
		printf("��Ϸ��ʼʧ��\n");
		getchar();
		return;
	}

	while (!IsGameOver())
	{
		if (!SetPieceByAI())
		{
			printf("���ֲ�����������⣬��ȷ�����糩ͨ�һ��ֳ��㣨���ǻ��ֲ��㣬��ֵ��ɼ������ζԾ�\n");
			printf("��ǰ����Ϊ��%d\n", GetPoint());
			break;
		}
		Show();
		getchar();	//�ȴ��û�����������һ��
	}

	switch (GetWinner())
	{
	case -1:
		printf("�����ʤ\n");
		break;
	case 1:
		printf("�����ʤ\n");
		break;
	case 0:
		printf("ƽ��\n");
		break;
	}
	getchar();

	SaveModel("model.mod");
	SaveSteps("data.txt");
}