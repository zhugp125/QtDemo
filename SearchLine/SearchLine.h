#ifndef SEARCHLINE_H
#define SEARCHLINE_H

#include <QLineEdit>
#include <QIcon>

class SearchLine : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QIcon normal_clear_button_icon READ GetNormalClearButtonIcon WRITE SetNormalClearButtonIcon)
    Q_PROPERTY(QIcon hover_clear_button_icon READ GetHoverClearButtonIcon WRITE SetHoverClearButtonIcon)
    Q_PROPERTY(QIcon press_clear_button_icon READ GetPressClearButtonIcon WRITE SetPressClearButtonIcon)
    Q_PROPERTY(QIcon disable_clear_button_icon READ GetDisableClearButtonIcon WRITE SetDisableClearButtonIcon)
    Q_PROPERTY(QIcon normal_search_button_icon READ GetNormalSearchButtonIcon WRITE SetNormalSearchButtonIcon)
    Q_PROPERTY(QIcon hover_search_button_icon READ GetHoverSearchButtonIcon WRITE SetHoverSearchButtonIcon)
    Q_PROPERTY(QIcon press_search_button_icon READ GetPressSearchButtonIcon WRITE SetPressSearchButtonIcon)
    Q_PROPERTY(QIcon disable_search_button_icon READ GetDisableSearchButtonIcon WRITE SetDisableSearchButtonIcon)
public:
    explicit SearchLine(QWidget *parent = nullptr);

    /// 下面这八对函数用于样式表设置qss
    /// 不推荐直接在代码中调用
    /// 在qss中设置超级简单
    /// SearchLine {
    ///     qproperty-normal_clear_button_icon: url(:/images/clear_nor.svg);
    ///     ....
    /// }
    void SetNormalClearButtonIcon(const QIcon& normal_icon);
    QIcon GetNormalClearButtonIcon() const;

    void SetHoverClearButtonIcon(const QIcon& hover_icon);
    QIcon GetHoverClearButtonIcon() const;

    void SetPressClearButtonIcon(const QIcon& press_icon);
    QIcon GetPressClearButtonIcon() const;

    void SetDisableClearButtonIcon(const QIcon& disable_icon);
    QIcon GetDisableClearButtonIcon() const;

    void SetNormalSearchButtonIcon(const QIcon& normal_icon);
    QIcon GetNormalSearchButtonIcon() const;

    void SetHoverSearchButtonIcon(const QIcon& hover_icon);
    QIcon GetHoverSearchButtonIcon() const;

    void SetPressSearchButtonIcon(const QIcon& press_icon);
    QIcon GetPressSearchButtonIcon() const;

    void SetDisableSearchButtonIcon(const QIcon& disable_icon);
    QIcon GetDisableSearchButtonIcon() const;

    /// 设置图标绘制的方向
    /// qlineedit更新文本时，会使用默认的布局方向导致图标错位
    void SetLayoutDirection(const Qt::LayoutDirection direction);
    Qt::LayoutDirection GetLayoutDirection() const;

    /// 清除图标是否可用
    void SetClearButtonEnabled(bool enabled);
    bool GetClearButtonEnabled() const;

    /// 搜索图标是否可用
    void SetSearchButtonEnabled(bool enabled);
    bool GetSearchButtonEnabled() const;

signals:
    /// 模仿点击清除图标发出对信号
    void SignalClearButtonClicked();
    /// 模仿点击搜索图标发出对信号
    void SignalSearchButtonClicked();

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    bool event(QEvent* e);

private:
    /// 图标顺序
    enum ButtonPosition
    {
        NoButton = -1,
        ClearButton,
        SearchButton,
        ButtonCount    // last enum define
    };

    /// 图标状态
    enum ButtonStatus
    {
        NormalButton = 0,
        HoverButton,
        PressButton,
        DisableButton,
        StatusCount
    };

    /// 获取对应图标所在对位置（相对位置）
    /// QPoint 起点位置
    /// QRect 图标所在区域
    QPoint GetButtonPos(ButtonPosition btn_postion) const;
    QRect GetButtonRect(ButtonPosition btn_postion) const;

    /// 设置图标是否可用，非对外开发
    void SetButtonEnabled(ButtonPosition btn_postion, bool enabled);
    bool GetButtonEnabled(ButtonPosition btn_postion) const;

    /// 设置绘制图标外观，非对外开发
    void SetButtonPixmap(ButtonPosition btn_postion, ButtonStatus btn_status, const QIcon& icon);
    QPixmap GetButtonPixmap(ButtonPosition btn_postion, ButtonStatus btn_status) const;

    /// 实际绘制图标的方法
    void DrawButtonItem(QPainter* painter, ButtonPosition btn_postion);

private:
    Qt::LayoutDirection direction_ = Qt::LeftToRight;

    QMap<ButtonPosition, bool> map_btn_enabled_;

    QMap<ButtonPosition, QVector<QPixmap> > map_btn_pixmap_;

    ButtonPosition btn_hover_ = ButtonPosition::NoButton;
    ButtonPosition btn_press_ = ButtonPosition::NoButton;
};

#endif // SEARCHLINE_H
