#include "hello_application.h"
#include "hello_document.h"
const TUid KUidHello = {0x1020F4AE};
TUid CHelloApplication::AppDllUid() const { return KUidHello; }
CApaDocument* CHelloApplication::CreateDocumentL() { return CHelloDocument::NewL(*this); }
