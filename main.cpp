#include <stdio.h>

#include <alchemy/win_interop.hpp>
#include <alchemy/random.hpp>

#include "tests/test.hpp"
#include "tests/data_span_test.cpp"
#include "tests/span_objects_test.cpp"
#include "tests/file_read_test.cpp"

int main(void)
{
	alc::_allow_win_interop();
	alc::random::seed();

	REGISTER_TEST(DataSpanTest);
	REGISTER_TEST(SpanObjectTest);
	REGISTER_TEST(FileReadTest);

	RUN_TESTS();
}