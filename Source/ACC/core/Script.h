#ifndef ACC_SCRIPT_H
#define ACC_SCRIPT_H

class Script
{
public:
    enum Type
    {
        open = 1,
        respawn,
        death,
        enter,
        pickup,
        blueReturn,
        redReturn,
        whiteReturn,
        lightning = 12,
        unloading,
        disconnect,
        returnScriptBase,
        eventScriptBase
    };

    Script (Type newType);

    //==============================================================================
    Type getType() const noexcept { return type; }

    const String& getName() const noexcept { return name; }

    //==============================================================================
    static String toString (Type type);

private:
    //==============================================================================
    const Type type;
    const String name;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Script)
};

#endif //ACC_SCRIPT_H