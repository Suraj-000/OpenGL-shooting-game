#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

using namespace std;

class Square
{
public:
     GLfloat vertices[40]={
        
        -0.3f, 0.0f,  0.3f,       1.0f, 1.0f,
        -0.3f, 0.0f, -0.3f,       1.0f, 0.0f,
        0.3f, 0.0f, -0.3f,       0.0f, 0.0f,
        0.3f, 0.0f,  0.3f,       0.0f, 1.0f,
        -0.3f, 0.6f,  0.3f,       0.0f, 0.0f,
        -0.3f, 0.6f, -0.3f,       0.0f, 1.0f,
        0.3f, 0.6f, -0.3f,       1.0f, 1.0f,
        0.3f, 0.6f,  0.3f,       1.0f, 0.0f
        
    };
    GLuint indices[36] =
        {
            0, 1, 2,
            0, 2, 3,
            0, 1, 4,
            0, 3, 7,
            0, 4, 7,
            4, 5, 1,
            4, 7, 5,
            6, 5, 7,
            6, 3, 7,
            6, 3, 2,
            6, 5, 1,
            6, 2, 1
     
        };
    
    GLuint VBO,VAO,EBO;
    
    void generate_square(){
        glGenVertexArrays( 1, &VAO );
        glGenBuffers( 1, &VBO );
        glGenBuffers( 1, &EBO );
        glBindVertexArray(VAO);
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
          glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );
        // Position attribute
        glVertexAttribPointer( 0, 3, GL_FLOAT , GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )0 );
        glEnableVertexAttribArray( 0 );
        // TexCoord attribute
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
        glEnableVertexAttribArray( 2 );
        glBindVertexArray( 0 );
    }
    
    void drawSquare(GLint viewLoc,glm::mat4 view2){
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view2 ) );
        glBindVertexArray( VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glBindVertexArray( 0 );
    }
    
    void clearBuffer(){
        glDeleteVertexArrays( 1, &VAO );
        glDeleteBuffers( 1, &VBO );
        glDeleteBuffers( 1, &EBO );
    }
};

#endif
