#pragma once
<<<<<<< HEAD
#include<iostream>
using namespace std;

#include<string>
#include<assert.h>

#include"HaffmanTree.h"

//1��ͳ���ַ����ִ���
//2������Haffman�����õ�Haffman����
//3���ļ�ѹ��
//4���ļ���ѹ��


//�ַ���Ϣ
typedef unsigned long LongType;
struct CharInfo
{
	char _ch;			//�ַ�
	LongType _count;	//����
	string _code;		//����

	CharInfo(LongType count = 0)
		:_count(count)
	{}

	bool operator<(const CharInfo& info)const
	{
		return _count < info._count;
	}

	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}

	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_count + info._count);
	}
};

class FileCompress
{
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infors[i]._ch = i;
			_infors[i]._count = 0;
		}
	}

	void Compress(const char* filename)
	{
		FILE* fout = fopen(filename, "rb");
		assert(fout);//�ж��ļ��Ƿ�򿪳ɹ�

		//1.ͳ���ļ����ַ����ֵĴ���
		char ch = fgetc(fout);
		while (!feof(fout))
		{
			//ע��ch����Ϊ�з���char��infor[256]�����±�0-256
			_infors[(unsigned char)ch]._count++;
			ch = fgetc(fout);
		}

		//2������Haffman��
		//ע�⣬ֻ���ַ���_count>0�Ź�������Huffman����
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_infors, 256, invalid);

		//3������Haffman����
		string code;
		_GenerateHuffmanCode(tree.GetRoot(), code);

		//4���ļ�ѹ��
		string CompressFileName = filename;
		CompressFileName += ".compress";

		FILE* fin = fopen(CompressFileName.c_str(), "wb");
		assert(fin);

		//FILE* fout = fopen(filename, "r");
		fseek(fout, 0, SEEK_SET);//���ļ�ָ������ļ���ʼ
		char value = 0;
		int size = 0;		//��������λ��
		ch = fgetc(fout);
		while (!feof(fout))
		{
			string& code = _infors[(unsigned char)ch]._code;
			for (size_t i = 0; i < code.size(); ++i)
			{
				//������һλ
				value = value << 1;
				if (code[i] == '1')
				{
					value |= 1;
				}
				else
				{
					value |= 0;
				}
				++size;

				if (size == 8)
				{
					//printf("%x\n", value);
					fwrite(&value, sizeof(value), 1, fin);
					//fputc(value, fin);
					size = 0;
					value = 0;
				}

			}
			ch = fgetc(fout);
		}
		//û����8λ
		if (size != 0)
		{
			value <<= (8 - size);
			fwrite(&value, sizeof(value), 1, fin);
			//printf("%x\n", value);
		}

		//5��д�����ļ����ַ����ִ�����
		string configFilename = filename;
		configFilename += ".config";
		FILE* finconfig = fopen(configFilename.c_str(), "wb");
		assert(finconfig);

		size_t num=0;
		for (size_t i = 0; i < 256; ++i)
		{
			if (_infors[i] != invalid)
			{
				++num;
			}
		}

		fwrite(&num, sizeof(num), 1, finconfig);
		for (size_t i = 0; i < 256; ++i)
		{
			if (_infors[i]._count)
			{
				fwrite(&_infors[i]._ch, sizeof(_infors[i]._ch), 1, finconfig);
				fwrite(&_infors[i]._count, sizeof(_infors[i]._count), 1, finconfig);
			}
		}

		fclose(fout);
		fclose(fin);
		fclose(finconfig);
	}

	//��ѹ��
	void UnCompress(const char* Compressfilename)
	{
		string CompressFilename = Compressfilename;
		string filename;
		size_t pos=CompressFilename.rfind('.');
		filename = CompressFilename.substr(0,pos);

		string configFilename = filename;
		configFilename += ".config";
		FILE* foutconfig = fopen(configFilename.c_str(), "rb");
		assert(foutconfig);

		//�������ļ�����_countд��_infors
		size_t num;
		fread(&num, sizeof(num), 1, foutconfig);

		while (num)
		{
			CharInfo infor;
			fread(&infor._ch, sizeof(infor._ch), 1 , foutconfig);
			fread(&infor._count, sizeof(infor._count), 1 , foutconfig);
			--num;

			_infors[(unsigned char)infor._ch] = infor;
		}

		//�ؽ�Huffman���������ļ���
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_infors, 256, invalid);
		HuffmanTreeNode<CharInfo>* root = tree.GetRoot();
		HuffmanTreeNode<CharInfo>* cur = root;

		LongType charCount = root->_w._count;

		string uncompressFilename = filename;
		uncompressFilename += ".uncompress";
		FILE* fin = fopen(uncompressFilename.c_str(), "wb");
		assert(fin);

		FILE* fout = fopen(CompressFilename.c_str(), "rb");
		assert(fout);

		int index= 7;
		char ch;
		fread(&ch, sizeof(ch), 1, fout);
		while (1)
		{
			char value = 1;
			value <<= index;
			--index;

			if (ch & value)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}

			if (cur->_left == NULL && cur->_right == NULL)
			{
				--charCount;
				fwrite(&(cur->_w._ch), sizeof(cur->_w._ch),1 , fin);
				cur = root;
			}

			if (index < 0)//ע��
			{
				fread(&ch, sizeof(ch), 1, fout);
				index = 7;
			}

			if (charCount == 0)
			{
				break;
			}

		}
	}
	
protected:

	void _GenerateHuffmanCode(HuffmanTreeNode<CharInfo>* root,string code)
	{
		if (root == NULL)
			return;

		if (root->_left == NULL && root->_right == NULL)
		{
			_infors[(unsigned char)root->_w._ch]._code = code;
			return;
		}

		_GenerateHuffmanCode(root->_left, code + '0');
		_GenerateHuffmanCode(root->_right, code + '1');
	}
protected:
	CharInfo _infors[256];
};

//ע�����һ���ַ������ 
//���ݶ���ļ�
//��ͬ��ʽ�ļ�
void testCompressFile()
{
	FileCompress fc;
	/*fc.UnCompress("input.compress");

	fc.Compress("hh.jpg");
	fc.UnCompress("hh.jpg.compress");*/

	fc.Compress("��.zpl");
	fc.UnCompress("��.zpl.compress");
}
=======

#include "Heap.h"

template<class >
>>>>>>> 9ed2c27b35d6c2e1b5a897a982181f2fe1e3e035
