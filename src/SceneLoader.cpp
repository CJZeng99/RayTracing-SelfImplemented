#include "SceneLoader.h"

SceneLoader::SceneLoader(Scene* scene)
    : scene(scene) {}

bool SceneLoader::ReadVals(std::stringstream& s, const int numvals, float* values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            std::cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

void SceneLoader::ReadFile(const char* filename)
{
    std::string str, cmd;
    std::ifstream in;
    in.open(filename);
    if (in.is_open()) {

        // I need to implement a matrix stack to store transforms.  
        // This is done using standard STL Templates 
        transfstack.push(glm::mat4(1.0f));  // identity

        getline(in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                std::stringstream s(str);
                s >> cmd;
                int i;
                float values[10]; // Position and color for light, colors for others
                                    // Up to 10 params for cameras.
                bool validinput; // Validity of input 

                // Process the light, add it to database.
                // Lighting Command
                if (cmd == "directional") {
                    if (scene->lights.size() == MAX_LIGHTS) { // No more Lights 
                        std::cerr << "Reached Maximum Number of Lights " << scene->lights.size() << " Will ignore further lights\n";
                    }
                    else {
                        validinput = ReadVals(s, 6, values); // Position/color for lts.
                        if (validinput) {
                            glm::vec3 direction = glm::vec3(values[0], values[1], values[2]);
                            glm::vec3 color = glm::vec3(values[3], values[4], values[5]);
                            Light* light = (Light*) new DirectionalLight(direction, color);
                            scene->lights.push_back(light);
                        }
                    }
                }

                if (cmd == "point") {
                    if (scene->lights.size() == MAX_LIGHTS) { // No more Lights 
                        std::cerr << "Reached Maximum Number of Lights " << scene->lights.size() << " Will ignore further lights\n";
                    }
                    else {
                        validinput = ReadVals(s, 6, values); // Position/color for lts.
                        if (validinput) {
                            glm::vec3 position = glm::vec3(values[0], values[1], values[2]);
                            glm::vec3 color = glm::vec3(values[3], values[4], values[5]);
                            Light* light = (Light*) new PointLight(position, color);
                            scene->lights.push_back(light);
                        }
                    }
                }

                // Material Commands 
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in 
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors. 

                else if (cmd == "ambient") {
                    validinput = ReadVals(s, 3, values); // colors 
                    if (validinput) {
                        Light::ambient = glm::vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "attenuation") {
                    validinput = ReadVals(s, 3, values); // colors 
                    if (validinput) {
                        for (int i = 0; i < 3; i++)
                            Light::attenuation[i] = values[i];
                    }
                }
                else if (cmd == "diffuse") {
                    validinput = ReadVals(s, 3, values);
                    if (validinput) {
                        diffuse = glm::vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "specular") {
                    validinput = ReadVals(s, 3, values);
                    if (validinput) {
                        specular = glm::vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "emission") {
                    validinput = ReadVals(s, 3, values);
                    if (validinput) {
                        emission = glm::vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "shininess") {
                    validinput = ReadVals(s, 1, values);
                    if (validinput) {
                        shininess = values[0];
                    }
                }

                // General Commands
                // 
                //
                //
                else if (cmd == "size") {
                    validinput = ReadVals(s, 2, values);
                    if (validinput) {
                        Camera::w = (int)values[0];
                        Camera::h = (int)values[1];
                    }
                }
                else if (cmd == "maxdepth") {
                    validinput = ReadVals(s, 1, values);
                    if (validinput) {
                        Raytracer::depth = (int)values[0];
                    }
                }
                else if (cmd == "output") {
                    s >> outputFile;
                }

                // Camera Commands
                else if (cmd == "camera") {
                    validinput = ReadVals(s, 10, values); // 10 values eye cen up fov
                    if (validinput) {
                        glm::vec3 eye = glm::vec3(values[0], values[1], values[2]);
                        glm::vec3 center = glm::vec3(values[3], values[4], values[5]);
                        glm::vec3 up = glm::vec3(values[6], values[7], values[8]);
                        float fovy = values[9];
                        scene->cam = new Camera(eye, center, up, fovy, outputFile);
                    }
                }

                else if (cmd == "vertex") {
                    validinput = ReadVals(s, 3, values);
                    if (validinput) {
                        vectices.push_back(glm::vec3(values[0], values[1], values[2]));
                    }
                }

                // I've left the code for loading objects in the skeleton, so 
                // you can get a sense of how this works.  
                // Also look at demo.txt to get a sense of why things are done this way.
                else if (cmd == "sphere") {
                    if (scene->objects.size() == MAX_OBJECTS) { // No more objects 
                        std::cerr << "Reached Maximum Number of Objects " << scene->objects.size() << " Will ignore further objects\n";
                    }
                    else {
                        validinput = ReadVals(s, 1, values);
                        if (validinput) {
                            glm::vec3 center = glm::vec3(values[0], values[1], values[2]);
                            float radius = values[3];
                            Object* obj = (Object*) new Sphere(center, radius);
                            obj->geoType = GeoType::sphere;

                            // Set the object's light properties
                            for (i = 0; i < 3; i++) {
                                obj->diffuse  = diffuse;
                                obj->specular = specular;
                                obj->emission = emission;
                            }
                            obj->shininess = shininess;

                            // Set the object's transform
                            obj->model = transfstack.top();

                            scene->objects.push_back(obj);
                        }
                    }
                }

                else if (cmd == "tri") {
                if (scene->objects.size() == MAX_OBJECTS) { // No more objects 
                    std::cerr << "Reached Maximum Number of Objects " << scene->objects.size() << " Will ignore further objects\n";
                }
                else {
                    validinput = ReadVals(s, 1, values);
                    if (validinput) {
                        Object* obj = (Object*) new Triangle(vectices[values[0]], vectices[values[1]], vectices[values[2]]);
                        obj->geoType = GeoType::tri;

                        // Set the object's light properties
                        for (i = 0; i < 3; i++) {
                            obj->diffuse = diffuse;
                            obj->specular = specular;
                            obj->emission = emission;
                        }
                        obj->shininess = shininess;

                        // Set the object's transform
                        obj->model = transfstack.top();

                        scene->objects.push_back(obj);
                    }
                }
                }

                else if (cmd == "translate") {
                    validinput = ReadVals(s, 3, values);
                    if (validinput) {
                        transfstack.top() *= glm::translate(glm::mat4(), glm::vec3(values[0], values[1], values[2]));
                    }
                }
                else if (cmd == "scale") {
                    validinput = ReadVals(s, 3, values);
                    if (validinput) {
                        transfstack.top() *= glm::scale(glm::mat4(), glm::vec3(values[0], values[1], values[2]));
                    }
                }
                else if (cmd == "rotate") {
                    validinput = ReadVals(s, 4, values);
                    if (validinput) {
                        transfstack.top() *= glm::rotate(glm::mat4(), values[3], glm::vec3(values[0], values[1], values[2]));
                    }
                }

                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top());
                }
                else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        std::cerr << "Stack has no elements.  Cannot Pop\n";
                    }
                    else {
                        transfstack.pop();
                    }
                }

                else {
                    std::cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }
    }
    else {
        std::cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}
