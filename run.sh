if [ ! -d ".src/build" ]; then
    mkdir build
fi

cd src/build
rm -rf ./*
cmake ..
make && echo "Build Successful, file in ./build/zjucmm"
cd ..