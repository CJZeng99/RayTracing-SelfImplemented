/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

#include <vector>

EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye 
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up 

#ifdef MAINPROGRAM 
vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
vec3 center(0.0,0.0,0.0) ; // Center look at point 
int amountinit = 5;
int w = 500, h = 500 ; // width and height 
float fovy = 90.0 ; // For field of view
#else 
EXTERN vec3 eyeinit ; 
EXTERN vec3 upinit ; 
EXTERN vec3 center ; 
EXTERN int amountinit;
EXTERN int w, h ;
EXTERN float fovy ; 
#endif

EXTERN int depth;
EXTERN std::string outputFile;

EXTERN bool useGlu; // Toggle use of "official" opengl/glm transform vs user 
EXTERN mat4 projection, modelview; // The mvp matrices
static enum {view, translate, scale} transop ; // which operation to transform 
enum shape {sphere, tri} ;
EXTERN float sx, sy ; // the scale in x and y 
EXTERN float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10 ; 
enum lightType { directional, point };
EXTERN float lightvec [3*numLights] ; // Light Positions
EXTERN float lightcolor[3*numLights] ; // Light Colors
EXTERN lightType lighttype[numLights] ; // Lights transformed by modelview
EXTERN int numused ;                     // How many lights are used 

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN float ambient[3];
EXTERN float diffuse[3];
EXTERN float specular[3];
EXTERN float emission[3];
EXTERN float shininess;

class Object {};
// For multiple objects, read from a file.  
const int maxobjects = 10; 
EXTERN int numobjects; 
EXTERN struct object {
  shape type;
  Object* geometry;
  float ambient[3];
  float diffuse[3];
  float specular[3];
  float emission[3];
  float shininess;
  mat4 transform; 
};
EXTERN object objects[maxobjects];
EXTERN std::vector<vec3> vertices;
