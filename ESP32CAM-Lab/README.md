## cv2 show on colab
* [Introduction to Image Processing in Python](https://colab.research.google.com/github/xn2333/OpenCV/blob/master/Image_Processing_in_Python_Final.ipynb)
* Google patch in colab
##
<pre>
import cv2
from google.colab.patches import cv2_imshow
img = cv2.imread('predictions.jpg', cv2.IMREAD_UNCHANGED)
cv2_imshow(img)
</pre>
##
* video streaming in jupyter notebook
    * [Video streaming in the Jupyter Notebook](https://towardsdatascience.com/video-streaming-in-the-jupyter-notebook-635bc5809e85)
    * [Displaying real-time webcam stream in IPython at (relatively) high framerate](https://medium.com/@kostal91/displaying-real-time-webcam-stream-in-ipython-at-relatively-high-framerate-8e67428ac522)
    * [Live video streaming over network with OpenCV and ImageZMQ](https://www.pyimagesearch.com/2019/04/15/live-video-streaming-over-network-with-opencv-and-imagezmq/)
    * [Webcam capture with ffmpeg and OpenCV from Jupyter Notebook](https://www.bojankomazec.com/2020/12/webcam-capture-with-ffmpeg-and-opencv.html)
