#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

// Morse code map including custom support for # * |
map<char, string> morseCode = {
    {'A', ".-"},     {'B', "-..."},  {'C', "-.-."}, {'D', "-.."},    {'E', "."},
    {'F', "..-."},   {'G', "--."},   {'H', "...."}, {'I', ".."},     {'J', ".---"},
    {'K', "-.-"},    {'L', ".-.."},  {'M', "--"},   {'N', "-."},     {'O', "---"},
    {'P', ".--."},   {'Q', "--.-"},  {'R', ".-."},  {'S', "..."},    {'T', "-"},
    {'U', "..-"},    {'V', "...-"},  {'W', ".--"},  {'X', "-..-"},   {'Y', "-.--"},
    {'Z', "--.."},   {'1', ".----"}, {'2', "..---"},{'3', "...--"},  {'4', "....-"},
    {'5', "....."},  {'6', "-...."}, {'7', "--..."},{'8', "---.."},  {'9', "----."},
    {'0', "-----"},  {' ', "/"},     {'.', ".-.-.-"},{',', "--..--"}, {'?', "..--.."},
    {'\'', ".----."},{'!', "-.-.--"},{'/', "-..-."}, {'(', "-.--."},  {')', "-.--.-"},
    {'&', ".-..."},  {':', "---..."},{';', "-.-.-."},{'=', "-...-"},  {'+', ".-.-."},
    {'-', "-....-"}, {'_', "..--.-"},{'"', ".-..-."},{'$', "...-..-"},{'@', ".--.-."},
    {'#', "......"},    // Custom for #
    {'*', "..*.."},     // Custom for *
    {'|', "..||.."}     // Custom for |
};

// Reverse Morse map
map<string, char> reverseMorse;

void buildReverseMorseMap() {
    for (auto& p : morseCode) {
        reverseMorse[p.second] = p.first;
    }
}

// Encode to Morse (preserves lowercase using ^)
string encode(const string& text) {
    stringstream ss;
    for (char c : text) {
        if (isalpha(c)) {
            char upper = toupper(c);
            if (morseCode.count(upper)) {
                if (islower(c)) {
                    ss << "^" << morseCode[upper] << " ";
                } else {
                    ss << morseCode[upper] << " ";
                }
            } else {
                ss << "? ";
            }
        } else if (morseCode.count(c)) {
            ss << morseCode[c] << " ";
        } else {
            ss << "? ";
        }
    }
    return ss.str();
}

// Decode Morse to text (supports ^ for lowercase)
string decode(const string& morse) {
    stringstream ss(morse);
    string token, result;

    while (ss >> token) {
        bool isLower = false;

        if (token[0] == '^') {
            isLower = true;
            token = token.substr(1);
        }

        if (reverseMorse.count(token)) {
            char decodedChar = reverseMorse[token];
            result += isLower ? tolower(decodedChar) : decodedChar;
        } else {
            result += '?';
        }
    }

    return result;
}

int main() {
    buildReverseMorseMap();

    while (true) {
        int choice;
        cout << "\n--- Morse Code Tool ---\n";
        cout << "1. Encode Text to Morse\n";
        cout << "2. Decode Morse to Text\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string input;
            cout << "Enter text to encode: ";
            getline(cin, input);
            cout << "\nEncoded Morse:\n" << encode(input) << "\n";

        } else if (choice == 2) {
            string morseInput;
            cout << "Enter Morse code to decode (use '/' for space, '^' for lowercase):\n";
            getline(cin, morseInput);
            cout << "\nDecoded Text:\n" << decode(morseInput) << "\n";

        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;

        } else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
