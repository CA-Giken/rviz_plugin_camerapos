#include <pluginlib/class_list_macros.h>
#include <std_msgs/Float64.h>

#include "camerapos_panel.h"
#include "ui_main.h"

namespace rviz_plugin_camerapos 
{
    CameraposPanel::CameraposPanel(QWidget* parent) : rviz::Panel( parent ), ui_(new Ui::MainUI())
    {
        ui_->setupUi(this);
    }
    CameraposPanel::~CameraposPanel() = default;

    void CameraposPanel::onInitialize()
    {
        pub_ = nh_.advertise<std_msgs::Float64>("camerapos", 1);
        parentWidget()->setVisible(true);
    }

    void CameraposPanel::onEnable()
    {
        show();
        parentWidget()->show();
    }

    void CameraposPanel::onDisable()
    {
        hide();
        parentWidget()->hide();
    }
}
PLUGINLIB_EXPORT_CLASS(rviz_plugin_camerapos::CameraposPanel, rviz::Panel)