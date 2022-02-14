#include <iostream>
#include <algorithm>
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
	Light(Point pos, Color col, float intense) {
		position = pos;
		color = col;
		intensity = intense;
	}
};

struct Scene {
	vector<Sphere> spheres;
	vector<Light> lights;

};

struct AABB {
	Point minP;
	Point maxP;
	AABB(Point min, Point max) {
		minP = min;
		maxP = max;
	}
};


AABB aabb = AABB(Point(-1.5, -1.5, -1.5), Point(1.5, 1.5, 1.5));
Scene scene = Scene();


Vector minVec(Vector a, Vector b) {

	return (a.x < b.x ? a.x : b.x,
			a.y < b.y ? a.y : b.y,
			a.z < b.z ? a.z : b.z);
}

Vector maxVec(Vector a, Vector b) {

	return (a.x > b.x ? a.x : b.x,
			a.y > b.y ? a.y : b.y,
			a.z > b.z ? a.z : b.z);
}

void closestHit(HitAttribute *hitAttribute, Ray *ray, Payload *payload) {

	//cout << "Clostest Hit " << endl;

	Point pointOnSphere = ray->origin + ray->dir * hitAttribute->t;
	Vector lightVec = scene.lights[0].position - pointOnSphere;

	payload->color = hitAttribute->material * lightVec.normalize().dot(hitAttribute->normal) * scene.lights[0].intensity;    // * -ray->dir.dot(hitAttribute->normal);
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
	hitAttribute->normal = (ray->getPointAt(t) - sphere.center).normalize(); //normals must also be transformed
	hitAttribute->material = sphere.material;

	return true;
}

bool intersectAABB(Ray *ray) {

	Vector t0 = (aabb.minP - ray->origin) / ray->dir;
	Vector t1 = (aabb.maxP - ray->origin) / ray->dir;

	Vector tMin = minVec(t0, t1);
	Vector tMax = maxVec(t0, t1);

	float maxMin = max(max(t0.x, t0.y), t0.z);
	float minMax = min(min(t1.x, t1.y), t1.z);

	return maxMin <= minMax;
}


bool traverseScene(Ray *ray, HitAttribute *hitAttr) {

	bool intersection = false;
	//intersection = intersectAABB(ray); // FIX THIS
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

	Point cameraOrigin = Point(0, 0, -5); //camera eye
	Point cameraAt = Point(0, 0, 0);
	Vector cameraUp = Vector(0, 1, 0); //to define y axis
	Vector cameraDir = cameraOrigin - cameraAt; // eye - at

	Vector W = cameraDir.normalize();
	Vector U = cameraUp.cross(W).normalize();
	Vector V = W.cross(U);

	Vector cameraU = U * viewWidth / 2.0;
	Vector cameraV = V * viewHeight / 2.0;

	Sphere circleSphere = Sphere(Point(0, 0, 0), 0.5, Color(0.0, 0.0, 1.0));
	scene.spheres.push_back(circleSphere);

	Light light1 = Light(Point (1, 0, -3), Color (1, 1, 1), 1.5);
	scene.lights.push_back(light1);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			float ndcX = 2.0 * x / width - 1;  //normalized device coordinates
			float ndcY = 2.0 * y / height - 1;

			Vector pixelDir = -W + cameraV * ndcY + cameraU * ndcX;
			//Vector pixelDir = -W + V * (2.0 * y / height - 1.0)*(viewHeight/2.0) + U * (2.0 * x / width - 1.0) * (viewWidth / 2.0);

			Ray ray = Ray(cameraOrigin, pixelDir, EPSILON, INFIN);
				
	Matrix mat = Matrix();
	//mat.translate(-1, 0, 0);
	////mat.inverse();

	//cout << "x: " << ray.origin.x << " y: " << ray.origin.y << " z: " << ray.origin.z << endl;

	//ray.origin = mat * ray.origin;
	////ray.dir = mat * ray.dir;
	//cout << "Post: " << endl;
	//cout << "x: " << ray.origin.x << " y: " << ray.origin.y << " z: " << ray.origin.z << endl << endl;
	





			Payload payload = Payload(Color(0.5, 0.5, 1)); //background color (no hit)
			traceRay(&ray, &payload);

			Color pixelColor = payload.color;
			canvas.setPixel(x, y, pixelColor);
		}
	}

	canvas.Save("picture");
}
