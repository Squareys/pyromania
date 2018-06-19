/*
 * PyromaniaGameScene.cpp
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#include "PyromaniaGameScene.h"
#include "GameLogic/TileMap.h"

#include <iostream>
using namespace std;

using namespace irr;

using namespace gui;
using namespace core;
using namespace scene;
using namespace video;

IMeshSceneNode* playerModel = NULL;

//-----------------------------------------------
// Constructors of PyromaniaGameScene
//-----------------------------------------------
PyromaniaGameScene::PyromaniaGameScene(irr::scene::ISceneManager *sm, irr::gui::IGUIEnvironment* ge, Joypad* jp, ResourceManager* rm, Poco::Net::SocketAddress sa) : Scene(sm, ge, rm), socketAddress(sa), socket(), sockOut(socket), sockIn(socket) {
	try {
		socket.connect(socketAddress);
		socket.setKeepAlive(true);
		socket.setReceiveBufferSize(8192);
	} catch (...){
		cout << "[ERROR] Couldn't connect to Server" << endl;
	}

	//Get the current gameState from Server
	sockIn.clear();

	sockOut << "GETSTATE\r\n";
	sockOut.flush();

	world = new World();

	bool done = false;

	char* buffer = new char[1024];

	if (!sockIn.socket().poll(100, Poco::Net::Socket::SELECT_READ)) {
		cout << "unprepared" << endl;
	}

	while(!done){

		sockIn >> buffer;

		if (strcmp(buffer, "MAP") == 0){
			int size = 0;

			cout << sockIn.get() << ";" << endl;
			cout << sockIn.get() << ";" << endl;

			sockIn.read((char*) &size, sizeof(int));

			char* mapBuffer = new char[size];

			try {
				sockIn.read(mapBuffer, size);
			} catch(...) {
				cout << "(MAP) Exception!" << endl;
				break;
			}

			TileMap map = TileMap();
			map.deserialize(mapBuffer);

			cout << "Got Map with: " << endl << "w: " << map.getWidth() << endl << "h: " << map.getHeight() << endl;

			world->setMap(map);

		} else if (strcmp(buffer, "YOU") == 0){
			int size = 0;

			cout << sockIn.get() << ";" << endl;
			cout << sockIn.get() << ";" << endl;

			sockIn.read((char*) &size, 4);

			char* b = new char[size];

			try {
				sockIn.read(b, size);
			} catch(...) {
				cout << "(YOU) Exception!" << endl;
				break;
			}

			player = new Player();
			player->deserialize(b);

			world->spawnPlayer(player, player->getX(), player->getY());
		} else if (strcmp(buffer, "END") == 0){
			cout << "GOT the END" << endl;
			done = true;
			break;
		}
	}

	sockIn.clear();

	lastSendTime = -1;
	amount = 0;
	amountSent = 0;

	joypad = jp;
}

PyromaniaGameScene::~PyromaniaGameScene() {
	sockOut << "DC\r\n";
	sockOut.flush();

	socket.close();
}

//-----------------------------------------------
// Public Member Functions of PyromaniaGameScene
//-----------------------------------------------

void PyromaniaGameScene::update(int time){
	if (socket.poll(0, Poco::Net::Socket::SELECT_READ)){
		//Read something
		char buffer[1024];

		sockIn >> buffer;

		if (strcmp(buffer, "UPD") == 0){
			float x = 0;
			float y = 0;

			sockIn.get();
			sockIn.get();

			sockIn.read((char*) &x, sizeof(float));
			sockIn.read((char*) &y, sizeof(float));

			player->setPosition(x, y);
			sceneManager->getActiveCamera()->setTarget(vector3df(x, 0.0, y));
			playerModel->setPosition(vector3df(x, 0.0f, y));
		}
		cout << "[" << amount++ << "/" << amountSent << "] Received: " << buffer << endl;
	}

	lastSendTime += time;

	if ((lastSendTime == -1 || lastSendTime > 1000) && socket.poll(0, Poco::Net::Socket::SELECT_WRITE)){
		lastSendTime = 0;

		sockOut << "DIR\r\n" << player->getDirection();
		sockOut.flush();
		sockOut << "UPD\r\n";
		sockOut.flush();

		amountSent++;
	}

	handleInput();
}

void PyromaniaGameScene::prepare(){
	guiEnv->addStaticText(L"Hello World :)", rect<s32>(10, 10, 260, 50), false);

	TileMap* map = world->getMap();
	for (int x = 0; x < map->getWidth(); x++){
		for (int y = 0; y < map->getHeight(); y++){

			Tile tile = map->getTile(x, y);

			short id = (tile.type == NULL) ? -1 : tile.type->id;

			if (id == -1) continue;

			IMeshSceneNode* node = NULL;

			switch(id) {
			case TILE_BOX: node = sceneManager->addMeshSceneNode(resourceManager->mesh_box);
						break;
			case TILE_WALL_MID: node = sceneManager->addMeshSceneNode(resourceManager->mesh_mid);
						break;
			case TILE_CUL: node = sceneManager->addMeshSceneNode(resourceManager->mesh_corner);
						break;
			case TILE_CUR: node = sceneManager->addMeshSceneNode(resourceManager->mesh_corner);
						node->setRotation(vector3df(0.0, 90.0, 0.0));
						break;
			case TILE_CLR: node = sceneManager->addMeshSceneNode(resourceManager->mesh_corner);
						node->setRotation(vector3df(0.0, 180.0, 0.0));
						break;
			case TILE_CLL: node = sceneManager->addMeshSceneNode(resourceManager->mesh_corner);
						node->setRotation(vector3df(0.0, 270.0, 0.0));
						break;
			case TILE_EDL: node = sceneManager->addMeshSceneNode(resourceManager->mesh_edge);
						break;
			case TILE_EDU: node = sceneManager->addMeshSceneNode(resourceManager->mesh_edge);
						node->setRotation(vector3df(0.0, 90.0, 0.0));
						break;
			case TILE_EDR: node = sceneManager->addMeshSceneNode(resourceManager->mesh_edge);
						node->setRotation(vector3df(0.0, 180.0, 0.0));
						break;
			case TILE_EDD: node = sceneManager->addMeshSceneNode(resourceManager->mesh_edge);
						node->setRotation(vector3df(0.0, 270.0, 0.0));
						break;
			case TILE_WALL_H: node = sceneManager->addMeshSceneNode(resourceManager->mesh_wall);
						break;
			case TILE_WALL_V: node = sceneManager->addMeshSceneNode(resourceManager->mesh_wall);
						node->setRotation(vector3df(0.0, 90, 0.0));
						break;
			case TILE_WALL_CUL: node = sceneManager->addMeshSceneNode(resourceManager->mesh_wall_corner);
						break;
			case TILE_WALL_CUR: node = sceneManager->addMeshSceneNode(resourceManager->mesh_wall_corner);
						node->setRotation(vector3df(0.0, 90.0, 0.0));
						break;
			case TILE_WALL_CLR: node = sceneManager->addMeshSceneNode(resourceManager->mesh_wall_corner);
						node->setRotation(vector3df(0.0, 180.0, 0.0));
						break;
			case TILE_WALL_CLL: node = sceneManager->addMeshSceneNode(resourceManager->mesh_wall_corner);
						node->setRotation(vector3df(0.0, 270.0, 0.0));
						break;
			}

			if (node) {
				node->setMaterialFlag(EMF_LIGHTING, false);
				node->setMaterialTexture(0, resourceManager->texture_tiles);
				node->setPosition(vector3df(2.0 * x, 0.0, 2.0 * y));
			}
		}
	}


	/*
	 * add a node for entity:
	 */
	if ( player != NULL) {
		playerModel = sceneManager->addMeshSceneNode(resourceManager->mesh_guy, NULL, -1, vector3df(player->getX(), 0.0f, player->getY()));
		sceneManager->addCameraSceneNode(NULL, vector3df(25.0f, 9.0f, 6.0f), playerModel->getAbsolutePosition());
	} else {
		cout << "[ERROR] No entity" << endl;
	}

	ILightSceneNode* light = sceneManager->addLightSceneNode(0, vector3df(0.0, 1.0, 0.0));
	light->setLightType(ELT_DIRECTIONAL);
	sceneManager->setAmbientLight(video::SColorf(0.2f, 0.2f, 0.5f, 0.2f));
}

//-----------------------------------------------
// Private Member Functions of PyromaniaGameScene
//-----------------------------------------------

void PyromaniaGameScene::handleInput(){

	if (joypad->state(irr::KEY_KEY_W) > 0){
		cout << "W DOWN" << endl;
		player->setDirection(UP);
	} else if (joypad->state(irr::KEY_KEY_S) > 0){
		cout << "S DOWN" << endl;
		player->setDirection(DOWN);
	} else if (joypad->state(irr::KEY_KEY_A) > 0){
		cout << "A DOWN" << endl;
		player->setDirection(LEFT);
	} else if (joypad->state(irr::KEY_KEY_D) > 0){
		cout << "D DOWN" << endl;
		player->setDirection(RIGHT);
	} else {
		player->setDirection(STOP);
	}
}
