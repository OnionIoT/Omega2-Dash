# install package to build system
./scripts/feeds update onion
./scripts/feeds list -r onion
./scripts/feeds install littlev-demo


# build package
make package/littlev-demo/clean
make package/littlev-demo/prepare USE_SOURCE_DIR=/home/ubuntu/littlev
make package/littlev-demo/compile V=99