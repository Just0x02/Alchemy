#ifndef __FMODES_H__
#define __FMODES_H__

namespace alc
{
	// THESE AREN'T DEFINED ANYWHERE IN THE STL
	namespace fmodes
	{
		static const char *read = "r";
		static const char *read_bin = "rb";

		static const char *write = "w";
		static const char *write_bin = "wb";

		static const char *append = "a";
		static const char *append_bin = "ab";

		static const char *create_read = "r+";
		static const char *create_read_bin = "rb+";

		static const char *create_write = "w+";
		static const char *create_write_bin = "wb+";

		static const char *create_append = "a+";
		static const char *create_append_bin = "ab+";

		struct ModeRequest
		{
			bool append, read, write;
			bool create, bin;
		};

		const char *generate_mode(ModeRequest req)
		{
			char *mode; // see what i'm doing?

			if (!req.create && !req.bin)
			{
				mode = (char *) calloc(1, sizeof(char));
			}
			else if (!req.create || !req.bin)
			{
				mode = (char *) calloc(2, sizeof(char));

				if (req.create) mode[1] = '+';
				if (req.bin)    mode[1] = 'b';
			}
			else
			{
				mode = (char *) calloc(3, sizeof(char));

				mode[1] = 'b';
				mode[2] = '+';
			}

			if (req.append)     mode[0] = 'a';
			else if (req.write) mode[0] = 'w';
			else if (req.read)  mode[0] = 'r';

			return mode;
		}
	};
};

#endif // __FMODES_H__