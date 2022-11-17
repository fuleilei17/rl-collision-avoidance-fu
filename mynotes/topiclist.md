针对循环判断部分：
while self.scan is None or self.speed is None or self.state is None\
                or self.speed_GT is None or self.state_GT is None or self.is_crashed is None:


            #调试
            #print("enter the loop of waiting for first callback")    

            pass


self.scan  ->  claser_scan_callback  ->  /scan

self.speed  ->  odometry_callback  ->  /odom

self.state  ->   odometry_callback  ->  /odom

self.is_crashed  ->  crash_callback   -> /is_crashed

self.state_GT  ->  ground_truth_callback  -> /base_pose_ground_truth

self.speed_GT  ->  ground_truth_callback  ->  /base_pose_ground_truth

