/* Program Name: Bitset Lab
 * Student Name: Clark Kirby
 * Program Description: Design a bitset class that can solve problems by
 *						using the bitwise opperator, such as clearing bits, 
 *						seting bits values, and checking those values.	*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class BITSET {
    vector<int> mSets;

  public:
    BITSET();
    bool Test(int index) const;
    void Set(int index);
    void Clear(int index);
    int GetNumSets() const;
    int GetSet(int index) const;
};


string ToBinary(int bit_set, int spacing = 4);



int main() {
    BITSET sets;
    string command;
    int which;
    do {
        cout << "> ";
        if (!(cin >> command) || "q" == command) {
            // If cin fails for any reason, it usually means
            // an EOF state, break and quit.
			break;
        }
        
        if ("t" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else { // simply test the bit
                cout << sets.Test(which) << '\n';
            }
        } else if ("s" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                sets.Set(which); // once again, simply set the bit
            }
        } else if ("g" == command) {
            int spacing;
            string line;
            getline(cin, line);
            istringstream sin{line};
            if (!(sin >> which)) {
                cout << "Invalid index\n";
            } else {
                if (!(sin >> spacing)) { // check to see if spacing is given, else automatically 4
                    spacing = 4;
                }
                cout << ToBinary(sets.GetSet(which), spacing) << '\n'; // cout the given set
            }
        } else if ("c" == command) {
			if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                sets.Clear(which); // clear set
            }
		} else if ("n" == command) { 
			int size = sets.GetNumSets();
			cout << size << endl;  
		} else {
            cout << "Unknown command '" << command << "'\n"; // check for garbage input
        }
    } while (true); // infinite loop til broken 
    return 0;
}




string ToBinary(int bit_set, int spacing) {
    string ret;
	BITSET sets;
    
    for (int i = 31;i >= 0;i--) { // count down the bits
		if (bit_set & (1 << i)) { // if the bit is a 1
            ret += '1';
        } else { // if it isnt one, its a zero
            ret += '0';
        }
        if (((32 - i) % spacing) == 0) { // find the spaces for specified spacing
			if(i != 0) { 
				ret += ' '; 
			} 
        }
    }
    return ret;
}


BITSET::BITSET() : mSets(1, 0) {}

bool BITSET::Test(int index) const {
    int which_set = index / 31; 
    int which_bit = index % 31; 
    
	if (which_set >= GetNumSets()) { // if the desired index is out of bounds
        return false;
    } 

	int set = mSets.at(which_set); 
	int mask = 1 << which_bit; // create bit mask for singular bit

    return ((set & mask) != 0); // apply mask to test
}


void BITSET::Set(int index) {
    int which_set = index / 32; 
    int which_bit = index % 32; 

	if(which_set >= mSets.size()) { // if the index of wanted bit is out of bounds, expand the set 
		mSets.resize((which_set + 1), 0); // set to size desired and fill with 0's
	}
    
	int mask = 1 << which_bit; // set the singular desired bit to 1

	mSets.at(which_set) |= mask; // apply

}


void BITSET::Clear(int index) {
    int which_set = index / 32;
    int which_bit = index % 32; 
    if (which_set < GetNumSets()) { // if we clear before the end of the sets
		int mask = ~(1 << which_bit);
        mSets.at(which_set) &= mask; 

		for ( int i = GetNumSets() - 1; i > 0; i--){ // truncate empty sets at the end of the sets
			if( mSets[i] == 0 ){
				mSets.pop_back();	
			} else { break; } 
		}
	}
}

int BITSET::GetNumSets() const { return static_cast<int>(mSets.size()); }

int BITSET::GetSet(int which_set) const {

	// Check to see if index exists
	if(which_set >= GetNumSets()){ // if out of bounds 
		return 0;
	}
	
    return mSets.at(which_set);
}
