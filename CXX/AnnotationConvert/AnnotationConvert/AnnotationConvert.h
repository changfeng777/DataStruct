#include<errno.h>
#include<stdio.h>
#include<string.h>

#pragma warning (disable:4996)

enum STATE{
	SUCCESS = 0,		// �ɹ�
	FILE_ERROR = 1,		// �ļ�����
	NO_MATCH = 2,		// ��ƥ��
	OTHER_ERROR = 3,	// ��������
};

enum TAG
{
	TAG_NONE,			// ��Ч��־
	TAG_BEGIN,			// ��ʼ��־
	TAG_END,			// ������־
};

typedef enum STATE STATE;
typedef enum TAG TAG;


STATE DealState(FILE* fIn, FILE* fOut)
{
	TAG tag = TAG_END;
	char first, second;

	do{
		first = fgetc(fIn);

		switch(first)
		{
		case '/': 
			second = fgetc(fIn);
			if (second == '*') // /* -> //
			{
				//
				// 3.ƥ������--ͨ��tag��־ʶ��
				//
				if (tag == TAG_END)
				{
					fputc('/', fOut);
					fputc('/', fOut);
					tag = TAG_BEGIN;
				}
			}
			else if (second == '/')
			{
				char next;
				//
				// 7.C++ע������--���굱ǰ��
				//
				fputc('/', fOut);
				fputc('/', fOut);
				do {
					next = fgetc(fIn);
					if (next == EOF)
						break;

					fputc(next, fOut);
				}while(next != '\n');
			}
			else
			{
				fputc(first, fOut);
				fputc(second, fOut);
			}

			break;
		case '\n':
			//
			// 4.����ע������--�����C++ע�ͣ������������//
			//
			fputc('\n', fOut);
			if (tag == TAG_BEGIN)
			{
				fputc('/', fOut);
				fputc('/', fOut); 
			}

			break;
		case '*':
			second = fgetc(fIn); 
			if (second == '/')
			{
				// ����־
				if (tag == TAG_BEGIN)
				{
					char next;
					tag = TAG_END;

					// 2.��������
					// 5.����ע������
					next = fgetc(fIn);
					if (next == EOF)
					{
						break;
					}
					else if (next != '\n')
					{
						fputc('\n', fOut);
						fseek(fIn, -1, SEEK_CUR);
					}
					else
					{
						fputc(next, fOut);
					}
				}
			}
			else if(second == '*')
			{
				// 6.������**/��β
				fputc(first, fOut);
				fseek(fIn, -1, SEEK_CUR);
			}
			break;
		default:
			if (first != EOF)
			{
				fputc(first, fOut);
			}
			break;
		}
	}while (first != EOF);

	if (tag != TAG_END)
	{
		return NO_MATCH;
	}
	else
	{
		return SUCCESS;
	}
}

// ע��ת��
STATE AnnotationConvert (const char* inFileName, const char* outFileName)
{
	STATE ret;
	FILE* fIn = fopen (inFileName, "r");
	FILE* fOut = fopen (outFileName, "w");

	if (fIn == 0)
	{
		return FILE_ERROR;
	}

	if (fOut == 0)
	{
		fclose(fIn);

		return FILE_ERROR;
	}

	//
	// ����״̬��
	// 
	ret = DealState (fIn, fOut);

	fclose(fIn);
	fclose(fOut);

	return ret;
}

void StartConvert ()
{
	const char* inFileName = "input.c";
	const char* outFileName = "output.c";

	STATE s = AnnotationConvert(inFileName, outFileName);

	if (s == SUCCESS) {
		printf("Convert Success\n");
	}
	else if (s == FILE_ERROR)
	{
		printf("File Error: %d\n", errno);
	}
	else if (s == NO_MATCH)
	{
		printf("No Match\n");
	}
	else
	{
		printf("Other Error\n");
	}
}
