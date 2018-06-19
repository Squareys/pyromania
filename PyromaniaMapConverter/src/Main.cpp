
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <cstring>

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

void readmap (string data, int size, short* tiles){
	string buf = "";
	int num = 0;
	unsigned int i;
	
	for (i = 0; i < data.length(); i++){
		if (data.substr(i, 1) == ","){
			tiles[num] = (short)strtoi(buf);
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
	cout << "Opening Map.dat..." << endl;
	FILE* file = fopen("Map.dat", "rb");

	if (file == NULL){
		cout << "Error: Map.dat doesn't exist!" << endl;
		return 1;
	}
	
	char buf[5000];
	if (buf == NULL) cout << "Error: Unable to create Buffer!" << endl; //Hahaha xD Yeah, sure, as if that's going to happen :P

	string line;
	
	cout << "Reading..." << endl;

	while (fgets(buf, sizeof(buf), file)) {
		#ifdef DEBUG
			cout << "Debug: Started new Line!" << endl;
		#endif
		
		line = buf;

		int tilesnum;

		short* walkables;
		int walknum = 0;

		short* destructables;
		int destrnum = 0;

		if (line.substr(0, 9) == "tilesnum:"){
			tilesnum = strtoi(line.substr(9, line.length()));
			cout << "Map: Num of tile types is " << tilesnum << "." << endl;
		}

		if (line.substr(0, 8) == "walknum:"){
			walknum = strtoi(line.substr(8, line.length()));
			cout << "Map: Num of walkable tiles is " << walknum << "." << endl;
		}

		if (line.substr(0, 9) == "destrnum:"){
			destrnum = strtoi(line.substr(9, line.length()));
			cout << "Map: Num of destructable tiles is " << destrnum << "." << endl;
		}

		if (line.substr(0, 7) == "walkon:"){
			walkables = new short[walknum];
			readmap(line.substr(7, line.length()), walknum, walkables);
			cout << "Map: Walkable tiles part found!" << endl;
		} 

		if (line.substr(0, 9) == "destruct:"){
			destructables = new short[destrnum];
			readmap(line.substr(9, line.length()), destrnum, destructables);
			cout << "Map: Destructable tiles part found!" << endl;
		}

        if (line.substr(0, 5) == "Name:"){
			string name = line.substr(5, line.length() - 7);
			string filename = name + ".map";
			cout << "Info: Found new map! Name is \"" << name << "\"!" << endl;
			
			FILE* map = fopen(filename.c_str(), "wb");

			int w, h;

			short* FG;
			short* BG;
			short* MG;

			while (fgets(buf, sizeof(buf), file)) {
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
					FG = new short[w*h];
					readmap(line.substr(3, line.length()), w*h, FG);
					cout << name << ": Front part found!" << endl;
				}
				if (line.substr(0, 3) == "MG:"){
					MG = new short[w*h];
					readmap(line.substr(3, line.length()), w*h, MG);
					cout << name << ": Mid part found!" << endl;
				}
				if (line.substr(0, 3) == "BG:"){
					BG = new short[w*h];
					readmap(line.substr(3, line.length()), w*h, BG);
					cout << name << ": Back part found!" << endl;
				}
				if (line.substr(0, 8) == "endofmap") {
					cout << "End of " << name << "." << endl;
					break;
				}
			}	

			int mapsize = w*h;

			fputc(w, map); 			//Width
			fputc(h, map); 			//Heigth
			fputc(tilesnum, map); //number of tileTypes
			fputc(walknum, map); 		//Num Of Walkable Tiles
			fwrite(walkables, 2, walknum, map); //Walkable Tiles
			fputc(destrnum, map); 		//Num Of Destructable Tiles
			fwrite(destructables, 2, destrnum, map);	//Destructable Tiles
			fwrite(BG, 2, mapsize, map); 	//sizeof(BG\FG\MG) int is 4
			fwrite(MG, 2, mapsize, map);
			fwrite(FG, 2, mapsize, map);
			fclose(map);

			cout << "Written new map: " << name << ".map!" << endl;
		}
    }

	fclose(file);
	cout << endl << "Thank you for using MapConv for Pyromania!" << endl << "(c) by Jonathan Hale 2012-2013" << endl;
}
