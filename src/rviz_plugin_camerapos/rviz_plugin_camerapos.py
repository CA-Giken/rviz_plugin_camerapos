# my_rqt_plugin.py

#! /usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os
import rospy
import rospkg
import string
import re

import roslib
roslib.load_manifest('rviz_plugin_camerapos')

from qt_gui.plugin import Plugin
from python_qt_binding import loadUi
from python_qt_binding.QtGui import *
from python_qt_binding.QtCore import QTimer, QVariant, QPoint
from python_qt_binding.QtWidgets import *
from std_msgs.msg import *

# ================ 定数 start ================

# ================ 定数 end ================

class RvizPluginCamerapos(Plugin):
  def __init__(self, context):
    # Pluginクラスを初期化する
    super(RvizPluginCamerapos, self).__init__(context)
    self.setObjectName('RvizPluginCamerapos')

    # Widgetを作成する
    self._widget = QWidget()

    # .ui ファイルを取得する
    main_ui_file = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'main.ui')
    create_ui_file = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'create.ui')

    # .ui ファイルを読み込み、_widget配下にする
    loadUi(main_ui_file, self._widget)
    self._widget.setObjectName('RvizPluginCameraposUi')

    # ウィンドウタイトルを設定する
    if context.serial_number() > 1:
      self._widget.setWindowTitle(self._widget.windowTitle() + (' (%d)' % context.serial_number()))

    # Widgetを親のオブジェクトに追加する
    context.add_widget(self._widget)

  # Pluginとしてのインターフェースを記述する
  def shutdown_plugin(self):
    pass

  def save_settings(self, plugin_settings, instance_settings):
    pass

  def restore_settings(self, plugin_settings, instance_settings):
    pass