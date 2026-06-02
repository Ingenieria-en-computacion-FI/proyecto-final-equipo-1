import random

# Abrimos (o creamos) un archivo txt/csv para guardar los datos generados
with open("data/inputs/procesos.csv", "w") as file:
    for i in range(10):
        burst = random.randint(1, 20)
        memory = random.randint(10, 500)
        
        # Guardamos en formato: pid,burst_time,memory
        file.write(f"{i},{burst},{memory}\n")
        
print("Archivo de procesos generado exitosamente en data/inputs/procesos.csv")
