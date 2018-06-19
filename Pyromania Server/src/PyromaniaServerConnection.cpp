/*
 * PyromaniaServerConnection.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "PyromaniaServerConnection.h"
#include "Poco/StreamCopier.h"

using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;
using Poco::Net::SocketStream;

#include <iostream>

using namespace std;

PyromaniaServerConnection::PyromaniaServerConnection(const StreamSocket& s, World* w) : TCPServerConnection(s), sockIn(s), sockOut(s)
{
	world = w;
	player = 0;
}

PyromaniaServerConnection::~PyromaniaServerConnection()
{
	delete player;
}

void PyromaniaServerConnection::run()
{
	cout << "Request from " + this->socket().peerAddress().toString() << ": " << endl;

	socket().setKeepAlive(true);

	bool running = true;

	while (running == true) {

		if (!socket().poll(100, Poco::Net::Socket::SELECT_READ)) continue;

		char buffer[1024];
		sockIn >> buffer;

		if (strcmp(buffer, "GETSTATE") == 0){
			cout << "requested: GETSTATE" << endl;

			int mapSize    = 0;
			int playerSize = 0;
			int headerSize = 9 + 9 + 5; //header for map and for player and for end

			player = new Player();
			world->spawnPlayer(player);

			char* serializedTileMap = world->getMap()->serialize(&mapSize);
			char* serializedPlayer = player->serialize(&playerSize);

			int size = mapSize + playerSize + headerSize;

			cout << "Size: " << size << endl;
			cout << "mapSize: " << mapSize << endl;
			cout << "playerSize: " << playerSize << endl;
			cout << "headerSize: " << headerSize << endl;

			char* data = new char[size];
			char* p = data;

			/* send the Map */
			memcpy(p, "MAP\r\n", 5);
			p += 5;
			memcpy(p, (char*) &mapSize, sizeof(int));
			p += sizeof(int);
			memcpy(p, serializedTileMap, mapSize);

			socket().sendBytes(data, mapSize + 5 + sizeof(int));

			cout << "Sent player and complete TileMap with: " << endl;
			cout << "w: " << world->getMap()->getWidth() << endl << "h: " << world->getMap()->getHeight() << endl;
			cout << "mapSize: " << mapSize << endl;

			p = data;
			/* send the entity */
			memcpy(p, "YOU\r\n", 5);
			p += 5;
			memcpy(p, (char*) &playerSize, sizeof(int));
			p += sizeof(int);
			memcpy(p, serializedPlayer, playerSize);
			p += playerSize;
			socket().sendBytes(data, playerSize + 9);

			cout << "Sent player: " << data << endl;

			/* send end */
			strcpy(p, "END\r\n");
			socket().sendBytes(p, 5);

			cout << "Sent end" << endl;

		} else if (strcmp(buffer, "SETNAME") == 0) {
			sockIn >> buffer;
			std::string dt("Changing name to ");
			dt = dt + buffer + "the\r\n";
			socket().sendBytes(dt.data(), (int) dt.length());
		} else if (strcmp(buffer, "UPD") == 0){
			char buff[8+5];
			float x = player->getX();
			float y = player->getY();
			memcpy(buff, (char*)"UPD\r\n", 5);
			memcpy(buff+5, &x, sizeof(float));
			memcpy(buff+5+sizeof(float), &y, sizeof(float));

			socket().sendBytes(buff, 5 + 2*sizeof(float));
		} else if (strcmp(buffer, "DIR") == 0){
			int dir;
			sockIn>> dir;
			player->setDirection(dir);
		} else if (strcmp(buffer, "LOADMAP") == 0){
			sockIn >> buffer;
			string dt("You don't have permission to load ");
			dt = dt + buffer + "\r\n";
			socket().sendBytes(dt.data(), (int) dt.length());
		} else if (strcmp(buffer, "DC") == 0){
			running = false;
			break;
		}

		sockIn.clear();
		sockOut.flush();
	}

	cout << "Socket became unavailable..."<< endl;

}
