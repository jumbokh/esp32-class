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
