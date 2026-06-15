import matplotlib.pyplot as plt

x = list(range(8, 18))

y1 = [
    0.000001,
    0.000005,
    0.000016,
    0.000060,
    0.000229,
    0.000959,
    0.003775,
    0.016702,
    0.059096,
    0.235514
]

y2 = [
    0.000001,
    0.000002,
    0.000004,
    0.000009,
    0.000019,
    0.000040,
    0.000086,
    0.000185,
    0.000393,
    0.000838
]

plt.figure(figsize=(8, 5))

plt.plot(x, y1, 'o-', label='Enumération code')
plt.plot(x, y2, 's-', label='Transformé Walsh')

plt.xlabel('n')
plt.ylabel('Temps (s)')
plt.title('Temps de calcul non linéarité')
plt.xticks(x)
plt.grid(True)
plt.legend()

# Très recommandé ici
plt.yscale('log')

plt.tight_layout()
plt.show()
