#include <iostream>
#include <vector>
#include "Client/XClient.h"

void main( )
{
	char cBuffer[15] = {0};
	XClient *pClient = NULL;
	std::vector< XClient * > oClients;
	for ( int i = 0; i < 5; i++ )
	{
		XClient *pClient = new XClient( i );
		if ( NULL != pClient )oClients.push_back( pClient );
	}
	std::vector< XClient * >::iterator iter = oClients.begin();
	for ( ; iter != oClients.end(); iter++ )
	{
		if ( (*iter)->Init() )
		{
			if ( !(*iter)->ConnectServer( "172.28.1.24", 5150 ) )
			{
				goto FINISH_ERROR;
			}
		}
	}

	for ( int i = 0; i < 1000; i++ )
	{
		for ( iter = oClients.begin(); iter != oClients.end(); iter++ )
		{
			pClient = *iter;
			std::string oMsg( "Send Msg by XClient[");
			itoa( i, cBuffer, 10 );
			oMsg.append( cBuffer );
			oMsg.append("]");
			char cBuffer[ 512 ];
			memcpy( cBuffer, oMsg.c_str(), oMsg.length() );
			pClient->SendData( cBuffer, 512 );
		}
	}

	for ( iter = oClients.begin(); iter != oClients.end(); iter++ )
	{
		pClient = *iter;
		printf( "Client [%d], send [%d] bytes\n", pClient->GetIndex(), pClient->GetSendBytes() );
	}
	//if ( oClient.Init() )
	//{
	//	if ( oClient.ConnectServer( "127.0.0.1", 5050 ) )
	//	{
	//		for ( int i = 0; i < 20; i++ )
	//		{
	//			std::string oMsg( "Send Message ");
	//			char *pTemp = itoa( i, cBuffer, 10 );
	//			oMsg.append( cBuffer );
	//			oClient.SendData( oMsg.c_str(), oMsg.length() );
	//		}
	//	}

	//}

FINISH_ERROR:
	std::system("pause");
}