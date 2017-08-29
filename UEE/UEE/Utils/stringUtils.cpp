#include"stringUtils.h"


namespace uee
{
	namespace utils
	{

#define BUFFER_SIZE 1024

		struct StringFactory
		{
			struct Buffer
			{
				char mem[BUFFER_SIZE];
				unsigned free = BUFFER_SIZE;
				struct Buffer *nexbuffer = nullptr;
			}buffer;

			~StringFactory()
			{
				struct Buffer *curr, *next;
				curr = buffer.nexbuffer;
				while (curr)
				{
					next = curr->nexbuffer;
					delete curr;
					curr = next;
				}
			}

		}strFactory;


		unsigned MakeString(char* str, char** des, const char* delim)
		{
			static struct StringFactory::Buffer* curr = &strFactory.buffer;
			static char* pbuf = curr->mem;

			unsigned len = 0;
			char* s;

			s = strstr(str, delim);
			if (s)
				*s = 0;

			len = strlen(str);

			if (len > (BUFFER_SIZE / 2 - 1))
				return 0;

			if (len < curr->free)
			{
				strcpy_s(pbuf, curr->free, str);
				curr->free -= (len + 1);
				s = pbuf;
				pbuf += (len + 1);
			}
			else
			{
				curr->nexbuffer = new struct StringFactory::Buffer;
				curr = curr->nexbuffer;
				pbuf = curr->mem;
				strcpy_s(pbuf, curr->free, str);
				curr->free -= (len + 1);
				s = pbuf;
				pbuf += (len + 1);
			}
			*des = s;
			return len;
		}

	}

}