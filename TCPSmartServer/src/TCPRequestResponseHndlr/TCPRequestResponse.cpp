/*
 * TCPRequestResponse.cpp
 *
 *  Created on: 27-Apr-2015
 *      Author: sjayasinghs
 */

#include "TCPRequestResponseHndlr/TCPRequestResponse.h"

TCPRequestResponse::TCPRequestResponse(const StreamSocket& socket) : Poco::Net::TCPServerConnection(socket)
{
	// TODO Auto-generated constructor stub.

}

TCPRequestResponse::~TCPRequestResponse()
{
	// TODO Auto-generated destructor stub.

}

void TCPRequestResponse::getRandomString(string &str)
{
	// Creating the Transaction Id.
	Poco::UUIDGenerator& generator = Poco::UUIDGenerator::defaultGenerator();
	Poco::UUID uuid(generator.createRandom());	// Random Based
	Poco::UUID uuidextra(generator.createRandom());	// Random Based

	char sendBuffer[100]; // String length of (The message is ) + 50 + 1 character new line.

	memset(sendBuffer, '\0', sizeof(sendBuffer));

	int retLen = snprintf(sendBuffer, sizeof(sendBuffer), SEND_STR, uuid.toString().c_str(), uuidextra.toString().c_str());

	sendBuffer[retLen] = '\0';

	string random50Str(sendBuffer, 0, 49);

	str = MESSAGE_STR + random50Str + "\n";
}

void TCPRequestResponse::run()
{
	 Poco::Logger::get(TCP_LOG).information("TCPRequestResponse::run: New connection from %s.", socket().peerAddress().host().toString());

     bool isOpen = true;

     Poco::Timespan timeOut(10,0);
	 unsigned char incommingBuffer[1000];
	 char *recvMsgCheck = NULL;

	 string str;

	 while(isOpen)
	 {
		 if (socket().poll(timeOut,Poco::Net::Socket::SELECT_READ) == false)
		 {
		 }
		 else
		 {
			int nBytes = -1;

			 try
			 {
				 nBytes = socket().receiveBytes(incommingBuffer, sizeof(incommingBuffer));

				 if (nBytes > 0)
				 {
					 // Check if the content is GETMESSAGE
					 recvMsgCheck = strstr((char *)incommingBuffer, EXPECTED_STR);

					 if (recvMsgCheck != NULL)
					 {
						 // Got GETMESSAGE, get the ranRandomString.
						 getRandomString(str);
					 }
					 else
					 {
						 // Check for close message from client.
						 recvMsgCheck = strstr((char *)incommingBuffer, EXPECTED_CLOSE);

						 if (recvMsgCheck != NULL)
						 {
							 // Got Bye Closing Connections.
							 isOpen = false;
						 }
						 else
						 {
							 // Bad request from Client.
							 str = "Bad Request\n";
						 }
					 }

					 if (isOpen)
					 {
						 socket().sendBytes(str.c_str(), str.length());
					 }
				 }
			 }
			 catch (Poco::Exception& exc)
			 {
				 //Handle your network errors.
				 Poco::Logger::get(TCP_LOG).information("TCPRequestResponse::run: Network error: %s.", exc.displayText());
				 isOpen = false;
			 }


			 if (nBytes==0)
			 {
				 isOpen = false;
			 }
			 else
			 {
				 string incommingStr((char *)incommingBuffer);
				 Poco::Logger::get(TCP_LOG).information("TCPRequestResponse::run: Received Msg from Client: %s, message Send: %s", incommingStr, str);
			 }
		 }
	 }
	 Poco::Logger::get(TCP_LOG).information("TCPRequestResponse::run: Connection Closed.");
}

TCPRequestHandlerFactory::TCPRequestHandlerFactory()
{

}

TCPRequestHandlerFactory::~TCPRequestHandlerFactory()
{

}

TCPServerConnection* TCPRequestHandlerFactory::createConnection(const StreamSocket& socket)
{
	return new TCPRequestResponse(socket);
}
