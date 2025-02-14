#include "Kpch.h"
#include "ScriptWrappers.h"

#include "Key/Core/Math/Noise.h"

#include "Key/Scene/Scene.h"
#include "Key/Scene/Entity.h"
#include "Key/Scene/Components.h"

#include <glm/gtc/type_ptr.hpp>

#include "Key/Core/Input.h"
#include <mono/jit/jit.h>

#include <box2d/box2d.h>

namespace Key {
	extern std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	extern std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;
}

namespace Key {
	namespace Script {

		enum class ComponentID
		{
			None = 0,
			Transform = 1,
			Mesh = 2,
			Script = 3,
			SpriteRenderer = 4
		};



		////////////////////////////////////////////////////////////////
		// Math ////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////

		float Key_Noise_PerlinNoise(float x, float y)
		{
			return Noise::PerlinNoise(x, y);
		}

		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////
		// Input ///////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////

		bool Key_Input_IsKeyPressed(KeyCode key)
		{
			return Input::IsKeyPressed(key);
		}
		bool Key_Input_IsMouseButtonPressed(MouseButton button)
		{
			return Input::IsMouseButtonPressed(button);
		}

		void Key_Input_GetMousePosition(glm::vec2* outPosition)
		{
			auto [x, y] = Input::GetMousePosition();
			*outPosition = { x, y };
		}

		void Key_Input_SetCursorMode(CursorMode mode)
		{
			Input::SetCursorMode(mode);
		}

		CursorMode Key_Input_GetCursorMode()
		{
			return Input::GetCursorMode();
		}

		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////
		// Entity //////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////

		void Key_Entity_CreateComponent(uint64_t entityID, void* type)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
			s_CreateComponentFuncs[monoType](entity);
		}

		bool Key_Entity_HasComponent(uint64_t entityID, void* type)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
			bool result = s_HasComponentFuncs[monoType](entity);
			return result;
		}

		uint64_t Key_Entity_FindEntityByTag(MonoString* tag)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");

			Entity entity = scene->FindEntityByTag(mono_string_to_utf8(tag));
			if (entity)
				return entity.GetComponent<IDComponent>().ID;

			return 0;
		}

		void Key_TransformComponent_GetTransform(uint64_t entityID, TransformComponent* outTransform)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			*outTransform = entity.GetComponent<TransformComponent>();
		}

		void Key_TransformComponent_SetTransform(uint64_t entityID, TransformComponent* inTransform)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			entity.GetComponent<TransformComponent>() = *inTransform;
		}

		void Key_TransformComponent_GetTranslation(uint64_t entityID, glm::vec3* outTranslation)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			*outTranslation = entity.GetComponent<TransformComponent>().Translation;
		}

		void Key_TransformComponent_SetTranslation(uint64_t entityID, glm::vec3* inTranslation)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			entity.GetComponent<TransformComponent>().Translation = *inTranslation;
		}

		void Key_TransformComponent_GetRotation(uint64_t entityID, glm::vec3* outRotation)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			*outRotation = entity.GetComponent<TransformComponent>().Rotation;
		}

		void Key_TransformComponent_SetRotation(uint64_t entityID, glm::vec3* inRotation)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			entity.GetComponent<TransformComponent>().Rotation = *inRotation;
		}

		void Key_TransformComponent_GetScale(uint64_t entityID, glm::vec3* outScale)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			*outScale = entity.GetComponent<TransformComponent>().Scale;
		}

		void Key_TransformComponent_SetScale(uint64_t entityID, glm::vec3* inScale)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			entity.GetComponent<TransformComponent>().Scale = *inScale;
		}



		void* Key_MeshComponent_GetMesh(uint64_t entityID)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			auto& meshComponent = entity.GetComponent<MeshComponent>();
			return new Ref<Mesh>(meshComponent.Mesh);
		}

		void Key_MeshComponent_SetMesh(uint64_t entityID, Ref<Mesh>* inMesh)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			auto& meshComponent = entity.GetComponent<MeshComponent>();
			meshComponent.Mesh = inMesh ? *inMesh : nullptr;
		}

		void Key_RigidBody2DComponent_ApplyLinearImpulse(uint64_t entityID, glm::vec2* impulse, glm::vec2* offset, bool wake)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			KEY_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
			auto& component = entity.GetComponent<RigidBody2DComponent>();
			b2Body* body = (b2Body*)component.RuntimeBody;
			body->ApplyLinearImpulse(*(const b2Vec2*)impulse, body->GetWorldCenter() + *(const b2Vec2*)offset, wake);
		}

		void Key_RigidBody2DComponent_GetLinearVelocity(uint64_t entityID, glm::vec2* outVelocity)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			KEY_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
			auto& component = entity.GetComponent<RigidBody2DComponent>();
			b2Body* body = (b2Body*)component.RuntimeBody;
			const auto& velocity = body->GetLinearVelocity();
			KEY_CORE_ASSERT(outVelocity);
			*outVelocity = { velocity.x, velocity.y };
		}

		void Key_RigidBody2DComponent_SetLinearVelocity(uint64_t entityID, glm::vec2* velocity)
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			KEY_CORE_ASSERT(scene, "No active scene!");
			const auto& entityMap = scene->GetEntityMap();
			KEY_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

			Entity entity = entityMap.at(entityID);
			KEY_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
			auto& component = entity.GetComponent<RigidBody2DComponent>();
			b2Body* body = (b2Body*)component.RuntimeBody;
			KEY_CORE_ASSERT(velocity);
			body->SetLinearVelocity({ velocity->x, velocity->y });
		}

		Ref<Mesh>* Key_Mesh_Constructor(MonoString* filepath)
		{
			return new Ref<Mesh>(new Mesh(mono_string_to_utf8(filepath)));
		}

		void Key_Mesh_Destructor(Ref<Mesh>* _this)
		{
			Ref<Mesh>* instance = (Ref<Mesh>*)_this;
			delete _this;
		}

		Ref<Material>* Key_Mesh_GetMaterial(Ref<Mesh>* inMesh)
		{
			Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
			const auto& materials = mesh->GetMaterials();
			return new Ref<Material>(materials[0]);
		}

		Ref<Material>* Key_Mesh_GetMaterialByIndex(Ref<Mesh>* inMesh, int index)
		{
			Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
			const auto& materials = mesh->GetMaterials();

			KEY_CORE_ASSERT(index < materials.size());
			return new Ref<Material>(materials[index]);
		}

		int Key_Mesh_GetMaterialCount(Ref<Mesh>* inMesh)
		{
			Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
			const auto& materials = mesh->GetMaterials();
			return materials.size();
		}

		void* Key_Texture2D_Constructor(uint32_t width, uint32_t height)
		{
			auto result = Texture2D::Create(ImageFormat::RGBA, width, height);
			return new Ref<Texture2D>(result);
		}

		void Key_Texture2D_Destructor(Ref<Texture2D>* _this)
		{
			delete _this;
		}

		void Key_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count)
		{
			Ref<Texture2D>& instance = *_this;

			uint32_t dataSize = count * sizeof(glm::vec4) / 4;

			instance->Lock();
			Buffer buffer = instance->GetWriteableBuffer();
			KEY_CORE_ASSERT(dataSize <= buffer.Size);
			// Convert RGBA32F color to RGBA8
			uint8_t* pixels = (uint8_t*)buffer.Data;
			uint32_t index = 0;
			for (int i = 0; i < instance->GetWidth() * instance->GetHeight(); i++)
			{
				glm::vec4& value = mono_array_get(inData, glm::vec4, i);
				*pixels++ = (uint32_t)(value.x * 255.0f);
				*pixels++ = (uint32_t)(value.y * 255.0f);
				*pixels++ = (uint32_t)(value.z * 255.0f);
				*pixels++ = (uint32_t)(value.w * 255.0f);
			}

			instance->Unlock();
		}

		void Key_Material_Destructor(Ref<Material>* _this)
		{
			delete _this;
		}

		void Key_Material_SetFloat(Ref<Material>* _this, MonoString* uniform, float value)
		{
			Ref<Material>& instance = *(Ref<Material>*)_this;
			instance->Set(mono_string_to_utf8(uniform), value);
		}

		void Key_Material_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture)
		{
			Ref<Material>& instance = *(Ref<Material>*)_this;
			instance->Set(mono_string_to_utf8(uniform), *texture);
		}

		void Key_MaterialInstance_Destructor(Ref<Material>* _this)
		{
			delete _this;
		}

		void Key_MaterialInstance_SetFloat(Ref<Material>* _this, MonoString* uniform, float value)
		{
			Ref<Material>& instance = *(Ref<Material>*)_this;
			instance->Set(mono_string_to_utf8(uniform), value);
		}

		void Key_MaterialInstance_SetVector3(Ref<Material>* _this, MonoString* uniform, glm::vec3* value)
		{
			Ref<Material>& instance = *(Ref<Material>*)_this;
			instance->Set(mono_string_to_utf8(uniform), *value);
		}

		void Key_MaterialInstance_SetVector4(Ref<Material>* _this, MonoString* uniform, glm::vec4* value)
		{
			Ref<Material>& instance = *(Ref<Material>*)_this;
			instance->Set(mono_string_to_utf8(uniform), *value);
		}

		void Key_MaterialInstance_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture)
		{
			Ref<Material>& instance = *(Ref<Material>*)_this;
			instance->Set(mono_string_to_utf8(uniform), *texture);
		}

		void* Key_MeshFactory_CreatePlane(float width, float height)
		{
			// TODO: Implement properly with MeshFactory class!
			return new Ref<Mesh>(new Mesh("assets/models/Plane1m.obj"));
		}

		////////////////////////////////////////////////////////////////

	}
}