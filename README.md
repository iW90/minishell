# 42 Cursus - minishell

<img src="https://game.42sp.org.br/static/assets/achievements/minishelln.png" alt="completion-with-bonus-badge" align="left">


O **minishell**, como o nome já sugere, é um programa que reproduz alguns comportamentos do terminal de comandos `shell`. O programa é desenvolvido em **C** e permite que o usuário interaja com o computador por meios de comandos de texto. O shell também oferece recursos como redirecionamento de entrada e saída, criação de scripts para automatização tarefas, controle de processos, entre outros, enquanto o **minishell** oferece apenas algumas dessas funcionalidades.

## Implementações <img src="https://img.shields.io/badge/GRADE-101%2F100-green" align="right">

- Prompt display.
- Histórico de comandos.
- Executáveis do sistema disponíveis no ambiente (`ls`, `cat`, `grep`, etc.).
- Executáveis locais (`./minishell`).
- Pipes (`|`) que redirecionam a saída de um comando para a entrada do próximo.
- Variáveis de ambiente (`$VAR`) que se expandem para seus valores.
- Variável especial `$?` que armazena o código de saída (exit code) do último comando executado (Exemplo: 200 Success).

### Sinais de Teclado

- <kbd>Ctrl</kbd> + <kbd>C</kbd>: Exibe uma nova linha de prompt.
- <kbd>Ctrl</kbd> + <kbd>D</kbd>: Sai do minishell.
- <kbd>Ctrl</kbd> + <kbd>\\</kbd>: Não faz nada.

### Redirecionadores

- `>` *\<arquivo>*: Redireciona a saída para o 'arquivo' especificado.
- `<` *\<arquivo>*: Redireciona  a entrada para o 'arquivo' especificado.
- `>>` *\<arquivo>*: Redireciona a saída, mas acrescenta ao final do arquivo ao invés de substituir o conteúdo.
- `<<` *\<delimitador>*: Permite a entrada de múltiplas linhas, terminando com o delimitador. Exibe um novo prompt interativo, lê a entrada até atingir o 'delimitador', redireciona a entrada do usuário para a entrada do comando (não atualiza o histórico).

### Builtins

- `echo` (e opção `-n`): Exibe mensagens ou variáveis na saída padrão.
- `cd` (com apenas um caminho, relativo ou absoluto): Altera o diretório atual através do caminho.
- `pwd` (sem opções): Exibe o caminho completo do diretório atual.
- `export` (sem opções): Usado para definir variáveis de ambiente (`VAR="valor"`).
- `unset` (sem opções): Remove as variáveis de ambiente (`unset VAR`).
- `env` (sem opções nem argunentos): Exibe todas as variáveis de ambiente do sistema e seu valor.
- `exit` (sem opções): Encerra a sessão do shell ou um script em execução.

