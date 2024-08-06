import math
from display import *


  # IMPORANT NOTE

  # Ambient light is represeneted by a color value

  # Point light sources are 2D arrays of doubles.
  #      - The fist index (LOCATION) represents the vector to the light.
  #      - The second index (COLOR) represents the color.

  # Reflection constants (ka, kd, ks) are represened as arrays of
  # doubles (red, green, blue)

AMBIENT = 0
DIFFUSE = 1
SPECULAR = 2
LOCATION = 0
COLOR = 1
SPECULAR_EXP = 4

#lighting functions
def get_lighting(normal, view, ambient, light, symbols, reflect ):

    n = normal[:]
    normalize(n)
    normalize(light[LOCATION])
    normalize(view)
    r = symbols[reflect][1]

    a = calculate_ambient(ambient, r)
    d = calculate_diffuse(light, r, n)
    s = calculate_specular(light, r, view, n)

    i = [0, 0, 0]
    i[RED] = int(a[RED] + d[RED] + s[RED])
    i[GREEN] = int(a[GREEN] + d[GREEN] + s[GREEN])
    i[BLUE] = int(a[BLUE] + d[BLUE] + s[BLUE])
    limit_color(i)

    return i

def calculate_ambient(alight, reflect):
    a = [0, 0, 0]
    a[RED] = alight[RED] * reflect['red'][AMBIENT]
    a[GREEN] = alight[GREEN] * reflect['green'][AMBIENT]
    a[BLUE] = alight[BLUE] * reflect['blue'][AMBIENT]
    return a

def calculate_diffuse(light, reflect, normal):
    d = [0, 0, 0]

    dot = dot_product( light[LOCATION], normal)

    dot = dot if dot > 0 else 0
    d[RED] = light[COLOR][RED] * reflect['red'][DIFFUSE] * dot
    d[GREEN] = light[COLOR][GREEN] * reflect['green'][DIFFUSE] * dot
    d[BLUE] = light[COLOR][BLUE] * reflect['blue'][DIFFUSE] * dot
    return d

def calculate_specular(light, reflect, view, normal):
    s = [0, 0, 0]
    n = [0, 0, 0]

    result = 2 * dot_product(light[LOCATION], normal)
    n[0] = (normal[0] * result) - light[LOCATION][0]
    n[1] = (normal[1] * result) - light[LOCATION][1]
    n[2] = (normal[2] * result) - light[LOCATION][2]

    result = dot_product(n, view)
    result = result if result > 0 else 0
    result = pow( result, SPECULAR_EXP )

    s[RED] = light[COLOR][RED] * reflect['red'][SPECULAR] * result
    s[GREEN] = light[COLOR][GREEN] * reflect['green'][SPECULAR] * result
    s[BLUE] = light[COLOR][BLUE] * reflect['blue'][SPECULAR] * result
    return s

def limit_color(color):
    color[RED] = 255 if color[RED] > 255 else color[RED]
    color[GREEN] = 255 if color[GREEN] > 255 else color[GREEN]
    color[BLUE] = 255 if color[BLUE] > 255 else color[BLUE]

#vector functions
#normalize vetor, should modify the parameter
def normalize(vector):
    magnitude = math.sqrt( vector[0] * vector[0] +
                           vector[1] * vector[1] +
                           vector[2] * vector[2])
    for i in range(3):
        if magnitude != 0.0:
            vector[i] = vector[i] / magnitude

#Return the dot porduct of a . b
def dot_product(a, b):
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]

#Calculate the surface normal for the triangle whose first
#point is located at index i in polygons
def calculate_normal(polygons, i):

    A = [0, 0, 0]
    B = [0, 0, 0]
    N = [0, 0, 0]

    A[0] = polygons[i+1][0] - polygons[i][0]
    A[1] = polygons[i+1][1] - polygons[i][1]
    A[2] = polygons[i+1][2] - polygons[i][2]

    B[0] = polygons[i+2][0] - polygons[i][0]
    B[1] = polygons[i+2][1] - polygons[i][1]
    B[2] = polygons[i+2][2] - polygons[i][2]

    N[0] = A[1] * B[2] - A[2] * B[1]
    N[1] = A[2] * B[0] - A[0] * B[2]
    N[2] = A[0] * B[1] - A[1] * B[0]

    return N

def calculate_normal_vector(polygons,map):
    count = {}
    total = {}
    point = 0
    while point < len(polygons) - 2:
        normal = calculate_normal(polygons, point)
        pt = point+3
        while point < pt:
            if tuple(polygons[point]) in count:
                count[tuple(polygons[point])] += 1
                total[tuple(polygons[point])][0] += normal[0] 
                total[tuple(polygons[point])][1] += normal[1]
                total[tuple(polygons[point])][2] += normal[2]
                #print(total[tuple(polygons[point])])

            else:
                count[tuple(polygons[point])] = 1
                total[tuple(polygons[point])] = [normal[0], normal[1], normal[2]]
            point += 1
    for vertex in total:
        total[vertex][0] /= count[vertex]
        total[vertex][1] /= count[vertex]
        total[vertex][2] /= count[vertex]
        normalize(total[vertex])
        map[vertex] = [total[vertex][0], total[vertex][1] ,total[vertex][2] ]
    
        
def get_normal_phong(map, x, y, z, polygons, point):
    n1 = map[tuple(polygons[point])]
    n2 = map[tuple(polygons[point+1])]
    n3 = map[tuple(polygons[point+2])]
    
    total_area = calculate_triangle_area(polygons[point], polygons[point+1], polygons[point+2])
    area1 = calculate_triangle_area(polygons[point+1], polygons[point+2], [x, y, z])
    area2 = calculate_triangle_area(polygons[point+2], polygons[point], [x, y, z])
    area3 = calculate_triangle_area(polygons[point], polygons[point+1], [x, y, z])
    
    if total_area != 0:
        weight1 = area1 / total_area
        weight2 = area2 / total_area
        weight3 = area3 / total_area
    else:
        weight1 = weight2 = weight3 = 0
    new_normal = [
        weight1 * n1[0] + weight2 * n2[0] + weight3 * n3[0],
        weight1 * n1[1] + weight2 * n2[1] + weight3 * n3[1],
        weight1 * n1[2] + weight2 * n2[2] + weight3 * n3[2]
    ]

    normalize(new_normal)

    return new_normal

def calculate_triangle_area(p1, p2, p3):
    cross_product = [
        (p2[1] - p1[1]) * (p3[2] - p1[2]) - (p2[2] - p1[2]) * (p3[1] - p1[1]),
        (p2[2] - p1[2]) * (p3[0] - p1[0]) - (p2[0] - p1[0]) * (p3[2] - p1[2]),
        (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0])
    ]

    return 0.5 * math.sqrt(cross_product[0] ** 2 + cross_product[1] ** 2 + cross_product[2] ** 2)