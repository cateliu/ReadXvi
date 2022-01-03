#include"xviHeader.h"
#include <vector>
#include <Eigen/Dense>
#include <fstream>
#include "phaseUnwrap/phaseUnwrap.h"
using Eigen::Matrix2d;
using Eigen::Matrix2f;
xviHeader::xviHeader()			//	默认构造函数
{
	this->h = new XVIHANDLE;
	this->e = I_OK;
	this->filename = "";
}
xviHeader::xviHeader(string file) //	有参构造
{
	filename = file;
}
xviHeader::~xviHeader()
{
	XVI_Close(*(this->h));
}
bool xviHeader::OpenXvi(const char* file)			//	打开xvi文件
{

	cout << "-------------------------------------" << endl;
	cout << "-------------------------------------" << endl;
	filename = file;
	this->e = XVI_Open(this->h, file);
//	cout << "正在打开文件......" << endl;
	if (this->e == E_NOT_FOUND)
	{
		cout << "无法找到文件。（" << this->filename << "）" << endl;
	//	system("pause");
		return false;
	}
	else if (this->e == E_INVALID_FORMAT)
	{
		cout << "该文件并不是有效的XVI格式文件，（" << this->filename << "）" << endl;
	//	system("pause");
		return false;
	}
	else if (this->e == 2001)
	{
		cout << "打开文件出错，（" << this->filename << "）" << endl;
//		system("pause");
		return false;
	}
	else if (this->e == I_OK)
	{
		cout << "成功打开文件！（" << this->filename << "）" << endl;
		return true;
	}
	else
	{
		cout << "打开文件出错，（" << this->filename << "）" << endl;
		return false;
	}
}
//#pragma optimize("", off)
void xviHeader::OutputXvi(const char* file)		//	读取Xvi文件
{
	string fileName = file;
	string phaseName = fileName + "phase.txt";
	string phaseUnName = fileName + "phaseUn.txt";
	fileName += ".txt";
	if (this->e == I_OK)
	{
		int resolution = 320 * 256;
		short* frame0 = new short[resolution];
		short* frame1 = new short[resolution];
		short* frame2 = new short[resolution];
		short* frame3 = new short[resolution];
		float* phase = new float[resolution];
		float* phaseUn = new float[resolution];
		//vector<float> phase1, phase2;
		unsigned long ulframeIdx = 0;

		word* frameBuffer = 0;
		dword size = XVI_GetFrameSize(*(this->h)) / 2;

		frameBuffer = new word[size];
		FILE* fileOP; 
		FILE* phaseOP;
		FILE* phaseUnOP;
		phaseUnOP = fopen(phaseUnName.c_str(), "w");
		fileOP = fopen(fileName.c_str(), "w");
		phaseOP = fopen(phaseName.c_str(), "w");
		XviError e1;
		for (int i = 0; i < XVI_GetFrameCount(*(this->h));  i++)
		{
			e1 = XVI_GetFrame(*h, FT_NATIVE, i, frameBuffer, 1);
			if (e1 == I_OK)
			{
				if (i < XVI_GetFrameCount(*(this->h)) - 1)
				{
					printf("\r读取中[%.2lf%%]:", i * 100.0 / (XVI_GetFrameCount(*(this->h)) - 1));
				}
				else
				{
					printf("\r读取完成[%.2lf%%]:", i * 100.0 / (XVI_GetFrameCount(*(this->h)) - 1));
				}
				for (int j = 1; j < i * 20 / (XVI_GetFrameCount(*(this->h))); j++)
				{
					cout << "█";
				}
				if (i % 20000 == 0  && i > 0)
				{
					fclose(phaseOP);
					fclose(fileOP);
					fclose(phaseUnOP);
					/*fileName.clear();
					phaseName.clear();
					phaseUnName.clear();*/
					
					fileName = file;
					phaseName = fileName + "phase_part" + to_string(i / 5000) + ".txt";
					phaseUnName = fileName + "phaseUn_part" + to_string(i / 5000) + ".txt";
					fileName = fileName + ".txt";
					//cout << fileName << " " << phaseUnName << " " << phaseName;
					//system("pause");
					fileOP = fopen(fileName.c_str(), "a");
					phaseOP = fopen(phaseName.c_str(), "a");
					phaseUnOP = fopen(phaseUnName.c_str(), "a");
					cout << fileName << " " << phaseUnName << " " << phaseName;
				}


				int frameIndex = i % 4;
				float* frame = new float[resolution];
				
				for (int j = 0; j < resolution; j++)
				{
					frame[j] = *(frameBuffer + j);
					fprintf(fileOP, "%d ", *(frameBuffer + j));
					if (frameIndex == 0)
					{
						frame0[j] = *(frameBuffer + j);
					}
					else if(frameIndex == 1)
					{
						frame1[j] = *(frameBuffer + j);
					}
					else if (frameIndex == 2)
					{
						frame2[j] = *(frameBuffer + j);
					}
					else if (frameIndex == 3)
					{
						frame3[j] = *(frameBuffer + j);
						float phase_temp = atan2(frame3[j] - frame1[j], frame0[j] - frame2[j]);
						phase[j] = phase_temp / TWOPI;
						//phase1.push_back(phase_temp);
						fprintf(phaseOP, "%f ", phase_temp);
					}
				}
				if (frameIndex == 3 && i > 0)
				{
					phaseUnwrap(phase, phaseUn);
					for (int i = 0; i < resolution; i++)
					{
						//phase2.push_back(phaseUn[i]);
						fprintf(phaseUnOP, "%f ", phaseUn[i]);
					}
					fprintf(phaseUnOP, "\n");
					fprintf(phaseOP, "\n");
				}
				fprintf(fileOP, "\n");
			}
		}
		//cout << endl;
		
		::fclose(fileOP);
		::fclose(phaseOP);
		delete [] frameBuffer;
	}
}
//#pragma optimize("", on)
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
