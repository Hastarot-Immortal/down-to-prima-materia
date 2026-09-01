#pragma once
#include "Widget.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using Widgets = std::vector<std::shared_ptr<Widget>>;
using OptVector2f = sf::Vector2<std::optional<float>>;

class VContainer : public Widget
{
private:
    float margin_;
    sf::Vector2f size_;
    Widgets subwidgets_;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        for (const auto& subwidget : subwidgets_)
        {
            target.draw(*subwidget, states);
        }
    }
public:
    VContainer(Widgets widgets, float margin = MARGIN)
    : VContainer(widgets, {std::nullopt, std::nullopt}, margin)
    {}

    VContainer(Widgets widgets, OptVector2f widgetSize, float margin = MARGIN)
    : margin_(std::max(margin, 0.f)), size_({0.f, 0.f}), subwidgets_(widgets)
    {
        if (subwidgets_.empty()) {
            return;
        }

        sf::Vector2f currentPos = {0.f, 0.f};
         
        for (auto& subwidget : subwidgets_)
        {
            sf::Vector2f wSize = subwidget->getSize(); 
            subwidget->setSize({
                widgetSize.x.value_or(wSize.x),
                widgetSize.y.value_or(wSize.y), 
            });
            subwidget->setPosition(currentPos);
            wSize = subwidget->getSize(); 
            currentPos.y += wSize.y + margin_;
            size_.x = std::max(size_.x, wSize.x); 
        }

        size_.y = currentPos.y - margin_;
    }

    sf::FloatRect getBounds() const override { 
        return {getPosition(), size_}; 
    }

    const sf::Vector2f getSize() const override
    {
        return size_;
    }
    
    void setSize(sf::Vector2f size) override
    {
        setScale({size.x / size_.x, size.y / size_.y});
        size_ = size;
    }
};
