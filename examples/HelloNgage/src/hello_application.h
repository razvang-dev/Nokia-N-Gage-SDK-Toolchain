#ifndef HELLO_APPLICATION_H
#define HELLO_APPLICATION_H
#include <aknapp.h>
class CHelloApplication : public CAknApplication {
public: TUid AppDllUid() const;
protected: CApaDocument* CreateDocumentL();
};
#endif
