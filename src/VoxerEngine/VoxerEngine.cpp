#include "stdafx.h"
#include "VoxerEngine.h"

const int32	VOXEL_IN_CHUNK_XY = 32;
const int32 VOXEL_IN_CHUNK_Z = 128;
const float	VOXEL_SIZE = 100.0f;
const float	CHUNK_SIZE_XY = VOXEL_IN_CHUNK_XY * VOXEL_SIZE;
const float	CHUNK_SIZE_Z = VOXEL_IN_CHUNK_Z * VOXEL_SIZE;
const float	CHUNK_LOADING_RADIUS = 300.0f * 100.0f;