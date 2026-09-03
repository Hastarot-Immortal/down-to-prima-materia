#pragma once
#include "Widget.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using Widgets = std::vector<std::shared_ptr<Widget>>;
using OptVector2f = sf::Vector2<std::optional<float>>;

class VContainer : public InteractableWidget
{
private:
    float padding_;
    InteractableWidget* lastHovered_ = nullptr;
    sf::Vector2f size_;
    OptVector2f widgetSize_;
    Widgets subwidgets_;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        for (const auto& subwidget : subwidgets_)
        {
            target.draw(*subwidget, states);
        }
    }

    static void alignWidgetsWithPadding(Widgets& widgets, sf::Vector2f& size, float padding, OptVector2f widgetSize)
    {
        sf::Vector2f currentPos = {0.f, 0.f};
        size.x = 0;
            
        for (auto& widget : widgets)
        {
            sf::Vector2f wSize = widget->getSize(); 
            widget->setSize({
                widgetSize.x.value_or(wSize.x),
                widgetSize.y.value_or(wSize.y), 
            });
            widget->setPosition(currentPos);
            wSize = widget->getSize(); 
            currentPos.y += wSize.y + padding;
            size.x = std::max(size.x, wSize.x); 
        }

        size.y = currentPos.y - padding;
    }
public:
    VContainer(Widgets widgets, float padding = PADDING)
    : VContainer(widgets, {std::nullopt, std::nullopt}, padding)
    {}

    VContainer(Widgets widgets, OptVector2f widgetSize, float padding = PADDING)
    : padding_(std::max(padding, 0.f)), size_({0.f, 0.f}), widgetSize_(widgetSize), subwidgets_(widgets)
    {
        if (subwidgets_.empty()) return; 
        alignWidgetsWithPadding(subwidgets_, size_, padding_, widgetSize);
    }

    const float getPadding() const { return padding_; }

    void setPadding(float padding)
    {
        if (subwidgets_.empty()) return;
        padding_ = std::max(0.f, padding);
        alignWidgetsWithPadding(subwidgets_, size_, padding_, {std::nullopt, std::nullopt});
    }

    const OptVector2f getWidgetSize() const { return widgetSize_; }

    void setWidgetSize(OptVector2f widgetSize)
    {
        if (subwidgets_.empty()) return;
        widgetSize_ = widgetSize;
        alignWidgetsWithPadding(subwidgets_, size_, padding_, widgetSize_);
    }

    const Widget* get(const size_t index) const 
    {
        return subwidgets_[index].get();
    }

    Widget* get(const size_t index) 
    {
        return subwidgets_[index].get();
    }

    const sf::FloatRect getBounds() const override { return getTransform().transformRect({{0.f, 0.f}, size_}); }
    const sf::Vector2f getSize() const override { return size_; }
    
    void setSize(sf::Vector2f size) override
    {
        if (subwidgets_.empty()) return; 
        widgetSize_.x = size.x;
        float totalPadding = padding_ * (subwidgets_.size() - 1);
        widgetSize_.y = std::max(0.f, (size.y - totalPadding) / subwidgets_.size());
        alignWidgetsWithPadding(subwidgets_, size_, padding_, widgetSize_);
    }

    void onPressed() override {}

    void handle(MouseEvent& event) override
    {
        InteractableWidget::handle(event);

        sf::Vector2f localPos = getInverseTransform().transformPoint(
            {(float)event.position_.x, (float)event.position_.y}
        );
        
        MouseEvent localEvent = event;
        localEvent.position_ = {(int)localPos.x, (int)localPos.y};

        InteractableWidget* currentHovered = nullptr;

        auto it = std::lower_bound(subwidgets_.begin(), subwidgets_.end(), localEvent.position_.y,
            [](const std::shared_ptr<Widget>& widget, int mouseY) {
                return (widget->getPosition().y + widget->getSize().y) < mouseY;
            });

        if (it != subwidgets_.end())
            if ((*it)->isIntersected(localEvent.position_)) 
                currentHovered = dynamic_cast<InteractableWidget*>(it->get());
            
        if (lastHovered_ != currentHovered)
        {
            if (lastHovered_ != nullptr)
            {
                MouseEvent fakeLeaveEvent = event;
                fakeLeaveEvent.position_ = {-9999, -9999}; 
                lastHovered_->handle(fakeLeaveEvent);
            }
            lastHovered_ = currentHovered;
        }

        if (currentHovered != nullptr) currentHovered->handle(localEvent);
    }
};