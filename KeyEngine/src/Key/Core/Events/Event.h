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
 * @brief ��ȡ�¼�����.
 * 
 * Ϊ��ͬ���͵��¼�����ӹ�ͬ�ķ��������ԡ�
 * GetStaticType()��������������¼����͵ľ�̬���͡�����һ����̬��Ա���������ڻ�ȡ�¼�������͡�
 * GetEventType()������������麯�������ڻ�ȡ�¼������͡����������Է��ض�Ӧ�¼���ľ�̬���͡�
 * GetName()���������Ҳ���麯�������ڻ�ȡ�¼������ơ����������Է��ض�Ӧ�¼�������ơ�
 * #��Ϊ�ַ������������������ǽ������ת��Ϊ�ַ�����
 */
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

/**
 * @brief �����¼�����.
 */
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    /**
     * @brief �¼��ĳ�����.
     * 
     * �����¼��Ļ������ܰ��������¼����ͣ����࣬���Ƶ�
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
     * @brief �¼��ַ�����.
     * 
     * �ַ��¼���������Ӧ�Ĵ�����
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
         * @brief �¼��ַ�.
         * 
         *  @details ��Dispath��������ָ��ģ�������뱾�ַ�������ʱ�趨��event������ͬ���򽫷ַ�����m_event��Ϊ������������func����ִ��
         *  F���ɱ������Ƶ�����
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