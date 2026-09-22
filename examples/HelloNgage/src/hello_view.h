#ifndef HELLO_VIEW_H
#define HELLO_VIEW_H
#include <coecntrl.h>
class CHelloView : public CCoeControl {
public:
 static CHelloView* NewL(const TRect& aRect);
 ~CHelloView();
 void Draw(const TRect& aRect) const;
private:
 CHelloView();
 void ConstructL(const TRect& aRect);
};
#endif
