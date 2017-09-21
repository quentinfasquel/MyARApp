//
//  ARSceneViewController.m
//  MyARApp
//
//  Created by Quentin on 9/21/17.
//  Copyright © 2017 Quentin Fasquel. All rights reserved.
//

#import "ARSceneViewController.h"

#include <AR6/ARController.h>

@interface ARSceneViewController () <SCNSceneRendererDelegate>
@property (weak, nonatomic) SCNNode *cameraNode;
@end

@implementation ARSceneViewController

- (SCNScene *)scene {
  return self.sceneView.scene;
}

- (void)viewDidLoad {
  [super viewDidLoad];
  // Do any additional setup after loading the view.
  self.sceneView.delegate = self;
  self.sceneView.scene = [SCNScene scene];
  self.sceneView.rendersContinuously = YES;

  [self setupScene];
}

- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}

- (void)setupScene {
  SCNNode *cameraNode = [SCNNode node];
  cameraNode.camera = [SCNCamera camera];
  cameraNode.position = SCNVector3Make(0, 0, 10);
  [self.scene.rootNode addChildNode:cameraNode];
  _cameraNode = cameraNode;
}

// MARK: - Scene Renderer Delegate

- (void)renderer:(id<SCNSceneRenderer>)renderer updateAtTime:(NSTimeInterval)time {
  
}

- (void)renderer:(id<SCNSceneRenderer>)renderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time {
  
}

@end
