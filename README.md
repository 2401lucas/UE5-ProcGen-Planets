# UE5-ProcGen-Planets

This a project I did over a weekend. There are several ways to generate sphere vertices, I chose to go with the Icosahedron/Icosphere method.

# Generating a sphere
## Generating an Icosahedron
We get Icosahedron vertices by getting the corners of three orthogonal rectangles, each with a side length of the Golden Ratio. 

![image](https://user-images.githubusercontent.com/32739337/176906124-5cbf050b-86cb-4b42-b10b-b8126e02b8ee.png)

## Smoothing the Icosahedron
To get a shape that more resembles a sphere, we take each face and find the middle point of each side, this gives the ability to divide each triangle into 4 smaller triangles. An important note is that each new Vertex we generate needs the position updated to have the same radius as the original 12 vertices. If we don't do this, we will have loads more faces, but it will maintain the same shape of an Icosahedron.

![image](https://user-images.githubusercontent.com/32739337/176908472-28a0f40c-8d5a-4b98-b12f-0ec50ef76475.png)

## Recursion
In order to smooth the Icosahedron further, we can run the smoothing algorithm recursivly. This demonstrates the main disadvantage of generating a sphere using this method, which is lack of control of detail. The number of triangles increase quickly. The examples are 0 thru 5 recursion levels.

![image](https://user-images.githubusercontent.com/32739337/176916328-66b3b7e1-cc52-4463-a157-c27b3e1dd7db.png)
![image](https://user-images.githubusercontent.com/32739337/176916414-307587cc-54f7-4d55-85f6-2f18fe58dbaa.png)
![image](https://user-images.githubusercontent.com/32739337/176916450-58af8b8b-c9ca-412a-a847-06f4ebc4915e.png)
![image](https://user-images.githubusercontent.com/32739337/176916500-843376fc-0542-426a-a435-4466193a2cbc.png)
![image](https://user-images.githubusercontent.com/32739337/176916549-198d3fc6-bd6e-430c-97bd-709d1d50740e.png)
![image](https://user-images.githubusercontent.com/32739337/176916624-051c40bf-ad88-4a16-94b8-2a557e27cecc.png)


## The Importance of cashing Vertices
When generating Vertices, they register the with the FMeshDescriptionBuilder. If Vertex positions aren't cashed, each triangle will register their vertices even if other triangles share them and have already registered them. When cashing vertices, if the vertex is not found it is registered, if it is found the cashe would return the VertexID. Cashing vertices generates (Vertices Count - 2 * 6) extra vertices, quickly adding up. 
```
Recursion Level |    Vertices   |     Triangles  | Vertices Without a Cache
        0       |    12         |     20         |        60
        1       |    42         |     80         |        240
        2       |    162        |     320        |        960
        3       |    642        |     1280       |        3840
        4       |    2562       |     5120       |        15360
        5       |    10242      |     20480      |        61440
        6       |    40962      |     81920      |        245760
        7       |    163842     |     327650     |        983040
        8       |    655362     |     1310720    |        3932160
        9       |    2621442    |     5242880    |        15728640
       
```

# Adding Surface Detail 

## 3D Noise
For noise, the Engines PerlinNoise is used.
### Shape
To modify the shape of a planet, we use  an extremely low scaled noise with a higher amplitude to create very unique shapes.

![image](https://user-images.githubusercontent.com/32739337/176919585-1c77dd0f-6e7e-41c1-8371-26978ec16955.png)
![image](https://user-images.githubusercontent.com/32739337/176920446-7e0c3b4f-86b1-4a83-b37a-5adfe02365dc.png)
![image](https://user-images.githubusercontent.com/32739337/176920728-74609597-de2a-4faa-b538-de8b2b34795b.png)
![image](https://user-images.githubusercontent.com/32739337/176920956-659e87ca-0767-40ac-b68f-f1761e7fc572.png)

### Surface
![image](https://user-images.githubusercontent.com/32739337/176921312-78d78dec-51eb-465d-a7d3-07da3185a8f5.png)
![image](https://user-images.githubusercontent.com/32739337/176921462-38c4d913-6689-4587-aa40-1d64d3f0d0ac.png)

### Craters
![image](https://user-images.githubusercontent.com/32739337/176921833-8924a92c-87e1-4ff9-8903-4ee839693e71.png)
![image](https://user-images.githubusercontent.com/32739337/176921765-77b41c18-1b44-4128-ac6c-f3258484e30b.png)


## Ocean
![image](https://user-images.githubusercontent.com/32739337/176922289-d242a556-d62c-4663-97c5-21fe29675aff.png)
![image](https://user-images.githubusercontent.com/32739337/176922315-60aec632-e200-472e-9137-e520c5767f36.png)

## TODO
Add Colours
