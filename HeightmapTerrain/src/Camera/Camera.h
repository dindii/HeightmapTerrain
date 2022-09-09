#pragma once
#include "Math/mat4.h"
#include "Event/Event.h"
#include "Util/DeltaTime.h"

namespace Height
{
	/*    Very Primitive Camera */

	class Camera
	{
	public:
		Camera() : m_CameraLag(false), m_LagVal(0.0f), m_FOV(0.0f), m_Yaw(0.0f), m_Pitch(0.0f), m_AspectRatio(1.0f) {};
		Camera(const float AR, const vec3& position);
		//Camera() : m_Yaw(0.0f), m_Pitch(0.0f) {};

		mat4 GetViewMatrix() const;



		void AddCameraTargetPosition(vec3 pos, DeltaTime& dt);

		inline void SetCameraTarget(vec3& target) { m_CameraTarget = target; }
		void SetCameraPosition(vec3& position);
		inline void SetCameraYaw(float Yaw) { UpdateCameraVectors(); m_Yaw = Yaw; }
		inline void SetCameraPitch(float Pitch) { UpdateCameraVectors(); m_Pitch = Pitch; }

		inline vec3 GetCameraTarget() const { return m_CameraTarget; }
		inline vec3 GetCameraFacingDirection() const { return m_FacingDirection; }
		inline vec3 GetCameraUp() const { return m_CameraUp; }
		inline vec3 GetCameraRight() const { return m_CameraRight; }
		inline vec3 GetCameraPos() const { return m_CameraPos; }
		inline float GetFieldOfView() const { return m_FOV; }
		inline float GetCameraYaw() const { return m_Yaw; }
		inline float GetCameraPitch() const { return m_Pitch; }

		inline mat4 GetProjection() const { return m_Projection; }

		inline void SetProjection(float AR);
		inline void SetViewMatrix(mat4& view) { m_ViewMatrix = view; }
		inline void SetFieldOfView(const float FOV) { m_FOV = FOV; }
		inline void SetCameraLag(bool val) { m_CameraLag = val; }
		inline void SetCameraLagValue(float LagVal) { m_LagVal = LagVal; }

		void RemakeProjection(float newWidth, float newHeight);

		inline void LockCamera(bool lockCamera) { m_CameraLock = lockCamera; }

	private:
		bool m_CameraLock = false;
		void UpdateCameraVectors();

		vec3 m_FacingDirection;
		vec3  m_DesiredPos;
		bool  m_CameraLag;
		float m_LagVal;
		float m_FOV;
	private:
		vec3 m_CameraTarget;
		vec3 m_CameraUp;
		vec3 m_CameraRight;
		vec3 m_CameraPos;
	private:
		float m_Yaw, m_Pitch;
		float m_AspectRatio;

	private:
		mat4 m_ViewMatrix, m_Projection;
	};
}