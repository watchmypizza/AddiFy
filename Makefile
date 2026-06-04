PWD = $(shell pwd)
classes = $(PWD)/Classes
buildDir = $(PWD)/build
includeDir = $(PWD)/Include

.PHONY: all clean

all:
	ls $(buildDir) 2>/dev/null; \
	if [ $$? -ne 0 ]; then \
		echo "$(buildDir) does not exist, creating..."; \
		mkdir $(buildDir); \
	fi; \
	g++ $(classes)/*.cpp -o $(buildDir)/AddiFy -lcurl -lyaml-cpp -I/usr/include -I$(includeDir) -std=c++20; \

windows:
	x86_64-w64-mingw32-g++ -std=c++20 Classes/*.cpp -o build/AddiFy.exe -static-libgcc -static-libstdc++ -lyaml-cpp -lcurl

clean:
	ls $(buildDir) 2>/dev/null; \
	if [ $$? -ne 0 ]; then \
		echo "$(buildDir) does not exist, exiting..."; \
	else \
		echo "$(buildDir) cleaning up..."; \
		rm -r $(buildDir); \
		echo "$(buildDir) done."; \
	fi