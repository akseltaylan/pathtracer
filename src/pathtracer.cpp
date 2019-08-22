#include "pathtracer.h"

std::default_random_engine generator;
std::uniform_real_distribution<float> distr(0.0f, 1.0f);

float pathtracer::rand_gen(short unsigned* seed) {
	return distr(generator);
}

pathtracer::pathtracer() {
	image * im;
	samples = 8;
	img = im;
	eyept = glm::vec3(0.0f, 0.0f, 1000.0f);
}

pathtracer::pathtracer(image * m_img) {
	int spp;
	std::cout << "How many samples per pixel? " << std::endl;
	while (std::cin >> spp && spp < 4) {
		std::cout << "Try again, how many samples per pixel? " << std::endl;
	}
	img = m_img;
	samples = spp;
	pixels = new float[3 * img->width * img->height];
	eyept = glm::vec3(0.0f, 0.0f, 1000.0f);
}

void pathtracer::set_scene(scene * _s) {
	eyept = _s->get_camera();
	accel_struct = new bvh(_s);
	s = _s;
}

void pathtracer::shade_coord_system(const glm::vec3& normal, glm::vec3& n_t, glm::vec3& n_b) {
	if (std::fabs(normal.y) < std::fabs(normal.x)) {
		n_t = normalize(glm::vec3(normal.z, 0.0f, -normal.x));
	}
	else {
		n_t = normalize(glm::vec3(0.0f, -normal.z, normal.y));
	}
	n_b = glm::cross(normal, n_t);
}

glm::vec3 pathtracer::get_uniform_hemisphere_sample(const float& rand1, const float& rand2) {
	float sin_t = sqrtf(1.0f - rand1 * rand1);
	float phi = rand2 * (2.0f * PI);
	float x = sin_t * cos(phi);
	float z = sin_t * sin(phi);
	return glm::vec3(x, rand1, z);
}

glm::vec3 pathtracer::convert_sample(const glm::vec3& n_t, const glm::vec3& n_b, const glm::vec3& normal, const glm::vec3& sample) {
	float x = sample.x * n_b.x + sample.y * normal.x + sample.z * n_t.x;
	float y = sample.x * n_b.y + sample.y * normal.y + sample.z * n_t.y;
	float z = sample.x * n_b.z + sample.y * normal.z + sample.z * n_t.z;
	return glm::vec3(x, y, z);
}

ray pathtracer::refract(const ray& r, const glm::vec3& hit_normal, const float& nc,  const float& ior) {
	float cos_i = glm::dot(r.v, hit_normal) < -1.0f ? -1.0f : glm::dot(r.v, hit_normal) > 1.0f ? 1.0f : glm::dot(r.v, hit_normal);
	float etai = nc;
	float etat = ior;
	glm::vec3 n = hit_normal;
	if (cos_i < 0.0f) cos_i = -cos_i;
	else {
		std::swap(etai, etat);
		n = -n;
	}
	float eta = etai / etat;
	float k = 1.0f - eta * eta * (1.0f - cos_i * cos_i);
	return ray(r.p, k < 0.0f ? glm::vec3(0.0f) : normalize( eta * r.v + (eta * cos_i - sqrtf(k)) * n));
}

ray pathtracer::reflect(const ray& r, const glm::vec3& phit, const glm::vec3& hit_normal) {
	return ray(phit, r.v - hit_normal * 2.0f * glm::dot(hit_normal, r.v));
}

void pathtracer::fresnel(const ray& r, const glm::vec3& hit_normal, const float& nc, const float& ior, float& fres) {
	float cos_i = glm::dot(r.v, hit_normal) < -1.0f ? -1.0f : glm::dot(r.v, hit_normal) > 1.0f ? 1.0f : glm::dot(r.v, hit_normal);
	float etai = nc;
	float etat = ior;
	if (cos_i > 0.0f) std::swap(etai, etat);
	float sin_t = etai / etat * sqrtf(std::max(0.0f, 1.0f - cos_i * cos_i)); // Snell's law
	// TIR
	if (sin_t >= 1.0f) {
		fres = 1.0f;
	}
	else {
		float cos_t = sqrtf(std::max(0.0f, 1.0f - sin_t * sin_t));
		cos_i = fabsf(cos_i);
		float r_s = ((etat * cos_i) - (etai * cos_t)) / ((etat * cos_i) + (etai * cos_t));
		float r_p = ((etai * cos_i) - (etat * cos_t)) / ((etai * cos_i) + (etat * cos_t));
		fres = (r_s * r_s + r_p * r_p) / 2.0f;
	}

}

const object * pathtracer::trace(const ray & r, float & t_near, int& tri_idx, float& u, float& v) {
	int closest = -1;
	const object * hit_obj = nullptr;
	hit_obj = accel_struct->intersect(r, t_near, tri_idx, u, v);
	return hit_obj;
}

glm::vec3 pathtracer::cast(const ray & r, const int & depth, unsigned short* seed) {
	++num_rays;

	float t_near = std::numeric_limits<float>::infinity();
	float u = std::numeric_limits<float>::infinity();
	float v = std::numeric_limits<float>::infinity();
	int tri_idx = -1;
	const object * obj = trace(r, t_near, tri_idx, u, v);

	if (obj == nullptr) {
		return s->bg_color;
	}

	glm::vec3 phit = glm::vec3(0.0f);
	glm::vec3 hit_normal = glm::vec3(0.0f);
	glm::vec2 uv_coords;
	obj->get_shading_properties(phit, hit_normal, t_near, u, v, tri_idx, r, uv_coords);
	glm::vec3 col = obj->get_material()->get_albedo(uv_coords);

	// global illumination
	glm::vec3 il = glm::vec3(0.0f);
	// russian roulette termination
	float p = col.r > col.g && col.r > col.b ? col.r : col.g > col.b ? col.g : col.b;
	if (depth > 5) {
		if (rand_gen(seed) > p || !p) {
			col = col * (1.0f / p);
		}
		else {
			return glm::vec3(0.0f);
		}
	}

	float pdf = 1.0f / (2.0f * PI);
	glm::vec3 normal_l = glm::dot(hit_normal, r.v) < 0.0f ? hit_normal : hit_normal * -1.0f;

	if (obj->get_material()->mtype == material::mat_type::diffuse) {
		// compute shaded point coordinate system using hit_normal
		glm::vec3 n_t = glm::vec3(0.0f);
		glm::vec3 n_b = glm::vec3(0.0f);
		shade_coord_system(hit_normal, n_t, n_b);

		// create samples on the hemisphere
		float rint1 = rand_gen(seed);
		float rint2 = rand_gen(seed);

		glm::vec3 sample = get_uniform_hemisphere_sample(rint1, rint2);
		glm::vec3 new_dir = convert_sample(n_t, n_b, hit_normal, sample);
		return  obj->get_material()->emissive + col * rint1 * (cast(ray(phit + new_dir * 0.001f, new_dir), depth + 1, seed)) / pdf;
	}
	else if (obj->get_material()->mtype == material::mat_type::specular) {
		return obj->get_material()->emissive + col * cast(reflect(r, phit, hit_normal), depth + 1, seed)  ;
	}
	else if (obj->get_material()->mtype == material::mat_type::glass) {
		float fres = 0.0f;
		float nc = 1.0f;
		float ior = 1.5f;
		fresnel(r, hit_normal, nc, ior, fres);
		bool into = glm::dot(hit_normal, r.v) > 0.0f;
		glm::vec3 bias = hit_normal * 0.00001f;
		glm::vec3 refr_col = glm::vec3(0.0f);
		ray orig;
		if (fres < 1.0f) {
			orig = ray(into ? phit + bias : phit - bias, r.v);
			refr_col = obj->get_material()->emissive + col * cast(refract(orig, hit_normal, nc, ior), depth+1, seed);
		}
		orig = ray(into ? phit - bias : phit + bias, r.v);
		ray refl = reflect(orig, phit, hit_normal);
		glm::vec3 refl_col = obj->get_material()->emissive + col * cast(refl, depth + 1, seed);
		return refl_col * fres + refr_col * (1.0f - fres);
	}
	else {
		return glm::vec3(0.0f);
	}
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	auto start = std::chrono::high_resolution_clock::now();

	implane * ip = new implane(img->width, img->height);
	std::vector<object*> objs = accel_struct->s->get_objs();

	int pixel_ct = 1;
	float gamma = 1.0f/2.2f;
	
#pragma omp parallel for schedule(dynamic, 2) 
	for (int i = 0; i < img->height; ++i) {
		fprintf(stderr, "\rRendering (%d spp)...", samples);
		for (int j = 0; j < img->width; ++j) {
			unsigned short seed[3] = { 0,0,j*j*j };
			auto start = std::chrono::high_resolution_clock::now();
			glm::vec3 pixel_color(0.0f, 0.0f, 0.0f);
			int jitter = -1;
			for (int k = 0; k < samples; ++k) {
				++jitter;
				if (jitter % 4 == 0) jitter = 0;
				glm::vec3 cur_pixel = ip->nextpixel(jitter, j, i);
				ray primary_ray(eyept, cur_pixel - eyept);
				pixel_color += cast(primary_ray, 0, seed)*(1.0f/(float)samples);
			}
			
			pixel_color = glm::vec3(powf(pixel_color.r, gamma), powf(pixel_color.g, gamma), powf(pixel_color.b, gamma)); // gamma correction
			img->set_pixel(j, i, pixel_color);
			
			if (PIXEL_DEBUG) {
				if (pixel_ct % 10000 == 0) {
					auto stop = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration<double, std::milli>(stop - start).count();
					std::cout << "Computed pixel " << pixel_ct << " in " << duration / 1000 << " seconds" << std::endl;
				}
			}

			++pixel_ct;
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double, std::milli>(stop - start).count();
	std::cout << "Rendered image in " << duration / 1000 << " seconds" << std::endl;
	img->create_image();
}