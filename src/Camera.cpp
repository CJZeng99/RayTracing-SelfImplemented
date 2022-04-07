#include "Camera.h"

int Camera::w;
int Camera::h;
float Camera::zNear = 0.1f;
float Camera::zFar = 99.0f;

Camera::Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, const float fovy, const std::string outputFile)
    : eye(eye), center(center), fovy(fovy), outputFile(outputFile)
{
    float aspect = (float)w / (float)h;
    float pix = w * h;

    this->up = glm::normalize(up);
    down = -this->up;
    front = glm::normalize(center - eye);
    right = glm::normalize(glm::cross(front, up));
    viewX = aspect;
    viewY = 1.0f;
    viewZ = glm::tan(90.0f - fovy / 2.0f);

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

void Camera::SaveScreenshot() {
    FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

    std::cout << "Saving screenshot: " << outputFile << "\n";

    FreeImage_Save(FIF_PNG, img, outputFile.c_str(), 0);
}