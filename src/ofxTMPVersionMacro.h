//
//  ofxTMPVersionMacro.h
//
//  Created by ISHII 2bit on 2016/04/28.
//
//

#pragma once
#include "ofConstants.h"

#define OFX_MAKE_OF_VERSION(major, minor, patch) (major * 10000 + minor * 100 + patch)
#define OFX_THIS_OF_VERSION OFX_MAKE_OF_VERSION(OF_VERSION_MAJOR, OF_VERSION_MINOR, OF_VERSION_PATCH)
#define OFX_THIS_OF_IS_OLDER_THAN(major, minor, patch) (OFX_OF_VERSION < OFX_MAKE_OF_VERSION(major, minor, patch))
#define OFX_THIS_OF_IS_OLDER_THAN_EQ(major, minor, patch) (OFX_OF_VERSION <= OFX_MAKE_OF_VERSION(major, minor, patch))
#define OFX_THIS_OF_IS_NEWER_THAN(major, minor, patch) (OFX_MAKE_OF_VERSION(major, minor, patch) < OFX_OF_VERSION)
#define OFX_THIS_OF_IS_NEWER_THAN_EQ(major, minor, patch) (OFX_MAKE_OF_VERSION(major, minor, patch) <= OFX_OF_VERSION)
