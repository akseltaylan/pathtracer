#include "extents.h"

extents::extents() {
	for (int i = 0; i < num_plane_normals; ++i) {
		std::vector<float> plane_ds;
		plane_ds.push_back(k_infinity);
		plane_ds.push_back(-k_infinity);
		d.push_back(plane_ds);
	}
}

bool extents::intersect(const ray& r, std::vector<float> denoms, std::vector<float> numers, float& t_near, float& t_far, int& plane_idx) {
	for (int i = 0; i < num_plane_normals; ++i) {
		float new_t_near = (d[i][0] - numers[i]) / denoms[i];
		float new_t_far = (d[i][1] - numers[i]) / denoms[i];

		if (denoms[i] < 0) {
			std::swap(new_t_near, new_t_far);
		}

		if (new_t_near > t_near) {
			t_near = new_t_near;
			plane_idx = i;
		}
		if (new_t_far < t_far) {
			t_far = new_t_far;
		}
		if (t_near > t_far) return false;
	}
	//std::cout << "found an extent!" << std::endl;
	return true;
}