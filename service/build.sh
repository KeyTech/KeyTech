gtest="/opt/gtest-1.6.0"
gcovr="/usr/local/bin/gcovr"

# Clean
rm -R build
mkdir build
mkdir build/main

# Compile
g++ main/*.cc -c -o build/main/program.o -fprofile-arcs -ftest-coverage

# Test prepare
g++ -I $gtest/include -I $gtest -c $gtest/src/gtest-all.cc -o build/gtest-all.o
ar -rv build/libgtest.a build/gtest-all.o

# Test compile
g++ -I $gtest/include $gtest/src/gtest_main.cc build/main/program.o test/*Test.cc build/libgtest.a -o build/tests -pthread -fprofile-arcs

# Execute tests and publish the results in XML format
./build/tests --gtest_output=xml:build/test-results.xml

# Publish the coverage in XML format
$gcovr -r . -x -o build/coverage.xml
