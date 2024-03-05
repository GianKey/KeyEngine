#pragma once

//#include "Key/Core/Base.h"

#include "RenderCommandQueue.h"
#include "RendererAPI.h"
//#include "OrthographicCamera.h"
//#include "Shader.h"

namespace Key {
	class ShaderLibrary;

	class Renderer
	{
	public:
		typedef void(*RenderCommandFn)(void*);

		//Commands
		static void Clear();
		static void Clear(float r, float g, float b, float a = 1.0f);
		static void SetClearColor(float r, float g, float b, float a);

		static void DrawIndexed(uint32_t count, bool depthTest = true);

		static void ClearMagenta();

		static void Init();

		static void* Submit(RenderCommandFn fn, unsigned int size)
		{
			return s_Instance->m_CommandQueue.Allocate(fn, size);
		}
		inline static RendererAPIType GetAPI() { return RendererAPI::GetAPI(); }
		//3D
		static const Scope<ShaderLibrary>& GetShaderLibrary() { return Get().m_ShaderLibrary; }

		void WaitAndRender();

		inline static Renderer& Get() { return *s_Instance; }


	private:

		static Renderer* s_Instance;
		RenderCommandQueue m_CommandQueue;

		Scope<ShaderLibrary> m_ShaderLibrary;
	};

}

//将两个标识符连接成一个新的标识符。## 运算符是预处理器中的粘合（paste）操作符
#define KEY_RENDER_PASTE2(a, b) a ## b
#define KEY_RENDER_PASTE(a, b) KEY_RENDER_PASTE2(a, b)
#define KEY_RENDER_UNIQUE(x) KEY_RENDER_PASTE(x, __LINE__)


#define KEY_RENDER(code) \
    struct KEY_RENDER_UNIQUE(KEYRenderCommand) \
    {\
        static void Execute(void*)\
        {\
            code\
        }\
    };\
	{\
		auto mem = ::Key::Renderer::Submit(KEY_RENDER_UNIQUE(KEYRenderCommand)::Execute, sizeof(KEY_RENDER_UNIQUE(KEYRenderCommand)));\
		new (mem) KEY_RENDER_UNIQUE(KEYRenderCommand)();\
	}\

//定义一个构造函数，用于初始化参数 arg0，并定义了一个静态成员函数 Execute，用于执行传入的代码块。
//在 Execute 函数中，通过从传入的参数缓冲区中提取 arg0 的引用，来获取传入的参数值
//使用 do-while(0) 结构确保宏在展开时只能被当做一个语句使用，而不是单独的代码块。
//remove_const移除模板类型中的 const 修饰符和引用符号的模板元编程表达式。这种类型转换通常用于获取传递给模板的参数的原始类型。
#define KEY_RENDER_1(arg0, code) \
	do {\
    struct KEY_RENDER_UNIQUE(KEYRenderCommand) \
    {\
		KEY_RENDER_UNIQUE(KEYRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0) \
		: arg0(arg0) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg0;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
    };\
	{\
		auto mem = Renderer::Submit(KEY_RENDER_UNIQUE(KEYRenderCommand)::Execute, sizeof(KEY_RENDER_UNIQUE(KEYRenderCommand)));\
		new (mem) KEY_RENDER_UNIQUE(KEYRenderCommand)(arg0);\
	} } while(0)

#define KEY_RENDER_2(arg0, arg1, code) \
    struct KEY_RENDER_UNIQUE(KEYRenderCommand) \
    {\
		KEY_RENDER_UNIQUE(KEYRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1) \
		: arg0(arg0), arg1(arg1) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg1;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
    };\
	{\
		auto mem = Renderer::Submit(KEY_RENDER_UNIQUE(KEYRenderCommand)::Execute, sizeof(KEY_RENDER_UNIQUE(KEYRenderCommand)));\
		new (mem) KEY_RENDER_UNIQUE(KEYRenderCommand)(arg0, arg1);\
	}\

#define KEY_RENDER_3(arg0, arg1, arg2, code) \
    struct KEY_RENDER_UNIQUE(KEYRenderCommand) \
    {\
		KEY_RENDER_UNIQUE(KEYRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2) \
		: arg0(arg0), arg1(arg1), arg2(arg2) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg2;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
    };\
	{\
		auto mem = Renderer::Submit(KEY_RENDER_UNIQUE(KEYRenderCommand)::Execute, sizeof(KEY_RENDER_UNIQUE(KEYRenderCommand)));\
		new (mem) KEY_RENDER_UNIQUE(KEYRenderCommand)(arg0, arg1, arg2);\
	}\

#define KEY_RENDER_4(arg0, arg1, arg2, arg3, code) \
    struct KEY_RENDER_UNIQUE(KEYRenderCommand) \
    {\
		KEY_RENDER_UNIQUE(KEYRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3)\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg2;\
			auto& arg3 = ((KEY_RENDER_UNIQUE(KEYRenderCommand)*)argBuffer)->arg3;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3;\
    };\
	{\
		auto mem = Renderer::Submit(KEY_RENDER_UNIQUE(KEYRenderCommand)::Execute, sizeof(KEY_RENDER_UNIQUE(KEYRenderCommand)));\
		new (mem) KEY_RENDER_UNIQUE(KEYRenderCommand)(arg0, arg1, arg2, arg3);\
	}

#define KEY_RENDER_S(code) auto self = this;\
	KEY_RENDER_1(self, code)

#define KEY_RENDER_S1(arg0, code) auto self = this;\
	KEY_RENDER_2(self, arg0, code)

#define KEY_RENDER_S2(arg0, arg1, code) auto self = this;\
	KEY_RENDER_3(self, arg0, arg1, code)

#define KEY_RENDER_S3(arg0, arg1, arg2, code) auto self = this;\
	KEY_RENDER_4(self, arg0, arg1, arg2, code)