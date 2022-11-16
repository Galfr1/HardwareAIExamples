import cv2
import tkinter as tk
import os

window = tk.Tk()
window.title("Name")
window.geometry("800x800")

def cap():
    cam = cv2.VideoCapture(0)

    cv2.namedWindow("press space to take a photo", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("press space to take a photo", 500, 300)

    img_counter = 0
    
    DIR = '/dataset/'+name
    print(DIR)
    
    if os.path.exists(DIR):
        img_counter = img_counter + len([name for name in os.listdir(DIR) if os.path.isfile(os.path.join(DIR, name))])
        print('exists - shots will be added')
    else:
        print('dirctory will be created')

    while True:
        ret, frame = cam.read()
        if not ret:
            print("failed to grab frame")
            break
        cv2.imshow("press space to take a photo", frame)

        k = cv2.waitKey(1)
        if k%256 == 27:
            # ESC pressed
            print("Escape hit, closing...")
            break
        elif k%256 == 32:
            # SPACE pressed
            print(name)
            img_name = "dataset/"+ name +"/image_{}.jpg".format(img_counter)
            img_name = img_name.replace('\n', '')
            cv2.imwrite(img_name, frame)
            print("{} written!".format(img_name))
            img_counter += 1

    cam.release()

    cv2.destroyAllWindows()


input = tk.Text(window)
def read():
    global name
    name = ''
    print(name)
    inp = input.get("1.0", tk.END)
    name = inp.lower().replace(" ", "")
    print(name)
    window.destroy()
    
    pop = tk.Tk()
    pop.title("Important")
    pop.geometry("600x600")

    lab = tk.Label(pop, text="press space to take a photo in the next window, esc to close...")
    lab.pack()
    bt1 = tk.Button(pop, text="OK", command=cap)
    bt1.pack()

button = tk.Button(window, text="OK", command=read)
lab1 = tk.Label(window, text="Please enter a name:")
lab1.pack()
input.pack()
button.pack()
window.mainloop()
