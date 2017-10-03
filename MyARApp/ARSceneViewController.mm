//
//  ARSceneViewController.mm
//  MyARApp
//
//  Created by Quentin on 9/21/17.
//  Copyright © 2017 Quentin Fasquel. All rights reserved.
//

#import "ARSceneViewController.h"
#import "ARToolkitExtensions.h"

#include <AR6/ARController.h>

@interface ARSceneViewController () <SCNSceneRendererDelegate> {
  ARController *arController;
  int contextWidth;
  int contextHeight;
  bool contextRotate90;
  bool contextFlipH;
  bool contextFlipV;
  bool contextWasUpdated;
  int32_t viewport[4];
  std::vector<int> trackableIds;
  std::vector<bool> trackableVisible;
}
@property (weak, nonatomic) SCNNode *cameraNode;
@property (strong, nonatomic) NSMutableArray<SCNNode *> *trackableNodes;
- (void)setupAR;
- (void)tearDownAR;
@end

@implementation ARSceneViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  // Do any additional setup after loading the view.
  self.sceneView.delegate = self;
  self.sceneView.scene = [self createScene];
  self.sceneView.rendersContinuously = YES;

  [self setupAR];
}

- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}

- (void)dealloc {
  [self tearDownAR];
}


- (void)viewDidLayoutSubviews {
  [super viewDidLayoutSubviews];
  CGFloat scale = [UIScreen mainScreen].nativeScale;
  contextWidth = (int)CGRectGetWidth([UIScreen mainScreen].bounds) * scale;
  contextHeight = (int)CGRectGetHeight([UIScreen mainScreen].bounds) * scale;
  NSLog(@"%d %d", contextWidth, contextHeight);
  switch ([UIApplication sharedApplication].statusBarOrientation) {
    case UIInterfaceOrientationLandscapeLeft:
      contextRotate90 = false; contextFlipH = contextFlipV = true;
      break;
    case UIInterfaceOrientationPortraitUpsideDown:
      contextRotate90 = contextFlipH = contextFlipV = true;
      break;
    case UIInterfaceOrientationLandscapeRight:
      contextRotate90 = contextFlipH = contextFlipV = false;
      break;
    case UIInterfaceOrientationPortrait:
    case UIInterfaceOrientationUnknown:
    default:
      contextRotate90 = true; contextFlipH = contextFlipV = false;
      break;
  }
  contextWasUpdated = true;
}

- (BOOL)prefersStatusBarHidden {
  return YES;
}

- (BOOL)shouldAutorotate {
  return YES;
}

// MARK: -

- (nonnull SCNScene *)createScene {
  SCNScene *scene = [SCNScene scene];
  SCNNode *cameraNode = [SCNNode node];
  cameraNode.camera = [SCNCamera camera];
  cameraNode.position = SCNVector3Make(0, 0, 10);
  [scene.rootNode addChildNode:cameraNode];
  _cameraNode = cameraNode;
  
  _trackableNodes = [NSMutableArray new];
  return scene;
}

- (void)addTrackable:(NSString *)imagePath width:(CGFloat)width height:(CGFloat)height {
  const char *resourcePath = [imagePath cStringUsingEncoding:NSUTF8StringEncoding];
  char *trackableConfig;
  // TODO: find out relation between height and h
  asprintf(&trackableConfig, "2d;%s;%f", resourcePath, height);
  int trackableId = arController->addTrackable(trackableConfig);
  if (trackableId == -1) {
    ARLOGe("Error adding trackable.\n");
    return;
  }

  trackableIds.push_back(trackableId);
  trackableVisible.push_back(false); // not visible by default
  SCNPlane *plane = [SCNPlane planeWithWidth:width height:height];
  plane.firstMaterial.diffuse.contents = [UIColor redColor];
  plane.firstMaterial.transparency = 0.5f;
  SCNNode *trackableNode = [SCNNode nodeWithGeometry:plane];
  trackableNode.position = SCNVector3Zero;
  [self.cameraNode addChildNode:trackableNode];
  [self.trackableNodes addObject:trackableNode];
  free(trackableConfig);
}

- (void)setupTrackables {
  // Here you add all the trackables you want
}

- (void)setupAR {
  char vconf[] = "-preset=720p";

  [EAGLContext setCurrentContext:self.sceneView.eaglContext];

  // Initialise the ARController.
  arController = new ARController();
  if (!arController->initialiseBase()) {
    ARLOGe("Error initialising ARController.\n");
    return;
  }

  // Add trackables.
#ifdef DEBUG
  char buf[MAXPATHLEN];
  ARLOGe("CWD is '%s'.\n", getcwd(buf, sizeof(buf)));
#endif

  [self setupTrackables];

  arController->get2DTracker().setMaxSimultaneousTrackedImages((int)trackableIds.size());

  // Start tracking.
  arController->startRunning(vconf, NULL, NULL, 0);
}

- (void)tearDownAR {
  if (arController) {
    arController->displayFrameFinal(0);
    arController->shutdown();
    delete arController;
  }
}

// MARK: - Scene Renderer Delegate

- (void)renderer:(id<SCNSceneRenderer>)renderer updateAtTime:(NSTimeInterval)time {
  bool gotFrame = arController->capture();
  if (gotFrame) {
    if (!arController->update()) {
      ARLOGe("Error in ARController::update().\n");
      return;
    }
  }
}

- (void)renderer:(id<SCNSceneRenderer>)renderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time {
  [EAGLContext setCurrentContext:self.sceneView.eaglContext];

  if (arController->isRunning()) {
    if (contextWasUpdated) {
      arController->displayFrameInit(0);
      arController->displayFrameSettings(0, contextWidth, contextHeight, contextRotate90, contextFlipH, contextFlipV, ARView::HorizontalAlignment::H_ALIGN_CENTRE, ARView::VerticalAlignment::V_ALIGN_CENTRE, ARView::ScalingMode::SCALE_MODE_FIT, viewport);
      contextWasUpdated = false;
    }

    // Display the current video frame to the current OpenGL context.
    arController->displayFrame(0);
    
    // Get the projection matrix
    SCNMatrix4 projectionMatrix;
    SCNMatrix4 transformMatrix;
    ARdouble projection[16];
    arController->getProjectionMatrix(0, projection);
    projectionMatrix = SCNMatrix4Make(projection);
    
    // Flip works fine for landscapeLeft versus landscapeRight
    if (contextFlipV || contextFlipH) {
      projectionMatrix = SCNMatrix4Scale(projectionMatrix, contextFlipH ? -1 : 1, contextFlipV ? -1 : 1, 1);
    }

    // Rotation (SCNMatrix4Rotate takes radians)
    if (contextRotate90) {
      projectionMatrix = SCNMatrix4Rotate(projectionMatrix, (M_PI * 90)/180, 0, 0, -1);
    }
    
    // Look for trackables, and draw on each found one.
    size_t trackableCount = trackableIds.size();
    for (size_t i = 0; i < trackableCount; i++) {
      // Find the trackable for the given trackable ID.
      ARTrackable *trackable = arController->findTrackable(trackableIds[i]);
      SCNCamera *camera = self.cameraNode.camera;
      SCNNode *trackableNode = self.trackableNodes[i];
      if (trackable->visible) {
        transformMatrix = SCNMatrix4Make(trackable->transformationMatrix);
        camera.projectionTransform = projectionMatrix;
        trackableNode.transform = transformMatrix;
        trackableNode.opacity = 1;
      } else {
        trackableNode.opacity = 0;
      }
    }
  }
}

@end
