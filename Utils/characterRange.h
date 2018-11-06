bool characterNotSupported(unsigned const char &c) {
    if(c >= 'A' && c <= 'Z') {
        return false;
    } else {
        switch(c){
            case 193:
            case 201:
			case 205:
			case 209:
            case 211:
            case 218:
            case 220:
                return false;
        }
    }
    if(c >= 'a' && c <= 'z') {
        return false;
    } else {
        switch(c){
            case 225:
            case 233:
			case 237:
			case 241:
            case 243:
            case 250:
            case 252: // U  con acento dieresis
                return false;
        }
    }
    return true;
}