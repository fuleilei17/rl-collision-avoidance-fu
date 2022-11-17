# 多移动机器人（阿克曼小车）在gazebo中的配置

## 前言

最近需要进行异构多机器人方面的工作，在之前的工作中已经实现了多麦克纳姆轮小车在gazebo中的仿真。（如何在Gazebo中实现多机器人仿真 https://www.guyuehome.com/4889）

本文主要介绍了多阿克曼结构小车，在gazebo的配置过程。项目参考了古月居的阿克曼小车项目，以阿克曼小车的模型为基础，针对多机器人的仿真目的进行修改。

原项目github地址：https://github.com/guyuehome/guyueclass/tree/main/simulation%26control/ackerman_simulation

（这个项目在古月学院也有课程，因为作者主要是参考模型，所以没有参考课程，直接基于github源码修改，感兴趣的同学可以去看看课程。**如何在Gazebo中实现阿克曼转向车的仿真 • 王泽恩**https://class.guyuehome.com/detail/p_60541530e4b05a6195c158f0/6）

## 配置过程

### 1. launch文件修改

原有的仿真只考虑单机器人，需要对其launch文件做如下修改:

- 加入group及ns属性
- 去掉原有的全局`/racecar`的namepsace
- 使用`<tf_prefix>`重新定义tf关系

原launch文件：

```xml
	<!-- 加载机器人模型描述参数 -->
	<param name="robot_description" command="$(find xacro)/xacro --inorder '$(find racecar_description)/urdf/racecar.urdf.xacro'"/>


	<!--运行joint_state_publisher节点，发布机器人关节状态-->
	<!--<node name = "robot_state_publisher" pkg = "robot_state_publisher" type = "state_publisher">-->
	<node name= "robot_state_publisher" pkg= "robot_state_publisher" type= "robot_state_publisher">
		<param name="publish_frequency" type="double" value="20.0" />
		<remap from="/joint_states" to="/racecar/joint_states"/>
	</node>
	    <!-- 在gazebo中加载机器人模型-->
    <node name="urdf_spawner" pkg="gazebo_ros" type="spawn_model" respawn="false" output="screen"
          args="-urdf -model racecar -param robot_description -x $(arg x_pos) -y $(arg y_pos) -z $(arg z_pos)"/> 


	 <!-- 从yaml文件加载联合控制器的参数 -->
	<rosparam file="$(find bringup)/config/ctrl.yaml" command="load"/>
	
	<!-- 加载控制器 spawner -->
	<node name="controller_manager" pkg="controller_manager" type="spawner" 
	      respawn="false" output="screen" ns="/racecar" 
	      args="left_rear_wheel_velocity_controller       right_rear_wheel_velocity_controller
	            left_front_wheel_velocity_controller      right_front_wheel_velocity_controller
	            left_steering_hinge_position_controller   right_steering_hinge_position_controller
	            joint_state_controller"/>


<node pkg="racecar_description" type="servo_commands.py" name="servo_commands" output="screen">
</node>
```

修改后的launch文件：

```xml
<!--机器人robot_0-->
	<group ns="robot_0">
	
	<!-- 加载机器人模型描述参数 bodyframe作用是向xacro文件中传参-->	
	<param name="robot_description" command="$(find xacro)/xacro --inorder '$(find racecar_description)/urdf/racecar.urdf.xacro' bodyframe:=robot_0 ns:=robot_0"/>
	
	<!-- 运行joint_state_publisher节点，发布机器人的关节状态  --> 
    	<node name="joint_state_publisher" pkg="joint_state_publisher" type="joint_state_publisher" ></node> 

	<!-- 运行robot_state_publisher节点，发布tf  -->
	<!--<node name = "robot_state_publisher" pkg = "robot_state_publisher" type = "state_publisher">-->
	<node name= "robot_state_publisher" pkg= "robot_state_publisher" type= "robot_state_publisher">
		<param name="publish_frequency" type="double" value="20.0" />
		<param name="tf_prefix" value="robot_0" />
	</node>
	
	<!-- 在gazebo中加载机器人模型-->
    	<node name="urdf_spawner" pkg="gazebo_ros" type="spawn_model" respawn="false" output="screen"
          args="-urdf -model robot_0 -param robot_description -x $(arg x_pos0) -y $(arg y_pos0) -z $(arg z_pos0)"/> 


	 <!-- 从yaml文件加载联合控制器的参数 -->
	<rosparam file="$(find bringup)/config/ctrl.yaml" command="load"/>
	
	<!-- 加载控制器 spawner -->
	<node name="controller_manager" pkg="controller_manager" type="spawner" 
	      respawn="false" output="screen"
	      args="left_rear_wheel_velocity_controller       right_rear_wheel_velocity_controller
	            left_front_wheel_velocity_controller      right_front_wheel_velocity_controller
	            left_steering_hinge_position_controller   right_steering_hinge_position_controller
	            joint_state_controller"/>

	<!-- 舵机控制转换节点 -->
	<node pkg="racecar_description" type="servo_commands.py" name="servo_commands" output="screen"></node>
	
	</group>
```

### 2. urdf文件中的修改

1) 在原有的`racecar.urdf.xacro`文件中，在line468 对gazebo_ros_control的插件进行了namespace定义，需要进行删去，否则在launch文件中我们加入的group的ns属性无法加上去，gazebo会出现卡死的情况（也是一开始让我非常疑惑的一点）。

```xml
  <gazebo>
    <plugin name="gazebo_ros_control" filename="libgazebo_ros_control.so">
    <legacyModeNS>true</legacyModeNS>
    <robotSimType>gazebo_ros_control/DefaultRobotHWSim</robotSimType>
    <!--robotNamespace>/racecar</robotNamespace-->
    </plugin>
  </gazebo>
```

2) lidar.xacro, imu.xacro, camera.xacro中的topicname，都需要去掉全局“/”，否则无法加上命名空间。

### 3. yaml文件中的修改

在launch文件中我们需要从yaml文件加载联合控制器的参数，在原有的yaml文件中，文件的第一行写了`racecar：`，这样就导致yaml文件中的所有的参数都会加上`racecar/`的命名空间前缀，导致出错。我们需要将第一行的`racecar：`删去。

```yaml
#racecar:
  # Publish all joint states --公布所有--------------------
  joint_state_controller:
    type: joint_state_controller/JointStateController
    publish_rate: 50
  
    ....
```

### 4.`servo_commands.py` 和`keyboard_teleop.py`中的修改

这两个文件中的修改都一样，就是将所有的`/racecar`命名空间去掉，同时将所有全局消息改成局部消息（去掉前面的全局“/”）。

`例如：`

`/ackermann_cmd_mux/output   --->   ackermann_cmd_mux/output`
`/left_rear_wheel_velocity_controller/command  --->  left_rear_wheel_velocity_controller/command`

**servo_commands.py**

```python
pub_vel_left_rear_wheel = rospy.Publisher('left_rear_wheel_velocity_controller/command', Float64, queue_size=1)
pub_vel_right_rear_wheel = rospy.Publisher('right_rear_wheel_velocity_controller/command', Float64, queue_size=1)
pub_vel_left_front_wheel = rospy.Publisher('left_front_wheel_velocity_controller/command', Float64, queue_size=1)
pub_vel_right_front_wheel = rospy.Publisher('right_front_wheel_velocity_controller/command', Float64, queue_size=1)

pub_pos_left_steering_hinge = rospy.Publisher('left_steering_hinge_position_controller/command', Float64, queue_size=1)
pub_pos_right_steering_hinge = rospy.Publisher('right_steering_hinge_position_controller/command', Float64, queue_size=1)
...
rospy.Subscriber("ackermann_cmd_mux/output", AckermannDriveStamped, set_throttle_steer)
```

**keyboard_teleop.py**

```python
  pub = rospy.Publisher("ackermann_cmd_mux/output", AckermannDriveStamped,queue_size=1)
```

可以通过加命名空间对任一机器人进行键盘控制

`ROS_NAMESPACE=robot_0 rosrun racecar_description keyboard_teleop.py`

## 效果

## 总结

其实单机器人到多机器人的配置过程都大同小异，其关键在于运用<group>，将ns属性加给每一个机器人，使不同的机器人加载同一个urdf模型文件，同时可以用不同的namespace对其进行区分。

这一次配置的重点，就是在顶层加入namespace后，发现会有各种各样的bug，那么问题很清晰，肯定是下一层的配置文件中存在着不同的命名空间，导致上层命名失败。根据这个思路，一步步排查即可。

原项目作者的模型建的很好，只是可能没考虑到多机器人的运用，在他的基础上进行开发，也减少了很多重复造轮子的工作。之后作者也会一直更新基于多异构机器人平台的项目开发过程。



**“山路若抖缓步迈，斗酒洒羁绊”**