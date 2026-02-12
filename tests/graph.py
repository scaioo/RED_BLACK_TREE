import pandas as pd
import matplotlib.pyplot as plt

# Carica i dati generati dal C++
df = pd.read_csv('rbt_ratio_stats.csv')

plt.figure(figsize=(10, 6))

# Plot Ratio Insert con Barre di Errore (Sigma)
plt.errorbar(df['N'], df['RatioInsert_Mean'], yerr=df['RatioInsert_Sigma'], 
             fmt='-o', capsize=5, label='Ratio Insert (Mean ± σ)', color='blue')

# Plot Ratio Delete con Barre di Errore (Sigma)
plt.errorbar(df['N'], df['RatioDelete_Mean'], yerr=df['RatioDelete_Sigma'], 
             fmt='-s', capsize=5, label='Ratio Delete (Mean ± σ)', color='red')

plt.xscale('log') # Fondamentale
plt.xlabel('Input Size (N)')
plt.ylabel('Ratio coefficient (Time / N log N)')
plt.title('Stabilità Asintotica: Analisi del Ratio con Deviazione Standard')
plt.grid(True, which="both", ls="-", alpha=0.5)
plt.legend()

plt.tight_layout()
plt.show()