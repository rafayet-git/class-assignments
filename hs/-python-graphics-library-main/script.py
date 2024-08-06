import mdl
import copy
from display import *
from matrix import *
from draw import *

def run(filename):
    """
    This function runs an mdl script
    """
    p = mdl.parseFile(filename)

    if p:
        (commands, symbols) = p
    else:
        print("Parsing failed.")
        return

    view = [0,
            0,
            1];
    ambient = [50,
               50,
               50]
    light = [[0.5,
              0.75,
              1],
             [255,
              255,
              255]]
    ltype = "flat"
    color = [0, 0, 0]
    tmp = new_matrix()
    ident( tmp )

    stack = [ [x[:] for x in tmp] ]
    screen = new_screen()
    zbuffer = new_zbuffer()
    tmp = []
    step_3d = 100
    consts = ''
    coords = {"new": copy.deepcopy(stack[-1])}
    # print(symbols)
    symbols['.white'] = ['constants',
                         {'red': [0.2, 0.5, 0.5],
                          'green': [0.2, 0.5, 0.5],
                          'blue': [0.2, 0.5, 0.5]}]
    reflect = '.white'

    for command in commands:
        print(command)
        c = command['op']
        args = command['args']

        if c == 'box':
            if command['constants']:
                reflect = command['constants']
            add_box(tmp,
                    args[0], args[1], args[2],
                    args[3], args[4], args[5])
            if command["cs"] and command["cs"] in coords:
                matrix_mult(coords[command["cs"]],tmp)
            else:
                matrix_mult( stack[-1], tmp )
            draw_polygons(tmp, screen, zbuffer, view, ambient, light, symbols, reflect, ltype)
            tmp = []
            reflect = '.white'
        elif c == 'sphere':
            if command['constants']:
                reflect = command['constants']
            add_sphere(tmp,
                       args[0], args[1], args[2], args[3], step_3d)
            if command["cs"] and command["cs"] in coords:
                matrix_mult(coords[command["cs"]],tmp)
            else:
                matrix_mult( stack[-1], tmp )
            draw_polygons(tmp, screen, zbuffer, view, ambient, light, symbols, reflect, ltype)
            tmp = []
            reflect = '.white'
        elif c == 'circle':
            if command['constants']:
                reflect = command['constants']
            add_circle(tmp, args[0], args[1], args[2], args[3], step_3d)
            if command["cs"] and command["cs"] in coords:
                matrix_mult(coords[command["cs"]],tmp)
            else:
                matrix_mult( stack[-1], tmp )
            draw_polygons(tmp, screen, zbuffer, view, ambient, light, symbols, reflect, ltype)
            tmp = []
            reflect = '.white'
        elif c == 'cylinder':
            if command['constants']:
                reflect = command['constants']
            add_cylinder(tmp, args[0], args[1], args[2], args[3], args[4], step_3d)
            if command["cs"] and command["cs"] in coords:
                matrix_mult(coords[command["cs"]],tmp)
            else:
                matrix_mult( stack[-1], tmp )
            draw_polygons(tmp, screen, zbuffer, view, ambient, light, symbols, reflect, ltype)
            tmp = []
            reflect = '.white'
        elif c == 'cone':
            if command['constants']:
                reflect = command['constants']
            add_cone(tmp, args[0], args[1], args[2], args[3], args[4], step_3d)
            if command["cs"] and command["cs"] in coords:
                matrix_mult(coords[command["cs"]],tmp)
            else:
                matrix_mult( stack[-1], tmp )
            draw_polygons(tmp, screen, zbuffer, view, ambient, light, symbols, reflect, ltype)
            tmp = []
            reflect = '.white'
        elif c == 'torus':
            if command['constants']:
                reflect = command['constants']
            add_torus(tmp,
                      args[0], args[1], args[2], args[3], args[4], step_3d)
            if command["cs"] and command["cs"] in coords:
                matrix_mult(coords[command["cs"]],tmp)
            else:
                matrix_mult( stack[-1], tmp )
            draw_polygons(tmp, screen, zbuffer, view, ambient, light, symbols, reflect, ltype)
            tmp = []
            reflect = '.white'
        elif c == 'line':
            nav = []
            add_point(nav, args[0],args[1],args[2])
            if command["cs0"] and command["cs0"] in coords:
                matrix_mult(coords[command["cs0"]],nav)
            else:
                matrix_mult( stack[-1], nav )
            nav2 = []
            add_point(nav2, args[0],args[1],args[2])
            if command["cs1"] and command["cs1"] in coords:
                matrix_mult(coords[command["cs1"]],nav2)
            else:
                matrix_mult( stack[-1], nav2 )
            add_edge(tmp,
            nav[0], nav[1], nav[2], nav2[0], nav2[1], nav2[2])
       
            draw_lines(tmp, screen, zbuffer, color)
            tmp = []
        elif c == 'move':
            tmp = make_translate(args[0], args[1], args[2])
            matrix_mult(stack[-1], tmp)
            stack[-1] = [x[:] for x in tmp]
            tmp = []
        elif c == 'scale':
            tmp = make_scale(args[0], args[1], args[2])
            matrix_mult(stack[-1], tmp)
            stack[-1] = [x[:] for x in tmp]
            tmp = []
        elif c == 'rotate':
            theta = args[1] * (math.pi/180)
            if args[0] == 'x':
                tmp = make_rotX(theta)
            elif args[0] == 'y':
                tmp = make_rotY(theta)
            else:
                tmp = make_rotZ(theta)
            matrix_mult( stack[-1], tmp )
            stack[-1] = [ x[:] for x in tmp]
            tmp = []
        elif c == 'push':
            stack.append([x[:] for x in stack[-1]] )
        elif c == 'pop':
            stack.pop()
        elif c == 'save_coord_system':
            coords[command["cs"]] = copy.deepcopy(stack[-1])
        elif c == 'shading':
            ltype = command['shade_type']
        elif c == 'mesh':
            parseMeshFile(args[0], tmp) 
            if tmp:
                if command['constants']:
                    reflect = command['constants']
                if command["cs"] and command["cs"] in coords:
                    matrix_mult(coords[command["cs"]],tmp)
                else:
                    matrix_mult( stack[-1], tmp )
                draw_polygons(tmp, screen, zbuffer, view, ambient, light, symbols, reflect, ltype)
            tmp = []
            reflect = '.white'
                
        elif c == 'display':
            display(screen)
        elif c == 'save':
            save_extension(screen, args[0])
