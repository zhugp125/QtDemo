### QWidget 鼠标事件和拖动事件
两个事件单独使用没有问题
1. mousePressEvent 获取落点位置；
   mouseMoveEvent 获取移动点位置；
   mouseReleaseEvent 获取释放点位置

2. mousePressEvent 获取落点位置；
   mouseMoveEvent 执行一个Drag；
   dragMoveEvent  获取移动点位置
   dropEvent      获取释放点位置

两个事件同时使用时，拖放事件会覆盖鼠标事件
