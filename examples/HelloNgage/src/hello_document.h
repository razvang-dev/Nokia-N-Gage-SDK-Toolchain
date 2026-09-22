#ifndef HELLO_DOCUMENT_H
#define HELLO_DOCUMENT_H
#include <akndoc.h>
class CHelloDocument : public CAknDocument {
public:
 static CHelloDocument* NewL(CEikApplication& aApp);
 ~CHelloDocument();
 CEikAppUi* CreateAppUiL();
private:
 CHelloDocument(CEikApplication& aApp);
 void ConstructL();
};
#endif
