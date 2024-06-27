/* Program Name: Multi User Dungeons Program
 * Student Name: Clark Kirby
 * Program Description: BRIEF, Create a single user dungeons game
 *								with exits of multiple rooms that the
 *								player has to find and locate only by knowing
 *								the direction. */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

struct Room {
    int north = -1; // -1 means no room
    int south = -1;
    int east = -1;
    int west = -1;
    string name;
    string description;
};

// Take in a direction char, return the room index in that direction.
int getExit(const Room &room, const char direction) {
        switch (direction) {
        case 'n': return room.north;
			break;        
		case 'e': return room.east;
			break;
		case 's': return room.south;
			break;
        case 'w': return room.west;
			break;
		default: return -1; // no exit 
	}
}

// Take in a direction char and index and assign the exit to the room.
void setExit(Room &room, const char direction, const int roomIndex) {
        switch (direction) {
        case 'n': room.north = roomIndex;
				  break;
        case 'e': room.east = roomIndex;
				  break;
        case 's': room.south = roomIndex;
				  break;
        case 'w': room.west = roomIndex; 
				  break;  
		default: break; // just break if bad input
	}
}

// Take in a name and description and assign them to the room.
void setInfo(Room &room, const string &name, const string &description) {
    room.name = name; // simply setting the info for name and description
	room.description = description; 
}

// Print the room's name, description, and exits.
void look(const Room &room) {
	
	cout << room.name << endl;
	
	cout << room.description << endl << endl;
	
	cout << "Exits: ";
	bool first_direction = true; // find if we need a space after the input


	if(!(room.north == -1)){
		if(!(first_direction)){ cout << " "; first_direction = false; } // check if its the first one in the list
		cout << "n";
		first_direction = false;
	}
	if(!(room.south == -1)){
        if(!(first_direction)){ cout << " "; first_direction = false; }
        cout << "s";
		first_direction = false;
    }
	if(!(room.east == -1)){
        if(!(first_direction)){ cout << " "; first_direction = false; }
        cout << "e";
		first_direction = false;
    }
	if(!(room.west == -1)){
        if(!(first_direction)){ cout << " "; first_direction = false; }
        cout << "w";
		first_direction = false;
    }
	cout << endl;
}

// For debugging
void dumpRooms(const Room *const rooms, const size_t roomCount) {
    for (size_t i = 0; i < roomCount; ++i) {
        cout << "Room " << i << endl;
        cout << "  name: " << rooms[i].name << endl;
        cout << "  description: " << rooms[i].description << endl;
        cout << "  north: " << rooms[i].north << endl;
        cout << "  south: " << rooms[i].south << endl;
        cout << "  east:  " << rooms[i].east << endl;
        cout << "  west:  " << rooms[i].west << endl;
    }
}

// Removes whitespace inplace from the front and back of a string.
// "\n hello\n \n" -> "hello"
void stripWhitespace(string &str) {
    while (!str.empty() && isspace(str.back())) {
        str.pop_back();
    }
    while (!str.empty() && isspace(str.front())) {
        str.erase(str.begin());
    }
}

// Take in a char 'n', 's', 'e', or 'w' and return the full direction name.
string getDirectionName(const char direction) {
	switch (direction) {
		case 'vn': return "NORTH";
			break; 
		case 's': return "SOUTH";
			break;
		case 'e': return "EAST";
			break; 
		case 'w': return "WEST";
			break;
		default : return "ERROR";
	}
}

Room *loadRooms(const string dungeonFilename) {

	ifstream fin(dungeonFilename);
	if (!fin.is_open()){ // check if file is open
        cerr << "Error: failed to open file" << endl;
        exit(1);
    } 

    int tildeCount = 0;

	char x;
	while(fin.get(x)){ // read in file until it cant anymore 
		if(x == '~'){
			tildeCount ++; // count tildes for sections
		}
	}
	fin.clear(); // clear and restart file
	fin.seekg(0);

    size_t roomCount = tildeCount / 3;
    Room *rooms = new Room[roomCount]; // set our rooms


    // Read in the rooms
    for (size_t i = 0; i < roomCount; i++) {

		string line; 
		getline(fin, rooms[i].name, '~'); // first section seperated by tildes
        getline(fin, rooms[i].description, '~');
        getline(fin, line, '~');

		stripWhitespace(rooms[i].name); // clear white space between name and description 
		stripWhitespace(rooms[i].description);

        istringstream iss(line); // read in just the exits segment
        char direction;
        int roomNumber;
		
        while(iss >> direction >> roomNumber) { // read in the exits that the file gave
            switch (direction) {
                case 'n' : setExit(rooms[i], direction, roomNumber);
						   break;
				case 's' : setExit(rooms[i], direction, roomNumber);
						   break;
				case 'e' : setExit(rooms[i], direction, roomNumber);
						   break; 
				case 'w' : setExit(rooms[i], direction, roomNumber);
						   break;
			}
        }
    }
    fin.close(); // always close filestream
    
	dumpRooms(rooms, roomCount); // Debugging
    return rooms;
}



int main(int argc, char **argv) {
    
	if (argc < 2) {
        cerr << "Usage: ./mud filename" << endl;
        return 1;
    } // error check

	string filename = argv[1];
	Room* rooms = loadRooms(filename); // load rooms 

    int currentRoom = 0; // Start at room 0

    while (true) {

        char input;
        cout << "> ";
        cin >> input; // ask for input

        switch (input) {
			case 'q' : delete[] rooms; // quit
					return 0;
            
			case 'l' : //look
				look(rooms[currentRoom]);
				break;
			
			case 'n' :
			case 's' :
			case 'e' :
			case 'w' :
				if(getExit(rooms[currentRoom], input) != -1){
					currentRoom = getExit(rooms[currentRoom], input);
					cout << "You moved " << getDirectionName(input) << "." << endl; 
				}
				else{ cout << "You can't go " << getDirectionName(input) << "!" << endl; } 
				break;
			default : break;
        }
    }
}
