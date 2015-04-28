/*
 * TCPServer.h
 *
 *  Created on: 27-Apr-2015
 *      Author: sjayasinghs
 */

#ifndef SRC_TCPSERVER_TCPSERVER_H_
#define SRC_TCPSERVER_TCPSERVER_H_

#include "TCPCommon.h"
#include "TCPRequestResponseHndlr/TCPRequestResponse.h"

#define PORT_NUM 		 8787
#define MAX_LISTEN_QUEUE 4096
#define MAX_POCO_THREADS 1000

class TCPDemoServer :public Poco::Util::ServerApplication
{
public:
	TCPDemoServer();
	virtual ~TCPDemoServer();

protected:
	 void initialize(Application& self);
	 void uninitialize();
	 void defineOptions(Poco::Util::OptionSet& options);
	 void handleHelp(const std::string& name, const std::string& value);
	 void handlePortNumber(const std::string& name, const std::string& value);
	 void handleListenQueue(const std::string& name, const std::string& value);
	 void handlePocoThreads(const std::string& name, const std::string& value);

	 int main(const std::vector<std::string>& args);

private:
	 bool _helpRequested;
	 short int m_port_number;
	 int m_max_listen_queue;
	 int m_poco_threads;
};

#endif /* SRC_TCPSERVER_TCPSERVER_H_ */
