#ifndef GUN_H
#define GUN_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

using namespace std;

class Gun
{
public:
     
    GLfloat vertices[160];
   GLuint indices2[111];
    GLuint VBO,VAO,EBO;
    
    void drawShape(float r,float l){
        vector<float> v;
        int n=12;
        float  val=3.14/6.0;
        
        float vertice[40]={
            
            -0.3f, 0.0f,  0.3f,       1.0f, 1.0f,
            -0.3f, 0.0f, -0.3f,       1.0f, 0.0f,
            0.3f, 0.0f, -0.3f,       0.0f, 0.0f,
            0.3f, 0.0f,  0.3f,       0.0f, 1.0f,
            -0.3f, 0.6f,  0.3f,       0.0f, 0.0f,
            -0.3f, 0.6f, -0.3f,       0.0f, 1.0f,
            0.3f, 0.6f, -0.3f,       1.0f, 1.0f,
            0.3f, 0.6f,  0.3f,       1.0f, 0.0f
            
        };
        for(int i=0;i<40;i++)v.push_back(vertice[i]);
        int indice[36] =
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
        
        vector<int> indices;
        for(int i=0;i<36;i++)indices.push_back(indice[i]);
        
        for(int i=0;i<n;i++){
            v.push_back(r*cos(val*i));
            v.push_back(0.0);
            v.push_back(r*sin(val*i));
            v.push_back(0.0);
            v.push_back(1.0);
        }
        for(int i=0;i<n;i++){
            v.push_back(r*cos(val*i));
            v.push_back((-l/2)-1.0);
            v.push_back(r*sin(val*i));
            v.push_back(1.0);
            v.push_back(0.0);
        }
        vector<int> ind;
        for(int i=0;i<n-1;i++){
            ind.push_back(i);
            ind.push_back(i+1);
            ind.push_back(n+i);
        }
        ind.push_back(11);
        ind.push_back(0);
        ind.push_back(23);
        for(int i=n;i<2*n-1;i++){
            ind.push_back(i);
            ind.push_back(i+1);
            ind.push_back(i-n+1);
        }
        ind.push_back(23);
        ind.push_back(12);
        ind.push_back(0);
        
//        indices.push_back(1);
//        indices.push_back(2);
//        indices.push_back(15);
//
        for(auto i:ind)indices.push_back(i+8);
        
        for(int i=0;i<v.size();i++){
            vertices[i]=(GLfloat)v[i];
        }
        for(int i=0;i<indices.size();i++){
        indices2[i]=(GLuint)indices[i];
    }
        
    }
    
    
    
    void generateGun(GLfloat r,GLfloat l){
        this->drawShape(r, l);
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
    
    void drawGun(GLint viewLoc,glm::mat4 view2){
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
