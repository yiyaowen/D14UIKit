#include "Common/Precompile.h"

#include "DraggablePanel.h"
#include "Panel.h"
#include "ResizablePanel.h"
#include "Window.h"

#include "Common/MathUtils/Basic.h"
#include "UIKit/IconLabel.h"
#include "UIKit/Label.h"
#include "UIKit/Window.h"

using namespace d14engine;

namespace d14uikit
{
    Window::Window(const std::wstring& title) : Window(Passkey{})
    {
        pimpl->uiobj = uikit::makeUIObject<uikit::Window>(title);

        Panel::pimpl->uiobj = pimpl->uiobj;
        DraggablePanel::pimpl->uiobj = pimpl->uiobj;
        ResizablePanel::pimpl->uiobj = pimpl->uiobj;

        Panel::initialize();
        DraggablePanel::initialize();
        ResizablePanel::initialize();
        Window::initialize();
    }

    const std::wstring& Window::title() const
    {
        return pimpl->uiobj->caption()->label()->text();
    }

    void Window::setTitle(const std::wstring& title)
    {
        pimpl->uiobj->caption()->label()->setText(title);
    }

    int Window::captionHeight() const
    {
        return math_utils::round(pimpl->uiobj->captionPanelHeight());
    }

    void Window::setCaptionHeight(int value)
    {
        pimpl->uiobj->setCaptionPanelHeight((float)value);
    }

    int Window::decoBarHeight() const
    {
        return math_utils::round(pimpl->uiobj->decorativeBarHeight());
    }

    void Window::setDecoBarHeight(int value)
    {
        pimpl->uiobj->setDecorativeBarHeight((float)value);
    }

    int Window::contentHeight() const
    {
        return math_utils::round(pimpl->uiobj->clientAreaHeight());
    }

    int Window::nonContentHeight() const
    {
        return math_utils::round(pimpl->uiobj->nonClientAreaHeight());
    }

    Panel* Window::content() const
    {
        return pimpl->content;
    }

    void Window::setContent(Panel* uiobj)
    {
        pimpl->content = uiobj;

        if (uiobj != nullptr)
        {
            pimpl->uiobj->setCenterUIObject(uiobj->getImpl()->uiobj);
        }
        else pimpl->uiobj->setCenterUIObject(nullptr);
    }

    bool Window::normal() const
    {
        return pimpl->uiobj->isDisplayNormal();
    }

    bool Window::minimized() const
    {
        return pimpl->uiobj->isDisplayMinimized();
    }

    bool Window::maximized() const
    {
        return pimpl->uiobj->isDisplayMaximized();
    }

    bool Window::minimizeButton() const
    {
        return pimpl->uiobj->isMinimizeEnabled;
    }

    void Window::setMinimizeButton(bool value)
    {
        pimpl->uiobj->isMinimizeEnabled = value;
    }

    bool Window::maximizeButton() const
    {
        return pimpl->uiobj->isMaximizeEnabled;
    }

    void Window::setMaximizeButton(bool value)
    {
        pimpl->uiobj->isMaximizeEnabled = value;
    }

    bool Window::closeButton() const
    {
        return pimpl->uiobj->isCloseEnabled;
    }

    void Window::setCloseButton(bool value)
    {
        pimpl->uiobj->isCloseEnabled = value;
    }

    Window::Callback& Window::callback() const
    {
        return *pcallback;
    }

    Window::Window(Passkey)
        :
        Panel(Panel::Passkey{}),
        DraggablePanel(DraggablePanel::Passkey{}),
        ResizablePanel(ResizablePanel::Passkey{}),
        pimpl(std::make_shared<Impl>()),
        pcallback(std::make_unique<Callback>()) { }

    void Window::initialize()
    {
        pimpl->uiobj->f_onMinimize = [this]
        (uikit::Window* w)
        {
            onMinimize();
            if (pcallback->onMinimize)
            {
                pcallback->onMinimize(this);
            }
        };
        pimpl->uiobj->f_onMaximize = [this]
        (uikit::Window* w)
        {
            onMaximize();
            if (pcallback->onMaximize)
            {
                pcallback->onMaximize(this);
            }
        };
        pimpl->uiobj->f_onRestore = [this]
        (uikit::Window* w)
        {
            onRestore();
            if (pcallback->onRestore)
            {
                pcallback->onRestore(this);
            }
        };
        pimpl->uiobj->f_onClose = [this]
        (uikit::Window* w)
        {
            onClose();
            if (pcallback->onClose)
            {
                pcallback->onClose(this);
            }
        };
    }

    void Window::onMinimize() { }

    void Window::onMaximize() { }

    void Window::onRestore() { }

    void Window::onClose() { }
}
