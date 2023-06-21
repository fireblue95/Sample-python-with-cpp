import task
import cv2

frame = cv2.imread('cat.jpg')

frame = cv2.resize(frame, (1280, 720))
print(frame.shape)

time1 = task.preprocess(frame.shape[1], frame.shape[0], bytearray(frame))

print('time:', time1)
