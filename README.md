# Comparação de algoritmos de ordenação

Trabalho de Projeto e Análise de Algoritmos. Mede o tempo de execução de
Bubble, Insertion, Selection, Shell, Quick, Heap e Merge Sort em vetores de
inteiros aleatórios com 10, 100, 1.000, 10.000 e 100.000 elementos, com 10
repetições por tamanho (7 × 5 × 10 = 350 medições).

## Estrutura

| Arquivo | Função |
|---|---|
| `algoritmos.c` / `algoritmos.h` | Os sete algoritmos |
| `teste.c` / `teste.h` | Gerador de vetores, cópia, cronômetro e verificação de ordem |
| `main.c` | Modos de execução, laços de tamanhos e repetições, gravação do CSV |
| `Resultados/resultados.csv` | As 350 medições (uma linha por execução) |
| `Resultados/analise.py` | Médias, fatores de crescimento, tabelas e gráficos |
| `Resultados/relatorio.pdf` | Relatório com a análise dos resultados |

## Compilar

```powershell
gcc main.c algoritmos.c teste.c -o ordenacao -Wall -Wextra -O2 -std=c11
```

## Executar

```powershell
.\ordenacao            # teste completo -> resultados.csv (alguns minutos)
.\ordenacao rapido     # teste curto, até 1.000 elementos -> resultados_rapido.csv
.\ordenacao demo       # mostra um vetor de 10 elementos antes e depois de cada algoritmo
```

O teste completo leva alguns minutos: com 100.000 elementos, o Bubble Sort passa
de 10 segundos por repetição. Use `rapido` para conferir o programa em segundos.

## Gerar tabelas e gráficos

```powershell
cd Resultados
pip install pandas matplotlib
python analise.py
```

Gera `tabela_medias.csv`, `tabela_medias_excel.csv` (separador `;` e vírgula
decimal, para abrir no Excel em português), `grafico_log.png` e
`grafico_rapidos.png`.

## Como os testes são feitos

- **Mesma entrada para todos.** A cada repetição é gerado um vetor aleatório e os
  sete algoritmos ordenam cópias idênticas dele.
- **Semente fixa.** O gerador usa `srand(12345)`: rodar o programa de novo gera os
  mesmos vetores. Os tempos, porém, mudam de uma execução para outra, porque
  dependem do estado do computador.
- **Valores de 30 bits.** Cada número junta 15 bits de duas chamadas a `rand()`,
  pois no Windows `rand()` sozinho só chega a 32.767.
- **O que entra na medição.** Só a chamada do algoritmo. Ficam fora a geração do
  vetor, a cópia, a verificação de ordem e a gravação do CSV. O Merge Sort inclui
  a alocação do seu vetor auxiliar, porque ela acontece dentro da função.
- **Cronômetro.** `QueryPerformanceCounter` no Windows (resolução de
  nanossegundos) e `clock_gettime` em Linux/Mac. Os resultados do trabalho foram
  medidos no Windows; a versão para Linux foi apenas compilada e executada para
  conferir o funcionamento.
- **Verificação.** Após cada ordenação, o programa confere se o vetor está
  crescente e grava o resultado na coluna `ordenado` do CSV.

## Observações

- O tamanho de 1.000.000 de elementos não foi executado (ver o relatório, seção 6).
- Ambiente dos testes: **[processador, RAM, versão do gcc]**.
