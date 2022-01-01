#include <stdio.h>
#include <math.h>
#include "BranchCuts.h"
#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include "ctype.h"
/*
 * util.c -- utility Functions: I/O, memory, etc.
 */

/* Print error message and exit */
void ErrorHandler(const char *msg, const char *item, int code)
{
  fprintf(stderr, "%s\nItem: %s\n", msg, item);
  exit(code);
}

/* open the file */
//void OpenFile(FILE **fp, char *name, char *mode)
//{
//  if ((*fp = fopen(name, mode))==NULL) 
//    ErrorHandler("Cannot open file", name, FILE_OPEN_ERROR);
//}

/* Search for the keyword in the string. If present, return 1. */
int Keyword(char *string, char *keyword)
{
  int  i, lenstr, lenkey;
  char str[500], key[500];
  lenstr = strlen(string);
  lenkey = strlen(keyword);
  if (lenstr != lenkey) return 0;
  str[lenstr] = key[lenstr] = 0;
  for (i=0; i<=lenstr; i++) 
    str[i] = tolower(string[i]);
  for (i=0; i<=lenstr; i++) 
    key[i] = tolower(keyword[i]);
  return (!strcmp(str, key));
}

/* Allocate array of bytes and initialize to zero. */
void AllocateByte(unsigned char **ptr, int len,const char *name)
{
  int i;
  *ptr = (unsigned char *) malloc(len*sizeof(unsigned char));
  if ((*ptr)==NULL) 
    ErrorHandler("Cannot allocate memory", name,
                 MEMORY_ALLOCATION_ERROR);
  for (i=0; i<len; i++) (*ptr)[i] = 0;
}

/* Allocate array of short integers  and initialize to zero. */
void AllocateShort(short **ptr, int len, char *name)
{
  int i;
  *ptr = (short *) malloc(len*sizeof(short));
  if ((*ptr)==NULL) 
    ErrorHandler((char*)"Cannot allocate memory", name,
                 MEMORY_ALLOCATION_ERROR);
  for (i=0; i<len; i++) (*ptr)[i] = 0;
}
 
/* Allocate array of integers and initialize to zero. */
void AllocateInt(int **ptr, int len, const char *name)
{
  int i;
  *ptr = (int *) malloc(len*sizeof(int));
  if ((*ptr)==NULL) 
    ErrorHandler((char*)"Cannot allocate memory", name, 
                 MEMORY_ALLOCATION_ERROR);
  for (i=0; i<len; i++) (*ptr)[i] = 0;
}
 
/* Allocate array of floats and initialize to zero. */
void AllocateFloat(float **ptr, int len, const char *name)
{
  int i;
  *ptr = (float *) malloc(len*sizeof(float));
  if ((*ptr)==NULL) 
    ErrorHandler((char*)"Cannot allocate memory", name,
                 MEMORY_ALLOCATION_ERROR);
  for (i=0; i<len; i++) (*ptr)[i] = 0.0;
}

/* Allocate array of doubles and initialize to zero. */
void AllocateDouble(double **ptr, int len, char *name)
{
  int i;
  *ptr = (double *) malloc(len*sizeof(double));
  if ((*ptr)==NULL) 
    ErrorHandler((char*)"Cannot allocate memory", name,
                 MEMORY_ALLOCATION_ERROR);
  for (i=0; i<len; i++) (*ptr)[i] = 0.0;
}

/* Read array of bytes */
void ReadByte(FILE *fp, unsigned char *data, int len, char *name)
{
  if (len != fread(data, sizeof(unsigned char), len, fp)) 
    ErrorHandler((char*)"File read error", name, FILE_READ_ERROR);
  fclose(fp);
}
 
/* Read array of short integers */
void ReadShort(FILE *fp, short *data, int len, char *name)
{
  if (len != fread(data, sizeof(short), len, fp))
    ErrorHandler((char*)"File read error", name, FILE_READ_ERROR);
  fclose(fp);
}
 
/* Read array of integers */
void ReadInt(FILE *fp, int *data, int len, char *name)
{
  if (len != fread(data, sizeof(int), len, fp))
    ErrorHandler((char*)"File read error", name, FILE_READ_ERROR);
  fclose(fp);
}
 
/* Read array of floats */
void ReadFloat(FILE *fp, float *data, int len, char *name)
{
  if (len != fread(data, sizeof(float), len, fp)) 
    ErrorHandler((char*)"File read error", name, FILE_READ_ERROR);
  fclose(fp);
}

/* Read array of double-precision floats */
void ReadDouble(FILE *fp, double *data, int len, char *name)
{
  if (len != fread(data, sizeof(double), len, fp)) 
    ErrorHandler((char*)"File read error", name, FILE_READ_ERROR);
  fclose(fp);
}
 
/* Write array of bytes */
void WriteByte(FILE *fp, unsigned char *data, int len, char *name)
{
  if (len != fwrite(data, sizeof(unsigned char), len, fp)) 
    ErrorHandler((char*)"File write error", name, FILE_WRITE_ERROR);
  fclose(fp);
}

/* Write array of short integers */
void WriteShort(FILE *fp, short *data, int len, char *name)
{
  if (len != fwrite(data, sizeof(short), len, fp)) 
    ErrorHandler((char*)"File write error", name, FILE_WRITE_ERROR);
  fclose(fp);
}

/* Write array of integers */
void WriteInt(FILE *fp, int *data, int len, char *name)
{
  if (len != fwrite(data, sizeof(int), len, fp)) 
    ErrorHandler((char*)"File write error", name, FILE_WRITE_ERROR);
  fclose(fp);
}

/* Write array of floats */
void WriteFloat(FILE *fp, float *data, int len, char *name)
{
  if (len != fwrite(data, sizeof(float), len, fp)) 
    ErrorHandler((char*)"File write error", name, FILE_WRITE_ERROR);
  fclose(fp);
}

/* Write array of doubles */
void WriteDouble(FILE *fp, double *data, int len, char *name)
{
  if (len != fwrite(data, sizeof(double), len, fp)) 
    ErrorHandler((char*)"File write error", name, FILE_WRITE_ERROR);
  fclose(fp);
}

/* Save an array of bytes in a file.  If neg = 1, reverse   */
/* the values (like photographic negative).  If binary = 1, */
/* save values as 0's and 255's (black and white binary     */
/* image).  If mask_code is not 0, then ignore the pixels   */
/* that are marked with the bits defined by mask_code.      */
//void SaveByteToImage(unsigned char *im, char *what, char *filename,
//           int xsize, int ysize, int neg, int binary, int mask_code)
//{
//  int  k;
//  FILE *fp;
//  unsigned char *out, mask;
//  printf("Saving %s to file %s\n", what, filename);
//  AllocateByte(&out, xsize*ysize, "byte array");
//  mask = (mask_code) ? mask_code : 0xFF;     /* bits all 1's */
//  for (k=0; k<xsize*ysize; k++) {
//    if (binary)
//      out[k] = ((neg && !(im[k]&mask)) 
//                       || (!neg && (im[k]&mask))) ? 255 : 0;
//    else
//      out[k] = (neg) ? 255 - (im[k]&mask) : (im[k]&mask);
//  }
//  OpenFile(&fp, filename, "w");
//  WriteByte(fp, out, xsize*ysize, filename);
//  free(out);
//}

/* Scale the floating-point array to 0-255 (byte array),    */
/* and then save values in a file.  If neg = 1, reverse     */
/* the values (like photographic negative).  If binary = 1, */
/* save values as 0's and 255's (black and white binary     */
/* image).  If logflag = 1, then perform a log-linear       */
/* scaling on the data (useful for "brightening" images).   */
void SaveFloatToImage(float *data, char *what, char *filename,
           int xsize, int ysize, int neg, int binary, int logflag)
{
  int  k;
  unsigned char *im;
  double  r, rmin, rmax, rscale;
  AllocateByte(&im, xsize*ysize, (char*)"byte array");
  for (rmin=1.0e+10, rmax=-1.0e+10, k=0; k<xsize*ysize; k++) {
    if (rmin > data[k]) rmin = data[k];
    if (rmax < data[k]) rmax = data[k];
  }
  if (logflag)
    r = (rmin==rmax) ? 1.0 : 255.0/log(1.0 + rmax - rmin);
  else
    r = (rmin==rmax) ? 1.0 : 255.0/(rmax - rmin);
  printf("Min & max of %s = %lf %lf\n", what, rmin, rmax);
  for (k=0; k<xsize*ysize; k++) 
    im[k] = (logflag) ? r*log(1.0 + data[k] - rmin) 
                                    : r*(data[k] - rmin);
  //SaveByteToImage(im, what, filename, xsize, ysize, neg, binary, 0);
  free(im);
}

/* Averages byte values and scale from 0-255 to 0-1.  Store      */
/* results in array "out".  tsize is size of averaging template. */
void AverageByteToFloat(unsigned char *in, float *out, int tsize,
                        int xsize, int ysize)
{
  int  hs, i, j, n, ii, jj, c, sum;
  double  scale=1.0/255.0;
  hs = tsize/2;
  for (j=0; j<ysize; j++) {
    for (i=0; i<xsize; i++) {
      for (n=0, sum=0.0, jj=j-hs; jj<=j+hs; jj++) {
        if (jj < 0 || jj > ysize - 1) continue;
        for (ii=i-hs; ii<=i+hs; ii++) {
          if (ii < 0 || ii > xsize - 1) continue;
          c = in[jj*xsize + ii];
          sum += c;
          ++n;
        }
      }
      out[j*xsize + i] = scale*sum/n;
    }
  }
}

/* Search for the keyword "key" in the command line arguments, */
/* then read the value into the variable pointed to by ptr.    */
/* If required = 1, exit if the parameter is not found.  Print */
/* the string "usage" in this case before exiting.             */
//int CommandLineParm(int argc, char *argv[], char *key, 
//  CommandLineParmType type, void *ptr, int required, char *usage)
//{
//  int  i, found=0;
//  for (i=1; i<argc; i++) {
//    if (Keyword(argv[i], key)) {
//      if (i < argc - 1) {
//        found = 1;
//        if (type==IntegerParm) 
//          sscanf(argv[i+1], "%d", (int *)ptr);
//        else if (type==FloatParm) 
//          sscanf(argv[i+1], "%f", (float *)ptr);
//        else if (type==DoubleParm) 
//          sscanf(argv[i+1], "%lf", (double *)ptr);
//        else if (type==StringParm) 
//          sscanf(argv[i+1], "%s", (char *)ptr);
//        break;
//      }
//      else {
//        fprintf(stderr, "Missing parameter value for %s\n",
//                argv[i]);
//        fprintf(stderr, "%s", usage);
//        exit(BAD_USAGE);
//      }
//    }
//  }
//  if (required && !found) {
//    fprintf(stderr, "Required parameter missing: %s\n", key);
//    fprintf(stderr, "%s", usage);
//    exit(BAD_USAGE);
//  }
//  return found;
//}

/* Compute and print the min & max of the array "soln". */
void PrintMinAndMax(int w, int h, float *soln, char *keyword)
{
  int   i, j;
  float rmin, rmax;
  printf("Finding min, max of %s...", keyword);
  rmin = rmax = soln[0];
  for (j=0; j<w*h; j++) {
    if (soln[j] > rmax) rmax = soln[j];
    if (soln[j] < rmin) rmin = soln[j];
  }
  printf("Min %f, max %f\n", rmin, rmax);
}

/*
 *   brcut.c -- functions for branch cutting
 */

 /* Place a branch cut in the bitflags array from pixel (a,b) */
/* to pixel (c,d).  The bit for the branch cut pixels is     */
/* given by the value of "code".                             */
void PlaceCut(unsigned char *array, int a, int b, int c, int d,
              int xsize, int ysize, int code)
{
  int  i, j, k, ii, jj, m, n, istep, jstep;
  double  r;

  /* residue location is upper-left corner of 4-square */
  if (c > a && a > 0) a++;
  else if (c < a && c > 0) c++;
  if (d > b && b > 0) b++;
  else if (d < b && d > 0) d++;

  if (a==c && b==d) {
    array[b*xsize + a] |= code;
    return;
  }
  m = (a < c) ? c - a : a - c;
  n = (b < d) ? d - b : b - d;
  if (m > n) {
    istep = (a < c) ? +1 : -1;
    r = ((double)(d - b))/((double)(c - a));
    for (i=a; i!=c+istep; i+=istep) {
      j = b + (i - a)*r + 0.5;
      array[j*xsize + i] |= code;
    }
  }
  else {   /* n < m */
    jstep = (b < d) ? +1 : -1;
    r = ((double)(c - a))/((double)(d - b));
    for (j=b; j!=d+jstep; j+=jstep) {
      i = a + (j - b)*r + 0.5;
      array[j*xsize + i] |= code;
    }
  }
  return;
}

/* Return the squared distance between the pixel (a,b) and the */
/* nearest border pixel.  The border pixels are encoded in the */
/* bitflags array by the value of "border_code".               */
int DistToBorder(unsigned char *bitflags, int border_code,
               int a, int b, int *ra, int *rb, int xsize, int ysize)
{
  int  besta, bestb, found, dist2, best_dist2;
  int  i, j, k, bs;
  *ra = *rb = 0;
  for (bs=0; bs<xsize + ysize; bs++) {
    found = 0;
    best_dist2 = 1000000;  /* initialize to large value */
    /* search boxes of increasing size until border pixel found */
    for (j=b - bs; j<=b + bs; j++) {
      for (i=a - bs; i<=a + bs; i++) {
        k = j*xsize + i;
        if (i<=0 || i>=xsize - 1 || j<=0 || j>=ysize - 1
              || (bitflags[k] & border_code)) {
          found = 1;
          dist2 = (j - b)*(j - b) + (i - a)*(i - a);
          if (dist2 < best_dist2) {
            best_dist2 = dist2;
            besta = i;
            bestb = j;
          }           
        }
      }
    }
    if (found) {
      *ra = besta;
      *rb = bestb;
      break;
    }
  }
  return best_dist2;
} 

/*
 *   grad.c -- function for computing phase derivative 
 *             (wrapped phase difference)
 */

/* return wrapped phase difference */
float Gradient(float p1, float p2)
{
  float  r;
  r = p1 - p2;
  if (r > 0.5) r -= 1.0;
  if (r < -0.5) r += 1.0;
  return r;
}

/*
 *   list.c -- functions for managing list of pixels to unwrap
 */

/* Returns 0 if no pixels left, 1 otherwise */
int GetNextOneToUnwrap(int *a, int *b, int *index_list,
                       int *num_index, int xsize, int ysize)
{
  int index;
  if (*num_index < 1) 
    return 0;   /* return if list empty */
  index = index_list[*num_index - 1];
  *a = index%xsize;
  *b = index/xsize;
  --(*num_index);
  return 1;
}

/* Insert new pixel into the list.  */
/* Note: qual_map can be NULL       */
void InsertList(float *soln, float val, float *qual_map, 
           unsigned char *bitflags, int a, int b, int *index_list,
           int *num_index, int xsize, int ysize, int processed_code,
           int postponed_code, float *min_qual, int max_list_size)
{
  int i, n, index, top, bot, mid;
  double  quality;

  index = b*xsize + a;
  quality = (qual_map) ? qual_map[index] : 0.0;
  if (~(bitflags[index] & postponed_code)) { 
    /* if not postponed, store new unwrapped value */
    if (soln) soln[index] = val;
  }
  else {
    /* if postponed, leave old value */
  }
  /* if quality is too low, postpone it */
  if (qual_map && min_qual && quality < *min_qual) {
    bitflags[index] |= postponed_code;
    return;
  }
  /* otherwise, add to list */
  if (!qual_map) {   /* don't order if qual_map is NULL */
    index_list[*num_index] = index;
    ++(*num_index);
  }
  else {
    /* insert in list in order from lowest to highest quality */
    n = *num_index;
    if (n < 1) {
      (*num_index) = 0;   /* will be incremented below */
      index_list[0] = index;
    }
    else {
      if (quality <= qual_map[index_list[0]]) {
        /* insert at top of list */
        for (i=n; i>0; i--) 
          index_list[i] = index_list[i-1];
        index_list[0] = index;
      }
      else if (quality > qual_map[index_list[n - 1]]) {
        /* insert at bottom */
        index_list[n] = index;
      }
      else {   /* insert in middle */
        top = 0;
        bot = n - 1;
        while (bot - top > 1) {
          mid = (top + bot)/2;
          if (quality <= qual_map[index_list[mid]])  bot = mid;
          else  top = mid;
        }
        for (i=n; i>top+1; i--) 
          index_list[i] = index_list[i-1];
        index_list[top+1] = index;
      }
    }
    ++(*num_index);
  }
  bitflags[index] |= processed_code;
  bitflags[index] &= (~postponed_code);

  /* trim list if it's too big, and increase the quality */
  if (qual_map && min_qual 
          && max_list_size > 0 && *num_index >= max_list_size) {
    n = 0.50*(*num_index);  /* discard 50% */
    for (i=0; i<n; i++) {
      bitflags[index_list[i]] |= postponed_code;
      bitflags[index_list[i]] &= (~processed_code);
    }
    for (i=0; i<*num_index - n; i++)
      index_list[i] = index_list[i + n];
    *num_index -= n;
    *min_qual = qual_map[index_list[0]];
  }

  return;
}

/* Insert the four neighboring pixels of the given pixel */
/* (x,y) into the list.  The quality value of the given  */
/* pixel is "val".                                       */
void UpdateList(float *qual_map, int x, int y, float val,
         float *phase, float *soln, unsigned char *bitflags,
         int xsize, int ysize, int *index_list, int *num_index,
         int ignore_code, int processed_code, int postponed_code, 
         int max_list_size, int dxdy_flag, float *min_qual)
{
  int    i, a, b, k, w;
  float  grad;
  a = x - 1;
  b = y;
  k = b*xsize + a;

  if (a >= 0 
        && !(bitflags[k] & (ignore_code | processed_code))) {
    w = y*xsize + x-1;
    grad = Gradient(phase[w], phase[w+1]);
    if (dxdy_flag && qual_map)
      qual_map[k] = -fabs(grad);
    InsertList(soln, val + grad, qual_map, bitflags, a, b,
               index_list, num_index, xsize, ysize, processed_code,
               postponed_code, min_qual, max_list_size);
  }

  a = x + 1;
  b = y;
  k = b*xsize + a;
  if (a < xsize 
        && !(bitflags[k] & (ignore_code | processed_code))) {
    w = y*xsize + x;
    grad = - Gradient(phase[w], phase[w+1]);
    if (dxdy_flag && qual_map)
      qual_map[k] = -fabs(grad);
    InsertList(soln, val + grad, qual_map, bitflags, a, b,
               index_list, num_index, xsize, ysize, processed_code,
               postponed_code, min_qual, max_list_size);
  }

  a = x;
  b = y - 1;
  k = b*xsize + a;
  if (b >= 0 
        && !(bitflags[k] & (ignore_code | processed_code))) {
    w = (y-1)*xsize + x;
    grad = Gradient(phase[w], phase[w+xsize]);
    if (dxdy_flag && qual_map) 
      qual_map[k] = -fabs(grad);
    InsertList(soln, val + grad, qual_map, bitflags, a, b,
               index_list, num_index, xsize, ysize, processed_code,
               postponed_code, min_qual, max_list_size);
  }

  a = x;
  b = y + 1;
  k = b*xsize + a;
  if (b < ysize 
        && !(bitflags[k] & (ignore_code | processed_code))) {
    w = y*xsize + x;
    grad = - Gradient(phase[w], phase[w+xsize]);
    if (dxdy_flag && qual_map) qual_map[k] = -fabs(grad);
    InsertList(soln, val + grad, qual_map, bitflags, a, b,
               index_list, num_index, xsize, ysize, processed_code, 
               postponed_code, min_qual, max_list_size);
  }
}

/*
 *   dipole.c -- function for finding dipoles and eliminating them
 */

/* Find the dipoles (adjoining residues of opposite sign) in   */
/* the bitflags array, remove them, and place branch cut.      */
/* The bits for the positive and negative residues are defined */
/* by POS_RES and NEG_RES (defined in brcut.h), while the      */
/* branch cut bits are defined by "branchcut_code".            */
void Dipole(unsigned char *bitflags, int xsize, int ysize,
            int branchcut_code)
{
  int  i, j, k, kk;
  // printf("Dipoles...\n");
  for (j=0; j<ysize; j++) {
    for (i=0; i<xsize; i++) {
      k = j*xsize + i;
      kk = 0;
      if ((bitflags[k] & POS_RES)) {
        if (i<xsize-1 && (bitflags[k+1] & NEG_RES)) kk=k+1;
        else if (j<ysize-1) {
          if ((bitflags[k+xsize] & NEG_RES)) kk=k+xsize;
        }
      }
      else if ((bitflags[k] & NEG_RES)) {
        if (i<xsize-1 && (bitflags[k+1] & POS_RES)) kk=k+1;
        else if (j<ysize-1) {
          if ((bitflags[k+xsize] & POS_RES)) kk=k+xsize;
        }
      }
      if (kk) {
        /*printf("Connecting dipoles %d,%d - %d,%d\n", i, j, kk%xsize,
               kk/xsize);*/
        PlaceCut(bitflags, i, j, kk%xsize, kk/xsize,
                 xsize, ysize, branchcut_code);
        bitflags[k] &= (~(RESIDUE)); 
        bitflags[kk] &= (~(RESIDUE)); 
      }
    }
  }
}

/*
 * extract.c -- extract phase from input data
 */

/*
 *  Get the phase data from the input data.  Allocate the temporary
 *  memory required and read the input file.
 *
 *  in_format = 0 for 8-byte complex data,
 *              1 for 4-byte complex data,
 *              2 for 1-byte phase data,
 *              3 for 4-byte float phase data
 *
 *  Output: normalized (0 - 1) phase values in array "phase" 
 */
void GetPhase(int in_format, FILE *ifp, char *infile, float *phase,
              int xsize, int ysize)
{
  void  *in_data;
  if (in_format==0)  /* floating-pt real & imaginary parts */
    AllocateFloat((float**)(&in_data), 2*xsize*ysize, (char*)"input data");
  else if (in_format==1)  /* short integer real & imaginary parts */
    AllocateShort((short**)(&in_data), 2*xsize*ysize, (char*)"input data");
  else if (in_format==2)  /* 1-byte (quantized) phase values */
    AllocateByte((unsigned char **)(&in_data), xsize*ysize,
        (char*)"input data");
  else                    /* floating-pt phase values */
    AllocateFloat((float **)(&in_data), xsize*ysize, (char*)"input data");

  printf("Reading input data...\n");
  if (in_format==1)      /* short int real and imaginary parts */
    ReadShort(ifp, (short *)in_data, 2*xsize*ysize, infile);
  else if (in_format==0) /* floating-pt real and imag parts */
    ReadFloat(ifp, (float *)in_data, 2*xsize*ysize, infile);
  else if (in_format==3) /* floating-pt phase */
    ReadFloat(ifp, (float *)in_data, xsize*ysize, infile);
  else                   /* 1-byte quantized phase */
    ReadByte(ifp, (unsigned char *)in_data, xsize*ysize, infile);

  ExtractPhase(in_format, in_data, phase, xsize, ysize, 1);
  free(in_data);
}

/* Extract the phase from the input data.  If status_flag is 0 */
/* then do not print any status.                               */
void ExtractPhase(int in_format, void *in_data, float *phase,
                  int xsize, int ysize, int status_flag)
{
  int            i, j;
  double         x, y, r, angle;
  static double  one_over_twopi = 1.0/TWOPI;
  static double  scale;
  float          *in8_data = (float*)in_data;
  short          *in4_data = (short*)in_data;
  unsigned char  *quantized_phase = (unsigned char*)in_data;
  float          *float_phase = (float*)in_data;
  if (in_format==0 || in_format==1) {
    for (j=0; j<ysize; j++) {
      if (status_flag && j%100==0) {
       // printf("%d ", j);
        fflush(stdout);
        if (j + 100 >= ysize) {}//printf("\n");
      }
      for (i=0; i<xsize; i++) {
        if (in_format==1) {
          x = in4_data[2*(j*xsize + i)];
          y = in4_data[2*(j*xsize + i) + 1];
        }
        else {
          x = in8_data[2*(j*xsize + i)];
          y = in8_data[2*(j*xsize + i) + 1];
        }
        r = sqrt((double)(x*x + y*y));
        r = (r==0.0) ? 0.0 : 1.0/r;
        x *= r;
        y *= r;
        angle = atan2((double)y, (double)x);
        if (angle < 0) angle += TWOPI;
        if (angle >= TWOPI) angle -= TWOPI;
        angle *= one_over_twopi;
        phase[j*xsize + i] = angle;
      }
    }
  }
  else if (in_format==2) {     /* quantized phase */
    scale = 1.0/256.0;
    for (j=0; j<xsize*ysize; j++) {
      phase[j] = quantized_phase[j]*scale;
    }
  }
  else {    /* 4-byte float phase */
    scale = one_over_twopi;
    for (j=0; j<xsize*ysize; j++) { 
      /* re-scale phase to interval (0,1) */
      phase[j] = float_phase[j]*scale;
    }
  }
}

/*
 * gold.c -- generate branch cuts by Goldstein's algorithm
 */

/* Goldstein's phase-unwrapping algorithm.  The bitflags store */
/* the masked pixels (to be ignored) and the residues and      */
/* accumulates other info such as the branch cut pixels.       */
void GoldsteinBranchCuts(unsigned char *bitflags, int MaxCutLen,
               int NumRes, int xsize, int ysize, int branchcut_code)
{
  int            i, j, k, ii, jj, kk, m, n, ri, rj;
  int            charge, boxctr_i, boxctr_j, boxsize, bs2;
  int            dist, min_dist, rim_i, rim_j, near_i, near_j;
  int            ka, num_active, max_active, *active_list;
  int            bench; 
  int            draw_cut_line;
  double         r;
  bench = ysize/100;
  if (bench < 1) bench = 1;
  if (MaxCutLen < 2) MaxCutLen = 2;
  max_active = NumRes + 10;
  AllocateInt(&active_list, max_active + 1, (char*)"book keeping data");
  /* branch cuts */
  //printf("Computing branch cuts\n");
  for (j=0; j<ysize; j++) {
    if (j%bench==0) {
    //  printf("%d ", j/bench);
    //  fflush(stdout);
    }
    for (i=0; i<xsize; i++) {
      k = j*xsize + i;
      if ((bitflags[k] & (POS_RES | NEG_RES))
               && !(bitflags[k] & VISITED)) {
        bitflags[k] |= VISITED;  /* turn on visited flag */
        bitflags[k] |= ACTIVE;   /* turn on active flag */
        charge = (bitflags[k] & POS_RES) ? 1 : -1;
        num_active = 0;
        active_list[num_active++] = k;
        if (num_active > max_active) num_active = max_active;
        for (boxsize = 3; boxsize<=2*MaxCutLen; boxsize += 2) {
          bs2 = boxsize/2;
          for (ka=0; ka<num_active; ka++) {
            boxctr_i = active_list[ka]%xsize;
            boxctr_j = active_list[ka]/xsize;
            for (jj=boxctr_j - bs2; jj<=boxctr_j + bs2; jj++) {
              for (ii=boxctr_i - bs2; ii<=boxctr_i + bs2; ii++) {
                kk = jj*xsize + ii;
                if (ii<0 || ii>=xsize || jj<0 || jj>=ysize) { 
                  continue;
                }
                else { 
                  if (ii==0 || ii==xsize-1 || jj==0 || jj==ysize-1
                        || (bitflags[kk] & BORDER)) {
                    charge = 0;
                    DistToBorder(bitflags, BORDER, boxctr_i,
                             boxctr_j, &ri, &rj, xsize, ysize);
                    PlaceCut(bitflags, ri, rj, boxctr_i, boxctr_j,
                             xsize, ysize, branchcut_code);
                  }
                  else if ((bitflags[kk] & (POS_RES | NEG_RES))
                                   && !(bitflags[kk] & ACTIVE)) {
                    if (!(bitflags[kk] & VISITED)) {
                      charge += (bitflags[kk] & POS_RES) ? 1 : -1;
                      bitflags[kk] |= VISITED;   /* set flag */
                    }
                    active_list[num_active++] = kk;
                    if (num_active > max_active) 
                           num_active = max_active;
                    bitflags[kk] |= ACTIVE;  /* set active flag */
                    PlaceCut(bitflags, ii, jj, boxctr_i, boxctr_j,
                             xsize, ysize, branchcut_code);
                  }
                  if (charge==0)
                    goto continue_scan;
                }  /* else */
              }   /* for (ii ... */
            }   /* for (jj ... */
          }  /* for (ka ... */  
        }   /* for (boxsize ... */  

        if (charge != 0) {   /* connect branch cuts to rim */
          min_dist = xsize + ysize;  /* large value */
          for (ka=0; ka<num_active; ka++) {
            ii = active_list[ka]%xsize;
            jj = active_list[ka]/xsize;
            if ((dist = DistToBorder(bitflags, BORDER,
                        ii, jj, &ri, &rj, xsize, ysize))<min_dist) {
              min_dist = dist;
              near_i = ii;
              near_j = jj;
              rim_i = ri;
              rim_j = rj;
            }
          } 
          PlaceCut(bitflags, near_i, near_j, rim_i, rim_j,
                   xsize, ysize, branchcut_code);
        } 
        continue_scan :
        /* mark all active pixels inactive */
        for (ka=0; ka<num_active; ka++) 
          bitflags[active_list[ka]] &= ~ACTIVE;  /* turn flag off */
      }  /* if (bitflags ... */
    }  /* for (i ... */
  }  /* for (j ... */
  //printf("\n");
  free(active_list);
  return;
} 

/*
 * maskfat.c -- fatten mask
 */

/* Fattens mask and border by "thickness" pixels */
void FattenMask(unsigned char *array, int mask_code, int thickness,
                int xsize, int ysize)
{
  int i, j, k, ii, jj, kk, t2=thickness;
  unsigned char *temp;
  if (t2 < 1) return;
  AllocateByte(&temp, xsize*ysize, (char*)"temp array");
  //unsigned char** ptr = NULL;
  //*ptr = new unsigned char[xsize * ysize];
  //for (i = 0; i < xsize * ysize; i++) (*ptr)[i] = 0;
  /*temp = *ptr;*/
  for (j=0; j<ysize; j++) {
    for (i=0; i<xsize; i++) {
      k = j*xsize + i;
      temp[k] = 0;
      for (jj=j-t2; jj<=j+t2 && !temp[k]; jj++) {
        for (ii=i-t2; ii<=i+t2 && !temp[k]; ii++) {
          kk = jj*xsize + ii;
          if (ii>=0 && ii<xsize && jj>=0 && jj<ysize 
                                     && (array[kk] & mask_code))
            temp[k] = 1;
        }
      }
    }
  }
  for (k=0; k<xsize*ysize; k++) {
    if (temp[k]) array[k] |= mask_code;
  }
  free(temp);
}

/* Fattens zero values in quality map by "thickness" pixels */
void FattenQual(float *qual_map, int thickness,
                int xsize, int ysize)
{
  int i, j, k, ii, jj, kk, t2=thickness;
  unsigned char *temp;
  if (t2 < 1) return;
  AllocateByte(&temp, xsize*ysize, (char*)"temp array");
  for (j=0; j<ysize; j++) {
    for (i=0; i<xsize; i++) {
      k = j*xsize + i;
      temp[k] = 0;
      for (jj=j-t2; jj<=j+t2 && !temp[k]; jj++) {
        for (ii=i-t2; ii<=i+t2 && !temp[k]; ii++) {
          kk = jj*xsize + ii;
          if (ii>=0 && ii<xsize && jj>=0 && jj<ysize 
                      && qual_map[kk]==0.0)
            temp[k] = 1;
        }
      }
    }
  }
  for (k=0; k<xsize*ysize; k++) {
    if (temp[k]) qual_map[k] = 0.0;
  }
  free(temp);
}

/*
 *   path.c -- function for unwrapping around cuts
 */

/* Unwrap the phase data (by Itoh's method) without crossing
 * any branch cuts.  Return number of disconnected pieces.
 */
int UnwrapAroundCuts(float *phase, unsigned char *bitflags, 
              float *soln, int xsize, int ysize, int cut_code,
              int debug_flag, char *infile)
{
  int  i, j, k, a, b, c, n, num_pieces=0;
  float  value;
  float  min_qual, small_val = -1.0E+10;
  int    num_index, max_list_size, bench, benchout;
  int    *index_list;
  int    unwrapped_code=UNWRAPPED, postponed_code = POSTPONED;
  int    avoid_code; 

  bench = xsize*ysize/100;
  if (bench < 1) bench = 1;
  benchout = 10*bench;
  min_qual = small_val;
  max_list_size = xsize*ysize; /* this size may be reduced */
  AllocateInt(&index_list, max_list_size + 1, 
      (char*)"bookkeeping list (index)");

  avoid_code = cut_code | unwrapped_code | BORDER;

  /* find starting point */
  n = 0;
  num_index = 0;
  for (j=0; j<ysize; j++) {
    for (i=0; i<xsize; i++) {
      k = j*xsize + i;
      if (!(bitflags[k] & avoid_code)) {
        bitflags[k] |= unwrapped_code;
        if (bitflags[k] & postponed_code)
          /* soln[k] already stores the unwrapped value */
          value = soln[k];
        else {
          ++num_pieces;
          value = soln[k] = phase[k];
        }
        UpdateList(NULL, i, j, value, phase, soln, bitflags, xsize,
                   ysize, index_list, &num_index, avoid_code,
                   unwrapped_code, postponed_code, max_list_size,
                   0, &min_qual);
        while (num_index > 0) {
          if (n%bench==0) {
           // printf("%d ", n/bench);
           // fflush(stdout);
            if (0 && debug_flag && n%benchout==0 && n>0) {
              char filename[300];
              static char file_num = 0;
              //sprintf(filename, "%s.fill-%d", infile, ++file_num);
              /*SaveByteToImage(bitflags, "fill path", filename,
                              xsize, ysize, 1, 1, avoid_code);*/
            }
          }
          ++n;
          if (!GetNextOneToUnwrap(&a, &b, index_list,
                                  &num_index, xsize, ysize))
            break;   /* no more to unwrap */
          c = b*xsize + a;
          bitflags[c] |= unwrapped_code;
          value = soln[c];        
          UpdateList(NULL, a, b, value, phase, soln, bitflags,
                     xsize, ysize, index_list, &num_index,
                     avoid_code, unwrapped_code, postponed_code,
                     max_list_size, 0, &min_qual);
        }
      }
    }
  }
  //printf("\n");
  free(index_list);
  /* unwrap branch cut pixels */
  for (j=1; j<ysize; j++) {
    for (i=1; i<xsize; i++) {
      k = j*xsize + i;
      if (bitflags[k] & cut_code) {
        if (!(bitflags[k-1] & cut_code)) 
          soln[k] = soln[k-1] + Gradient(phase[k], phase[k-1]);
        else if (!(bitflags[k-xsize] & cut_code))
          soln[k] 
             = soln[k-xsize] + Gradient(phase[k], phase[k-xsize]);
      }
    }
  }
  return num_pieces;
}

/*
 *   residues.c -- function for extracting residues from phase
 */

/* Detect residues in phase data and mark them as positive or  */
/* negative residues in the bitflags array.  Ignore the pixels */
/* marked with avoid_code in the bitflags araay.               */
int Residues(float *phase, unsigned char *bitflags, int posres_code,
             int negres_code, int avoid_code, int xsize, int ysize)
{
  int  i, j, k, NumRes=0;
  double  r;
  for (j=0; j<ysize - 1; j++) {
    for (i=0; i<xsize - 1; i++) {
      k = j*xsize + i;
      if (bitflags && ((bitflags[k] & avoid_code) 
           || (bitflags[k+1] & avoid_code)
             || (bitflags[k+1+xsize] & avoid_code)
                 || (bitflags[k+xsize] & avoid_code))) {
        continue; /* masked region: don't unwrap */
      }
      r = Gradient(phase[k+1], phase[k])
           + Gradient(phase[k+1+xsize], phase[k+1])
              + Gradient(phase[k+xsize], phase[k+1+xsize])
                 + Gradient(phase[k], phase[k+xsize]);
      if (bitflags) {
        if (r > 0.01) bitflags[k] |= posres_code;
        else if (r < -0.01) bitflags[k] |= negres_code;
      }
      if (r*r > 0.01) ++NumRes;
    }
  }
  return NumRes;
}

