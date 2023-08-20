# CONVENÇÕES NO GIT

## Gitflow

### Branches principais:

- `main` - Branch principal, em produção, e funcionando sem bugs.
- `dev` - Branch secundária, onde se desenvolve, faz testes, etc.

### Branches temporárias:

- `feature/nome_da_branch`: Nova funcionalidade (dev);
- `release/nome_da_branch`: Lançamento de novos recursos (main);
- `hotfix/nome_da_branch`: Correção de bug (dev/main);

### Release:

Ao mesclar a release na main, o padrão é colocar o número da versão:

- **v1.0** - O número é trocado pela versão referente.

## Padronização de Commits

Primeiro digite um tipo (obrigatório):

- `feat:` Nova funcionalidade.
- `fix:` Correção de bug.
- `doc:` Alteração na documentação.
- `style:` Alteração visual (identação) e norminette.
- `refactor:` Melhorias no código.
- `test:` Testes unitários, TDD, etc.
- `revert:` Reversão de um commit.

Depois descreva o commit iniciando pelo verbo:

- add
- change
- remove
- update
- implement
- solve
- back to

etc.
