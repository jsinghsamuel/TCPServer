/*
 * TCPDemoServer.cpp
 *
 *  Created on: 27-Apr-2015
 *      Author: sjayasinghs
 */

#include "TCPServer/TCPDemoServer.h"

TCPDemoServer::TCPDemoServer() :  _helpRequested(false)
{
	m_port_number = PORT_NUM;
	m_poco_threads = MAX_POCO_THREADS;
	m_max_listen_queue = MAX_LISTEN_QUEUE;
}

TCPDemoServer::~TCPDemoServer() {
	// TODO Auto-generated destructor stub
}

void TCPDemoServer::initialize(Application& self)
{
	loadConfiguration(CONFIG_PROPERTIES_FILE);

	AutoPtr<Poco::FileChannel> rtErrorLogger(new Poco::FileChannel(LOG_ERROR_FILE));

	rtErrorLogger->setProperty("rotation", "1 days");
	rtErrorLogger->setProperty("archive", "timestamp");
	rtErrorLogger->setProperty("compress", "true");
	rtErrorLogger->setProperty("rotateOnOpen", "true");

	//"%d-%m-%Y %H:%M:%S: %t"
	AutoPtr<Poco::Formatter> formatter(new PatternFormatter("%N-%d-%m-%Y %H:%M:%S %s: %t"));
	formatter->setProperty("times", "local");

	AutoPtr<Poco::Channel> formattingChannel(new FormattingChannel(formatter, rtErrorLogger));

    Poco::Logger& sLog = Poco::Logger::create(TCP_LOG, formattingChannel, Poco::Message::PRIO_TRACE);
    sLog.setChannel(formattingChannel);

	AutoPtr<Poco::FileChannel> rtTransactionLogger(new Poco::FileChannel(LOG_TRANSACTION_FILE));

	rtTransactionLogger->setProperty("rotation", "1 days");
	rtTransactionLogger->setProperty("archive", "timestamp");
	rtTransactionLogger->setProperty("compress", "true");
	rtTransactionLogger->setProperty("rotateOnOpen", "true");

	//"%d-%m-%Y %H:%M:%S: %t"
	AutoPtr<Poco::Channel> formattingTransactionChannel(new FormattingChannel(formatter, rtTransactionLogger));

    Poco::Logger& tLog = Poco::Logger::create(TCP_TRANSACTION, formattingTransactionChannel, Poco::Message::PRIO_TRACE);
    tLog.setChannel(formattingTransactionChannel);

	ServerApplication::initialize(self);
}

void TCPDemoServer::uninitialize()
{
	ServerApplication::uninitialize();
}

void TCPDemoServer::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
	Option("help", "h", "display argument help information")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<TCPDemoServer>(
			this, &TCPDemoServer::handleHelp)));

	options.addOption(
	Option("portnumber", "p", "Port Number for the Server to run.")
			.required(false)
			.repeatable(false)
			.argument("p")
			.callback(OptionCallback<TCPDemoServer>(
				this, &TCPDemoServer::handlePortNumber)));

	options.addOption(
	Option("queue", "q", "Maximum listen queue for the Server to run, default: 4096.")
			.required(false)
			.repeatable(false)
			.argument("q")
			.callback(OptionCallback<TCPDemoServer>(
				this, &TCPDemoServer::handleListenQueue)));

	options.addOption(
	Option("threads", "t", "Poco threads to handle Server connections, default: 1000")
			.required(false)
			.repeatable(false)
			.argument("p")
			.callback(OptionCallback<TCPDemoServer>(
				this, &TCPDemoServer::handlePocoThreads)));
}

void TCPDemoServer::handlePortNumber(const std::string& name,
                const std::string& value)
{
	short int portNumber = atoi(value.c_str());

	if (portNumber > 0)
	{
		m_port_number = portNumber;
	}
}

void TCPDemoServer::handlePocoThreads(const std::string& name,
                const std::string& value)
{
	short int pocoThreads = atoi(value.c_str());

	if (pocoThreads > 0)
	{
		m_poco_threads = pocoThreads;
	}
}

void TCPDemoServer::handleListenQueue(const std::string& name,
                const std::string& value)
{
	short int queue = atoi(value.c_str());

	if (queue > 0)
	{
		m_max_listen_queue = queue;
	}
}

void TCPDemoServer::handleHelp(const std::string& name,
                const std::string& value)
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("TCP Demo Program.");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
    _helpRequested = true;
}

int TCPDemoServer::main(const std::vector<std::string>& args)
{
	if (!_helpRequested)
	{
		int maxQueued  = config().getInt("MAX_LISTEN_QUEUE", 4096);
        int maxThreads = config().getInt("MAX_POCO_THREADS", 1000);

        ThreadPool::defaultPool().addCapacity(maxThreads);

        TCPServerParams* pParams = new TCPServerParams;
		pParams->setMaxQueued(maxQueued);
		pParams->setMaxThreads(maxThreads);

		ServerSocket svs(m_port_number);
		TCPServer srv(new TCPRequestHandlerFactory(), svs, pParams);

		Poco::Logger::get(TCP_LOG).information("TCPDemoServer::main: Started TCP Server with Port Number: %d.", m_port_number);

		srv.start();
		waitForTerminationRequest();
		srv.stop();
	}
	return Application::EXIT_OK;
}

int main(int argc, char** argv)
{
	TCPDemoServer app;
    return app.run(argc, argv);
}


