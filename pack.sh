#!/bin/bash

TARGET=xhrdin10

rm -rf "$TARGET"
mkdir "$TARGET"
cp -r --parents -t "$TARGET" \
CMakeLists.txt \
genEffect \
README.md \
pgr-projekt.pro \
cmake \
demos \
shaders \
src \
fonts/DejaVuSerif-Bold.ttf \
fonts/Roboto-Bold.ttf \
fonts/Roboto-Regular.ttf \
fonts/Roboto-Thin.ttf

zip -r "$TARGET" "$TARGET"