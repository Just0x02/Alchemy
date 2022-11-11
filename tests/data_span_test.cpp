#include "test.hpp"

#include <alchemy/assert.hpp>
#include <alchemy/span.hpp>

class DataSpanTest : public Test
{
public:
	DataSpanTest() : Test("Data Span Test", "Testing the limits/edgecases of data span.", __FILE__) {};

	void RunTest() override
	{
		using namespace alc;
		
		// make span of 256 bytes
		alc::DataSpan<u8> bytes(0x100);

		// set all bytes to their index
		bytes.map([](u8 byte, usize i) {
			return (u8) i;
		});

		// check for validility
		assert(bytes.at(0x1) == 0x1,   "Value at index was not assigned value. (0x1 !=)");
		assert(bytes.at(0x32) == 0x32, "Value at index was not assigned value. (0x32 !=)");

		// empty span and check again
		bytes.clear();

		assert(bytes.at(0x1) != 0x1,   "Value at index was not assigned value. (0x1 ==)");
	}
};