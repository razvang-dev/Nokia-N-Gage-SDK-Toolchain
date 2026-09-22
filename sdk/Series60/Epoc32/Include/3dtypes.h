#ifndef _3D_TYPES_H
#define _3D_TYPES_H

#include <e32std.h>
#include <e32math.h>

// Fixed point declaration.
typedef int TFixed;

// Fixed point square root.
TFixed FixSqrt(TFixed aValue);

// Fixed point operations.
void FixSinCos(int Angle, int& Sin, int& Cos);

// Division.
inline TFixed FixDiv(TFixed i, TFixed j)
{
    return (((TInt64(i) << 16) / TInt64(j)).GetTInt());
}

// Multiplication.
inline TFixed FixMul(const TFixed i, const TFixed j)
{
    register TFixed ret, tmp;
    asm(
        "SMULL %0, %1, %2, %3\n\t" // Long mul.
        "MOVS %0, %0, LSR#16\n\t" // Shift low.
        "ADC %0, %0, %1, LSL#16\n\t" // Shift high.
        : // Output operands.
        "=&r" (ret),        // %0 r0
        "=&r" (tmp)     // %1
        : // Input operands.
        // Parameters.
        "r" (i), // %2
        "r" (j)  // %3
        : // Clobbers registers.
        "cc"
        );
    return ret;
}

#define M_PI 3.14159265358979323846

// One divided by int return fixedpoint value.
#define KFixOne 0x10000
#define OneDivInt(i) (KFixOne/(i))
#define Int2Fix(i) ((i)<<16)
#define Fix2Int(i) ((((unsigned int)(i)>0xFFFF0000)?0:((i)>>16)))
#define Fix2Real(i) ((i)/65536.0)
#define Real2Fix(i) ((TFixed)((i)*65536.0))
#define Angle2Fix(i) ((TFixed)((i)*65536.0*180.0/3.14159265358979323846))

// Vector declaration.
class TPoint3D
{
public:
    // Constructor
    inline TPoint3D(TFixed f = 0)
    {
        iX = iY = iZ = f;
    }
    inline TPoint3D(TFixed f[3])
    {
        iX = f[0]; iY = f[1]; iZ = f[2];
    }
    inline TPoint3D(TFixed a, TFixed b, TFixed c)
    {
        iX = a; iY = b; iZ = c;
    }
    // Access grants.
    inline const TFixed& operator[] (int i) const
    {
        return (&iX)[i];
    }
    inline               TFixed& operator[] (int i)
    {
        return (&iX)[i];
    }
    // Casting.
    operator TFixed* ()
    {
        return (TFixed*)this;
    }
    operator const TFixed* () const
    {
        return (TFixed*)this;
    }
    // Unary operators.
    inline TPoint3D operator + (const TPoint3D& p) const
    {
        return p;
    }
    inline TPoint3D operator - (const TPoint3D& p) const
    {
        return TPoint3D(-p.iX, -p.iY, -p.iZ);
    }
    // Assignment operators.
    inline TPoint3D& operator += (const TPoint3D& p)
    {
        iX += p.iX; iY += p.iY; iZ += p.iZ; return *this;
    }
    inline TPoint3D& operator -= (const TPoint3D& p)
    {
        iX -= p.iX; iY -= p.iY; iZ -= p.iZ; return *this;
    }
    inline TPoint3D& operator *= (const TFixed i)
    {
        iX = FixMul(iX, i); iY = FixMul(iY, i); iZ = FixMul(iZ, i); return *this;
    }

    // Two params.
    friend inline TPoint3D operator + (const TPoint3D& a, const TPoint3D& b)
    {
        return TPoint3D(a.iX + b.iX, a.iY + b.iY, a.iZ + b.iZ);
    }
    friend inline TPoint3D operator - (const TPoint3D& a, const TPoint3D& b)
    {
        return TPoint3D(a.iX - b.iX, a.iY - b.iY, a.iZ - b.iZ);
    }
    // Cross product.
    friend inline TPoint3D operator ^ (const TPoint3D& a, const TPoint3D& b)
    {
        return TPoint3D(
            FixMul(a.iY, b.iZ) - FixMul(a.iZ, b.iY), FixMul(a.iZ, b.iX) - FixMul(a.iX, b.iZ),
            FixMul(a.iX, b.iY) - FixMul(a.iY, b.iX));
    }
    // Dot product.
    inline TFixed Normalize(TPoint3D& d) const
    {
        TFixed len = Length();
        if (len)
        {
            // Normalize axis.
            d.iX = FixDiv(iX, len);
            d.iY = FixDiv(iY, len);
            d.iZ = FixDiv(iZ, len);
        }
        return len;
    }
    inline TFixed Normalize()
    {
        // Compute length.
        TFixed   len = Length();
        // If possible to normalize.
        if (len)
        {
            // Normalize axis.
            iX = FixDiv(iX, len);
            iY = FixDiv(iY, len);
            iZ = FixDiv(iZ, len);
        }
        return len;
    }
    inline TFixed Length() const
    {
        return (FixSqrt(FixMul(iX, iX) + FixMul(iY, iY) + FixMul(iZ, iZ)));
    }
    inline TFixed Length2() const
    {
        return(FixMul(iX, iX) + FixMul(iY, iY) + FixMul(iZ, iZ));
    }

public:
    TFixed iX, iY, iZ;
};

// Vector declaration.
typedef TPoint3D TVector;

// Dot product.
inline TFixed operator * (const TPoint3D& a, const TPoint3D& b)
{
    register TFixed ret, tmp;

    asm(
        "SMULL %0, %1, %2, %5\n\t" // Long mul.
        "SMLAL %0, %1, %3, %6\n\t" // Long mul.
        "SMLAL %0, %1, %4, %7\n\t" // Long mul.
        "MOVS  %0, %0, LSR#16\n\t" // Shift low.
        "ADC %0, %0, %1, LSL#16\n\t" // shift high
        : // Output operands.
        "=&r" (ret), // %0
        "=&r" (tmp)  // %1
        : // Input operands.
        // Parameters.
        "r" (a.iX), // %2
        "r" (a.iY), // %3
        "r" (a.iZ), // %4
        "r" (b.iX), // %5
        "r" (b.iY), // %6
        "r" (b.iZ) // %7
        : // Clobbers registers.
        "cc"
        );
    return ret;
}

// Matrix declaration.
class TMatrix
{
public:
    inline const TFixed  operator[] (int i) const
    {
        return (&_11)[i];
    }
    inline TFixed& operator[] (int i)
    {
        return (&_11)[i];
    }
    inline const TFixed  operator()(int iRow, int iColumn) const
    {
        return (&_11)[iRow + (iColumn << 2)];
    }
    inline TFixed& operator()(int iRow, int iColumn)
    {
        return (&_11)[iRow + (iColumn << 2)];
    }
    // Casting.
    operator TFixed* ()
    {
        return (TFixed*)this;
    }
    operator const TFixed* () const
    {
        return (TFixed*)this;
    }
    // Rotation.
    inline void RotationX(TFixed aAngle);
    inline void RotationY(TFixed aAngle);
    inline void RotationZ(TFixed aAngle);
    void Rotation(TFixed aAngleX, TFixed aAngleY, TFixed aAngleZ);
    void RotationAxis(TFixed aAngle, TVector aAxis);
    inline void Scale(TFixed aScaleX, TFixed aScaleY, TFixed aScaleZ);
    inline void ScaleTransform(TFixed aScaleX, TFixed aScaleY, TFixed aScaleZ,
        TFixed aTx, TFixed aTy, TFixed aTz);
    inline void Scale(TFixed aScale)
    {
        Scale(aScale, aScale, aScale);
    }
    inline void Transform(TFixed aTx, TFixed aTy, TFixed aTz);
    inline void Indentity()
    {
        Scale(KFixOne, KFixOne, KFixOne);
    }

public:
    TFixed _11, _12, _13, _14;
    TFixed _21, _22, _23, _24;
    TFixed _31, _32, _33, _34;
};

// Multily two matrices.
void Multiply(const TMatrix& aScr1, const TMatrix& aScr2, TMatrix& aDest);

// Multiply vertor by matrix.
inline void FixVectorMatrixMul(const TFixed x, const TFixed y, const TFixed z, const TFixed* j, TFixed* k)
{
    register TFixed ret, tmp;

    asm(
        "SMULL %0, %1, %2, %5\n\t" // Long mul.
        "SMLAL %0, %1, %3, %6\n\t" // Long mul.
        "SMLAL %0, %1, %4, %7\n\t" // Long mul.
        "MOVS %0, %0, LSR#16\n\t" // Shift low.
        "ADC %0, %0, %1, LSL#16\n\t" // Shift high.
        "ADD %0, %0, %8\n\t" // Shift high.
        : // Output operands.
        "=&r" (ret), // %0
        "=&r" (tmp) // %1
        : // Input Operands.
        // Parameters.
        "r" (x), // %2
        "r" (y), // %3
        "r" (z), // %4
        "r" (j[0]), // %5
        "r" (j[1]), // %6
        "r" (j[2]), // %7
        "r" (j[3]) // %8
        : // Clobbers registers
        "cc"
        );
    k[0] = ret;
    asm(
        "SMULL %0, %1, %2, %5\n\t" // Long mul.
        "SMLAL %0, %1, %3, %6\n\t" // Long mul.
        "SMLAL %0, %1, %4, %7\n\t" // Long mul.
        "MOVS  %0, %0, LSR#16\n\t" // Shift low.
        "ADC %0, %0, %1, LSL#16\n\t" // Shift high.
        "ADD %0, %0, %8\n\t" // Shift high.
        : // Output operands.
        "=&r" (ret), // %0
        "=&r" (tmp) // %1
        : // Input operands.
        // Parameters.
        "r" (x), // %2
        "r" (y), // %3
        "r" (z), // %4
        "r" (j[4]), // %5
        "r" (j[5]), // %6
        "r" (j[6]), // %7
        "r" (j[7]) // %8
        : // Clobbers registers.
        "cc"
        );
    k[1] = ret;
    asm(
        "SMULL %0, %1, %2, %5\n\t" // Long mul.
        "SMLAL %0, %1, %3, %6\n\t" // Long mul.
        "SMLAL %0, %1, %4, %7\n\t" // Long mul.
        "MOVS %0, %0, LSR#16\n\t" // Shift low.
        "ADC %0, %0, %1, LSL#16\n\t"   // Shift high.
        "ADD %0, %0, %8\n\t" // Shift high.
        : // Output operands.
        "=&r" (ret), // %0
        "=&r" (tmp) // %1
        : // Input operands.
        // Parameters.
        "r" (x), // %2
        "r" (y), // %3
        "r" (z), // %4
        "r" (j[8]), // %5
        "r" (j[9]), // %6
        "r" (j[10]), // %7
        "r" (j[11]) // %8
        : // Clobbers registers.
        "cc"
        );
    k[2] = ret;
}

// Rotation on X-axis.
inline void TMatrix::RotationX(TFixed aAngle)
{
    register TFixed CosTemp, SinTemp;

    FixSinCos(aAngle, SinTemp, CosTemp);

    _11 = KFixOne;
    _12 = _13 = _14 = _21 = 0;
    _22 = CosTemp;
    _23 = -SinTemp;
    _24 = _31 = 0;
    _32 = SinTemp;
    _33 = CosTemp;
    _34 = 0;
}

// Rotation on Y-axis.
inline void TMatrix::RotationY(TFixed aAngle)
{
    register TFixed CosTemp, SinTemp;

    FixSinCos(aAngle, SinTemp, CosTemp);

    _11 = CosTemp;
    _12 = 0;
    _13 = SinTemp;
    _14 = _21 = 0;
    _22 = KFixOne;
    _23 = _24 = 0;
    _31 = -SinTemp;
    _32 = 0;
    _33 = CosTemp;
    _34 = 0;
}

// Rotation on Z-axis.
inline void TMatrix::RotationZ(TFixed aAngle)
{
    register TFixed CosTemp, SinTemp;

    FixSinCos(aAngle, SinTemp, CosTemp);

    _11 = CosTemp;
    _12 = -SinTemp;
    _13 = _14 = 0;
    _21 = SinTemp;
    _22 = CosTemp;
    _23 = _24 = 0;
    _31 = 0;
    _32 = 0;
    _33 = KFixOne;
    _34 = 0;
}

// Scale.
inline void TMatrix::Scale(TFixed aScaleX, TFixed aScaleY, TFixed aScaleZ)
{
    _11 = aScaleX;
    _12 = _13 = _14 = _21 = 0;
    _22 = aScaleY;
    _23 = _24 = _31 = _32 = 0;
    _33 = aScaleZ;
    _34 = 0;

}

// Scale and transform.
inline void TMatrix::ScaleTransform(TFixed aScaleX, TFixed aScaleY, TFixed aScaleZ,
    TFixed aTx, TFixed aTy, TFixed aTz)
{
    _11 = aScaleX;
    _12 = _13 = 0;
    _14 = aTx;
    _21 = 0;
    _22 = aScaleY;
    _23 = 0;
    _24 = aTy;
    _31 = _32 = 0;
    _33 = aScaleZ;
    _34 = aTz;
}

// Transform.
inline void TMatrix::Transform(TFixed aTx, TFixed aTy, TFixed aTz)
{
    _11 = KFixOne;
    _12 = _13 = 0;
    _14 = aTx;
    _21 = 0;
    _22 = KFixOne;
    _23 = 0;
    _24 = aTy;
    _31 = _32 = 0;
    _33 = KFixOne;
    _34 = aTz;
}

typedef TUint32 TArgb;

// Projected vertex structures.
class TXyz
{
public:
    union
    {
        TFixed iX;
        TFixed x;
    };
    union
    {
        TFixed iY;
        TFixed y;
    };
    union
    {
        TFixed iZ;
        TFixed oow;
    };

};

class TXyzRgb : public TXyz
{
public:
    union
    {
        TArgb iColor;
        TArgb clip;
    };

};

class TXyzTex : public TXyz
{
public:
    union
    {
        TArgb iU;
        TArgb u;
    };
    union
    {
        TArgb iV;
        TArgb v;
    };
};

class TXyzRgbTex : public TXyzRgb
{
public:
    union
    {
        TArgb iU;
        TArgb u;
    };
    union
    {
        TArgb iV;
        TArgb v;
    };
};

// Faces Structure.
class TFace3
{
public:
    TXyz* iI0;
    TXyz* iI1;
    TXyz* iI2;
};

class TFaceTex3 : public TFace3
{
public:
    TFixed iU0;
    TFixed iV0;

    TFixed iU1;
    TFixed iV1;

    TFixed iU2;
    TFixed iV2;
};

class TFaceRgb3
{
public:
    TAny* iI0;
    TAny* iI1;
    TAny* iI2;
    TArgb iC0;
    TArgb iC1;
    TArgb iC2;
};

class TFaceRgbTex3 : public TFace3
{
public:
    TArgb  iC0;
    TFixed iU0;
    TFixed iV0;

    TArgb  iC1;
    TFixed iU1;
    TFixed iV1;

    TArgb  iC2;
    TFixed iU2;
    TFixed iV2;
};

#endif