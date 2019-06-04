#include <Windows.h>
#include <cuda_gl_interop.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
//#include <helper_math.h>
//#include "BezierDefines.h"

#define MAX_RAND 2147483647
//#define USE_PBO
#define MAXCHARVAL 0.00392156862745
#define DEBUG_DEVICES

#define DEBUGVRaa

#define uint unsigned int
#define MAX_X 2048
#define MAX_Y 2048
#define MAX_Y2 2048 / 4


// 0-255 color values
//texture<uchar4, cudaTextureType2D, cudaReadModeElementType> textureIn;
// 0.0-1.0 color values
//texture<uchar4, cudaTextureType2D,  cudaReadModeNormalizedFloat> textureIn;
__constant__ float PI = 3.1415926535;



__device__ int randCu(uint* seed) // 1 <= *seed < m
{
    uint const a = 16807; //ie 7**5
    uint const m = MAX_RAND; //ie 2**31-1

    *seed = (*seed * a)%m;
    return(*seed);
}


__global__ void vrtogCU
(
        float *positions,
        char *colors,
        int *seedmem,
        float incMov
#ifdef DEBUGVR
        uint *debugmem0,
        uint *debugmem1,
        uint *debugmem2,
        float *debugmemFloat0,
        float *debugmemFloat1,
        float *debugmemFloat2,
        char *debugmemChar0,
        char *debugmemChar1,
        char *debugmemChar2
#endif
)
{
    unsigned int m = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int n = blockIdx.y * blockDim.y + threadIdx.y;

    if(m < MAX_X && n < MAX_Y)
    {
        uint iIndex = (n * MAX_X) + m;
        uint iIndex1= iIndex * 3;// * 3;
        uint iIndex2= iIndex * 4;
  //  // Park-Miller Pseudorandom Number Generator (PRNG).
        unsigned int seed = seedmem[m];
        float randNum1 = ((float)randCu(&seed) / (float)MAX_RAND);
        float randNum2 = ((float)randCu(&seed) / (float)MAX_RAND);
        float randNum3 = ((float)randCu(&seed) / (float)MAX_RAND);
        float randomZ1 = incMov * randNum1;// * 1.0; // Generate the random number.
//        float randomZ2 = incMov * randNum2 * 3.0;
//        float randomZ3 = incMov * randNum3 * 2.0;
        seedmem[m] = seed;
		positions[iIndex1 + 0] = (float)(m - (MAX_X * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 1] = (float)(n - (MAX_Y * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 2] = randomZ1;// *0.5;//(m * 0.3) + randomZ1;
        colors[iIndex2+0] = (char)(randNum1 * 255);
        colors[iIndex2+1] = (char)(randNum2 * 255);
        colors[iIndex2+2] = (char)(randNum3 * 255);
        colors[iIndex2+3] = (char)(255);
#ifdef DEBUGVR
        int iBase = 1 * 2048;
        if(iIndex >= iBase && iIndex < (iBase + 256)){
//blockIdx.x * blockDim.x + threadIdx.x
            debugmem0[m] = iIndex;
            debugmem1[m] = iIndex1;
            debugmem2[m] = iIndex2;
            debugmemFloat0[m] = positions[iIndex1+0];
            debugmemFloat1[m] = positions[iIndex1+1];
            debugmemFloat2[m] = positions[iIndex1+2];
            debugmemChar0[m] = colors[iIndex2+0];
            debugmemChar1[m] = colors[iIndex2+1];
            debugmemChar2[m] = colors[iIndex2+2];
        }
#endif
    }
//*/
}

__device__ int randCu01(uint* seed) // 1 <= *seed < m
{
	uint const a = 16807; //ie 7**5
	uint const m = MAX_RAND; //ie 2**31-1

	*seed = (*seed * a) % m;
	return(*seed);
}


__global__ void vrtogCU01
(
	float *positions,
	char *colors,
	int *seedmem,
	float incMov,
	uint iPosStart,
	uint iColStart
#ifdef DEBUGVR
	uint *debugmem0,
	uint *debugmem1,
	uint *debugmem2,
	float *debugmemFloat0,
	float *debugmemFloat1,
	float *debugmemFloat2,
	char *debugmemChar0,
	char *debugmemChar1,
	char *debugmemChar2
#endif
)
{
	int m = blockIdx.x * blockDim.x + threadIdx.x;
	int n = blockIdx.y * blockDim.y + threadIdx.y;

	if (m < MAX_X && n < MAX_Y2)
	{
		//uint iIndex = (n * MAX_X) + m;
		//uint iIndex1 = 0;// iPosStart + (iIndex * 3);
		//uint iIndex2 = 0;// iColStart + (iIndex * 4);
		////  // Park-Miller Pseudorandom Number Generator (PRNG).
		//unsigned int seed = 1.0;// seedmem[m];
		//float randNum1 = ((float)randCu01(&seed) / (float)MAX_RAND);
		//float randNum2 = ((float)randCu01(&seed) / (float)MAX_RAND);
		//float randNum3 = ((float)randCu01(&seed) / (float)MAX_RAND);
//		float randomZ1 = incMov * randNum1;// * 1.0; // Generate the random number.
//        float randomZ2 = incMov * randNum2 * 3.0;
//        float randomZ3 = incMov * randNum3 * 2.0;
//		seedmem[m] = seed;
		//positions[iIndex1 + 0] = (float)(m - (MAX_X * 0.5));// *0.25;// * 0.3;
		//positions[iIndex1 + 1] = (float)(n - (MAX_Y2 * 0.5));// *0.25;// * 0.3;
		//positions[iIndex1 + 2] = randomZ1;// *0.5;//(m * 0.3) + randomZ1;
		//colors[iIndex2 + 0] = (char)255;// (randNum1 * 255);
		//colors[iIndex2 + 1] = (char)(randNum2 * 255);
		//colors[iIndex2 + 2] = (char)(randNum3 * 255);
		//colors[iIndex2 + 3] = (char)(255);
#ifdef DEBUGVR
		int iBase = 1 * 2048;
		if (iIndex >= iBase && iIndex < (iBase + 256)) {
			//blockIdx.x * blockDim.x + threadIdx.x
			debugmem0[m] = iIndex;
			debugmem1[m] = iIndex1;
			debugmem2[m] = iIndex2;
			debugmemFloat0[m] = positions[iIndex1 + 0];
			debugmemFloat1[m] = positions[iIndex1 + 1];
			debugmemFloat2[m] = positions[iIndex1 + 2];
			debugmemChar0[m] = colors[iIndex2 + 0];
			debugmemChar1[m] = colors[iIndex2 + 1];
			debugmemChar2[m] = colors[iIndex2 + 2];
		}
#endif
	}
	//*/
}


__device__ int randCu02(uint* seed) // 1 <= *seed < m
{
	uint const a = 16807; //ie 7**5
	uint const m = MAX_RAND; //ie 2**31-1

	*seed = (*seed * a) % m;
	return(*seed);
}


__global__ void vrtogCU02
(
	float *positions,
	char *colors,
	int *seedmem,
	float incMov,
	uint iPosStart,
	uint iColStart
#ifdef DEBUGVR
	uint *debugmem0,
	uint *debugmem1,
	uint *debugmem2,
	float *debugmemFloat0,
	float *debugmemFloat1,
	float *debugmemFloat2,
	char *debugmemChar0,
	char *debugmemChar1,
	char *debugmemChar2
#endif
)
{
	unsigned int m = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned int n = blockIdx.y * blockDim.y + threadIdx.y;

	if (m < MAX_X && n < MAX_Y2)
	{
		uint iIndex = (n * MAX_X) + m;
		uint iIndex1 = iPosStart + (iIndex * 3);
		uint iIndex2 = iColStart + (iIndex * 4);
		//  // Park-Miller Pseudorandom Number Generator (PRNG).
		unsigned int seed = seedmem[m];
		float randNum1 = ((float)randCu02(&seed) / (float)MAX_RAND);
		float randNum2 = ((float)randCu02(&seed) / (float)MAX_RAND);
		float randNum3 = ((float)randCu02(&seed) / (float)MAX_RAND);
		float randomZ1 = incMov * randNum1;// * 1.0; // Generate the random number.
//        float randomZ2 = incMov * randNum2 * 3.0;
//        float randomZ3 = incMov * randNum3 * 2.0;
		seedmem[m] = seed;
		positions[iIndex1 + 0] = (float)(m - (MAX_X * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 1] = (float)(n - (MAX_Y2 * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 2] = randomZ1;// *0.5;//(m * 0.3) + randomZ1;
		colors[iIndex2 + 0] = (char)(randNum1 * 255);
		colors[iIndex2 + 1] = (char)255;// (randNum2 * 255);
		colors[iIndex2 + 2] = (char)(randNum3 * 255);
		colors[iIndex2 + 3] = (char)(255);
#ifdef DEBUGVR
		int iBase = 1 * 2048;
		if (iIndex >= iBase && iIndex < (iBase + 256)) {
			//blockIdx.x * blockDim.x + threadIdx.x
			debugmem0[m] = iIndex;
			debugmem1[m] = iIndex1;
			debugmem2[m] = iIndex2;
			debugmemFloat0[m] = positions[iIndex1 + 0];
			debugmemFloat1[m] = positions[iIndex1 + 1];
			debugmemFloat2[m] = positions[iIndex1 + 2];
			debugmemChar0[m] = colors[iIndex2 + 0];
			debugmemChar1[m] = colors[iIndex2 + 1];
			debugmemChar2[m] = colors[iIndex2 + 2];
		}
#endif
	}
	//*/
}


__device__ int randCu03(uint* seed) // 1 <= *seed < m
{
	uint const a = 16807; //ie 7**5
	uint const m = MAX_RAND; //ie 2**31-1

	*seed = (*seed * a) % m;
	return(*seed);
}


__global__ void vrtogCU03
(
	float *positions,
	char *colors,
	int *seedmem,
	float incMov,
	uint iPosStart,
	uint iColStart
#ifdef DEBUGVR
	uint *debugmem0,
	uint *debugmem1,
	uint *debugmem2,
	float *debugmemFloat0,
	float *debugmemFloat1,
	float *debugmemFloat2,
	char *debugmemChar0,
	char *debugmemChar1,
	char *debugmemChar2
#endif
)
{
	unsigned int m = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned int n = blockIdx.y * blockDim.y + threadIdx.y;

	if (m < MAX_X && n < MAX_Y2)
	{
		uint iIndex = (n * MAX_X) + m;
		uint iIndex1 = iPosStart + (iIndex * 3);
		uint iIndex2 = iColStart + (iIndex * 4);
		//  // Park-Miller Pseudorandom Number Generator (PRNG).
		unsigned int seed = seedmem[m];
		float randNum1 = ((float)randCu03(&seed) / (float)MAX_RAND);
		float randNum2 = ((float)randCu03(&seed) / (float)MAX_RAND);
		float randNum3 = ((float)randCu03(&seed) / (float)MAX_RAND);
		float randomZ1 = incMov * randNum1;// * 1.0; // Generate the random number.
//        float randomZ2 = incMov * randNum2 * 3.0;
//        float randomZ3 = incMov * randNum3 * 2.0;
		seedmem[m] = seed;
		positions[iIndex1 + 0] = (float)(m - (MAX_X * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 1] = (float)(n - (MAX_Y2 * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 2] = randomZ1;// *0.5;//(m * 0.3) + randomZ1;
		colors[iIndex2 + 0] = (char)(randNum1 * 255);
		colors[iIndex2 + 1] = (char)(randNum2 * 255);
		colors[iIndex2 + 2] = (char)255;// (randNum3 * 255);
		colors[iIndex2 + 3] = (char)(255);
#ifdef DEBUGVR
		int iBase = 1 * 2048;
		if (iIndex >= iBase && iIndex < (iBase + 256)) {
			//blockIdx.x * blockDim.x + threadIdx.x
			debugmem0[m] = iIndex;
			debugmem1[m] = iIndex1;
			debugmem2[m] = iIndex2;
			debugmemFloat0[m] = positions[iIndex1 + 0];
			debugmemFloat1[m] = positions[iIndex1 + 1];
			debugmemFloat2[m] = positions[iIndex1 + 2];
			debugmemChar0[m] = colors[iIndex2 + 0];
			debugmemChar1[m] = colors[iIndex2 + 1];
			debugmemChar2[m] = colors[iIndex2 + 2];
		}
#endif
	}
	//*/
}


__device__ int randCu04(uint* seed) // 1 <= *seed < m
{
	uint const a = 16807; //ie 7**5
	uint const m = MAX_RAND; //ie 2**31-1

	*seed = (*seed * a) % m;
	return(*seed);
}


__global__ void vrtogCU04
(
	float *positions,
	char *colors,
	int *seedmem,
	float incMov,
	uint iPosStart,
	uint iColStart
#ifdef DEBUGVR
	uint *debugmem0,
	uint *debugmem1,
	uint *debugmem2,
	float *debugmemFloat0,
	float *debugmemFloat1,
	float *debugmemFloat2,
	char *debugmemChar0,
	char *debugmemChar1,
	char *debugmemChar2
#endif
)
{
	unsigned int m = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned int n = blockIdx.y * blockDim.y + threadIdx.y;

	if (m < MAX_X && n < MAX_Y2)
	{
		uint iIndex = (n * MAX_X) + m;
		uint iIndex1 = iPosStart + (iIndex * 3);
		uint iIndex2 = iColStart + (iIndex * 4);
		//  // Park-Miller Pseudorandom Number Generator (PRNG).
		unsigned int seed = seedmem[m];
		float randNum1 = ((float)randCu04(&seed) / (float)MAX_RAND);
		float randNum2 = ((float)randCu04(&seed) / (float)MAX_RAND);
		float randNum3 = ((float)randCu04(&seed) / (float)MAX_RAND);
		float randomZ1 = incMov * randNum1;// * 1.0; // Generate the random number.
//        float randomZ2 = incMov * randNum2 * 3.0;
//        float randomZ3 = incMov * randNum3 * 2.0;
		seedmem[m] = seed;
		positions[iIndex1 + 0] = (float)(m - (MAX_X * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 1] = (float)(n - (MAX_Y2 * 0.5));// *0.25;// * 0.3;
		positions[iIndex1 + 2] = randomZ1;// *0.5;//(m * 0.3) + randomZ1;
		colors[iIndex2 + 0] = (char)(randNum1 * 255);
		colors[iIndex2 + 1] = (char)128 + (randNum2 * 128);
		colors[iIndex2 + 2] = (char)255;// (randNum3 * 255);
		colors[iIndex2 + 3] = (char)(255);
#ifdef DEBUGVR
		int iBase = 1 * 2048;
		if (iIndex >= iBase && iIndex < (iBase + 256)) {
			//blockIdx.x * blockDim.x + threadIdx.x
			debugmem0[m] = iIndex;
			debugmem1[m] = iIndex1;
			debugmem2[m] = iIndex2;
			debugmemFloat0[m] = positions[iIndex1 + 0];
			debugmemFloat1[m] = positions[iIndex1 + 1];
			debugmemFloat2[m] = positions[iIndex1 + 2];
			debugmemChar0[m] = colors[iIndex2 + 0];
			debugmemChar1[m] = colors[iIndex2 + 1];
			debugmemChar2[m] = colors[iIndex2 + 2];
		}
#endif
	}
	//*/
}

