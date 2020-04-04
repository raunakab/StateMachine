ROOT=./../src

if [ -f "test_out" ]; then
	rm test_out
fi
g++ test.cpp $ROOT/Iterators.cpp -o test_out
if [ -f "test_out" ]; then
	clear
	./test_out
	rm test_out
fi
