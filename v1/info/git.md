# CONVENÇÕES NO GIT

## Gitflow

Funciona apenas no local, servindo como um facilitador.

> Instalação: `sudo apt install git-flow`

### Configurando o Gitflow

Necessário configurar sempre que clonar o repositório novamente, já que é apenas local. Dentro da pasta raiz, digite:

`git flow init`

Branches principais:

- `main` - Branch principal, em produção, e funcionando sem bugs.
- `dev` - Branch secundária, onde se desenvolve, faz testes, etc.

Branches temporárias:

- `feature/`- Nova funcionalidade.
- `bugfix/` - Correção de bug em dev.
- `hotfix/` - Correção de bug tanto em dev quando na main.
- `release/` - Lançamento de novos recursos (ela que será mesclada na main).
- `support/` - Apenas suporte, se necessário.

Ao mesclar a release na main, o padrão é colocar o número da versão:

- **minishell-v1.0** - O número é trocado pela versão referente.

## Padronização de Commits

Primeiro digite um tipo (obrigatório):

- `feat:` Nova funcionalidade.
- `fix:` Correção de bug.
- `docs:` Alteração na documentação.
- `style:` Alteração visual (identação).
- `refactor:` Melhorias no código.
- `test:` Testes unitários, TDD, etc.
- `revert:` Reversão de um commit.
- `build:` Modificação nas dependências e arquivos de build.
- `chore:` Atualizações de tarefas de build, configurações de administrador, pacotes.
- `ci:` Mudanças relacionadas a integração contínua.
- `perf:` Melhorias de performance.

Depois descreva o commit iniciando pelo verbo:

- add
- change
- remove
- update
- implement
- back to

etc.

## Fluxo

Para cada nova alteração, uma branch deve ser criaada seguindo os padrões do Gitflow para branches temporárias.

Exemplo de adição de uma nova feature:

- `git flow feature start nome_do_feature`.
- Faça as alterações necessárias na sua branch e suba para o Github:
	- `git add *`
	- `git commit -m "feat: update file.c"`
	- `git push --set-upstream origin feature/nome_do_feature`
- Saia da branch:
	- `git checkout dev`
- Encerre o gitflow (ele fará o merge em dev automaticamete e vai fechar a branch):
	- `git flow feature finish nome_do_feature`
- Dê um push na dev para finalizar:
	- `git push`
