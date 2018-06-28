
#define ALLEGRO_NO_MAGIC_MAIN
#define ALLEGRO_USE_CONSOLE

#include <allegro.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool operator== (string s1, string s2){
	return (strcmp(s1.c_str(), s2.c_str()) == 0);
}

string itostr(int i){
	stringstream out;
	out << i;
	string s = out.str();
	return s;
}

int strtoi(string s){
	stringstream out;
	out << s;
	int i ;
	out >> i;
	return i;
}

void readmap (string data, int size, int* tiles){
	string buf = "";
	int num = 0;
	unsigned int i;
	
	for (i = 0; i < data.length(); i++){
		if (data.substr(i, 1) == ","){
			tiles[num] = strtoi(buf);
			buf = "";
			num++;
			continue;
		}
		buf += data.substr(i, 1);
	}

	/* got to add the last number which doesn't end with ',' */
	buf += data.substr(i, 1);
	num ++;

	if (num < size) 
		cout << "Didn't find enough data! (found " << num << "/" << size << ")"<< endl;

	return;
}

int main (int argc, char* arg[]){
	allegro_init();
	/*
	if (argc < 2){
		cout << "Error: to few arguments!" << endl;
		return 1;
	}

	if (!exists(arg[1])){
		cout << "Error: " << arg[1] << " doesn't exist!" << endl;
		return 1;
	}
	*/

	cout << "Opening " << "Map.dat" /*arg[1]*/ << "..." << endl;
	PACKFILE* file = pack_fopen("Map.dat", "rb");
	if (!file) {
		cout << "Error: Couldn't read Map.dat!" << endl;
	}
	
	char buf[5000];
	if (buf == NULL) cout << "Error: Unable to create Buffer!" << endl;

	string line;
	
	cout << "Reading..." << endl;

	while (pack_fgets(buf, sizeof(buf), file)) {
		#ifdef DEBUG
			cout << "Debug: Started new Line!" << endl;
		#endif
		
		line = buf;

		int* walkables;
		int walknum = 0;

		int* destructables;
		int destrnum = 0;

		if (line.substr(0, 8) == "walknum:"){
			walknum = strtoi(line.substr(8, line.length()));
			cout << "Map: Num of walkable tiles is " << walknum << " !" << endl;
		}
		if (line.substr(0, 9) == "destrnum:"){
			destrnum = strtoi(line.substr(9, line.length()));
			cout << "Map: Num of destructable tiles is " << destrnum << " !" << endl;
		}
		if (line.substr(0, 7) == "walkon:"){
			walkables = new int[walknum];
			readmap(line.substr(7, line.length()), walknum, walkables);
			cout << "Map: Walkable tiles part found!" << endl;
		} 
		if (line.substr(0, 9) == "destruct:"){
			destructables = new int[destrnum];
			readmap(line.substr(9, line.length()), destrnum, destructables);
			cout << "Map: Destructable tiles part found!" << endl;
		}

         	if (line.substr(0, 5) == "Name:"){
			string name = line.substr(5, line.length());
			string filename = name + ".map";
			cout << "Info: Found new map! Name is \"" << name << "\"!" << endl;
			
			PACKFILE* map = pack_fopen(filename.c_str(), "wb");

			int w, h;

			int* FG;
			int* BG;
			int* MG;

			while (pack_fgets(buf, sizeof(buf), file)) {
				line = buf;
				if (line.substr(0, 3) == "w: "){
					w = strtoi(line.substr(3, line.length()));
					cout << name << ": Width is " << w << "!" << endl;
				}
				if (line.substr(0, 3) == "h: "){
					h = strtoi(line.substr(3, line.length()));
					cout << name << ": Height is " << h << "!" << endl;
				}
				if (line.substr(0, 3) == "FG:"){
					FG = new int[w*h];
					readmap(line.substr(3, line.length()), w*h, FG);
					cout << name << ": Front part found!" << endl;
				}
				if (line.substr(0, 3) == "MG:"){
					MG = new int [w*h];
					readmap(line.substr(3, line.length()), w*h, MG);
					cout << name << ": Mid part found!" << endl;
				}
				if (line.substr(0, 3) == "BG:"){
					BG = new int[w*h];
					readmap(line.substr(3, line.length()), w*h, BG);
					cout << name << ": Back part found!" << endl;
				}
				if (line.substr(0, 8) == "endofmap") {
					cout << "End of " << name << "." << endl;
					break;
				}
			}	
			int mapsize = w*h;

			pack_iputl(w, map); 			//Width
			pack_iputl(h, map); 			//Heigth
			pack_iputl(walknum, map); 		//Num Of Walkable Tiles
			pack_fwrite(walkables, walknum*4, map); //Walkable Tiles
			pack_iputl(walknum, map); 		//Num Of Destructable Tiles
			pack_fwrite(walkables, walknum*4, map);	//Destructable Tiles
			pack_fwrite(BG, mapsize*4, map); 	//sizeof(BG\FG\MG) int is 4
			pack_fwrite(MG, mapsize*4, map);
			pack_fwrite(FG, mapsize*4, map);
			pack_fclose(map);

			cout << "Written new map: " << name << ".map!" << endl;
		}
      	}
	pack_fclose(file);
	cout << endl << "Thank you for using MapConv for Pyromania!" << endl << "(c) by Jonathan Hale 2012" << endl;
}
