/** --------------------------------------------------------------------------
 *  echoServer.cpp
 *
 *  A basic example of how to implement a WebSocketServer.  Creats a WS server
 *  bound to port 8080.  It listens for connections, and when a message is 
 *  received, it echos the same message back to the client.
 *
 *  Author    : Jason Kruse <jason@jasonkruse.com> or @mnisjk
 *  Copyright : 2014
 *  License   : BSD (see LICENSE)
 *  -------------------------------------------------------------------------- 
 **/

#include <exception>
#include "../../WebSocketServer.h"

using namespace std;

// For any real project this should be defined separately in a header file
class EchoServer : public WebSocketServer
{
public: 
    EchoServer( int port );
    ~EchoServer( );
    virtual void onConnect(    int socketID                        );
    virtual void onMessage(    int socketID, const string& data    );
    virtual void onDisconnect( int socketID                        );
    virtual void   onError(    int socketID, const string& message );
};

int main( int argc, char **argv )
{
    EchoServer es = EchoServer( 8080 );
    es.run( );
}

EchoServer::EchoServer( int port ) : WebSocketServer( port )
{
}

EchoServer::~EchoServer( )
{
}


void EchoServer::onConnect( int socketID )
{
    cout << "New connection (id " << socketID << ")" << endl;
}

void EchoServer::onMessage( int socketID, const string& data )
{
    // Reply back with the same message
	try {
		cout << "Received: " << data << endl;
	}
	catch (exception e) {
		cerr << "Error while receiving data: " + *e.what() << endl;
	}
	cout << "try to send " << data << " to " << socketID << endl;
	try {
		this->send(socketID, data);
	}
	catch (exception e) {
		cerr << "Error while sending data: " + *e.what() << endl;
	}
}

void EchoServer::onDisconnect( int socketID )
{
    cout << "Disconnect" << endl;
}

void EchoServer::onError( int socketID, const string& message )
{
    cerr << "Error: " << message << endl;
}


