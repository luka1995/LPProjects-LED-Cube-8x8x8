//
//  LPMultipleCubes.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 26/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPMultipleCubes.h"


#define M_TAU (2*M_PI)

static BOOL initialized = NO;
static GLKVector3 vertices[8];
static GLKVector4 colors[8];
static GLKVector3 triangleVertices[36];
static GLKVector4 triangleColors[36];
static GLKBaseEffect *effect;


@interface LPMultipleCubes ()

@end


@implementation LPMultipleCubes
+ (void)initialize {
    if (!initialized) {
        vertices[0] = GLKVector3Make(-0.5, -0.5,  0.5); // Left  bottom front
        vertices[1] = GLKVector3Make( 0.5, -0.5,  0.5); // Right bottom front
        vertices[2] = GLKVector3Make( 0.5,  0.5,  0.5); // Right top    front
        vertices[3] = GLKVector3Make(-0.5,  0.5,  0.5); // Left  top    front
        vertices[4] = GLKVector3Make(-0.5, -0.5, -0.5); // Left  bottom back
        vertices[5] = GLKVector3Make( 0.5, -0.5, -0.5); // Right bottom back
        vertices[6] = GLKVector3Make( 0.5,  0.5, -0.5); // Right top    back
        vertices[7] = GLKVector3Make(-0.5,  0.5, -0.5); // Left  top    back
        
        colors[0] = GLKVector4Make(1.0, 0.0, 0.0, 1.0); // Red
        colors[1] = GLKVector4Make(0.0, 1.0, 0.0, 1.0); // Green
        colors[2] = GLKVector4Make(0.0, 0.0, 1.0, 1.0); // Blue
        colors[3] = GLKVector4Make(0.0, 0.0, 0.0, 1.0); // Black
        colors[4] = GLKVector4Make(0.0, 0.0, 1.0, 1.0); // Blue
        colors[5] = GLKVector4Make(0.0, 0.0, 0.0, 1.0); // Black
        colors[6] = GLKVector4Make(1.0, 0.0, 0.0, 1.0); // Red
        colors[7] = GLKVector4Make(0.0, 1.0, 0.0, 1.0); // Green
        
        int vertexIndices[36] = {
            // Front
            0, 1, 2,
            0, 2, 3,
            // Right
            1, 5, 6,
            1, 6, 2,
            // Back
            5, 4, 7,
            5, 7, 6,
            // Left
            4, 0, 3,
            4, 3, 7,
            // Top
            3, 2, 6,
            3, 6, 7,
            // Bottom
            4, 5, 1,
            4, 1, 0,
        };
        
        for (int i = 0; i < 36; i++) {
            triangleVertices[i] = vertices[vertexIndices[i]];
            triangleColors[i] = colors[vertexIndices[i]];
        }
        effect = [[GLKBaseEffect alloc] init];
        initialized = YES;
    }
}


-(id)initWithFrame:(CGRect)frame context:(EAGLContext *)context{
    self = [super init];
    if(self){
        self.bounds = frame;
        self.context = context;
        self.position = GLKVector3Make(-0.5, -0.25, 0.0);
        self.scale = GLKVector3Make(0.4, 0.4, 0.4);
        self.rotation = GLKVector3Make(1.0/8*M_TAU, 0, 1.0/8*M_TAU);
        self.rps = GLKVector3Make(0.3, 0.5, 0.4);
    }
    return self;
}


-(void)update {
}

-(void)render {
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //    GLKMatrix4 xRotationMatrix = GLKMatrix4MakeXRotation(self.rotation.x);
    //    GLKMatrix4 yRotationMatrix = GLKMatrix4MakeYRotation(self.rotation.y);
    //    GLKMatrix4 zRotationMatrix = GLKMatrix4MakeZRotation(self.rotation.z);
    //    GLKMatrix4 scaleMatrix     = GLKMatrix4MakeScale(self.scale.x, self.scale.y, self.scale.z);
    //    GLKMatrix4 translateMatrix = GLKMatrix4MakeTranslation(self.position.x, self.position.y, self.position.z);
    //
    //    GLKMatrix4 modelMatrix = GLKMatrix4Multiply(translateMatrix,GLKMatrix4Multiply(scaleMatrix,GLKMatrix4Multiply(zRotationMatrix, GLKMatrix4Multiply(yRotationMatrix, xRotationMatrix))));
    GLKMatrix4 modelMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 6.0);
    GLKMatrix4 viewMatrix = GLKMatrix4MakeLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
    effect.transform.modelviewMatrix = GLKMatrix4Multiply(viewMatrix, modelMatrix);
    
    effect.transform.projectionMatrix = GLKMatrix4MakePerspective(0.125*M_TAU, 2.0/3.0, 2, -1);
    
    [effect prepareToDraw];
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices);
    
    glEnableVertexAttribArray(GLKVertexAttribColor);
    glVertexAttribPointer(GLKVertexAttribColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glDisableVertexAttribArray(GLKVertexAttribPosition);
    glDisableVertexAttribArray(GLKVertexAttribColor);
    
}

- (void)setupGL{
}

- (void)tearDownGL{
}

@end
