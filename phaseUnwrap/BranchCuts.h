#pragma once
// pi.h
#define PI              3.141592653589793
#define TWOPI           6.28318530717959
//file.h
/*  exit codes  */
#define  BAD_USAGE                 10
#define  MEMORY_ALLOCATION_ERROR   20
#define  FILE_OPEN_ERROR           30
#define  FILE_READ_ERROR           31
#define  FILE_WRITE_ERROR          32
#define  FILE_CLOSE_ERROR          33
#define  BAD_PARAMETER            100
#define  BAD_DIMENSIONS           110
// util.h
#ifndef __UTIL
#define __UTIL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
typedef enum { IntegerParm, FloatParm, DoubleParm, StringParm }
CommandLineParmType;
void ErrorHandler(const char* msg, const char* item, int code);
//void OpenFile(FILE **fp, char *name, char *mode);
void AllocateByte(unsigned char** ptr, int len, const char* name);
void AllocateShort(short** ptr, int len, char* name);
void AllocateInt(int** ptr, int len, const char* name);
void AllocateFloat(float** ptr, int len, const char* name);
void AllocateDouble(double** ptr, int len, const char* name);
void ReadByte(FILE* fp, unsigned char* data, int len, char* name);
void ReadShort(FILE* fp, short* data, int len, char* name);
void ReadInt(FILE* fp, int* data, int len, char* name);
void ReadFloat(FILE* fp, float* data, int len, char* name);
void ReadDouble(FILE* fp, double* data, int len, char* name);
void WriteByte(FILE* fp, unsigned char* data, int len, char* name);
void WriteShort(FILE* fp, short* data, int len, char* name);
void WriteInt(FILE* fp, int* data, int len, char* name);
void WriteFloat(FILE* fp, float* data, int len, char* name);
void WriteDouble(FILE* fp, double* data, int len, char* name);
void AverageByteToFloat(unsigned char* in, float* out, int tsize,
    int xsize, int ysize);
//void SaveFloatToImage(float *data, char *what, char *filename,
//          int xsize, int ysize, int neg, int binary, int logflag);
//void SaveByteToImage(unsigned char *im, char *what, char *filename,
//          int xsize, int ysize, int neg, int binary, int mask_code);
int Keyword(char* string, char* keyword);
//int CommandLineParm(int argc, char *argv[], char *key,
//  CommandLineParmType type, void *ptr, int required, char *usage);
void PrintMinAndMax(int w, int h, float* soln, char* keyword);
#endif

/*
	brcut.h
*/

#ifndef __BRCUT
#define __BRCUT
void PlaceCut(unsigned char *array, int a, int b, int c, int d,
              int xsize, int ysize, int code);
int DistToBorder(unsigned char *bitflags, int border_code,
            int a, int b, int *ra, int *rb, int xsize, int ysize);
#endif

/*
	dipole.h
*/

#ifndef __DIPOLE
#define __DIPOLE
void Dipole(unsigned char *bitflags, int xsize, int ysize,
            int cut_code);
#endif

// extract.h
#ifndef __EXTRACT
#define __EXTRACT
void GetPhase(int in_format, FILE *ifp, char *in_file, float *phase,
              int xsize, int ysize);
void  ExtractPhase(int in_format, void *in_data, float *phase,
                   int xsize, int ysize, int status_flag);
#endif

// gold.h
#ifndef __GOLD
#define __GOLD
void GoldsteinBranchCuts(unsigned char *bitflags, int MaxCutLen,
                  int NumRes, int xsize, int ysize, int mask_code);
#endif

// grad.h
#ifndef __GRAD
#define __GRAD
float Gradient(float, float);
#endif
//list.h
#ifndef __LIST
#define __LIST
#define POS_RES     0x01   /* 1st bit */
#define NEG_RES     0x02   /* 2nd bit */
#define VISITED     0x04   /* 3rd bit */
#define ACTIVE      0x08   /* 4th bit */
#define BRANCH_CUT  0x10   /* 5th bit */
#define BORDER      0x20   /* 6th bit */
#define UNWRAPPED   0x40   /* 7th bit */
#define POSTPONED   0x80   /* 8th bit */
#define RESIDUE      (POS_RES | NEG_RES)
#define AVOID        (BRANCH_CUT | BORDER)
int GetNextOneToUnwrap(int *a, int *b, int *index_list,
                       int *num_index, int xsize, int ysize);
void UpdateList(float *qual_map, int x, int y, float val,
                float *phase, float *soln, unsigned char *bitflags,
                int xsize, int ysize, int *index_list,
                int *num_index, int ignore_code, int processed_code,
                int postponed_code, int max_list_size, 
                int dxdy_flag, float *min_qual);
void InsertList(float *soln, float val, float *qual_map,
                unsigned char *bitflags, int a, int b,
                int *index_list, int *num_index, int xsize,
                int ysize, int processed_code, int postponed_code,
                float *min_qual, int max_list_size);
#endif

// maskfat.h
#ifndef __MASKFAT
#define __MASKFAT
void FattenMask(unsigned char *mask, int mask_code, int thickness,
                int xsize, int ysize);
void FattenQual(float *qualmap, int thickness, int xsize,
                int ysize);
#endif

//path.h
#ifndef __PATH
#define __PATH
int UnwrapAroundCuts(float *phase, unsigned char *bitflags,
                 float *soln, int xsize, int ysize, int cut_code,
                 int debug_flag, char *infile);
#endif

// residues.h
#ifndef __RESIDUES
#define __RESIDUES
int Residues(float *phase, unsigned char *bitflags, int pos_code,
             int neg_code, int avoid_code, int xsize, int ysize);
#endif



