#!/usr/bin/env bash
set -euo pipefail
ROOT="${NGAGE_DEVKIT_ROOT:-$(cd "$(dirname "$0")/.." && pwd)}"
PRJ="${1:-$ROOT/examples/HelloNgage}"
PRJ="$(cd "$PRJ" && pwd)"
BUILD="$PRJ/build"; OBJ="$BUILD/obj"; OUT="$BUILD/package/System/Apps/HelloNgage"
TOOL="$ROOT/toolchain/bin"; SDK="$ROOT/sdk/Series60/Epoc32/Release/armi/urel"
export PATH="$ROOT/toolchain/arm-epoc-pe/bin:$TOOL:$PATH"
rm -rf "$BUILD"; mkdir -p "$OBJ" "$OUT"
UID1=0x10000079; UID2=0x100039CE; UID3=0x1020F4AE; CXX="$TOOL/arm-epoc-pe-g++"
COMMON=( -s -fomit-frame-pointer -O -march=armv4t -mthumb-interwork -c -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -D__DLL__ -D__SERIES60_10__ -D__SERIES60__ -DUID1=$UID1 -DUID2=$UID2 -DUID3=$UID3 -I"$PRJ/src" -I"$ROOT/caseinc" -I"$ROOT/sdk/Series60/Epoc32/Include" )
echo "[1/6] Compile"
for s in "$PRJ"/src/*.cpp; do b="$(basename "$s" .cpp)"; "$CXX" "${COMMON[@]}" "$s" -o "$OBJ/$b.o"; done
"$TOOL/arm-epoc-pe-ar" cr "$BUILD/hello.in" "$OBJ"/*.o
cat > "$BUILD/HelloNgage.def" <<DEF
EXPORTS
    NewApplication__Fv @ 1 NONAME
DEF
echo "[2/6] Two-pass EKA1 link"
"$TOOL/arm-epoc-pe-dlltool" -m arm_interwork --def "$BUILD/HelloNgage.def" --output-exp "$BUILD/HelloNgage.exp" --dllname 'HelloNgage[1020F4AE].app'
LIBS=( "$SDK/euser.lib" "$SDK/apparc.lib" "$SDK/cone.lib" "$SDK/eikcore.lib" "$SDK/avkon.lib" "$SDK/ws32.lib" )
"$TOOL/arm-epoc-pe-ld" -s -e _E32Dll -u _E32Dll "$BUILD/HelloNgage.exp" --dll --base-file "$BUILD/HelloNgage.bas" -o "$BUILD/HelloNgage.pass1.app" "$SDK/edll.lib" --whole-archive "$BUILD/hello.in" --no-whole-archive "$SDK/edllstub.lib" "$SDK/egcc.lib" "${LIBS[@]}"
"$TOOL/arm-epoc-pe-dlltool" -m arm_interwork --def "$BUILD/HelloNgage.def" --dllname 'HelloNgage[1020F4AE].app' --base-file "$BUILD/HelloNgage.bas" --output-exp "$BUILD/HelloNgage.exp2"
"$TOOL/arm-epoc-pe-ld" -s -e _E32Dll -u _E32Dll --dll "$BUILD/HelloNgage.exp2" -Map "$BUILD/HelloNgage.map" -o "$BUILD/HelloNgage.prepetran.app" "$SDK/edll.lib" --whole-archive "$BUILD/hello.in" --no-whole-archive "$SDK/edllstub.lib" "$SDK/egcc.lib" "${LIBS[@]}"
echo "[3/6] PETRAN"
"$TOOL/petran" -uid1 $UID1 -uid2 $UID2 -uid3 $UID3 -nocall "$BUILD/HelloNgage.prepetran.app" "$OUT/HelloNgage.app"
echo "[4/6] Resources"
CPP="$TOOL/cpp"
INC=( -I"$ROOT/caseinc" -I"$ROOT/sdk/Series60/Epoc32/Include" -I"$PRJ/res" )
"$CPP" -undef -nostdinc "${INC[@]}" "$PRJ/res/hello.rss" > "$BUILD/hello.rpp"
"$TOOL/rcomp" -6 -u -s"$BUILD/hello.rpp" -h"$BUILD/HelloNgage.rsg" -o"$OUT/HelloNgage.rsc"
"$CPP" -undef -nostdinc "${INC[@]}" "$PRJ/res/HelloNgage_caption.rss" > "$BUILD/HelloNgage_caption.rpp"
"$TOOL/rcomp" -6 -u -s"$BUILD/HelloNgage_caption.rpp" -o"$OUT/HelloNgage_caption.rsc"
echo "[5/6] AIF"
"$TOOL/bmconv" "$BUILD/hello.mbm" /c24"$PRJ/res/icon42x29.bmp" /1"$PRJ/res/icon42x29_mask.bmp" /c24"$PRJ/res/icon44x44.bmp" /1"$PRJ/res/icon44x44_mask.bmp"
cat > "$BUILD/hello.aifspec" <<SPEC
mbmfile=$BUILD/hello.mbm
ELangEnglish=Hello N-Gage
SPEC
"$TOOL/genaif" -u $UID3 "$BUILD/hello.aifspec" "$OUT/HelloNgage.aif"
echo "[6/6] Validate"
test -s "$OUT/HelloNgage.app"; test -s "$OUT/HelloNgage.rsc"; test -s "$OUT/HelloNgage_caption.rsc"; test -s "$OUT/HelloNgage.aif"
read -r U1 U2 U3 _ < <(od -An -tx4 -N16 "$OUT/HelloNgage.app")
test "$U1" = 10000079; test "$U2" = 100039ce; test "$U3" = 1020f4ae
echo; echo "SUCCESS"; echo "Install folder: $OUT"
