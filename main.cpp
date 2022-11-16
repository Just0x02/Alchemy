#include <stdio.h>

#include <alchemy/win_interop.hpp>
#include <alchemy/random.hpp>
#include <alchemy/cstd/alcio.h>

#include "tests/test.hpp"
#include "tests/data_span_test.cpp"
#include "tests/span_objects_test.cpp"
#include "tests/file_read_test.cpp"

int main(void)
{
	alc::_allow_win_interop();
	alc::random::seed();

	u64 buffer_size;
	byte_t *byte_buffer = alc::read_file_bytes("./tests/test_file.txt", &buffer_size);

	printf("READ %llu BYTES: %s", buffer_size, byte_buffer);

	// REGISTER_TEST(DataSpanTest);
	// REGISTER_TEST(SpanObjectTest);
	// REGISTER_TEST(FileReadTest);

	// RUN_TESTS();
}