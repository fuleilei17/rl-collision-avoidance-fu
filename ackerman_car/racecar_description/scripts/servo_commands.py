#!/usr/bin/env python

'''
author: fulei
date: 2022.10.06
note: 将接收的控制量ackermann_cmd_mux/output换成cmd_vel，让强化学习输出一致
参考网址：
https://blog.csdn.net/asafield/article/details/112835201
https://www.bilibili.com/video/BV1BE41177i4/?t=2314


author: fulei
date: 2022.10.06
note: line 73-77,参数改为*10，这样速度不会太快
'''
import rospy
import math
from std_msgs.msg import Bool
from std_msgs.msg import Float32
from std_msgs.msg import Float64
from geometry_msgs.msg import Twist
from ackermann_msgs.msg import AckermannDriveStamped

flag_move = 0

#设置最大的角度
def limsteer(data,maxdata):
    if data>0 and data > maxdata:
        data = maxdata
    elif data<0 and math.fabs(data) > maxdata:
        data = -maxdata
    return data


def set_speed(data):

    global flag_move
    #四个轮子的速度
    pub_vel_left_rear_wheel = rospy.Publisher('left_rear_wheel_velocity_controller/command', Float64, queue_size=1)
    pub_vel_right_rear_wheel = rospy.Publisher('right_rear_wheel_velocity_controller/command', Float64, queue_size=1)
    pub_vel_left_front_wheel = rospy.Publisher('left_front_wheel_velocity_controller/command', Float64, queue_size=1)
    pub_vel_right_front_wheel = rospy.Publisher('right_front_wheel_velocity_controller/command', Float64, queue_size=1)

    #前面两个轮子的打角
    pub_pos_left_steering_hinge = rospy.Publisher('left_steering_hinge_position_controller/command', Float64, queue_size=1)
    pub_pos_right_steering_hinge = rospy.Publisher('right_steering_hinge_position_controller/command', Float64, queue_size=1)
    
    #cmd_vel到阿克曼小车控制的转换   
    x = data.linear.x  
    z = data.angular.z
    L = 0.335   #轴距
    T = 0.305   #两侧轮子之间的距离
    if z!=0 and x!=0:
        r=math.fabs(x/z) #转弯半径（车子中心到转弯的圆心）

        rL_rear = r-(math.copysign(1,z)*(T/2.0))   #r为小车中心的转弯半径，所以T需要除以2在叠加上去
        rR_rear = r+(math.copysign(1,z)*(T/2.0))
        rL_front = math.sqrt(math.pow(rL_rear,2)+math.pow(L,2))
        rR_front = math.sqrt(math.pow(rR_rear,2)+math.pow(L,2))
        vL_rear = x*rL_rear/r
        vR_rear = x*rR_rear/r
        vL_front = x*rL_front/r
        vR_front = x*rR_front/r
        anL_front = math.atan2(L,rL_front)*math.copysign(1,z)
        anR_front = math.atan2(L,rR_front)*math.copysign(1,z)
        
    else:
        vL_rear = x
        vR_rear = x
        vL_front =x
        vR_front =x
        anL_front = z
        anR_front = z
    
    anL_front = limsteer(anL_front,0.6)  #最大转弯角度的弧度为0.6
    anR_front = limsteer(anR_front,0.6)
   
    pub_vel_left_rear_wheel.publish(vL_rear*10)
    pub_vel_right_rear_wheel.publish(vR_rear*10)
    pub_vel_left_front_wheel.publish(vL_front*10)
    pub_vel_right_front_wheel.publish(vR_front*10)
    pub_pos_left_steering_hinge.publish(anL_front)
    pub_pos_right_steering_hinge.publish(anR_front)

    '''
    throttle = data.drive.speed*13.95348
    steer = data.drive.steering_angle

    pub_vel_left_rear_wheel.publish(throttle)
    pub_vel_right_rear_wheel.publish(throttle)
    pub_vel_left_front_wheel.publish(throttle)
    pub_vel_right_front_wheel.publish(throttle)
    pub_pos_left_steering_hinge.publish(steer)
    pub_pos_right_steering_hinge.publish(steer)
    '''
    
def servo_commands():

    rospy.init_node('servo_commands', anonymous=True)

    #rospy.Subscriber("ackermann_cmd_mux/output", AckermannDriveStamped, set_throttle_steer)
    
    rospy.Subscriber("cmd_vel", Twist, set_speed)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    try:
        servo_commands()
    except rospy.ROSInterruptException:
        pass
