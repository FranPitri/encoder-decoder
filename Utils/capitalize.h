#include <string>

bool isCaps(unsigned char const &letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return true;
    } else {
        switch(letter){
            case 193: // Á con acento agudo
            case 201: // É  con acento agudo
			case 205: // Í  con acento agudo
			case 209: // Ñ 
            case 211: // Ó  con acento agudo
            case 218: // Ú  con acento agudo
            case 220: // U  con acento dieresis
                return true;
        }
    }
    return false;
}

void toCaps(std::string &word) {
    if (!isCaps((unsigned char const)word[0]))
        word[0] -= 32;
    //std::cout << word << '\n';
}