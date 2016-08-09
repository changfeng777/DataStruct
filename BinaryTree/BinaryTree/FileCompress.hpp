#pragma once
#include<string>
using namespace std;

#include "HuffmanTree.hpp"

typedef long long LongType;

//#define _DEBUG_

// �ļ���Ϣ
struct FileInfo
{
	unsigned char _ch;		// �ַ�
	LongType _appearCount;	// ���ִ���
	string _huffmanCode;	// �ַ���Ӧ��huffman����

	FileInfo(int appearCount = 0)
		:_ch(0)
		,_appearCount(appearCount)
	{}

	bool operator < (const FileInfo& info) const
	{
		return _appearCount < info._appearCount;
	}

	bool operator != (const FileInfo& info) const
	{
		return info._appearCount != _appearCount;
	}

	FileInfo operator +(const FileInfo& info)
	{
		return FileInfo(info._appearCount + _appearCount);
	}
};

ostream& operator<<(ostream& os, const FileInfo& info)
{
	os<<info._ch<<":"<<info._appearCount;

	return os;
}

class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; ++i)
		{
			_fileInfos[i]._ch = i;
		}
	}

	void _GenerateHuffmanCode(HuffmanNode<FileInfo>* root)
	{
		if (root)
		{
			_GenerateHuffmanCode(root->_left);
			_GenerateHuffmanCode(root->_right);

			// Ҷ�ӽڵ���Ϊ����ڵ㣬˳��Ҷ�ӽڵ�����Ѱ��Huffman����
			if (root->_left == NULL && root->_right == NULL)
			{
				// code��_fileInfos�����б����ַ�����������á�
				string& code = _fileInfos[root->_weight._ch]._huffmanCode;

				HuffmanNode<FileInfo>* cur = root;
				HuffmanNode<FileInfo>* parent = root->_parent;
				while (parent)
				{
					if (parent->_left == cur)
						code += '0';
					else
						code += '1';

					cur = parent;
					parent = cur->_parent;
				}
				
				// Ѱ�ұ����Ǵ�Ҷ�ӽڵ㵽���ڵ㣬����Ҫ�Ա����������
				reverse(code.begin(), code.end());
			}
		}
	}

	// �ݹ�ķ�ʽ���ɱ���
	void _GenerateHuffmanCode_R(HuffmanNode<FileInfo>* root, string code)
	{
		if (root)
		{
			_GenerateHuffmanCode_R(root->_left, code+'0');
			_GenerateHuffmanCode_R(root->_right, code+'1');

			// Ҷ�ӽڵ���Ϊ����ڵ㣬˳��Ҷ�ӽڵ�����Ѱ��Huffman����
			if (root->_left == NULL && root->_right == NULL)
			{
				_fileInfos[root->_weight._ch]._huffmanCode = code;
			}
		}
	}

	bool ReadLine(FILE* fOut, string& line)
	{
		assert(fOut);

		char ch = fgetc(fOut);
		if (feof(fOut))
			return false;

		while (ch != '\n')
		{
			line += ch;
			ch = fgetc(fOut);

			if (feof(fOut))
				break;
		}

		return true;
	}

	void Compress(const char* fileName)
	{
		long long charCount = 0;
		// 1.��ȡ�ļ�ͳ���ַ����ֵĴ�����
		FILE* fOut = fopen(fileName, "rb");
		while (1)
		{
			// ���feof���ļ�β�Ժ����һ���ļ�β�ı���ַ�-1
			char ch = fgetc(fOut);
			if (feof(fOut))
				break;

			_fileInfos[(unsigned char)ch]._appearCount++;
			++charCount;
		}

		// 2.�����ַ����ֵĴ�������Huffman����������ÿ���ַ���Ӧ��Huffman����
		HuffmanTree_P<FileInfo> tree;
		FileInfo invalid(0);
		tree.CreateHuffmanTree(_fileInfos, 256, invalid);

#ifdef _DEBUG_
		tree.LevelOrder();
#endif
		//string code;
		//_GenerateHuffmanCode(tree.GetRootNode(), code);
		_GenerateHuffmanCode(tree.GetRootNode());
		cout<<endl;

		string compressFileName = fileName;
		compressFileName += ".Compress";
		FILE* fIn = fopen(compressFileName.c_str(), "wb");

		// 3.��ѹ������д��ѹ���ļ���
		fseek( fOut, 0, SEEK_SET);
		int pos = 0;
		char value = 0;
		while (1)
		{
			char ch = fgetc(fOut);
			if (feof(fOut))
				break;

			string& code = _fileInfos[(unsigned char)ch]._huffmanCode;
#ifdef _DEBUG_
			cout<<code<<"->";
#endif
			for (size_t i = 0; i < code.size(); ++i)
			{
				value <<= 1;

				if (code[i] == '1')
					value |= 1;

				if(++pos == 8)
				{
					fputc(value, fIn);
					pos = 0;
					value = 0;
				}
			}
		}

		if (pos)
		{
			value <<= (8 - pos);
			fputc(value, fIn);
		}

		cout<<endl;

		// 4.��Huffman������Ϣд�������ļ���
		string configFileName = fileName;
		configFileName += ".config";
		FILE* fInConfig = fopen(configFileName.c_str(), "wb");

		string infoStr;
		char countStr[20];

		// ��д���ַ�����
		/*_itoa(charCount>>32, countStr, 10);
		fputs(countStr, fInConfig);
		fputc('\n', fInConfig);

		_itoa(charCount&0xFFFFFFFF, countStr, 10);
		fputs(countStr, fInConfig);
		fputc('\n', fInConfig);*/

		for(int i = 0; i < 256; ++i)
		{
			if (_fileInfos[i] != invalid)
			{
				infoStr = _fileInfos[i]._ch;
				infoStr += ',';

				//
				// �˴�appearCount��long long, �����ļ��������ַ����ֵĴ���
				// �������͵ı�ʾ��Χʱ����Ҫ������д����д��λ�ĸ��ֽڣ���д��λ�ĸ��ֽ�
				//
				_itoa(_fileInfos[i]._appearCount, countStr, 10);
				infoStr += countStr;
				infoStr += '\n';

				fputs(infoStr.c_str(), fInConfig);
			}
		}

		fclose(fIn);
		fclose(fOut);
		fclose(fInConfig);
	} 

	void Uncompress(const char* fileName)
	{
		// 1.��ȡ�����ļ���Huffman������Ϣ
		string configFileName = fileName;
		configFileName += ".config";
		FILE* fOutConfig = fopen(configFileName.c_str(), "rb");
		string line;
		char ch = 0;
		LongType appearCount = 0;

		// ��ȡ�ļ����ַ�����
	/*	long long charCount = 0;
		ReadLine(fOutConfig, line);
		charCount = atoi(line.c_str());
		charCount <<= 32;
		ReadLine(fOutConfig, line);
		charCount += atoi(line.c_str());
		line.clear();*/

		while(ReadLine(fOutConfig, line))
		{
			//
			// ������һ������(ͳ�Ƶ��ַ�Ϊ����)�����Ӧ�ַ�Ϊ���з�
			//
			if (!line.empty())
			{
				//sscanf(line.c_str(), "%s,%d", ch, appearCount);
				ch = line[0];

				_fileInfos[(unsigned char)ch]._appearCount = atoi(line.substr(2).c_str());
				line.clear();
			}
			else
			{
				line = '\n'; 
			}
		}

		// 2.���ݶ�����������Ϣ���ؽ�Huffman��
		HuffmanTree_P<FileInfo> tree;
		FileInfo invalid(0);
		tree.CreateHuffmanTree(_fileInfos, 256, invalid);

#ifdef _DEBUG_
		tree.LevelOrder();
#endif
		//
		// Huffman���ĸ��ڵ��Ȩֵ���������ļ��ַ����ִ����ĺͣ�
		// Ҳ�����ļ��ַ����ֵĴ���
		//
		HuffmanNode<FileInfo>* root = tree.GetRootNode();
		long long charCount = 0;
		charCount = root->_weight._appearCount;
		cout<<"��ѹ��"<<charCount<<"���ַ�"<<endl;

		// 3. ��ȡѹ����Ϣ�������ؽ���Huffman����ѹ��
		string uncompressFileName = fileName;
		uncompressFileName += ".Uncompress";
		FILE* fIn = fopen(uncompressFileName.c_str(), "wb");

		string compressFileName = fileName;
		compressFileName += ".Compress";
		FILE* fOut = fopen(compressFileName.c_str(), "rb");

		// 4.����ѹ���ļ��ַ�������Huffman����Ѱ�Ҷ�Ӧ���ַ�
		int pos = 8;
		HuffmanNode<FileInfo>* cur = root;
		ch = fgetc(fOut);
		while(1)
		{
			--pos;

			if(ch & (1<<pos))
				cur = cur->_right;
			else
				cur = cur->_left;
			
			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fIn);
				cur = root;

				//
				// �˴�ʹ�ø������жϽ�ѹ���Ƿ���ɣ���Ϊѹ��ʱ�����һ���ַ�
				// ���ܴ��ڲ�λ��������ѹ���������һЩ�ַ���
				//
				if (--charCount == 0)
					break;
			}

			if (pos == 0)
			{
				ch = fgetc(fOut);
				pos = 8;
			}
		}

		fclose(fIn);
		fclose(fOut);
		fclose(fOutConfig);
	}

private:
	FileInfo _fileInfos[256];
};

void TestCompress()
{
	FileCompress fc;

	int begin = GetTickCount();
	fc.Compress("Input.BIG");
	int end = GetTickCount();

	cout<<"Compress:"<<end - begin<<endl;
}

void TestUncompress()
{
	FileCompress fc;
	int begin = GetTickCount();
	fc.Uncompress("Input.BIG");
	int end = GetTickCount();

	cout<<"Compress:"<<end - begin<<endl;
}

void TestFileCompress()
{
	TestCompress();
	TestUncompress();
}