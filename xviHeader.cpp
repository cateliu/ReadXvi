#include"xviHeader.h"
#include <vector>

xviHeader::xviHeader()			//	Ĭ�Ϲ��캯��
{
	this->h = new XVIHANDLE;
	this->e = I_OK;
	this->filename = "";
}
xviHeader::xviHeader(string file) //	�вι���
{
	filename = file;
}
xviHeader::~xviHeader()
{
	XVI_Close(*(this->h));
}
bool xviHeader::OpenXvi(const char* file)			//	��xvi�ļ�
{

	cout << "-------------------------------------" << endl;
	cout << "-------------------------------------" << endl;
	filename = file;
	this->e = XVI_Open(this->h, file);
//	cout << "���ڴ��ļ�......" << endl;
	if (this->e == E_NOT_FOUND)
	{
		cout << "�޷��ҵ��ļ�����" << this->filename << "��" << endl;
	//	system("pause");
		return false;
	}
	else if (this->e == E_INVALID_FORMAT)
	{
		cout << "���ļ���������Ч��XVI��ʽ�ļ�����" << this->filename << "��" << endl;
	//	system("pause");
		return false;
	}
	else if (this->e == 2001)
	{
		cout << "���ļ�������" << this->filename << "��" << endl;
//		system("pause");
		return false;
	}
	else if (this->e == I_OK)
	{
		cout << "�ɹ����ļ�����" << this->filename << "��" << endl;
		return true;
	}
	else
	{
		cout << "���ļ�������" << this->filename << "��" << endl;
		return false;
	}
}
void xviHeader::OutputXvi(const char* file)		//	��ȡXvi�ļ�
{
	string fileName = file; 
	string phaseName = fileName + "phase.txt";
	fileName += ".txt";
	if (this->e == I_OK)
	{
		int resolution = 320 * 256;
		vector<int>	frame0(resolution), frame1(resolution), frame2(resolution), frame3(resolution);// , phase(resolution);

		unsigned long ulframeIdx = 0;

		word* frameBuffer = 0;
		dword size = XVI_GetFrameSize(*(this->h)) / 2;

		frameBuffer = new word[size];
		FILE* fileOP; 
		FILE* phaseOP;
		fileOP = fopen(fileName.c_str(), "w");
		phaseOP = fopen(phaseName.c_str(), "w");
		XviError e1;
		for (int i = 0; i < XVI_GetFrameCount(*(this->h)); i++)
		{
			e1 = XVI_GetFrame(*h, FT_NATIVE, i, frameBuffer, 1);
			if (e1 == I_OK)
			{
				if (i < XVI_GetFrameCount(*(this->h)) - 1)
				{
					printf("\r��ȡ��[%.2lf%%]:", i * 100.0 / (XVI_GetFrameCount(*(this->h)) - 1));
				}
				else
				{
					printf("\r��ȡ���[%.2lf%%]:", i * 100.0 / (XVI_GetFrameCount(*(this->h)) - 1));
				}
				for (int j = 1; j < i * 20 / (XVI_GetFrameCount(*(this->h))); j++)
				{
					cout << "��";
				}
				int frameIndex = i % 4;
				vector<int> frame(resolution);
				for (int j = 0; j < resolution; j++)
				{
					frame[j] = *(frameBuffer + j);
					fprintf(fileOP, "%d ", *(frameBuffer + j));
					
				}
				if (frameIndex == 0)
				{
					frame0 = frame;
				}
				else if (frameIndex == 1)
				{
					frame1 = frame;
				}
				else if (frameIndex == 2)
				{
					frame2 = frame;
				}
				else
				{
					frame3 = frame;
				}
				if (frameIndex == 3 && i > 0)
				{	
					for (int j = 0; j < resolution; j++)
					{
						double phase;
						phase = atan2(frame3[j] - frame1[j], frame0[j] - frame2[j]);
						fprintf(phaseOP, "%f ", phase);
					}
					fprintf(phaseOP, "\n");
				}
				fprintf(fileOP, "\n");
				
			}
		}
		cout << endl;
		
		::fclose(fileOP);
		::fclose(phaseOP);
		delete [] frameBuffer;
	}
}

void xviHeader::ShowInfo()
{
	if (e == I_OK)
	{

		printf("%12s: %d.%d\n", "Version", XVI_GetMajorversion(*h), XVI_GetMinorversion(*h));
		printf("%12s: %d x %d\n", "Resolution", XVI_GetWidth(*h), XVI_GetHeight(*h));
		printf("%12s: %d\n", "Bitsize", XVI_GetBitSize(*h));
		printf("%12s: %d\n", "Framesize", XVI_GetFrameSize(*h));
		printf("%12s: %0.0f\n", "Framerate", XVI_GetFrameRate(*h));
		printf("%12s: %d\n\n", "Framecount", XVI_GetFrameCount(*h));

		printf("%13s:%d\n", "EntryCount", XVI_GetEntryCount(*h));
		printf("%13s:%d\n\n", "PropertyCount", XVI_GetPropertyCount(*h));

	}

	
}
