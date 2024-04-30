#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <rviz/panel.h>
#endif

namespace Ui
{
    class MainUI;
}

namespace rviz_plugin_camerapos
{
    class CameraposPanel: public rviz::Panel
    {
        Q_OBJECT
        
        public:
            CameraposPanel(QWidget* parent = nullptr);
            ~CameraposPanel() override;

            void onInitialize() override;
            void onEnable();
            void onDisable();

        private Q_SLOTS:

        protected:
            Ui::MainUI* ui_;
            int value_{0};
            std::string topic_name_{"camerapos"};
            ros::NodeHandle nh_;
            ros::Publisher pub_;
    };
}