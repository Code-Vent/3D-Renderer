#ifndef UEE_MEMORY_H
#define UEE_MEMORY_H

#include"typedefs.h"

//These should be part of memory management i.e memory.h
#define UEE_FREE_PTR 0xCDCDCDCDU
#define UEE_NULL_PTR 0

namespace uee {

	namespace core
	{
		void* newPointerArray(UEEuint32 size);
		void deletePointerArray(void**mem);
		char* newCharArray(UEEuint32 size);
		void deleteCharArray(char* mem);
		void* newByteArray(UEEuint32 size);
		void deleteByteArray(void* mem);
		void* newFloatArray(UEEuint32 size);
		void deleteFloatArray(void*mem);
		void* newInt32Array(UEEuint32 size);
		void deleteInt32Array(void*mem);
		void* newInt16Array(UEEuint32 size);
		void deleteInt16Array(void*mem);
		UEEuint32 Ptrslen(void**ptrs);
		UEEuint32 FreePtrslen(void**ptrs);
		UEEuint32 UsedPtrslen(void**ptrs);
		extern UEEbool isFreePtr(void*);
		extern UEEbool isUsedPtr(void*);
	}
}
#endif
