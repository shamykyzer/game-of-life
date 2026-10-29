#!/usr/bin/env bash
# Zero-privilege check of the end state. Run as: bash scripts/verify.sh
set -uo pipefail
cd "$(dirname "$0")/.."
ok=0
check() { if eval "$2"; then echo "OK       $1"; else echo "MISSING  $1"; ok=1; fi; }
check "Xinerama header (libxinerama-dev)"   '[ -f /usr/include/X11/extensions/Xinerama.h ]'
check "raylib static lib built"             '[ -f raylib/src/libraylib.a ]'
check "game_of_life binary built"           '[ -x game_of_life ]'
check "no nested duplicate raylib clone"    '[ ! -d raylib/src/raylib ]'
exit $ok
