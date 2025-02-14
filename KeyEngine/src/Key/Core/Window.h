#pragma once
#include "Kpch.h"
#include "Key/Core/Base.h"
#include "Key/Core/Events/Event.h"
#include "Key/Renderer/RendererContext.h"

namespace Key {
	
	class VulkanSwapChain;

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Key Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class  Window :public RefCounted
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void ProcessEvents() = 0;
		virtual void SwapBuffers() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual std::pair<uint32_t, uint32_t> GetSize() const = 0;
		
		virtual std::pair<float, float> GetWindowPos() const = 0;
		

		virtual void Maximize() = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual void SetTitle(const std::string& title) = 0;

		virtual VulkanSwapChain& GetSwapChain() = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual Ref<RendererContext> GetRenderContext() = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};



}