root="./service"
gtest="/opt/gtest-1.6.0"
gcovr="/usr/local/bin/gcovr"

clean:
	-rm -R build

all: build

build: clean build-prepare compile test

build-complete: build publish-coverage-report generate-documentation run-cppcheck

build-prepare:
	mkdir build
	mkdir build/main

compile: main/protocol/*.cpp main/*.cpp
	g++ $^ -o build/main/program -I include -fprofile-arcs -ftest-coverage

test: test-prepare test-compile
	./build/tests --gtest_output=xml:build/test-results.xml

test-prepare:
	g++ -I $(gtest)/include -I $(gtest) -c $(gtest)/src/gtest-all.cc -o build/gtest-all.o
	ar -rv build/libgtest.a build/gtest-all.o

test-compile: test/protocol/*.cpp main/protocol/*.cpp
	g++ -I $(gtest)/include -I include $(gtest)/src/gtest_main.cc $^ build/libgtest.a -o build/tests -pthread -fprofile-arcs -ftest-coverage

generate-documentation:
	doxygen doxygen.config

publish-coverage-report:
	$(gcovr) -r . -x -d -o build/coverage.xml

run-cppcheck:
	cppcheck --xml --enable=all -I include main 2> build/cppcheck.xml