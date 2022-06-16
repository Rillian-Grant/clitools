all: build_dir binary installer_script
build_dir:
	mkdir -p ./build
binary: build_dir
	musl-gcc --static -o ./build/stdsplit stdsplit.c
installer_script: build_dir binary
	cp stdsplit-installer.sh ./build/stdsplit-installer.sh
	base64 ./build/stdsplit | sed 's/^/#bin/' >> ./build/stdsplit-installer.sh
