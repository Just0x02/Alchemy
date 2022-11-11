#include "test.hpp"

#include <alchemy/assert.hpp>
#include <alchemy/fmodes.hpp>
#include <alchemy/span.hpp>
#include <alchemy/filelink.hpp>

class FileReadTest : public Test
{
public:
	FileReadTest() : Test("File Reading Test", "Testing the reading of files.", __FILE__) {};

	void RunTest() override
	{
		using namespace alc;
		
		// create a file link
		FileLink link("./tests/test_file.txt");

		const char *written_str = "Hello world!";

		// write some stuff
		link.write(written_str);

		// check if read bytes are equivalent.
		DataSpan<i8> *bytes = link.read_bytes();

		assert(strcmp(written_str, (char *) bytes->data) == 0, "Written and read bytes are not equal; read: '" + string((char *) bytes->data) + "'.");

		// check if read string is equivalent.
		string str = link.read();

		assert(strcmp(written_str, str.c_str()) == 0, "Written and read strings are not equal; read: '" + str + "'.");
	}
};