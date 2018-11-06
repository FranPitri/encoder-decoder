unsigned int convert(unsigned char);

unsigned int convert(unsigned char letter){

    if(letter >= 'A' && letter <= 'Z'){
        letter+=32-97;
        return letter;
    }else{
        switch(letter){
            case 193: // Á con acento agudo
                letter-=167;
                return letter;
            break;
            case 201: // É  con acento agudo
            	letter-=174;
                return letter;
            break;
			case 205: // Í  con acento agudo
				letter-=177;
                return letter;
            break;
			case 209: // Ñ  
				letter-=177;
                return letter;
            break;
            case 211: // Ó  con acento agudo
				letter-=182;
                return letter;
            break;
            case 218: // Ú  con acento agudo
				letter-=188;
                return letter;
            break;
            case 220: // U  con acento dieresis
                letter-=189;
                return letter;
            break;
        }
    }
    if(letter >= 'a' && letter <= 'z'){
        return letter-97;
    }else{
        switch(letter){
            case 225: // á con acento agudo
				return letter-199;
            break;
            case 233: // É  con acento agudo
                return letter-206;
            break;
			case 237: // Í  con acento agudo
                return letter-209;
            break;
			case 241: // Í  con acento agudo
                return letter-209;
            break;
            case 243: // Ó  con acento agudo
                return letter-214;
            break;
            case 250: // Ú  con acento agudo
                return letter-220;
            break;
            case 252: // U  con acento dieresis
                return letter-221;
            break;
        }
    }
    return 33;
}