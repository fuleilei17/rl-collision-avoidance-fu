'''
date:2022.10.25
author: fulei
note: 

line126 避障距离改为0.5

'''
import time
import rospy
import copy
import tf
import numpy as np

from gazebo_msgs.srv import *#重置Gazebo中机器人位置的服务
from geometry_msgs.msg import Twist, Pose
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
from rosgraph_msgs.msg import Clock
from std_srvs.srv import Empty
from std_msgs.msg import Int8

from model.utils import test_init_pose, test_goal_point


class GazeboWorld():
    def __init__(self, beam_num, index, num_env):
        self.index = index
        self.num_env = num_env
        node_name = 'StageEnv_' + str(index)
        rospy.init_node(node_name, anonymous=None)

        self.beam_mum = beam_num
        self.laser_cb_num = 0
        self.scan = None

        self.COLLISION_DISTANCE=0.5 #碰撞检测距离
        # used in reset_world
        '''self.self_speed = [0.0, 0.0]
        self.step_goal = [0., 0.]
        self.step_r_cnt = 0.'''

        # used in generate goal point
        self.map_size = np.array([8., 8.], dtype=np.float32)  # 8x8m
        self.goal_size = 0.5

        self.robot_value = 10.
        self.goal_value = 0.
        # self.reset_pose = None

        self.init_pose = None



        # for get reward and terminate
        self.stop_counter = 0

        # -----------Publisher and Subscriber-------------
        cmd_vel_topic = 'robot_' + str(index) + '/cmd_vel'
        self.cmd_vel = rospy.Publisher(cmd_vel_topic, Twist, queue_size=10)

        '''cmd_pose_topic = 'robot_' + str(index) + '/cmd_pose'
        self.cmd_pose = rospy.Publisher(cmd_pose_topic, Pose, queue_size=2)'''

        object_state_topic = 'robot_' + str(index) + '/base_pose_ground_truth'
        self.object_state_sub = rospy.Subscriber(object_state_topic, Odometry, self.ground_truth_callback)

        #stage雷达话题名
        #laser_topic = 'robot_' + str(index) + '/base_scan'

        #gazebo雷达话题名
        laser_topic = 'robot_' + str(index) + '/scan'

        self.laser_sub = rospy.Subscriber(laser_topic, LaserScan, self.laser_scan_callback)

        odom_topic = 'robot_' + str(index) + '/odom'
        self.odom_sub = rospy.Subscriber(odom_topic, Odometry, self.odometry_callback)

        '''crash_topic = 'robot_' + str(index) + '/is_crashed'
        self.check_crash = rospy.Subscriber(crash_topic, Int8, self.crash_callback)'''
        
        self.sim_clock = rospy.Subscriber('clock', Clock, self.sim_clock_callback)

        # -----------Service-------------------
        #self.reset_stage = rospy.ServiceProxy('reset_positions', Empty)
        rospy.wait_for_service('/gazebo/set_model_state')#重置机器人的位姿
        self.set_state_service = rospy.ServiceProxy('/gazebo/set_model_state', SetModelState)


        # # Wait until the first callback
        self.speed = None
        self.state = None
        self.speed_GT = None
        self.state_GT = None
        while self.scan is None or self.speed is None or self.state is None\
                or self.speed_GT is None or self.state_GT is None:
            pass

        rospy.sleep(1.)
        # # What function to call when you ctrl + c
        # rospy.on_shutdown(self.shutdown)


    def ground_truth_callback(self, GT_odometry):
        Quaternious = GT_odometry.pose.pose.orientation
        Euler = tf.transformations.euler_from_quaternion([Quaternious.x, Quaternious.y, Quaternious.z, Quaternious.w])
        self.state_GT = [GT_odometry.pose.pose.position.x, GT_odometry.pose.pose.position.y, Euler[2]]
        v_x = GT_odometry.twist.twist.linear.x
        v_y = GT_odometry.twist.twist.linear.y
        v = np.sqrt(v_x**2 + v_y**2)
        self.speed_GT = [v, GT_odometry.twist.twist.angular.z]

    def laser_scan_callback(self, scan):
        self.scan_param = [scan.angle_min, scan.angle_max, scan.angle_increment, scan.time_increment,
                           scan.scan_time, scan.range_min, scan.range_max]
        self.scan = np.array(scan.ranges)
        self.laser_cb_num += 1

        '''碰撞检测'''
        self.scan_filter = []
        for i in range(360):
            if i <= 15 or i > 335:
                self.scan_filter.append(self.scan[i])
        if min(self.scan_filter) < self.COLLISION_DISTANCE: #避障距离设置为0.5m
            self.is_crashed=1
        else:
            self.is_crashed=0


    def odometry_callback(self, odometry):
        Quaternions = odometry.pose.pose.orientation
        Euler = tf.transformations.euler_from_quaternion([Quaternions.x, Quaternions.y, Quaternions.z, Quaternions.w])
        self.state = [odometry.pose.pose.position.x, odometry.pose.pose.position.y, Euler[2]]
        self.speed = [odometry.twist.twist.linear.x, odometry.twist.twist.angular.z]

    def sim_clock_callback(self, clock):
        self.sim_time = clock.clock.secs + clock.clock.nsecs / 1000000000.

    '''def crash_callback(self, flag):
        self.is_crashed = flag.data'''

    def get_self_stateGT(self):
        return self.state_GT

    def get_self_speedGT(self):
        return self.speed_GT

    def get_laser_observation(self):
        scan = copy.deepcopy(self.scan)
        scan[np.isnan(scan)] = 6.0
        scan[np.isinf(scan)] = 6.0
        raw_beam_num = len(scan)#360
        sparse_beam_num = self.beam_mum#512
        step = float(raw_beam_num) / sparse_beam_num
        sparse_scan_left = []
        index = 0.
        for x in range(int(sparse_beam_num / 2)):
            sparse_scan_left.append(scan[int(index)])
            index += step
        sparse_scan_right = []
        index = raw_beam_num - 1.
        for x in range(int(sparse_beam_num / 2)):
            sparse_scan_right.append(scan[int(index)])
            index -= step
        scan_sparse = np.concatenate((sparse_scan_left, sparse_scan_right[::-1]), axis=0)
        return scan_sparse / 6.0 - 0.5


    def get_self_speed(self):
        return self.speed

    def get_self_state(self):
        return self.state

    def get_crash_state(self):
        return self.is_crashed
        
    def get_env_index(self):
        return self.index

    def get_sim_time(self):
        return self.sim_time

    def get_local_goal(self):
        [x, y, theta] = self.get_self_stateGT()
        [goal_x, goal_y] = self.goal_point
        local_x = (goal_x - x) * np.cos(theta) + (goal_y - y) * np.sin(theta)
        local_y = -(goal_x - x) * np.sin(theta) + (goal_y - y) * np.cos(theta)
        return [local_x, local_y]


    def generate_goal_point(self):
        [x_g, y_g] = self.generate_random_goal()
        self.goal_point = [x_g, y_g]
        [x, y] = self.get_local_goal()

        self.pre_distance = np.sqrt(x ** 2 + y ** 2)
        self.distance = copy.deepcopy(self.pre_distance)

    '''
    #设置明确的目标点用于Gazebo中的仿真
    def generate_goal_point(self):
        self.init_pose = self.get_self_stateGT()#ppo_stage1.py中的126行计算distance会用到
        self.goal_point = test_goal_point(self.index)

        [x, y] = self.get_local_goal()

        self.pre_distance = np.sqrt(x ** 2 + y ** 2)
        self.distance = copy.deepcopy(self.pre_distance)
    '''
    def get_reward_and_terminate(self, t):
        terminate = False
        laser_scan = self.get_laser_observation()
        [x, y, theta] = self.get_self_stateGT()
        [v, w] = self.get_self_speedGT()
        self.pre_distance = copy.deepcopy(self.distance)
        self.distance = np.sqrt((self.goal_point[0] - x) ** 2 + (self.goal_point[1] - y) ** 2)
        reward_g = (self.pre_distance - self.distance) * 2.5#奖励与距离成反比
        reward_c = 0
        reward_w = 0
        result = 0
        is_crash = self.get_crash_state()

        if self.distance < self.goal_size:
            terminate = True
            reward_g = 15
            result = 'Reach Goal'

        if is_crash == 1:
            terminate = True
            reward_c = -15.
            result = 'Crashed'

        if np.abs(w) >  1.05:
            reward_w = -0.1 * np.abs(w)

        if t > 500:
            terminate = True
            result = 'Time out'
        reward = reward_g + reward_c + reward_w

        return reward, terminate, result

    def reset_pose(self):#同时重置所有追捕者的位姿
        reset_pose = self.generate_random_pose()
        rospy.sleep(0.05)
        self.control_pose(reset_pose)
        rospy.sleep(0.05)

    def control_pose(self, pose):
        '''重置robot_+str(index)位姿的服务'''
        print('in control pose')
        qtn = tf.transformations.quaternion_from_euler(0, 0, pose[2], 'rxyz')
        objstate = SetModelStateRequest()  # Create an object of type SetModelStateRequest
        objstate.model_state.model_name = 'robot_'+str(self.index) 
        objstate.model_state.pose.position.x = pose[0]
        objstate.model_state.pose.position.y = pose[1]
        objstate.model_state.pose.position.z = 0
        objstate.model_state.pose.orientation.w = qtn[3]
        objstate.model_state.pose.orientation.x = qtn[0]
        objstate.model_state.pose.orientation.y = qtn[1]
        objstate.model_state.pose.orientation.z = qtn[2]
        objstate.model_state.twist.linear.x = 0.0
        objstate.model_state.twist.linear.y = 0.0
        objstate.model_state.twist.linear.z = 0.0
        objstate.model_state.twist.angular.x = 0.0
        objstate.model_state.twist.angular.y = 0.0
        objstate.model_state.twist.angular.z = 0.0
        objstate.model_state.reference_frame = "world"
        result = self.set_state_service(objstate)


    def control_vel(self, action):
        move_cmd = Twist()
        move_cmd.linear.x = action[0]
        move_cmd.linear.y = 0.
        move_cmd.linear.z = 0.
        move_cmd.angular.x = 0.
        move_cmd.angular.y = 0.
        move_cmd.angular.z = action[1]
        self.cmd_vel.publish(move_cmd)



    def generate_random_pose(self):
        x = np.random.uniform(-5, 5) #在10*10的地图大小上更新位姿
        y = np.random.uniform(-5, 5)
        dis = np.sqrt(x ** 2 + y ** 2)
        while (dis > 5) and not rospy.is_shutdown():#距离原点的距离不超过5m
            x = np.random.uniform(-5, 5)
            y = np.random.uniform(-5, 5)
            dis = np.sqrt(x ** 2 + y ** 2)
        theta = np.random.uniform(0, 2 * np.pi)
        return [x, y, theta]

    def generate_random_goal(self):
        self.init_pose = self.get_self_stateGT()#当前小车位置
        x = np.random.uniform(-5, 5)
        y = np.random.uniform(-5, 5)
        dis_origin = np.sqrt(x ** 2 + y ** 2)
        dis_goal = np.sqrt((x - self.init_pose[0]) ** 2 + (y - self.init_pose[1]) ** 2)#更新的目标位置和小车原位置的距离
        while (dis_origin > 5 or dis_goal > 6 or dis_goal < 4) and not rospy.is_shutdown():#目标位置限定在半径5m的圆内，
            x = np.random.uniform(-5, 5)
            y = np.random.uniform(-5, 5)
            dis_origin = np.sqrt(x ** 2 + y ** 2)
            dis_goal = np.sqrt((x - self.init_pose[0]) ** 2 + (y - self.init_pose[1]) ** 2)

        return [x, y]





