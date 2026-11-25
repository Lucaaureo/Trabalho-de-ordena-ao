"""
Analise dos resultados do trabalho de ordenacao.

Entrada : resultados.csv (colunas: algoritmo,n,repeticao,tempo_s,ordenado)
Saidas  : tabela_medias.csv, grafico_log.png, grafico_rapidos.png

Como executar:  python analise.py
Requer:         pip install pandas matplotlib
"""
import pandas as pd
import matplotlib.pyplot as plt

ORDEM = ["Bubble", "Insertion", "Selection", "Shell", "Quick", "Heap", "Merge"]

# 1) Ler o CSV e conferir que tudo foi ordenado corretamente
df = pd.read_csv("resultados.csv")
assert (df["ordenado"] == 1).all(), "Algum algoritmo nao ordenou direito!"

# 2) Media e desvio padrao das 10 repeticoes de cada (algoritmo, n)
grupo = df.groupby(["algoritmo", "n"])["tempo_s"]
media = grupo.mean().unstack("n").loc[ORDEM]      # linhas = algoritmos, colunas = n
desvio = grupo.std().unstack("n").loc[ORDEM]

media.to_csv("tabela_medias.csv", float_format="%.9f")
print("Medias (s):")
print(media.to_string(float_format=lambda x: f"{x:.6f}"))

# 3) Fator de crescimento ao multiplicar n por 10 (confere a teoria)
print("\nFator de crescimento do tempo (n -> 10n):")
fator = media.T.pct_change().add(1).T.drop(columns=media.columns[0])
print(fator.to_string(float_format=lambda x: f"{x:.1f}x"))

"""
Analise dos resultados do trabalho de ordenacao.

Entrada : resultados.csv (colunas: algoritmo,n,repeticao,tempo_s,ordenado)
Saidas  : tabela_medias.csv, grafico_log.png, grafico_rapidos.png

Como executar:  python analise.py
Requer:         pip install pandas matplotlib
"""
import pandas as pd
import matplotlib.pyplot as plt

ORDEM = ["Bubble", "Insertion", "Selection", "Shell", "Quick", "Heap", "Merge"]

# 1) Ler o CSV e conferir que tudo foi ordenado corretamente
df = pd.read_csv("resultados.csv")
assert (df["ordenado"] == 1).all(), "Algum algoritmo nao ordenou direito!"

# 2) Media e desvio padrao das 10 repeticoes de cada (algoritmo, n)
grupo = df.groupby(["algoritmo", "n"])["tempo_s"]
media = grupo.mean().unstack("n").loc[ORDEM]      # linhas = algoritmos, colunas = n
desvio = grupo.std().unstack("n").loc[ORDEM]

media.to_csv("tabela_medias.csv", float_format="%.9f")
# versao para abrir direto no Excel em portugues (separador ; e virgula decimal)
media.to_csv("tabela_medias_excel.csv", sep=";", decimal=",", float_format="%.9f")
print("Medias (s):")
print(media.to_string(float_format=lambda x: f"{x:.6f}"))

# 3) Fator de crescimento ao multiplicar n por 10 (confere a teoria)
print("\nFator de crescimento do tempo (n -> 10n):")
fator = media.T.pct_change().add(1).T.drop(columns=media.columns[0])
print(fator.to_string(float_format=lambda x: f"{x:.1f}x"))

# 4) Grafico 1: todos os algoritmos, eixos logaritmicos
fig, ax = plt.subplots(figsize=(8, 5))
for alg in ORDEM:
    ax.errorbar(media.columns, media.loc[alg], yerr=desvio.loc[alg],
                marker="o", capsize=3, label=alg)
ax.set_xscale("log")
ax.set_yscale("log")
ax.set_xlabel("Quantidade de elementos (n)")
ax.set_ylabel("Tempo medio (s)")
ax.set_title("Tempo de execucao x tamanho da entrada (10 repeticoes)")
ax.grid(True, which="both", alpha=0.3)
ax.legend()
fig.tight_layout()
fig.savefig("grafico_log.png", dpi=150)

# 5) Grafico 2: so os algoritmos rapidos, eixo y linear (senao somem na escala)
rapidos = ["Shell", "Quick", "Heap", "Merge"]
fig, ax = plt.subplots(figsize=(8, 5))
for alg in rapidos:
    ax.plot(media.columns, media.loc[alg] * 1000, marker="o", label=alg)
ax.set_xlabel("Quantidade de elementos (n)")
ax.set_ylabel("Tempo medio (ms)")
ax.set_title("Algoritmos O(n log n) e Shell Sort")
ax.grid(True, alpha=0.3)
ax.legend()
fig.tight_layout()
fig.savefig("grafico_rapidos.png", dpi=150)
print("\nArquivos gerados: tabela_medias.csv, tabela_medias_excel.csv, "
      "grafico_log.png, grafico_rapidos.png")
