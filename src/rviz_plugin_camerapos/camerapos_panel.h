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
            virtual void load(const rviz::Config& config);
            virtual void save(rviz::Config config) const;

            void newPos(std::string name, std::vector<float> position, std::vector<float> rotation);

            void refreshTree();
            
        private Q_SLOTS:

        protected:
            Ui::MainUI* ui_;
            int value_{0};
            std::string topic_name_{"camerapos"};
            
            ros::NodeHandle nh_;
            ros::Publisher pub_;
    
            rviz::Config pos_list_config_;
    };
}