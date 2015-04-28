/*
 * TCPCommon.h
 *
 *  Created on: 27-Apr-2015
 *      Author: sjayasinghs
 */

#ifndef TCPCOMMON_H_
#define TCPCOMMON_H_

#define  CONFIG_PROPERTIES_FILE			"/var/opt/TCPSmartServer/config/TCPSmartServer.properties"
#define  LOG_ERROR_FILE					"/var/opt/TCPSmartServer/logs/TCPError.log"
#define  LOG_TRANSACTION_FILE			"/var/opt/TCPSmartServer/logs/TCPTransaction.log"
#define  TCP_LOG						"TCPErrorLog"
#define  TCP_TRANSACTION				"TCPTransactionLog"

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/ServerSocket.h"

#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPClientSession.h>

#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/FileChannel.h>
#include <Poco/SplitterChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>

#include <Poco/URI.h>
#include <Poco/StreamCopier.h>
using Poco::StreamCopier;
using Poco::Net::HTTPClientSession;

#include <iostream>

using namespace Poco::Net;
using Poco::PatternFormatter;
using Poco::AutoPtr;
using Poco::FormattingChannel;
using Poco::FileChannel;
using Poco::SplitterChannel;
using Poco::ConsoleChannel;
using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;


// MySQL Connectors.
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

using namespace std;

#endif /* TCPCOMMON_H_ */
