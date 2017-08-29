#ifndef UEE_APPLICATION_H
#define UEE_APPLICATION_H


namespace uee
{
	namespace apps
	{

		struct Application
		{
			virtual void Run() = 0;
			virtual void Shutdown() = 0;
		};

	}
}

#endif