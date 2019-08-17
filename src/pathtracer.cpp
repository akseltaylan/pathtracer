#include "pathtracer.h"
#define GI false
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);

pathtracer::pathtracer() {
	image * im;
	img = im;
	eyept = glm::vec3(0.0f, 0.0f, 1000.0f);
}

pathtracer::pathtracer(image * m_img) {
	img = m_img;
	pixels = new float[3 * img->width * img->height];
	eyept = glm::vec3(0.0f, 0.0f, 1000.0f);
}

void pathtracer::set_scene(scene * _s) {
	eyept = _s->get_camera();
	accel_struct = new bvh(_s);
	s = _s;
}

bool pathtracer::in_shadow(const ray& r, const glm::vec3& normal) {
	const float bias = .001f;
		
	ray shadow_ray(r.p, normalize(r.v - r.p));
	shadow_ray.p = r.p + bias * normal;
	float t = std::numeric_limits<float>::infinity();
	float u = std::numeric_limits<float>::infinity();
	float v = std::numeric_limits<float>::infinity();
	int idx = -1;
	const object * hitobj = trace(shadow_ray, t, idx, u, v);
	return hitobj != nullptr && !hitobj->is_light;
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

glm::vec3 pathtracer::compute_direct_lighting(const object * obj, const glm::vec3& phit, const glm::vec3& hit_normal, const bool& is_light) {
	if (!is_light) {
		
		glm::vec3 dl_contrib(0.0f, 0.0f, 0.0f);
		
		glm::vec3 ambient(0.0f);
		glm::vec3 diffuse(0.0f);
		glm::vec3 specular(0.0f);

		// compute ambient contribution
		const std::vector<light *>& lights = accel_struct->s->get_lights();
		ambient = obj->get_material()->ka * glm::vec3(0.4f) * lights[0]->get_intensity();

		// go through every light in scene	
		for (int i = 0; i < lights.size(); ++i) {

			if (!in_shadow(ray(phit, lights[i]->get_pos()), hit_normal)) {

				// compute diffuse contribution of light
				glm::vec3 l_m = normalize(lights[i]->get_pos() - phit);
				if (glm::dot(l_m, hit_normal) > 0) diffuse += lights[i]->get_color() * lights[i]->get_intensity() * obj->get_material()->kd * glm::dot(l_m, hit_normal);

				// compute specular contribution of light
				glm::vec3 r_m = reflected(-1.f * l_m, hit_normal);
				glm::vec3 view = normalize(eyept - phit);
				if (glm::dot(r_m, view) > 0 && glm::dot(l_m, hit_normal) > 0) {
					specular += obj->get_material()->ks * lights[i]->get_intensity() * powf(glm::dot(r_m, view), obj->get_material()->alpha);
				}
			}
		}

		//dl_contrib += ambient;
		dl_contrib += diffuse;
		//dl_contrib += specular;

		return dl_contrib / (float) lights.size();
		/*
		const std::vector<light *>& lights = accel_struct->s->get_lights();
		for (int i = 0; i < lights.size(); ++i) {
			if (!in_shadow(ray(phit, lights[i]->get_pos()), hit_normal)) {
				glm::vec3 light_dir = phit - lights[i]->get_pos();
				dl_contrib += lights[i]->get_color() * lights[i]->get_intensity() * std::max(0.0f, glm::dot(hit_normal, -1.0f * light_dir));
			}
		}
		return dl_contrib;*/
	}
	else {
		return obj->get_albedo();

	}
	return glm::vec3(0.0f);
}

const object * pathtracer::trace(const ray & r, float & t_near, int& tri_idx, float& u, float& v) {
	int closest = -1;
	const object * hit_obj = nullptr;
	hit_obj = accel_struct->intersect(r, t_near, tri_idx, u, v);
	return hit_obj;
}

glm::vec3 pathtracer::cast(const ray & r, const int & depth) {
	if (depth > MAX_DEPTH) return glm::vec3(0.0f);
	++num_rays;
	glm::vec3 hit_color = glm::vec3(0.0f, 0.0f, 0.0f);
	float t_near = std::numeric_limits<float>::infinity();
	float u = std::numeric_limits<float>::infinity();
	float v = std::numeric_limits<float>::infinity();
	int tri_idx = -1;
	const object * obj = trace(r, t_near, tri_idx, u, v);
	if (obj != nullptr) {
		glm::vec3 phit = glm::vec3(0.0f);
		glm::vec3 hit_normal = glm::vec3(0.0f);
		glm::vec2 uv_coords;
		obj->get_shading_properties(phit, hit_normal, t_near, u, v, tri_idx, r, uv_coords);
		if (obj->is_light) return obj->get_albedo();
		glm::vec3 col = obj->get_material()->get_albedo(uv_coords);
		
		glm::vec3 dl = compute_direct_lighting(obj, phit, hit_normal, obj->is_light);
		// global illumination
		glm::vec3 il = glm::vec3(0.0f);
		if (GI) {
			int samples = 8;
			float pdf = 1.0f / (2.0f * PI);

			// compute shaded point coordinate system using hit_normal
			glm::vec3 n_t = glm::vec3(0.0f);
			glm::vec3 n_b = glm::vec3(0.0f);
			shade_coord_system(hit_normal, n_t, n_b);

			for (int i = 0; i < samples; ++i) {
				
				// russian roulette termination
				float p = col.r > col.g && col.r > col.b ? col.r : col.g > col.b ? col.g : col.b;								
				float rint = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
				if (depth > 5) {
					if (rint < p * 0.9f) {
						col = col * (0.9f / p);
					}
					else {
						return glm::vec3(0.0f);
					}
				}

				// create samples on the hemisphere
				float rint1 = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
				float rint2 = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
				//float rint1 = distribution(generator);
				//float rint2 = distribution(generator);

				glm::vec3 sample = get_uniform_hemisphere_sample(rint1, rint2);
				glm::vec3 new_dir = convert_sample(n_t, n_b, hit_normal, sample);

				il += rint1 * cast(ray(phit + new_dir * 0.001f, new_dir), depth + 1) / pdf;
			}
			il /= (float)samples;
			hit_color = (2.0f*il + dl) / PI * col;
		}
		else {
			hit_color = dl * col;
		}
	}
	else {
		if (depth == 0) {
			hit_color = s->bg_color;
		}
	}
	return hit_color;
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	auto start = std::chrono::high_resolution_clock::now();

	implane * ip = new implane(img->width, img->height);
	std::vector<object*> objs = accel_struct->s->get_objs();

	int pixel_ct = 1;
	
#pragma omp parallel for schedule(dynamic, 2)
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {

			auto start = std::chrono::high_resolution_clock::now();
			glm::vec3 pixel_color(0.0f, 0.0f, 0.0f);
			int samples = 4;
			for (int k = 0; k < samples; ++k) {
				glm::vec3 cur_pixel = ip->nextpixel(k, j, i);
				ray primary_ray(eyept, cur_pixel - eyept);
				pixel_color += cast(primary_ray, 0);
			}
			img->set_pixel(j, i, pixel_color / (float) samples);
			
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