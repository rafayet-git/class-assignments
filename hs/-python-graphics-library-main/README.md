# gfx-10-final

Parenthesis () are optional arguments while brackets [] are required.

## Coordinate system saving

Saves the top (current) coordinate stack to be used by next shapes or lines.

```
save_coord_system [name]
```

The saved coordinate stack can be used by all the 3D shape commands: sphere, circle, line, cylinder, cone, torus, box, mesh

```
shape [args] (cstack)
```

## New primitive shapes

* Circle : Generates a flat 3D circle ( Was intended for use with other shapes, but it worked by itself. )

```
circle (constants) [cx] [cy] [cz] [r] (cstack) 
```

* Cylinder : Generates a 3D cyllinder (centered at the back circle)

```
cylinder (constants) [cx] [cy] [cz] [r] [h] (cstack) 
```

* Cone : Generates a 3d cone (centered at the back circle, faces at pointy side)

```
cone  (constants) [cx] [cy] [cz] [r] [h] (cstack) 
```

## Meshes
Mesh files in .obj format can be generated using the "v" and "f" values, such as this:

```
v 1 2 3
v 4 5 6 
v 7 8 9
v 10 20 30

f 1 2 3
f 1 2 3 4
```

Only supports polygons with 3 or 4 vertices.

```
mesh (constants) :[filename.obj] (cstack)
```

## Shaded
Implemented phong shading, to calculate light values on every pixel
To be used before drawing an object.

```
shading phong
```

