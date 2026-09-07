#pragma once
#include "Widget.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using Widgets = std::vector<std::shared_ptr<Widget>>;
using OptVector2f = sf::Vector2<std::optional<float>>;

class LinearContainer : public InteractableWidget, public DynamicWidget
{
protected:
    float padding_;
    InteractableWidget* lastHovered_ = nullptr;
    sf::Vector2f size_;
    OptVector2f widgetSize_;
    Widgets widgets_;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        if (!isVisible()) return;
        states.transform *= getTransform();
        for (const auto& widget : widgets_)
            target.draw(*widget, states);
    }

    virtual void alignWidgetsWithPadding(OptVector2f widgetSize) = 0;
    
    virtual Widgets::iterator searchForWidget(sf::Vector2i pos) = 0;
public:
    LinearContainer(Widgets widgets, OptVector2f widgetSize, float padding = PADDING)
    : padding_(std::max(padding, 0.f)), size_({0.f, 0.f}), widgetSize_(widgetSize), widgets_(widgets)
    {}

    const float getPadding() const { return padding_; }

    void setPadding(float padding)
    {
        if (widgets_.empty()) return;
        padding_ = std::max(0.f, padding);
        alignWidgetsWithPadding({std::nullopt, std::nullopt});
    }

    const OptVector2f getWidgetSize() const { return widgetSize_; }

    void setWidgetSize(OptVector2f widgetSize)
    {
        if (widgets_.empty()) return;
        widgetSize_ = widgetSize;
        alignWidgetsWithPadding(widgetSize_);
    }

    const Widget* get(const size_t index) const { return widgets_[index].get(); }

    Widget* get(const size_t index) { return widgets_[index].get(); }

    const sf::FloatRect getBounds() const override { return getTransform().transformRect({{0.f, 0.f}, size_}); }
    
    const sf::Vector2f getSize() const override { return size_; }

    void update() override
    {
        if (!isVisible()) return;
        for (auto widget : widgets_)
            if (auto dynamicWidget = dynamic_cast<DynamicWidget*>(widget.get()))
                dynamicWidget->update();
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

        auto it = searchForWidget(localEvent.position_);

        if (it != widgets_.end())
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