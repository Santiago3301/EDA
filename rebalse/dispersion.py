import matplotlib.pyplot as plt

# parámetros
s, t = 1000, 9999
M = 10

# función hash
def hash_linear(codigo):
    return (codigo - s) * M // (t - s + 1)

# generar códigos
codigos = range(s, t + 1)

# calcular índices
indices = [hash_linear(c) for c in codigos]

# histograma
plt.hist(indices, bins=M, edgecolor='black')
plt.xticks(range(M))
plt.xlabel("Índice del hash")
plt.ylabel("Cantidad de códigos")
plt.title("Distribución de códigos usando hash lineal")
plt.show()