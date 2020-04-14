STATE_MACHINE=./../../src/StateMachine/StateMachine.cpp
BASE_STATE=./../../src/BaseState/BaseState.cpp



if [ -f "test" ]; then
	rm test
	clear
fi
g++ test.cpp $STATE_MACHINE $BASE_STATE -o test
if [ -f "test" ]
	clear
	./test
	rm test
]
