#include "phaseUnwrap.h"

void phaseUnwrap(float* phase, float* phaseunwrap)
{
	int xsize = 320;
	int ysize = 256;
	int NumRes, i;
	unsigned char* bitflags = new unsigned char[xsize * ysize];

	/* maske data */
	for (int i = 0; i < 320 * 256; i++)
		bitflags[i] = 255;
	for (int i = 0; i < 320 * 256; i++)
		bitflags[i] = (!bitflags[i]) ? BORDER : 0;

	FattenMask(bitflags, BORDER, 1, xsize, ysize);


	/*	LOCATE AND PROCESS RESIDUES	*/
	/*	compute residues and store in bitflags array */
	NumRes = Residues(phase, bitflags, POS_RES, NEG_RES,
		BORDER, xsize, ysize);

	/*	GENERATE BRANCH CUTS	*/
	Dipole(bitflags, xsize, ysize, BRANCH_CUT);
	i = Residues(phase, bitflags, 0, 0, BORDER | BRANCH_CUT,
		xsize, ysize);
	int MaxCutLen = (xsize + ysize) / 2;
	GoldsteinBranchCuts(bitflags, MaxCutLen, NumRes, xsize, ysize,
		BRANCH_CUT);

	/* UNWRAP AROUND CUTS*/
	int k = 0;
	for (int i = 0; i < xsize * ysize; i++)
	{
		if (bitflags[i] && BRANCH_CUT)
			k++;
	}

	k = UnwrapAroundCuts(phase, bitflags, phaseunwrap, xsize, ysize, AVOID,
		0, NULL);
	for (k = 0; k < xsize * ysize; k++)
	{
		phaseunwrap[k] *= TWOPI;
	}
}