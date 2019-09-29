#include "SearchLine.h"
#include <QStyle>
#include <QPainter>
#include <QEvent>
#include <QDebug>

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
    if (direction_ != direction)
    {
        direction_ = direction;
        update();
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

void SearchLine::SetSearchButtonVisible(bool visible)
{
    if (search_btn_visible_ != visible)
    {
        search_btn_visible_ = visible;
        update();
    }
}

bool SearchLine::GetSearchButtonVisible() const
{
    return search_btn_visible_;
}

bool SearchLine::GetClearButtonVisible() const
{
    return !text().isEmpty();
}

void SearchLine::SetButtonSize(const QSize &size)
{
    if (!size.isNull() && size != btn_size_)
    {
        btn_size_ = size;
        update();
    }
}

void SearchLine::SetButtonSpacing(int spacing)
{
    if (spacing > 0 && spacing != btn_spacing_)
    {
        btn_spacing_ = spacing;
        update();
    }
}

void SearchLine::paintEvent(QPaintEvent *event)
{
    int btn_count = 0;
    if (GetClearButtonVisible())
    {
        ++btn_count;
    }
    if (GetSearchButtonVisible())
    {
        ++btn_count;
    }

    if (Qt::LeftToRight == direction_)
    {
        setTextMargins(5, 3, btn_count * btn_size_.width() + (btn_count + 1) * btn_spacing_, 3);
    }
    else
    {
        setTextMargins(btn_count * btn_size_.width() + (btn_count + 1) * btn_spacing_, 3, 5, 3);
    }

    QLineEdit::paintEvent(event);

    QPainter p(this);
    if (GetClearButtonVisible())
    {
        DrawButtonItem(&p, ButtonPosition::ClearButton);
    }
    if (GetSearchButtonVisible())
    {
        DrawButtonItem(&p, ButtonPosition::SearchButton);
    }
}

void SearchLine::mouseMoveEvent(QMouseEvent *event)
{
    QLineEdit::mouseMoveEvent(event);

    ButtonPosition btn_postion = ButtonPosition::ClearButton;
    if (GetClearButtonVisible() && GetClearButtonEnabled() && CheckMousePos(btn_postion))
    {
        btn_hover_ = btn_postion;
        update();
        return;
    }

    btn_postion = ButtonPosition::SearchButton;
    if (GetSearchButtonVisible() && GetSearchButtonEnabled() && CheckMousePos(btn_postion))
    {
        btn_hover_ = btn_postion;
        update();
        return;
    }

    btn_hover_ = ButtonPosition::NoButton;
    update();
}

void SearchLine::mousePressEvent(QMouseEvent *event)
{
    QLineEdit::mousePressEvent(event);

    ButtonPosition btn_postion = ButtonPosition::ClearButton;
    if (GetClearButtonVisible() && GetClearButtonEnabled() && CheckMousePos(btn_postion))
    {
        btn_press_ = ButtonPosition::ClearButton;
        update();
    }

    btn_postion = ButtonPosition::SearchButton;
    if (GetSearchButtonVisible() && GetSearchButtonEnabled() && CheckMousePos(btn_postion))
    {
        btn_press_ = ButtonPosition::SearchButton;
        update();
    }
}

void SearchLine::mouseReleaseEvent(QMouseEvent *event)
{
    QLineEdit::mouseReleaseEvent(event);

    ButtonPosition btn_postion = ButtonPosition::ClearButton;
    if (GetClearButtonVisible() && GetClearButtonEnabled() && CheckMousePos(btn_postion))
    {
        emit SignalClearButtonClicked();
        qDebug() << "emit SignalClearButtonClicked()";
    }

    btn_postion = ButtonPosition::SearchButton;
    if (GetSearchButtonVisible() && GetSearchButtonEnabled() && CheckMousePos(btn_postion))
    {
        emit SignalSearchButtonClicked();
        qDebug() << "emit SignalSearchButtonClicked()";
    }

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
    int start_y = (height() - btn_size_.height()) / 2;

    int relative_pos = 0;
    do
    {
        if (GetSearchButtonVisible())
        {
            ++relative_pos;
            if (ButtonPosition::SearchButton == btn_postion)
            {
                break;
            }
        }
        if (GetClearButtonVisible())
        {
            ++relative_pos;
            if (ButtonPosition::ClearButton == btn_postion)
            {
                break;
            }
        }
    }while(false);

    if (Qt::LeftToRight == direction_)
    {
        start_x = width() - (btn_size_.width() + btn_spacing_) * relative_pos;
    }
    else
    {
        start_x = btn_spacing_ * relative_pos + btn_size_.width() * (relative_pos - 1);
    }
    return QPoint(start_x, start_y);
}

QRect SearchLine::GetButtonRect(SearchLine::ButtonPosition btn_postion) const
{
    if (ButtonPosition::NoButton == btn_postion)
    {
        return QRect();
    }
    return QRect(GetButtonPos(btn_postion), btn_size_);
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

    pixmap_vec[static_cast<int>(btn_status)] = icon.pixmap(btn_size_);
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

bool SearchLine::CheckMousePos(SearchLine::ButtonPosition btn_postion) const
{
    if (ButtonPosition::NoButton == btn_postion)
    {
        return false;
    }

    QPoint pos = mapToGlobal(GetButtonPos(btn_postion));
    return QRect(pos, btn_size_).contains(QCursor::pos());
}
