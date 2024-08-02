""""
v = 顶点pos
vn = 法线
vt = uv
f = 面索引(顶点/uv/法线)
目标：顶点 uv 法线
"""
v = []
vn = []
vt = []
f = []
fa = []

with open(f"../assets/sphere.obj", 'r') as file:
    obj = file.read()

for line in obj.split('\n'):
    if len(line) > 0:
        # 法线
        if line.split(' ')[0] == "vn":
            vn.append(line[line.find(' ') + 1:].split(' '))
        # uv
        if line.split(' ')[0] == "vt":
            vt.append(line[line.find(' ') + 1:].split(' '))
        # 顶点
        if line.split(' ')[0] == "v":
            v.append(line[line.find(' ') + 1:].split(' '))
        # 面索引
        if line.split(' ')[0] == "f":
            # 1 2 3 4 -> 1 2 3 | 3 4 1
            face = line[line.find(' ') + 1:]
            if len(face.split(' ')) == 4:
                faces = face.split(' ')
                faces.insert(3, faces[2])
                faces.append(faces[0])
                f.append(faces[0:3])
                f.append(faces[3:])
            else:
                f.append(face.split(' '))

result = "float vertices[] = {\n"

for face in f:
    temp = []
    for i in range(3):
        a = face[i].split('/')
        for b in a:
            temp.append(int(b))
    fa.append(temp)

for face in fa:
    for i in range(0, 9, 3):
        for j in range(3):
            result += (str(v[face[i]-1][j]) + "f,")
        for j in range(2):
            result += (str(vt[face[i + 1]-1][j]) + "f,")
        for j in range(3):
            result += (str(vn[face[i + 2]-1][j]) + "f,")
        result += "\n"

result = result[:-2] + "\n};"

with open("../include/mesh.h", 'w') as file:
    file.write(result)