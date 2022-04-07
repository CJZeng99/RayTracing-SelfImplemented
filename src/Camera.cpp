#include "Camera.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
    : eye(eye), center(center), up(up)
{
    float aspect = (float)w / (float)h;
    float pix = w * h;

    // camera orientation initialization
    Perspective(fovy, aspect, zNear, zFar);

    // pixels initialization
    pixels = new unsigned char[3 * pix];
    for (int i = 0; i < 3 * pix; i++)
        pixels[i] = '\0';
}

Camera::~Camera()
{
    // clear pixels
    delete[] pixels;
}

void Camera::Perspective(float fovy, float aspect, float zNear, float zFar)
{
    float d = glm::tan(90.0f - fovy / 2.0f);
    float d_asp = d / aspect;
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -(2.0f * zFar * zNear) / (zFar - zNear);
    projectionMtx = glm::mat4(
        d_asp, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, A, -1.0f,
        0.0f, 0.0f, B, 0.0f
    );
}

void Camera::SaveScreenshot() {
    FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

    std::cout << "Saving screenshot: " << outputFile << "\n";

    FreeImage_Save(FIF_PNG, img, outputFile.c_str(), 0);
}