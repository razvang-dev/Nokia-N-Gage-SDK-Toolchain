#include "hello_view.h"
#include <eikenv.h>
#include <gdi.h>
CHelloView::CHelloView(){}
CHelloView::~CHelloView(){}
CHelloView* CHelloView::NewL(const TRect& aRect){ CHelloView* self=new(ELeave) CHelloView; CleanupStack::PushL(self); self->ConstructL(aRect); CleanupStack::Pop(self); return self; }
void CHelloView::ConstructL(const TRect& aRect){ CreateWindowL(); SetRect(aRect); ActivateL(); }
void CHelloView::Draw(const TRect& aRect) const {
 CWindowGc& gc=SystemGc();
 gc.SetBrushStyle(CGraphicsContext::ESolidBrush); gc.SetBrushColor(KRgbWhite); gc.Clear(aRect);
 gc.SetPenColor(KRgbBlack); gc.SetPenStyle(CGraphicsContext::ESolidPen);
 const CFont* font=iEikonEnv->TitleFont(); gc.UseFont(font);
 _LIT(KHello,"Hello N-Gage!");
 TInt y=(Rect().Height()+font->AscentInPixels())/2;
 gc.DrawText(KHello,Rect(),y,CGraphicsContext::ECenter);
 gc.DiscardFont();
}
