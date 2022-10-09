# HeightmapTerrain
A Terrain generated using a Heightmap
------------------------------------------------------------------------------------------------------------
How to run via command line:
  First parameter - The heightmap image you want to generate the terrain from.
  Second paramter [optional] - The texture you want your terrain to have.
------------------------------------------------------------------------------------------------------------
Controls:
  WASD - Camera movement
  SPACE - Move camera upwards
  LEFT CTRL - Move camera downwards
  MOUSE - Camera look (rotation)

  ESC - Close program
  F2  - Switch between mouse or free view
  F3  - Change render mode (Points, Lines, Triangles and Opaque)
  F4  - Turns attenuation on (light losing strength by distance)
  F5  - Enable normal map visualization

  RIGHT SHIFT - Move the light upwards
  RIGHT CTRL  - Move the light downwards
  ARROW KEYS  - Controls the light source
------------------------------------------------------------------------------------------------------------
TODO:
  Dynamic LOD (Tessellation)
------------------------------------------------------------------------------------------------------------
NOTES:
  Some artifacts are present because of the resolution of the heightmap image. To make it better, please use a noise map generated from a reliable source.
------------------------------------------------------------------------------------------------------------
![b1](https://user-images.githubusercontent.com/19862090/194765744-f0d21f1a-47db-4496-9c41-9074b784f99c.png)
![b2](https://user-images.githubusercontent.com/19862090/194765746-b6710d0f-a935-46a0-8e92-772829b5cf27.png)
![b3](https://user-images.githubusercontent.com/19862090/194765747-f7ee607e-fd61-480e-a2f1-5b6d1a65d44d.png)
![b4](https://user-images.githubusercontent.com/19862090/194765751-67cf11cf-a834-420c-b16f-57fb02fe49e0.png)
![b5](https://user-images.githubusercontent.com/19862090/194765753-0c454775-d19f-4b3e-a415-ab63ad143097.png)
![b6](https://user-images.githubusercontent.com/19862090/194765755-b1161613-959e-48ef-ac87-e0f8ae6e9219.png)
![b7](https://user-images.githubusercontent.com/19862090/194765757-907223e8-f244-438b-bc0c-5f0fe25acbaf.png)
