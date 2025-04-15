This is a OpenGL based (imgui) mini node based photoshop. The graphical node based image editing makes it very intuitive to edit an image. It is powered by OpenCV in the backend for image processing related tasks.
Features Implemented
- Drag-and-drop node editor interface using imgui-node-editor
- File operations: load input image, export output image
- Real-time visual previews on each node
- Graph execution engine with cycle detection and caching
- Interactive parameter controls and histograms for threshold node

Nodes and their functions:
- Image Input Node – Load image and display metadata
- Output Node – Save and preview final image
- Brightness/Contrast Node – Adjustable sliders for both parameters
- Color Channel Splitter – Outputs R, G, B, and grayscale
- Blur Node – Gaussian + uniform/directional blur with kernel preview
- Threshold Node – Binary, adaptive, and Otsu thresholding with histogram
- Edge Detection Node – Sobel and Canny with configuration UI
- Blend Node – Normal, multiply, screen, overlay, difference modes
- Noise Generation Node – Perlin, Simplex, Worley with scale/octaves/persistence
- Convolution Filter Node – 3×3 or 5×5 custom kernel with visual feedback

Demo: https://drive.google.com/file/d/1cRZnrwlUjQCElgVCkk-vu2Tf7tUNQF3_/view?usp=drive_link

Credits/Forks:
- https://github.com/ArthurSonzogni/smkflow
- https://github.com/ocornut/imgui

Contact: 
- asoni@arizona.edu
- anirudha.psoni@gmail.com

<img width="1281" alt="Screenshot 2025-04-15 at 7 29 29 AM" src="https://github.com/user-attachments/assets/ef3949aa-75ba-496a-8a7a-5c79c5b31351" />

<img width="1281" alt="Screenshot 2025-04-15 at 8 02 24 AM" src="https://github.com/user-attachments/assets/9dbdeebd-8545-4654-ac0e-e16ffd701e07" />
