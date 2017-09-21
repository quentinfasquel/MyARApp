//
//  ARToolkitExtensions.m
//  MyARApp
//
//  Created by Quentin on 9/21/17.
//  Copyright © 2017 Quentin Fasquel. All rights reserved.
//

#import "ARToolkitExtensions.h"

SCNMatrix4 SCNMatrix4Make(const ARdouble mat[16]) {
  return {
    mat[0], mat[1], mat[2], mat[3],
    mat[4], mat[5], mat[6], mat[7],
    mat[8], mat[9], mat[10], mat[11],
    mat[12], mat[13], mat[14], mat[15],
  };
}
