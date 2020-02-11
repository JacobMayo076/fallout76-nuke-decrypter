//Jacob Mayo
//Created: 10/05/2019
//Updated: 10/23/2019
//Current Status of Project: Working Version
//Version: 1.0
/*  
The purpose of this code is to solve nuclear lauch codes from 
the video game "Fallout 76", not to solve actual nuclear launch
codes; that is highly illegal. The method used by the following
code to decyrpt the silo launch codes was not created by me; I merely
just took their approach and automated/put it in code form. This code
is not to be used to gain monetary value, and I do not authorize anyone
to do so.
*/
//The user who detailed this decryption method is u/SaukPuhpet.
//Link to reddit post detailing this decryption method:
//https://www.reddit.com/r/fo76/comments/9ygyy9/stepbystep_guide_to_decrypting_launch_codes/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream file("8LetterWordList.txt");

bool programIntro() {
	string ans;
	ans.clear();

	cout << "                                   [Version 1.0]                                        " << endl;
	cout << "[------------------------------Important Information-----------------------------------]" << endl;
	cout << "|For this program to work, you must have 8 silo keys and the silo specific keyword.    |" << endl;
	cout << "|The 8 keys you have acquired must correspond to the same silo; either silo Alpha,     |" << endl;
	cout << "|silo Bravo, or silo Charlie. The keyword can be found in the Whitespring bunker's     |" << endl;
	cout << "|military wing, upstairs in command. To access the command, you must be a general.     |" << endl;
	cout << "|On the southwest wall of command, will be 3 boards labeled MISSLE SILO ALPHA,         |" << endl;
	cout << "|MISSLE SILO BRAVO, and MISSLE SILO CHARLIE. Below the labels will be seemingly        |" << endl;
	cout << "|random letters. These are in fact the keywords being generated. You can either        |" << endl;
	cout << "|come back daily to see if the keywords are done being generated, or you can try       |" << endl;
	cout << "|to figure the keyword out yourself with the letters given. The beginning letter       |" << endl;
	cout << "|of the keyword starts directly below the M in MISSLE on the board. The keyword        |" << endl;
	cout << "|itself will vary in length, but will have no repeating letters. You must make sure    |" << endl;
	cout << "|the keyword generated or guessed belongs to the same silo as your silo keys.          |" << endl;
	cout << "|If you do not have the required 8 silo keys or silo keyword, you should not continue. |" << endl;
	cout << "[--------------------------------------------------------------------------------------]" << endl;
	cout << "After reading the above information and checking that your 8 silo keys" << endl;
	cout << "and silo specific keyword match the above information;" << endl;
	TRYAGAIN1:
	cout << "Do you wish to continue? ";
	getline(cin, ans);
	for (int i = 0; i < ans.length(); i++) {
		ans.at(i) = toupper(ans.at(i));
	}
	if (ans == "YES")
		return true;
	else if (ans == "NO")
		return false;
	else {
		cout << "ERROR:NOT A VALID ANSWER" << endl;
		goto TRYAGAIN1;
	}
}

string getSiloKeys() {
	int numOfKeys = 0;
	int num = 1;
	string siloKeys;
	string input;
	siloKeys.clear();
	input.clear();

	cout << "[--------------------------------------------------------------------------------------]" << endl;
	cout << "Silo keys are in the form (letter)(number)." << endl;
	cout << "Example: A6" << endl;

	while (numOfKeys < 8) {
		cout << "Please enter the ";
		if (num == 1) {
			cout << "1st";
		}
		else if (num == 2) {
			cout << "2nd";
		}
		else if (num == 3) {
			cout << "3rd";
		}
		else {
			cout << num << "th";
		}
		cout << " silo key: ";
		getline(cin, input);
		input.at(0) = toupper(input.at(0));

		//Input error checking
		if (input.length() > 2 || input.length() < 2) {
			cout << "ERROR:NOT A VALID KEY" << endl;
			continue;
		}
		if (input[0] < 65 || input[0] > 90) {
			cout << "ERROR:NOT A VALID KEY" << endl;
			continue;
		}
		if (input[1] < 48 || input[1] > 57) {
			cout << "ERROR:NOT A VALID KEY" << endl;
			continue;
		}
			
		if (numOfKeys == 7) {
			siloKeys = siloKeys + input;
		}
		else {
			siloKeys = siloKeys + input;
			siloKeys = siloKeys + " ";
		}
		num++;
		numOfKeys++;
	}

	return siloKeys;
}

string getKeyword() {
	string keyword;
	keyword.clear();

	cout << "[--------------------------------------------------------------------------------------]" << endl;
	cout << "Plese enter the silo specific keyword: ";
	getline(cin, keyword);
	for (int i = 0; i < keyword.length(); i++) {
		keyword.at(i) = toupper(keyword.at(i));
	}

	return keyword;
}

bool checkKeyword(string keyword) {
	//A valid keyword does not have repeating letters.
	for (int i = 0; i < keyword.length() - 1; i++) {
		for (int j = i + 1; j < keyword.length(); j++) {
			if (keyword.at(i) == keyword.at(j))
				return false;
		}
	}
	return true;
}

string createCodeAlphabet(string keyword) {
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string codeAlphabet;
	codeAlphabet.clear();

	for (int i = 0; i < keyword.length(); i++) {
		for (int j = 0; j < alphabet.length(); j++) {
			if (keyword.at(i) == alphabet.at(j)) {
				alphabet.at(j) = ' ';
				break;
			}

		}
	}
	int count = 0;

	//Remove spaces from alphabet
	for (int i = 0; alphabet[i]; i++) {
		if (alphabet[i] != ' ')
			alphabet[count++] = alphabet[i]; 
		alphabet[count] = '\0';
	}

	codeAlphabet = keyword + alphabet;
	return codeAlphabet;
}

string runThroughCodedAlphabet(string siloKeys, string codeAlphabet, int timeThrough) {
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string codeSiloKeys = siloKeys;


	if (timeThrough == 1) {
		for (int i = 0; i < siloKeys.length(); i++) {
			if (siloKeys[i] >= 48 && siloKeys[i] <= 57) {
				continue;
			}
			if (siloKeys.at(i) == ' ') {
				continue;
			}
			for (int j = 0; j < alphabet.length(); j++) {
				if (siloKeys.at(i) == codeAlphabet.at(j)) {
					codeSiloKeys.at(i) = alphabet.at(j);
					break;
				}
			}
		}
	} 
	else if (timeThrough == 2) {
		for (int i = 0; i < siloKeys.length(); i++) {
			if (siloKeys[i] >= 48 && siloKeys[i] <= 57) {
				continue;
			}
			if (siloKeys.at(i) == ' ') {
				continue;
			}
			for (int j = 0; j < alphabet.length(); j++) {
				if (siloKeys.at(i) == alphabet.at(j)) {
					codeSiloKeys.at(i) = codeAlphabet.at(j);
					break;
				}
			}
		}
	}

	return codeSiloKeys;
}

bool checkIfCanUnscramble() {
	bool test = false;


	if (file.is_open() == true && test == true) {
		return true;
	}
	else {
		cout << "Unable to open file(s)." << endl;
		cout << "Manual descramble required." << endl;
		return false;
	}
}

string autoUnscramble(string codeSiloKeys) {
	string unscrambledSiloKeys;
	unscrambledSiloKeys.clear();

	return unscrambledSiloKeys;
}

string manualUnscramble(string codeSiloKeys) {
	string unscrambledWord;
	string unscrambledSiloKeys;
	unscrambledWord.clear();
	unscrambledSiloKeys.clear();

	for (int i = 0; i < codeSiloKeys.length(); i++) {
		if (codeSiloKeys.at(i) == ' ') {
			continue;
		}
		if (codeSiloKeys[i] >= 48 && codeSiloKeys[i] <= 57) {
			continue;
		}
		cout << codeSiloKeys.at(i);
	}

	cout << endl << "Please unscramble the above word." << endl;
	cout << "Unscrambled word: ";
	getline(cin, unscrambledWord);

	for (int i = 0; i < unscrambledWord.length(); i++) {
		unscrambledWord.at(i) = toupper(unscrambledWord.at(i));
	}



	for (int i = 0; i < unscrambledWord.length(); i++) {
		for (int j = 0; j < codeSiloKeys.length(); j++) {
			if (unscrambledWord.at(i) == codeSiloKeys.at(j)) {
				if (i + 1 >= unscrambledWord.length()) {
					unscrambledSiloKeys = unscrambledSiloKeys + unscrambledWord.at(i);
					unscrambledSiloKeys = unscrambledSiloKeys + codeSiloKeys.at(j + 1); //Problem?
					break;
				}
				unscrambledSiloKeys = unscrambledSiloKeys + unscrambledWord.at(i);
				unscrambledSiloKeys = unscrambledSiloKeys + codeSiloKeys.at(j + 1);
				unscrambledSiloKeys = unscrambledSiloKeys + " ";
				break;
			}
		}
	}

	return unscrambledSiloKeys;
}

string getSiloCode(string decryptedSiloKeys) {
	string siloCode;
	siloCode.clear();

	for (int i = 0; i < decryptedSiloKeys.length(); i++) {
		if (decryptedSiloKeys[i] >= 48 && decryptedSiloKeys[i] <= 57) {
			siloCode = siloCode + decryptedSiloKeys[i];
		}
	}

	return siloCode;
}

void printSiloCode(string siloCode) {
	cout << "The nuclear launch code is: " << siloCode << endl;
	cout << "Program is terminating." << endl;
}

int main() {
	
	char x;
	string word;
	string siloKeys;
	string codeSiloKeys;
	string unscrambledSiloKeys;
	string decryptedSiloKeys;
	string keyword;
	string ans;
	string codeAlphabet;
	string siloCode;
	bool hasInfo = false;
	bool valid = false;
	bool repeat = true;
	word.clear();
	siloKeys.clear();
	codeSiloKeys.clear();
	unscrambledSiloKeys.clear();
	decryptedSiloKeys.clear();
	keyword.clear();
	ans.clear();
	codeAlphabet.clear();
	siloCode.clear();

	//Makes sure that the user has all of the necessary information.
	hasInfo = programIntro();
	if (hasInfo == false) {
		cout << endl << "Program is terminating." << endl;
		system("pause");
		return 0;
	}

	//Collect necessary information.
	//Get the 8 silo keys.
	siloKeys = getSiloKeys();
	//While loop to collect necessary information.
	while (repeat == true) {
		//Get the silo specific keyword.
		keyword = getKeyword();

		//Checks if the keyword is valid.
		valid = checkKeyword(keyword);
		if (valid == false) {
			cout << "\"" << keyword << "\" is not a valid keyword." << endl;

			TRYAGAIN:
			cout << "Do you wish to enter the keyword again or enter a new keyword? ";
			getline(cin, ans);
			for (int i = 0; i < ans.length(); i++) {
				ans.at(i) = toupper(ans.at(i));
			}
			if (ans.at(0) == 'Y')
				continue;
			else if (ans.at(0) == 'N') {
				cout << endl << "Program is terminating." << endl;
				system("pause");
				return 0;
			}
			else {
				cout << "ERROR:NOT A VALID ANSWER" << endl;
				goto TRYAGAIN;
			}
		}
		else {
			repeat = false;
		}
	}

	//Create coded alphabet.
	codeAlphabet = createCodeAlphabet(keyword);
	//Get coded silo keys
	codeSiloKeys = runThroughCodedAlphabet(siloKeys, codeAlphabet, 1);

	//Checks if file is open and then searches for possible matches.
	/*if (file.is_open() == true) {
		while (!file.eof()) {
			x = file.get();

			if (x == -1) {
				if (word.empty() == true)
					continue;
				word.clear();
				continue;
			}
			else if (x == '\n') {
				cout << word << endl;
				word.clear();
				continue;
			}
			else {
				word = word + x;
			}
		}
	}
	else {
		cout << "Unable to open file(s)." << endl;
		cout << "Manual descramble required." << endl;
	}*/

	if (checkIfCanUnscramble())
		unscrambledSiloKeys = autoUnscramble(codeSiloKeys);
	else
		unscrambledSiloKeys = manualUnscramble(codeSiloKeys);

	decryptedSiloKeys = runThroughCodedAlphabet(unscrambledSiloKeys, codeAlphabet, 2);
	siloCode = getSiloCode(decryptedSiloKeys);
	printSiloCode(siloCode);

	system("pause");
	return 0;
}