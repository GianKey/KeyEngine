#pragma once

#include "../Base.h"


#include <string>
#include <functional>
#include <sstream>

namespace Key {

    // Events in Key are currently blocking, meaning when an event occurs it
    // immediately gets dispatched and must be dealt with right then an there.
    // For the future, a better strategy might be to buffer events in an event
    // bus and process them during the "event" part of the update stage.

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

/**
 * @brief 获取事件类型.
 * 
 * 为不同类型的事件类添加共同的方法和属性。
 * GetStaticType()：这个函数返回事件类型的静态类型。它是一个静态成员函数，用于获取事件类的类型。
 * GetEventType()：这个函数是虚函数，用于获取事件的类型。它被覆盖以返回对应事件类的静态类型。
 * GetName()：这个函数也是虚函数，用于获取事件的名称。它被覆盖以返回对应事件类的名称。
 * #称为字符串化操作符。作用是将宏参数转换为字符串。
 */
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

/**
 * @brief 返回事件种类.
 */
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    /**
     * @brief 事件的抽象类.
     * 
     * 定义事件的基本功能包括返回事件类型，种类，名称等
     */
    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    /**
     * @brief 事件分发器类.
     * 
     * 分发事件并调用相应的处理函数
     */
    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        /**\
         * @callgraph  
         * @brief 事件分发.
         * 
         *  @details 若Dispath函数调用指定模板类型与本分发器创建时设定的event类型相同，则将分发器的m_event作为参数交给参数func函数执行
         *  F将由编译器推导出来
         * 
         *
         */
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}