import cv2
# 選擇攝影機
cap = cv2.VideoCapture(0)

while cap.isOpened():
  # 從攝影機擷取一張影像
  ret, frame = cap.read() #ret=retval,frame=image    
  # 顯示圖片
  cv2.imshow('frame', frame)
  #轉成灰階
  #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
  #cv2.imshow('frame', gray)

  # 按a拍照存檔
  if cv2.waitKey(1) & 0xFF == ord('a'):
    cv2.imwrite("photo.jpg", frame)
  # 按q離開
  if cv2.waitKey(1) & 0xFF == ord('q'):
    break

# 釋放攝影機
cap.release()

# 關閉所有 OpenCV 視窗
cv2.destroyAllWindows()

