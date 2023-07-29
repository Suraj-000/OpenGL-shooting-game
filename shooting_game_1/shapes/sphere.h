#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "math.h"
#include<vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

using namespace std;

class Sphere
{
public:
     GLfloat vertices[310];
    GLuint indices2[360];
    
    GLuint VBO,VAO,EBO;
    
    void sphereCoordinates(GLfloat r){
        vector<float> v;
        float angle0=3.14/6;
        v.push_back(0.0);
        v.push_back(r*cos(0.0));
        v.push_back(0.0);
        v.push_back(0.5);
        v.push_back(-1.0);
        for(int i=1;i<=5;i++){
        float y=r*cos(angle0*i);
            for(int j=0;j<12;j++){
                float x=r*sin(angle0*i)*sin(angle0*j);
                float z=r*sin(angle0*i)*cos(angle0*j);
                v.push_back(x);
                v.push_back(y);
                v.push_back(z);
                v.push_back(0.5);
                v.push_back(1.0);
            }
        }
        v.push_back(0.0);
        v.push_back(-r*cos(0.0));
        v.push_back(0.0);
        v.push_back(0.0);
        v.push_back(1.0);

        vector<int> ind;

        for(int i=1;i<12;i++){
            ind.push_back(0);
            ind.push_back(i);
            ind.push_back(i+1);
        }
        ind.push_back(0);
            ind.push_back(12);
            ind.push_back(1);

        int n=12;
        for(int i=1;i<=11;i++){
             ind.push_back(i);
            ind.push_back(i+1);
            ind.push_back(n+i);
             ind.push_back(n+i);
            ind.push_back(n+i+1);
            ind.push_back(i+1);
        }
                 ind.push_back(12);
            ind.push_back(1);
            ind.push_back(24);
             ind.push_back(24);
            ind.push_back(13);
            ind.push_back(1);

            for(int i=n+1;i<n+12;i++){
             ind.push_back(i);
            ind.push_back(i+1);
            ind.push_back(n+i);
             ind.push_back(n+i);
            ind.push_back(n+i+1);
            ind.push_back(i+1);
        }
               ind.push_back(24);
            ind.push_back(13);
            ind.push_back(36);
             ind.push_back(36);
            ind.push_back(25);
            ind.push_back(13);

            for(int i=2*n+1;i<3*n;i++){
            ind.push_back(i);
            ind.push_back(i+1);
            ind.push_back(n+i);
            ind.push_back(n+i);
            ind.push_back(n+i+1);
            ind.push_back(i+1);
        }
            ind.push_back(36);
            ind.push_back(25);
            ind.push_back(48);
            ind.push_back(48);
            ind.push_back(37);
            ind.push_back(25);

        for(int i=3*n+1;i<4*n;i++){
            ind.push_back(i);
            ind.push_back(i+1);
            ind.push_back(n+i);
            ind.push_back(n+i);
            ind.push_back(n+i+1);
            ind.push_back(i+1);
        }
            ind.push_back(48);
            ind.push_back(37);
            ind.push_back(60);
            ind.push_back(60);
            ind.push_back(49);
            ind.push_back(37);

            for(int i=4*n+1;i<5*n;i++){
            ind.push_back(i);
            ind.push_back(i+1);
            ind.push_back(61);
        }
                ind.push_back(60);
            ind.push_back(49);
            ind.push_back(61);

        
    for(int i=0;i<v.size();i++){
        vertices[i]=(GLfloat)v[i];
    }
    for(int i=0;i<ind.size();i++){
    indices2[i]=(GLuint)ind[i];
}
    }
    
    void generateSphere(GLfloat r){
        this->sphereCoordinates(r);
        glGenVertexArrays( 1, &VAO );
        glGenBuffers( 1, &VBO );
        glGenBuffers( 1, &EBO );
        glBindVertexArray(VAO);
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
          glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices2 ), indices2, GL_STATIC_DRAW );
        // Position attribute
        glVertexAttribPointer( 0, 3, GL_FLOAT , GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )0 );
        glEnableVertexAttribArray( 0 );
        // TexCoord attribute
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
        glEnableVertexAttribArray( 2 );
        glBindVertexArray( 0 );
    }
    
    void drawSphere(GLint viewLoc,glm::mat4 view2){
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view2 ) );
        glBindVertexArray( VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);
        glBindVertexArray( 0 );
    }
    
    void clearBuffer(){
        glDeleteVertexArrays( 1, &VAO );
        glDeleteBuffers( 1, &VBO );
        glDeleteBuffers( 1, &EBO );
    }
};

#endif

