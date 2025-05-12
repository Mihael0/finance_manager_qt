#include "apptime.h"

AppTime::AppTime() {
    // This must be called to make sure that LocalAppTime is not undefined.
    _InitializeAppTimeToStartOfMonth();
}
