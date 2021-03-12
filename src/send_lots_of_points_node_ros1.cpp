
/*
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "pcl_conversions/pcl_conversions.h"

#include "ros/ros.h"
#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/PointCloud2.h"
#include "math.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "send_lots_of_points");

  int rate = 1;
  int width = 100;
  int length = 100;

  if (argc > 1)
  {
    rate = atoi(argv[1]);
  }
  if (argc > 2)
  {
    width = atoi(argv[2]);
  }
  if (argc > 3)
  {
    length = atoi(argv[3]);
  }

  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<sensor_msgs::PointCloud>("pointcloud", 100);
  ros::Publisher pub2 = nh.advertise<sensor_msgs::PointCloud2>("pointcloud2", 100);
  ros::Rate loop_rate(rate);

  sensor_msgs::PointCloud msg;
  msg.points.resize(width * length);
  msg.header.frame_id = "map";

  pcl::PointCloud<pcl::PointXYZI> cloud;

  int count = 0;
  while (ros::ok())
  {
    // width++;
    msg.points.resize(width * length + (count % 2));

    for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < length; y++)
      {
        geometry_msgs::Point32 &point = msg.points[x + y * width];
        point.x = float(x / 100.0);
        point.y = float(y / 100.0);
        point.z = ((x + y + count) % 100) / 100.0;
        pcl::PointXYZI tmp_point;
        tmp_point.x = static_cast<float>(x / 100.0);
        tmp_point.y = static_cast<float>(y / 100.0);
        tmp_point.z = static_cast<float>(((x + y + count) % 100) / 100.0f);
        tmp_point.intensity = 1.0;
        cloud.push_back(tmp_point);
      }
    }
    // if (count % 2)
    // {
    //   msg.points[width * length + 1].x = -.1;
    //   msg.points[width * length + 1].y = -.1;
    //   msg.points[width * length + 1].z = 1.1;
    // }
    msg.header.seq = count;
    msg.header.stamp = ros::Time::now();

    printf("publishing at %d hz, %d x %d points.\n", rate, width, length);

    pub.publish(msg);

    sensor_msgs::PointCloud2 msg2;
    pcl::toROSMsg(cloud, msg2);
    msg2.header.frame_id = "map";
    pub2.publish(msg2);

    ros::spinOnce();
    loop_rate.sleep();
    // count++;
  }
}
