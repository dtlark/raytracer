#include <iostream>

#include "Canvas.h" //#include "Tuples.h"
#include "Matrix.h"

float EPSILON = 0.001;
float INFIN = 999.0;

#define PI 3.141592653
float toRad = PI / 180.0;

using namespace std;

struct Ray {
	Point origin;
	Vector dir;
	float tMin, tMax;
	
	Ray(Point p, Vector v, float min, float max) {
		origin = p;
		dir = v;
		tMin = min;
		tMax = max;
	}
	Point getPointAt(float t) {
		return origin + dir * t;
	};
};

struct Sphere {
	Point center;
	float radius;
	Color material;

	Sphere(Point cent, float rad, Color materialColor) {
		center = cent;
		radius = rad;
		material = materialColor;
	}
};

struct Payload {
	Color color;
	Payload(Color col) {
		color = col;
	}
};

struct HitAttribute { // hit == intersection
	float t;
	Vector normal;
	Color material;
};

struct Light {
	Point position;
	Color color;
	float intensity;
};

struct Scene {
	vector<Sphere> spheres;
	vector<Light> lights;

};

Scene scene = Scene();


void closestHit(HitAttribute *hitAttribute, Ray *ray, Payload *payload) {

	//cout << "Clostest Hit " << endl;
	payload->color = hitAttribute->material; // * (-(ray.dir.dot(hitAttribute.normal)));
}


bool hitRaySphere(Ray *ray, Sphere sphere, HitAttribute *hitAttribute) {
	
	Vector OC = ray->origin - sphere.center;
	float a = ray->dir.dot(ray->dir);
	float b = 2.0 * OC.dot(ray->dir);
	float c = OC.dot(OC) - sphere.radius * sphere.radius;
	float disc = b * b - 4.0 * a * c;

	if (disc < 0.0) {
		return false;
	}
	
	disc = sqrt(disc);
	float t = (-b - disc) / (2.0 * a);
	
	if (t <= ray->tMin) {
		t = (-b + disc) / (2.0 * a);
	}

	if (t <= ray->tMin || t >= ray->tMax) {
		return false;
	}

	hitAttribute->t = t;
	hitAttribute->normal = (ray->getPointAt(t) - sphere.center).normalize();
	hitAttribute->material = sphere.material;

	return true;
}

bool traverseScene(Ray *ray, HitAttribute *hitAttr) {

	bool intersection = false;

	//vec3 tMin = (aabb.minP - ray.origin) / ray.direction;
	//vec3 tMax = (aabb.maxP - ray.origin) / ray.direction;

	//vec3 t1 = min(tMin, tMax);
	//vec3 t2 = max(tMin, tMax);

	//float tNear = max(max(max(t1.x, t1.y), t1.z), ray.tMin);
	//float tFar = min(min(min(t2.x, t2.y), t2.z), ray.tMax);

	//intersection = tNear <= tFar; // make new variable here to remove black box

	//if (intersection) {
		for (int i = 0; i < scene.spheres.size(); i++)
		{
			if (hitRaySphere(ray, scene.spheres[i], hitAttr))
			{
				intersection = true;
				ray->tMax = hitAttr->t;
			}
		}
	//}

	return intersection;
}

void traceRay(Ray *ray, Payload *payload) {
	HitAttribute hitAttr;
	if (traverseScene(ray, &hitAttr)) {
		closestHit(&hitAttr, ray, payload);
	}
}

int main() {
	
	// Canvas
	float width = 200;
	float height = 200;
	Canvas canvas = Canvas(width, height);
	float aspectRatio = width / height;

	// Camera
	float fov = 75.0 * toRad;
	float viewHeight = 2.0 * tan(fov / 2.0);
	float viewWidth = aspectRatio * viewHeight;

	Point cameraOrigin = Point(0, 0, 2); //camera eye
	Point cameraAt = Point(0, 0, 0);
	Vector cameraUp = Vector(0, 1, 0); //to define y axis
	Vector cameraDir = cameraOrigin - cameraAt; //at - eye

	Vector W = cameraDir.normalize();
	Vector U = cameraUp.cross(W).normalize();
	Vector V = W.cross(U);

	Vector cameraU = U * viewWidth / 2.0;
	Vector cameraV = V * viewHeight / 2.0;


	Sphere circleSphere = Sphere(Point(0, 0, 0), 0.5, Color(0.0, 0.0, 1.0));
	scene.spheres.push_back(circleSphere);

	for (int y = 0; y < height; y++) {

		//std::cerr << "\rLoading: " << y << "%" << std::flush;

		for (int x = 0; x < width; x++) {

			float ndcX = 2.0 * x / width - 1;  //normalized device coordinates
			float ndcY = 2.0 * y / height - 1;

			Vector pixelDir = -W + cameraV * ndcY + cameraU * ndcX;

			Ray ray = Ray(Point(ndcX, ndcY, -5), Vector(0, 0, 1), EPSILON, INFIN);

			Payload payload = Payload(Color(0.5, 0.5, 1)); //background color (no hit)
			traceRay(&ray, &payload);

			Color pixelColor = payload.color;
			canvas.setPixel(x, y, pixelColor);
		}
	}

	canvas.Save("picture");
}
