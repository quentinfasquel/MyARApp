//
//  ARSceneViewController.h
//  MyARApp
//
//  Created by Quentin on 9/21/17.
//  Copyright © 2017 Quentin Fasquel. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SceneKit/SceneKit.h>

@interface ARSceneViewController : UIViewController
@property (weak, nonatomic) IBOutlet SCNView *sceneView;
@property (readonly, nonatomic) SCNScene *scene;
- (void)setupScene;
@end
