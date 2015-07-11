Script::Script (Type newType) :
    type (newType),
    name (toString (newType))
{
}

//==============================================================================
String Script::toString (Type type)
{
    switch (type)
    {
        case open:              return "open";
        case respawn:           return "respawn";
        case death:             return "death";
        case enter:             return "enter";
        case pickup:            return "pickup";
        case blueReturn:        return "bluereturn";
        case redReturn:         return "redreturn";
        case whiteReturn:       return "whitereturn";
        case lightning:         return "lightning";
        case unloading:         return "unloading";
        case disconnect:        return "disconnect";
        case returnScriptBase:  return "return";
        case eventScriptBase:   return "event";

        default:
        break;
    };

    jassertfalse;
    return String();
}