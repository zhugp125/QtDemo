#include "SearchLine.h"
#include <QStyle>
#include <QPainter>
#include <QEvent>
#include <QDebug>

constexpr int g_btn_width = 24;
constexpr int g_btn_height = 24;
constexpr int g_btn_spacing = 3;

SearchLine::SearchLine(QWidget *parent) : QLineEdit(parent)
{
    setMouseTracking(true);

    SetClearButtonEnabled(true);
    SetSearchButtonEnabled(true);

    connect(this, &SearchLine::SignalClearButtonClicked, this, [=](){
        clear();
        update();
    });
}

void SearchLine::SetNormalClearButtonIcon(const QIcon &normal_icon)
{
    SetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::NormalButton, normal_icon);
}

QIcon SearchLine::GetNormalClearButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::NormalButton));
}

void SearchLine::SetHoverClearButtonIcon(const QIcon &hover_icon)
{
    SetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::HoverButton, hover_icon);
}

QIcon SearchLine::GetHoverClearButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::HoverButton));
}

void SearchLine::SetPressClearButtonIcon(const QIcon &press_icon)
{
    SetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::PressButton, press_icon);
}

QIcon SearchLine::GetPressClearButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::PressButton));
}

void SearchLine::SetDisableClearButtonIcon(const QIcon &disable_icon)
{
    SetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::DisableButton, disable_icon);
}

QIcon SearchLine::GetDisableClearButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::ClearButton, ButtonStatus::DisableButton));
}

void SearchLine::SetNormalSearchButtonIcon(const QIcon &normal_icon)
{
    SetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::NormalButton, normal_icon);
}

QIcon SearchLine::GetNormalSearchButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::NormalButton));
}

void SearchLine::SetHoverSearchButtonIcon(const QIcon &hover_icon)
{
    SetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::HoverButton, hover_icon);
}

QIcon SearchLine::GetHoverSearchButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::HoverButton));
}

void SearchLine::SetPressSearchButtonIcon(const QIcon &press_icon)
{
    SetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::PressButton, press_icon);
}

QIcon SearchLine::GetPressSearchButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::PressButton));
}

void SearchLine::SetDisableSearchButtonIcon(const QIcon &disable_icon)
{
    SetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::DisableButton, disable_icon);
}

QIcon SearchLine::GetDisableSearchButtonIcon() const
{
    return QIcon(GetButtonPixmap(ButtonPosition::SearchButton, ButtonStatus::DisableButton));
}

void SearchLine::SetLayoutDirection(const Qt::LayoutDirection direction)
{
    direction_ = direction;
    int btn_count = static_cast<int>(ButtonPosition::ButtonCount);
    if (Qt::LeftToRight == direction_)
    {
        setTextMargins(5, 3, btn_count * g_btn_width + (btn_count + 1) * g_btn_spacing, 3);
    }
    else
    {
        setTextMargins(btn_count * g_btn_width + (btn_count + 1) * g_btn_spacing, 3, 5, 3);
    }
}

Qt::LayoutDirection SearchLine::GetLayoutDirection() const
{
    return direction_;
}

void SearchLine::SetClearButtonEnabled(bool enabled)
{
    SetButtonEnabled(ButtonPosition::ClearButton, enabled);
}

bool SearchLine::GetClearButtonEnabled() const
{
    return GetButtonEnabled(ButtonPosition::ClearButton);
}

void SearchLine::SetSearchButtonEnabled(bool enabled)
{
    SetButtonEnabled(ButtonPosition::SearchButton, enabled);
}

bool SearchLine::GetSearchButtonEnabled() const
{
    return GetButtonEnabled(ButtonPosition::SearchButton);
}

void SearchLine::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter p(this);
    if (!text().isEmpty())
    {
        DrawButtonItem(&p, ButtonPosition::ClearButton);
    }
    DrawButtonItem(&p, ButtonPosition::SearchButton);
}

void SearchLine::mouseMoveEvent(QMouseEvent *event)
{
    QLineEdit::mouseMoveEvent(event);

    if (!text().isEmpty() && GetClearButtonEnabled())
    {
        QPoint clear_pos = mapToGlobal(GetButtonPos(ButtonPosition::ClearButton));
        if (QRect(clear_pos, QSize(g_btn_width, g_btn_height)).contains(QCursor::pos()))
        {
            btn_hover_ = ButtonPosition::ClearButton;
            update();
            return;
        }
    }
    if (GetSearchButtonEnabled())
    {
        QPoint search_pos = mapToGlobal(GetButtonPos(ButtonPosition::SearchButton));
        if (QRect(search_pos, QSize(g_btn_width, g_btn_height)).contains(QCursor::pos()))
        {
            btn_hover_ = ButtonPosition::SearchButton;
            update();
            return;
        }
    }

    btn_hover_ = ButtonPosition::NoButton;
    update();
}

void SearchLine::mousePressEvent(QMouseEvent *event)
{
    QLineEdit::mousePressEvent(event);

    if (!text().isEmpty() && GetClearButtonEnabled())
    {
        QPoint clear_pos = mapToGlobal(GetButtonPos(ButtonPosition::ClearButton));
        if (QRect(clear_pos, QSize(g_btn_width, g_btn_height)).contains(QCursor::pos()))
        {
            btn_press_ = ButtonPosition::ClearButton;
            update();

            emit SignalClearButtonClicked();
            qDebug() << "emit SignalClearButtonClicked()";
        }
    }
    if (GetSearchButtonEnabled())
    {
        QPoint search_pos = mapToGlobal(GetButtonPos(ButtonPosition::SearchButton));
        if (QRect(search_pos, QSize(g_btn_width, g_btn_height)).contains(QCursor::pos()))
        {
            btn_press_ = ButtonPosition::SearchButton;
            update();

            emit SignalSearchButtonClicked();
            qDebug() << "emit SignalSearchButtonClicked()";
        }
    }
}

void SearchLine::mouseReleaseEvent(QMouseEvent *event)
{
    QLineEdit::mouseReleaseEvent(event);

    if (btn_press_ != ButtonPosition::NoButton)
    {
        btn_press_ = ButtonPosition::NoButton;
        update();
    }
}

bool SearchLine::event(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::Leave:
    case QEvent::HoverLeave:
        if (btn_hover_ != ButtonPosition::NoButton)
        {
            btn_hover_ = ButtonPosition::NoButton;
            update();
        }
        break;
    default:
        break;
    }
    return QLineEdit::event(e);
}

QPoint SearchLine::GetButtonPos(SearchLine::ButtonPosition btn_postion) const
{
    if (ButtonPosition::NoButton == btn_postion)
    {
        return QPoint();
    }

    int start_x = 0;
    int start_y = (height() - g_btn_height) / 2;
    int relative_pos = static_cast<int>(ButtonPosition::ButtonCount - btn_postion);
    if (Qt::LeftToRight == direction_)
    {
        start_x = width() - (g_btn_width + g_btn_spacing) * relative_pos;
    }
    else
    {
        start_x = g_btn_spacing * relative_pos + g_btn_width * (relative_pos - 1);
    }
    return QPoint(start_x, start_y);
}

QRect SearchLine::GetButtonRect(SearchLine::ButtonPosition btn_postion) const
{
    if (ButtonPosition::NoButton == btn_postion)
    {
        return QRect();
    }
    return QRect(GetButtonPos(btn_postion), QSize(g_btn_width, g_btn_height));
}

void SearchLine::SetButtonEnabled(SearchLine::ButtonPosition btn_postion, bool enabled)
{
    map_btn_enabled_[btn_postion] = enabled;
}

bool SearchLine::GetButtonEnabled(SearchLine::ButtonPosition btn_postion) const
{
    return map_btn_enabled_[btn_postion];
}

void SearchLine::SetButtonPixmap(SearchLine::ButtonPosition btn_postion, SearchLine::ButtonStatus btn_status, const QIcon &icon)
{
    if (ButtonPosition::NoButton == btn_postion)
    {
        return;
    }

    auto& pixmap_vec = map_btn_pixmap_[btn_postion];
    int status_count = static_cast<int>(ButtonStatus::StatusCount);
    if (pixmap_vec.size() != status_count)
    {
        pixmap_vec.resize(status_count);
    }

    pixmap_vec[static_cast<int>(btn_status)] = icon.pixmap(g_btn_width, g_btn_height);
}

QPixmap SearchLine::GetButtonPixmap(SearchLine::ButtonPosition btn_postion, SearchLine::ButtonStatus btn_status) const
{
    if (ButtonPosition::NoButton == btn_postion)
    {
        return QPixmap();
    }

    const auto& pixmap_vec = map_btn_pixmap_[btn_postion];
    if (pixmap_vec.size() > btn_status)
    {
        return pixmap_vec[btn_status];
    }
    return QPixmap();
}

void SearchLine::DrawButtonItem(QPainter *painter, SearchLine::ButtonPosition btn_postion)
{
    if (ButtonPosition::NoButton == btn_postion || nullptr == painter)
    {
        return;
    }

    ButtonStatus btn_status = ButtonStatus::NormalButton;
    if (GetButtonEnabled(btn_postion))
    {
        if (btn_hover_ == btn_postion)
        {
            btn_status = ButtonStatus::HoverButton;
        }
        if (btn_press_ == btn_postion)
        {
            btn_status = ButtonStatus::PressButton;
        }
    }
    else
    {
        btn_status = ButtonStatus::DisableButton;
    }

    QPixmap pixmap = GetButtonPixmap(btn_postion, btn_status);
    QRect rect = GetButtonRect(btn_postion);
    if (!pixmap.isNull() && !rect.isNull())
    {
        style()->drawItemPixmap(painter, rect, Qt::AlignLeft, pixmap);
    }
}
