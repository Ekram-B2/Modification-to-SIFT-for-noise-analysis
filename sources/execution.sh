# Written by Ekram

# Compilation instructions
g++ project1.cpp api.cpp -o output_1 `pkg-config --cflags --libs opencv` -w
g++ project2.cpp api.cpp -o output_2 `pkg-config --cflags --libs opencv` -w
# Image partioning
./output_1 $1
# File paths
IMAGES_PATH=/home/4422/Images
BM3D_PATH=/home/ekram/4422/EECS4422/bm3d/build
# Apply BM3D
python bm3d.py 
# Rebuild image
./output_2 $1
# Apply contrast boost
python contrast_plus_SIFT.py $1
