#pragma once

#include "../Math/math.hpp"
#include "../GameFunctions/game_functions.hpp"

#include <Windows.h>

namespace gamehacking::helper
{
	gamehacking::math::Vector3D WorldToScreen(gamehacking::math::Vector3D location, gamehacking::math::Rotation rotation_in_degrees, gamehacking::math::Vector3D camera_location);
}