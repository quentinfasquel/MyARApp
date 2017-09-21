//
//  SceneViewController.swift
//  MyARApp
//
//  Created by Quentin on 9/21/17.
//  Copyright © 2017 Quentin Fasquel. All rights reserved.
//

import Foundation

class SceneViewController: ARSceneViewController {
  
  override func createScene() -> SCNScene {
    let scene = super.createScene()
    // Add anything else you want to the scene
    return scene
  }
  
  override func setupTrackables() {
    let imagePath = Bundle.main.path(forResource: "doritos-logo-big", ofType: "jpg")!
    let image = UIImage(named: imagePath)!
    addTrackable(imagePath, width: image.size.width, height: image.size.height)
  }
}
