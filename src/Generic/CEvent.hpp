/**
 * @file CEvent.hpp
 * @author Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CEvent class.
 * @date 01-12-2019
 * @copyright Copyright (c) 2019
 */


#pragma once

#include <tuple>
#include <vector>
#include <functional>

namespace gen
{

/**
 * @brief CEvent is a C++ event class that provides tools that allow your \n
 *          application components to communicate with each other by \n
 *          dispatching events and listening to them.
 *
 * @tparam Args... Hendler input parameter types.
 */
template<typename TOwner, typename TFn>
class CEvent
{
    friend TOwner;

    using THandler = std::function<TFn>;
    using THandlersVector = std::vector<THandler>;

public:

    CEvent() = default;
    ~CEvent() = default;
    CEvent(CEvent&&) = default;
    CEvent(const CEvent&) = default;

    /**
     * @brief Attaches an anonymous method to the event.
     *
     * @param handler The callable object, event handler.
     */
    void Add(THandler handler)
    {
        m_vecHandlers.emplace_back(std::move(handler));
    }

    /**
     * @brief Deletes all handlers.
     */
    void Clear()
    {
        m_vecHandlers.clear();
    }

private:

    /**
     * @brief Executes the specified event, on the thread that owns the \n
     *          control's underlying window handle, with the specified list \n
     *          of arguments.
     *
     * @param args Hendler input arguments.
     */
    template<typename ... TArgs>
    void Invoke(TArgs... args)
    {
        for (auto&& handler : m_vecHandlers)
        {
            handler(args...);
        }
    }

private:

    THandlersVector m_vecHandlers;
};


} // namespace gen