#include "hello_application.h"
GLDEF_C TInt E32Dll(TDllReason) { return KErrNone; }
EXPORT_C CApaApplication* NewApplication() { return new CHelloApplication; }
