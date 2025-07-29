import cv2
import numpy as np

# Callback function for trackbars (does nothing but required by createTrackbar)
def nothing(x):
    pass

# Initialize the camera
cam = cv2.VideoCapture(1)
#backends = [cv2.CAP_DSHOW, cv2.CAP_MSMF, cv2.CAP_VFW]
#rint(backends)
frame_width = int(cam.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))

# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
out = cv2.VideoWriter('output.mp4', fourcc, 20.0, (frame_width, frame_height))

# Create a window for sliders
cv2.namedWindow('Sliders')

# Create trackbarsqfor adjusting HSV ranges
cv2.createTrackbar('Lower H', 'Sliders', 20, 179, nothing)
cv2.createTrackbar('Lower S', 'Sliders', 100, 255, nothing)
cv2.createTrackbar('Lower V', 'Sliders', 100, 255, nothing)
cv2.createTrackbar('Upper H', 'Sliders', 30, 179, nothing)
cv2.createTrackbar('Upper S', 'Sliders', 255, 255, nothing)
cv2.createTrackbar('Upper V', 'Sliders', 255, 255, nothing)

while True:
    ret, frame = cam.read()

    if not ret:
        break

    # Get values from the trackbars
    lower_h = cv2.getTrackbarPos('Lower H', 'Sliders')
    lower_s = cv2.getTrackbarPos('Lower S', 'Sliders')
    lower_v = cv2.getTrackbarPos('Lower V', 'Sliders')
    upper_h = cv2.getTrackbarPos('Upper H', 'Sliders')
    upper_s = cv2.getTrackbarPos('Upper S', 'Sliders')
    upper_v = cv2.getTrackbarPos('Upper V', 'Sliders')

    # Define HSV range based on slider values
    lower_yellow = np.array([lower_h, lower_s, lower_v])
    upper_yellow = np.array([upper_h, upper_s, upper_v])

    # Convert the frame to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create a mask for yellow color
    mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

    # Find contours in the mask
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Flag to check if yellow color is detected
    yellow_detected = False
    bounding_box_count = 0

    for contour in contours:
        x, y, w, h = cv2.boundingRect(contour)

        # Draw the bounding box if the contour is large enough
        if cv2.contourArea(contour) > 500:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 255), 2)
            yellow_detected = True
            bounding_box_count += 1

    if yellow_detected:
        cv2.putText(frame, f'Corrosion Detected: {bounding_box_count}', 
                    (frame_width - 400, 30),  
                    cv2.FONT_HERSHEY_SIMPLEX, 
                    1,  
                    (0, 0, 255),  # Red color
                    2,  
                    cv2.LINE_AA)
    else:
        cv2.putText(frame, 'No Corrosion', 
                    (frame_width - 250, 30),  
                    cv2.FONT_HERSHEY_SIMPLEX, 
                    1,  # Font size
                    (50, 150, 50),  # Green color
                    2,  
                    cv2.LINE_AA)

    out.write(frame)
    cv2.imshow('Camera', frame)
    cv2.imshow('Mask', mask)

    if cv2.waitKey(1) == ord('q'):
        break

cam.release()
out.release()
cv2.destroyAllWindows()
