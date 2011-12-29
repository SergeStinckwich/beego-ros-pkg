/**********************************************************************************/
/*!
	@file main.cpp
	@brief sample program for controlling beego
	@author Kazuyuki KON
*/
/**********************************************************************************/

#include "ros/ros.h"					  //!< ROS
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/PoseStamped.h"//!< Message type for position
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
//#include "sensor_msgs/LaserScan.h"//!< 2d scandata
#include "beego/velocity.h"			  //!< Self deefined type for velocity
#include <sstream>					      //!<
#include "../include/mybeego.h"          //!< beego
#include <math.h>

static const char* beegoPort = "/dev/ttyUSB0";//!< Device name of beego

static int beegoBaudrate      = 115200;		//!< Baudrate of communication devide for beego


bool isNew;			//!< is new velocity data available
double v,w;			//!< velocity input [m/sec, rad/sec]
double vx,vy,vz;

/**********************************************************************************/
/*!
*	@brief Callback function for velocity subscriber
*	@param[in]
*/
/**********************************************************************************/
//void velocityCallback(const beego::velocityConstPtr& _velocity )
void velocityCallback(const geometry_msgs::Twist::ConstPtr & _velocity )
{
    vx = _velocity->linear.x;
    vy = _velocity->linear.y;
    vz = _velocity->linear.z;

    v = sqrt(vx*vx+vy*vy+vz*vz);
    w = _velocity->angular.z;
    isNew = true;
    ROS_INFO("Received input %d[m/sec] %d[rad/sec]",v,w);

}

/**********************************************************************************/
/*!
*	@brief main 
*	@param[in] argc 
*	@param[in] argv 
*/
/**********************************************************************************/
int main(int argc, char **argv)
{
	RunCtrl run;					//for beego
	int pre_times = 0;				//Counter for lrf capture
	nav_msgs::Odometry odom;//for odometry data
	//Connect to  beego
  	if(!run.isConnected())
  	{
  		if(run.connect(beegoPort,beegoBaudrate) <0 )
  		{
  			std::cout<<run.what()<<std::endl;
  			return -1;
  		}
  	}

	ros::init(argc, argv, "beego");
	tf::TransformBroadcaster tfb;

	//Setting of Subscriber(vel) and Publisher(lrfdata,odometry)
	ros::NodeHandle nh;
	ros::Subscriber velSub = nh.subscribe("beego/velocity",1,&velocityCallback);
	ros::Publisher  odom_pub = nh.advertise<nav_msgs::Odometry>("beego/odometry", 50);

	ros::Rate loop_rate(10);

	double th = 0.0;
	double dth = 0.0;

 	// time initialization
  	ros::Time current_time, last_time;
	current_time = ros::Time::now();
	last_time = ros::Time::now();


	//Main loop
	printf("Push 'q' to exit\n");
	while ( ros::ok() )
	{
		current_time = ros::Time::now();

		//Apply control input to beego
		if( isNew )
		{
			setVelocityCtrl(run, (v*1000), w );
			isNew = false;
		}
		//Get odometry data and publish
		VXV::Position pos =  run.getRunPosition();
		int ticks           = run.crd_ticks;
		//sec ;  ticks/1000;
		//nsec;  (ticks - (ticks/1000)*1000)*1000;
		//position
		odom.pose.pose.position.x = (double)pos.x / 1000;
		odom.pose.pose.position.y = (double)pos.y / 1000;
		odom.pose.pose.position.z = 0.0;

		double x = (double)pos.x / 1000;
		double y = (double)pos.y / 1000;
		double z = 0;
		
		//double dt = (current_time - last_time).toSec();
		//double dth = w * dt;
		//th = th+ dth;
		
		th = (double)pos.zt.to_rad();
 
  		//first, we'll publish the transform over tf
  		//position and velocity of frame base_link w.r.t. frame odom (fixed frame)
  		geometry_msgs::TransformStamped odom_trans;
		odom_trans.header.stamp = current_time;
		odom_trans.header.frame_id = "base_link";
		odom_trans.child_frame_id = "odom";
		odom_trans.transform.translation.x = x;
		odom_trans.transform.translation.y = y;
		odom_trans.transform.translation.z = 0.0;
		odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(th);
		tfb.sendTransform(odom_trans);
		 
		//next, we'll publish the odometry message over ROS
		nav_msgs::Odometry odom;
		odom.header.stamp = current_time;
		odom.header.frame_id = "base_link";
		odom.child_frame_id = "odom";
		odom.pose.pose.position.x = x;
		odom.pose.pose.position.y = y;
		odom.pose.pose.position.z = z;
		odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(th);
		odom.twist.twist.linear.x = vx;
		odom.twist.twist.linear.y = vy;
		odom.twist.twist.angular.z = w;
		odom_pub.publish(odom);

	
		last_time = current_time;		

		//ros loop
		ros::spinOnce();//only once
		loop_rate.sleep();
	}//end of while
	setVelocityCtrl(run, (v*1000), w );
	run.disconnect();

	return 0;
}
