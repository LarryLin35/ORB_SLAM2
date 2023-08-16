import cv2
import os

if __name__ == "__main__":
    cap = cv2.VideoCapture(0)

    count = 0  
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Can't receive frame. Exit.")
            break

        cv2.imshow('Live Video', frame) 

        key = cv2.waitKey(1)
        if key == ord('q'): 
            break
        elif key == ord('s'):  
            cv2.imwrite(f'Image/{count}.png', frame)
            count += 1  

    cap.release()
    cv2.destroyAllWindows()


