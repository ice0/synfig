
#include <synfig/blinepoint.h>
#include <synfig/real.h>
//#include <synfig/value.h>
//#include <synfig/valuenodes/valuenode_bline.h>
#include <ETL/hermite>

#include <vector>

#include "test_base.h"

using namespace synfig;

void fill_list(std::vector<BLinePoint>& list) {
	BLinePoint p;
	list.push_back(p);
	p.set_vertex(Point(0.0,1.0));
	list.push_back(p);
	p.set_vertex(Point(0.0,2.0));
	list.push_back(p);
}

Real
bline_length(const std::vector<BLinePoint>& bline, bool bline_loop, std::vector<Real> *lengths)
{
	if (lengths)
		lengths->clear();
	const std::vector<BLinePoint> list(bline);
	if (list.empty())
		return 0;
	size_t max_vertex_index(list.size());
	if(!bline_loop) max_vertex_index--;
	if(max_vertex_index < 1) return Real();

	if (lengths)
		lengths->reserve(max_vertex_index);

	// Calculate the lengths and the total length
	Real total_length = 0;
	for(size_t i0 = 0; i0 < max_vertex_index; ++i0) {
		size_t i1 = (i0 + 1)%list.size();
		const BLinePoint &blinepoint0 = list[i0];
		const BLinePoint &blinepoint1 = list[i1];
		etl::hermite<Vector> curve(blinepoint0.get_vertex(),   blinepoint1.get_vertex(),
								   blinepoint0.get_tangent2(), blinepoint1.get_tangent1());
		Real l=curve.length();
		if(lengths) lengths->push_back(l);
		total_length+=l;
	}

	return total_length;
}


void test_bline_length() {
	std::vector<BLinePoint> list;
	fill_list(list);
	
	bool loop = false;
	std::vector<Real> lengths;

	Real l = bline_length(list, loop, &lengths);
	ASSERT_EQUAL(2, lengths.size());
	ASSERT_APPROX_EQUAL(1.0, lengths[0]);
	ASSERT_APPROX_EQUAL(1.0, lengths[1]);
	ASSERT_APPROX_EQUAL(2.0, l);
}

int main() {
	TEST_SUITE_BEGIN()
		TEST_FUNCTION(test_bline_length)
	TEST_SUITE_END()

	return tst_exit_status;
}
