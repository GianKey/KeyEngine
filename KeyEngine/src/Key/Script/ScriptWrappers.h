#pragma once

#include "Key/Script/ScriptEngine.h"
#include "Key/Core/Input.h"

#include <glm/glm.hpp>

extern "C" {
	typedef struct _MonoString MonoString;
	typedef struct _MonoArray MonoArray;
}

namespace Key {
	namespace Script {

		// Math
		float Key_Noise_PerlinNoise(float x, float y);

		// Input
		bool Key_Input_IsKeyPressed(KeyCode key);
		bool Key_Input_IsMouseButtonPressed(MouseButton button);
		void Key_Input_GetMousePosition(glm::vec2* outPosition);
		void Key_Input_SetCursorMode(CursorMode mode);
		CursorMode Key_Input_GetCursorMode();

		// Entity
		void Key_Entity_CreateComponent(uint64_t entityID, void* type);
		bool Key_Entity_HasComponent(uint64_t entityID, void* type);
		uint64_t Key_Entity_FindEntityByTag(MonoString* tag);

		void Key_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform);
		void Key_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform);
		void Key_TransformComponent_GetTranslation(uint64_t entityID, glm::vec3* outTranslation);
		void Key_TransformComponent_SetTranslation(uint64_t entityID, glm::vec3* inTranslation);
		void Key_TransformComponent_GetRotation(uint64_t entityID, glm::vec3* outRotation);
		void Key_TransformComponent_SetRotation(uint64_t entityID, glm::vec3* inRotation);
		void Key_TransformComponent_GetScale(uint64_t entityID, glm::vec3* outScale);
		void Key_TransformComponent_SetScale(uint64_t entityID, glm::vec3* inScale);

		void* Key_MeshComponent_GetMesh(uint64_t entityID);
		void Key_MeshComponent_SetMesh(uint64_t entityID, Ref<Mesh>* inMesh);

		void Key_RigidBody2DComponent_ApplyLinearImpulse(uint64_t entityID, glm::vec2* impulse, glm::vec2* offset, bool wake);
		void Key_RigidBody2DComponent_GetLinearVelocity(uint64_t entityID, glm::vec2* outVelocity);
		void Key_RigidBody2DComponent_SetLinearVelocity(uint64_t entityID, glm::vec2* velocity);

		// Renderer
		// Texture2D
		void* Key_Texture2D_Constructor(uint32_t width, uint32_t height);
		void Key_Texture2D_Destructor(Ref<Texture2D>* _this);
		void Key_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count);

		// Material
		void Key_Material_Destructor(Ref<Material>* _this);
		void Key_Material_SetFloat(Ref<Material>* _this, MonoString* uniform, float value);
		void Key_Material_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture);

		void Key_MaterialInstance_Destructor(Ref<Material>* _this);
		void Key_MaterialInstance_SetFloat(Ref<Material>* _this, MonoString* uniform, float value);
		void Key_MaterialInstance_SetVector3(Ref<Material>* _this, MonoString* uniform, glm::vec3* value);
		void Key_MaterialInstance_SetVector4(Ref<Material>* _this, MonoString* uniform, glm::vec4* value);
		void Key_MaterialInstance_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture);
		// Mesh
		Ref<Mesh>* Key_Mesh_Constructor(MonoString* filepath);
		void Key_Mesh_Destructor(Ref<Mesh>* _this);
		Ref<Material>* Key_Mesh_GetMaterial(Ref<Mesh>* inMesh);
		Ref<Material>* Key_Mesh_GetMaterialByIndex(Ref<Mesh>* inMesh, int index);
		int Key_Mesh_GetMaterialCount(Ref<Mesh>* inMesh);

		void* Key_MeshFactory_CreatePlane(float width, float height);
	}
}