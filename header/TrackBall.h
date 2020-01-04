//
//  TrackBall.h
//  GLEditor
//
//  Created by Jaegwang Lim on 2020/01/03.
//  Copyright © 2020 Jaegwang Lim. All rights reserved.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TrackBall
{
private:

    double xpos, ypos;
    double pre_xpos, pre_ypos;

    glm::mat4 rotMatrix = glm::mat4(1.f);
    glm::mat4 transMatrix = glm::mat4(1.f);
    float scale = 1.f;

    glm::mat4 total = glm::mat4(1.f);
        
    
public:

    TrackBall() {}
    ~TrackBall() {}
    
    void trackMouseMove( const double x, const double y, const unsigned button, const float dt )
    {
        pre_xpos = xpos;
        pre_ypos = ypos;
        
        xpos = x;
        ypos = y;
        
        // update rotation
        if( button == 0 )
        {
            glm::vec3 dev(xpos-pre_xpos, -(ypos-pre_ypos), 0.f );
            float ang = glm::length(dev)*dt*5.f;
            
            if(ang > 1e-5f)
            {
                glm::vec3 axis = glm::cross(glm::vec3(0.f,0.f,1.f), dev);
                axis.x = 0.f;
                
                axis = glm::normalize(axis);
                
                glm::mat4 r = glm::rotate( ang*3.141592f/180.0f, axis );
                rotMatrix = r * rotMatrix;
            }
        }
        
        // update traslation
        if( button == 1 )
        {
            glm::vec3 dev( xpos-pre_xpos, -(ypos-pre_ypos), 0.f );
            glm::mat4 t = glm::translate( glm::mat4(1.f), dev*dt*0.3f );
            
            transMatrix = t * transMatrix;
        }
        
        // update scale
        if( button == 2 )
        {
            const float dev = (ypos-pre_ypos) * dt*0.2f;
            scale += dev;
            if( scale < 1e-10f ) scale = 10e-10f;
        }
    }
    
    glm::mat4 viewMatrix()
    {
        return transMatrix * rotMatrix;
    }
};
