PWD = $(shell pwd)
classes = $(PWD)/Classes
buildDir = $(PWD)/build

.PHONY: all clean

all:
	ls $(buildDir) 2>/dev/null; \
	if [ $$? -ne 0 ]; then \
		echo "$(buildDir) does not exist, creating..."; \
		mkdir $(buildDir); \
	fi; \
	g++ $(classes)/*.cpp -o $(buildDir)/AddiFy -lcurl -lyaml-cpp -I/usr/include -std=c++20;

clean:
	ls $(buildDir) 2>/dev/null; \
	if [ $$? -ne 0 ]; then \
		echo "$(buildDir) does not exist, exiting..."; \
	else \
		echo "$(buildDir) cleaning up..."; \
		rm -r $(buildDir); \
		echo "$(buildDir) done."; \
	fi