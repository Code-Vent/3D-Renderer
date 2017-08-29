#include"memory.h"
#include<string.h>

namespace uee
{
	namespace core
	{
		void* newPointerArray(UEEuint32 size)
		{
			void** ppMem = new void*[size + 1];
			memset(ppMem, UEE_FREE_PTR, size*sizeof(void*));
			memset(ppMem + size, UEE_NULL_PTR, sizeof(void*));
			return ppMem;
		}

		void deletePointerArray(void**mem)
		{
			delete[] mem;
		}

		char * newCharArray(UEEuint32 size)
		{
			char* pMem = new char[size + 1];
			pMem[size] = UEE_NULL;
			return pMem;
		}

		void deleteCharArray(char * mem)
		{
			delete[] mem;
		}

		void * newByteArray(UEEuint32 size)
		{
			//TODO: Align memory
			char* pMem = new char[size];
			return pMem;
		}

		void deleteByteArray(void * mem)
		{
			delete[] mem;
		}

		void * newFloatArray(UEEuint32 size)
		{
			float* pMem = new float[size];
			memset(pMem, 0, size*sizeof(float));
			return pMem;
		}

		void deleteFloatArray(void * mem)
		{
			delete[] mem;
		}

		void * newInt32Array(UEEuint32 size)
		{
			UEEint32* pMem = new UEEint32[size];
			memset(pMem, 0, size*sizeof(UEEint32));
			return pMem;
		}

		void deleteInt32Array(void * mem)
		{
			delete[] mem;
		}

		void * newInt16Array(UEEuint32 size)
		{
			UEEint16* pMem = new UEEint16[size];
			memset(pMem, 0, size*sizeof(UEEint16));
			return pMem;
		}

		void deleteInt16Array(void * mem)
		{
			delete[] mem;
		}

		UEEuint32 Ptrslen(void**ptrs)
		{
			UEEuint32 len = 0;
			while ((*ptrs++ != UEE_NULL_PTR))
				++len;
			return len;
		}

		UEEuint32 FreePtrslen(void**ptrs)
		{
			UEEuint32 len = 0;
			while ((*ptrs != UEE_NULL_PTR))
			{
				if (isFreePtr(*ptrs++))
					++len;
			}
			return len;
		}

		UEEuint32 UsedPtrslen(void**ptrs)
		{
			UEEuint32 len = 0;
			while ((*ptrs != UEE_NULL_PTR))
			{
				if (isUsedPtr(*ptrs++))
					++len;
			}
			return len;
		}

		inline UEEbool isFreePtr(void *ptr)
		{
			return (UEEuint32)ptr == UEE_FREE_PTR;
		}

		inline UEEbool isUsedPtr(void * ptr)
		{
			return (UEEuint32)ptr != UEE_FREE_PTR;;
		}
	}
}