#pragma once

#include "Common.h"

#include "BasicTypes.h"
#include "Event.h"

namespace d14uikit
{
    class Image;

    class DllExport Panel : public _D14_UIKIT_NONCOPYABLE
    {
        _D14_UIKIT_PIMPL_DEF

        Panel();

        bool destory();

        bool visible() const;
        void setVisible(bool value);

        bool enabled() const;
        void setEnabled(bool value);

        Size size() const;
        void setSize(const Size& value);

        int width() const;
        void setWidth(int value);

        int height() const;
        void setHeight(int value);

        Point position() const;
        void setPosition(const Point& value);

        int x() const;
        void setX(int value);

        int y() const;
        void setY(int value);

        Image* image() const;
        void setImage(Image* imgae);

        Color color() const;
        void setColor(const Color& value);

        float opacity() const;
        void setOpacity(float value);

        void setGlobal(bool value);

        Panel* parent() const;
        void setParent(Panel* uiobj);

        void moveTopmost();
        void moveAbove(Panel* uiobj);
        void moveBelow(Panel* uiobj);

        struct Callback
        {
            std::function<void(Panel*, SizeEvent&)> onSize = {};

            std::function<void(Panel*, MoveEvent&)> onMove = {};

            std::function<void(Panel*, const std::wstring&)> onChangeTheme = {};

            std::function<void(Panel*, const std::wstring&)> onChangeLangLocale = {};

            std::function<void(Panel*)> onGetFocus = {};

            std::function<void(Panel*)> onLoseFocus = {};

            std::function<void(Panel*, MouseMoveEvent&)> onMouseEnter = {};

            std::function<void(Panel*, MouseMoveEvent&)> onMouseMove = {};

            std::function<void(Panel*, MouseMoveEvent&)> onMouseLeave = {};

            std::function<void(Panel*, MouseButtonEvent&)> onMouseButton = {};

            std::function<void(Panel*, MouseWheelEvent&)> onMouseWheel = {};

            std::function<void(Panel*, KeyboardEvent&)> onKeyboard = {};
        };
        Callback& callback() const;
        
    protected:
        explicit Panel(Passkey);

        void initialize();

        std::unique_ptr<Callback> pcallback = {};

        virtual void onSize(SizeEvent& event);

        virtual void onMove(MoveEvent& event);

        virtual void onChangeTheme(const std::wstring& name);

        virtual void onChangeLangLocale(const std::wstring& name);

        virtual void onGetFocus();

        virtual void onLoseFocus();

        virtual void onMouseEnter(MouseMoveEvent& event);

        virtual void onMouseMove(MouseMoveEvent& event);

        virtual void onMouseLeave(MouseMoveEvent& event);

        virtual void onMouseButton(MouseButtonEvent& event);

        virtual void onMouseWheel(MouseWheelEvent& event);

        virtual void onKeyboard(KeyboardEvent& event);
    };
}
