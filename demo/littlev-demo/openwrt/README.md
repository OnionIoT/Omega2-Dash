# How to Compile this Demo Code

> This is a demo program! If you're looking for a solid foundation for building an LVGL program for the Omega2 Dash, please see the lvgl quickstart template: https://github.com/OnionIoT/lv_example

Assuming:

* [OnionIoT/source build system](https://github.com/OnionIoT/source) is cloned to `~/source` and the instructions have been followed to set it up
* This repo has been cloned to  `~/Omega2-Dash`

Copy the OpenWRT package Makefile from this directory to the Onion feed in the build system

```
mkdir ~/source/feeds/onion/littlev-demo
cp Makefile ~/source/feeds/onion/littlev-demo/
```

Go to the build system 

```
cd ~/source
```

Install the littlev-demo package to the build system

```
./scripts/feeds update onion
./scripts/feeds list -r onion
./scripts/feeds install littlev-demo
```

Use menuconfig to select the package for compilation:

```
make menuconfig
```

Inside menuconfig go to:

* `Onion`
* `Utilities`
* `littlev-demo`
* Press space to enable compilation as a module
* Exit and save your configuration


Build the package 

```
make package/littlev-demo/clean
make package/littlev-demo/prepare USE_SOURCE_DIR=~/Omega2-Dash/demo/littlev-demo
make package/littlev-demo/compile V=99
```