#include "../Helper/helper.hpp"

namespace gamehacking::helper
{
	gamehacking::math::ViewMatrix CreateViewMatrix(gamehacking::math::Rotation rotation_in_degrees)
	{
		static auto origin = gamehacking::math::Vector3D(0, 0, 0);
		float radPitch = DEG2RAD(rotation_in_degrees.pitch_);
		float radYaw = DEG2RAD(rotation_in_degrees.yaw_);
		float radRoll = DEG2RAD(rotation_in_degrees.roll_);

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		static gamehacking::math::ViewMatrix matrix;

		matrix[0][0] = CP * CY;
		matrix[0][1] = CP * SY;
		matrix[0][2] = SP;
		matrix[0][3] = 0.f;

		matrix[1][0] = SR * SP * CY - CR * SY;
		matrix[1][1] = SR * SP * SY + CR * CY;
		matrix[1][2] = -SR * CP;
		matrix[1][3] = 0.f;

		matrix[2][0] = -(CR * SP * CY + SR * SY);
		matrix[2][1] = CY * SR - CR * SP * SY;
		matrix[2][2] = CR * CP;
		matrix[2][3] = 0.f;

		matrix[3][0] = origin.x_;
		matrix[3][1] = origin.y_;
		matrix[3][2] = origin.z_;
		matrix[3][3] = 1.f;

		return matrix;
	}

	gamehacking::math::Vector3D WorldToScreen(gamehacking::math::Vector3D location, gamehacking::math::Rotation rotation_in_degrees, gamehacking::math::Vector3D camera_location)
	{
		auto Screenlocation = gamehacking::math::Vector3D(0, 0, 0);

		auto tempMatrix = gamehacking::helper::CreateViewMatrix(rotation_in_degrees);

		gamehacking::math::Vector3D vAxisX, vAxisY, vAxisZ;

		vAxisX = gamehacking::math::Vector3D(tempMatrix[0][0], tempMatrix[0][1], tempMatrix[0][2]);
		vAxisY = gamehacking::math::Vector3D(tempMatrix[1][0], tempMatrix[1][1], tempMatrix[1][2]);
		vAxisZ = gamehacking::math::Vector3D(tempMatrix[2][0], tempMatrix[2][1], tempMatrix[2][2]);

		gamehacking::math::Vector3D vDelta = location - camera_location;
		gamehacking::math::Vector3D vTransformed = gamehacking::math::Vector3D(vDelta.DotProduct(vAxisY), vDelta.DotProduct(vAxisZ), vDelta.DotProduct(vAxisX));

		if (vTransformed.z_ < 1.f)
			vTransformed.z_ = 1.f;

		auto screen_resolution = gamehacking::game_functions::GetResolution();
		float ScreenCenterX = screen_resolution.x_ / 2;
		float ScreenCenterY = screen_resolution.y_ / 2;

		auto FovAngle = gamehacking::game_functions::GetFOV();
		auto tmpFOV = tanf(FovAngle * (float)PI / 360.f);

		gamehacking::math::Vector3D screen;
		screen.x_ = ScreenCenterX + vTransformed.x_ * (ScreenCenterX / tmpFOV) / vTransformed.z_;
		screen.y_ = ScreenCenterY - vTransformed.y_ * (ScreenCenterX / tanf(FovAngle * (float)PI / 360.f)) / vTransformed.z_;
		return screen;
	}
}