#!/bin/bash

# Configurações
USUARIO="arleswasb"
PASTA_DESTINO="mpi-projects"

# Lista dos nomes dos seus repositórios no GitHub (adicione os 16 restantes aqui)
# Exemplo: REPOS=("nome-do-repo-2" "nome-do-repo-3" ...)
REPOS=(
    "projeto_SD_02"
    "projeto_PP_03"
    "projeto_PP_04"
    "projeto_PP_05"
    "projeto_PP_06"
    "projeto_PP_07"
    "projeto_PP_08"
    "projeto_PP_09"
    "projeto_PP_10"
    "projeto_PP_11"
    "projeto_PP_12"
    "projeto_PP_13"
    "projeto_PP_14"
    "projeto_PP_15"
    "projeto__PP_16"
    "projeto_PP_18"
    "projeto_PP_19"

    # Adicione os outros nomes aqui...
)

# Contador para nomear as pastas seguindo seu padrão (começando do 02)
CONTADOR=2

for REPO_NOME in "${REPOS[@]}"
do
    # Formata o número da pasta (ex: 02, 03, 10)
    NUM_PASTA=$(printf "%02d" $CONTADOR)
    NOME_SUBPASTA="project_$NUM_PASTA"
    
    echo "---------------------------------------------------"
    echo "📥 Processando: $REPO_NOME -> $NOME_SUBPASTA"
    
    # 1. Adiciona o repositório antigo como um remoto temporário
    git remote add temp_repo "https://github.com/$USUARIO/$REPO_NOME.git"
    git fetch temp_repo
    
    # 2. Mescla o histórico (tentando main ou master)
    git merge temp_repo/main --allow-unrelated-histories -m "Importando $REPO_NOME para $NOME_SUBPASTA" || \
    git merge temp_repo/master --allow-unrelated-histories -m "Importando $REPO_NOME para $NOME_SUBPASTA"

    # 3. Cria a pasta e move os arquivos
    mkdir -p "$PASTA_DESTINO/$NOME_SUBPASTA"
    
    # Move arquivos ignorando o que não deve ser movido
    # (Não movemos a pasta .git, a pasta mpi-projects e o README principal)
    find . -maxdepth 1 ! -name ".git" ! -name "$PASTA_DESTINO" ! -name "README.md" ! -name "." -exec mv {} "$PASTA_DESTINO/$NOME_SUBPASTA/" \;

    # 4. Limpa o remoto e faz o commit da organização
    git remote remove temp_repo
    git add .
    git commit -m "Organizado: $REPO_NOME movido para $PASTA_DESTINO/$NOME_SUBPASTA"
    
    let CONTADOR++
done

echo "✅ Tudo pronto! Agora é só rodar: git push origin main"
