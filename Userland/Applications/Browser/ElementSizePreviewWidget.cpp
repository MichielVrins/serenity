/*
 * Copyright (c) 2022, Michiel Vrins
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ElementSizePreviewWidget.h"
#include <LibGUI/Painter.h>

namespace Browser {

void ElementSizePreviewWidget::paint_event(GUI::PaintEvent& event)
{
    GUI::Frame::paint_event(event);
    GUI::Painter painter(*this);
    painter.fill_rect(frame_inner_rect(), Color::White);

    // outer rect
    Gfx::IntRect margin_rect {
        10,
        10,
        250,
        110
    };
    auto border_rect = margin_rect;
    border_rect.shrink(50, 30);
    auto padding_rect = border_rect;
    padding_rect.shrink(50, 30);
    auto content_rect = padding_rect;
    content_rect.shrink(50, 30);

    auto draw_borders = [&](Gfx::IntRect rect, Color color) {
        painter.fill_rect(rect.take_from_top(1), color);
        painter.fill_rect(rect.take_from_right(1), color);
        painter.fill_rect(rect.take_from_bottom(1), color);
        painter.fill_rect(rect.take_from_left(1), color);
    };

    auto draw_size_texts = [&](Gfx::IntRect rect, Color color, Web::Layout::PixelBox box) {
        painter.draw_text(rect, String::formatted("{}", box.top), font(), Gfx::TextAlignment::TopCenter, color);
        painter.draw_text(rect, String::formatted("{}", box.right), font(), Gfx::TextAlignment::CenterRight, color);
        painter.draw_text(rect, String::formatted("{}", box.bottom), font(), Gfx::TextAlignment::BottomCenter, color);
        painter.draw_text(rect, String::formatted("{}", box.left), font(), Gfx::TextAlignment::CenterLeft, color);
    };

    // paint margin box
    painter.fill_rect(margin_rect, Color(249, 204, 157));
    draw_borders(margin_rect, Color::Black);
    margin_rect.shrink(8, 4);
    painter.draw_text(margin_rect, "margin", font(), Gfx::TextAlignment::TopLeft, Color::Black);
    draw_size_texts(margin_rect, Color::Black, m_node_box_sizing.margin);

    // paint border box
    painter.fill_rect(border_rect, Color(253, 221, 155));
    draw_borders(border_rect, Color::Black);
    border_rect.shrink(8, 4);
    painter.draw_text(border_rect, "border", font(), Gfx::TextAlignment::TopLeft, Color::Black);
    draw_size_texts(border_rect, Color::Black, m_node_box_sizing.border);

    // paint padding box
    painter.fill_rect(padding_rect, Color(195, 208, 139));
    draw_borders(padding_rect, Color::Black);
    padding_rect.shrink(8, 4);
    painter.draw_text(padding_rect, "padding", font(), Gfx::TextAlignment::TopLeft, Color::Black);
    draw_size_texts(padding_rect, Color::Black, m_node_box_sizing.padding);

    // paint content box
    auto content_size_text = String::formatted("{}x{}", m_node_content_width, m_node_content_height);
    painter.fill_rect(content_rect, Color(140, 182, 192));
    draw_borders(content_rect, Color::Black);
    painter.draw_text(content_rect, content_size_text, font(), Gfx::TextAlignment::Center, Color::Black);
}

}