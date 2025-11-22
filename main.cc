#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "color.h"

using namespace std;

double hitSphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

color rayColor(const ray &r)
{
    auto t = hitSphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{

    // image
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = point3(0, 0, 0);

    auto viewport_U = vec3(viewportWidth, 0, 0);
    auto viewport_V = vec3(0, -viewportHeight, 0);

    auto pixel_delta_U = viewport_U / imageWidth;
    auto pixel_delta_V = viewport_V / imageHeight;

    auto viewport_UpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewport_U / 2 - viewport_V / 2;
    auto pixel00_loc = viewport_UpperLeft + 0.5 * (pixel_delta_U + pixel_delta_V);

    // render
    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            auto pixelCenter = pixel00_loc + (i * pixel_delta_U) + (j * pixel_delta_V);
            auto ray_direction = pixelCenter - cameraCenter;
            ray r(cameraCenter, ray_direction);
            color pixelColor = rayColor(r);
            // auto pixel_color = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
            write_color(std::cout, pixelColor);
        }
    }

std:
    clog << "\rDone.                \n";
}