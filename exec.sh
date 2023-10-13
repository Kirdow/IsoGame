#!/bin/bash

case "$(uname -s)" in
    Darwin)
        cp platform/osx/Makefile Makefile
        ;;
    Linux)
        cp platform/lnx/Makefile Makefile
        ;;
    MINGW*|MSYS*|CYGWIN*)
        cp platform/win/Makefile Makefile
        ;;
    *)
        echo "Unknown OS"
        exit 1
        ;;
esac

if [[ $# -lt 1 ]]; then
    make && make run
    exit 0
fi

mode="$1"

if [[ "$mode" == "build" ]]; then
    make
elif [[ "$mode" == "run" ]]; then
    make run
else
    echo "Unknown mode."
    echo "Supported modes: build, run"
    echo "Leave blank for both"
fi