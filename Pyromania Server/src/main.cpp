/*
 * main.cpp
 *
 *  Created on: 29.07.2013
 *      Author: Squareys
 */

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/Util.h"

#include "GameLogic/World.h"

#include "PyromaniaServerConnectionFactory.h"
#include <iostream>

using Poco::Net::ServerSocket;
using Poco::Net::TCPServer;
using Poco::Timestamp;
using namespace Poco::Util;

class PyromaniaServer: public Poco::Util::ServerApplication {
public:
	PyromaniaServer() :
			_helpRequested(false) {
		world = new World();
		world->setMap((char*)"Maps/Map6.map");

		//logger().information("Map6.map has been loaded.");
	}

	~PyromaniaServer() {
	}

protected:

	World* world;


	void initialize(Application& self) {
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}

	void uninitialize() {
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options) {
		ServerApplication::defineOptions(options);

		options.addOption(
				Option("help", "h",
						"display help information on command line arguments").required(
						false).repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value) {
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp() {
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader(
				"A server application that serves Pyromania Games to the Pyromania Clients.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args) {
		if (_helpRequested) {
			displayHelp();
		} else {
			// get parameters from configuration file
			unsigned short port = (unsigned short) config().getInt(
					"PyromaniaServer.port", 12345);

			// set-up a server socket
			ServerSocket svs(port);
			// set-up a TCPServer instance
			TCPServer srv(new PyromaniaServerConnectionFactory(world), svs);
			// start the TCPServer
			srv.start();
			// wait for CTRL-C or kill

			bool running = true;

			Timestamp ts = Timestamp();
			ts.update();

			while (running){

				if (world != NULL) {
					long ticksDiff = ts.elapsed();
					ts.update();

					world->update(ticksDiff);
				}

			}
			// Stop the TCPServer
			srv.stop();
		}
		return Application::EXIT_OK;
	}

private:
	bool _helpRequested;
};

int main(int argc, char** argv) {
	PyromaniaServer app;
	return app.run(argc, argv);
}

