#!/usr/bin/env bash
# Installs the one missing system package raylib's bundled GLFW needs to compile on this machine.
# Run as: sudo bash scripts/install-deps.sh
# Everything else (libx11-dev, libxcursor-dev, libxrandr-dev, libxi-dev, libgl1-mesa-dev, libasound2-dev) is already installed.
set -euo pipefail

# Privileged: install the Xinerama development header (X11/extensions/Xinerama.h).
# Without it, raylib/src `make` fails at rglfw.o. Idempotent: apt is a no-op if already installed.
apt-get install -y libxinerama-dev

echo "Done. Now, as your normal user, run:  make"
