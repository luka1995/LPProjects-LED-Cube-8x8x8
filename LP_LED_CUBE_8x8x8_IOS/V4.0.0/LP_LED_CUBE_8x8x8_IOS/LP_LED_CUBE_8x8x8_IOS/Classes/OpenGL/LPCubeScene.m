//
//  LPCubeScene.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 16/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPCubeScene.h"


typedef struct {
    float Position[3];
} Vertex;

Vertex vertex[] = {
    // Front
    {0.1, -0.1, 0.1},
    {0.1, 0.1, 0.1},
    {-0.1, 0.1, 0.1},
    {-0.1, -0.1, 0.1},
    // Back
    {0.1, 0.1, -0.1},
    {-0.1, -0.1, -0.1},
    {0.1, -0.1, -0.1},
    {-0.1, 0.1, -0.1},
    // Left
    {-0.1, -0.1, 0.1},
    {-0.1, 0.1, 0.1},
    {-0.1, 0.1, -0.1},
    {-0.1, -0.1, -0.1},
    // Right
    {0.1, -0.1, -0.1},
    {0.1, 0.1, -0.1},
    {0.1, 0.1, 0.1},
    {0.1, -0.1, 0.1},
    // Top
    {0.1, 0.1, 0.1},
    {0.1, 0.1, -0.1},
    {-0.1, 0.1, -0.1},
    {-0.1, 0.1, 0.1},
    // Bottom
    {0.1, -0.1, -0.1},
    {0.1, -0.1, 0.1},
    {-0.1, -0.1, 0.1},
    {-0.1, -0.1, -0.1}
};

const GLubyte Indices[] = {
    // Front
    0, 1, 2,
    2, 3, 0,
    // Back
    4, 6, 5,
    4, 5, 7,
    // Left
    8, 9, 10,
    10, 11, 8,
    // Right
    12, 13, 14,
    14, 15, 12,
    // Top
    16, 17, 18,
    18, 19, 16,
    // Bottom
    20, 21, 22,
    22, 23, 20
};


@interface LPCubeScene ()

@property (nonatomic, assign) GLuint vertexArray;
@property (nonatomic, assign) GLuint vertexBuffer;
@property (nonatomic, assign) GLuint indexBuffer;

@end


@implementation LPCubeScene

-(void)update
{
    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, self.zoom);
    
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, GLKMathDegreesToRadians(-self.rotate.y), 1, 0, 0);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, GLKMathDegreesToRadians(-self.rotate.x), 0, 1, 0);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, GLKMathDegreesToRadians(self.rotate.z), 0, 0, 1);
    modelViewMatrix = GLKMatrix4Translate(modelViewMatrix, self.translate.x, self.translate.y, self.translate.z);
    
    self.effect.transform.modelviewMatrix = modelViewMatrix;
}

-(void)render
{
    [self.effect prepareToDraw];

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
    glBlendColor(1.0, 1.0, 1.0, self.effect.constantColor.w);
    
    glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, 0);
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    self.effect = [GLKBaseEffect new];

    self.effect.useConstantColor = GL_TRUE;
    
    // Make the line a red color
    self.effect.constantColor = GLKVector4Make(
                                               0.1f, // Red
                                               0.1f, // Green
                                               0.1f, // Blue
                                               0.4f);// Alpha

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
 
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Position));
}

@end
