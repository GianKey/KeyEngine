#pragma once

#include "Key/Core/Window.h"
#include "Key/Renderer/RendererContext.h"
#include <GLFW/glfw3.h>
#include "Key/Core/input.h"

namespace Key {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void ProcessEvents() override;
		virtual void SwapBuffers() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void Maximize() override;

		virtual const std::string& GetTitle() const override { return m_Data.Title; }
		virtual void SetTitle(const std::string& title) override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
		virtual Ref<RendererContext> GetRenderContext() override { return m_RendererContext; }

		virtual std::pair<uint32_t, uint32_t> GetSize() const override { return { m_Data.Width, m_Data.Height }; }
		virtual std::pair<float, float> GetWindowPos() const override;
		
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		
		GLFWcursor* m_ImGuiMouseCursors[9] = { 0 };
		float m_LastFrameTime = 0.0f;

		Ref<RendererContext> m_RendererContext;
	};

}
