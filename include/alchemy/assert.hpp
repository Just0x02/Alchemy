#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <stdexcept>

// should be included in the stl
#define assert(cond, msg) do { if (!(cond)) throw new std::runtime_error(msg); } while(0)

#endif // __ASSERT_H__