#include "./../../src/BaseState/BaseState.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>



int main() {
	std::shared_ptr<BaseState> bs_0(new BaseState);
	std::shared_ptr<BaseState> bs_1(new BaseState);

	bool const result_0(bs_0->addJumper("default",bs_0));
	bool const result_1(bs_0->addJumper("basestate.bs_1",bs_1));
	bool const result_2(bs_1->addJumper("basestate.bs_0",bs_0));

	std::string const action_0("asdf");
	std::string const action_1("basestate.bs_1");

	std::shared_ptr<BaseState> transition_result_0(bs_0->transition(action_0));
	std::shared_ptr<BaseState> transition_result_1(bs_0->transition(action_1));

	printf("result_0:\t%i\n",result_0 ? 1 : 0);
	printf("result_1:\t%i\n",result_1 ? 1 : 0);
	printf("result_2:\t%i\n",result_2 ? 1 : 0);
	printf("transition_result_0:\t%p\n",&(*transition_result_0));
	printf("transition_result_1:\t%p\n",&(*transition_result_1));
	printf("actual address of bs_1:\t%p\n",&(*bs_1));
	
	return 0;
}