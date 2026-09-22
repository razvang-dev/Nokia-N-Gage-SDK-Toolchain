#!/usr/bin/env bash
# Source this file:  source ./env.sh
_NGAGE_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export NGAGE_DEVKIT_ROOT="$_NGAGE_ROOT"
export EPOCROOT="$_NGAGE_ROOT/sdk/Series60/"
export NGAGE_SDK="$_NGAGE_ROOT/sdk/Series60"
export NGAGE_SHARED_SDK="$_NGAGE_ROOT/sdk/Shared"
export NGAGE_CASEINC="$_NGAGE_ROOT/caseinc"
export NGAGE_TOOLCHAIN="$_NGAGE_ROOT/toolchain"
# dlltool invokes unprefixed 'as', so the target-specific bin directory must precede host /usr/bin.
export PATH="$_NGAGE_ROOT/toolchain/arm-epoc-pe/bin:$_NGAGE_ROOT/toolchain/bin:$PATH"
unset _NGAGE_ROOT
