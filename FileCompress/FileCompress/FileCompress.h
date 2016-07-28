#include<iostream>

#include"HuffmanTree.h"
#include<string>
#include<cassert>
#include<cstdlib>

using namespace std;

typedef unsigned long LongType;

struct charInfo
{
	charInfo(LongType count = 0)
	:_count(count)
	{}
	bool operator!=(const charInfo& info)const
	{
		return _count != info._count;
	}
	charInfo operator+(const charInfo& info)const
	{
		return charInfo(_count + info._count);
	}
	bool operator<(const charInfo& info)const
	{
		return _count < info._count;
	}

	unsigned char _ch;
	LongType _count;
	string _code;
};
class FileCompress
{
public:
	FileCompress()
	{
		for (size_t i = 0; i<256; i++)
		{
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}
	}
	void Compress(const char* filename)
	{
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);

		//统计文件中字符出现的次数
		char ch = fgetc(fOut);
		while (!feof(fOut))
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fOut);
		}

		//构建HaffmanTree
		charInfo invalid;
		HuffmanTree<charInfo> tree(_infos, 256, invalid);

		//生成Huffman编码
		string code;
		GenerateHuffmanCode(tree.GetRoot(), code);

		//压缩
		string CompressFileName = filename;
		CompressFileName += ".compress";
		FILE* fIn = fopen(CompressFileName.c_str(), "wb");
		assert(fIn);

		fseek(fOut, 0, SEEK_SET);
		ch = fgetc(fOut);
		char value = 0;
		int size = 0;
		while (!feof(fOut))
		{
			string& code = _infos[(unsigned char)ch]._code;
			for (size_t i = 0; i < code.size(); i++)
			{

				if (code[i] == '1')
				{
					value |= 1;
				}

				++size;
				if (size == 8)
				{
					fputc(value, fIn);
					value = 0;
					size = 0;
				}
				value <<= 1;
			}
			ch = fgetc(fOut);
		}
		//补位
		if (size > 0)
		{
			value <<= (7 - size);
			putc(value, fIn);
		}
		
		//写配置文件
		string configFile = filename;
		configFile += ".config";
		FILE* fConfig = fopen(configFile.c_str(), "wb");
		assert(fConfig);

		string line;
		char buffer[128];
		for (size_t i = 0; i<256; i++)
		{
			if (_infos[i]._count > 0)
			{
				line += _infos[i]._ch;
				line += ",";
				_itoa(_infos[i]._count, buffer, 10);
				line += buffer;
				line += '\n';
			}
			fputs(line.c_str(), fConfig);
			line.clear();
		}
		fclose(fOut);
		fclose(fIn);
		fclose(fConfig);
	}

	bool ReadLine(FILE* fOut, string& line)
	{
		char ch = fgetc(fOut);
		if (feof(fOut))
			return false;
		while (!feof(fOut) && ch != '\n')
		{
			line += ch;
			ch = fgetc(fOut);
		}
		return true;
	}
	void UnCompress(const char* filename)
	{
		//读取配置文件，得字符出现次数
		string configFile = filename;
		configFile += ".config";
		FILE* fConfig = fopen(configFile.c_str(), "rb");
		assert(fConfig);

		string line;
		LongType charCount = 0;
		while (ReadLine(fConfig, line))
		{
			//处理统计换行符出现的次数
			if (line.empty())
			{
				line += '\n';
			}
			else
			{
				unsigned char ch = line[0];
				_infos[ch]._count = atoi(line.substr(2).c_str());
				line.clear();
			}

		}

		//构建huffmanTree
		charInfo invalid;
		HuffmanTree<charInfo> tree(_infos, 256, invalid);
		charCount = tree.GetRoot()->_weight._count;

		//读取压缩文件，进行还原
		string compressFile = filename;
		compressFile += ".compress";
		FILE* fOut = fopen(compressFile.c_str(), "rb");
		assert(fOut);

		string uncompressFile = filename;
		uncompressFile += ".uncompress";
		FILE* fIn = fopen(uncompressFile.c_str(), "wb");
		assert(fIn);

		HuffmanTreeNode<charInfo>* root = tree.GetRoot();
		HuffmanTreeNode<charInfo>* cur = root;

		char ch = fgetc(fOut);
		int pos = 7;
		while (1)
		{
			if (ch & (1 << pos))
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
			if (pos-- == 0)
			{
				pos = 7;
				ch = fgetc(fOut);
			}

			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fIn);
				if (--charCount == 0)
				{
					break;
				}
				cur = root;
			}
		}
		fclose(fOut);
		fclose(fIn);
		fclose(fConfig);
	}
protected:
	void GenerateHuffmanCode(HuffmanTreeNode<charInfo>* root, string code)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
			return;
		}
		GenerateHuffmanCode(root->_left, code + '0');
		GenerateHuffmanCode(root->_right, code + '1');
	}
protected:
	charInfo _infos[256];
};