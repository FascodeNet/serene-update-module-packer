#!/usr/bin/env bash
mkdir build
cd build
cmake -GNinja ..
ninja -j4
cd ..
mkdir dist
dist_dir=$(realpath dist)
cd $1
./build.sh
zip -r "${dist_dir}/bufkun.zip" dist
cd ${dist_dir}
cat ../build/src/serene-update-module-packer ./bufkun.zip > ./serenelinux-update-wizard
chmod +x  ./serenelinux-update-wizard
rm bufkun.zip
