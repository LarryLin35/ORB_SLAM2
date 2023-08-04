"""
Before runn this program in this Unbuntu 18.04 VM, need to move to /ORB_SLAM2/Python/PythonEnvironment and execute "source py_env_01/bin/activate" in Terminal.
"""

import cv2
import os
import time
import concurrent.futures

if __name__ == "__main__":
    frame_counter = 0
    frame_counter_last_sec = 0
     
    cap = cv2.VideoCapture(0)
    
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280) # The default of the MSI laptop camera is 640*480 in this Unbuntu 18.04 VM
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720) # The default of the MSI laptop camera is 640*480 in this Unbuntu 18.04 VM
    
    start_time = time.time()
    while True:
        ret, frame = cap.read()

        cv2.imwrite(f'Temp_02/{frame_counter}.png',frame)
        frame_counter += 1
        
        # if one second has passed
        if time.time() - start_time >= 1:
            print(f"Saved {frame_counter - frame_counter_last_sec} frames in the last second.")
            frame_counter_last_sec = frame_counter
            start_time = time.time()  
        
        
    cap.release()
    cv2.destroyAllWindows()

