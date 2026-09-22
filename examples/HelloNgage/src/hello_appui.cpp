#include "hello_appui.h"
#include "hello_view.h"
#include <avkon.hrh>
#include <uikon.hrh>
CHelloAppUi::CHelloAppUi():iView(0){}
CHelloAppUi::~CHelloAppUi(){ if(iView){ RemoveFromStack(iView); delete iView; } }
void CHelloAppUi::ConstructL(){ BaseConstructL(); iView=CHelloView::NewL(ClientRect()); AddToStackL(iView); }
void CHelloAppUi::HandleCommandL(TInt aCommand){ if(aCommand==EAknSoftkeyExit || aCommand==EEikCmdExit || aCommand==EAknSoftkeyBack){ Exit(); } }
TKeyResponse CHelloAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType){ if(aType==EEventKey && aKeyEvent.iCode=='7'){ Exit(); return EKeyWasConsumed; } return EKeyWasNotConsumed; }
