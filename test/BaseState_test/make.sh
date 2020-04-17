BASE_STATE=./../../src/BaseState/BaseState.cpp
JUMPER=./../../src/Jumper/Jumper.cpp



if [ -f "test" ]; then
	rm test
	clear
fi
g++ -std=c++17 test.cpp $JUMPER $BASE_STATE -o test
if [ -f "test" ]; then
	clear
	./test
	rm test
fi
