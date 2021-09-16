export SHELL:=/bin/bash
export SHELLOPTS:=$(if $(SHELLOPTS),$(SHELLOPTS):)pipefail:errexit

.PHONY: build

.ONESHELL:
build:
		cd source
		mkdir build || true
		cd build
		cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -GNinja -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCMAKE_TOOLCHAIN_FILE=../../DevkitArm3DS.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCODEADDR=$(CODEADDR)
		ninja
		cp *.sym *.bin ../../

loader:
		cd loader
		export CODEADDR=0x0061cd90
		# THIS WILL CHANGE
		export DATAADDR=0x0086e460
		make build

clean:
		cd source
		rm -rf ./source/build ../newcode.bin ../newcode.elf ../newcode.sym ../basecode.ips ../newcode.bin ../newcode.sym

magikoopa:
		export CODEADDR=0x007cf000
		make build
		cd ../../
		make loader
		#Magikoopa --build --workdir .