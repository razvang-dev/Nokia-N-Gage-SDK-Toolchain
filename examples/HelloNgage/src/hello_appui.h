#ifndef HELLO_APPUI_H
#define HELLO_APPUI_H
#include <aknappui.h>
class CHelloView;
class CHelloAppUi : public CAknAppUi {
public:
 CHelloAppUi(); ~CHelloAppUi();
 void ConstructL();
 void HandleCommandL(TInt aCommand);
 TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
private: CHelloView* iView;
};
#endif
