#include "CommonLibrary.h"
#include "Server.h"

int main()
{
	Server server;

	if (server.Listen())
	{
		server.Run();
	}	
}