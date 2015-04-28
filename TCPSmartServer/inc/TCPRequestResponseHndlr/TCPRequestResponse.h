/*
 * TCPRequestResponse.h
 *
 *  Created on: 27-Apr-2015
 *      Author: sjayasinghs
 */

#ifndef SRC_TCPREQUESTRESPONSEHNDLR_TCPREQUESTRESPONSE_H_
#define SRC_TCPREQUESTRESPONSEHNDLR_TCPREQUESTRESPONSE_H_

#include "TCPCommon.h"
#include <string.h>

using Poco::UUID;
using Poco::UUIDGenerator;

#define EXPECTED_STR "GETMESSAGE\n"
#define EXPECTED_CLOSE "BYE\n"
#define MESSAGE_STR  "The message is "
#define SEND_STR     "%s%s"

class TCPRequestResponse : public TCPServerConnection
{
public:
	TCPRequestResponse(const StreamSocket& socket);
	virtual ~TCPRequestResponse();

	void run(void);
	void getRandomString(string &str);

};


class TCPRequestHandlerFactory: public TCPServerConnectionFactory
{
public:
	TCPRequestHandlerFactory();
	virtual ~TCPRequestHandlerFactory();

	TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket);
	string m_telephonyPartner;
	string m_transactionId;

};


#endif /* SRC_TCPREQUESTRESPONSEHNDLR_TCPREQUESTRESPONSE_H_ */
