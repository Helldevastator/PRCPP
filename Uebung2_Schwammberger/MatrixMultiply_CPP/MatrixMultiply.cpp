// MatrixMultiply.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Matrix.h"

int getPos(int x,int y, int width);
void multiply(jdouble* a,jdouble* b, jdouble* r,jint aheight, jint bWidth , jint aWidth) ;
void copyArr(jdouble* a,jdouble* b, jint len);

JNIEXPORT void JNICALL Java_Matrix_powerC(JNIEnv *env, jobject obj, jdoubleArray MatrixR, jint dim, jint pow)
{
	--pow;

	int len = dim*dim+1;
	jboolean isCopy = false;
	jdouble* a = env->GetDoubleArrayElements(MatrixR,&isCopy);
	jdouble* r1 = new jdouble[len];
	jdouble* r2 = new jdouble[len];
	copyArr(a,r1,len);		//memcpy doesn't seem to work properly
	
	for(int i = 0; i < pow;i++)
	{
		multiply(r1,a,r2,dim,dim,dim);
		jdouble* tmp = r1;
		r1 = r2;
		r2 = tmp;
	}

	//cpy back to original java array
	copyArr(r1,a,len);

	env->ReleaseDoubleArrayElements(MatrixR,a,0);
	delete[] r1;
	delete[] r2;
}

JNIEXPORT void JNICALL Java_Matrix_multiplyC(JNIEnv * env, jobject obj, jdoubleArray MatrixA, jdoubleArray MatrixB, jdoubleArray MatrixR, jint aheight, jint bWidth , jint aWidth) 
{
	jboolean isCopy;
	jdouble* a = env->GetDoubleArrayElements(MatrixA,&isCopy);
	jdouble* b = env->GetDoubleArrayElements(MatrixB,&isCopy);
	jdouble* r = env->GetDoubleArrayElements(MatrixR,&isCopy);

	multiply(a,b,r,aheight,bWidth,aWidth);

	env->ReleaseDoubleArrayElements(MatrixA,a,JNI_ABORT);
	env->ReleaseDoubleArrayElements(MatrixB,b,JNI_ABORT);
	env->ReleaseDoubleArrayElements(MatrixR,r,0);
}

int getPos(int x, int y, int width)
{
	return y*width + x;
}

void multiply(jdouble* a,jdouble* b, jdouble* r,jint aheight, jint bWidth , jint aWidth) 
{
	using namespace std;
	for(int i = 0;i < aheight;i++)
	{
		for(int j = 0; j < bWidth;j++)
		{
			double val = 0.0;

			for(int k = 0; k < aWidth;k++)
			{
				val += a[getPos(k, i,aWidth)] * b[getPos(j, k, bWidth)];
			}
			r[getPos(j,i,bWidth)] = val;
			
		}
	}
}

void copyArr(jdouble* a,jdouble* b, jint len)
{
	for(int i = 0;i < len;++i)
	{
		b[i] = a[i];
	}
}