// Copyright 2004 Nokia. All rights reserved.

#ifndef RENDERER_H
#define RENDERER_H

// INCLUDES
#include <coecntrl.h>
#include <aknappui.h>
#include <fbs.h>


class CNRenderer: public CBase
{
public:
	// Depth Compare functions
	enum TCompFunc
	{
		EGreaterEqual	=0x001,			
		ELessEqual		=0x002,			
		EGreater		=0x003,			
		ELess			=0x004,			
		EEqual			=0x005,			
		ENotEqual		=0x006
	};

	// Color texture mix functions
	enum TMixFunc
	{
		EModulate,
		EModulate2x,
		EAdd,
		ECustom
	};

	// Blending factors
	enum TBlendFactor
	{
		EZero				= 0,
		EAlpha25			= 64,
		EAlpha50			= 128,
		EAlpha75			= 196,
		EOne				= 256,
		ESrcColor			= 257,
		EOneMinusSrcColor	= 258,
		EDstColor			= 257,
		EOneMinusDstColor	= 258
	};


	// Render states
	enum TRenderState
	{
		// Enable Z buffer
		EDepthEnable		=0x0001,
		// Enable Z write buffer
		EDepthWrite			=0x0002,
		// Enable frame buffer write mask
		EColorWrite			=0x0004,

		// Enable texturing
		ETextureEnable		=0x0010,
		// Enable color key
		ETextureColorKey	=0x0020,
		// Enable bilinear minification filtering
		ETextureMinBilinear	=0x0040,
		// Enable bilinear magnification filtering
		ETextureMagBilinear	=0x0080,
		// Enable bilinear filtering
		ETextureBilinear	=ETextureMagBilinear|ETextureMinBilinear,
		// Enable perspective correcture texture mapping
		ETexturePerspective	=0x0100,


		// Enable double side rendering
		EDoubleSide			=0x0400,
		// Enable global texture state
		ETextureLocal		=0x0800,

		// Enable color mixing
		ELighting			=0x1000,
		// Enable smooth (gouraud) shading
		ESmooth				=0x2000,
		// Enable dithering
		EDithering			=0x4000,
		// Enable alpha blending
		EAlphaBlending		=0x8000,



		// All states
		EAllStates			=0xFFFF

	};

	// ------------------------------------------------------------------------------------
	// Constructor
	CNRenderer();

	// Two-phased constructor.
	static CNRenderer* NewL();

	// Destructor
	~CNRenderer();


	// Return member function
	inline CFbsBitmap* Bitmap() const { return iBitmap; }
	inline CFbsBitmapDevice* Device() const { return iDevice; }
	inline CFbsBitGc* Gc() const { return iGc; }
	inline TSize Size() const { return iSize; }
	inline TUint32* BackBufferAddress() const { return (TUint32 *)iAddress; }
	inline TUint32* DepthBufferAddress() const { return (TUint32 *)iZbuffer; }

	// ------------------------------------------------------------------------------------
	// Clear Buffer
	void Clear(TUint aColor = 0, TUint aDepth = 0) const;

	// Flip backbuffer to another graphic context
	inline void Flip (CFbsBitGc& aGc) const { aGc.BitBlt(TPoint(0,0), iBitmap); }
	inline void Flip (CFbsBitGc* aGc) const { aGc->BitBlt(TPoint(0,0), iBitmap); }
	// Flip backbuffer to direct screen
	void Flip (CDirectScreenAccess* aDirectScreen) const;

	// BeginScene update backbuffer pointes, that can be moved by Symbian
	inline void BeginScene (void) { iAddress = iBitmap->DataAddress(); iZbuffer = ((TUint16 *)iAddress) + iSize.iWidth*iSize.iHeight; }
	// For future compatibility
	inline void EndScene   (void) { }

	// Set texture
   	TBool SetTexture(TAny *aAddress, TInt aSizeX, TInt aSizeY, TInt aMipmapLevel = 0);
   	TBool SetTexturePower2(TAny *aAddress, TInt aSizeXP2, TInt aSizeYP2, TInt aMipmapLevel = 0); 
	// Set clut texture
   	inline void  SetTextureCLUT(TAny* aCLUT) { iTextureCLUT = (TUint16 *)aCLUT; }
   	inline TAny* GetTextureCLUT() const { return (iTextureCLUT); }

	// Set Render State
	inline TBool GetRenderState (TRenderState aState) const { return (iRenderState & aState); }
	inline TBool SetRenderState (TRenderState aState, TBool aValue) { if (aValue) iRenderState |= aState; else  iRenderState &= ~aState; SetRenderStateFunction(); if (aState & (ETextureColorKey|EDithering|EAlphaBlending|EDepthWrite)) SetRenderSubFunctions(); return ETrue; }
	// Set depth comparison function
	inline void		 SetDepthFunc (TCompFunc aDepthFunc) { iDepthCompFunc = aDepthFunc; SetRenderSubFunctions(); }
	inline TCompFunc GetDepthFunc () const { return (iDepthCompFunc); }
	// Set mix function
	inline void		SetCustomMixTable (const TUint8* aMixTable) { iMixFunc = ECustom; iMixTable = aMixTable; }
	inline void		SetMixFunc (TMixFunc aMixFunc) { iMixFunc = aMixFunc; SetStandardMixFunction(); }
	inline TMixFunc GetMixFunc () const { return (iMixFunc); }
	// Set current color
	void SetCurrentColor (TUint32 aColor);
	inline TUint32 GetCurrentColor () const { return (iCurrentColor); }
	// Set blending function
	void SetBlendFunc (const TUint aSrcFactor, const TUint aDstFactor);
	inline TUint GetBlendSrcFactor() const { return iBlendSrcFactor; }
	inline TUint GetBlendDstFactor() const { return iBlendDstFactor; }

	// Statistic function
	inline void ClearStatisticCounters() { iTriangleCounter = iDrawingCounter = iPixelCounter = 0; }
	inline void ClearTriangleCounter()   { iTriangleCounter = 0; }
	inline void ClearDrawingCounter()    { iDrawingCounter =  0; }
	inline void ClearPixelCounter()      { iPixelCounter = 0; }
	inline TUint GetTriangleCounter() { return iTriangleCounter; }
	inline TUint GetDrawingCounter()  { return iDrawingCounter; }
	inline TUint GetPixelCounter()    { return iPixelCounter; }

	// Render triangle Function
	inline void  DrawTriangleList (TInt *aFaceList, TInt aCount) { (this->*iDrawTriangleList) (aFaceList, aCount); }


private: 

	// EPOC default constructor.
	void ConstructL();

	// Set render function from render state
	void SetRenderStateFunction();

	// Set render sub function from render state
	void SetRenderSubFunctions();

	// Set Mix Function
	void SetStandardMixFunction();

private: 

	// Backbuffer
	CFbsBitmap*			iBitmap;
	CFbsBitmapDevice*	iDevice;
	CFbsBitGc*			iGc;

	// Rasterizer buffers
	TSize		iSize;
	TAny*		iAddress;
	TUint16*	iZbuffer;

	// Texture definitions
	TUint16*	iTextureCLUT;
	TUint16*	iTextureAddress;
    TUint		iTextureValue;
    TUint		iTextureNearest;
	TUint		iTextureMipMapLevel;

	// Render state
	TUint		iRenderState;
	// Depth compare 
	TCompFunc	iDepthCompFunc;
	// Current Color
	TUint32		iCurrentColor;
	// Current color in backbuffer format
	TUint32		iColor;


	// Mix unit function
	TMixFunc      iMixFunc;
	// Pointer to mix unit table
	const TUint8* iMixTable;
	// Blend factors
	TUint		iBlendSrcFactor;
	TUint		iBlendDstFactor;
	// Blending table 
	TUint8*		iBlendTable;

	// Draw Triangle Function
	void (CNRenderer::*iDrawTriangleList) (TInt*, TInt );


	// ------------------------------------------------------------------------------------
	// Sub functions
	// ------------------------------------------------------------------------------------
	// COLOR PIPELINE
	// Draw white light color function without/with depth buffer
	void (*iDrawWhiteLightTriangle) (TInt, TInt&, const TInt, TInt&, const TInt, TUint32&, const TInt, const TUint32, TUint16*&, const TUint8*, const TUint8*);
	void (*iDrawWhiteLightTriangleZ)(TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TUint32&, const TUint32, TUint16*&, const TUint8*, const TUint8 *);
	// TEXTURE PIPELINE
	// Draw texture mapping function without/with depth buffer
	void (*iDrawTextureTriangle)  (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TUint16 *&, const TUint16 *, const TUint, const TUint8*);
	void (*iDrawTextureTriangleZ) (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TInt&, const TInt, const TInt, TUint16*&, const TUint16*, const TUint, const TUint8*);
	// Draw bilinear texture mapping function without/with depth buffer
	void (*iDrawBilinearTextureTriangle)  (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TUint16 *&, const TUint16 *, const TUint, const TUint8*);
	void (*iDrawBilinearTextureTriangleZ) (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TInt&, const TInt, const TInt, TUint16*&, const TUint16*, const TUint, const TUint8*);
	// MIX PIPELINE
	// Draw white light color texture mapping function  without/with depth buffer
 	void (*iDrawWhiteLightTextureTriangle)  (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TUint32&, const TInt, TUint16*&, const TUint16*, const TUint, const TUint8*, const TUint8*);
	void (*iDrawWhiteLightTextureTriangleZ) (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TInt&, const TInt, const TInt, TUint32&, TUint16*&, const TUint16*, const TUint, const TUint8*, const TUint8*);
	// Draw white light color bilinear texture mapping function  without/with depth buffer
	void (*iDrawWhiteLightBilinearTextureTriangle)  (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TUint32&, const TInt, TUint16*&, const TUint16*, const TUint, const TUint8*, const TUint8*);
	void (*iDrawWhiteLightBilinearTextureTriangleZ) (TInt, TInt&, const TInt, TInt&, const TInt, TInt&, const TInt, const TInt, TInt&, const TInt, const TInt, TUint32&, TUint16*&, const TUint16*, const TUint, const TUint8*, const TUint8*);


	TUint iTriangleCounter;
	TUint iDrawingCounter;
	TUint iPixelCounter;
};

#endif
