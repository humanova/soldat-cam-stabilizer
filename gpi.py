import numpy as np
import cv2
from PIL import ImageGrab as ig
import time
import keyboard
import os

cv2.namedWindow("window")
cv2.moveWindow("window",1050, 600)

def create_folder():
    os.chdir('data')
    name = str(int(time.time()))
    os.mkdir(name)
    os.chdir(name)
    return name

def process_img(original_image):
    processed_img = cv2.cvtColor(original_image, cv2.COLOR_BGR2RGB)
    return processed_img

frame = 0
save_mode = False
create_folder()

while(True):

    screen = np.array(ig.grab(bbox=(487,345,538,403)))
    new_screen = process_img(screen)
    cv2.imshow("window", new_screen)
    
    if save_mode:
        cv2.imwrite(str(frame) + '.png', new_screen)
        frame +=1

    if keyboard.is_pressed('['):
        save_mode = not save_mode
        print('save mode : ', save_mode)

    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break