#include "dji_sdk_demo/ACSL_local_position_publisher.h"

#define ROW 6
#define COL 4

ros::Publisher ctrlPosYawPub;
ros::Publisher pub_local_position;

ros::Subscriber seqeunce;

uint8_t cpltFlag = 1;
uint8_t before = 0;
uint8_t now = 0;

using namespace std;


float trajectory[ROW][COL] = {
{0, 0, 10, 0},
{10, 0, 10, 0},
{10, 10, 10, 0},
{0, 10, 10, 0},
{0, 20, 10, 0},
{10, 20, 10, 0},
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "demo_local_position_control_node");
    ros::NodeHandle nh;

    pub_local_position = nh.advertise<dji_sdk::ACSL_local_position>("ACSL/local_position",10);

    ros::Subscriber seqeunceSub = nh.subscribe("dji_sdk/positionCplt", 10, &ACSL_seqeunce_callback);

    dji_sdk::ACSL_local_position local_position;

    local_position.seq = 0;
    local_position.targetX = 0;
    local_position.targetY = 0;
    local_position.targetZ = 0;
    local_position.targetYaw = 0;
    pub_local_position.publish(local_position);

    while (1)
    {
        while(1)
        {
            ros::spinOnce();
            if(cpltFlag == 1)
            {
                ROS_INFO("HEHE WE ARE THE ONE");
                cpltFlag = 0;
                break;
            }
        }
        ROS_INFO("HEHE WE ARE THE TWO");

        char a;

        float target[COL] = {0,};
        

        for(int i = 0 ; i < COL; i ++)
        {
            target[i] = trajectory[now][i];
            cout << target[i] << endl;
        }


        ROS_INFO("HEHE WE ARE THE THREE");

        

        
        ros::Duration(0.5).sleep();
        /*
        cout << "target local x" << endl << " : ";
        cin >> target[0];
        cout << "target local y" << endl << " : ";
        cin >> target[1];
        cout << "target local z" << endl << " : ";
        cin >> target[2];
        cout << "target yaw" << endl << " : ";
        cin >> target[3];
*/
        local_position.seq++;
        local_position.targetX = target[0];
        local_position.targetY = target[1];
        local_position.targetZ = target[2];
        local_position.targetYaw = target[3];
        cout << "local x" << local_position.targetX << endl;
        cout << "local x" << local_position.targetY << endl;
        cout << "local x" << local_position.targetZ << endl;
        cout << "local x" << local_position.targetYaw << endl;

        pub_local_position.publish(local_position);
        ros::spinOnce();
        ROS_INFO("HEHE WE ARE THE FOUR");
    }

    return 0;
}




void ACSL_seqeunce_callback(const std_msgs::UInt8::ConstPtr& msg)
{
    now = msg->data;
    
    if(now != before)
    {
        cpltFlag = 1;
        before = now;
        ROS_INFO("hello i am here");
    }
}