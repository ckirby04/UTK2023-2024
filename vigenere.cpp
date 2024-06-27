/* Program Name: Vigenere Cipher program
 * Student Name: Clark Kirby
 * Program Description: Similar to the ceasar cipher, comuter a
 *						propgram to decode a cipher that was 
 *						coded with a key and the vigenere cipher. */

#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

const size_t ALPHABET_SIZE = 26;

class VigenereCipher {
  private:
    string mKey = argv[2];
    char mVTable[ALPHABET_SIZE][ALPHABET_SIZE];
    string fileToString(const string inputFile) const;
    void stringToFile(const string message, const string outputFile) const;
    string makeKeystream(const string message) const;

  public:
    VigenereCipher(const string key);
    void encrypt(const string inputFile, const string outputFile) const;
    void decrypt(const string inputFile, const string outputFile) const;
    void printVTable() const;
};


string VigenereCipher::fileToString(const string inputFile) const {
    ifstream fin(inputFile);
    string message;
    char character;
    if (!fin.is_open()) {
        cerr << "file " << inputFile << " unable to open." << endl;
        exit(1);
    }
    while (fin.get(character)) {
        message.push_back(character);
    }
    fin.close();
    return message;
}



void VigenereCipher::stringToFile(const string message,
                                  const string outputFile) const {
    ofstream fout(outputFile);
    if (!fout.is_open()) {
        cerr << "output file " << outputFile << " unable to open." << endl;
        exit(1);
    }
    fout << message;
    fout.close();
}


string VigenereCipher::makeKeystream(const string message) const {
    
	string keyStream;
	int keyLength = mKey.length(); // make sure keystream repeats to length of cipher
	int x = 0;

	for(int i = 0; i < message.length(); i++){ // for length of message, repeat the key
		if(x == keyLength){ // if key ends, repeat again
				x = 0; // reset to begining of key
		}
		keyStream += mKey[x];
		x += 1;	
	}
	return(keyStream);
}


VigenereCipher::VigenereCipher(const string key) { // makes the vigenere table 
	for(size_t x = 0; x < ALPHABET_SIZE; x++){ // x portion of the cipher, A - Z
		for(size_t y = 0; y < ALPHABET_SIZE; y++){ // y portion, A - Z
			mVTable[x][y] = 'A' + ((x+y) % 26); 
		}
	}
}


void VigenereCipher::encrypt(const string inputFile, const string outputFile) const { // encrpt message to cipher

	string message = fileToString(inputFile);
	string key = makeKeystream(message);

	for(size_t i = 0; i < message.length(); i++){ // for every letter in the message, move it by the key letter
		message[i] = mVTable[message[i] - 'A'][key[i] - 'A']; 
	}

	stringToFile(message, outputFile);
}


void VigenereCipher::decrypt(const string inputFile, const string outputFile) const { // reverse engineer a crypted cipher

    string message = fileToString(inputFile);
    string key = makeKeystream(message);
    
	for(size_t i = 0; i < message.length(); i++){ // for every letter in the message
		int row = key[i] - 'A';

		for(size_t j = 0; j < ALPHABET_SIZE; i++){
			if(mVTable[row][j] == message[i]){	
				message[i] = 'A' + j;
				break;
			}
		}
	}
}


void VigenereCipher::printVTable() const { // prints the cipher table by x and y rows
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        for (size_t j = 0; j < ALPHABET_SIZE; j++) {
            cout << " " << mVTable[i][j] << " ";
        }
        cout << endl;
    }
}


int main(int argc, char **argv) {

    VigenereCipher cipher(key);
}
