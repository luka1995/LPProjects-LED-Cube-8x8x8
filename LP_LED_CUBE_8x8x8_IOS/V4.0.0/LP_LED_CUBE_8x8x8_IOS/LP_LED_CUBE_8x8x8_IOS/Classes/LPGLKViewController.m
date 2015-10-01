//
//  LPGLKViewController.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 30/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPGLKViewController.h"


#define cubeOFF GLKVector4Make(0.1f, 0.1f, 0.1f, 0.4f)
#define cubeON GLKVector4Make(0.0f, 0.4f, 1.0f, 1.0f)
#define background GLKVector4Make(0.2f, 0.2f, 0.2f, 1.0f)

//#define defaultRotation GLKVector3Make(48.0f, -21.5f, 0.0f)
#define defaultRotation GLKVector3Make(0.0f, 0.0f, 0.0f)

#define iphoneZoom -8.0f
#define ipadZoom -6.5f


@interface LPGLKViewController (){
    CGPoint touchBeganPoint;
    BOOL rotationEnded;
    GLKVector3 vectorRotateSave, vectorRotateSave1;
    BOOL loadedGLK;
}

@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, strong) NSMutableArray *cubes;
@property (nonatomic, assign) int playedEffectIndex;
@property (nonatomic, strong) NSTimer *timer;

@end


@implementation LPGLKViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    if (self.animation && [self.animation.effectsList count] > 0) {
        self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (!self.context) {
            NSLog(@"Failed to create ES context");
        }
        
        GLKView *glkView = (GLKView *)self.view;
        glkView.context = self.context;
        
        // Configure renderbuffers created by the view
        glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
        glkView.drawableDepthFormat = GLKViewDrawableDepthFormat16;
        glkView.drawableStencilFormat = GLKViewDrawableStencilFormat8;
        
        // Enable multisampling
        glkView.drawableMultisample = GLKViewDrawableMultisample4X;
        
        [self setupCubes];
        
        [self playEffects];
    }
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    
    if (self.timer) {
        [self.timer invalidate];
        self.timer = nil;
    }
}

- (void)viewDidLayoutSubviews
{
    for (LPCubeScene *cubeScene in self.cubes) {
        float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
        GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 0.0f, 50.0f);
        cubeScene.effect.transform.projectionMatrix = projectionMatrix;
        
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            cubeScene.zoom = iphoneZoom;
        } else {
            cubeScene.zoom = ipadZoom;
        }
    }
}

#pragma mark - Functions

- (void)setRotationHome
{
    for (LPCubeScene *cube in self.cubes) {
        cube.rotate =  defaultRotation;
    }
    
    vectorRotateSave = defaultRotation;
}

- (void)startAnimation
{
    if (self.timer) {
        [self.timer invalidate];
        self.timer = nil;
    }

    [self playEffects];
}

- (void)stopAnimation
{
    if (self.timer) {
        [self.timer invalidate];
        self.timer = nil;
    }
    
    _animationPlayer = NO;
    
    if ([self.delegateController respondsToSelector:@selector(animationStoped)]) {
        [self.delegateController animationStoped];
    }
}

#pragma mark - Animation

- (void)clearCube
{
    for (LPCubeScene *cubeScene in self.cubes) {
        cubeScene.effect.constantColor = cubeOFF;
    }
}

- (void)playEffects
{
    if (!_animationPlayer) {
        if ([self.delegateController respondsToSelector:@selector(animationStoped)]) {
            [self.delegateController animationStarted];
        }
    }
    
    _animationPlayer = YES;
    
    if (self.playedEffectIndex >= [self.animation.effectsList count]) self.playedEffectIndex = 0;
    
    LPCubeEffect *cubeEffect = [self.animation.effectsList objectAtIndex:self.playedEffectIndex];
    
    // Show effect
    
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            for (int z=0; z<8; z++) {
                BOOL state = (cubeEffect.cube[(x * 8) + y] & (1 << z)) ? YES : NO;
                
                LPCubeScene *cubeScene = [self.cubes objectAtIndex:((y * 64) + (x * 8) + z)];
                
                if (state) {
                    cubeScene.effect.constantColor = cubeON;
                } else {
                    cubeScene.effect.constantColor = cubeOFF;
                }
            }
        }
    }
    
    // Call next effect
    
    int delay = ((cubeEffect.delay + 1) * [[[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsMultiplierValues"] objectAtIndex:cubeEffect.delayUnit] intValue]);
    
    self.playedEffectIndex++;
    
    self.timer = [NSTimer scheduledTimerWithTimeInterval:(float)((float)delay / 1000) target:self selector:@selector(playEffects) userInfo:nil repeats:NO];
}

#pragma mark - GLKView

- (NSMutableArray *)cubes
{
    if (!_cubes) {
        _cubes = [NSMutableArray new];
    }
    return _cubes;
}

- (void)setupCubes
{
    float SPACING = 0.5;
    
    for (int x=0; x<8; x++) {
        for(int y=0; y<8; y++) {
            for(int z=0; z<8; z++) {
                LPCubeScene *cubeScene = [[LPCubeScene alloc] initWithFrame:self.view.frame context:self.context];
                cubeScene.translate = GLKVector3Make((SPACING * (x - 4)) + (SPACING / 2), (SPACING * (y - 4)) + (SPACING / 2), ((-SPACING * (z - 4)) + (SPACING / 2)) - SPACING);
                cubeScene.effect.constantColor = cubeOFF;
                cubeScene.rotate = defaultRotation;
                
                [self.cubes addObject:cubeScene];
            }
        }
    }
    
    [self.cubes makeObjectsPerformSelector:@selector(setupGL)];
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(background.x, background.y, background.z, background.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    [self.cubes makeObjectsPerformSelector:@selector(render)];
    
    if (!loadedGLK) {
        loadedGLK = YES;
        
        [ProgressHUD dismiss];
    }
}

#pragma mark - GLKViewControllerDelegate

-(void)update
{
    [self.cubes makeObjectsPerformSelector:@selector(update)];
}

#pragma mark - Touch events

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    
    touchBeganPoint = [touch locationInView:self.view];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    vectorRotateSave = vectorRotateSave1;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    
    CGPoint touchMovedPoint = [touch locationInView:self.view];
    CGFloat rotateX = touchBeganPoint.x - touchMovedPoint.x;
    CGFloat rotateY = touchBeganPoint.y - touchMovedPoint.y;
    
    //NSLog(@"%f %f", rotateX, rotateY);
    
    vectorRotateSave1 = GLKVector3Make(vectorRotateSave.x + rotateX, vectorRotateSave.y + rotateY, 0.0f);

    for (LPCubeScene *cube in self.cubes) {
        cube.rotate =  vectorRotateSave1;
    }
}

@end
