#pragma once

#include "Common.h"

#include "Panel.h"

namespace d14uikit
{
    class DllExport ClickablePanel : virtual public Panel
    {
        _D14_UIKIT_PIMPL_DEF

        ClickablePanel();

        bool doubleClick() const;
        void setDoubleClick(bool value);

        struct Callback
        {
            std::function<void(ClickablePanel*, MouseButtonClickEvent&)> onMouseButtonPress = {};

            std::function<void(ClickablePanel*, MouseButtonClickEvent&)> onMouseButtonRelease = {};
        };
        Callback& callback() const;

    protected:
        explicit ClickablePanel(Passkey);

        void initialize();

        std::unique_ptr<Callback> pcallback = {};

        virtual void onMouseButtonPress(MouseButtonClickEvent& event);

        virtual void onMouseButtonRelease(MouseButtonClickEvent& event);
    };
}
