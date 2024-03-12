#pragma once

#include "Key/Script/ScriptEngine.h"
#include "Key/Core/KeyCodes.h"

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

		// Entity
		void Key_Entity_GetTransform(uint64_t entityID, glm::mat4* outTransform);
		void Key_Entity_SetTransform(uint64_t entityID, glm::mat4* inTransform);
		void Key_Entity_CreateComponent(uint64_t entityID, void* type);
		bool Key_Entity_HasComponent(uint64_t entityID, void* type);

		void* Key_MeshComponent_GetMesh(uint64_t entityID);
		void Key_MeshComponent_SetMesh(uint64_t entityID, Ref<Mesh>* inMesh);

		// Renderer
		// Texture2D
		void* Key_Texture2D_Constructor(uint32_t width, uint32_t height);
		void Key_Texture2D_Destructor(Ref<Texture2D>* _this);
		void Key_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count);

		// Material
		void Key_Material_Destructor(Ref<Material>* _this);
		void Key_Material_SetFloat(Ref<Material>* _this, MonoString* uniform, float value);
		void Key_Material_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture);

		void Key_MaterialInstance_Destructor(Ref<MaterialInstance>* _this);
		void Key_MaterialInstance_SetFloat(Ref<MaterialInstance>* _this, MonoString* uniform, float value);
		void Key_MaterialInstance_SetVector3(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec3* value);
		void Key_MaterialInstance_SetTexture(Ref<MaterialInstance>* _this, MonoString* uniform, Ref<Texture2D>* texture);

		// Mesh
		Ref<Mesh>* Key_Mesh_Constructor(MonoString* filepath);
		void Key_Mesh_Destructor(Ref<Mesh>* _this);
		Ref<Material>* Key_Mesh_GetMaterial(Ref<Mesh>* inMesh);
		Ref<MaterialInstance>* Key_Mesh_GetMaterialByIndex(Ref<Mesh>* inMesh, int index);
		int Key_Mesh_GetMaterialCount(Ref<Mesh>* inMesh);

		void* Key_MeshFactory_CreatePlane(float width, float height);
	}
}