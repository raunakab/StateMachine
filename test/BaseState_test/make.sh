BASE_STATE=./../../src/BaseState/BaseState.cpp



if [ -f "test" ]; then
	rm test
	clear
fi
g++ -std=c++17 test.cpp  $BASE_STATE -o test
if [ -f "test" ]; then
	clear
	./test
	rm test
fi
