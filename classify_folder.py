import os, glob, shutil

dir = './build'
files = '*.png'

dst_img0 = './data/no_housing/cam0'
dst_img1 = './data/no_housing/cam1'
dst_img2 = './data/no_housing/cam2'
dst_img3 = './data/no_housing/cam3'

for img_file in sorted(glob.glob(os.path.join(dir, files))):
    src = img_file
    folder = img_file.split('_')[-1][0:4]
    if (folder == 'img0'):
        shutil.move(src, dst_img0)
    elif (folder == 'img1'):        
        shutil.move(src, dst_img1)
    elif (folder == 'img2'):        
        shutil.move(src, dst_img2)
    elif (folder == 'img3'):        
        shutil.move(src, dst_img3)
    else:
        print("Error: The name of this image file is wrong!")