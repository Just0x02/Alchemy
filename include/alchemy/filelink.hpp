#ifndef __FILELINK_H__
#define __FILELINK_H__

#include "types.hpp"
#include "assert.hpp"
#include "fmodes.hpp"
#include "span.hpp"

#include <stdlib.h>
#include <io.h>

namespace alc
{
	// Hey kid... pssst... have you ever wanted to be like REALLY lazy with opening files?
	struct FileLink
	{
		const char *file_name;
		FILE *fptr = NULL; // will usually remain as a nullptr but occasionally be opened.
	
		FileLink(const char *file_name) : file_name(file_name) {};

		inline void _assert_file_opened() const
		{
			assert(this->fptr != NULL, "Could not open file: '" + string(this->file_name) + "' as the file pointer returned was NULL.");
		}

		inline void _open_file(const char *mode)
		{
			this->fptr = fopen(this->file_name, mode);
		}

		inline void _close_file()
		{
			fclose(this->fptr);
			this->fptr = NULL;
		}

		inline const usize size_of()
		{
			usize size;

			this->_open_file("r");
			this->_assert_file_opened();

			fseek(this->fptr, 0L, SEEK_END);
			size = ftell(this->fptr);

			this->_close_file();

			return size;
		}

		alc::DataSpan<i8> *read_bytes()
		{
			const usize file_size = this->size_of();
			DataSpan<i8> *output_buffer = new DataSpan<i8>(file_size);

			this->_open_file("r");
			this->_assert_file_opened();

			fread(output_buffer->begin(), sizeof(i8), file_size, this->fptr);

			this->_close_file();

			return output_buffer;
		}

		string read()
		{
			DataSpan<i8> *bytes = this->read_bytes();

			char *raw_chars = new char[bytes->len];
			strcpy(raw_chars, (char *) bytes->data);

			delete bytes;

			return string(raw_chars);
		}

		// these overloaded functions might compile wrong because of the tomfoolery I did on the last lines of "types.hpp", if future me is reading this then: screw you.
		void write(string data, bool create_file = false) 
		{
			this->write(data.c_str(), create_file);
		}

		void write(const char *data, bool create_file = false) 
		{
			const char *mode = fmodes::generate_mode({
				.write  = true,
				.create = create_file
			});

			this->_open_file(mode);
			this->_assert_file_opened();

			fprintf(this->fptr, data);

			this->_close_file();
		}

		void append(string data, bool create_file = false) 
		{
			this->append(data.c_str(), create_file);
		}

		void append(const char *data, bool create_file = false) 
		{
			const char *mode = fmodes::generate_mode({
				.append  = true,
				.create = create_file
			});

			this->_open_file(mode);
			this->_assert_file_opened();

			fprintf(this->fptr, data);

			this->_close_file();
		}
	};
};

#endif // __FILELINK_H__