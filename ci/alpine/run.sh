#!/bin/sh

set -e

export CI_DISTRO=alpine
/outside/ci/alpine/install.sh
sudo -E -u \#$HUID /outside/ci/alpine/test.sh
