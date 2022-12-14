#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 该例程将请求“/spawn”服务，服务数据类型“turtlesim::Spawn”
import sys
import rospy
from turtlesim.srv import Spawn

def turtle_spawn():
    rospy.init_node('turtle_spawn') # ROS节点初始化
    # 发现“/spawn”服务后，创建一个客户端，连接名为“/spawn”的service
    rospy.wait_for_service('/spawn')

    try:
        add_turtle = rospy.ServiceProxy('/spawn', Spawn)
        # 请求服务调用，输入请求数据
        response = add_turtle(2.0, 2.0, 0.0, "turtle2")
        return response.name
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

if __name__ == "__main__":
    # 服务调用并显示调用结果
    print "Spwan turtle successfully [name:%s]" %(turtle_spawn())
