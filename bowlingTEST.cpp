/* Program Name: Bowling Lab
 * Student Name: Clark Kirby
 * Program Description: Keep track and score multiple bowlers scores and tally 
 *						up the totals at the end under proper bolwing scoring
 *						rules and regulations.								*/



#include <iostream>
#include <string>
#include <vector>

using namespace std;


const size_t NUMBER_OF_FRAMES = 10;
const size_t ROLLS_PER_FRAME = 2;
const size_t TOTAL_ROLLS = NUMBER_OF_FRAMES * 2 + 1; // 21
const int NUMBER_OF_PINS = 10;

// Use for debugging
void printPlayerRolls(const vector<int> &playerRolls) {
    for (size_t i = 0; i < playerRolls.size(); ++i) {
        cerr << playerRolls[i] << " ";
    }
    cerr << endl;
}


vector<int> inputPlayerRolls() {

    vector<int> playerRolls(TOTAL_ROLLS, 0);
    int rollInput; // individual roll number of pins

    // input first 20 rolls
    for ( size_t frame = 0; frame < NUMBER_OF_FRAMES; ++frame ) { // loops between frames
		
		for ( size_t roll = 0; roll < ROLLS_PER_FRAME; ++roll ) { // loops between the two rolls in the larger looped frame
            cout << "Enter score for frame " << frame + 1 << ", roll " << roll + 1 << ": "; // rolls and frames are zero based, i.e. why we do + 1
            cin >> rollInput;

            playerRolls[frame * 2 + roll] = rollInput;

            if ( rollInput == NUMBER_OF_PINS ) {
                break;
            }
        }
    }

	if( playerRolls[18] == 10 ) { // if strike on last frame
        cout << "Enter score for frame 10, roll 2: ";
        cin >> rollInput;
		playerRolls[19] = rollInput;
		cout << "Enter score for frame 10, roll 3: ";
		cin >> rollInput;
		playerRolls[20] = rollInput;
		}
	else if( playerRolls[18] + playerRolls[19] == 10 ) { // if spare on last frame 
        cout << "Enter score for frame 10, roll 3: ";
        cin >> rollInput; 
        playerRolls[20] = rollInput;
    } 

    return playerRolls;
}


int calculatePlayerScore( const vector<int> &playerRolls ) {
    int playerScore = 0;

    for ( size_t frameNumber = 0; frameNumber < NUMBER_OF_FRAMES - 1; ++frameNumber ) {
        const size_t currentFrame = frameNumber * 2;
        const size_t nextFrame = currentFrame + 2;
        const size_t nextNextFrame = nextFrame + 2;

        const int roll1 = playerRolls[currentFrame];
        const int roll2 = playerRolls[currentFrame + 1];

        const bool isStrike = roll1 == NUMBER_OF_PINS;
        const bool isSpare = roll1 + roll2 == NUMBER_OF_PINS;

		if (isStrike) {
            playerScore += NUMBER_OF_PINS; // Add 10 points for the strike
			
            if (frameNumber < NUMBER_OF_FRAMES - 1) { // Check if it's not the 10th frame
                // If the next frame is also a strike, add 10 + the next roll
                if (playerRolls[nextFrame] == NUMBER_OF_PINS) {
                    playerScore += NUMBER_OF_PINS + playerRolls[nextNextFrame];
                } 
                // Otherwise, add the sum of the next two rolls
                else {
                    playerScore += playerRolls[nextFrame] + playerRolls[nextFrame + 1];
                }
            }
		}

        else if (isSpare) {	// spare is ten pins plus the next single roll
            playerScore += NUMBER_OF_PINS + playerRolls[nextFrame];
        } 
        else {
            playerScore += roll1 + roll2;
        }
	}

	playerScore += playerRolls[18] + playerRolls[19] + playerRolls[20];	// the final frame plus a last frame if neccesary, if not, 20 is 0
    
	return playerScore;
}


void printGameSummary(const vector<string> &playerNames, const vector<int> &playerScores) {

    // This line prevents the program from seg faulting if no players were
    // entered
    if (playerNames.empty()) {
        cout << "No players were entered." << endl;
        return;
    }


    cout << endl;

    for (size_t i = 0; i < playerNames.size(); ++i) { // list players played and scores
        cout << playerNames[i] << " scored " << playerScores[i] << "." << endl;
    }

    string worstPlayerName = playerNames[0];
    int worstPlayerScore = playerScores[0];

    string bestPlayerName = playerNames[0];
    int bestPlayerScore = playerScores[0];

    for (size_t i = 1; i < playerNames.size(); ++i) {
        if (playerScores[i] < worstPlayerScore) {
            worstPlayerScore = playerScores[i];
            worstPlayerName = playerNames[i];
        }
        if (playerScores[i] > bestPlayerScore) {
            bestPlayerScore = playerScores[i];
            bestPlayerName = playerNames[i];
        }
    }

    cout << worstPlayerName << " did the worst by scoring " << worstPlayerScore << "." << endl;
    cout << bestPlayerName << " won the game by scoring " << bestPlayerScore << "." << endl;
}


int main() {
    vector<string> playerNames;
    vector<int> playerScores;

    while (true) {
        string inputString;

        cout << "Enter player's name (done for no more players): ";
        cin >> inputString;

        if (inputString == "done") {
            break;
        }

        const vector<int> playerRolls = inputPlayerRolls();

        const int playerScore = calculatePlayerScore(playerRolls);

        playerNames.push_back(inputString);
        playerScores.push_back(playerScore);

        // Prevents infinite loop if cin is in a bad state
        if (!cin) {
            throw runtime_error("Invalid input");
        }
    }

    printGameSummary(playerNames, playerScores);

    return 0;
}

