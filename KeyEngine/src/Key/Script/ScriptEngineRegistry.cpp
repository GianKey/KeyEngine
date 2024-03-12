#include "Kpch.h"
#include "ScriptEngineRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Key/Scene/Entity.h"
#include "ScriptWrappers.h"
#include <iostream>

namespace Key {

	std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;

	extern MonoImage* s_CoreAssemblyImage;

#define Component_RegisterType(Type) \
	{\
		MonoType* type = mono_reflection_type_from_name("Key." #Type, s_CoreAssemblyImage);\
		if (type) {\
			uint32_t id = mono_type_get_type(type);\
			s_HasComponentFuncs[type] = [](Entity& entity) { return entity.HasComponent<Type>(); };\
			s_CreateComponentFuncs[type] = [](Entity& entity) { entity.AddComponent<Type>(); };\
		} else {\
			KEY_CORE_ERROR("No C# component class found for " #Type "!");\
		}\
	}

	static void InitComponentTypes()
	{
		Component_RegisterType(TagComponent);
		Component_RegisterType(TransformComponent);
		Component_RegisterType(MeshComponent);
		Component_RegisterType(ScriptComponent);
		Component_RegisterType(CameraComponent);
		Component_RegisterType(SpriteRendererComponent);
	}

	void ScriptEngineRegistry::RegisterAll()
	{
		InitComponentTypes();

		mono_add_internal_call("Key.Noise::PerlinNoise_Native", Key::Script::Key_Noise_PerlinNoise);

		mono_add_internal_call("Key.Entity::GetTransform_Native", Key::Script::Key_Entity_GetTransform);
		mono_add_internal_call("Key.Entity::SetTransform_Native", Key::Script::Key_Entity_SetTransform);
		mono_add_internal_call("Key.Entity::CreateComponent_Native", Key::Script::Key_Entity_CreateComponent);
		mono_add_internal_call("Key.Entity::HasComponent_Native", Key::Script::Key_Entity_HasComponent);
		
		mono_add_internal_call("Key.MeshComponent::GetMesh_Native", Key::Script::Key_MeshComponent_GetMesh);
		mono_add_internal_call("Key.MeshComponent::SetMesh_Native", Key::Script::Key_MeshComponent_SetMesh);

		mono_add_internal_call("Key.Input::IsKeyPressed_Native", Key::Script::Key_Input_IsKeyPressed);

		mono_add_internal_call("Key.Texture2D::Constructor_Native", Key::Script::Key_Texture2D_Constructor);
		mono_add_internal_call("Key.Texture2D::Destructor_Native", Key::Script::Key_Texture2D_Destructor);
		mono_add_internal_call("Key.Texture2D::SetData_Native", Key::Script::Key_Texture2D_SetData);

		mono_add_internal_call("Key.Material::Destructor_Native", Key::Script::Key_Material_Destructor);
		mono_add_internal_call("Key.Material::SetFloat_Native", Key::Script::Key_Material_SetFloat);
		mono_add_internal_call("Key.Material::SetTexture_Native", Key::Script::Key_Material_SetTexture);

		mono_add_internal_call("Key.MaterialInstance::Destructor_Native", Key::Script::Key_MaterialInstance_Destructor);
		mono_add_internal_call("Key.MaterialInstance::SetFloat_Native", Key::Script::Key_MaterialInstance_SetFloat);
		mono_add_internal_call("Key.MaterialInstance::SetVector3_Native", Key::Script::Key_MaterialInstance_SetVector3);
		mono_add_internal_call("Key.MaterialInstance::SetTexture_Native", Key::Script::Key_MaterialInstance_SetTexture);

		mono_add_internal_call("Key.Mesh::Constructor_Native", Key::Script::Key_Mesh_Constructor);
		mono_add_internal_call("Key.Mesh::Destructor_Native", Key::Script::Key_Mesh_Destructor);
		mono_add_internal_call("Key.Mesh::GetMaterial_Native", Key::Script::Key_Mesh_GetMaterial);
		mono_add_internal_call("Key.Mesh::GetMaterialByIndex_Native", Key::Script::Key_Mesh_GetMaterialByIndex);
		mono_add_internal_call("Key.Mesh::GetMaterialCount_Native", Key::Script::Key_Mesh_GetMaterialCount);

		mono_add_internal_call("Key.MeshFactory::CreatePlane_Native", Key::Script::Key_MeshFactory_CreatePlane);

		// static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
		// 
		// static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		// static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		// static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		// static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	}

}