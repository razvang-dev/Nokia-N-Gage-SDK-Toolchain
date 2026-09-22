#include "hello_document.h"
#include "hello_appui.h"
CHelloDocument::CHelloDocument(CEikApplication& aApp):CAknDocument(aApp){}
void CHelloDocument::ConstructL(){}
CHelloDocument* CHelloDocument::NewL(CEikApplication& aApp){ CHelloDocument* self=new(ELeave) CHelloDocument(aApp); CleanupStack::PushL(self); self->ConstructL(); CleanupStack::Pop(self); return self; }
CHelloDocument::~CHelloDocument(){}
CEikAppUi* CHelloDocument::CreateAppUiL(){ return new(ELeave) CHelloAppUi; }
