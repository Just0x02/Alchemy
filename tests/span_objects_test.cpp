#include "test.hpp"

#include <alchemy/assert.hpp>
#include <alchemy/span.hpp>
#include <alchemy/point.hpp>



class SpanObjectTest : public Test
{
public:
	SpanObjectTest() : Test("Data Span Test", "Testing the limits/edgecases of data span.", __FILE__) {};


	void RunTest() override
	{
		using namespace alc;
		
		// make span that holds 24 point struct pointers
		DataSpan<iPoint*> vertices(24);

		// initialize all points to zero
		vertices.map([&]() {
			iPoint *pt = new iPoint();
			
			pt->x = 0;
			pt->y = 0;

			return pt;
		});

		// // get first and last points and set them to 1, 1
		iPoint *first_pt = vertices.front();
		iPoint *last_pt  = vertices.back();

		first_pt->x = 1;
		first_pt->y = 1;

		last_pt->x = 1;
		last_pt->y = 1;

		// check for points that have been modified

		std::vector<iPoint*> modified_pts = vertices.filter([&](iPoint *pt, usize idx) {
			return pt->length() > 0;
		});

		assert(modified_pts.size() == 2, "Filter didn't detect all modified points! (!= 2)");
	}
};