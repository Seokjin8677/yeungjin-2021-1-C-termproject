#pragma once
#include "ImageLayerInterface.h"
#include "ImageLayerImpl.h"

const ImageLayer DEFAULT_IMAGE_LAYER = { NULL, 0, RGB(80,232,34) , NULL, NULL,_initialize, _renderAll, _renderAndFadeIn, _renderAndFadeOut };