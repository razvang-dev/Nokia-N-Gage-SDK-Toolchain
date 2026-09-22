#!/usr/bin/env bash
set -euo pipefail
ROOT="${NGAGE_DEVKIT_ROOT:-$(cd "$(dirname "$0")/.." && pwd)}"
export PATH="$ROOT/toolchain/arm-epoc-pe/bin:$ROOT/toolchain/bin:$PATH"
echo "N-Gage/S60 6.1 offline dev kit"
echo "Root: $ROOT"
echo
"$ROOT/toolchain/bin/arm-epoc-pe-gcc" -v 2>&1 | tail -n 2
"$ROOT/toolchain/bin/arm-epoc-pe-ld" -v 2>&1 | head -n 2 || true
timeout 2 "$ROOT/toolchain/bin/rcomp" 2>&1 | head -n 12 || true
timeout 2 "$ROOT/toolchain/bin/bmconv" 2>&1 | head -n 5 || true
timeout 2 "$ROOT/toolchain/bin/petran" 2>&1 | head -n 7 || true
timeout 2 "$ROOT/toolchain/bin/makesis" 2>&1 | head -n 4 || true
echo
printf 'SDK e32base.h: '; test -f "$ROOT/sdk/Series60/Epoc32/Include/e32base.h" && echo OK
printf 'ARMI euser.lib: '; test -f "$ROOT/sdk/Series60/Epoc32/Release/armi/urel/euser.lib" && echo OK
printf 'Case alias AknWsEventObserver.h: '; test -e "$ROOT/caseinc/AknWsEventObserver.h" && echo OK
printf 'bmconv: '; test -x "$ROOT/toolchain/bin/bmconv" && echo OK
printf 'genaif: '; test -x "$ROOT/toolchain/bin/genaif" && echo OK
printf 'aiftool: '; test -x "$ROOT/toolchain/bin/aiftool" && echo OK
printf 'uidcrc: '; test -x "$ROOT/toolchain/bin/uidcrc" && echo OK
printf 'makesis: '; test -x "$ROOT/toolchain/bin/makesis" && echo OK
