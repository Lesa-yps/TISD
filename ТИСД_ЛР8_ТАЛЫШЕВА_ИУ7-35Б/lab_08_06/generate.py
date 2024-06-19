import numpy as np

def generate_connected_graph_edges(num_vertices):
    edges = []
    for i in range(num_vertices):
        for j in range(i + 1, num_vertices):
            weight = np.random.randint(-10, 10)
            edges.append((i, j, weight))
    return edges

def save_edges_to_file(edges, filename, num_vertices):
    with open(filename, 'w') as file:
        file.write(f"{num_vertices}\n")  # Записываем количество вершин в файл
        for edge in edges:
            if edge[2] > 0:
                file.write(f"{edge[0]} {edge[1]} {edge[2]}\n")

def generate_and_save_graph(num_vertices, filename_prefix):
    edges = generate_connected_graph_edges(num_vertices)

    edges_filename = f"{filename_prefix}.txt"
    save_edges_to_file(edges, edges_filename, num_vertices)

    print(f"Ребра сохранены в файл {edges_filename}.")

# Генерируем и сохраняем графы для 10, 50 и 100 вершин
generate_and_save_graph(10, "test/graph_10")
generate_and_save_graph(50, "test/graph_50")
generate_and_save_graph(100, "test/graph_100")
for i in range (5, 11):
    generate_and_save_graph(i, str(i))
generate_and_save_graph(15, "15")
