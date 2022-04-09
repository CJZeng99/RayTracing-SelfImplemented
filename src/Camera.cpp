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

    front = glm::normalize(center - eye);
    right = glm::normalize(glm::cross(front, up));
    this->up = glm::normalize(glm::cross(right, front));
    down = -this->up;
    viewY = glm::tan(glm::radians(fovy / 2.0f));
    viewX = aspect * viewY;
    viewZ = 1.0f;

    // pixels initialization
    pixels = new unsigned char[3 * pix];
    // pixels = new unsigned char[3 * pix];
    for (int i = 0; i < 3 * pix; i++)
        pixels[i] = '\0';
}

Camera::~Camera()
{
    // clear pixels
    delete[] pixels;
}

void Camera::TakeScreenshot(const std::vector<Object*>& objList) {
    Raytracer::tracer(this, objList);
    //for (int i = 0; i < h/2; i++)
    //{
    //    for (int j = 1; j < w/2; j++)
    //    {
    //        pixels[3 * (i * w + j)] = '\255';         // blue
    //        pixels[3 * (i * w + j) + 1] = '\255';     // green
    //        pixels[3 * (i * w + j) + 2] = '\0';   // red
    //    }
    //}
    //for (int i = 0; i < h/2; i++)
    //{
    //    for (int j = 1; j < w/2; j++)
    //    {
    //        std::cerr << pixels[3 * (i * w + j)] << "\n";
    //    }
    //}
}

void Camera::SaveScreenshot() {
    FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);

    std::cout << "Saving screenshot: " << outputFile << "\n";
    FreeImage_Save(FIF_PNG, img, (OUTPUT_DIR + outputFile).c_str(), 0);
}