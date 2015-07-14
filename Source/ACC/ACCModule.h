#ifndef ACC_MODULE_H
#define ACC_MODULE_H

#include "JuceHeader.h"

//=============================================================================
/** Config: DONT_SET_USING_ACC_NAMESPACE

    If your uses a lot of ACC classes, declaring
    using namespace acc obviously will save you a lot of typing!

    You may disable this default by defining DONT_SET_USING_ACC_NAMESPACE somewhere,
    and setting it to 1.
*/
#ifndef DONT_SET_USING_ACC_NAMESPACE
 #define DONT_SET_USING_ACC_NAMESPACE 0
#endif

//=============================================================================
namespace acc
{
    #include "core/ACCCodeTokeniser.h"
    #include "core/Script.h"
    #include "core/ScriptParser.h"
    #include "graphics/ACCApplicationCommands.h"
    #include "graphics/ACCCodeEditor.h"
    #include "graphics/ACCMainComponent.h"
    #include "graphics/ACCWindow.h"
}

//=============================================================================
#if ! DONT_SET_USING_ACC_NAMESPACE
 using namespace acc;
#endif

#endif //ACC_MODULE_H