#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL2/SOIL2.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "shapes/pyramid.h"
#include "shapes/square.h"
#include "shapes/squarepyramid.h"
#include "shapes/cylinder.h"
#include "shapes/sphere.h"
#include "shapes/gun.h"


static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void moveBall(GLfloat cpx,GLfloat cpy, GLfloat cpz,GLfloat tpx,GLfloat tpy,GLfloat tpz);

GLfloat ballx=0,bally=0,ballz=-5.0;
const GLuint WIDTH = 800, HEIGHT = 600;
GLfloat x=-0.5f;
GLfloat y=0.5f;
double X=0.0;
double Y=0.0;
GLfloat p = 0.0f ,q = 0.0f;
GLboolean click=false;
float speed = 0.02f;
GLfloat h=1.0,j=1.0,k=-5.0;
GLfloat xspeed=0.0,yspeed=0.0,zspeed=0.0;
glm::vec3 spherePosition=glm::vec3(h,j,k);

int main()
{
    glfwInit( );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "OpenGL", nullptr, nullptr );
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent( window );
    glewExperimental = GL_TRUE;
    
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    glViewport( 0, 0, screenWidth, screenHeight );
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    Shader ourShader( "res/shaders/core.vs", "res/shaders/core.frag" );
    
//cylinder
    Cylinder cylinder;
    cylinder.generateCylinder(0.15,1.5);
//sphere
    Sphere sphere;
    sphere.generateSphere(0.3);
    Sphere sphere2;
    sphere2.generateSphere(0.2);
//    gun
    Gun gun;
    gun.generateGun(0.15, 1.5);
    
//    // Load and create a texture
    GLuint texture;
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    // Set our texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // Load, create texture and generate mipmaps
    int width, height;
    unsigned char *image = SOIL_load_image( "res/images/image6.png", &width, &height, 0, SOIL_LOAD_RGBA );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( image );
    glBindTexture( GL_TEXTURE_2D, 0 ); // Unbind texture when done, so we won't accidentily mess up our texture.
//
    glm::mat4 projection;
    projection = glm::perspective( 45.0f, ( GLfloat )screenWidth / ( GLfloat )screenHeight, 0.1f, 100.0f );
    //projection =   glm::ortho(0.0f, ( GLfloat )screenWidth, 0.0f, ( GLfloat )screenHeight, 0.1f, 1000.0f);

    
    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents( );
        
        glClearColor( 1.700f, 1.203f, 0.783f, 1.0f  );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        ourShader.Use( );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture );
        glUniform1i(glGetUniformLocation( ourShader.Program, "ourTexture1" ), 0 );

        glm::mat4 model = glm::mat4( 1.0f );
        glm::mat4 model2 = glm::mat4( 1.0f );
        glm::mat4 view = glm::mat4( 1.0f );
        glm::mat4 view2 = glm::mat4( 1.0f );
        glm::mat4 view3 = glm::mat4( 1.0f );
        glm::mat4 view4 = glm::mat4( 1.0f );

//        model = glm::rotate( model,x, glm::vec3( 1.0f, 0.0f, 0.0f ));
        model = glm::rotate( model,x, glm::vec3( 0.0f, 1.0f, 0.0f ));
        view = glm::translate( view, glm::vec3(0.0f,-1.0f, -5.0f ) );
 
        view3 = glm::translate( view, glm::vec3(1.0f,-1.0f, -5.0f ) );

        
        // Get their uniform location
        GLint modelLoc = glGetUniformLocation( ourShader.Program, "model" );
        GLint viewLoc = glGetUniformLocation( ourShader.Program, "view" );
        GLint projLoc = glGetUniformLocation( ourShader.Program, "projection" );
        // Pass them to the shaders
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1,GL_FALSE,glm::value_ptr(projection ));
        
        gun.drawGun(viewLoc, view);
        
    
        model2 = glm::rotate( model2,-y, glm::vec3( 0.0f, 0.0f, 1.0f ));
        model2 = glm::rotate( model2,-x, glm::vec3( 1.0f, 0.0f, 0.0f ));
        
        glm::mat3 rotationSubmatrix = glm::mat3(model2);
        glm::mat3 rotationOnlyMatrix = glm::mat3(rotationSubmatrix);
        glm::vec3 directionVector = glm::vec3(rotationOnlyMatrix[0][2], rotationOnlyMatrix[1][2], rotationOnlyMatrix[2][2]);
        float translationDistance = 0.01f;
        glm::vec3 translation = directionVector * translationDistance;
        spherePosition += translation;

        
        view3 = glm::translate( view3, glm::vec3(-1.0f,1.3f, 5.0f ) );

        // Pass them to the shaders
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model2 ) );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view3 ) );
        glUniformMatrix4fv( projLoc, 1,GL_FALSE,glm::value_ptr(projection ));
        
        cylinder.drawCylinder(viewLoc, view3);
        
        
        view4 = glm::translate( view4,glm::vec3(h,j,k) );
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model2 ) );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view4 ) );
        glUniformMatrix4fv( projLoc, 1,GL_FALSE,glm::value_ptr(projection ));
        h+=xspeed;
        j+=yspeed;
        k+=zspeed;
        if(abs(h-ballx)<0.01 && abs(j-bally)<0.01){
            cout<<"you hit the target"<<endl;
            h=0.0f;j=-0.6f;
            xspeed=0;
            yspeed=0;
            zspeed=0;
        }
        
        sphere2.drawSphere(viewLoc, view4);
        
        
        
        view2 = glm::translate( view2, glm::vec3(ballx,bally,ballz ) );
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model2 ) );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view2 ) );
        glUniformMatrix4fv( projLoc, 1,GL_FALSE,glm::value_ptr(projection ));
        
        sphere.drawSphere(viewLoc, view2);
        
        
        
        
        
        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        
        glfwSwapBuffers( window );
    }
    // Properly de-allocate all resources once they've outlived their purpose
    cylinder.clearBuffer();
    sphere.clearBuffer();
    sphere2.clearBuffer();
    gun.clearBuffer();


    glfwTerminate( );
    return EXIT_SUCCESS;
}


static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    double a,b;
    glfwGetCursorPos(window, &a,&b);
    if(click==true){
//        cout<<a<<" "<<b<<endl;
         X = -1.0 + 2.0 * (double)a / 800.0;
         Y = 1.0 - 2.0 * (double)b / 600.0;
//        cout<<X<<" "<<Y<<endl;
         
        
        x=(GLfloat)a/300;
        y=(GLfloat)b/300;
        
        p=x;
        q=y;
        
    }
    else{x=p;y=q;}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)click=true;
    else click=false;
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_B && action == GLFW_PRESS){
        float a,b,c;
        cout<<"enter the position of target ball:\n";
        cin>>a>>b>>c;
        ballx=(GLfloat)a;
        bally=(GLfloat)b;
        ballz=(GLfloat)c;
    }
    if(key == GLFW_KEY_SPACE && action==GLFW_PRESS){
        moveBall(h,j,k,ballx,bally,ballz);
    }
}
void moveBall(GLfloat cpx,GLfloat cpy, GLfloat cpz,GLfloat tpx,GLfloat tpy,GLfloat tpz){
    double dx = tpx - cpx;
    double dy = tpy-cpy;
    double dz=tpz-cpz;
    double distance = sqrt(dx * dx + dy * dy + dz*dz);
    double steps = distance / speed;
    double stepX = dx / steps;
    double stepY = dy / steps;
    double stepZ= dz / steps;

    
    xspeed=(GLfloat)stepX;
    yspeed=(GLfloat)stepY;
    zspeed=(GLfloat)stepZ;
}
