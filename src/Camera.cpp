#include "Camera.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float fovy, std::string outputFile)
    : eye(eye), center(center), fovy(fovy), outputFile(outputFile)
{
    float aspect = (float)w / (float)h;
    float pix = w * h;

    this->up = glm::normalize(up);
    down = -this->up;
    front = glm::normalize(center - eye);
    right = glm::normalize(glm::cross(front, up));

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

    // From Ravi's lecture
    float viewX = aspect;
    float viewY = 1.0f;
    float viewZ = glm::tan(90.0f - fovy / 2.0f);
    float d_asp = viewZ / aspect;
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -(2.0f * zFar * zNear) / (zFar - zNear);
    projectionMtx = glm::mat4(
        d_asp, 0.0f, 0.0f, 0.0f,
        0.0f, viewZ, 0.0f, 0.0f,
        0.0f, 0.0f, A, -1.0f,
        0.0f, 0.0f, B, 0.0f
    );
}

void Camera::SaveScreenshot() {
    FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

    std::cout << "Saving screenshot: " << outputFile << "\n";

    FreeImage_Save(FIF_PNG, img, outputFile.c_str(), 0);
}