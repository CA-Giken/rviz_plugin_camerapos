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
        ROS_INFO("TEST");
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

    void CameraposPanel::load( const rviz::Config& config)
    {
        // rviz configから読み込み
        rviz::Panel::load( config );
        pos_list_config_ = config.mapGetChild("pos_list");
        
        // ツリー更新
        CameraposPanel::refreshTree();        
    };
    
    void CameraposPanel::save(rviz::Config config) const
    {

    };

    void CameraposPanel::newPos(std::string name, std::vector<float> position, std::vector<float> rotation) {
        // 新しい子エントリを作成
        rviz::Config position_config = pos_list_config_.listAppendNew();
        QString qname = QString::fromStdString(name);
        // 各キーと値を保存
        position_config.mapSetValue("name", qname);
        position_config.mapSetValue("x", position[0]);
        position_config.mapSetValue("y", position[1]);
        position_config.mapSetValue("z", position[2]);
        position_config.mapSetValue("rx", rotation[0]);
        position_config.mapSetValue("ry", rotation[1]);
        position_config.mapSetValue("rz", rotation[2]);

        // ツリー更新
        CameraposPanel::refreshTree();
    }

    void CameraposPanel::refreshTree(){
        // ツリーをクリア
        ui_->treeWidget->clear();

        // 当クラスに保持されたConfigからツリーを再構成
        for(int32_t i = 0; i < pos_list_config_.listLength(); ++i){
            rviz::Config position_config = pos_list_config_.listChildAt(i);
            QString qname;
            float x, y, z, rx, ry, rz;

            if (position_config.mapGetString("name", &qname) &&
                position_config.mapGetFloat("x", &x) &&
                position_config.mapGetFloat("y", &y) &&
                position_config.mapGetFloat("z", &z) &&
                position_config.mapGetFloat("rx", &rx) &&
                position_config.mapGetFloat("ry", &ry) &&
                position_config.mapGetFloat("rz", &rz)) {
                QTreeWidgetItem* item = new QTreeWidgetItem(ui_->treeWidget);
                item->setText(0, qname);
            }
        }
    }
}
PLUGINLIB_EXPORT_CLASS(rviz_plugin_camerapos::CameraposPanel, rviz::Panel)