#pragma once

//for use by key application


#include <stdio.h>
#include "Key/Core/Application.h"
#include "Key/Core/Log.h"
#include "Key/Core/TimeStep.h"

#include "Key/Core/Events/Event.h"
#include "Key/Core/Events/ApplicationEvent.h"
#include "Key/Core/Events/KeyBoardEvent.h"
#include "Key/Core/Events/MouseEvent.h"

#include "Key/Core/Layer.h"
#include "Key/ImGui/ImGuiLayer.h"
#include "Key/Core/input.h"

#include "Key/Core/KeyCodes.h"  
#include "Key/Core/MouseButtonCodes.h"
#include "imgui/imgui.h"
//--------Renderer API----------

#include "Key/Renderer/Renderer.h"
#include "Key/Renderer/Framebuffer.h"
#include "Key/Renderer/Buffer.h"
#include "Key/Renderer/Shader.h"
#include "Key/Renderer/VertexArray.h"
#include "Key/Renderer/Texture.h"
#include "Key/Renderer/Mesh.h"
#include "Key/Renderer/Camera.h"
#include "Key/Renderer/Material.h"

#include "Key/Renderer/OrthographicCamera.h"

//-----------------------------------------

// --- Entry Point -----------------
#include "Key/EntryPoint.h"
// --- Entry Point -----------------