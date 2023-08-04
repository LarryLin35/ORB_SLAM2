"""
Before runn this program in this Unbuntu 18.04 VM, need to move to /ORB_SLAM2/Python/PythonEnvironment and execute "source py_env_01/bin/activate" in Terminal.
"""

import cv2
import os
import time
import concurrent.futures

def save_frame(frame, output_path):
    cv2.imwrite(output_path, frame)

if __name__ == "__main__":
    cap = cv2.VideoCapture(0) 
    #cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280) # The default of the MSI laptop camera is 640*480 in this Unbuntu 18.04 VM
    #cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720) # The default of the MSI laptop camera is 640*480 in this Unbuntu 18.04 VM
    while True:
        ret, frame = cap.read()
        if not ret or frame is None:  # Check if frame was read successfully
            print("Failed to read frame")
            continue
        cv2.imshow('Live Video', frame) 
        if cv2.waitKey(1) == ord('q'): # Press 'q' to leave the loop
            break
    cap.release()
    cv2.destroyAllWindows()

