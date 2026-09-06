#pragma once
#include "LinearContainer.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class HContainer : public LinearContainer
{
private:
    void alignWidgetsWithPadding(OptVector2f widgetSize) override
    {
        sf::Vector2f currentPos = {0.f, 0.f};
        size_.y = 0;
            
        for (auto& widget : widgets_)
        {
            sf::Vector2f wSize = widget->getSize(); 
            widget->setSize({
                widgetSize.x.value_or(wSize.x),
                widgetSize.y.value_or(wSize.y), 
            });
            widget->setPosition(currentPos);
            wSize = widget->getSize(); 
            currentPos.x += wSize.x + padding_;
            size_.y = std::max(size_.y, wSize.y); 
        }

        size_.x = currentPos.x - padding_;
    }

    Widgets::iterator searchForWidget(sf::Vector2i pos) override
    {
        return std::lower_bound(
            widgets_.begin(), 
            widgets_.end(), 
            pos.x,
            [](const std::shared_ptr<Widget>& widget, int mouseX) 
            {
                return (widget->getPosition().x + widget->getSize().x) < mouseX;
            }
        );
    }
public:
    HContainer(Widgets widgets, float padding = PADDING)
    : HContainer(widgets, {std::nullopt, std::nullopt}, padding) {}

    HContainer(Widgets widgets, OptVector2f widgetSize, float padding = PADDING)
    : LinearContainer(widgets, widgetSize, padding) 
    {
        if (!widgets_.empty()) alignWidgetsWithPadding(widgetSize_);
    }

    void setSize(sf::Vector2f size) override
    {
        if (widgets_.empty()) return; 
        widgetSize_.y = size.y;
        float totalPadding = padding_ * (widgets_.size() - 1);
        widgetSize_.x = std::max(0.f, (size.x - totalPadding) / widgets_.size());
        alignWidgetsWithPadding(widgetSize_);
    }
};

