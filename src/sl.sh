#!/bin/bash

version=2023
self=$0
if [ -L "$self" ]; then
    link=$(readlink "$self")
    case "$link" in
        /*) self=$link ;;
        *)  self=$(dirname "$self")/$link ;;
    esac
fi
bindir=$(dirname "$self")/../libexec/sl-classic

while [[ $# -gt 0 ]]; do
    case "$1" in
        --2023|--2010|--1985)
            version=${1#--}
            shift
            ;;
        *)
            break
            ;;
    esac
done

exec "$bindir/sl-$version" "$@"
