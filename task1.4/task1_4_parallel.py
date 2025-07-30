import face_recognition
import os
import subprocess
from multiprocessing import Pool, cpu_count

# adding knownman face 
known_image = face_recognition.load_image_file('known_man.jpg')
known_encoding = face_recognition.face_encodings(known_image)[0]

# for imageset folder
image_folder = 'imageset'
image_list = [os.path.join(image_folder, img) for img in os.listdir(image_folder) if img.endswith(('.jpg', '.png'))]

def process_image(image_path):
    try:
        unknown_image = face_recognition.load_image_file(image_path)
        unknown_encodings = face_recognition.face_encodings(unknown_image)

        if len(unknown_encodings) == 0:
            return (image_path, False)

        
        for unknown_encoding in unknown_encodings:
            result = face_recognition.compare_faces([known_encoding], unknown_encoding, tolerance=0.45)
            if result[0]:
                return (image_path, True)
        return (image_path, False)
    except Exception as e:
        return (image_path, False)

if __name__ == '__main__':
    print(f"Using {cpu_count()} CPU cores for parallel processing...")

    with Pool(cpu_count()) as pool:
        results = pool.map(process_image, image_list)

    print("\n--- Matching Results ---")
    for img_path, match in results:
        if match:
            print(f"{os.path.basename(img_path)} --> 🚩 Match Found!")

            # a path to open the image
            full_path = os.path.abspath(img_path)
            subprocess.run(['open', full_path]) 

        else:
            print(f"{os.path.basename(img_path)} --> No Match")
