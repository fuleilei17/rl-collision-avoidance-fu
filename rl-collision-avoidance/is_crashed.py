Header header            # Header也是一个结构体,包含了seq,stamp,frame_id,其中seq指的是扫描顺序增加的id,stamp包含了开始扫描的时间和与开始扫描的时间差,frame_id是扫描的参考系名称.注意扫描是逆时针从正前方开始扫描的.

float32 angle_min        # 开始扫描的角度(角度)
float32 angle_max        # 结束扫描的角度(角度)
float32 angle_increment  # 每一次扫描增加的角度(角度)

float32 time_increment   # 测量的时间间隔(s)
float32 scan_time        # 扫描的时间间隔(s)

float32 range_min        # 距离最小值(m)
float32 range_max        # 距离最大值(m)

float32[] ranges         # 距离数组(长度360)
float32[] intensities    # 与设备有关,强度数组(长度360)


import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

class Obstacle():
    def __init__(self):
        self.LIDAR_ERR = 0.05
        self._cmd_pub = rospy.Publisher('cmd_vel', Twist, queue_size=1)
        self.obstacle()

    def get_scan(self):
        msg = rospy.wait_for_message("scan", LaserScan)
        self.scan_filter = []
        for i in range(360):
            if i <= 15 or i > 335:
                if msg.ranges[i] >= self.LIDAR_ERR:
                    self.scan_filter.append(msg.ranges[i])

    def obstacle(self):
        self.twist = Twist()
        while not rospy.is_shutdown():
            self.get_scan()

            if min(self.scan_filter) < 0.5:
                self.twist.linear.x = 0.0
                self.twist.angular.z = 0.0
                self._cmd_pub.publish(self.twist)
                rospy.loginfo('Stop!')

            else:
                self.twist.linear.x = 0.0
                self.twist.angular.z = 0.0
                rospy.loginfo('distance of the obstacle : %f', min(self.scan_filter))

            self._cmd_pub.publish(self.twist)

def main():
    rospy.init_node('turtlebot_scan')
    try:
        obstacle = Obstacle()
    except rospy.ROSInterruptException:
        pass

if __name__ == '__main__':
    main()


def get_crash_state(self):
    self.LIDAR_ERR = 0.05
    self.scan_filter = []
    for i in range(360):
        if i <= 15 or i > 335:
            if msg.ranges[i] >= self.LIDAR_ERR:
                self.scan_filter.append(msg.ranges[i])
    if min(self.scan_filter) < 0.25:#避障距离设置为0.25m
        self.is_crashed=1
    else:
        self.is_crashed=0
    return self.is_crashed