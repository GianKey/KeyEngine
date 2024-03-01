#pragma once

#include "Key/Core/Window.h"
#include <GLFW/glfw3.h>
#include "Key/Core/input.h"
#include "Key/Renderer/GraphicsContext.h"

namespace Key {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

		//3D
		virtual std::pair<float, float> GetWindowPos() const override;
		//3D---end
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		GraphicsContext* m_Context;

		//3D
		GLFWcursor* m_ImGuiMouseCursors[9] = { 0 };
		float m_LastFrameTime = 0.0f;
		//3D---end
	};

}
