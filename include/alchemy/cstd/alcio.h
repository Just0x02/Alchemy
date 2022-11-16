#ifndef __ALCIO_H__
#define __ALCIO_H__


#include "../types.hpp"
#include "c_alchemy.h"
#include <stdio.h>
#include <malloc.h>

#ifdef __cplusplus
namespace alc
{
#endif

const u64 get_file_size(const char *file_name)
{
	FILE *fptr = fopen(file_name, "r");
	u64 size;

	fseek(fptr, 0L, SEEK_END);
	size = ftell(fptr);

	fclose(fptr);

	return size;
}

byte_t *read_file_bytes(const char *file_name, u64 *bytes_read)
{
	FILE *fptr = fopen(file_name, "r");
	const u64 size = get_file_size(file_name);
	*bytes_read = size;

	byte_t *output_buffer = (byte_t *) calloc(sizeof(byte_t), size); 
	byte_t *buffer_iter = output_buffer;
	byte_t ch;

	do
	{
		ch = getc(fptr);
		*buffer_iter = ch;
		buffer_iter++;
	} while (ch != EOF);	

	return output_buffer;
}

#ifdef __cplusplus
}
#endif


#endif // __ALCIO_H__