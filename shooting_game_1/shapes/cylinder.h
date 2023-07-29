#ifndef CYLINDER_H
#define CYLINDER_H

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

class Cylinder
{
public:
     GLfloat vertices[120];
    GLuint indices2[72];
    int n=12;
    GLuint VBO,VAO,EBO;
    void cylinderCoordinates(GLfloat r,GLfloat l){
            GLfloat val=3.14/6.0;
    vector<float> v;
    for(int i=0;i<n;i++){
        v.push_back(r*cos(val*i));
        v.push_back(0);
        v.push_back(r*sin(val*i));
        v.push_back(0.0);
        v.push_back(1.0);
    }
    for(int i=0;i<n;i++){
        v.push_back(r*cos(val*i));
        v.push_back(l);
        v.push_back(r*sin(val*i));
        v.push_back(1.0);
        v.push_back(0.0);
    }
    vector<int> indices;
    for(int i=0;i<n-1;i++){
        indices.push_back(i);
        indices.push_back(i+1);
        indices.push_back(n+i);
    }
    indices.push_back(11);
    indices.push_back(0);
    indices.push_back(23);
    for(int i=n;i<2*n-1;i++){
        indices.push_back(i);
        indices.push_back(i+1);
        indices.push_back(i-n+1);
    }
    indices.push_back(23);
    indices.push_back(12);
    indices.push_back(0);
    for(int i=0;i<v.size();i++){
        vertices[i]=(GLfloat)v[i];
    }
    for(int i=0;i<indices.size();i++){
    indices2[i]=(GLuint)indices[i];
}
    }
    
    void generateCylinder(GLfloat r,GLfloat l){
        this->cylinderCoordinates(r,l);
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
    
    void drawCylinder(GLint viewLoc,glm::mat4 view2){
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

