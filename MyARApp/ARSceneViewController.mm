//
//  ARSceneViewController.mm
//  MyARApp
//
//  Created by Quentin on 9/21/17.
//  Copyright © 2017 Quentin Fasquel. All rights reserved.
//

#import "ARSceneViewController.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdocumentation"
#include <ARX/ARController.h>
#pragma GCC diagnostic pop
#import <OpenGLES/ES2/gl.h>

SCNMatrix4 SCNMatrix4Make(const ARdouble mat[16]) {
  return {
    mat[0], mat[1], mat[2], mat[3],
    mat[4], mat[5], mat[6], mat[7],
    mat[8], mat[9], mat[10], mat[11],
    mat[12], mat[13], mat[14], mat[15],
  };
}

#pragma mark -

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
  SCNMatrix4 projectionMatrix;
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
  cameraNode.name = @"defaultCamera";
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
  asprintf(&trackableConfig, "2d;%s;%f", resourcePath, width);
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
  plane.firstMaterial.doubleSided = YES;
  plane.name = @"plane";
  SCNNode *trackableNode = [SCNNode nodeWithGeometry:plane];
  trackableNode.position = SCNVector3Make(0.0, 0.0, -10.0);
  trackableNode.name = [NSString stringWithFormat:@"trackableNode_%d", trackableId];
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

  arController->get2dTracker()->setTwoDMultiMode(true);
//  arController->get2DTracker().setMaxSimultaneousTrackedImages((int)trackableIds.size());

  // Start tracking.
  arController->startRunning(vconf, NULL, NULL, 0);
}

- (void)tearDownAR {
  if (arController) {
    arController->drawVideoFinal(0);
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
      arController->drawVideoInit(0);
      arController->drawVideoSettings(0, contextWidth, contextHeight, contextRotate90,
                                      contextFlipH, contextFlipV,
                                      ARVideoView::HorizontalAlignment::H_ALIGN_LEFT,
                                      ARVideoView::VerticalAlignment::V_ALIGN_CENTRE,
                                      ARVideoView::ScalingMode::SCALE_MODE_FIT,
                                      viewport);

      // Get the projection matrix
      ARdouble projection[16];
      arController->projectionMatrix(0, 100, -1000, projection);
      projectionMatrix = SCNMatrix4Make(projection);
      if (contextFlipV || contextFlipH) {
        // Flip works fine for landscapeLeft versus landscapeRight
        projectionMatrix = SCNMatrix4Scale(projectionMatrix, contextFlipH ? -1 : 1, contextFlipV ? -1 : 1, 1);
      }
      if (contextRotate90) {
        // Rotation (SCNMatrix4Rotate takes radians)
        projectionMatrix = SCNMatrix4Rotate(projectionMatrix, (M_PI * 90)/180, 0, 0, -1);
      }
      contextWasUpdated = false;
    }

    // Display the current video frame to the current OpenGL context.
    arController->drawVideo(0);

    SCNCamera *camera = self.sceneView.pointOfView.camera;

    // Look for trackables, and draw on each found one.
    size_t trackableCount = trackableIds.size();
    float scaleFactor = 1000;
    for (size_t i = 0; i < trackableCount; i++) {
      // Find the trackable for the given trackable ID.
      ARTrackable *trackable = arController->findTrackable(trackableIds[i]);
      SCNNode *trackableNode = self.trackableNodes[i];
      if (trackable->visible) {
        SCNMatrix4 transformMatrix = SCNMatrix4Make(trackable->transformationMatrix);
        camera.projectionTransform = projectionMatrix;
        transformMatrix = SCNMatrix4Scale(transformMatrix, scaleFactor, scaleFactor, scaleFactor);
        trackableNode.transform = transformMatrix;
        trackableNode.opacity = 1;
      } else {
        trackableNode.opacity = 0;
      }
    }
  }
}

@end
