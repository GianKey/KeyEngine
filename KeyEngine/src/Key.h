#pragma once

//for use by key application

#include "Key/Core/Application.h"
#include "Key/Core/Log.h"
#include "Key/Core/Input.h"
#include "Key/Core/TimeStep.h"
#include "Key/Core/Timer.h"

#include "Key/Core/Events/Event.h"
#include "Key/Core/Events/ApplicationEvent.h"
#include "Key/Core/Events/KeyBoardEvent.h"
#include "Key/Core/Events/MouseEvent.h"

#include "Key/Core/Math/AABB.h"
#include "Key/Core/Math/Ray.h"

#include "imgui/imgui.h"
//--------Renderer API----------

#include "Key/Renderer/Renderer.h"
#include "Key/Renderer/SceneRenderer.h"
#include "Key/Renderer/RenderPass.h"
#include "Key/Renderer/Framebuffer.h"
#include "Key/Renderer/VertexBuffer.h"
#include "Key/Renderer/IndexBuffer.h"
#include "Key/Renderer/Pipeline.h"
#include "Key/Renderer/Shader.h"
#include "Key/Renderer/Texture.h"
#include "Key/Renderer/Mesh.h"
#include "Key/Renderer/Camera.h"
#include "Key/Renderer/Material.h"

//-----------------------------------------

// Scenes
#include "Key/Scene/Entity.h"
#include "Key/Scene/Scene.h"
#include "Key/Scene/SceneCamera.h"
#include "Key/Scene/SceneSerializer.h"
#include "Key/Scene/Components.h"
