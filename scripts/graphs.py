import pandas as pd
import matplotlib.pyplot as plt

# 1. Leer los resultados del cronómetro
try:
    df = pd.read_csv("reports/csv/benchmark.csv")
except FileNotFoundError:
    print("Error: No se encontró benchmark.csv. Corre 'python3 scripts/benchmark.py' primero.")
    exit()

# 2. Configurar la gráfica
plt.figure(figsize=(10, 6))
plt.plot(df['size'], df['time'], marker='o', linestyle='-', color='b', linewidth=2)

# 3. Decorar la gráfica
plt.title('Rendimiento del Simulador OS (Benchmarking)', fontsize=16)
plt.xlabel('Cantidad de Procesos Simulados', fontsize=12)
plt.ylabel('Tiempo de Ejecución (Segundos)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)

# 4. Guardar la imagen en la carpeta reports/png/
output_path = "reports/png/benchmark_plot.png"
plt.savefig(output_path, dpi=300, bbox_inches='tight')
print(f"¡Gráfica generada con éxito! Se guardó en: {output_path}")